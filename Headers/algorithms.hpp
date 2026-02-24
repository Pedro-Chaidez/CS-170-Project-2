#ifndef NN_A
#define NN_A
#include <vector>
using namespace std;

// Algorithm Options
enum Algorithm
{
	FORWARD_SELECTION = 1,
	BACKWARD_ELIMINATION = 2
};

struct NearestNeighborAlgorithm
{
	void NNBackwardEliminationSearch();
	void NNForwardSelectionSearch();
	void KNNSearch(unsigned int k, vector<vector<double>> data);
};

#endif