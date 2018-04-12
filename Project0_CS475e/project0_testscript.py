#!/usr/bin/python
import os

speedup = [0,0,0];
t1times = [0,0,0];
t4times = [0,0,0];
parFrac = [0,0,0];
resStrings = [0,0,0];

for thread in [1,4]:
    for size in [1000000,2000000,4000000]:
    	ccmd = "g++ -DNUM_THREADS=%d -DARRAY_SIZE=%d project0.cpp lib_cs475.cpp -o proj0 -lm -fopenmp" %(thread,size);
    	rcmd = "./proj0";
    	os.system(ccmd);
    	os.system(rcmd);
        
        #Read the results file and save times for this run.
    	f = open("project0.results.txt","r");
    	line = f.readlines()[-3];
    	t = line.split("=")[1].split("microseconds")[0];
    	ft = float(t);
    	f.close();
    	if thread == 1:
    		if size == 1000000:
    			t1times[0] = ft;
    		elif size == 2000000:
    			t1times[1] = ft;
    		else:
    			t1times[2] = ft;
    	else:
    		if size == 1000000:
    			t4times[0] = ft;
    		elif size == 2000000:
    			t4times[1] = ft;
    		else:
    			t4times[2] = ft;

# Calculate the speedup factore.
for x in [0,1,2]:
	speedup[x] = t1times[x]/t4times[x];
	parFrac[x] = (4./3.)*(1.-(1./speedup[x]));
	if x == 0:
		resStrings[x] = "4 thread to 1 speedup factor for arraysize 1000000 = %f.\nWith parallel fraction = %f.\n" %(speedup[x],parFrac[x]);
	elif x == 1:
		resStrings[x] = "4 thread to 1 speedup factor for arraysize 2000000 = %f.\nWith Parallel fraction = %f.\n" %(speedup[x],parFrac[x]);
	else:
		resStrings[x] = "4 thread to 1 speedup factor for arraysize 4000000 = %f.\nWith Parallel fraction = %f.\n" %(speedup[x],parFrac[x]);

# Print results to console and to log file.
of = open("project0.results.txt","a");
for res in [0,1,2]:
	print resStrings[res];
	of.write(resStrings[res]);
of.close();