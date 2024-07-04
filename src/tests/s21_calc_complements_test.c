#include <stdio.h>

#include "s21_matrix_suites.h"

START_TEST(calc_complements_test_1) {
  matrix_t matrix1, matrix2, result = {0};
  s21_create_matrix(3, 3, &matrix1);
  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[1][0] = 0;
  matrix1.matrix[1][1] = 4;
  matrix1.matrix[1][2] = 2;
  matrix1.matrix[2][0] = 5;
  matrix1.matrix[2][1] = 2;
  matrix1.matrix[2][2] = 1;

  s21_create_matrix(3, 3, &matrix2);

  s21_create_matrix(3, 3, &result);
  result.matrix[0][0] = 0;
  result.matrix[0][1] = 10;
  result.matrix[0][2] = -20;
  result.matrix[1][0] = 4;
  result.matrix[1][1] = -14;
  result.matrix[1][2] = 8;
  result.matrix[2][0] = -8;
  result.matrix[2][1] = -2;
  result.matrix[2][2] = 4;

  int res = s21_calc_complements(&matrix1, &matrix2);
  ck_assert_int_eq(s21_eq_matrix(&matrix2, &result), SUCCESS);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_test_2) {
  matrix_t matrix1, matrix2, result = {0};
  s21_create_matrix(4, 4, &matrix1);

  matrix1.matrix[0][0] = 7;
  matrix1.matrix[0][1] = 8;
  matrix1.matrix[0][2] = 9;
  matrix1.matrix[0][3] = 10;
  matrix1.matrix[1][0] = 1;
  matrix1.matrix[1][1] = 2;
  matrix1.matrix[1][2] = 3;
  matrix1.matrix[1][3] = 4;
  matrix1.matrix[2][0] = 6;
  matrix1.matrix[2][1] = 5;
  matrix1.matrix[2][2] = 4;
  matrix1.matrix[2][3] = -3;
  matrix1.matrix[3][0] = 2;
  matrix1.matrix[3][1] = 1;
  matrix1.matrix[3][2] = 0;
  matrix1.matrix[3][3] = 1;
  s21_create_matrix(4, 4, &matrix2);
  s21_create_matrix(4, 4, &result);
  result.matrix[0][0] = -32;
  result.matrix[0][1] = 64;
  result.matrix[0][2] = -32;
  result.matrix[0][3] = 0;
  result.matrix[1][0] = 80;
  result.matrix[1][1] = -160;
  result.matrix[1][2] = 80;
  result.matrix[1][3] = 0;
  result.matrix[2][0] = 12;
  result.matrix[2][1] = -24;
  result.matrix[2][2] = 12;
  result.matrix[2][3] = 0;
  result.matrix[3][0] = 36;
  result.matrix[3][1] = -72;
  result.matrix[3][2] = 36;
  result.matrix[3][3] = 0;
  int res = s21_calc_complements(&matrix1, &matrix2);
  ck_assert_int_eq(s21_eq_matrix(&matrix2, &result), SUCCESS);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_test_3) {
  matrix_t A = {0};
  s21_create_matrix(5, 4, &A);
  matrix_t result = {0};
  s21_create_matrix(5, 4, &result);
  ck_assert_int_eq(s21_calc_complements(&A, &result), CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_test_4) {
  matrix_t A = {0};
  s21_create_matrix(5, 1, &A);
  matrix_t result = {0};
  s21_create_matrix(1, 4, &result);

  ck_assert_int_eq(s21_calc_complements(&A, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *calc_complements_suite() {
  Suite *s;
  TCase *tc;
  s = suite_create("calc_complements");
  tc = tcase_create("calc_complements_case");

  tcase_add_test(tc, calc_complements_test_1);
  tcase_add_test(tc, calc_complements_test_2);
  tcase_add_test(tc, calc_complements_test_3);
  tcase_add_test(tc, calc_complements_test_4);

  suite_add_tcase(s, tc);
  return s;
}
