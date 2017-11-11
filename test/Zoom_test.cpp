/*
 * Zoom_test.cpp
 *
 *  Created on: Nov 8, 2017
 *      Author: vergel
 */

#include "gtest/gtest.h"

#include "Zoom.h"
#include "Coords.h"

using namespace mandelbrot;

TEST(ZoomTest, ScaleCoords) {
	const int width = 3;
	const int height = 3;
	Zoom zoom(width, height);
	Coords<double> coords = zoom.scaleCoords(Coords<int>{0, 0});
	EXPECT_EQ(-1, coords.x);
	EXPECT_EQ(-1, coords.y);
	coords = zoom.scaleCoords(Coords<int>{1, 1});
	EXPECT_EQ(0, coords.x);
	EXPECT_EQ(0, coords.y);
	coords = zoom.scaleCoords(Coords<int>{2, 2});
	EXPECT_EQ(1, coords.x);
	EXPECT_EQ(1, coords.y);
}

TEST(ZoomTest, ScaleCoordsSetCenter) {
	const int width = 3;
	const int height = 3;
	Zoom zoom(width, height);
	zoom.setCenter(Coords<int>{0, 0});
	Coords<double> coords = zoom.scaleCoords(Coords<int>{0, 0});
	EXPECT_EQ(-2, coords.x);
	EXPECT_EQ(-2, coords.y);
	coords = zoom.scaleCoords(Coords<int>{1, 1});
	EXPECT_EQ(-1, coords.x);
	EXPECT_EQ(-1, coords.y);
	coords = zoom.scaleCoords(Coords<int>{2, 2});
	EXPECT_EQ(0, coords.x);
	EXPECT_EQ(0, coords.y);
}

