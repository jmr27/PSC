#include "MatProbGenerator.h"

Matrix func1(int m, int n, int square)
{
	Matrix M;

	if (square == 1)
	{
		M.row = m;
		M.col = m;
	}
	else
	{
		M.row = m;
		M.col = n;
	}
	return M;
}

Matrix MatrixIO()
{
	static Matrix M;
	int m, n, square;
	square = 1;
	/*std::cout << "Is Intended Matrix Square Matrix? Type 1 for yes otherwise it will be no" << endl;
	std::cin >> square;
	if (square == 1) {
		cout << "Size of square Matrix: " << endl;
		cin >> m;
		n = m;
	}
	else {
		cout << "Matrix row size :" << endl;
		cin >> m;
		cout << "Matrix column size :" << endl;
		cin >> n;
	}*/
	cout << "Size of Matrix : " << endl;
	cin >> m;
	n = m;
	M = func1(m, n, square);

	cout << "Matrix row " << M.row << ", Matrix column " << M.col << endl;

	return M;

}

double** Par_CDDMatrix_generator(Matrix M)
{
	double sum, rannum, tmp;
	double** arr;
	int m = M.row;
	int n = M.col;
	int i, j;
	double start, end;
	arr = new double* [m]();
	srand(time(NULL));
	start = omp_get_wtime();
#pragma omp parallel
	{
#pragma omp for
		for (int i = 0; i < m; i++)
		{
			arr[i] = new double[n]();
		}
#pragma omp for private(sum,j) 
		for (int i = 0; i < m; i++)
		{
			sum = 0;
			for (int j = 0; j < n; j++)
			{
				if (i != j)
				{
					arr[j][i] = static_cast <double> (rand())/**pow(-1,rand())*/;
					sum += abs(arr[j][i]);
				}
			}
			rannum = static_cast <double> (rand());
			arr[i][i] = (sum + rannum)/**pow(-1,rand())*/;
		}
	}
	end = omp_get_wtime();
	cout << "Time Ellapsed for Matrix Generation Par : " << end - start << endl;
	return (double**)arr;
	freedynalloc(arr, M);
}

double** Par_pos_neg_CDDMatrix_generator(Matrix M)
{
	double sum, rannum, tmp;
	double** arr;
	int m = M.row;
	int n = M.col;
	int i, j;
	double start, end;
	arr = new double* [m]();
	srand(time(NULL));
	start = omp_get_wtime();
#pragma omp parallel
	{
#pragma omp for
		for (int i = 0; i < m; i++)
		{
			arr[i] = new double[n]();
		}
#pragma omp for private(sum,j) 
		for (int i = 0; i < m; i++)
		{
			sum = 0;
			for (int j = 0; j < n; j++)
			{
				if (i != j)
				{
					arr[j][i] = static_cast <double> (rand())*pow(-1,rand());
					sum += abs(arr[j][i]);
				}
			}
			rannum = static_cast <double> (rand());
			arr[i][i] = (sum + rannum)*pow(-1,rand());
		}
	}
	end = omp_get_wtime();
	cout << "Time Ellapsed for Matrix Generation Par : " << end - start << endl;
	return (double**)arr;
	freedynalloc(arr, M);
}



double** CDDMatrix_generator(Matrix M)
{
	double sum, rannum, tmp;
	double** arr;
	int m = M.row;
	int n = M.col;
	int i, j;
	double start, end;
	arr = new double* [m]();
	srand(time(NULL));
	start = omp_get_wtime();
	for (int i = 0; i < m; i++)
	{
		arr[i] = new double[n]();
	}
	for (int i = 0; i < m; i++)
	{
		sum = 0;
		for (int j = 0; j < n; j++)
		{
			if (i != j)
			{
				arr[j][i] = static_cast <double> (rand()) /** pow(-1, rand())*/;
				sum += abs(arr[j][i]);
			}
		}
		rannum = static_cast <double> (rand());
		arr[i][i] = (sum + rannum) /** pow(-1, rand())*/;
	}
	end = omp_get_wtime();
	cout << "Time Ellapsed for Matrix Generation Ser : " << end - start << endl;
	return (double**)arr;
	freedynalloc(arr, M);
}

