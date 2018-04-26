*******************************************************
*  Name      :      Bryant Wong    
*  Student ID:      107571009           
*  Class     :  CSC 3453         
*  HW#       :  Lab 1                
*  Due Date  :  Sept. 25, 2017
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************

This program asks the user how many threads they would like to use for calculating
a resulting matrix from multiplying 2 other matrices from an input file.  Each row 
of the result matrix should be calculated by a new thread until the maximum number 
of threads is reached.  The result matrix is then displayed along with a total
execution timer.

*******************************************************
*  Source files
*******************************************************

Name:  main.cpp
   Main program.  This has member function calls that contains all of the actual code and 
asks user how many threads to use.

Name:  Threading.h
   Originally, I wanted to use a class for creating and working threads, however, I found out
midway through that threading cannot be done using C++ classes because of "this" in the function calls

Name: Threading.cpp
   Contains all of the functions that creates threads, reads the file, calculates the result matrix
and outputs.
   
   
*******************************************************
*  Circumstances of programs
*******************************************************

Compiles and runs on csegrid.

Developed on Visual Studio Community 2017 version 15.3.2.  


*******************************************************
*  How to build and run the program
*******************************************************

1. Uncompress the homework.  The homework file is compressed.  
   To uncompress it use the following commands 
       % unzip [Won1009]

   Now you should see a directory named homework with the files:
        main.cpp
	Threading.h
	Threading.cpp
        makefile
	input.txt
        Readme.txt
	Report.docx

2. Build the program.

    Change to the directory that contains the file by:
    % cd [Won1009] 

    Compile the program by:
    % make

3. Run the program by:
   % ./lab1

4. Delete the obj files, executables, and core dump by
   %./make clean
