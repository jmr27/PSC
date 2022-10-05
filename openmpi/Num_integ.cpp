#include <iostream>
#include <stdlib.h>
#include <mpi.h>
using namespace std;

int main(int argc, char** argv)
{
	MPI_Init(&argc, &argv);
	int numprocs, myid;
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	int n, i;
	if (myid == 0)
	{
		cout << "Enter the number of interval: " << endl;
		cin >> n;
	}
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	double dx,x;
	dx = 1.0 / (double)n;
	double s = 0;
	double total = 0;
	double answer;
	for (i = myid + 1; i < n; i += numprocs)
	{
		x = (double)i * dx;
		s += 4 / (1 + x*x);
	}
	MPI_Reduce(&s, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if (myid == 0)
	{
		total += (4 + 2) / 2;
		answer = total * dx;
		cout << "Answer = " << answer << endl;
	}
	MPI_Finalize();
}