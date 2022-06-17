#include "s21_matrix.h"

#include <check.h>
#include <math.h>
#include <stdio.h>

START_TEST(create_matrix) {
  double orig_matrix[5][5] = {{0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0}};
  matrix_t res_matrix = s21_create_matrix(5, 5);
  for (int i = 0; i < res_matrix.rows; i++) {
    for (int j = 0; j < res_matrix.columns; j++) {
      ck_assert_double_eq(res_matrix.matrix[i][j], orig_matrix[i][j]);
    }
  }
  s21_remove_matrix(&res_matrix);
}
END_TEST

START_TEST(remove_matrix) {
  double first[5][5] = {{2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55}};
  matrix_t first_matrix = s21_create_matrix(5, 5);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  s21_remove_matrix(&first_matrix);
  ck_assert_int_eq(first_matrix.matrix_type, INCORRECT_MATRIX);
  ck_assert_ptr_null(first_matrix.matrix);
}
END_TEST

START_TEST(sum_matrix_1) {
  double first[5][5] = {{2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55}};
  double second[5][5] = {{3.01, 2.01, 3.01, 2.01, 3.01},
                         {3.01, 2.01, 3.01, 2.01, 3.01},
                         {3.01, 2.01, 3.01, 2.01, 3.01},
                         {3.01, 2.01, 3.01, 2.01, 3.01},
                         {3.01, 2.01, 3.01, 2.01, 3.01}};
  double third[5][5] = {{5.56, 5.56, 5.56, 5.56, 5.56},
                        {5.56, 5.56, 5.56, 5.56, 5.56},
                        {5.56, 5.56, 5.56, 5.56, 5.56},
                        {5.56, 5.56, 5.56, 5.56, 5.56},
                        {5.56, 5.56, 5.56, 5.56, 5.56}};
  matrix_t first_matrix = s21_create_matrix(5, 5);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t sec_matrix = s21_create_matrix(5, 5);
  init_from_arr(&sec_matrix, &second[0][0]);
  sec_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t orig_matrix = s21_create_matrix(5, 5);
  init_from_arr(&orig_matrix, &third[0][0]);
  orig_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t res_matrix = s21_sum_matrix(&first_matrix, &sec_matrix);
  ck_assert_int_eq(res_matrix.rows, orig_matrix.rows);
  ck_assert_int_eq(res_matrix.columns, orig_matrix.columns);
  ck_assert_int_eq(res_matrix.matrix_type, orig_matrix.matrix_type);
  for (int i = 0; i < orig_matrix.rows; i++) {
    for (int j = 0; j < orig_matrix.columns; j++) {
      ck_assert_double_eq(res_matrix.matrix[i][j], orig_matrix.matrix[i][j]);
    }
  }
  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&sec_matrix);
  s21_remove_matrix(&orig_matrix);
  s21_remove_matrix(&res_matrix);
}
END_TEST

START_TEST(sum_matrix_2) {
  double first[5][5] = {
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432},
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432},
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432},
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432},
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432}};
  double second[5][5] = {
      {-0.321456987, -1.098765432, -2.0010023, -0.321456987, -1.098765432},
      {-0.321456987, -1.098765432, -2.0010023, -0.321456987, -1.098765432},
      {-0.321456987, -1.098765432, -2.0010023, -0.321456987, -1.098765432},
      {-0.321456987, -1.098765432, -2.0010023, -0.321456987, -1.098765432},
      {-0.321456987, -1.098765432, -2.0010023, -0.321456987, -1.098765432}};
  double third[5][5] = {{0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}};
  matrix_t first_matrix = s21_create_matrix(5, 5);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t sec_matrix = s21_create_matrix(5, 5);
  init_from_arr(&sec_matrix, &second[0][0]);
  sec_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t orig_matrix = s21_create_matrix(5, 5);
  init_from_arr(&orig_matrix, &third[0][0]);
  orig_matrix.matrix_type = ZERO_MATRIX;
  matrix_t res_matrix = s21_sum_matrix(&first_matrix, &sec_matrix);
  ck_assert_int_eq(res_matrix.rows, orig_matrix.rows);
  ck_assert_int_eq(res_matrix.columns, orig_matrix.columns);
  ck_assert_int_eq(res_matrix.matrix_type, orig_matrix.matrix_type);
  for (int i = 0; i < orig_matrix.rows; i++) {
    for (int j = 0; j < orig_matrix.columns; j++) {
      ck_assert_double_eq(res_matrix.matrix[i][j], orig_matrix.matrix[i][j]);
    }
  }
  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&sec_matrix);
  s21_remove_matrix(&orig_matrix);
  s21_remove_matrix(&res_matrix);
}
END_TEST

