/*
 * Rgb.cpp
 *
 *  Created on: Nov 8, 2017
 *      Author: vergel
 */

#include "Rgb.h"

namespace mandelbrot {

Rgb operator-(const Rgb& rgb1, const Rgb& rgb2) {
	return Rgb{
		rgb1.red - rgb2.red,
		rgb1.green - rgb2.green,
		rgb1.blue - rgb2.blue
	};
}

} //using namespace mandelbrot
