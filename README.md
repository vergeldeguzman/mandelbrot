# mandelbrot

A console program to generate mandelbrot image and save to bitmap file

## Build 

Run `make mandelbrot` to build the program

## Running the tests

Run `make test` to build and run unit tests

## Usage

Usage: mandelbrot [OPTION...]
  -w, --width=VALUE            Image width (default: 800)
  -h, --height=VALUE           Image height (default: 600)
  -z, --zoom=X,Y,SCALE_FACTOR  Zoom in by scale factor on x and y coordinates, can be repeated (default: 0.005,400,300)
  -m, --max-iterations         Mandelbrot maximum iterations (default: 1000)
  -o, --output=FILE            Write fractal image to bitmap file
  -?, --help                   Show this help message

## Example run

```
./mandelbrot -o fractal.bmp -z 0.005,400,300 -z 0.1,295,202 -z 0.1,300,310 -m 1000
```

[fractal.bmp - 1.4 MB](test/Resource/fractal.bmp)
