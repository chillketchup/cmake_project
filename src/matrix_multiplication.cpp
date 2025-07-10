#include <iostream>
#include <vector>
#include <chrono>

int N; // size of matrix

// naive implementation of matrix multiplication (C = A * B)
// assumes A, B, and C are all N x N square matrices
void naive_matrix_multiplication(const std::vector<std::vector<float>>& A,
                                 const std::vector<std::vector<float>>& B,
                                 std::vector<std::vector<float>>& C,
                                 int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < N; ++k) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

// optimised implementation using 1d array and loop interchange
// assumes A, B, and C are all 1d arrays of length N*N
void optimised_matrix_multiplication(const float* A,
                                     const float* B, 
                                     float* C,
                                     int N) {
    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            float a = A[i*N + k];
            for (int j = 0; j < N; ++j) {
                C[i*N + j] += a * B[k*N + j];
            }
        }
    }
}

int main(){
    std::cout << "enter size of matrix (NxN): " << std::endl;
    std::cin >> N;

    //create 2d vectors to contain matrix
    std::vector<std::vector<float>> v1(N, std::vector<float>(N)), v2(N, std::vector<float>(N)), v3(N, std::vector<float>(N));

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            v1[i][j] = i+j;
            v2[i][j] = i+j;
        }
    }

    //create 1d arrays to contain matrix
    float arr1[N*N], arr2[N*N], arr3[N*N];

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            arr1[i*N+j] = i+j;
            arr2[i*N+j] = i+j;
        }
    }

    //time naive function
    auto start = std::chrono::steady_clock::now();

    naive_matrix_multiplication(v1, v2, v3, N);

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<float> duration = end - start;
    float seconds = duration.count();

    std::cout << "naive program runtime (seconds):" << std::endl;
    std::cout << seconds << std::endl;

    //time optimised function
    start = std::chrono::steady_clock::now();

    optimised_matrix_multiplication(arr1, arr2, arr3, N);

    end = std::chrono::steady_clock::now();
    duration = end - start;
    seconds = duration.count();

    std::cout << "optimised program runtime (seconds):" << std::endl;
    std::cout << seconds << std::endl;
}