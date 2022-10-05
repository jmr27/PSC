#include <iostream>
#include <mpi.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char** argv)
{
	int myid, size;
	int baton = 1;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	if (myid == 0) {
		numsent = 0;
		MPI_Bcast(&x[0], numcol, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		for (i = 0; i < numprocs - 1 && i < numrow; i++) {
			MPI_Send(&A[i][0], numcol, MPI_DOUBLE, i + 1, i, MPI_COMM_WORLD);
			numsent++;
		}
		for (i = 0; i < numrow; i++) {
			MPI_Recv(&ans, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG,
				MPI_COMM_WORLD, &status);
			sender = status.MPI_SOURCE;
			row = status.MPI_TAG;
			y[row] = ans;
			if (numsent < numrow) {
				MPI_Send(&A[numsent][0], numcol, MPI_DOUBLE, sender,
					numsent, MPI_COMM_WORLD);
				numsent++;
			}
			else MPI_Send(MPI_BOTTOM, 0, MPI_DOUBLE, sender, numrow,
				MPI_COMM_WORLD);
		}
	}
	else {
		MPI_Bcast(&x[0], numcol, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		buffer = (double*)malloc(sizeof(double) * numcol);
		po = 1;
		while (myid <= numrow && po) {
			MPI_Recv(buffer, numcol, MPI_DOUBLE, 0, MPI_ANY_TAG,
				MPI_COMM_WORLD, &status);
			row = status.MPI_TAG;
			if (row < numrow) {
				ans = 0.0;
				for (j = 0; j < ncol; j++) ans += buffer[j] * x[j];
				MPI_Send(&ans, 1, MPI_DOUBLE, 0, row, MPI_COMM_WORLD);
			}
			else po = 0;
		}
		free(buffer);
	}
}