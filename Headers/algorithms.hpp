#ifndef NN_A
#define NN_A
#include <vector>
#include <limits>
using namespace std;

// Algorithm Options
enum Algorithm
{
	FORWARD_SELECTION = 1,
	BACKWARD_ELIMINATION = 2
};

class NearestNeighborAlgorithm
{
	// A constant representing a very large number, used to initialize minimum distance tracking
	const double INFINITE = std::numeric_limits<double>::max();
	
	// Variables to store the state of the nearest neighbor found during KNNSearch
	double nnDistance; // The minimum distance found so far
	double nnLocation; // The index of the nearest neighbor in the dataset
	double nnLabel;    // The class label of the nearest neighbor
	
	// Helper function to calculate the Euclidean distance between two data instances
	// using only a specific subset of features.
	double CalculateDistance(const vector<double> &instance1, const vector<double> &instance2, const vector<int> &features_to_use);
	
	public:
		// Evaluates a specific subset of features using Leave-One-Out Cross-Validation
		double CrossValidation(const vector<vector<double>> &data, const vector<int> &current_set_of_features);
		
		// Performs Backward Elimination Search to find the best subset of features
		void NNBackwardEliminationSearch(const vector<vector<double>> &data);
		
		// Performs Forward Selection Search to find the best subset of features
		void NNForwardSelectionSearch(const vector<vector<double>> &data);
		
		// Finds the nearest neighbor for a specific object in the dataset using all features
		void KNNSearch(const unsigned int k, const vector<vector<double>> &data);
};

#endif