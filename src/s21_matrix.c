#include "s21_matrix.h"

#include <math.h>
#include <stdlib.h>

matrix_t s21_create_matrix(int rows, int columns) {  // Creating matrices
  matrix_t arr;
  if (rows <= 0 || columns <= 0) {
    arr.matrix = NULL;
    arr.rows = 0;
    arr.columns = 0;
    arr.matrix_type = INCORRECT_MATRIX;
  } else {
    arr.matrix_type = ZERO_MATRIX;
    arr.rows = rows;
    arr.columns = columns;
    arr.matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
      arr.matrix[i] = (double *)calloc(columns, sizeof(double));
    }
  }
  return arr;
}

void s21_remove_matrix(matrix_t *A) {  // Cleaning matrices
  if (A->rows > 0 || A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
    A->matrix_type = INCORRECT_MATRIX;
  }
}

int s21_eq_matrix(matrix_t *A,
                  matrix_t *B) {  // Comparison matrices (SUCCESS or FAILURE)
  int res = FAILURE;
  if (A->matrix_type != INCORRECT_MATRIX &&
      B->matrix_type != INCORRECT_MATRIX) {
    if (A->rows == B->rows && A->columns == B->columns) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 0.000001) {
            res = FAILURE;
            i = A->rows;
            break;
          } else {
            res = SUCCESS;
          }
        }
      }
    }
  }
  return res;
}

matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B) {  // adding matrices
  matrix_t arr = s21_create_matrix(A->rows, A->columns);
  if (A->matrix_type != INCORRECT_MATRIX &&
      B->matrix_type != INCORRECT_MATRIX) {
    if (A->rows == B->rows && A->columns == B->columns) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          arr.matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
      arr.matrix_type = CORRECT_MATRIX;
      is_identity(&arr);
      is_zero(&arr);
    } else {
      arr.matrix_type = INCORRECT_MATRIX;
    }
  } else {
    arr.matrix_type = INCORRECT_MATRIX;
  }
  return arr;
}

matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B) {  // substracting matrices
  matrix_t arr = s21_create_matrix(A->rows, A->columns);
  if (A->matrix_type != INCORRECT_MATRIX &&
      B->matrix_type != INCORRECT_MATRIX) {
    if (A->rows == B->rows && A->columns == B->columns) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          arr.matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
      arr.matrix_type = CORRECT_MATRIX;
      is_identity(&arr);
      is_zero(&arr);
    } else {
      arr.matrix_type = INCORRECT_MATRIX;
    }
  } else {
    arr.matrix_type = INCORRECT_MATRIX;
  }
  return arr;
}

matrix_t s21_mult_number(matrix_t *A,
                         double number) {  // Matrix multiplication by scalar
  matrix_t arr = s21_create_matrix(A->rows, A->columns);
  if (A->matrix_type != INCORRECT_MATRIX) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        arr.matrix[i][j] = A->matrix[i][j] * number;
      }
    }
    arr.matrix_type = CORRECT_MATRIX;
    is_identity(&arr);
    is_zero(&arr);
  } else {
    arr.matrix_type = INCORRECT_MATRIX;
  }
  return arr;
}

matrix_t s21_mult_matrix(matrix_t *A,
                         matrix_t *B) {  // Multiplication of two matrices
  matrix_t arr = s21_create_matrix(A->rows, B->columns);
  if (A->matrix_type != INCORRECT_MATRIX &&
      B->matrix_type != INCORRECT_MATRIX) {
    if (A->columns == B->rows) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          for (int k = 0; k < B->columns; k++) {
            arr.matrix[i][k] += A->matrix[i][j] * B->matrix[j][k];
          }
        }
      }
      arr.matrix_type = CORRECT_MATRIX;
      is_identity(&arr);
      is_zero(&arr);
    } else {
      arr.matrix_type = INCORRECT_MATRIX;
    }
  } else {
    arr.matrix_type = INCORRECT_MATRIX;
  }
  return arr;
}

matrix_t s21_transpose(matrix_t *A) {  // Matrix transpose
  matrix_t arr = s21_create_matrix(A->columns, A->rows);
  if (A->matrix_type != INCORRECT_MATRIX && A->rows > 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        arr.matrix[j][i] = A->matrix[i][j];
      }
    }
    arr.matrix_type = CORRECT_MATRIX;
    is_identity(&arr);
    is_zero(&arr);
  } else {
    arr.matrix_type = INCORRECT_MATRIX;
  }
  return arr;
}

