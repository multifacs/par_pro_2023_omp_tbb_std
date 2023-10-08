// Copyright 2023 Matveev Sergey
#ifndef MODULES_TASK_2_MATVEEV_S_CCS_MARIX_M_SPARSE_MATRIX_M_H_
#define MODULES_TASK_2_MATVEEV_S_CCS_MARIX_M_SPARSE_MATRIX_M_H_

#include <ctime>
#include <random>
#include <vector>
#include <queue>
#include <iostream>
class SparseMatrix {
public:
    int rows, cols;
    std::vector<int> column_idx;
    std::vector<int> row_nums;
    std::vector<double> values;
    SparseMatrix() :rows(0), cols(0) {}
    SparseMatrix(double* arr, int _rows, int _cols);
    SparseMatrix(const SparseMatrix& lhs);
    SparseMatrix& operator = (const SparseMatrix& lhs);
    friend SparseMatrix operator *(const SparseMatrix& first,
        const SparseMatrix& second);
    friend bool operator == (const SparseMatrix& first,
        const SparseMatrix& second);
};
void TransponationSparseMatrix(SparseMatrix* matrixPtr);
SparseMatrix ParallelMultiplication(const SparseMatrix& first, const SparseMatrix& second);
double* create_random_matrix(int size_n);
#endif  // MODULES_TASK_1_MATVEEV_S_CCS_MARIX_M_SPARSE_MATRIX_M_H_