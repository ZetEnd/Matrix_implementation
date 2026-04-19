#include "s21_matrix.h"

#include <math.h>
#include <stdlib.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0 || result == NULL) return ERR_INCORRECT_MATRIX;

  /*if(result->matrix != NULL)
  s21_remove_matrix(result);*/

  result->columns = columns;
  result->rows = rows;
  result->matrix = NULL;

  result->matrix = (double **)calloc(rows, sizeof(double *));
  if (result->matrix == NULL) return ERR_INCORRECT_MATRIX;

  double *varr = calloc(rows * columns, sizeof(double));
  if (varr == NULL) {
    free(result->matrix);
    result->matrix = NULL;
    return ERR_INCORRECT_MATRIX;
  }

  for (int i = 0; i < rows; i++) {
    result->matrix[i] = varr + i * columns;
  }

  return 0;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->matrix != NULL) {
      if (A->matrix[0] != NULL) free(A->matrix[0]);

      free(A->matrix);
    }

    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL) return ERR_INCORRECT_MATRIX;

  if (A->matrix == NULL || B->matrix == NULL) return ERR_INCORRECT_MATRIX;

  if (is_same_size(A, B) == FAILURE) return ERR_CALCULATION;

  // if (result->matrix == NULL)
  if (s21_create_matrix(A->rows, A->columns, result) != OK)
    return ERR_INCORRECT_MATRIX;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }

  return OK;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (A == NULL || B == NULL) return FAILURE;

  if (A->matrix == NULL || B->matrix == NULL) return FAILURE;

  if (is_same_size(A, B) == FAILURE) return FAILURE;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > eps) return FAILURE;
    }
  }

  return SUCCESS;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL) return ERR_INCORRECT_MATRIX;

  if (A->matrix == NULL || B->matrix == NULL) return ERR_INCORRECT_MATRIX;

  if (is_same_size(A, B) == FAILURE) return ERR_CALCULATION;

  // if (result->matrix == NULL)
  if (s21_create_matrix(A->rows, A->columns, result) != OK)
    return ERR_INCORRECT_MATRIX;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }

  return OK;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (A == NULL || result == NULL) return ERR_INCORRECT_MATRIX;

  if (A->matrix == NULL) return ERR_INCORRECT_MATRIX;

  // if (result->matrix == NULL)
  if (s21_create_matrix(A->rows, A->columns, result) != OK)
    return ERR_INCORRECT_MATRIX;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = number * A->matrix[i][j];
    }
  }

  return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL) return ERR_INCORRECT_MATRIX;

  if (A->matrix == NULL || B->matrix == NULL) return ERR_INCORRECT_MATRIX;

  if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0)
    return ERR_INCORRECT_MATRIX;

  if (is_compatable(A, B) == FAILURE) return ERR_CALCULATION;

  // if (result->matrix == NULL)
  if (s21_create_matrix(A->rows, B->columns, result) != OK)
    return ERR_INCORRECT_MATRIX;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }

  return OK;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL) return ERR_INCORRECT_MATRIX;

  if (A->matrix == NULL) return ERR_INCORRECT_MATRIX;

  // if (result->matrix == NULL)
  if (s21_create_matrix(A->columns, A->rows, result) != OK)
    return ERR_INCORRECT_MATRIX;

  for (int i = 0; i < A->columns; i++) {
    for (int j = 0; j < A->rows; j++) {
      result->matrix[i][j] = A->matrix[j][i];
    }
  }

  return OK;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL) return ERR_INCORRECT_MATRIX;

  if (A->matrix == NULL) return ERR_INCORRECT_MATRIX;

  if (A->rows < 1 || A->columns < 1) return ERR_INCORRECT_MATRIX;

  if (is_square(A) == FAILURE) return ERR_CALCULATION;

  // if (result->matrix == NULL)
  if (s21_create_matrix(A->rows, A->rows, result) != OK)
    return ERR_INCORRECT_MATRIX;

  if (A->rows == 1) {
    result->matrix[0][0] = 1;
  } else {
    double det_M;
    matrix_t M = {0};

    if (s21_create_matrix(A->rows - 1, A->rows - 1, &M) != OK) {
      // s21_remove_matrix(&M);
      s21_remove_matrix(result);
      return ERR_INCORRECT_MATRIX;
    }

    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (getting_M(A, &M, i, j) != SUCCESS) {
          s21_remove_matrix(&M);
          s21_remove_matrix(result);
          return ERR_CALCULATION;
        }

        if (s21_determinant(&M, &det_M) != OK) {
          s21_remove_matrix(&M);
          s21_remove_matrix(result);
          return ERR_INCORRECT_MATRIX;
        }

        result->matrix[i][j] = (((i + j) % 2 == 0) ? 1 : -1) * det_M;
      }
    }

    s21_remove_matrix(&M);
  }

  return OK;
}

int s21_determinant(matrix_t *A, double *result) {
  if (A == NULL || result == NULL) return ERR_INCORRECT_MATRIX;

  if (A->matrix == NULL) return ERR_INCORRECT_MATRIX;

  if (A->rows < 1 || A->columns < 1) return ERR_INCORRECT_MATRIX;

  if (is_square(A) == FAILURE) return ERR_CALCULATION;

  *result = 0;

  if (A->rows == 1 && A->columns == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2 && A->columns == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - (A->matrix[0][1] * A->matrix[1][0]);
  } else {
    matrix_t M = {0};

    if (s21_calc_complements(A, &M) != OK) {
      s21_remove_matrix(&M);
      return ERR_CALCULATION;
    }

    for (int i = 0; i < A->rows; i++) {
      *result += A->matrix[i][0] * M.matrix[i][0];
    }

    s21_remove_matrix(&M);
  }

  return OK;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL) return ERR_INCORRECT_MATRIX;

  if (A->matrix == NULL) return ERR_INCORRECT_MATRIX;

  if (is_square(A) == FAILURE) return ERR_CALCULATION;

  matrix_t M = {0}, M_t = {0};

  double det_A;

  if (s21_determinant(A, &det_A) != OK) return ERR_CALCULATION;

  if (det_A == 0) return ERR_CALCULATION;

  if (s21_calc_complements(A, &M) != OK) return ERR_CALCULATION;

  if (s21_transpose(&M, &M_t) != OK) {
    s21_remove_matrix(&M);
    return ERR_CALCULATION;
  }

  /*if (s21_create_matrix(A->rows, A->columns, result) != OK) {
    s21_remove_matrix(&M);
    s21_remove_matrix(&M_t);
    return ERR_INCORRECT_MATRIX;
  }*/

  if (s21_mult_number(&M_t, (double)(1.0 / det_A), result) != OK) {
    s21_remove_matrix(&M);
    s21_remove_matrix(&M_t);
    s21_remove_matrix(result);
    return ERR_CALCULATION;
  }

  s21_remove_matrix(&M);
  s21_remove_matrix(&M_t);
  // s21_remove_matrix(result);

  return OK;
}
