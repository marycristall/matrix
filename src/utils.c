#include "s21_matrix.h"

int is_size_zero(int rows, int columns) {
  int res = 0;
  if (!rows || !columns) {
    res = 1;
  }
  return res;
}

int is_ptr_null(matrix_t *A) {
  int res = 0;
  if (A == NULL) {
    res = 1;
  }
  return res;
}

int is_size_equal(matrix_t *A, matrix_t *B) {
  if (A->rows != B->rows || A->columns != B->columns || A->columns <= 0 ||
      B->columns <= 0 || A->rows <= 0 || B->rows <= 0)
    return 1;
  else
    return 0;
}

void find_minor(int m, int n, matrix_t *A, matrix_t *result) {
  s21_create_matrix(A->rows - 1, A->columns - 1, result);
  int rows = 0;
  int columns = 0;
  for (int i = 0; i < A->rows; i++) {
    if (m == i) continue;
    for (int g = 0; g < A->columns; g++) {
      if (n == g) continue;
      result->matrix[rows][columns] = A->matrix[i][g];
      columns++;
    }
    rows++;
    columns = 0;
  }
}