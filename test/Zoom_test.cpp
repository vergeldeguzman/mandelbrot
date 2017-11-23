/*
 * Zoom_test.cpp
 *
 *  Created on: Nov 8, 2017
 *      Author: vergel
 */

#include "gtest/gtest.h"

#include "Zoom.h"

#include <utility>

using namespace mandelbrot;

TEST(ZoomTest, ScaleCoords) {
	const int width = 3;
	const int height = 3;
	Zoom zoom(width, height);
	std::pair<double, double> coords = zoom.scaleCoords(0, 0);
	EXPECT_EQ(-1, coords.first);
	EXPECT_EQ(-1, coords.second);
	coords = zoom.scaleCoords(1, 1);
	EXPECT_EQ(0, coords.first);
	EXPECT_EQ(0, coords.second);
	coords = zoom.scaleCoords(2, 2);
	EXPECT_EQ(1, coords.first);
	EXPECT_EQ(1, coords.second);
}

TEST(ZoomTest, ScaleCoordsSetCenter) {
	const int width = 3;
	const int height = 3;
	Zoom zoom(width, height);
	zoom.setCenter(0, 0);
	std::pair<double, double> coords = zoom.scaleCoords(0, 0);
	EXPECT_EQ(-2, coords.first);
	EXPECT_EQ(-2, coords.second);
	coords = zoom.scaleCoords(1, 1);
	EXPECT_EQ(-1, coords.first);
	EXPECT_EQ(-1, coords.second);
	coords = zoom.scaleCoords(2, 2);
	EXPECT_EQ(0, coords.first);
	EXPECT_EQ(0, coords.second);
}

