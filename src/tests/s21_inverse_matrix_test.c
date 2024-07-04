#include <stdio.h>

#include "s21_matrix_suites.h"

START_TEST(inverse_matrix_test_1) {
  matrix_t matrix1, matrix2, result;
  s21_create_matrix(3, 3, &result);
  s21_create_matrix(3, 3, &matrix1);

  matrix1.matrix[0][0] = 2;
  matrix1.matrix[0][1] = 5;
  matrix1.matrix[0][2] = 7;
  matrix1.matrix[1][0] = 6;
  matrix1.matrix[1][1] = 3;
  matrix1.matrix[1][2] = 4;
  matrix1.matrix[2][0] = 5;
  matrix1.matrix[2][1] = -2;
  matrix1.matrix[2][2] = -3;

  s21_create_matrix(3, 3, &matrix2);

  matrix2.matrix[0][0] = 1;
  matrix2.matrix[0][1] = -1;
  matrix2.matrix[0][2] = 1;
  matrix2.matrix[1][0] = -38;
  matrix2.matrix[1][1] = 41;
  matrix2.matrix[1][2] = -34;
  matrix2.matrix[2][0] = 27;
  matrix2.matrix[2][1] = -29;
  matrix2.matrix[2][2] = 24;
  s21_inverse_matrix(&matrix1, &result);
  ck_assert_int_eq(s21_eq_matrix(&matrix2, &result), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_test_2) {
  matrix_t matrix1, result;
  s21_create_matrix(3, 3, &result);
  s21_create_matrix(3, 3, &matrix1);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[1][0] = 4;
  matrix1.matrix[1][1] = 5;
  matrix1.matrix[1][2] = 6;
  matrix1.matrix[2][0] = 7;
  matrix1.matrix[2][1] = 8;
  matrix1.matrix[2][2] = 9;
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), CALC_ERROR);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
}
END_TEST
START_TEST(inverse_matrix_test_3) {
  matrix_t matrix1, result;
  s21_create_matrix(3, 4, &result);
  s21_create_matrix(3, 4, &matrix1);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[0][3] = 0;
  matrix1.matrix[1][0] = 4;
  matrix1.matrix[1][1] = 2;
  matrix1.matrix[1][2] = 5;
  matrix1.matrix[1][3] = 2;
  matrix1.matrix[2][0] = 1;
  matrix1.matrix[2][1] = 1;
  matrix1.matrix[2][2] = 1;
  matrix1.matrix[2][3] = 1;
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), CALC_ERROR);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
}
END_TEST

Suite *inverse_matrix_suite() {
  Suite *s;
  TCase *tc;
  s = suite_create("inverse_matrix");
  tc = tcase_create("inverse_matrix_case");

  tcase_add_test(tc, inverse_matrix_test_1);
  tcase_add_test(tc, inverse_matrix_test_2);
  tcase_add_test(tc, inverse_matrix_test_3);

  suite_add_tcase(s, tc);
  return s;
}
