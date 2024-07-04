#include <stdio.h>

#include "s21_matrix_suites.h"

START_TEST(sub_matrix_test_1) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  rows = -rows;
  columns = -columns;
  matrix_t matrix1 = {0};
  s21_create_matrix(rows, columns, &matrix1);
  matrix_t matrix2 = {0};
  s21_create_matrix(columns, rows, &matrix2);
  matrix_t res = {0};
  s21_create_matrix(columns, rows, &res);
  ck_assert_int_eq(s21_sub_matrix(&matrix1, &matrix2, &res), INCORRECT_MATRIX);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&res);
}
END_TEST
START_TEST(sub_matrix_test_2) {
  matrix_t matrix1 = {0};
  int rows = 2;
  int columns = 3;
  s21_create_matrix(rows, columns, &matrix1);
  matrix_t matrix2 = {0};
  int rows1 = 4;
  int columns1 = 5;
  s21_create_matrix(rows1, columns1, &matrix2);

  matrix_t res = {0};
  ck_assert_int_eq(s21_sub_matrix(&matrix1, &matrix2, &res), CALC_ERROR);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&res);
}
END_TEST
START_TEST(sub_matrix_test_3) {
  matrix_t matrix1, matrix2, result, expected_result = {0};
  s21_create_matrix(3, 2, &result);

  s21_create_matrix(3, 2, &matrix1);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;

  matrix1.matrix[1][0] = 2;
  matrix1.matrix[1][1] = 2;

  matrix1.matrix[2][0] = 3;
  matrix1.matrix[2][1] = 3;

  s21_create_matrix(3, 2, &matrix2);
  matrix2.matrix[0][0] = 1;
  matrix2.matrix[0][1] = 1;

  matrix2.matrix[1][0] = 1;
  matrix2.matrix[1][1] = 1;

  matrix2.matrix[2][0] = 1;
  matrix2.matrix[2][1] = 1;

  s21_create_matrix(3, 2, &expected_result);

  expected_result.matrix[0][0] = 0;
  expected_result.matrix[0][1] = 1;

  expected_result.matrix[1][0] = 1;
  expected_result.matrix[1][1] = 1;
  ;
  expected_result.matrix[2][0] = 2;
  expected_result.matrix[2][1] = 2;

  int res = s21_sub_matrix(&matrix1, &matrix2, &result);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&expected_result, &result), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
}
END_TEST

Suite *sub_matrix_suite() {
  Suite *s;
  TCase *tc;
  s = suite_create("sub_matrix");
  tc = tcase_create("sub_matrix_case");

  tcase_add_test(tc, sub_matrix_test_1);
  tcase_add_test(tc, sub_matrix_test_2);
  tcase_add_test(tc, sub_matrix_test_3);

  suite_add_tcase(s, tc);
  return s;
}
