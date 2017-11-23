/*
 * Main.cpp

 *
 *  Created on: Nov 21, 2017
 *      Author: vergel
 */

#include "Mandelbrot.h"
#include "Rgb.h"
#include "Utils.h"
#include "Bitmap.h"

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <getopt.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

struct ZoomArgs {
	double scaleFactor;
	int x;
	int y;
};

struct Args {
	int width { 800 };
	int height { 600 } ;
	int maxIterations { 1000 };
	vector<ZoomArgs> zooms;
	string output;
};

void showUsage() {
	cout << "Usage: mandelbrot [OPTION...]" << endl
		 << "  -w, --width=VALUE            Image width (default: 800)" << endl
		 << "  -h, --height=VALUE           Image height (default: 600)" << endl
	     << "  -z, --zoom=X,Y,SCALE_FACTOR  Zoom in by scale factor on x and" << endl
	     << "                               y coordinates, can be repeated" << endl
	     << "                               (default: 0.005,400,300)" << endl
		 << "  -m, --max-iterations         Mandelbrot maximum iterations (default: 1024)" << endl
		 << "  -o, --output=FILE            Write fractal image to bitmap file" << endl
		 << "  -?, --help                   Show this help message" << endl
		 << endl;
}

void exitWithError(const string& errorMessage) {
	cerr << "Error: " << errorMessage << endl;
	showUsage();
	exit(1);
}

Args parseArgs(int argc, char* argv[]) {
	int longindex = 0;

	const option longopts[] = {
		{ "width",          required_argument, NULL, 'w' },
		{ "height",         required_argument, NULL, 'h' },
		{ "max-iterations", required_argument, NULL, 'm' },
		{ "center",         no_argument,       NULL, 'c' },
		{ "zoom",           required_argument, NULL, 'z' },
		{ "output",         required_argument, NULL, 'o' },
		{ "help",           no_argument,       NULL, '?' },
		{ NULL,             no_argument,       NULL, 0   }
	};


	Args args { };
	int opt = 0;
	while ((opt = getopt_long(argc, argv, "w:h:m:c:z:o:?", longopts, &longindex)) != -1) {
		switch (opt) {
		case 'w':
			try {
				args.width = stod(optarg);
			}
			catch (...) {
				exitWithError(string("Invalid value on width option: ") + optarg);
			}
			break;
		case 'h':
			try {
				args.height = stod(optarg);
			}
			catch (...) {
				exitWithError(string("Invalid value on height option: ") + optarg);
			}
			break;
		case 'm':
			try {
				args.maxIterations = stod(optarg);
			}
			catch (...) {
				exitWithError(string("Invalid value on max iterations option: ") + optarg);
			}
			break;
		case 'z':
		{
			vector<string> zoomValues = utils::splitString(optarg, ',');
			if (zoomValues.size() != 3) {
				exitWithError(string("Invalid X,Y,SCALE_FACTOR format on zoom option: ") + optarg);
			}
			try {
				args.zooms.push_back(ZoomArgs{
					.scaleFactor=stod(zoomValues[0]),
					.x=stoi(zoomValues[1]),
					.y=stoi(zoomValues[2])
				});
			}
			catch (...) {
				exitWithError(string("Invalid value (non-numeric) on zoom option: ") + optarg);
			}
			break;
		}
		case 'o':
			args.output = optarg;
			break;
		case '?':
			showUsage();
			exit(0);
			break;
		default:
			exitWithError("Invalid option: " + to_string(opt));
		}
	}

	if (args.zooms.empty()) {
		args.zooms.push_back(ZoomArgs{
			.scaleFactor=0.005,  // default scale
			.x=400, // default zoom x
			.y=300  // default zoom y
		});
	}
	if (args.output.empty()) {
		exitWithError("-o is a required argument");
	}
	return args;
}

int main(int argc, char* argv[]) {
	Args args = parseArgs(argc, argv);

	mandelbrot::Mandelbrot mandelbrot(args.width, args.height, args.maxIterations);
	for (auto zoom: args.zooms) {
		mandelbrot.setCenter(zoom.x, zoom.y);
		mandelbrot.setScale(zoom.scaleFactor);
	}
	mandelbrot.addColorRange(make_pair(0.0, mandelbrot::Rgb{.red=0x00,.green=0x00,.blue=0xff}));
	mandelbrot.addColorRange(make_pair(0.05, mandelbrot::Rgb{.red=0xff,.green=0x00,.blue=0x00}));
	mandelbrot.addColorRange(make_pair(0.08, mandelbrot::Rgb{.red=0xff,.green=0xff,.blue=0x00}));
	mandelbrot.addColorRange(make_pair(1.0, mandelbrot::Rgb{.red=0xff,.green=0xff,.blue=0xff}));

	vector<vector<mandelbrot::Rgb> > image = mandelbrot.createFractalImage();
	mandelbrot.writeToBitmap(image, args.output);

	return 0;
}