double** pos_neg_CDDMatrix_generator(Matrix M)
{
	double sum, rannum, tmp;
	double** arr;
	int m = M.row;
	int n = M.col;
	int i, j;
	double start, end;
	arr = new double* [m]();
	srand(time(NULL));
	start = omp_get_wtime();
	for (int i = 0; i < m; i++)
	{
		arr[i] = new double[n]();
	}
	for (int i = 0; i < m; i++)
	{
		sum = 0;
		for (int j = 0; j < n; j++)
		{
			if (i != j)
			{
				arr[j][i] = static_cast <double> (rand()) * pow(-1, rand());
				sum += abs(arr[j][i]);
			}
		}
		rannum = static_cast <double> (rand());
		arr[i][i] = (sum + rannum) * pow(-1, rand());
	}
	end = omp_get_wtime();
	cout << "Time Ellapsed for Matrix Generation Ser : " << end - start << endl;
	return (double**)arr;
	freedynalloc(arr, M);
}


double* Par_RandVecGenerator(Matrix M)
{
	int m = M.row;
	double* vec = new double[m];
	double tmp,start,end;
	start = omp_get_wtime();
#pragma omp parallel
	{
		srand(time(NULL));
#pragma omp for nowait private(tmp)
		for (int i = 0; i < m; i++) {
			tmp = static_cast <double> (rand())/* * pow(-1, rand())*/;
			vec[i] = tmp;
		}
	}
	end = omp_get_wtime();
	cout << "Time Ellapsed for Vector Generation Par : " << end - start << endl;
	return (double*)vec;
	delete[] vec;
}

double* Par_pos_neg_RandVecGenerator(Matrix M)
{
	int m = M.row;
	double* vec = new double[m];
	double tmp, start, end;
	start = omp_get_wtime();
#pragma omp parallel
	{
		srand(time(NULL));
#pragma omp for nowait private(tmp)
		for (int i = 0; i < m; i++) {
			tmp = static_cast <double> (rand()) * pow(-1, rand());
			vec[i] = tmp;
		}
	}
	end = omp_get_wtime();
	cout << "Time Ellapsed for Vector Generation Par : " << end - start << endl;
	return (double*)vec;
	delete[] vec;
}

double* RandVecGenerator(Matrix M)
{
	int m = M.row;
	double* vec = new double[m];
	double tmp, start,end;
	start = omp_get_wtime();
	srand(time(NULL));
	for (int i = 0; i < m; i++) {
		tmp = static_cast <double> (rand())/* * pow(-1, rand())*/;
		vec[i] = tmp;
	}
	end = omp_get_wtime();
	cout << "Time Ellapsed for Vector Generation Ser : " << end - start << endl;
	return (double*)vec;
	delete[] vec;
}

double* pos_neg_RandVecGenerator(Matrix M)
{
	int m = M.row;
	double* vec = new double[m];
	double tmp, start, end;
	start = omp_get_wtime();
	srand(time(NULL));
	for (int i = 0; i < m; i++) {
		tmp = static_cast <double> (rand()) * pow(-1, rand());
		vec[i] = tmp;
	}
	end = omp_get_wtime();
	cout << "Time Ellapsed for Vector Generation Ser : " << end - start << endl;
	return (double*)vec;
	delete[] vec;
}


int freedynalloc(double** arr, Matrix M)
{
	for (int i = 0; i < M.row; i++)
	{
		delete(arr[i]);
	}
	delete(arr);
	return 0;
}

int MatrixViewer(double** arr, Matrix M)
{
	for (int i = 0; i < M.row; i++)
	{
		for (int j = 0; j < M.col; j++)
		{
			cout << arr[i][j] << "  ";
		}
		cout << endl;
	}
	return 0;
}

int VectorViewer(double* vec, Matrix M)
{
	for (int i = 0; i < M.row; i++)
	{
		cout << vec[i] << endl;
	}
	return 0;
}
