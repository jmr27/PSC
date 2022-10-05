#include "Jacobi_Solver.h"


double* JacobiInitializer(Matrix M, double** A, double* b)
{
	int row = M.row;
	int col = M.col;
	double* x = new double[row];
	for (int i = 0; i < row; i++)
	{
		x[i] = 0;
	}

	return x;
	delete[] x;
}

double L2norm(double* x, double* nx, int row)
{
	double sum = 0;
	double norm;
	for (int i = 0; i < row; i++)
	{
		sum += pow(nx[i] - x[i], 2);
	}
	norm = sqrt(sum);
	return norm;
}

double NormalL2norm(double* x, double* nx, int row)
{
	double* z = new double[row];
	for (int i = 0; i < row; i++)
	{
		z[i] = 0;
	}
	double norm;
	norm = L2norm(x, nx, row) / L2norm(z, x, row);
	return norm;
}

double* UpdateVec(int row, double* x, double* nx)
{
	for (int i = 0; i < row; i++)
	{
		x[i] = nx[i];
	}
	return x;
}

Pdef JacobiSolver(Matrix M, double** A, double* b)
{
	Pdef JS;
	double* x = JacobiInitializer(M, A, b);
	int row = M.row;
	double* nx = new double[row];
	int k = 0;
	double norm = 1.0;
	double tol = 1e-3;
	double sum;
	int col = M.col;
	double start, end,s,e;
	cout << "Solver Initialization" << endl;
	cout << "Solver Convergence Tolerance : " << tol << endl;
	start = omp_get_wtime();
	do
	{
		s = omp_get_wtime();
		{
			for (int i = 0; i < row; i++)
			{
				sum = 0.0;
				for (int j = 0; j < col; j++)
				{
					if (i != j)
					{
						sum += A[i][j] * x[j];
					}
				}
				nx[i] = (b[i] - sum) / A[i][i];
			}
			norm = NormalL2norm(x, nx, row);
			x = UpdateVec(row, x, nx);
			k += 1;
		}
		e = omp_get_wtime();
		if (norm < tol)
		{
			cout << "Time per Iter : " << e - s << endl;
		}
	} while (norm>tol);
	
	cout << "End of Iteration" << endl;
	end = omp_get_wtime();
	cout << "Serial Running time : " << end - start << endl;;
	JS.iter = k;
	JS.Mat = A;
	JS.norm = norm;
	JS.Vec = b;
	JS.Sol = x;
	return JS;
	delete[] nx;
	delete[] x;
}

double AccTest(Matrix M, double** A, double* b, double* x)
{
	int row = M.row;
	double* nb = new double[row];
	double* zero = new double[row];
	double sum, norm;
	for (int i = 0; i < row; i++)
	{
		sum = 0;
		for (int j = 0; j < row; j++)
		{
			sum += A[i][j] * x[j];
		}
		nb[i] = sum;
		zero[i] = 0;
	}
	norm = L2norm(b, nb, row) / L2norm(zero, b, row);
	return norm;
	delete[] nb;
	delete[] zero;
}