START_TEST(sum_matrix_3) {
  double first[5][5] = {{2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55}};
  double second[2][5] = {{3.01, 2.01, 3.01, 2.01, 3.01},
                         {3.01, 2.01, 3.01, 2.01, 3.01}};
  double third[5][5] = {{0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}};
  matrix_t first_matrix = s21_create_matrix(5, 5);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t sec_matrix = s21_create_matrix(2, 5);
  init_from_arr(&sec_matrix, &second[0][0]);
  sec_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t orig_matrix = s21_create_matrix(5, 5);
  init_from_arr(&orig_matrix, &third[0][0]);
  orig_matrix.matrix_type = INCORRECT_MATRIX;
  matrix_t res_matrix = s21_sum_matrix(&first_matrix, &sec_matrix);
  ck_assert_int_eq(res_matrix.rows, orig_matrix.rows);
  ck_assert_int_eq(res_matrix.columns, orig_matrix.columns);
  ck_assert_int_eq(res_matrix.matrix_type, orig_matrix.matrix_type);
  for (int i = 0; i < orig_matrix.rows; i++) {
    for (int j = 0; j < orig_matrix.columns; j++) {
      ck_assert_double_eq(res_matrix.matrix[i][j], orig_matrix.matrix[i][j]);
    }
  }
  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&sec_matrix);
  s21_remove_matrix(&orig_matrix);
  s21_remove_matrix(&res_matrix);
}
END_TEST

START_TEST(sum_matrix_4) {
  double first[5][5] = {{0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}};
  double second[5][5] = {{3.01, 2.01, 3.01, 2.01, 3.01},
                         {3.01, 2.01, 3.01, 2.01, 3.01}};
  double third[5][5] = {{0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}};
  matrix_t first_matrix = s21_create_matrix(5, 5);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t sec_matrix = s21_create_matrix(5, 5);
  init_from_arr(&sec_matrix, &second[0][0]);
  sec_matrix.matrix_type = INCORRECT_MATRIX;
  matrix_t orig_matrix = s21_create_matrix(5, 5);
  init_from_arr(&orig_matrix, &third[0][0]);
  orig_matrix.matrix_type = INCORRECT_MATRIX;
  matrix_t res_matrix = s21_sum_matrix(&first_matrix, &sec_matrix);
  ck_assert_int_eq(res_matrix.rows, orig_matrix.rows);
  ck_assert_int_eq(res_matrix.columns, orig_matrix.columns);
  ck_assert_int_eq(res_matrix.matrix_type, orig_matrix.matrix_type);
  for (int i = 0; i < orig_matrix.rows; i++) {
    for (int j = 0; j < orig_matrix.columns; j++) {
      ck_assert_double_eq(res_matrix.matrix[i][j], orig_matrix.matrix[i][j]);
    }
  }
  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&sec_matrix);
  s21_remove_matrix(&orig_matrix);
  s21_remove_matrix(&res_matrix);
}
END_TEST

START_TEST(sum_matrix_5) {
  double first[5][5] = {
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432},
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432},
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432},
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432},
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432}};
  double second[5][5] = {
      {0.678543013, -1.098765432, -2.0010023, -0.321456987, -1.098765432},
      {-0.321456987, -0.098765432, -2.0010023, -0.321456987, -1.098765432},
      {-0.321456987, -1.098765432, -1.0010023, -0.321456987, -1.098765432},
      {-0.321456987, -1.098765432, -2.0010023, 0.678543013, -1.098765432},
      {-0.321456987, -1.098765432, -2.0010023, -0.321456987, -0.098765432}};
  double third[5][5] = {{1, 0, 0, 0, 0},
                        {0, 1, 0, 0, 0},
                        {0, 0, 1, 0, 0},
                        {0, 0, 0, 1, 0},
                        {0, 0, 0, 0, 1}};
  matrix_t first_matrix = s21_create_matrix(5, 5);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t sec_matrix = s21_create_matrix(5, 5);
  init_from_arr(&sec_matrix, &second[0][0]);
  sec_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t orig_matrix = s21_create_matrix(5, 5);
  init_from_arr(&orig_matrix, &third[0][0]);
  orig_matrix.matrix_type = IDENTITY_MATRIX;
  matrix_t res_matrix = s21_sum_matrix(&first_matrix, &sec_matrix);
  ck_assert_int_eq(res_matrix.rows, orig_matrix.rows);
  ck_assert_int_eq(res_matrix.columns, orig_matrix.columns);
  ck_assert_int_eq(res_matrix.matrix_type, orig_matrix.matrix_type);
  for (int i = 0; i < orig_matrix.rows; i++) {
    for (int j = 0; j < orig_matrix.columns; j++) {
      ck_assert_double_eq_tol(res_matrix.matrix[i][j], orig_matrix.matrix[i][j],
                              7);
    }
  }
  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&sec_matrix);
  s21_remove_matrix(&orig_matrix);
  s21_remove_matrix(&res_matrix);
}
END_TEST

