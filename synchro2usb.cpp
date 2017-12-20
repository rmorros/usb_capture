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

using namespace cv;
using namespace std;

#include <boost/cstdint.hpp> // see http://www.boost.org/doc/libs/1_50_0/libs/integer/doc/html/boost_integer/cstdint.html
//#include <cstdint>         // should replace boost version with C++11?

    // Define integer types (8, 16, 32, 64)

    /*!
     * \defgroup ImagePlusTypes Basic Data Types
     */

    //! Unsigned 8 bits integer  \ingroup ImagePlusTypes
typedef boost::uint8_t        uint8;

//! Signed 8 bits integer    \ingroup ImagePlusTypes
typedef boost::int8_t         int8;
    
    //! Unsigned 16 bits integer \ingroup ImagePlusTypes
    typedef boost::uint16_t       uint16;
    
    //! Signed 16 bits integer   \ingroup ImagePlusTypes
    typedef boost::int16_t        int16;
    
    //! Unsigned 32 bits integer \ingroup ImagePlusTypes
    typedef boost::uint32_t       uint32;
    
    //! Signed 32 bits integer   \ingroup ImagePlusTypes
    typedef boost::int32_t        int32;

//! Unsigned 64 bits integer \ingroup ImagePlusTypes
typedef boost::uint64_t       uint64;

//! Signed 64 bits integer   \ingroup ImagePlusTypes
typedef boost::int64_t        int64;
//#endif

//! Signed 32 bits float     \ingroup ImagePlusTypes
typedef float                 float32;

//! Signed 64 bits float     \ingroup ImagePlusTypes
typedef double                float64;



int main()
{
    VideoCapture captureL(0);
    if (!captureL.isOpened()) cout << "L doesn't work" << endl;
    VideoCapture captureR(1);
    if (!captureR.isOpened()) cout << "R doesn't work" << endl;

    // TODO: change the width, height, and capture FPS to your desired
    // settings.
    cap.set(CAP_PROP_FRAME_WIDTH, 1920);
    cap.set(CAP_PROP_FRAME_HEIGHT, 1080);
    cap.set(CAP_PROP_FPS, 30);

    
    Mat frameL, frameR;

    uint64 msecCounter = 0;
    uint64 frameNumber = 0;
    
    
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

            // VideoCapture::retrieve color converts the image and places
            // it in the Mat that you provide.
            if(captureL.retrieve(&frameL))
            {
                // Pass the frame and parameters to your processing
                // method.
                ProcessFrame(&frame, msecCounter, frameNumber);
            }
        }

        captureL >> imageL;
        captureR >> imageR;
        imshow("OriginalL", imageL);
        imshow("OriginalR", imageR);
        waitKey(1);
    }
captureL.release();
captureR.release();
return 0;
}



