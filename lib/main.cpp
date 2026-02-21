#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	// 1. Specify the file path and create an input file stream object
	string file_path = "test.txt";
	ifstream file(file_path); //

	// 2. Check if the file opened successfully
	if (!file.is_open())
	{
		cerr << "Error: Could not open the file." << endl;
		return 1;
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

	return 0;
}
