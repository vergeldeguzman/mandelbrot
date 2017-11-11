/*
 * Bitmap.cpp
 *
 *  Created on: Oct 24, 2017
 *      Author: vergel
 */

#include "Bitmap.h"
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

#include <fstream>

namespace mandelbrot {

void Bitmap::setPixel(int x, int y, mandelbrot::Rgb color) {
	int pos = (y*3)*width + x*3;
	pixels[pos] = color.blue;
	pixels[pos+1] = color.green;
	pixels[pos+2] = color.red;
}

void Bitmap::write(const string& filename) {
	BitmapFileHeader fileHeader;
	BitmapInfoHeader infoHeader;

	fileHeader.fileSize = sizeof(fileHeader) + sizeof(infoHeader) + width*height*3;
	fileHeader.dataOffset = sizeof(fileHeader) + sizeof(infoHeader);

	infoHeader.height = height;
	infoHeader.width = width;

	ofstream ofs;
	ofs.open(filename.c_str(), ios::binary);
	if (!ofs) {
		throw BitmapException("Failed to open " + filename);
	}

	ofs.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
	ofs.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
	ofs.write(reinterpret_cast<char*>(pixels.get()), width*height*3);
	ofs.close();
	if (!ofs) {
		throw BitmapException("Failed to close " + filename);
	}
}

} // namespace mandelbrot
