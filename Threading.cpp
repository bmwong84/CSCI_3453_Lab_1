#include "Threading.h"
std::vector<std::vector<int>> AMatrix;		//2-d vectors to hold the matrices
std::vector<std::vector<int>> BMatrix;
std::vector<int>* CMatrix = new std::vector<int>[0];		//dynamic array to hold result matrix


double totalExecutionTime;					//record total execution time
int ARows, AColumns, BRows, BColumns;		//number of rows and columns in matrix A/B
int numThreads;								//number of threads the user input	
							

Threading::Threading()
{
}

bool isPosInt(const std::string checkString)
{
	return checkString.find_first_not_of("-1234567890") == std::string::npos;	//checks if it is an integer i.e. has anything other than -0987654321 in the string, returns false if something other than digit is found
}


void *OutputMatrix(void *rowsGiven)
{

	std::vector<int>* tempRowsGiven;					
	tempRowsGiven = (std::vector<int>*)rowsGiven;		//list of rows this thread is supposed to do
	std::vector<int> tempRow;							
	std::vector<int> CRow;								//the row being input into the result matrix
	for (int rowCalculating = 0; rowCalculating < tempRowsGiven->size(); rowCalculating++)			//the row the thread is caluclating
	{
		int rowInThread = tempRowsGiven->at(rowCalculating);					//the row number of the AMatrix the row is calculating
		for (int BColumn = 0; BColumn < BMatrix.size(); BColumn++)
		{
			for (int count = 0; count < AMatrix.size() - 1; count++)
			{
				int temp;
				temp = AMatrix[rowInThread][count] * BMatrix[count][BColumn];			//the term that is being multiplied
				tempRow.push_back(temp);
			}
			int temp = 0;
			for (int count = 0; count < tempRow.size(); count++)
			{
				temp = temp + tempRow[count];											//the C-matrix sum
			}
			CRow.push_back(temp);														//pushes back the sum into the vector that is the C row
			tempRow.erase(tempRow.begin(), tempRow.end());								//clears the sum
		}
		CMatrix[rowInThread] = CRow;													//add entire row to result matrix
		CRow.erase(CRow.begin(), CRow.end());											//clears the row
	}


	pthread_exit(nullptr);
	return nullptr;
}

void Threading::displayExecutionTime()
{
	std::cout << "Total execution time using " << numThreads << " threads is " << totalExecutionTime << "ns." << std::endl;
}

void Threading::displayOutput()
{
	
	std::cout << "Matrix C = Matrix A x Matrix B: " << std::endl;
	for (int i = 0; i < AMatrix.size(); i++)						
	{
		for (int j = 0; j < CMatrix[0].size(); j++)
		{
			std::cout << CMatrix[i][j] << " ";				//displays the result matrix
		}
		std::cout << std::endl;
	}
	//std::cout << "Total execution time using " << numThreads << " threads is " << totalExecutionTime << "ns." << std::endl;
}

//fixthis edit: fixed, assigns rows to certain threads to be executed
void Threading::createThreads()
{
	//thread takes the list of rows that it needs to do

	auto timeMark1 = timer::now();						//start timer
	int result_code;
	std::vector<int>* threadIndex = new std::vector<int>[numThreads];		//the list of rows each thread is supposed to do
	pthread_t* threads = new pthread_t[numThreads];							//dynamic array of threads created to handle calculations


	for (int i = 0; i < AMatrix.size(); i++)	//for each row of MatrixA
	{
		for (int j = 0; j < numThreads; j++)
		{
			if (j == i%numThreads)				//if the thread number equals the thread assigned to the row, add it to the list of rows this thread is supposed to do
			{
				//pushback
				threadIndex[j].push_back(i);	//adds the row number to the list that this thread is supposed to do
			}
		}

	}
	if (numThreads > AMatrix.size())							//if the desired number of threads used to calculate is greater than the number of rows to calculate
	{
		std::cout << "Reducing number of threads to match number of rows calculated" << std::endl;
		numThreads = AMatrix.size();							//set the number of threads to the number of rows to be calculated
	}
	for (int count = 0; count < numThreads; count++)
	{
		//create a thread for each threadIndex, passing the list of rows this particular thread is supposed to calculate
		result_code = pthread_create(&threads[count], NULL, OutputMatrix, &threadIndex[count]);		
	}

	for (int count = 0; count < numThreads; count++)				//output saying which thread handles which rows
	{
		std::cout << "Creating worker thread " << &threads[count] << " for row ";
		for (int count2 = 0; count2 < threadIndex[count].size(); count2++)
		{
			std::cout << threadIndex[count][count2]<< " ";
		}
		std::cout << std::endl;
	}
	void *status;
	for (int i = 0; i < numThreads; i++)
	{
		result_code = pthread_join(threads[i], &status);			//joins the threads; waits for all to finish
		if (result_code)
		{
			std::cout << "Cannot join " << result_code << std::endl;
			exit(-1);
		}
	}
	auto timeMark2 = timer::now();	//end timer
	totalExecutionTime = totalExecutionTime + std::chrono::duration_cast<std::chrono::nanoseconds>(timeMark2 - timeMark1).count(); //sum time

	delete[]threads;
}


