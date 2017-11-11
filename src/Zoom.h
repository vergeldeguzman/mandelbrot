/*
 * ZoomList.h
 *
 *  Created on: Oct 26, 2017
 *      Author: vergel
 */

#ifndef ZOOM_H_
#define ZOOM_H_

#include "Coords.h"

#include <iostream>

namespace mandelbrot {

class Zoom {
private:
	int width{0};
	int height{0};
	double scale{1.0};
	Coords<double> center;

public:
	Zoom(int width, int height) : width(width), height(height) {}
	void setScale(double _scale) {
		scale *= _scale;
	}
	void setCenter(const Coords<int>& coords);
	Coords<double> scaleCoords(const Coords<int>& coords) const;
};

} /* namespace mandelbrot */

#endif /* ZOOM_H_ */
