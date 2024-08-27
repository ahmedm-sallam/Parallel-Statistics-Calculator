# Parallel-Statistics-Calculator
 
A C-based parallel computing project that calculates statistical measures (mean, variance, and standard deviation) of an array of numbers using both MPI (Message Passing Interface) and OpenMP (Open Multi-Processing) for high-performance computing. This project demonstrates the utilization of parallel processing techniques to optimize computational tasks on multi-core and distributed systems.

## Introduction

Statistical calculations are often computationally expensive when dealing with large datasets. This project leverages parallel computing techniques to speed up the computation of the mean, variance, and standard deviation of an array of numbers. By using MPI and OpenMP, the workload is distributed across multiple processors and threads, making the computation faster and more efficient.

## Features

- **Parallel Computation with MPI**: Distributes the workload across multiple processes in a distributed computing environment.
- **Parallel Computation with OpenMP**: Utilizes multi-threading to perform computations in a shared-memory environment.
- **Efficient Handling of Large Datasets**: Capable of handling large arrays by distributing the workload.
- **Dynamic Memory Management**: Uses dynamic memory allocation to handle large datasets efficiently.

## Prerequisites

To compile and run the code, you need:

- **MPI Library**: Such as OpenMPI or MPICH.
- **OpenMP Support**: Typically included with most modern C compilers like GCC.
- **C Compiler**: GCC or any other C compiler with MPI and OpenMP support.

## Installation

**Compile the MPI Program**

- To compile the MPI version of the program, use the following command:

```
mpicc -o mpi mpi.c -lm
```

**Compile the OpenMP Program**

- To compile the OpenMP version of the program, use the following command:

```
gcc -o openMP openMP.c -fopenmp -lm
```

## Usage

1. MPI Program

- Run the MPI program with the desired number of processes:

```
mpirun -np <number_of_processes> ./mpi
```

2. OpenMP Program

- Run the OpenMP program:
```
./openMP
```

## Example

- To compute the mean, variance, and standard deviation for an array:

** Input : **
```
Enter array size: 8
Enter array elements: 2 4 4 4 5 5 7 9
```

**Output:**

```
Mean = 5.000000
Variance = 4.000000
Standard deviation = 2.000000
```