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

#include "opencv2/opencv.hpp"
using namespace cv;
int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    // TODO: change the width, height, and capture FPS to your desired
    // settings.
    cap.set(CAP_PROP_FRAME_WIDTH, 1920);
    cap.set(CAP_PROP_FRAME_HEIGHT, 1080);
    cap.set(CAP_PROP_FPS, 30);

    Mat frame;
    long msecCounter = 0;
    long frameNumber = 0;

    for(;;)
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
            msecCounter = (long) cap.get(CAP_PROP_POS_MSEC);
            frameNumber = (long) cap.get(CAP_PROP_POS_FRAMES);

            // VideoCapture::retrieve color converts the image and places
            // it in the Mat that you provide.
            if(cap.retrieve(&frame))
            {
                // Pass the frame and parameters to your processing
                // method.
                ProcessFrame(&frame, msecCounter, frameNumber);
            }
        }

        // TODO: Handle your loop termination condition here
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}

void ProcessFrame(Mat& frame, long msecCounter, long frameNumber)
{
    // TODO: Make a copy of frame if you are going to process it
    // asynchronously or put it in a buffer or queue and then return
    // control from this function. This is because the reference Mat
    // being passed in is "owned" by the processing loop, and on each
    // iteration it will be destructed, so any references to it will be
    // invalid. Hence, if you do any work async, you need to copy frame.
    //
    // If all your processing happens synchronously in this function,
    // you don't need to make a copy first because the loop is waiting
    // for this function to return.

    // TODO: Your processing logic goes here.
}





