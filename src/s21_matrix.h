#ifndef S21_MATRIX
#define S21_MATRIX

#include <math.h>
#include <stdlib.h>

enum returns { OK, INCORRECT_MATRIX, CALC_ERROR };
enum compare_returns { FAILLURE, SUCCESS };

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// -----функции операций с матрицами-----

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

//-----дополнительные функции-------
int is_size_zero(int rows, int columns);
int is_ptr_null(matrix_t *A);
int is_size_equal(matrix_t *A, matrix_t *B);
void find_minor(int i, int j, matrix_t *A, matrix_t *result);
#endif
