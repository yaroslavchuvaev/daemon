#include <stdio.h>
#include <mpi.h>

int main (int argc, char* argv[])
{
    int rank, size;
 
    MPI_Init (&argc, &argv);
    

    while(1)
    	system("php build/test/test.php");printf("\n");
 
 	MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
 	
    return 0;
}