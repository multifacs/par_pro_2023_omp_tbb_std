// Copyright 2023 Matveev Sergey
#include "../../task_2/matveyev_s_ccs_matrix/ccs_matrix.h"
#include <omp.h>
double* create_random_matrix(int size_n) {
    std::random_device dev;
        std::mt19937 gen(dev());
    double* in = new double[size_n];
    for (int i = 0; i < size_n; ++i) {
        in[i] = static_cast<double>(gen()) / gen();
        if ((i % 3 == 0)) in[i] = 0;
    }
    return in;
}
SparseMatrix::SparseMatrix(double* arr, int _rows, int _cols) {
    rows = _rows;
    cols = _cols;
    bool f = true;
    int num = 0;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            if (arr[j * rows + i] != 0) {
                if (f) {
                    column_idx.push_back(num);
                    f = false;
                }
                num++;
                values.push_back(arr[j * rows + i]);
                row_nums.push_back(j);
            }
        }
        if (f)  column_idx.push_back(num);
        f = true;
    }
    column_idx.push_back(num);
}
SparseMatrix::SparseMatrix(const SparseMatrix& lhs) {
    rows = lhs.rows;
    cols = lhs.cols;
    column_idx = lhs.column_idx;
    row_nums = lhs.row_nums;
    values = lhs.values;
}
SparseMatrix& SparseMatrix::operator =(const SparseMatrix& lhs) {
    if (this == &lhs) return (*this);
    rows = lhs.rows;
    cols = lhs.cols;
    column_idx = lhs.column_idx;
    row_nums = lhs.row_nums;
    values = lhs.values;
    return (*this);
}
SparseMatrix operator *(const SparseMatrix& first, const SparseMatrix& second) {
    SparseMatrix Copy(first);
    std::vector<int> row_nums;
    std::vector<double>values;
    std::vector<int>column_idx;
    TransponationSparseMatrix(&Copy);
    int current_idx = 0;
    bool flag = true;
    for (int i = 0; i < first.cols; i++) {
        for (int j = 0; j < Copy.cols; j++) {
            double res = 0;
            int ls = second.column_idx[i];
            int lf = second.column_idx[i + 1] - 1;
            int ks = Copy.column_idx[j];
            int kf = Copy.column_idx[j + 1] - 1;
            while ((ks <= kf) && (ls <= lf)) {
                if (Copy.row_nums[ks] == second.row_nums[ls]) {
                    res += Copy.values[ks] * second.values[ls];
                    ks++;
                    ls++;
                }
                else {
                    if (Copy.row_nums[ks] < second.row_nums[ls]) {
                        ks++;
                    }
                    else {
                        ls++;
                    }
                }
            }
            if (res != 0) {
                if (flag) {
                    column_idx.push_back(current_idx);
                    flag = false;
                }
                values.push_back(res);
                row_nums.push_back(j);
                current_idx++;
            }
        }
        if (flag)  column_idx.push_back(current_idx);
        flag = true;
    }
    column_idx.push_back(current_idx);
    Copy.row_nums = row_nums;
    Copy.values = values;
    Copy.column_idx = column_idx;
    return Copy;
}
bool operator == (const SparseMatrix& first, const SparseMatrix& second) {
    if (first.column_idx == second.column_idx
        && first.rows == second.rows
        && first.values == second.values
        && first.cols == second.cols
        && first.row_nums == second.row_nums) return true;
    return false;
}
void TransponationSparseMatrix(SparseMatrix* matrixPtr) {
    int num = 0;
    bool f = true;
    std::vector<std::queue<int>> first(matrixPtr->rows);
    std::vector<std::queue<double>> second(matrixPtr->rows);
    std::vector<int>column_idx(matrixPtr->cols);
    for (int i = 0; i < matrixPtr->cols; i++) {
        for (int j = matrixPtr->column_idx[i];
            j <= matrixPtr->column_idx[i + 1] - 1;
            j++) {
            first[matrixPtr->row_nums[j]].push(i);
            second[matrixPtr->row_nums[j]].push(matrixPtr->values[j]);
        }
    }
    matrixPtr->row_nums.resize(0);
    matrixPtr->values.resize(0);
    for (int i = 0; i < matrixPtr->rows; i++) {
        while (!second[i].empty()) {
            if (f) {
                column_idx[i] = num;
                f = false;
            }
            matrixPtr->values.push_back(second[i].front());
            second[i].pop();
            matrixPtr->row_nums.push_back(first[i].front());
            first[i].pop();
            num += 1;
        }
        f = true;
    }
    column_idx.push_back(num);
    matrixPtr->column_idx = column_idx;
}


SparseMatrix ParallelMultiplication(const SparseMatrix& f, const SparseMatrix& s) {
    SparseMatrix Copy(f);
    std::vector<double>values;
    std::vector<int> rows;
    std::vector<int>column_idx(s.cols, 0);
    std::vector<std::vector<int>> rows_p(omp_get_max_threads());
    std::vector<std::vector<double >> values_p(omp_get_max_threads());
    TransponationSparseMatrix(&Copy);
#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < s.cols; i++) {
            for (int j = 0; j < Copy.cols; j++) {
                double res = 0;
                int ls = s.column_idx[i];
                int lf = s.column_idx[i + 1] - 1;
                int ks = Copy.column_idx[j];
                int kf = Copy.column_idx[j + 1] - 1;
                while ((ks <= kf) && (ls <= lf)) {
                    if (Copy.row_nums[ks] == s.row_nums[ls]) {
                        res +=  Copy.values[ks] * s.values[ls];
                        ks++;
                        ls++;
                    } else {
                        if (Copy.row_nums[ks] < s.row_nums[ls]) {
                            ks++;
                        } else {
                            ls++;
                        }
                    }
                }
                if (res != 0) {
                    column_idx[i]++;
                    values_p[omp_get_thread_num()].push_back(res);
                    rows_p[omp_get_thread_num()].push_back(j);
                }
            }
        }
#pragma omp single
        {
            for (int i = 0; i < omp_get_num_threads(); i++) {
                for (size_t j = 0; j < values_p[i].size(); j++) {
                    values.push_back(values_p[i][j]);
                    rows.push_back(rows_p[i][j]);
                }
            }
            int sum = 0;
            for (size_t i = 0; i < column_idx.size(); i++) {
                int tmp = column_idx[i];
                column_idx[i] = sum;
                sum = tmp + sum;
            }
            column_idx.emplace_back(sum);
        }
    }
    Copy.column_idx = column_idx;
    Copy.row_nums = rows;
    Copy.values = values;
    return Copy;
}
