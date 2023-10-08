// Copyright 2023 Matveev Sergey
#include <gtest/gtest.h>

#include "../../../modules/task_1/matveyev_s_ccs_matrix/ccs_matrix.h"

TEST(CCS_MATRIX_MULT_SEQ, CREATE_MATRIX) {
  double* ptr = create_random_matrix(4);
  SparseMatrix first(ptr, 2, 2);
  SparseMatrix second(ptr, 2, 2);
  delete[] ptr;
  ASSERT_NO_THROW(first * second);
}

TEST(CCS_MATRIX_MULT_SEQ, MULT_1) {
  double ptr1[] = {1, 0, 0, 2};
  double ptr2[] = {0, 3, 7, 0};
  double ptr3[] = {0, 3, 14, 0};
  SparseMatrix f(ptr1, 2, 2);
  SparseMatrix s(ptr2, 2, 2);
  SparseMatrix t(ptr3, 2, 2);
  ASSERT_EQ(t == f * s, true);
}

TEST(CCS_MATRIX_MULT_SEQ, MULT_2) {
  double ptr1[] = {0, 5, 0, 0, 1, 0, 3, 0, 8};
  double ptr2[] = {1, 0, 0, 0, 0, 1, 0, 0, 4};
  double ptr3[] = {0, 0, 5, 0, 0, 1, 3, 0, 32};
  SparseMatrix f(ptr1, 3, 3);
  SparseMatrix s(ptr2, 3, 3);
  SparseMatrix t(ptr3, 3, 3);
  ASSERT_EQ(t == f * s, true);
}

TEST(CCS_MATRIX_MULT_SEQ, MULT_3) {
  int count = 4;
  double* ptr1 = create_random_matrix(count * count);
  double* ptr2 = create_random_matrix(count * count);
  SparseMatrix f(ptr1, count, count);
  SparseMatrix s(ptr2, count, count);
  delete[] ptr1;
  delete[] ptr2;
  ASSERT_NO_THROW(f * s);
}

TEST(CCS_MATRIX_MULT_SEQ, MULT_4) {
  int count = 5;
  double* ptr1 = create_random_matrix(count * count);
  double* ptr2 = create_random_matrix(count * count);
  SparseMatrix f(ptr1, count, count);
  SparseMatrix s(ptr2, count, count);
  delete[] ptr1;
  delete[] ptr2;
  ASSERT_NO_THROW(f * s);
}

TEST(CCS_MATRIX_MULT_SEQ, MULT_5) {
  int count = 6;
  double* ptr1 = create_random_matrix(count * count);
  double* ptr2 = create_random_matrix(count * count);
  SparseMatrix f(ptr1, count, count);
  SparseMatrix s(ptr2, count, count);
  delete[] ptr1;
  delete[] ptr2;
  ASSERT_NO_THROW(f * s);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
