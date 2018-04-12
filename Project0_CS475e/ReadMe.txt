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