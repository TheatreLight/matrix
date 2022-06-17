#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#define SUCCESS 1
#define FAILURE 0

typedef enum {
    CORRECT_MATRIX = 0,
    INCORRECT_MATRIX = 1,
    IDENTITY_MATRIX = 2,
    ZERO_MATRIX = 3
} matrix_type_t;

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
    matrix_type_t matrix_type;
} matrix_t;

matrix_t s21_create_matrix(int rows, int columns);  // Creating matrices
void s21_remove_matrix(matrix_t *A);  // Cleaning matrices
int s21_eq_matrix(matrix_t *A, matrix_t *B);  // Comparison matrices (SUCCESS or FAILURE)
matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B);  // adding matrices
matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B);  // substracting matrices
matrix_t s21_mult_number(matrix_t *A, double number);  // Matrix multiplication by scalar
matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B);  // Multiplication of two matrices
matrix_t s21_transpose(matrix_t *A);  // Matrix transpose
matrix_t s21_calc_complements(matrix_t *A);  // Minor of matrix and matrix of algebraic complements
double s21_determinant(matrix_t *A);  // Matrix determinant
matrix_t s21_inverse_matrix(matrix_t *A);  // Matrix inverse

matrix_t arr_minor(matrix_t A, int row_index, int col_index);
double small_determ(matrix_t A);
void init_from_arr(matrix_t *matrix, const double *arr);
int is_zero(matrix_t *A);
int is_identity(matrix_t *A);

#endif  // SRC_S21_MATRIX_H_
