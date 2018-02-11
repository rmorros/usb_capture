// --------------------------------------------------------------
// Copyright (C)
// Universitat Politecnica de Catalunya (UPC) - Barcelona - Spain
// --------------------------------------------------------------

//!
//!  \file synchro2usb.cpp
//!
//!  Add brief description of the file here
//!

//! https://stackoverflow.com/questions/44490743/how-to-extract-timestamps-from-each-frame-obtained-by-usb-camera

#include <iostream>
#include <fstream>
#include <ctime>
#include <sys/time.h>

#include <opencv2/opencv.hpp>
//include <opencv/highgui.h>
#include "synchro2usb.hpp"

using namespace cv;


// https://stackoverflow.com/questions/16357999/current-date-and-time-as-string
std::string mytimestr(bool ms)
{
  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,sizeof(buffer),"%d-%m-%Y-%I-%M-%S",timeinfo);

  if (ms)
  {
      struct timeval tv;
      gettimeofday(&tv, NULL); 
      sprintf(buffer, "%s-%d",buffer,tv.tv_usec/1000);
  }

  return std::string(buffer);
}




int main()
{

    // TODO: change the width, height, and capture FPS to your desired
    // settings.
    int width  = 640;
    int height = 480;
    double fps =  25.0;  

    cv::VideoCapture captureL(0);
    if (!captureL.isOpened())
    {
        std::cout << "L doesn't work" << std::endl;
        return -1;
    }
    VideoCapture captureR(1);
    if (!captureR.isOpened())
    {
        std::cout << "R doesn't work" << std::endl;
        return -1;
    }

    captureL.set(CAP_PROP_FRAME_WIDTH,  width);
    captureL.set(CAP_PROP_FRAME_HEIGHT, height);
    captureL.set(CAP_PROP_FPS, fps); // Does not work! Camera always captures at ~30fps

    captureR.set(CAP_PROP_FRAME_WIDTH,  width);
    captureR.set(CAP_PROP_FRAME_HEIGHT, height);
    captureR.set(CAP_PROP_FPS, fps); // Does not work! Camera always captures at ~30fps

    
    cv::Mat frameL, frameR, frame;

    uint64 msecCounterL = 0;
    uint64 frameNumberL = 0;

    uint64 msecCounterR = 0;
    uint64 frameNumberR = 0;
    
    uint64 counterL = 0, counterR = 0;
    std::string NAME = mytimestr(false);

    //int ex = -1; // Pop-up window asking for available codecs
    int codec = CV_FOURCC('M','J','P','G');

    VideoWriter outputVideo;
    Size S = Size(width, height);
    outputVideo.open(NAME+".avi" , codec, fps, S, true);

    std::ofstream index_file(NAME.c_str(), std::ofstream::out);

    long frame_num = 0;

    bool okL, okR, resL, resR;

    int debug_count = 0;

    std::cout << "TP" << debug_count++ << std::endl;
    
    for (;;)
    {
        // Instead of cap >> frame; we'll do something different.
        //
        // VideoCapture::grab() tells OpenCV to grab a frame from
        // the camera, but to not worry about all the color conversion
        // and processing to convert that frame into BGR.
        //
        // This means there's less processing overhead, so the time
        // stamp will be more accurate because we are fetching it
        // immediately after.
        //
        // grab() should also wait for the next frame to be available
        // based on the capture FPS that is set, so it's okay to loop
        // continuously over it.

        okL = captureL.grab();
        std::string stsL = mytimestr(true);
        okR = captureR.grab();
        std::string stsR = mytimestr(true);

        std::cout << "TP" << debug_count++ << std::endl;
        
        if(okL && okR)
        {
            msecCounterL = (uint64) captureL.get(CAP_PROP_POS_MSEC);
            //frameNumberL = (uint64) captureL.get(CAP_PROP_POS_FRAMES);
            msecCounterR = (uint64) captureR.get(CAP_PROP_POS_MSEC);
            //frameNumberR = (uint64) captureR.get(CAP_PROP_POS_FRAMES);

            std::cout << "TP" << debug_count++ << std::endl;

            // VideoCapture::retrieve color converts the image and places
            // it in the Mat that you provide.
            resL = captureL.retrieve(frameL);
            resR = captureR.retrieve(frameR);

            std::cout << "TP" << debug_count++ << std::endl;

            if (resL && resR)
            {
                cv::hconcat(frameL, frameR, frame);
                outputVideo.write(frame);

                // Save frame & timestamp to .ndx file
                index_file << counterL++ << "\t" << counterR++ << "\t" << msecCounterL << "\t" << msecCounterR << "\t" << stsL << "\t" << stsR << std::endl;
            }
            else
            {
                if (resL)
                {
                    std::cerr << "R retrieval failed!" << std::endl;
                }
                else if (resR)
                {
                    std::cerr << "L retrieval failed!" << std::endl;
                }
                else
                {                       
                    std::cerr << "L and R retrieval failed!" << std::endl;
                }
            }
        }
        else
        {
            if (okL)
            {
                std::cerr << "R capture failed!" << std::endl;
            }
            else if (okR)
            {
                std::cerr << "L capture failed!" << std::endl;
            }
            else
            {                       
                std::cerr << "L and R capture failed!" << std::endl;
            }
        }
    }

    index_file.close();

    // the cameras will be deinitialized automatically in VideoCapture destructor
    return 0;
}