START_TEST(sub_matrix_1) {
  double first[5][5] = {
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432},
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432},
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432},
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432},
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432}};
  double second[5][5] = {{1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                         {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                         {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                         {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                         {1.1111, 2.2222, 3.3333, 2.2222, 1.1111}};
  double third[5][5] = {
      {-0.789643013, -1.123434568, -1.3322977, -1.900743013, -0.012334568},
      {-0.789643013, -1.123434568, -1.3322977, -1.900743013, -0.012334568},
      {-0.789643013, -1.123434568, -1.3322977, -1.900743013, -0.012334568},
      {-0.789643013, -1.123434568, -1.3322977, -1.900743013, -0.012334568},
      {-0.789643013, -1.123434568, -1.3322977, -1.900743013, -0.012334568}};
  matrix_t first_matrix = s21_create_matrix(5, 5);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t sec_matrix = s21_create_matrix(5, 5);
  init_from_arr(&sec_matrix, &second[0][0]);
  sec_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t orig_matrix = s21_create_matrix(5, 5);
  init_from_arr(&orig_matrix, &third[0][0]);
  orig_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t res_matrix = s21_sub_matrix(&first_matrix, &sec_matrix);
  ck_assert_int_eq(res_matrix.rows, orig_matrix.rows);
  ck_assert_int_eq(res_matrix.columns, orig_matrix.columns);
  ck_assert_int_eq(res_matrix.matrix_type, orig_matrix.matrix_type);
  for (int i = 0; i < orig_matrix.rows; i++) {
    for (int j = 0; j < orig_matrix.columns; j++) {
      ck_assert_double_eq_tol(res_matrix.matrix[i][j], orig_matrix.matrix[i][j],
                              8);
    }
  }
  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&sec_matrix);
  s21_remove_matrix(&orig_matrix);
  s21_remove_matrix(&res_matrix);
}
END_TEST

START_TEST(sub_matrix_2) {
  double first[5][5] = {{2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55}};
  double second[2][5] = {{3.01, 2.01, 3.01, 2.01, 3.01},
                         {3.01, 2.01, 3.01, 2.01, 3.01}};
  double third[5][5] = {{0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}};
  matrix_t first_matrix = s21_create_matrix(5, 5);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t sec_matrix = s21_create_matrix(2, 5);
  init_from_arr(&sec_matrix, &second[0][0]);
  sec_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t orig_matrix = s21_create_matrix(5, 5);
  init_from_arr(&orig_matrix, &third[0][0]);
  orig_matrix.matrix_type = INCORRECT_MATRIX;
  matrix_t res_matrix = s21_sub_matrix(&first_matrix, &sec_matrix);
  ck_assert_int_eq(res_matrix.rows, orig_matrix.rows);
  ck_assert_int_eq(res_matrix.columns, orig_matrix.columns);
  ck_assert_int_eq(res_matrix.matrix_type, orig_matrix.matrix_type);
  for (int i = 0; i < orig_matrix.rows; i++) {
    for (int j = 0; j < orig_matrix.columns; j++) {
      ck_assert_double_eq(res_matrix.matrix[i][j], orig_matrix.matrix[i][j]);
    }
  }
  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&sec_matrix);
  s21_remove_matrix(&orig_matrix);
  s21_remove_matrix(&res_matrix);
}
END_TEST

START_TEST(sub_matrix_3) {
  double first[5][5] = {{2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55},
                        {2.55, 3.55, 2.55, 3.55, 2.55}};
  double second[5][5] = {{3.01, 2.01, 3.01, 2.01, 3.01},
                         {3.01, 2.01, 3.01, 2.01, 3.01}};
  double third[5][5] = {{0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}};
  matrix_t first_matrix = s21_create_matrix(5, 5);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t sec_matrix = s21_create_matrix(5, 5);
  init_from_arr(&sec_matrix, &second[0][0]);
  sec_matrix.matrix_type = INCORRECT_MATRIX;
  matrix_t orig_matrix = s21_create_matrix(5, 5);
  init_from_arr(&orig_matrix, &third[0][0]);
  orig_matrix.matrix_type = INCORRECT_MATRIX;
  matrix_t res_matrix = s21_sub_matrix(&first_matrix, &sec_matrix);
  ck_assert_int_eq(res_matrix.rows, orig_matrix.rows);
  ck_assert_int_eq(res_matrix.columns, orig_matrix.columns);
  ck_assert_int_eq(res_matrix.matrix_type, orig_matrix.matrix_type);
  for (int i = 0; i < orig_matrix.rows; i++) {
    for (int j = 0; j < orig_matrix.columns; j++) {
      ck_assert_double_eq(res_matrix.matrix[i][j], orig_matrix.matrix[i][j]);
    }
  }
  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&sec_matrix);
  s21_remove_matrix(&orig_matrix);
  s21_remove_matrix(&res_matrix);
}
END_TEST

