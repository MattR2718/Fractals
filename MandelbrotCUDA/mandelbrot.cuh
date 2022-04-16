#ifndef MANDELBROT_CUDA
#define MANDELBROT_CUDA

#include <iostream>
#include <cuda_runtime.h>
#include <vector>
#include <thrust/complex.h>

void mandelbrot(const int& width, const int& height, std::pair<double, double> tl, std::pair<double, double> br, const int& maxIter, int *numIterations);

#endif