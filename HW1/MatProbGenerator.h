#pragma once

#include "Include.h"

Matrix func1(int m, int n, int square);
Matrix MatrixIO();
double** Par_CDDMatrix_generator(Matrix M);
double** Par_pos_neg_CDDMatrix_generator(Matrix M);
double** CDDMatrix_generator(Matrix M);
double** pos_neg_CDDMatrix_generator(Matrix M);
double* Par_RandVecGenerator(Matrix M);
double* Par_pos_neg_RandVecGenerator(Matrix M);
double* RandVecGenerator(Matrix M);
double* pos_neg_RandVecGenerator(Matrix M);
int freedynalloc(double** arr, Matrix M);
int MatrixViewer(double** arr, Matrix M);
int VectorViewer(double* vec, Matrix M);