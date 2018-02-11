// --------------------------------------------------------------
// Copyright (C)
// Universitat Politecnica de Catalunya (UPC) - Barcelona - Spain
// --------------------------------------------------------------

//!
//!  \file usb_capture.cpp
//!
//!  Add brief description of the file here
//!


//! https://stackoverflow.com/questions/44490743/how-to-extract-timestamps-from-each-frame-obtained-by-usb-camera

#include <iostream>
#include <fstream>
#include <ctime>
#include <sys/time.h>

#include "opencv2/opencv.hpp"

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


int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    int width  = 1280;
    int height =  720;
    double fps =   25.0;

        
    // TODO: change the width, height, and capture FPS to your desired
    // settings.
    cap.set(CAP_PROP_FRAME_WIDTH,  width);
    cap.set(CAP_PROP_FRAME_HEIGHT, height);
    cap.set(CAP_PROP_FPS, fps);

    Mat  frame(width,height,3);
    long msecCounter = 0;
    long frameNumber = 0;

    //std::string NAME = "patata.mov";
    std::string NAME = mytimestr(false);



    
    
    //int ex = -1; // Pop-up window asking for available codecs
    int codec = CV_FOURCC('M','J','P','G');

    VideoWriter outputVideo;
    Size S = Size(width, height);
    outputVideo.open(NAME+".avi" , codec, fps, S, true);


    std::ofstream index_file(NAME.c_str(), std::ofstream::out);

    long frame_num = 0;
    
    // for(;;)
    for(int i=0; i < 300; ++i)  // 12s@25Hz
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

        if(cap.grab())
        {
 	    std::string sts = mytimestr(true);

            msecCounter = (long) cap.get(CAP_PROP_POS_MSEC);
            //frameNumber = (long) cap.get(CAP_PROP_POS_FRAMES);

	    std::cout << msecCounter << std::endl;
	    
            // VideoCapture::retrieve color converts the image and places
            // it in the Mat that you provide.
            if(cap.retrieve(frame))
            {
                outputVideo.write(frame);

                // Save frame & timestamp to .ndx file
                index_file << frame_num++ << "\t" << frameNumber << "\t" << msecCounter << "\t" << sts << std::endl;
            }
        }

        // TODO: Handle your loop termination condition here
    }

    
    index_file.close();
    
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}






