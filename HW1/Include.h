#pragma once

#include <iostream>
#include <omp.h>
#include <cmath>
#include <stdlib.h>
#include <mpi.h>
using namespace std;

typedef struct mat {
	int row;
	int col;
}Matrix;