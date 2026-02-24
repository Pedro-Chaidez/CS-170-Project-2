#include <iostream> //Input Output
#include <fstream> //File Reading
#include <vector> //Lists handling
#include <exception> // Error handling
#include <sstream> //Need for parsing strings into numbers
#include "../Headers/algorithms.hpp"

using namespace std;

int main()
{
	string inputString;
	while(true){
		cout<<"Welcome to Pedro Chaidez\'s Feature Selection Algorithm!"<<endl
				<<"Type in the name of the file to test "<<endl
				<<"(make sure all test files are in the Data folder as a txt file): ";
		cin>>inputString;
		cout<<endl<<endl;

		// Access the file
		string file_path = "lib/Data/"+inputString;
		ifstream file(file_path);
		if (!file.is_open()) throw runtime_error("Error: Could not open the file.\n");
				
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

		cout<<"Type the number of the algorithm you want to run."<<endl
				<<"1) Forward Selection"<<endl
				<<"2) Backward Elimination"<<endl
				<<"Selection: ";
		cin>>inputString;
		cout << endl << endl
				 << "This dataset has " << colCount - 1 << " features (not including the class attribute), with " << rowCount << " instances." << endl
				 << endl
				 << "Running nearest neighbor with all " << colCount - 1 << " features, using \"leaving-one-out\" evaluation, I get an accuracy of " << 0 << '%' << endl
				 << endl
				 << "Beginning search." << endl
				 << endl;

		// Use the numbers to print
		cout << "Numbers read from file:" << endl;
		for (vector<double> dataLine : data)
		{
			if(dataLine.size()>0)
				cout<<"Class "<<dataLine.at(0)<<": ";
			for(unsigned int i = 1; i<dataLine.size()-1;i++){
				cout<<dataLine.at(i)<<", ";
			}
			if(dataLine.size()>1){
				cout<<dataLine.at(dataLine.size()-1)<<endl;
			}
		}
		cout<<"Finished search! The best feature subset is {"<<0<<','<<0<<"}, which has an accuracy of "<<0<<'%'<<endl
				<<endl
				<<"Done with program? Type Quit"<<endl
				<<"Anything else would restart the program..."<<endl
				<<"Selection: ";
		cin>>inputString;
		cout<<endl<<endl;
		if (inputString == "Quit") return 0;
	}
	return 0;
}
