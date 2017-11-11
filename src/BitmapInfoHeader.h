/*
 * BitmapInfoHeader.h
 *
 *  Created on: Oct 24, 2017
 *      Author: vergel
 */

#ifndef BITMAPINFOHEADER_H_
#define BITMAPINFOHEADER_H_

#include <cstdint>

#pragma pack(push, 2)  // align to 2-byte struct

struct BitmapInfoHeader {
	int32_t headerSize{40};
	int32_t width;
	int32_t height;
	int16_t planes{1};
	int16_t bitsPerPixel{24};
	int32_t compression{0};
	int32_t dataSize{0};
	int32_t horizontalResolution{2400};
	int32_t verticalResolution{2400};
	int32_t colors{0};
	int32_t importantColors{0};
};
#pragma pack(pop) // restore byte alignment

#endif /* BITMAPINFOHEADER_H_ */
