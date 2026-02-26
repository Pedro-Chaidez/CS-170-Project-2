#include <iostream>	 //Input Output
#include <fstream>	 //File Reading
#include <vector>		 //Lists handling
#include <sstream>	 //Need for parsing strings into numbers
#include "../Headers/algorithms.hpp"

using namespace std;

int main()
{
	string inputString;
	NearestNeighborAlgorithm nn;

	while (true)
	{
		cout << "Welcome to Pedro Chaidez\'s Feature Selection Algorithm!" << endl
				 << "Type in the name of the file to test " << endl
				 << "(make sure all test files are in the Data folder as a txt file): ";
		cin >> inputString;
		cout << endl << endl;

		// Access the file
		string file_path = "lib/Data/" + inputString;
		ifstream file(file_path);
		if (!file.is_open())
		{
			cout << "Error: Could not open the file " << file_path << endl;
			continue;
		}

		// Read numbers from the file into a container
		vector<vector<double>> data; // 2D vector to store rows and columns
		string line;
		int rowCount = 0;
		int colCount = 0;

		// Read the file line by line
		while (getline(file, line))
		{
			if (line.empty())
				continue; // Skip empty lines

			stringstream ss(line);
			double value;
			vector<double> currentRow;

			// Read each number in the current line
			while (ss >> value)
			{
				currentRow.push_back(value);
			}

			if (!currentRow.empty())
			{
				// Set colCount based on the first valid row
				if (rowCount == 0)
					colCount = currentRow.size();
				data.push_back(currentRow);
				rowCount++;
			}
		}
		file.close();

		if (data.empty())
		{
			cout << "Error: File is empty or improperly formatted." << endl;
			continue;
		}

		cout << "Type the number of the algorithm you want to run." << endl
				 << "1) Forward Selection" << endl
				 << "2) Backward Elimination" << endl
				 << "Selection: ";

		int selection;
		cin >> selection;

		cout << endl
				 << endl
				 << "This dataset has " << colCount - 1 << " features (not including the class attribute), with " << rowCount << " instances." << endl
				 << endl;

		// Display initial search info as per the requested format
		cout << "Beginning search." << endl
				 << endl;

		if (selection == FORWARD_SELECTION)
		{
			nn.NNForwardSelectionSearch(data);
		}
		else if (selection == BACKWARD_ELIMINATION)
		{
			nn.NNBackwardEliminationSearch(data);
		}
		else
		{
			cout << "Invalid selection. Returning to start..." << endl;
			continue;
		}

		cout << endl
				 << "Done with program? Type Quit" << endl
				 << "Anything else would restart the program..." << endl
				 << "Selection: ";
		cin >> inputString;
		cout << endl
				 << endl;
		if (inputString == "Quit" || inputString == "quit")
			return 0;
	}
	return 0;
}