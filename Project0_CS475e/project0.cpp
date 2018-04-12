/* 
	Written by Adam Sunderman for CS475.
	This code was adapted from the provided code template here. http://web.engr.oregonstate.edu/~mjb/cs575/Projects/proj00.html

	Program to test the gains of parallel computing by cross-multiplying two
    large floating point arrays seeded with random values. 

    To use the program run the "project0_testscript.py" file in the code directory. This file will
    compile and run the "proj0.exe" program several times with different test values while also saving the results. 
    The results will be displayed to the console but also appended to the file "project0.results.txt" which 
    should already be inside of this code directory. The program will run iterations of the tests with 3 different 
    array sizes (1000000, 2000000, and 4000000) and 2 different numbers of threads (1 and 4). 

    There are two dependancies for this file "lib_cs475.h" and "lib_cs475.cpp" these are just files for sharing code across
    projects but must be included. 

    !! Important: If you wish to compile this code without the provided script please use the following command.

            g++ -DNUM_THREADS=[pick_threads] -DARRAY_SIZE=[pick_size] project0.cpp lib_cs475.cpp -o proj0 -lm -fopenmp   

    !! where "pick_threads" should be the number of threads to use and "pick_size" will be the array sizes. Theses values 
    !! are not defined in the .cpp file so they must be defined at compile time to avoid errors. 
*/
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "lib_cs475.h"

#define NUM_TRIES 10

float A[ARRAY_SIZE];
float B[ARRAY_SIZE];
float C[ARRAY_SIZE];

int main (int argc, char const *argv[]){

	// Test results log file
	FILE * outfile = fopen("project0.results.txt","a");

	// Verify OpenMP support.
	if(!openmp_supported()){
		fprintf (stderr, "OpenMP is not supported!\n");
		return 1;
	}

	// Fill Arrays with random numbers.
	for (int j=0; j<ARRAY_SIZE; j++){
		A[j] = randFloat();
		B[j] = randFloat();
		C[j] = 0;
	}

	// Print current date/time to console and log file.
	time_t t = time(NULL);
	char* tt = ctime(&t);
	tt[strlen(tt)-1] = 0;
	fprintf(outfile, "%s.\n", tt);
	fprintf(stderr, "%s.\n", tt);

	// Set number of threads to use for the test and check the number available on the cpu.
	// Print the values to both the console and a log file "project0.results.txt".
	omp_set_num_threads(NUM_THREADS);
	int available = omp_get_num_procs();
	if(outfile != NULL){
		fprintf(outfile, "Running cross-multiplication on arrays of length %d.\n", ARRAY_SIZE);
		fprintf(outfile, "Using %d thread(s) of %d available thread(s).\n", NUM_THREADS, available);
	}
	fprintf(stderr, "Running cross-multiplication on arrays of length %d.\n", ARRAY_SIZE);
	fprintf(stderr, "Using %d thread(s) of %d available thread(s).\n", NUM_THREADS, available);	

	// Test result values .
	double maxMegaMults = 0.;
	double sumMegaMults = 0.;
	double sumDiff = 0.;
	double peakDiff = 0.;

	// Main test loop.
	for (int i=0; i<NUM_TRIES; i++){

		// Fill Arrays with random numbers.
		for (int j=0; j<ARRAY_SIZE; j++){
			A[j] = randFloat();
			B[j] = randFloat();
			C[j] = 0;
		}

		// Start time.
		double timeIn = omp_get_wtime();

		// Multiply the arrays in parallel.
		#pragma omp parallel for 
		for (int x=0; x<ARRAY_SIZE; x++){

			C[x] = A[x] * B[x];

		}

		// End time.
		double timeOut = omp_get_wtime();
		double diff = (timeOut-timeIn);
		sumDiff += diff;
		if(diff < peakDiff || peakDiff == 0.){
			peakDiff = diff;
		}

		// Calculate the MegaMultiplications for this test run and add to the sum.
		// Update best test run MegaMults val when required.
		double MM = (double)ARRAY_SIZE/(timeOut-timeIn)/1000000.;
		sumMegaMults += MM;
		if (MM > maxMegaMults){
			maxMegaMults = MM;
		}
	}

	// Calculate the average MegaMultiplications for all test runs.
	double avgMegaMults = sumMegaMults/(double)NUM_TRIES;

	// Print test results to console and log file then exit.
	if(outfile != NULL){
		fprintf(outfile, "Peak performance = %8.2lf MegaMults/Sec.\n", maxMegaMults);
		fprintf(outfile, "Average performance = %8.2lf MegaMults/Sec.\n", avgMegaMults);
		fprintf(outfile, "Peak run time = %10.2lf microseconds.\n", 1000000 * peakDiff);
		fprintf(outfile, "Average run time = %10.2lf microseconds.\n", 1000000 * (sumDiff/NUM_TRIES));
	}
	fprintf(outfile, "\n");
	fclose(outfile);
	fprintf(stderr, "Peak performance = %8.2lf MegaMults/Sec.\n", maxMegaMults);
	fprintf(stderr, "Average performance = %8.2lf MegaMults/Sec.\n", avgMegaMults);
	fprintf(stderr, "Peak run time = %10.2lf microseconds.\n", 1000000 * peakDiff);
	fprintf(stderr, "Average run time = %10.2lf microseconds.\n", 1000000 * (sumDiff/NUM_TRIES));
	printf("\n");
	/*
	printf("Press Enter To Continue.\n");
	char e;
	scanf("%c", &e);
	*/ 
	return 0;
}