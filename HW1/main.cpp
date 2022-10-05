#include "Par_Jacobi_Solver.h"

int main(int argc, char** argv)
{
	Matrix M = MatrixIO();
	double** A;
	double* x;
	double** As;
	double* bs;
	int row = M.row;
	double* a = new double[row];
	/*double norm, parnorm;
	double PSerr;
	Pdef PJS, JS;*/
	A = Par_CDDMatrix_generator(M);
	x = Par_RandVecGenerator(M);
	/*As = CDDMatrix_generator(M);
	bs = RandVecGenerator(M);
	PJS = Par_JacobiSolver_hw(M, A, b);
	parnorm = AccTest(M, A, b, PJS.Sol);
	cout << "Number of Par Iteration : " << PJS.iter << endl;
	cout << fixed;
	cout.precision(15);
	cout << "Error of Par Solution : " << PJS.norm << endl;
	cout << "Error of b derived from Parallel solution : " << parnorm << endl;
	JS = JacobiSolver(M, A, b);
	norm = AccTest(M, A, b, JS.Sol);
	cout << "Number of Ser Iteration : " << JS.iter << endl;
	cout << fixed;
	cout.precision(15);
	cout << "Error of Ser Solution : " << JS.norm << endl;
	cout << "Error of b derived from Serial solution : " << norm << endl;
	cout.unsetf(ios::fixed);
	PSerr = NormalL2norm(JS.Sol, PJS.Sol, row);
	cout << "Error between Par and Ser : " << PSerr << endl;*/

	//MPI_MAT_VEC_EXAMPLE

	int myid, size;
	int baton = 1;
	int numsent;
	int numprocs = 8;
	int numrow = M.row;
	int numcol = M.col;
	double ans;
	double* y = new double[numcol];
	int i,po,j;
	int sender;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	if (myid == 0) {
		numsent = 0;
		MPI_Bcast(&x, numcol, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		for (i = 0; (i < numprocs - 1) && (i < numrow); i++) {
			MPI_Send(&A[i], numcol, MPI_DOUBLE, i + 1, i, MPI_COMM_WORLD);
			numsent++;
		}
		for (i = 0; i < numrow; i++) {
			MPI_Recv(&ans, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG,MPI_COMM_WORLD, &status);
			sender = status.MPI_SOURCE;
			row = status.MPI_TAG;
			y[row] = ans;
			if (numsent < numrow) {
				MPI_Send(&A[numsent], numcol, MPI_DOUBLE, sender,numsent, MPI_COMM_WORLD);
				numsent++;
			}
			else MPI_Send(MPI_BOTTOM, 0, MPI_DOUBLE, sender, numrow,MPI_COMM_WORLD);
		}
	}
	else {
		MPI_Bcast(&x, numcol, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		
		double* buffer = new double[numcol];
		po = 1;
		while (myid <= numrow && po) {
			MPI_Recv(buffer, numcol, MPI_DOUBLE, 0, MPI_ANY_TAG,MPI_COMM_WORLD, &status);
			row = status.MPI_TAG;
			if (row < numrow) {
				ans = 0.0;
				for (j = 0; j < numcol; j++) ans += buffer[j] * x[j];
				MPI_Send(&ans, 1, MPI_DOUBLE, 0, row, MPI_COMM_WORLD);
			}
			else po = 0;
		}
		delete buffer;
		delete y;
	}
	MPI_Finalize();


	
	return 0;
}