bool Threading::readFile()
{
	std::cout << "Enter number of threads to be used" << std::endl;
	std::cin >> numThreads;

	std::ifstream infile("input.txt");
	std::string inputLine;
	for (int count = 0; count < 2; count++)		//for each of the 2 vectors
	{

		std::string matrixSize;				//dimensions of the matrix
		std::getline(infile, matrixSize);		//read first line in as dimensions of the matrix
		std::stringstream inStream(matrixSize);		//make a stream from the line
		if (count == 0)
		{
			std::vector<std::vector<int>> inputMatrix;		//2-d vector for matrix
			inStream >> ARows;		//make the stream read first space-delineated
			inStream >> AColumns;		//make the stream read second delineated thing
			for (int numRows = 0; numRows < ARows; numRows++)
			{
				std::getline(infile, inputLine);
				std::vector<int> matrixRow;
				std::stringstream inputStream(inputLine);
				std::string temp;

				while (inputStream >> temp)
				{
					if (isPosInt == false)					//changed to "is int" allows negative sign
					{
						std::cout << "Unsable data, terminating program" << std::endl;
						return -1;
					}
					int tempNum = std::stoi(temp);				//changes string to integers
					matrixRow.push_back(tempNum);				//pushes back the integer into the matrix row
				}
				inputMatrix.push_back(matrixRow);				//pushes the entire row into the matrix
			}
			AMatrix = inputMatrix;								
			std::cout << "A Matrix: " << std::endl;
			for (int i = 0; i < ARows; i++)
			{
				for (int j = 0; j < AColumns; j++)
				{
					std::cout << inputMatrix[i][j] << " ";				//outputs AMatrix
				}
				std::cout << std::endl;
			}
		}
		else
		{
			std::vector<std::vector<int>> inputMatrix;		//2-d vector for matrix
			inStream >> BRows;		//make the stream read first space-delineated
			inStream >> BColumns;		//make the stream read second delineated thing
			for (int numRows = 0; numRows < ARows; numRows++)
			{
				std::getline(infile, inputLine);
				std::vector<int> matrixRow;
				std::stringstream inputStream(inputLine);
				std::string temp;
				while (inputStream >> temp)
				{
					if (isPosInt == false)
					{
						std::cout << "Unsable data, terminating program" << std::endl;
						return -1;
					}
					int tempNum = std::stoi(temp);
					matrixRow.push_back(tempNum);
				}
				inputMatrix.push_back(matrixRow);
			}
			BMatrix = inputMatrix;
			//char mat;
			//if (count == 0)
			//	mat = 'A';
			//else
			//	mat = 'B';
			std::cout << "Matrix B: " << std::endl;
			for (int i = 0; i < BRows; i++)
			{
				for (int j = 0; j < BColumns; j++)
				{
					std::cout << inputMatrix[i][j] << " ";
				}
				std::cout << std::endl;
			}
		}
	}

	 CMatrix = new std::vector<int>[AMatrix.size()];
	 return true;
}

//void Threading::OutputMatrix(void* threadarg)
//{
//	thread_data *threadData;
//	threadData = (struct thread_data*)threadarg;
//	//start timer
//	//thread takes the row of A given multiplies it by the column of B given, sums them
//	int tempRowSize = threadData->rowGiven;
//	std::vector<int> tempRow;
//	std::vector<int> CRow;
//	for (int BColumn = 0; BColumn < threadData->BMatrix.size(); BColumn++)
//	{
//		for (int count = 0; count < threadData->AMatrix.size() - 1; count++)
//		{
//			int temp;
//			temp = threadData->AMatrix[threadData->rowGiven][count] * threadData->BMatrix[count][BColumn];
//			tempRow.push_back(temp);
//		}
//		int temp = 0;
//		for (int count = 0; count < tempRow.size(); count++)
//		{
//			temp = temp + tempRow[count];
//		}
//		CRow.push_back(temp);
//		tempRow.erase(tempRow.begin(), tempRow.end());
//	}
//	threadData->CMatrix.push_back(CRow);
//	//end timer, sum time
//	//pthread_exit(0)
//}

//void Threading::OutputMatrix(/*void *threadid,*/ int rowGiven)
//{
//	//start timer
//	//thread takes the row of A given multiplies it by the column of B given, sums them
//	int tempRowSize = rowGiven;
//	std::vector<int> tempRow;
//	std::vector<int> CRow;
//	for (int BColumn = 0; BColumn < BMatrix.size(); BColumn++)
//	{
//		for (int count = 0; count < AMatrix.size() - 1; count++)
//		{
//			int temp;
//			temp = AMatrix[rowGiven][count] * BMatrix[count][BColumn];
//			tempRow.push_back(temp);
//		}
//		int temp = 0;
//		for (int count = 0; count < tempRow.size(); count++)
//		{
//			temp = temp + tempRow[count];
//		}
//		CRow.push_back(temp);
//		tempRow.erase(tempRow.begin(), tempRow.end());
//	}
//	CMatrix.push_back(CRow);
//	//end timer, sum time
//	//pthread_exit(0)
//}
