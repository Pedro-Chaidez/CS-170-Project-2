#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include "../Headers/algorithms.hpp"

using namespace std;

int main()
{
	string inputString;
	while(true){
		cout<<"Welcome to Pedro Chaidez\'s Feature Selection Algorithm!"<<endl
				<<"Type in the name of the file to test (make sure all test files are in the Data folder as a txt file): ";
		cin>>inputString;
		cout<<endl<<endl;

		// Access the file
		string file_path = "lib/Data/"+inputString;
		ifstream file(file_path);
		if (!file.is_open()) throw runtime_error("Error: Could not open the file.\n");
				
		// Read numbers from the file into a container
		vector<double> numbers;
		double number;
		while (file >> number)
		{ 
			numbers.push_back(number);
		}

		// 4. Close the file
		file.close(); //

		// 5. Use the numbers (e.g., print them)
		cout << "Numbers read from file:" << endl;
		for (double n : numbers)
		{
			cout << n << endl;
		}
		cout<<"Finished search! The best feature subset is {___}, which has an accuracy of _%"<<endl
				<<"Done with program? Type Quit"<<endl
				<<"Anything else would restart it"<<endl
				<<"Selection: ";
		cin>>inputString;
		cout<<endl<<endl;
		if (inputString == "Quit") return 0;
	}
	return 0;
}
