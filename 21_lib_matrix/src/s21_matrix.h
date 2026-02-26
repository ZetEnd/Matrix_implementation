#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define ERR_INCORRECT_MATRIX 1
#define ERR_CALCULATION 2
#define CALCULATION_ERROR 2
#define INCORRECT_MATRIX 1

#define eps 10e-6
#include <stdio.h>

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

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

// Extra function

int is_compatable(matrix_t *A, matrix_t *B);

int is_same_size(matrix_t *A, matrix_t *B);

int is_square(matrix_t *A);

int getting_M(matrix_t *A, matrix_t *M, int i_miss, int j_miss);