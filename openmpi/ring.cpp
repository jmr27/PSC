#include <iostream>
#include <mpi.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char** argv)
{
	int rank, size;
	int baton = 1;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;
	if (rank == 0)
	{
		MPI_Send(&baton, 1, MPI_INT, 1, 999, MPI_COMM_WORLD);
		MPI_Recv(&baton, 1, MPI_INT, size - 1, 999, MPI_COMM_WORLD,&status);
		cout << "Baton " << baton << ":Process " << size - 1 << " --> Process 0" << endl;
	}
	else
	{
		MPI_Recv(&baton, 1, MPI_INT, rank - 1, 999, MPI_COMM_WORLD, &status);
		/*cout << "Baton " << baton << ":Process " << rank-1 << " --> Process 0" << rank<<endl;*/
		MPI_Send(&baton, 1, MPI_INT, (rank + 1) % size, 999, MPI_COMM_WORLD);
	}
	MPI_Finalize();
}