START_TEST(eq_matrix_1) {
  double first[5][5] = {
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432},
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432},
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432},
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432},
      {0.321456987, 1.098765432, 2.0010023, 0.321456987, 1.098765432}};
  double second[5][5] = {{1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                         {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                         {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                         {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                         {1.1111, 2.2222, 3.3333, 2.2222, 1.1111}};
  matrix_t first_matrix = s21_create_matrix(5, 5);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t sec_matrix = s21_create_matrix(5, 5);
  init_from_arr(&sec_matrix, &second[0][0]);
  sec_matrix.matrix_type = CORRECT_MATRIX;
  int res = s21_eq_matrix(&first_matrix, &sec_matrix);
  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&sec_matrix);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(eq_matrix_2) {
  double first[5][5] = {{1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111}};
  double second[5][5] = {{1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                         {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                         {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                         {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                         {1.1111, 2.2222, 3.3333, 2.2222, 1.1111}};
  matrix_t first_matrix = s21_create_matrix(5, 5);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t sec_matrix = s21_create_matrix(5, 5);
  init_from_arr(&sec_matrix, &second[0][0]);
  sec_matrix.matrix_type = CORRECT_MATRIX;
  int res = s21_eq_matrix(&first_matrix, &sec_matrix);
  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&sec_matrix);
  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(eq_matrix_3) {
  double first[5][5] = {{1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111}};
  double second[3][5] = {{1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                         {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                         {1.1111, 2.2222, 3.3333, 2.2222, 1.1111}};
  matrix_t first_matrix = s21_create_matrix(5, 5);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t sec_matrix = s21_create_matrix(3, 5);
  init_from_arr(&sec_matrix, &second[0][0]);
  sec_matrix.matrix_type = CORRECT_MATRIX;
  int res = s21_eq_matrix(&first_matrix, &sec_matrix);
  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&sec_matrix);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(mult_number_1) {
  double first[5][5] = {{1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111}};
  matrix_t first_matrix = s21_create_matrix(5, 5);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  double number = 0.001;
  double orig[5][5] = {{0.0011111, 0.0022222, 0.0033333, 0.0022222, 0.0011111},
                       {0.0011111, 0.0022222, 0.0033333, 0.0022222, 0.0011111},
                       {0.0011111, 0.0022222, 0.0033333, 0.0022222, 0.0011111},
                       {0.0011111, 0.0022222, 0.0033333, 0.0022222, 0.0011111},
                       {0.0011111, 0.0022222, 0.0033333, 0.0022222, 0.0011111}};
  matrix_t res_matrix = s21_mult_number(&first_matrix, number);
  for (int i = 0; i < res_matrix.rows; i++) {
    for (int j = 0; j < res_matrix.columns; j++) {
      ck_assert_double_eq(res_matrix.matrix[i][j], orig[i][j]);
    }
  }
  ck_assert_int_eq(res_matrix.matrix_type, CORRECT_MATRIX);
  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&res_matrix);
}
END_TEST

START_TEST(mult_number_2) {
  double first[4][5] = {{1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111}};
  matrix_t first_matrix = s21_create_matrix(5, 5);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = INCORRECT_MATRIX;
  double number = 1.5;
  double orig[5][5] = {{0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0}};
  matrix_t res_matrix = s21_mult_number(&first_matrix, number);
  for (int i = 0; i < res_matrix.rows; i++) {
    for (int j = 0; j < res_matrix.columns; j++) {
      ck_assert_double_eq(res_matrix.matrix[i][j], orig[i][j]);
    }
  }
  ck_assert_int_eq(res_matrix.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&res_matrix);
}
END_TEST

START_TEST(mult_number_3) {
  double first[5][5] = {{1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111},
                        {1.1111, 2.2222, 3.3333, 2.2222, 1.1111}};
  matrix_t first_matrix = s21_create_matrix(5, 5);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  double number = 0;
  double orig[5][5] = {{0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0}};
  matrix_t res_matrix = s21_mult_number(&first_matrix, number);
  for (int i = 0; i < res_matrix.rows; i++) {
    for (int j = 0; j < res_matrix.columns; j++) {
      ck_assert_double_eq(res_matrix.matrix[i][j], orig[i][j]);
    }
  }
  ck_assert_int_eq(res_matrix.matrix_type, ZERO_MATRIX);
  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&res_matrix);
}
END_TEST

START_TEST(mult_matrix_1) {
  double first[5][3] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
  matrix_t first_matrix = s21_create_matrix(5, 3);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  double second[3][4] = {{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}};
  matrix_t second_matrix = s21_create_matrix(3, 4);
  init_from_arr(&second_matrix, &second[0][0]);
  second_matrix.matrix_type = CORRECT_MATRIX;
  double orig[5][4] = {{6, 12, 18, 24},
                       {6, 12, 18, 24},
                       {6, 12, 18, 24},
                       {6, 12, 18, 24},
                       {6, 12, 18, 24}};
  matrix_t res_matrix = s21_mult_matrix(&first_matrix, &second_matrix);
  ck_assert_int_eq(res_matrix.matrix_type, CORRECT_MATRIX);
  for (int i = 0; i < res_matrix.rows; i++) {
    for (int j = 0; j < res_matrix.columns; j++) {
      ck_assert_double_eq_tol(res_matrix.matrix[i][j], orig[i][j], 0.000001);
    }
  }
  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&second_matrix);
  s21_remove_matrix(&res_matrix);
}
END_TEST

START_TEST(mult_matrix_2) {
  double first[3][5] = {{1, 2, 3, 1, 2}, {3, 1, 2, 3, 1}, {2, 3, 1, 2, 3}};
  matrix_t first_matrix = s21_create_matrix(3, 5);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  double second[3][4] = {{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}};
  matrix_t second_matrix = s21_create_matrix(3, 4);
  init_from_arr(&second_matrix, &second[0][0]);
  second_matrix.matrix_type = CORRECT_MATRIX;
  double orig[3][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  matrix_t res_matrix = s21_mult_matrix(&first_matrix, &second_matrix);
  ck_assert_int_eq(res_matrix.matrix_type, INCORRECT_MATRIX);
  for (int i = 0; i < res_matrix.rows; i++) {
    for (int j = 0; j < res_matrix.columns; j++) {
      ck_assert_double_eq_tol(res_matrix.matrix[i][j], orig[i][j], 0.000001);
    }
  }
  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&second_matrix);
  s21_remove_matrix(&res_matrix);
}
END_TEST

START_TEST(mult_matrix_3) {
  double first[3][3] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
  matrix_t first_matrix = s21_create_matrix(3, 3);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t second_matrix = s21_create_matrix(3, 3);
  second_matrix.matrix_type = INCORRECT_MATRIX;
  matrix_t res_matrix = s21_mult_matrix(&first_matrix, &second_matrix);
  ck_assert_int_eq(res_matrix.matrix_type, INCORRECT_MATRIX);

  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&second_matrix);
  s21_remove_matrix(&res_matrix);
}
END_TEST

START_TEST(transpose_1) {
  double first[3][3] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
  matrix_t first_matrix = s21_create_matrix(3, 3);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  double orig[3][3] = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
  matrix_t res_matrix = s21_transpose(&first_matrix);
  ck_assert_int_eq(res_matrix.matrix_type, CORRECT_MATRIX);
  for (int i = 0; i < res_matrix.rows; i++) {
    for (int j = 0; j < res_matrix.columns; j++) {
      ck_assert_double_eq_tol(res_matrix.matrix[i][j], orig[i][j], 0.000001);
    }
  }
  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&res_matrix);
}
END_TEST

START_TEST(transpose_2) {
  double first[0][0];
  matrix_t first_matrix = s21_create_matrix(0, 0);
  init_from_arr(&first_matrix, &first[0][0]);
  first_matrix.matrix_type = CORRECT_MATRIX;
  matrix_t res_matrix = s21_transpose(&first_matrix);
  ck_assert_int_eq(res_matrix.matrix_type, INCORRECT_MATRIX);
  ck_assert_ptr_null(res_matrix.matrix);
  s21_remove_matrix(&first_matrix);
  s21_remove_matrix(&res_matrix);
}
END_TEST

START_TEST(compl_1) {
  double arr[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  matrix_t src = s21_create_matrix(3, 3);
  init_from_arr(&src, &arr[0][0]);
  src.matrix_type = CORRECT_MATRIX;
  matrix_t dst = s21_calc_complements(&src);
  double orig[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  ck_assert_int_eq(dst.matrix_type, CORRECT_MATRIX);
  for (int i = 0; i < dst.rows; i++) {
    for (int j = 0; j < dst.columns; j++) {
      ck_assert_double_eq(dst.matrix[i][j], orig[i][j]);
    }
  }
  s21_remove_matrix(&src);
  s21_remove_matrix(&dst);
}
END_TEST

START_TEST(compl_2) {
  double arr[2][3] = {{1, 2, 3}, {0, 4, 2}};
  matrix_t src = s21_create_matrix(2, 3);
  init_from_arr(&src, &arr[0][0]);
  src.matrix_type = INCORRECT_MATRIX;
  matrix_t dst = s21_calc_complements(&src);
  ck_assert_int_eq(dst.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&src);
  s21_remove_matrix(&dst);
}
END_TEST

START_TEST(compl_3) {
  double arr[2][2] = {{1, 2}, {0, 4}};
  matrix_t src = s21_create_matrix(2, 2);
  init_from_arr(&src, &arr[0][0]);
  src.matrix_type = CORRECT_MATRIX;
  matrix_t dst = s21_calc_complements(&src);
  double orig[2][2] = {{4, 0}, {-2, 1}};
  ck_assert_int_eq(dst.matrix_type, CORRECT_MATRIX);
  for (int i = 0; i < dst.rows; i++) {
    for (int j = 0; j < dst.columns; j++) {
      ck_assert_double_eq(dst.matrix[i][j], orig[i][j]);
    }
  }
  s21_remove_matrix(&src);
  s21_remove_matrix(&dst);
}
END_TEST

START_TEST(compl_4) {
  double arr[1][1] = {{5}};
  matrix_t src = s21_create_matrix(1, 1);
  init_from_arr(&src, &arr[0][0]);
  src.matrix_type = CORRECT_MATRIX;
  matrix_t dst = s21_calc_complements(&src);
  ck_assert_int_eq(dst.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&src);
  s21_remove_matrix(&dst);
}
END_TEST

START_TEST(determ_1) {
  double arr[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  matrix_t src = s21_create_matrix(3, 4);
  init_from_arr(&src, &arr[0][0]);
  src.matrix_type = INCORRECT_MATRIX;
  double det = s21_determinant(&src);
  ck_assert_double_nan(det);
  s21_remove_matrix(&src);
}
END_TEST

START_TEST(determ_2) {
  double arr[1][1] = {{2}};
  matrix_t src = s21_create_matrix(1, 1);
  init_from_arr(&src, &arr[0][0]);
  src.matrix_type = CORRECT_MATRIX;
  double det = s21_determinant(&src);
  double orig_det = 2;
  ck_assert_double_eq_tol(det, orig_det, 0.000001);

  s21_remove_matrix(&src);
}
END_TEST

START_TEST(determ_3) {
  double arr[5][5] = {{1, 2, 1, 4, 2},
                      {2, 1, 3, 2, 1},
                      {1, 2, 2, 2, 1},
                      {2, 1, 1, 1, 2},
                      {1, 2, 1, 2, 3}};
  matrix_t src = s21_create_matrix(5, 5);
  init_from_arr(&src, &arr[0][0]);
  src.matrix_type = CORRECT_MATRIX;
  double det = s21_determinant(&src);
  double orig_det = 21;
  ck_assert_double_eq_tol(det, orig_det, 0.000001);

  s21_remove_matrix(&src);
}
END_TEST

START_TEST(determ_4) {
  double arr[2][2] = {{1, 2}, {0, 4}};
  matrix_t src = s21_create_matrix(2, 2);
  init_from_arr(&src, &arr[0][0]);
  src.matrix_type = CORRECT_MATRIX;
  double det = s21_determinant(&src);
  double orig_det = 4;
  ck_assert_double_eq_tol(det, orig_det, 0.000001);

  s21_remove_matrix(&src);
}
END_TEST

START_TEST(invert_1) {
  double src[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  matrix_t src_arr = s21_create_matrix(3, 3);
  init_from_arr(&src_arr, &src[0][0]);
  src_arr.matrix_type = CORRECT_MATRIX;
  matrix_t dst = s21_inverse_matrix(&src_arr);
  s21_remove_matrix(&src_arr);
  double orig[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  ck_assert_int_eq(dst.matrix_type, CORRECT_MATRIX);
  for (int i = 0; i < dst.rows; i++) {
    for (int j = 0; j < dst.columns; j++) {
      ck_assert_double_eq(dst.matrix[i][j], orig[i][j]);
    }
  }
  s21_remove_matrix(&dst);
}
END_TEST

START_TEST(invert_2) {
  double src[1][1] = {{2}};
  matrix_t src_arr = s21_create_matrix(1, 1);
  init_from_arr(&src_arr, &src[0][0]);
  src_arr.matrix_type = CORRECT_MATRIX;
  matrix_t dst = s21_inverse_matrix(&src_arr);
  s21_remove_matrix(&src_arr);
  double orig[3][3] = {{0.5}};
  ck_assert_int_eq(dst.matrix_type, CORRECT_MATRIX);
  for (int i = 0; i < dst.rows; i++) {
    for (int j = 0; j < dst.columns; j++) {
      ck_assert_double_eq(dst.matrix[i][j], orig[i][j]);
    }
  }
  s21_remove_matrix(&dst);
}
END_TEST

START_TEST(invert_3) {
  double src[2][2] = {{2, -3}, {1, 1}};
  matrix_t src_arr = s21_create_matrix(2, 2);
  init_from_arr(&src_arr, &src[0][0]);
  src_arr.matrix_type = CORRECT_MATRIX;
  matrix_t dst = s21_inverse_matrix(&src_arr);
  s21_remove_matrix(&src_arr);
  double orig[2][2] = {{0.2, 0.6}, {-0.2, 0.4}};
  ck_assert_int_eq(dst.matrix_type, CORRECT_MATRIX);
  for (int i = 0; i < dst.rows; i++) {
    for (int j = 0; j < dst.columns; j++) {
      ck_assert_double_eq_tol(dst.matrix[i][j], orig[i][j], 0.000001);
    }
  }
  s21_remove_matrix(&dst);
}
END_TEST

START_TEST(invert_4) {
  double src[3][3] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
  matrix_t src_arr = s21_create_matrix(3, 3);
  init_from_arr(&src_arr, &src[0][0]);
  src_arr.matrix_type = CORRECT_MATRIX;
  matrix_t dst = s21_inverse_matrix(&src_arr);
  s21_remove_matrix(&src_arr);
  ck_assert_int_eq(dst.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&dst);
}
END_TEST

Suite *Creation() {
  Suite *s1 = suite_create("Creation");
  TCase *tc1_1 = tcase_create("create_and_remove_matrix");

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, create_matrix);
  tcase_add_test(tc1_1, remove_matrix);
  return s1;
}

Suite *Addition() {
  Suite *s2 = suite_create("Addition");
  TCase *tc1_1 = tcase_create("sum_and_sub");

  suite_add_tcase(s2, tc1_1);
  tcase_add_test(tc1_1, sum_matrix_1);
  tcase_add_test(tc1_1, sum_matrix_2);
  tcase_add_test(tc1_1, sum_matrix_3);
  tcase_add_test(tc1_1, sum_matrix_4);
  tcase_add_test(tc1_1, sum_matrix_5);

  tcase_add_test(tc1_1, sub_matrix_1);
  tcase_add_test(tc1_1, sub_matrix_2);
  tcase_add_test(tc1_1, sub_matrix_3);

  return s2;
}

Suite *Compare() {
  Suite *s3 = suite_create("Compare");
  TCase *tc1_3 = tcase_create("eq_matrix");

  suite_add_tcase(s3, tc1_3);
  tcase_add_test(tc1_3, eq_matrix_1);
  tcase_add_test(tc1_3, eq_matrix_2);
  tcase_add_test(tc1_3, eq_matrix_3);

  return s3;
}

Suite *Multiplication() {
  Suite *s4 = suite_create("Multiplication");
  TCase *tc1_1 = tcase_create("mult_matrix");

  suite_add_tcase(s4, tc1_1);
  tcase_add_test(tc1_1, mult_number_1);
  tcase_add_test(tc1_1, mult_number_2);
  tcase_add_test(tc1_1, mult_number_3);
  tcase_add_test(tc1_1, mult_matrix_1);
  tcase_add_test(tc1_1, mult_matrix_2);
  tcase_add_test(tc1_1, mult_matrix_3);
  return s4;
}

Suite *Transpose() {
  Suite *s5 = suite_create("Transpose");
  TCase *tc1_1 = tcase_create("trans_matrix");

  suite_add_tcase(s5, tc1_1);
  tcase_add_test(tc1_1, transpose_1);
  tcase_add_test(tc1_1, transpose_2);
  return s5;
}

Suite *Complements() {
  Suite *s6 = suite_create("Complements");
  TCase *tc1_1 = tcase_create("calc_complements");

  suite_add_tcase(s6, tc1_1);
  tcase_add_test(tc1_1, compl_1);
  tcase_add_test(tc1_1, compl_2);
  tcase_add_test(tc1_1, compl_3);
  tcase_add_test(tc1_1, compl_4);

  return s6;
}

Suite *Determinant() {
  Suite *s7 = suite_create("Determinant");
  TCase *tc1_1 = tcase_create("determ");

  suite_add_tcase(s7, tc1_1);
  tcase_add_test(tc1_1, determ_1);
  tcase_add_test(tc1_1, determ_2);
  tcase_add_test(tc1_1, determ_3);
  tcase_add_test(tc1_1, determ_4);
  return s7;
}

Suite *Inversion() {
  Suite *s8 = suite_create("Inversion");
  TCase *tc1_1 = tcase_create("invert");

  suite_add_tcase(s8, tc1_1);
  tcase_add_test(tc1_1, invert_1);
  tcase_add_test(tc1_1, invert_2);
  tcase_add_test(tc1_1, invert_3);
  tcase_add_test(tc1_1, invert_4);

  return s8;
}

int main(void) {
  int nf = 0;
  Suite *s1 = Creation();
  Suite *s2 = Addition();
  Suite *s3 = Compare();
  Suite *s4 = Multiplication();
  Suite *s5 = Transpose();
  Suite *s6 = Complements();
  Suite *s7 = Determinant();
  Suite *s8 = Inversion();

  SRunner *sr1 = srunner_create(s1);
  SRunner *sr2 = srunner_create(s2);
  SRunner *sr3 = srunner_create(s3);
  SRunner *sr4 = srunner_create(s4);
  SRunner *sr5 = srunner_create(s5);
  SRunner *sr6 = srunner_create(s6);
  SRunner *sr7 = srunner_create(s7);
  SRunner *sr8 = srunner_create(s8);

  srunner_run_all(sr1, CK_VERBOSE);
  nf += srunner_ntests_failed(sr1);
  srunner_free(sr1);
  srunner_run_all(sr2, CK_VERBOSE);
  nf += srunner_ntests_failed(sr2);
  srunner_free(sr2);
  srunner_run_all(sr3, CK_VERBOSE);
  nf += srunner_ntests_failed(sr3);
  srunner_free(sr3);
  srunner_run_all(sr4, CK_VERBOSE);
  nf += srunner_ntests_failed(sr4);
  srunner_free(sr4);
  srunner_run_all(sr5, CK_VERBOSE);
  nf += srunner_ntests_failed(sr5);
  srunner_free(sr5);
  srunner_run_all(sr6, CK_VERBOSE);
  nf += srunner_ntests_failed(sr6);
  srunner_free(sr6);
  srunner_run_all(sr7, CK_VERBOSE);
  nf += srunner_ntests_failed(sr7);
  srunner_free(sr7);
  srunner_run_all(sr8, CK_VERBOSE);
  nf += srunner_ntests_failed(sr8);
  srunner_free(sr8);

  return nf == 0 ? 0 : 1;
}
