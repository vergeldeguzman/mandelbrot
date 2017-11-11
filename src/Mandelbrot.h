/*
 * Mandelbrot.h
 *
 *  Created on: Oct 24, 2017
 *      Author: vergel
 */

#ifndef MANDELBROT_H_
#define MANDELBROT_H_

#include <memory>
#include <vector>
#include <array>

#include "Zoom.h"
#include "Bitmap.h"

namespace mandelbrot {

const int MAX_ITERATIONS = 1000;

struct IterationRange {
	int startRange;
	int endRange;
	Rgb startColor;
	Rgb endColor;
	int iterations;
};

class Mandelbrot {
private:

	int width{0};
	int height{0};
	int totalIterations{0};

	Zoom zoom;
	std::vector<std::pair<double, Rgb> > colorRanges;

	int getIterations(double x, double y);
	std::vector<IterationRange> createIterationRanges(const std::vector<int>& histogram);
	std::vector<int> createHistogram(const std::vector<std::vector<int> >& fractals);
	std::vector<std::vector<int> > createFractal();
	void drawFractals(const std::vector<std::vector<int> >& fractals,
			const std::vector<int>& histogram,
			const std::vector<IterationRange>& iterationRanges,
			Bitmap& bitmap);

public:
	Mandelbrot(int width, int height) :
		width(width),
		height(height),
		zoom(width, height) {}
	void setCenter(const Coords<int>& coords) {
		zoom.setCenter(coords);
	}
	void setScale(double scale) {
		zoom.setScale(scale);
	}
	void addColorRange(std::pair<double, Rgb> colorRange) {
		colorRanges.push_back(colorRange);
	}
	void writeBitmap(const std::string& filename);
};

} // namespace mandelbrot

#endif /* MANDELBROT_H_ */

