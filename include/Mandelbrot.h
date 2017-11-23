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
#include "Rgb.h"

namespace mandelbrot {

struct IterationRange {
	int startRange;
	int endRange;
	Rgb startColor;
	Rgb endColor;
	int iterations;
};

class Mandelbrot {
private:

	int width;
	int height;
	int maxIterations;

	Zoom zoom;
	std::vector<std::pair<double, Rgb> > colorRanges;

	int getIterations(double x, double y);
	std::vector<IterationRange> createIterationRanges(const std::vector<int>& histogram);
	std::vector<int> createHistogram(const std::vector<std::vector<int> >& fractals);
	std::vector<std::vector<int> > createFractal();
	std::vector<std::vector<Rgb> > toImage(
			const std::vector<std::vector<int> >& fractals,
			const std::vector<int>& histogram,
			const std::vector<IterationRange>& iterationRanges);

public:

	Mandelbrot(int width, int height, int maxIterations) :
		width(width),
		height(height),
		maxIterations(maxIterations),
		zoom(width, height) {}
	void resetCenter() {
		zoom.resetCenter();
	}
	void setCenter(int x, int y) {
		zoom.setCenter(x, y);
	}
	void setScale(double scale) {
		zoom.setScale(scale);
	}
	void addColorRange(const std::pair<double, Rgb> colorRange) {
		colorRanges.push_back(colorRange);
	}
	std::vector<std::vector<Rgb> > createFractalImage();
	void writeToBitmap(const std::vector<std::vector<Rgb> >& image,
			const std::string& filename);
};

} // namespace mandelbrot

#endif /* MANDELBROT_H_ */

