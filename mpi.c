#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <math.h>


int main(int argc , char * argv[])
{
	int my_rank;		/* rank of process	*/
	int p;			/* number of process	*/
	int source;		/* rank of sender	*/
	int dest;		/* rank of reciever	*/
	int tag = 0;		/* tag for messages	*/
	MPI_Status status;	/* return status for 	*/
				/* recieve		*/
	int arrSize;
	int portion;
	int remainder;
    double mean;
    double tempArr[1000000]; // can be replaced with dynamic allocation to achieve reliability.
    double start;
	/* Start up MPI */
	MPI_Init( &argc , &argv );

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);


	if(my_rank == 0){        
		printf("Enter array size:");
		scanf("%d",&arrSize);
        double arr[arrSize];
		printf("enter array elements:");
        for (int i = 0 ; i < arrSize ; i++){
            scanf("%lf",&arr[i]);
            tempArr[i] = arr[i];
        }
        
		portion = (arrSize)/(p-1);
        remainder = (arrSize)%(p-1);
        for (int i = 0 ; i < arrSize ; i++){
            mean+=arr[i];
        }
        mean = mean/arrSize;

        MPI_Bcast(&portion, 1, MPI_INT,0, MPI_COMM_WORLD);
		MPI_Bcast(&mean, 1, MPI_DOUBLE,0, MPI_COMM_WORLD);
	}

    // recieving portion and mean for each subprocess.
    start = MPI_Wtime();

    MPI_Bcast(&portion, 1, MPI_INT,0, MPI_COMM_WORLD);
	MPI_Bcast(&mean, 1, MPI_DOUBLE,0, MPI_COMM_WORLD);

    double subArray[portion];
    MPI_Scatter(&tempArr,portion,MPI_DOUBLE,&subArray,portion,MPI_DOUBLE,0,MPI_COMM_WORLD);
    //squared difference  part
    for (int i = 0 ; i < portion ; i++){
        subArray[i] = pow(subArray[i] - mean , 2);
    }
    MPI_Gather(&subArray,portion,MPI_DOUBLE,&tempArr,portion,MPI_DOUBLE,0,MPI_COMM_WORLD);
    double finish  = MPI_Wtime();

    if (my_rank == 0){

        // handling  remainder 
        if (remainder != 0){
            for (int i = portion*p ; i < arrSize ; i++){
                tempArr[i] = pow(tempArr[i] - mean , 2);
            }
        }
        // variance part
        double variance;
        for (int i = 0 ; i < arrSize ; i++){
            variance += tempArr[i];
        }
        
        variance = variance / arrSize;
        double time = finish - start ;

        printf("\nTime elapsed = %lf\n\n" , time);
        printf("Mean = %f\n" , mean);
        printf("Variance = %f\n" , variance);
        variance = pow(variance , 0.5);
        printf("Standard deviation = %f\n" , variance);
    }

	/* shutdown MPI */
	MPI_Finalize();
	return 0;
}


/*

8
2 4 4 4 5 5 7 9

7
4 5 6 6 7 9 12



*/
