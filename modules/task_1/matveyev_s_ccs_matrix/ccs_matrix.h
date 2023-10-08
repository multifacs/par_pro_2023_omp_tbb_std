// Copyright 2023 Matveyev Sergey
#ifndef MODULES_TASK_1_MATVEYEV_S_CCS_MATRIX_CCS_MATRIX_H_
#define MODULES_TASK_1_MATVEYEV_S_CCS_MATRIX_CCS_MATRIX_H_

#include <ctime>
#include <iostream>
#include <queue>
#include <random>
#include <vector>
class SparseMatrix {
 public:
  int rows, cols;
  std::vector<int> column_idx;
  std::vector<int> row_nums;
  std::vector<double> values;
  SparseMatrix() : rows(0), cols(0) {}
  SparseMatrix(double* arr, int _rows, int _cols);
  SparseMatrix(const SparseMatrix& lhs);
  SparseMatrix& operator=(const SparseMatrix& lhs);
  friend SparseMatrix operator*(const SparseMatrix& first,
                                const SparseMatrix& second);
  friend bool operator==(const SparseMatrix& first, const SparseMatrix& second);
};
void TransponationSparseMatrix(SparseMatrix* matrixPtr);
double* create_random_matrix(int size_n);
#endif  // MODULES_TASK_1_MATVEYEV_S_CCS_MATRIX_CCS_MATRIX_H_
