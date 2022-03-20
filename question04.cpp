//Question 4 - Filesystem & args  

// Task: Implement the code as described in the main body, make sure to handle cases when the requested file is not found or the "files" directory doesn't exists and you have to create it
// Prefer modern solutions over classic C style solutions and keep in mind that this code should be able to run in other windows, linux and other platforms (hint: '/' and '\' in file paths)


#include <iostream>
#include <fstream>
#include <direct.h>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
	char ch;
	std::cout << "Enter c for create or write? else enter r" << std::endl;
	std::cin >> ch;
	//If user passed "create" argument 
	//Create (or overwrite) a file named *argument2.txt*  with the text "Hello from *argument3*" in a folder named "files"
	//under the current working directory  
	if (ch == 'c')
	{
		_mkdir("c:/code/files");
		ofstream file("c:/code/files/argument2.txt");
		file << "Hello from *argument3*";
		file.close();

		/*_mkdir("C:/Users/Abir/Desktop/βιερ/elbit/files");                   
		ofstream file("C:/Users/Abir/Desktop/βιερ/elbit/files/argument2.txt");
		file << "Hello from *argument3*";
		file.close();*/
	}//else if user passed "read" argument 
	//read a file named* argument2* from a folder named "files" under the current working directory and print it to the console
	else if (ch == 'r')
	{
		fstream file;
		file.open("C:/Users/Abir/Desktop/βιερ/elbit/files/argument2.txt", ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				cout << line << endl;
			}
			file.close();
		}	
	}
	
	
	//Execution example (assuming working directory c:\code): question04.exe create test1 Nir - should create the
	//file c:\code\files\test1.txt with the content "Hello from Nir"
	//Execution example (assuming working directory c:\code): question04.exe read test1  - should print "Hello from Nir" in the console (assuming the previous command was executed) 

	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}