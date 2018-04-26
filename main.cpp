//#include "pthread.h"
#include "Threading.h"

//all the stuff the thread is supposed to do, the multiplication, the timing, the address, and print out matrix C



int main()
{
	Threading Threads;
	if (Threads.readFile() == false)
	{
		return 0;
	}
	//Threads.readFile();
	Threads.createThreads();
	std::cout << "Would you like to view the result matrix? (Y/N)" << std::endl;
	char answer;
	std::cin >> answer;
	while (answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n')
	{
		std::cout << "Invalid entry.  Please answer Y/N if you would like to display the result matrix." << std::endl;
		std::cin >> answer;
	}
	if (answer == 'Y' || answer == 'y')
	{
		Threads.displayOutput();
	}
	Threads.displayExecutionTime();
	std::cout << "Exiting program";
	std::cin.ignore(1);
	std::cin.get();
	//system("pause");
	return 0;
}
