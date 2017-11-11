/*
 * Rgb_test.cpp
 *
 *  Created on: Nov 7, 2017
 *      Author: vergel
 */

#include "gtest/gtest.h"

#include "Rgb.h"

using namespace std;

TEST(MinusOperatorTest, Minus) {
	mandelbrot::Rgb rgb1({.red = 0x44, .green = 0x66, .blue = 0x88});
	mandelbrot::Rgb rgb2({.red = 0x11, .green = 0x22, .blue = 0x33});

	mandelbrot::Rgb diff = mandelbrot::Rgb{0x33, 0x44, 0x55};
	EXPECT_EQ(diff, rgb1 - rgb2);

	diff = mandelbrot::Rgb{0x0, 0x0, 0x0};
	EXPECT_EQ(diff, rgb1 - rgb1);
}


