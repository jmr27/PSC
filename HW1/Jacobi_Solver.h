#pragma once

#include "MatProbGenerator.h"

typedef struct CheckVal
{
	double** Mat;
	double* Vec;
	double* Sol;
	int iter;
	double norm;
}Pdef;
double* JacobiInitializer(Matrix M, double** A, double* b);
double L2norm(double* x, double* nx, int row);
double* UpdateVec(int row, double* x, double* nx);
double NormalL2norm(double* x, double* nx, int row);
Pdef JacobiSolver(Matrix M, double** A, double* b);
double AccTest(Matrix M, double** A, double* b, double* x);