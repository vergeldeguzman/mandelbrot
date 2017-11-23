/*
 * Zoom.cpp
 *
 *  Created on: Oct 26, 2017
 *      Author: vergel
 */

#include "Zoom.h"

#include <iostream>

using namespace std;

namespace mandelbrot {

void Zoom::setCenter(int x, int y) {
	centerX += (x - width/2)*scale;
	centerY += (y - height/2)*scale;
}

pair<double, double> Zoom::scaleCoords(int x, int y) const {
	double rescaledX = (x - width/2)*scale + centerX;
	double rescaledY = (y - height/2)*scale + centerY;
	return make_pair(rescaledX, rescaledY);
}

} /* namespace mandelbrot */
