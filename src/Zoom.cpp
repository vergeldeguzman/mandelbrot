/*
 * ZoomList.cpp
 *
 *  Created on: Oct 26, 2017
 *      Author: vergel
 */

#include "Zoom.h"

#include <iostream>

using namespace std;

namespace mandelbrot {

void Zoom::setCenter(const Coords<int>& coords) {
	center.x += (coords.x - width/2)*scale;
	center.y += (coords.y - height/2)*scale;
}

Coords<double> Zoom::scaleCoords(const Coords<int>& coords) const {
	double rescaledX = (coords.x - width/2)*scale + center.x;
	double rescaledY = (coords.y - height/2)*scale + center.y;
	return Coords<double>{.x=rescaledX, .y=rescaledY};
}

} /* namespace mandelbrot */
