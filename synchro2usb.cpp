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
#include <thread>

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


//This function will be called from a thread
void  call_from_thread(cv::VideoCapture& capture, cv::Mat& frame, std::pair<std::string, uint64>& out) 
{
    bool ok = capture.grab();
    std::string sts = mytimestr(true);

    uint64 msecCounter = 0;

    if (ok)
    {
        msecCounter = (uint64) capture.get(CAP_PROP_POS_MSEC);

        // VideoCapture::retrieve color converts the image and places
        // it in the Mat that you provide.
        bool res = capture.retrieve(frame);
    }
    else
    {
        sts = "";
    }    
    out = std::make_pair(sts,msecCounter);
}



#define USE_THREADS = 1


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
    VideoCapture captureR(2);
    if (!captureR.isOpened())
    {
        std::cout << "R doesn't work" << std::endl;
        return -1;
    }

    //int codec = -1; // Pop-up window asking for available codecs
    int codec = CV_FOURCC('M','J','P','G');

    captureL.set(CAP_PROP_FRAME_WIDTH,  width);
    captureL.set(CAP_PROP_FRAME_HEIGHT, height);
    captureL.set(CAP_PROP_FPS, fps); // Does not work! Camera always captures at ~30fps
    captureL.set(CAP_PROP_FOURCC, codec);
    
    
    captureR.set(CAP_PROP_FRAME_WIDTH,  width);
    captureR.set(CAP_PROP_FRAME_HEIGHT, height);
    captureR.set(CAP_PROP_FPS, fps); // Does not work! Camera always captures at ~30fps
    captureR.set(CAP_PROP_FOURCC, codec);

    
    cv::Mat frameL(width,height,3), frameR(width,height,3), frame(width,height,3);

    std::string NAME = mytimestr(false);


    VideoWriter outputVideo;
    Size S = Size(2*width, height);
    outputVideo.open(NAME+".avi" , codec, fps, S, true);

    std::ofstream index_file(NAME.c_str(), std::ofstream::out);

#ifdef USE_THREADS
    static const int num_threads = 2;
    std::thread tt[num_threads];

    std::pair<std::string, uint64> outL, outR;
    uint64 counter = 0;
#else

    uint64 msecCounterL = 0;
    uint64 frameNumberL = 0;

    uint64 msecCounterR = 0;
    uint64 frameNumberR = 0;
    
    uint64 counterL = 0, counterR = 0;

    bool okL, okR, resL, resR;
#endif


    for (;;)
    {
#ifdef USE_THREADS
        //Call function from one thread
        tt[0] = std::thread(call_from_thread, std::ref(captureL), std::ref(frameL), std::ref(outL));
        //Call function from another thread
        tt[1] = std::thread(call_from_thread, std::ref(captureR), std::ref(frameR), std::ref(outR));

        // Join the threads with the main thread
        tt[0].join();
        tt[1].join();

        if (outL.first != "" && outR.first != "")
        {
            cv::hconcat(frameL, frameR, frame);
            outputVideo.write(frame);
            
            // Save frame & timestamp to .ndx file
            index_file << counter++ << "\t" << outL.second << "\t" << outR.second << "\t" << outL.first << "\t" << outR.first << std::endl;
        }
#else
        okL = captureL.grab();
        std::string stsL = mytimestr(true);
        okR = captureR.grab();
        std::string stsR = mytimestr(true);

        if(okL && okR)
        {
            msecCounterL = (uint64) captureL.get(CAP_PROP_POS_MSEC);
            //frameNumberL = (uint64) captureL.get(CAP_PROP_POS_FRAMES);
            msecCounterR = (uint64) captureR.get(CAP_PROP_POS_MSEC);
            //frameNumberR = (uint64) captureR.get(CAP_PROP_POS_FRAMES);

            // VideoCapture::retrieve color converts the image and places
            // it in the Mat that you provide.
            resL = captureL.retrieve(frameL);
            resR = captureR.retrieve(frameR);

            if (resL && resR)
            {
                cv::hconcat(frameL, frameR, frame);
        
                cv::Mat frame3;
                if (frame.channels() < 3)
                {
                    std::vector<Mat> channels;
                    channels.push_back(frame);
                    channels.push_back(frame);
                    channels.push_back(frame);
                    
                    cv::merge(channels, frame3);
                }
                else
                {
                    frame3 = frame;
                }

                outputVideo.write(frame3);

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
#endif


    }

    index_file.close();

    // the cameras will be deinitialized automatically in VideoCapture destructor
    return 0;
}



