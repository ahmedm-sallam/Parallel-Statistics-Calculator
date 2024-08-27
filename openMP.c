// Reference used : https://curc.readthedocs.io/en/latest/programming/OpenMP-C.html


#include <stdio.h>
#include <math.h>
#include <omp.h>

int main()
{
    int arrSize;
    
    printf("Enter array size:");
    scanf("%d", &arrSize);
    
    double arr[arrSize];
    
    for (int i = 0; i < arrSize; i++)
    {
        scanf("%lf", &arr[i]);
    }
    
    int numProcesses = omp_get_max_threads();
    int portion = arrSize / numProcesses;
    
    int remainder = arrSize % numProcesses ;

    double subMean = 0.0;
    double totalSum = 0.0;
    
    #pragma omp parallel shared(arr, portion) private(subMean)
    {
        int threadNum = omp_get_thread_num();
        

        double sum = 0.0;
        printf("portion = %d \n" , portion);


        for (int i = threadNum * portion; i <  (threadNum * portion) + portion ; i++)
        {
            sum += arr[i];

        }
        if ( remainder != 0 && threadNum == 0 ) {
            for (int i = portion * omp_get_max_threads() ; i < (portion * omp_get_max_threads()) + remainder ; i++){
                sum += arr[i];
            }

        }

        #pragma omp critical
        {
            totalSum += sum;
        }
    }
    
    double mean = totalSum / arrSize;
    
    printf("Mean = %f\n", mean);
    
    double variance = 0.0;
    double tempArr[arrSize];
    
    #pragma omp parallel for reduction(+:variance)
    for (int i = 0; i < arrSize; i++)
    {
        tempArr[i] = pow(arr[i] - mean, 2);
        variance += tempArr[i];
    }
    
    variance = variance / arrSize;
    printf("Variance = %f\n", variance);
    
    double standardDeviation = sqrt(variance);
    printf("Standard deviation = %f\n", standardDeviation);
    
    return 0;
}


/*

8
2 4 4 4 5 5 7 9

7
4 5 6 6 7 9 12



*/
