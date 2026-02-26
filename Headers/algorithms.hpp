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
	const double INFINITE = std::numeric_limits<double>::max();
	double nnDistance;
	double nnLocation;
	double nnLabel;
	double calculate_distance(const vector<double> &instance1, const vector<double> &instance2, const vector<int> &features_to_use);
	double cross_validation(const vector<vector<double>> &data, const vector<int> &current_set_of_features);
	public :
		void NNBackwardEliminationSearch(const vector<vector<double>> &data);
		void NNForwardSelectionSearch(const vector<vector<double>> &data);
		void KNNSearch(const unsigned int k, const vector<vector<double>> &data);
};

#endif