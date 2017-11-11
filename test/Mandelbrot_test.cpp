/*
 * Mandelbrot_test.cpp
 *
 *  Created on: Nov 6, 2017
 *      Author: vergel
 */

#include "gtest/gtest.h"

#include "Rgb.h"
#include "Mandelbrot.h"
#include "Utils.h"

using namespace mandelbrot;

TEST(MandelbrotTest, WriteBitmap) {
	const int width = 800;
	const int height = 600;
	Mandelbrot mandelbrot(width, height);
	mandelbrot.setCenter(Coords<int>{.x=400, .y=300});
	mandelbrot.setScale(0.005); // x200
	mandelbrot.setCenter(Coords<int>{.x=295, .y=(height - 202)});
	mandelbrot.setScale(0.1); // x10
	mandelbrot.setCenter(Coords<int>{.x=300, .y=(height - 310)});
	mandelbrot.setScale(0.1); // x10
	mandelbrot.addColorRange(make_pair(0.0, Rgb{.red=0x00,.green=0x00,.blue=0xff}));
	mandelbrot.addColorRange(make_pair(0.05, Rgb{.red=0xff,.green=0x00,.blue=0x00}));
	mandelbrot.addColorRange(make_pair(0.08, Rgb{.red=0xff,.green=0xff,.blue=0x00}));
	mandelbrot.addColorRange(make_pair(1.0, Rgb{.red=0xff,.green=0xff,.blue=0xff}));

	EXPECT_NO_THROW(mandelbrot.writeBitmap("output.bmp"));
	EXPECT_TRUE(utils::diff("test/Resource/fractal.bmp", "output.bmp"));

	// cleanup
	remove("output.bmp");
}

