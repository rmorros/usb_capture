// Copyright <2018> <Josep Ramon Morros - Universitat Politecnica de Catalunya (UPC) - Barcelona - Spain>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial
// portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

//!
//!  \file usb_capture.cpp
//!
//!  Capture video from a USB camera. Save file with timestamps of each frame
//!
//!  Some useful information used to write this code:
//! 
//! https://stackoverflow.com/questions/44490743/how-to-extract-timestamps-from-each-frame-obtained-by-usb-camera
//! https://stackoverflow.com/questions/16357999/current-date-and-time-as-string

#include <iostream>
#include <fstream>
#include <ctime>
#include <sys/time.h>

#include "opencv2/opencv.hpp"

// Uso opencv
using namespace cv;


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

    // TODO: change the width, height, and capture FPS to your desired
    // settings.
    int width  = 640;
    int height = 480;
    double fps =  25.0;
        
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    // TODO: change the width, height, and capture FPS to your desired
    // settings.
    cap.set(CAP_PROP_FRAME_WIDTH,  width);
    cap.set(CAP_PROP_FRAME_HEIGHT, height);
    cap.set(CAP_PROP_FPS, fps);    // Does not work! Camera allways captures at ~30fps

    Mat  frame;
    long msecCounter = 0;
    long frameNumber = 0;

    long counter = 0;
   
    std::string NAME = mytimestr(false);
    
    //int ex = -1; // Pop-up window asking for available codecs
    int codec = CV_FOURCC('M','J','P','G');

    VideoWriter outputVideo;
    Size S = Size(width, height);
    outputVideo.open(NAME+".avi" , codec, fps, S, true);


    std::ofstream index_file(NAME.c_str(), std::ofstream::out);

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

            // VideoCapture::retrieve color converts the image and places
            // it in the Mat that you provide.
            if(cap.retrieve(frame))
            {
 	        std::cout << frame.dims << std::endl;
                outputVideo.write(frame);

                // Save frame & timestamp to .ndx file
                index_file << counter++ << "\t" << frameNumber << "\t" << msecCounter << "\t" << sts << std::endl;
            }
        }

        // TODO: Handle your loop termination condition here
    }

    
    index_file.close();
    
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}






