/*
 * Rgb.h
 *
 *  Created on: Oct 27, 2017
 *      Author: vergel
 */

#ifndef RGB_H_
#define RGB_H_

namespace mandelbrot {

struct Rgb {
	int red;
	int green;
	int blue;

	bool operator==(const Rgb& rgb2) const {
		return (red == rgb2.red && green == rgb2.green && blue == rgb2.blue);
	}
};

Rgb operator-(const Rgb& rgb1, const Rgb& rgb2);

} /* namespace mandelbrot */

#endif /* RGB_H_ */
