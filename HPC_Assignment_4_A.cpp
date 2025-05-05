#include <iostream>
#include <vector>
using namespace std;

// To run on Google Colab run below commands
// !nvcc -arch=sm_75 vector_add_small.cu -o vector_add_small
// !./vector_add_small



// CUDA kernel for element-wise vector addition
__global__ void vecAdd(int* A, int *B, int *C, int size) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < size)
        C[tid] = A[tid] + B[tid];
}

int main()
{
    int size = 7;
    vector<int> arr1 = {1, 2, 3, 4, 5, 6, 7};
    vector<int> arr2 = {2, 3, 5, 6, 7, 8, 9};
    vector<int> ans(size, 0); // Initialize ans vector with zeros

    int totalSize = size * sizeof(int);
    int *a, *b, *c;

    // Allocate memory on the GPU
    cudaMalloc(&a, totalSize);
    cudaMalloc(&b, totalSize);
    cudaMalloc(&c, totalSize);

    // Copy input vectors from host to device
    cudaMemcpy(a, arr1.data(), totalSize, cudaMemcpyHostToDevice);
    cudaMemcpy(b, arr2.data(), totalSize, cudaMemcpyHostToDevice);

    // Launch kernel with 1 block and 255 threads
    vecAdd<<<1, 255>>>(a, b, c, size);

    // Check for kernel launch errors
    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) {
        cout << "CUDA kernel error: " << cudaGetErrorString(err) << endl;
    }

    // Copy the result back from device to host
    cudaMemcpy(ans.data(), c, totalSize, cudaMemcpyDeviceToHost);

    // Print input arrays and the result
    cout << "arr1 = ";
    for (auto x : arr1) {
        cout << x << " ";
    }
    cout << endl;

    cout << "arr2 = ";
    for (auto x : arr2) {
        cout << x << " ";
    }
    cout << endl;

    cout << "ans = ";
    for (auto x : ans) {
        cout << x << " ";
    }
    cout << endl;

    // Free allocated memory
    cudaFree(a);
    cudaFree(b);
    cudaFree(c);

    return 0;
}
