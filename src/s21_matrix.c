#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = OK;
  if (is_size_zero(rows, columns)) {
    res = INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)malloc(result->rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)malloc(result->columns * sizeof(double));
    }
  }
  return res;
}
void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i]) {
        free(A->matrix[i]);
      }
    }
    free(A->matrix);
    A->matrix = NULL;
  }
  if (A->rows) {
    A->rows = 0;
  }
  if (A->columns) {
    A->columns = 0;
  }
}
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (is_size_equal(A, B)) {
    res = FAILLURE;
  } else {
    for (int n = 0; n < A->rows; n++) {
      for (int m = 0; m < A->columns; m++) {
        if (fabs(A->matrix[n][m] - B->matrix[n][m]) >= 1e-7) {
          res = FAILLURE;
          n = A->rows;
          m = A->columns;
        }
      }
    }
  }
  return res;
};
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (is_size_equal(A, B)) res = CALC_ERROR;
  if (is_ptr_null(A) || is_ptr_null(B) || is_ptr_null(result) || !A->matrix ||
      !B->matrix)
    res = INCORRECT_MATRIX;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int n = 0; n < A->rows; n++) {
      for (int m = 0; m < A->columns; m++) {
        result->matrix[n][m] = A->matrix[n][m] + B->matrix[n][m];
      }
    }
  }
  return res;
}
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (is_size_equal(A, B)) res = CALC_ERROR;
  if (is_ptr_null(A) || is_ptr_null(B) || is_ptr_null(result) || !A->matrix ||
      !B->matrix)
    res = INCORRECT_MATRIX;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int n = 0; n < A->rows; n++) {
      for (int m = 0; m < A->columns; m++) {
        result->matrix[n][m] = A->matrix[n][m] - B->matrix[n][m];
      }
    }
  }
  return res;
};
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (is_ptr_null(A) || is_ptr_null(result) || !A->matrix)
    res = INCORRECT_MATRIX;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int n = 0; n < A->rows; n++) {
      for (int m = 0; m < A->columns; m++) {
        result->matrix[n][m] = A->matrix[n][m] * number;
      }
    }
  }
  return res;
}
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (A->columns != B->rows || A->rows != B->columns) res = CALC_ERROR;
  if (is_ptr_null(A) || is_ptr_null(B) || is_ptr_null(result) || !A->matrix ||
      !B->matrix)
    res = INCORRECT_MATRIX;
  else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (is_ptr_null(A) || is_ptr_null(result))
    res = INCORRECT_MATRIX;
  else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int n = 0; n < result->rows; n++) {
      for (int m = 0; m < result->columns; m++) {
        result->matrix[n][m] = A->matrix[m][n];
      }
    }
  }
  return res;
}
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  {
    int res = OK;
    if (!A || !A->matrix || !result || A->columns <= 1 || A->rows <= 1) {
      res = INCORRECT_MATRIX;
    } else if (A->columns != A->rows) {
      res = CALC_ERROR;
    } else {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t minor;
          find_minor(i, j, A, &minor);
          double det = 0;
          s21_determinant(&minor, &det);
          det *= pow(-1, 2 + i + j);
          result->matrix[i][j] = det;
          s21_remove_matrix(&minor);
        }
      }
    }
    return res;
  }
}

int s21_determinant(matrix_t *A, double *result) {
  int res = OK;
  if (is_ptr_null(A) || !result || A->columns <= 0 || A->rows <= 0) {
    res = INCORRECT_MATRIX;
  } else if (A->columns != A->rows) {
    res = CALC_ERROR;
  } else {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      *result = 0;
      for (int i = 0; i < A->columns; i++) {
        matrix_t minor_matrix;
        find_minor(0, i, A, &minor_matrix);
        double buffer_determ = 0;
        s21_determinant(&minor_matrix, &buffer_determ);
        s21_remove_matrix(&minor_matrix);
        double buffer_res = pow(-1, 2 + i) * A->matrix[0][i] * buffer_determ;
        *result += buffer_res;
      }
    }
  }
  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (is_ptr_null(A) || !result || A->columns <= 1 || A->rows <= 1) {
    res = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    res = CALC_ERROR;
  } else {
    double determ = 0;
    matrix_t buffer;
    matrix_t buffer_1;
    s21_determinant(A, &determ);
    if (fabs(determ) > 1e-7) {
      s21_calc_complements(A, &buffer);
      s21_transpose(&buffer, &buffer_1);
      s21_remove_matrix(&buffer);
      s21_mult_number(&buffer_1, 1. / fabs(determ), result);
      s21_remove_matrix(&buffer_1);
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] *= -1;
        }
      }
    } else {
      res = CALC_ERROR;
    }
  }
  return res;
}