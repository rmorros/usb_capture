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
//!  \file synchro2usb.hpp
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

