#include "s21_matrix.h"

int is_compatable(matrix_t *A, matrix_t *B) {
  if (A == NULL || B == NULL) return FAILURE;

  if (A->columns == B->rows)
    return SUCCESS;
  else
    return FAILURE;
}

int is_same_size(matrix_t *A, matrix_t *B) {
  if (A == NULL || B == NULL) return FAILURE;

  if (A->columns == B->columns && A->rows == B->rows)
    return SUCCESS;
  else
    return FAILURE;
}

int is_square(matrix_t *A) {
  if (A == NULL) return FAILURE;

  if (A->rows == A->columns)
    return SUCCESS;
  else
    return FAILURE;
}

int getting_M(matrix_t *A, matrix_t *M, int i_miss, int j_miss) {
  if (A == NULL || M == NULL) return FAILURE;

  double val;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      val = A->matrix[i][j];

      if (i != i_miss && j != j_miss) {
        if (i > i_miss && j > j_miss)
          M->matrix[i - 1][j - 1] = val;
        else if (i > i_miss)
          M->matrix[i - 1][j] = val;
        else if (j > j_miss)
          M->matrix[i][j - 1] = val;
        else
          M->matrix[i][j] = val;
      }
    }
  }

  return SUCCESS;
}

// int validation_v1()