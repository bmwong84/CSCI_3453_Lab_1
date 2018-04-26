#ifndef THREADING
#define THREADING
#define HAVE_STRUCT_TIMESPEC	//comment this out in linux
//#include <thread>

//to include pthread library on unix use:
//use g++ main.cpp -std=c++11 -lpthread 
#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

typedef std::chrono::high_resolution_clock timer;




class Threading
{
private: 

public:
	Threading();
	bool readFile();							//reads file, if matrix contains non-integers, quits program
	void displayExecutionTime();
	//void OutputMatrix(void*);
	//void OutputMatrix(int);
	void createThreads();
	void displayOutput();

};



#endif


//struct thread_data
//{
//	std::vector<std::vector<int>> AMatrix;		//2-d vectors to hold the matrices
//	std::vector<std::vector<int>> BMatrix;
//	std::vector<std::vector<int>> CMatrix;
//	double totalExecutionTime;					//record total execution time
//	int ARows, AColumns, BRows, BColumns;		//number of rows and columns in matrix A/B
//	int numThreads;
//	int rowGiven;
//	//void setNumThreads(int _numThreads)
//	//{
//	//	numThreads = _numThreads;
//	//}
//};
