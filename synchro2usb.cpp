// --------------------------------------------------------------
// Copyright (C)
// Universitat Politecnica de Catalunya (UPC) - Barcelona - Spain
// --------------------------------------------------------------

//!
//!  \file synchro2usb.cpp
//!
//!  Add brief description of the file here
//!

#include <opencv2\opencv.hpp>
#include <opencv\highgui.h>
#include "synchro2usb.hpp"

using namespace cv;
using namespace std;




int main()
{
    VideoCapture captureL(0);
    if (!captureL.isOpened()) cout << "L doesn't work" << endl;
    VideoCapture captureR(1);
    if (!captureR.isOpened()) cout << "R doesn't work" << endl;

    // TODO: change the width, height, and capture FPS to your desired
    // settings.
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(CAP_PROP_FPS, 15);

    
    std::vector<Mat> frameL, frameR;

    uint64 msecCounter = 0;
    uint64 frameNumber = 0;
    
    uint64 counterL = 0, counterR = 0;
    
    while (1)
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

        if(captureL.grab())
        {
            msecCounter = (uint64) captureL.get(CAP_PROP_POS_MSEC);
            frameNumber = (uint64) captureL.get(CAP_PROP_POS_FRAMES);

            // VideoCapture::retrieve color converts the image and places it in the Mat that you provide.
            resL = captureL.retrieve(&frameL[counterL++]);
            ...
        }

    }

    captureL.release();
    captureR.release();
    return 0;
}



