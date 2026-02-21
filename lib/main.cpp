#include <iostream>
#include <fstream>
#include <vector>
#include <exception>

using namespace std;

int main()
{
	string inputString;
	while(inputString != "Quit"){
		// 1. Specify the file path and create an input file stream object
		string file_path = "CS-170-Project-2/bin/Data/test.txt";
		ifstream file(file_path); //

		// 2. Check if the file opened successfully
		if (!file.is_open())
		{
			throw runtime_error("Error: Could not open the file.\n");
		}

		// 3. Read numbers from the file into a container (e.g., a vector)
		vector<int> numbers;
		int number;
		while (file >> number)
		{ //
			numbers.push_back(number);
		}

		// 4. Close the file
		file.close(); //

		// 5. Use the numbers (e.g., print them)
		cout << "Numbers read from file:" << endl;
		for (int n : numbers)
		{
			cout << n << endl;
		}
		cin>>inputString;
	}
	return 0;
}
