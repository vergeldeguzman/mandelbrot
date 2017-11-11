/*
 * Rgb_test.cpp
 *
 *  Created on: Nov 7, 2017
 *      Author: vergel
 */

#include "gtest/gtest.h"

#include "Bitmap.h"
#include "Rgb.h"
#include "Utils.h"

#include <cstdio>

using namespace std;
using namespace mandelbrot;

TEST(BitmapFileTest, WriteSuccess) {
	Bitmap bitmap(4, 3);

	bitmap.setPixel(0, 0, Rgb{.red=0xff,.green=0xff,.blue=0xff});
	bitmap.setPixel(0, 1, Rgb{.red=0xff,.green=0xff,.blue=0xff});
	bitmap.setPixel(0, 2, Rgb{.red=0xff,.green=0xff,.blue=0xff});
	bitmap.setPixel(1, 0, Rgb{.red=0xff,.green=0x0,.blue=0x0});
	bitmap.setPixel(1, 1, Rgb{.red=0xff,.green=0x0,.blue=0x0});
	bitmap.setPixel(1, 2, Rgb{.red=0xff,.green=0x0,.blue=0x0});
	bitmap.setPixel(2, 0, Rgb{.red=0x0,.green=0xff,.blue=0x0});
	bitmap.setPixel(2, 1, Rgb{.red=0x0,.green=0xff,.blue=0x0});
	bitmap.setPixel(2, 2, Rgb{.red=0x0,.green=0xff,.blue=0x0});
	bitmap.setPixel(3, 0, Rgb{.red=0x0,.green=0x0,.blue=0xff});
	bitmap.setPixel(3, 1, Rgb{.red=0x0,.green=0x0,.blue=0xff});
	bitmap.setPixel(3, 2, Rgb{.red=0x0,.green=0x0,.blue=0xff});

	EXPECT_NO_THROW(bitmap.write("output.bmp"));
	EXPECT_TRUE(utils::diff("test/Resource/4x3.bmp", "output.bmp"));

	// cleanup
	remove("output.bmp");
}

TEST(BitmapFileTest, WriteFail) {
	mandelbrot::Bitmap bitmap(4, 3);
	EXPECT_THROW(bitmap.write(""), mandelbrot::BitmapException);
}

