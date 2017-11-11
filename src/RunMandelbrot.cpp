/*
 * RunMandelbrot.cpp
 *
 *  Created on: Oct 24, 2017
 *      Author: vergel
 */

#include "Bitmap.h"
#include "Mandelbrot.h"
#include "Rgb.h"
#include "Coords.h"

#include <iostream>
#include <memory>

using namespace std;
using namespace mandelbrot;

int main() {
	try {
		const int width = 800;
		const int height = 600;

		Mandelbrot mandelbrot(width, height);
		mandelbrot.setCenter(Coords<int>{.x=width/2, .y=height/2});
		mandelbrot.setScale(4.0/height);

		mandelbrot.addColorRange(make_pair(0.0, Rgb{0,0,0}));
		mandelbrot.addColorRange(make_pair(0.3, Rgb{255,0,0}));
		mandelbrot.addColorRange(make_pair(0.6, Rgb{255,255,0}));
		mandelbrot.addColorRange(make_pair(1.0, Rgb{255,255,255}));
		mandelbrot.writeBitmap("output.bmp");
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
		return 1;
	}
	return 0;
}
