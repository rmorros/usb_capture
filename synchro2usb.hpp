// --------------------------------------------------------------
// Copyright (C)
// Universitat Politecnica de Catalunya (UPC) - Barcelona - Spain
// --------------------------------------------------------------

//!
//!  \file synchro2usb.hpp
//!
//!  Add brief description of the file here
//! 

#ifndef NAMESPACE_SYNCHRO2USB_HPP
#define NAMESPACE_SYNCHRO2USB_HPP


#include <boost/cstdint.hpp> // see http://www.boost.org/doc/libs/1_50_0/libs/integer/doc/html/boost_integer/cstdint.html
#include <opencv2/opencv.hpp>



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




std::string mytimestr(bool ms);
void  call_from_thread(cv::VideoCapture& capture, cv::Mat& frame, std::pair<std::string, uint64>& out);

#endif