matrix_t s21_calc_complements(
    matrix_t *A) {  // Minor of matrix and matrix of algebraic complements
  matrix_t arr = s21_create_matrix(A->rows, A->columns);
  if (A->rows > 1 && A->rows == A->columns &&
      A->matrix_type == CORRECT_MATRIX) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t min_arr = arr_minor(*A, i, j);
        double M = s21_determinant(&min_arr);
        s21_remove_matrix(&min_arr);
        arr.matrix[i][j] = pow((-1), (i + j)) * M;
      }
    }
    arr.matrix_type = CORRECT_MATRIX;
  } else {
    arr.matrix_type = INCORRECT_MATRIX;
  }
  return arr;
}

double s21_determinant(matrix_t *A) {  // Matrix determinant
  if (A->rows != A->columns || A->matrix_type == INCORRECT_MATRIX) return NAN;
  double res = 0;
  if (A->rows > 2) {
    for (int j = 0; j < A->columns; j++) {
      double temp = A->matrix[0][j];
      matrix_t temp_arr = arr_minor(*A, 0, j);
      if (j % 2 != 0) temp *= (-1);
      res += temp * s21_determinant(&temp_arr);
      s21_remove_matrix(&temp_arr);
    }
  } else {
    res = small_determ(*A);
  }
  return res;
}

matrix_t s21_inverse_matrix(matrix_t *A) {  // Matrix inverse
  double det = s21_determinant(A);
  if (det == 0 || A->rows != A->columns) {
    matrix_t arr = s21_create_matrix(A->rows, A->columns);
    arr.matrix_type = INCORRECT_MATRIX;
    return arr;
  }
  matrix_t mult;
  if (A->rows == 1) {
    mult = s21_create_matrix(1, 1);
    mult.matrix[0][0] = pow(A->matrix[0][0], -1);
    mult.matrix_type = CORRECT_MATRIX;
  } else {
    matrix_t alg_compl = s21_calc_complements(A);
    matrix_t trans = s21_transpose(&alg_compl);
    s21_remove_matrix(&alg_compl);
    det = 1 / det;
    mult = s21_mult_number(&trans, det);
    s21_remove_matrix(&trans);
  }
  return mult;
}

matrix_t arr_minor(matrix_t A, int row_index, int col_index) {
  matrix_t arr = s21_create_matrix(A.rows - 1, A.columns - 1);
  for (int i = 0, p = 0; i < arr.rows; i++, p++) {
    if (p != row_index) {
      for (int j = 0, q = 0; j < arr.columns; j++, q++) {
        if (q != col_index)
          arr.matrix[i][j] = A.matrix[p][q];
        else
          j--;
      }
    } else {
      i--;
    }
  }
  arr.matrix_type = CORRECT_MATRIX;
  return arr;
}

double small_determ(matrix_t A) {
  double res;
  if (A.rows == 1)
    res = A.matrix[0][0];
  else
    res = A.matrix[0][0] * A.matrix[1][1] - A.matrix[0][1] * A.matrix[1][0];
  return res;
}

int is_zero(matrix_t *A) {
  int is_zero = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - 0) < 0.000001) {
        is_zero = 1;
      } else {
        is_zero = 0;
        i = A->rows;
        break;
      }
    }
  }
  if (is_zero) A->matrix_type = ZERO_MATRIX;
  return is_zero;
}

int is_identity(matrix_t *A) {
  int is_identity = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (i == j) {
        if (fabs(A->matrix[i][j] - 1) < 0.000001) {
          is_identity = 1;
        } else {
          is_identity = 0;
          i = A->rows;
          break;
        }
      } else {
        if (fabs(A->matrix[i][j] - 0) < 0.0000001) {
          is_identity = 1;
        } else {
          is_identity = 0;
          i = A->rows;
          break;
        }
      }
    }
  }
  if (is_identity) A->matrix_type = IDENTITY_MATRIX;
  return is_identity;
}

void init_from_arr(matrix_t *matrix, const double *arr) {
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->columns; j++) {
      matrix->matrix[i][j] = arr[i * matrix->columns + j];
    }
  }
}
