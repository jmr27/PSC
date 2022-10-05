#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char** argv)
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		cout << "Hello, world! : from " << size << " processes" << endl;
		cout << "I am process" << rank << endl;
	}
	else
		cout << "I am process" << rank << endl;
	MPI_Finalize();
}