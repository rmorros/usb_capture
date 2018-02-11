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

    // TODO: change the width, height, and capture FPS to your desired
    // settings.
    cap.set(CAP_PROP_FRAME_WIDTH,  width);
    cap.set(CAP_PROP_FRAME_HEIGHT, height);
    cap.set(CAP_PROP_FPS, fps);

    
    std::vector<cv::Mat> frameL, frameR;

    uint64 msecCounterL = 0;
    uint64 frameNumberL = 0;

    uint64 msecCounterR = 0;
    uint64 frameNumberR = 0;
    
    uint64 counterL = 0, counterR = 0;
    std::string NAME = mytimestr();

    //int ex = -1; // Pop-up window asking for available codecs
    int codec = CV_FOURCC('M','J','P','G');

    VideoWriter outputVideo;
    Size S = Size(width, height);
    outputVideo.open(NAME+".avi" , codec, fps, S, true);

    std::ofstream index_file(NAME.c_str(), std::ofstream::out);

    long frame_num = 0;

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

        if(okL = captureL.grab())
        {
 	    std::string sts = mytimestr();
            msecCounterL = (uint64) captureL.get(CAP_PROP_POS_MSEC);
            frameNumberL = (uint64) captureL.get(CAP_PROP_POS_FRAMES);

            // VideoCapture::retrieve color converts the image and places it in the Mat that you provide.
            resL = captureL.retrieve(&frameL[counterL++]);
            ...
        }

    }

    captureL.release();
    captureR.release();
    return 0;
}



