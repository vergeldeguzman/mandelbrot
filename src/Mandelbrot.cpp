/*
 * Mandelbrot.cpp
 *
 *  Created on: Oct 24, 2017
 *      Author: vergel
 */

#include "Mandelbrot.h"
#include "Zoom.h"
#include "Bitmap.h"

#include <complex>
#include <memory>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

namespace mandelbrot {

int Mandelbrot::getIterations(double x, double y) {
	complex<double> z = 0;
	complex<double> c(x, y);

	int iterations = 0;
	while (iterations < maxIterations) {
		// f(z) = z*z + c
		z = z*z + c;
		if (abs(z) > 2) {
			break;
		}

		iterations++;
	}

	return iterations;
}

vector<vector<int> > Mandelbrot::createFractal() {
	vector<vector<int> > fractals;
	fractals.reserve(width);
	for (int x = 0; x < width; x++) {
		fractals.push_back(vector<int>());
		fractals.back().reserve(height);
		for (int y = 0; y < height; y++) {
			pair<double, double> newCoords = zoom.scaleCoords(x, y);
			fractals.back().push_back(getIterations(newCoords.first, newCoords.second));
		}
	}
	return fractals;
}

vector<vector<Rgb> > Mandelbrot::toImage(const vector<vector<int> >& fractals,
		const vector<int>& histogram,
		const vector<IterationRange>& iterationRanges) {

	vector<vector<Rgb> > image;
	image.reserve(width);
	for (int x = 0; x < width; ++x) {
		image.push_back(vector<Rgb>());
		image.back().reserve(height);
		for (int y = 0; y < height; ++y) {
			int iterations = fractals[x][y];

			auto colorIter = find_if(iterationRanges.begin(), iterationRanges.end(),
				[&iterations](const IterationRange& iterationRange){
					return (iterationRange.startRange <= iterations && iterationRange.endRange > iterations);
				}
			);

			mandelbrot::Rgb color({0,0,0});
			if (iterations != maxIterations && colorIter != iterationRanges.end()) {
				int pixels = 0;
				for (int i = colorIter->startRange; i <= iterations; ++i) {
					pixels += histogram[i];
				}
				Rgb colorDiff = colorIter->endColor - colorIter->startColor;
				double pixelPerc = static_cast<double>(pixels)/colorIter->iterations;
				color.red = colorIter->startColor.red + (colorDiff.red*pixelPerc);
				color.green = colorIter->startColor.green + (colorDiff.green*pixelPerc);
				color.blue = colorIter->startColor.blue + (colorDiff.blue*pixelPerc);
			}

			image.back().push_back(color);
		}
	}
	return image;
}

vector<int> Mandelbrot::createHistogram(const vector<vector<int> >& fractals) {
	vector<int> histogram(maxIterations, 0);
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int iterations = fractals[x][y];
			if (iterations != maxIterations) {
				histogram[iterations]++;
			}
		}
	}
	return histogram;
}

vector<IterationRange> Mandelbrot::createIterationRanges(const vector<int>& histogram) {
	int maxIter = maxIterations;
	vector<IterationRange> iterationRanges;
	int startRange = static_cast<int>(colorRanges[0].first*maxIterations);
	Rgb startColor = colorRanges[0].second;

	for_each(colorRanges.begin() + 1, colorRanges.end(),
		[&histogram, &startRange, &startColor, &iterationRanges, &maxIter](const pair<double, Rgb>& colorRange){
			int endRange = static_cast<int>(colorRange.first*maxIter);
			Rgb endColor = colorRange.second;
			int iterationRange = 0;
			for (int i = startRange; i < endRange; ++i) {
				iterationRange += histogram[i];
			}
			iterationRanges.push_back(
				IterationRange{
					startRange,
					endRange,
					startColor,
					endColor,
					iterationRange});

			startRange = endRange;
			startColor = endColor;
		}
	);
	return iterationRanges;
}

vector<vector<Rgb> > Mandelbrot::createFractalImage() {
	vector<vector<int> > fractals = createFractal();
	vector<int> histogram = createHistogram(fractals);
	vector<IterationRange> iterationRanges = createIterationRanges(histogram);
	return toImage(fractals, histogram, iterationRanges);
}

void Mandelbrot::writeToBitmap(const vector<vector<mandelbrot::Rgb> >& image,
		const string& filename) {

	bitmap::Bitmap bitmap(width, height);
	for (size_t x = 0; x < image.size(); ++x) {
		for (size_t y = 0; y < image[x].size(); ++y) {
			bitmap.setPixel(x, y, image[x][y].red, image[x][y].green, image[x][y].blue);
		}
	}
	bitmap.write(filename);
}

} // namespace mandelbrot
