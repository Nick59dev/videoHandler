#ifndef PROC_FILE_H00
#define PROC_FILE_H00

#include "st.h"

namespace handler
{
	class videoHandler {
		public:
			videoHandler();

			unsigned char counting_yuv(const POINT& im, const char& type) const;

			size_t reading_yuv(const char * filename, unsigned char * writing_stream, const unsigned int& height,
		                   const unsigned int& width, const size_t& offset, const char& type);

    	int reading_rgb(const char * filename, const char * yuv_file,  const std::size_t& yuv_frames,
    						 const std::size_t& yuv_width, const std::size_t& yuv_height, const char * output_file);
			~videoHandler();
	};
}

#endif
