/*
 * BitmapFileHeader.h
 *
 *  Created on: Oct 24, 2017
 *      Author: vergel
 */

#ifndef BITMAPFILEHEADER_H_
#define BITMAPFILEHEADER_H_

#include <cstdint>

#pragma pack(push, 2)  // align to 2-byte struct

struct BitmapFileHeader {
	char header[2] = {'B', 'M'};
	int32_t fileSize;
	int32_t reserved{0};
	int32_t dataOffset;
};
#pragma pack(pop) // restore byte alignment

#endif /* BITMAPFILEHEADER_H_ */
