// Copyright 2023 Matveev Sergey
#include <gtest/gtest.h>
#include <omp.h>

#include "../../../modules/task_2/matveyev_s_ccs_matrix/ccs_matrix.h"

TEST(CCS_MATRIX_MULT_SEQ, CREATE_MATRIX) {
  double* arr = create_random_matrix(4);
  SparseMatrix A(arr, 2, 2);
  SparseMatrix B(arr, 2, 2);
  ASSERT_EQ(1, 1);
}

TEST(CCS_MATRIX_MULT_SEQ, TRANSPOSE) {
  double arr[] = {1, 0, 0, 2};
  double arr2[] = {0, 3, 7, 0};
  double arr3[] = {0, 3, 14, 0};
  SparseMatrix A(arr, 2, 2);
  SparseMatrix B(arr2, 2, 2);
  SparseMatrix C(arr3, 2, 2);
  ASSERT_EQ(C, A * B);
}

TEST(CCS_MATRIX_MULT_SEQ, MULT_1) {
  double ptr1[] = {0, 5, 0, 0, 1, 0, 3, 0, 8};
  double ptr2[] = {1, 0, 0, 0, 0, 1, 0, 0, 4};
  double ptr3[] = {0, 0, 5, 0, 0, 1, 3, 0, 32};
  SparseMatrix A(ptr1, 3, 3);
  SparseMatrix B(ptr2, 3, 3);
  SparseMatrix C(ptr3, 3, 3);
  ASSERT_EQ(C == A * B, true);
}

TEST(SPARSE_MATRIX_MULT_SEQ, MULT_2) {
  int count = 100;
  double* ptr1 = create_random_matrix(count * count);
  double* ptr2 = create_random_matrix(count * count);
  SparseMatrix A(ptr1, count, count);
  SparseMatrix B(ptr2, count, count);
  delete[] ptr1;
  delete[] ptr2;
  double start_seq = omp_get_wtime();
  SparseMatrix C = A * B;
  // double end_seq = omp_get_wtime();
  // double seq_time = end_seq - start_seq;
  // double start_omp = omp_get_wtime();
  SparseMatrix D = ParallelMultiplication(A, B);
  // double end_omp = omp_get_wtime();
  // double omp_time = end_omp - start_omp;
  // std::cout << "seq time: " << seq_time << "\n";
  // std::cout << "omp time: " << omp_time << "\n";
  // std::cout << "a: " << seq_time / omp_time << "\n";
  ASSERT_EQ(D, C);
}

TEST(SPARSE_MATRIX_MULT_SEQ, MULT_3) {
  int count = 120;
  double* ptr1 = create_random_matrix(count * count);
  double* ptr2 = create_random_matrix(count * count);
  SparseMatrix A(ptr1, count, count);
  SparseMatrix B(ptr2, count, count);
  delete[] ptr1;
  delete[] ptr2;
  // double start_seq = omp_get_wtime();
  SparseMatrix C = A * B;
  // double end_seq = omp_get_wtime();
  // double seq_time = end_seq - start_seq;
  // double start_omp = omp_get_wtime();
  SparseMatrix D = ParallelMultiplication(A, B);
  // double end_omp = omp_get_wtime();
  // double omp_time = end_omp - start_omp;
  // std::cout << "seq time: " << seq_time << "\n";
  // std::cout << "omp time: " << omp_time << "\n";
  // std::cout << "a: " << seq_time / omp_time << "\n";
  ASSERT_EQ(D, C);
}
TEST(SPARSE_MATRIX_MULT_SEQ, MULT_4) {
  int count = 150;
  double* ptr1 = create_random_matrix(count * count);
  double* ptr2 = create_random_matrix(count * count);
  SparseMatrix A(ptr1, count, count);
  SparseMatrix B(ptr2, count, count);
  delete[] ptr1;
  delete[] ptr2;
  // double start_seq = omp_get_wtime();
  SparseMatrix C = A * B;
  // double end_seq = omp_get_wtime();
  // double seq_time = end_seq - start_seq;
  // double start_omp = omp_get_wtime();
  SparseMatrix D = ParallelMultiplication(A, B);
  // double end_omp = omp_get_wtime();
  // double omp_time = end_omp - start_omp;
  // std::cout << "seq time: " << seq_time << "\n";
  // std::cout << "omp time: " << omp_time << "\n";
  // std::cout << "a: " << seq_time / omp_time << "\n";
  ASSERT_EQ(D, C);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
