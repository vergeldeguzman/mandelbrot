/*
 * Zoom.h
 *
 *  Created on: Oct 26, 2017
 *      Author: vergel
 */

#ifndef ZOOM_H_
#define ZOOM_H_

#include <iostream>
#include <utility>

namespace mandelbrot {

class Zoom {
private:
	int width{0};
	int height{0};
	double centerX{0.0};
	double centerY{0.0};
	double scale{1.0};

public:
	Zoom(int width, int height) : width(width), height(height) {}
	void setScale(double _scale) {
		scale *= _scale;
	}
	void resetCenter() {
		centerX = 0.0;
		centerY = 0.0;
		scale = 1.0;
	}
	void setCenter(int x, int y);
	std::pair<double, double> scaleCoords(int x, int y) const;
};

} /* namespace mandelbrot */

#endif /* ZOOM_H_ */
