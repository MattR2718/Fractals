#include "mandelbrot.cuh"

std::vector<double> linspace(double start, double end, int num)
{
  std::vector<double> linspaced;
  if (num == 0) { return linspaced; }
  if (num == 1) 
    {
      linspaced.push_back(start);
      return linspaced;
    }
  double delta = (end - start) / (num - 1);
  for(int i=0; i < num-1; ++i)
    {
      linspaced.push_back(start + delta * i);
    }
  linspaced.push_back(end);
  return linspaced;
}

__global__ void mandel(int n, const int maxIter, thrust::complex<double> *v, int *numIterations){
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;
    for(int i = index; i < n; i+=stride){
        thrust::complex<double> z = thrust::complex<double>(0.0, 0.0);
        int iters = 0;
        for (iters = 0; iters < maxIter; iters++){
            z = z * z + v[i];
            if (thrust::abs(z) > 4){
                numIterations[i] = iters;
                break;
            }
            numIterations[i] = maxIter;
        }
        
    }
}

void mandelbrot(const int& width, const int& height, std::pair<double, double> tl, std::pair<double, double> br, const int& maxIter, int *numIterations){
    int N = width * height;
    thrust::complex<double> *v;
    int *numIt;
    cudaMallocManaged(&numIt, N*sizeof(int));
    cudaMallocManaged(&v, N*sizeof(thrust::complex<double>));

    std::vector<double> xvalues = linspace(tl.first, br.first, width);
    std::vector<double> yvalues = linspace(tl.second, br.second, height);
    for (int i = 0; i < xvalues.size(); i++){
        for (int j = 0; j < yvalues.size(); j++){
            v[(j * width) + i] = thrust::complex<double>(xvalues[i], yvalues[j]);
        }
    }

    int blockSize = 256;
    int numBlocks = (N + blockSize - 1) / blockSize;
    mandel<<<numBlocks, blockSize>>>(N, maxIter, v, numIt);
    cudaDeviceSynchronize();

    for (int i = 0; i < N; i++){
        numIterations[i] = numIt[i];
    }

    cudaFree(numIt);
}
