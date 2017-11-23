/*
 * Bitmap_test.cpp
 *
 *  Created on: Nov 7, 2017
 *      Author: vergel
 */

#include "gtest/gtest.h"

#include "Rgb.h"
#include "Utils.h"
#include "Bitmap.h"

#include <cstdio>

using namespace std;
using namespace mandelbrot;

TEST(BitmapFileTest, WriteSuccess) {
	bitmap::Bitmap bitmap(4, 3);

	bitmap.setPixel(0, 0, 0xff, 0xff, 0xff);
	bitmap.setPixel(0, 1, 0xff, 0xff, 0xff);
	bitmap.setPixel(0, 2, 0xff, 0xff, 0xff);
	bitmap.setPixel(1, 0, 0xff, 0x0, 0x0);
	bitmap.setPixel(1, 1, 0xff, 0x0, 0x0);
	bitmap.setPixel(1, 2, 0xff, 0x0, 0x0);
	bitmap.setPixel(2, 0, 0x0, 0xff, 0x0);
	bitmap.setPixel(2, 1, 0x0, 0xff, 0x0);
	bitmap.setPixel(2, 2, 0x0, 0xff, 0x0);
	bitmap.setPixel(3, 0, 0x0, 0x0, 0xff);
	bitmap.setPixel(3, 1, 0x0, 0x0, 0xff);
	bitmap.setPixel(3, 2, 0x0, 0x0, 0xff);

	EXPECT_NO_THROW(bitmap.write("output.bmp"));
	EXPECT_TRUE(utils::diff("test/Resource/4x3.bmp", "output.bmp"));

	// cleanup
	remove("output.bmp");
}

TEST(BitmapFileTest, WriteFail) {
	bitmap::Bitmap bitmap(4, 3);
	EXPECT_THROW(bitmap.write(""), bitmap::BitmapException);
}

