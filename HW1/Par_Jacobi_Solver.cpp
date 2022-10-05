#include "Par_Jacobi_Solver.h"

Pdef Par_JacobiSolver1(Matrix M, double** A, double* b)
{
	omp_set_nested(1);
	Pdef JS;
	double* x = JacobiInitializer(M, A, b);
	int row = M.row;
	double* nx = new double[row];
	double sum = 0;
	double sum1 = 0;
	double sum2 = 0;
	int k = 0;
	double norm = 1.0;
	double norm1 = 0;
	double norm2 = 0;
	double tol = 1e-3;
	int col = M.col;
	double start, end,s,e;
	int th,i,j;
	//double start, end;
	cout << "Solver Initialization" << endl;
	cout << "Solver Convergence Tolerance : " << tol << endl;
	start = omp_get_wtime();
	do {
		s = omp_get_wtime();
		sum1 = 0;
		sum2 = 0;
		for (int i = 0; i < row; i++)
		{
			sum = 0;
			for (int j = 0; j < col; j++)
			{
				if (i != j)
				{
					sum += A[i][j] * x[j];
				}
			}
			nx[i] = (b[i] - sum) / A[i][i];
		}


#pragma omp parallel for private(i,norm) reduction(+:sum1,sum2)
		for (int i = 0; i < row; i++)
		{
			sum1 += pow(nx[i] - x[i], 2);
			sum2 += pow(x[i], 2);
			x[i] = nx[i];
		}
		norm1 = sqrt(sum1);
		norm2 = sqrt(sum2);
		norm = norm1 / norm2;
		k++;
		e = omp_get_wtime();
		if (k % 1000 == 0)
		{
			cout << "Number of Iteration : " << k << endl;
		}
		if (norm < tol)
		{
			cout << "Time per Iter Par : " << e - s << endl;
		}
	} while (norm > tol);
	end = omp_get_wtime();
	cout << "Parallel running time : " << end - start << endl;;
	cout << "End of Iteration" << endl;
	JS.iter = k;
	JS.Mat = A;
	JS.norm = norm;
	JS.Vec = b;
	JS.Sol = x;
	return JS;
	delete[] nx;
	delete[] x;
}

Pdef Par_JacobiSolver2(Matrix M, double** A, double* b)
{
	Pdef JS;
	double* x = JacobiInitializer(M, A, b);
	int row = M.row;
	double* nx = new double[row];
	double* sum = new double[row]();
	double sum1 = 0;
	double sum2 = 0;
	double tmp = 0;
	int iter = 0;
	double norm = 0;
	double norm1 = 0;
	double norm2 = 0;
	double tol = 1e-3;
	int col = M.col;
	double start, end, s, e;
	int i, j, k;
	//double start, end;
	cout << "Solver Initialization" << endl;
	cout << "Solver Convergence Tolerance : " << tol << endl;
	start = omp_get_wtime();
	do {
		s = omp_get_wtime();
		sum1 = 0;
		sum2 = 0;
		// Jacobi Calculation
		//MatrixViewer(A, M);
		//VectorViewer(b, M);

		for (int i = 0; i < row; i++)
		{
			tmp = 0;
#pragma omp parallel
			{
#pragma omp for nowait private(j) reduction(+:tmp)
				for (int j = 0; j < col; j++)
				{
					if (i == j)
					{
						tmp += 0;
					}
					else
					{
						tmp += A[i][j] * x[j];
					}
				}
			}
			sum[i] = tmp;
		}

#pragma omp parallel 
		{
#pragma omp for nowait private(i,norm) reduction(+:sum1,sum2)
			for (int i = 0; i < row; i++)
			{
				nx[i] = (b[i] - sum[i]) / A[i][i];
				sum1 += pow(nx[i] - x[i], 2);
				sum2 += pow(x[i], 2);
				x[i] = nx[i];
			}
		}
		norm1 = sqrt(sum1);
		norm2 = sqrt(sum2);
		norm = norm1 / norm2;
		iter ++;
		if (iter % 1000 == 0)
		{
			cout << "Number of Iteration : " << iter << endl;
		}
		e = omp_get_wtime();
		if (norm < tol)
		{
			cout << "Time per Iter : " << e - s << endl;
		}
	} while (norm > tol);
	end = omp_get_wtime();
	cout << "Parallel running time : " << end - start << endl;;
	cout << "End of Iteration" << endl;
	JS.iter = iter;
	JS.Mat = A;
	JS.norm = norm;
	JS.Vec = b;
	JS.Sol = x;
	return JS;
	delete[] nx;
	delete[] x;
}

Pdef Par_JacobiSolver_hw(Matrix M, double** A, double* b)
{
	Pdef JS;
	double* x = JacobiInitializer(M, A, b);
	int row = M.row;
	double* nx = new double[row];
	double* sum = new double[row]();
	double sum1 = 0;
	double sum2 = 0;
	double tmp = 0;
	int iter = 0;
	double norm = 1.0;
	double norm1 = 0;
	double norm2 = 0;
	double tol = 1e-3;
	int col = M.col;
	double start, end, s, e;
	int  i, j, k;
	//double start, end;
	cout << "Solver Initialization" << endl;
	cout << "Solver Convergence Tolerance : " << tol << endl;
	start = omp_get_wtime();
	do {
		s = omp_get_wtime();
		sum1 = 0;
		sum2 = 0;
		// Jacobi Calculation
		//MatrixViewer(A, M);
		//VectorViewer(b, M);
#pragma omp parallel
		{
#pragma omp for nowait private(j,tmp) reduction(+:sum1,sum2)
			for (int i = 0; i < row; i++)
			{
				tmp = 0;
				for (int j = 0; j < col; j++)
				{
					if (i == j)
					{
						tmp += 0;
					}
					else
					{
						tmp += A[i][j] * x[j];
					}
				}
				sum[i] = tmp;
				nx[i] = (b[i] - sum[i]) / A[i][i];
				sum1 += pow(nx[i] - x[i], 2);
				sum2 += pow(x[i], 2);
				x[i] = nx[i];
			}
		}
		norm1 = sqrt(sum1);
		norm2 = sqrt(sum2);
		norm = norm1 / norm2;
		iter++;
		e = omp_get_wtime();
		if (iter % 1000 == 0)
		{
			cout << "Number of Iteration : " << iter << endl;
		}
		if (norm < tol)
		{
			cout << "Time per Iter Par : " << e - s << endl;
		}
	} while (norm > tol);
	end = omp_get_wtime();
	cout << "Parallel running time : " << end - start << endl;;
	cout << "End of Iteration" << endl;
	JS.iter = iter;
	JS.Mat = A;
	JS.norm = norm;
	JS.Vec = b;
	JS.Sol = x;
	return JS;
	delete[] nx;
	delete[] x;
}