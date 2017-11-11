/*
 * Mandelbrot.cpp
 *
 *  Created on: Oct 24, 2017
 *      Author: vergel
 */

#include "Mandelbrot.h"
#include "Bitmap.h"
#include "Zoom.h"

#include <complex>
#include <memory>
#include <algorithm>
#include <string>

using namespace std;

namespace mandelbrot {

int Mandelbrot::getIterations(double x, double y) {
	complex<double> z = 0;
	complex<double> c(x, y);

	int iterations = 0;
	while (iterations < MAX_ITERATIONS) {
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
	for (int x = 0; x < width; x++) {
		fractals.push_back(vector<int>());
		for (int y = 0; y < height; y++) {
			Coords<double> newCoords = zoom.scaleCoords(Coords<int>{.x=x, .y=y});
			fractals.back().push_back(getIterations(newCoords.x, newCoords.y));
		}
	}
	return fractals;
}

void Mandelbrot::drawFractals(const vector<vector<int> >& fractals,
		const vector<int>& histogram,
		const vector<IterationRange>& iterationRanges,
		Bitmap& bitmap) {
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int iterations = fractals[x][y];

			auto colorIter = find_if(iterationRanges.begin(), iterationRanges.end(),
				[&iterations](const IterationRange& iterationRange){
					return (iterationRange.startRange <= iterations && iterationRange.endRange > iterations);
				}
			);

			mandelbrot::Rgb color({0,0,0});
			if (iterations != MAX_ITERATIONS && colorIter != iterationRanges.end()) {
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

			bitmap.setPixel(x, y, color);
		}
	}
}

vector<int> Mandelbrot::createHistogram(const vector<vector<int> >& fractals) {
	vector<int> histogram(MAX_ITERATIONS, 0);
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			int iterations = fractals[x][y];
			if (iterations != MAX_ITERATIONS) {
				histogram[iterations]++;
			}
		}
	}
	return histogram;
}

vector<IterationRange> Mandelbrot::createIterationRanges(const vector<int>& histogram) {

	vector<IterationRange> iterationRanges;
	int startRange = static_cast<int>(colorRanges[0].first*MAX_ITERATIONS);
	Rgb startColor = colorRanges[0].second;

	for_each(colorRanges.begin() + 1, colorRanges.end(),
		[&histogram, &startRange, &startColor, &iterationRanges](const pair<double, Rgb>& colorRange){
			int endRange = static_cast<int>(colorRange.first*MAX_ITERATIONS);
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

void Mandelbrot::writeBitmap(const string& filename) {
	vector<vector<int> > fractals = createFractal();
	vector<int> histogram = createHistogram(fractals);
	vector<IterationRange> iterationRanges = createIterationRanges(histogram);

	Bitmap bitmap(width, height);
	drawFractals(fractals, histogram, iterationRanges, bitmap);
	bitmap.write(filename);
}

} // namespace mandelbrot
