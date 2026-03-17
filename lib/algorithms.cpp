#include "../Headers/algorithms.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

double NearestNeighborAlgorithm::CalculateDistance(const vector<double> &instance1, const vector<double> &instance2, const vector<int> &featuresToUse)
{
	double distance = 0.0;
	for (int feature : featuresToUse)
	{
		// Assuming the class label is at index 0, features start at index 1
		double diff = instance1[feature] - instance2[feature];
		distance += diff * diff;
	}
	return sqrt(distance);
}

double NearestNeighborAlgorithm::CrossValidation(
		const vector<vector<double>> &data,
		const vector<int> &currentSetOfFeatures)
{
	// Prevent divide-by-zero if no features are provided
	if (currentSetOfFeatures.empty())
		return 0.0;

	int correctPredictions = 0;

	// Leave-One-Out Cross-Validation (LOOCV)
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		double nearestNeighborDistance = INFINITE;
		double nearestNeighborLabel = -1;

		// Find the nearest neighbor for the held-out instance 'i'
		for (unsigned int j = 0; j < data.size(); ++j)
		{
			if (i == j)
				continue; // Don't compare the object to itself

			double distance = CalculateDistance(data[i], data[j], currentSetOfFeatures);
			if (distance < nearestNeighborDistance)
			{
				nearestNeighborDistance = distance;
				nearestNeighborLabel = data[j][0];
			}
		}

		if (nearestNeighborLabel == data[i][0])
		{
			correctPredictions++;
		}
	}

	return (double)correctPredictions / data.size();
}

void NearestNeighborAlgorithm::NNForwardSelectionSearch(const vector<vector<double>> &data)
{
	vector<int> currentSetOfFeatures;
	vector<int> bestOverallFeatures;
	double bestOverallAccuracy = 0.0;
	// Number of features (excluding the class label)
	int numberOfFeatures = data.empty() ? 0 : (int)data[0].size() - 1;

	for (int i = 1; i <= numberOfFeatures; i++)
	{
		int featureToAddAtThisLevel = -1;
		double bestSoFarAccuracy = -1.0;

		// Evaluate all unselected features to find the best addition
		for (int k = 1; k <= numberOfFeatures; k++)
		{
			// Only test features not already in the current set
			if (find(currentSetOfFeatures.begin(), currentSetOfFeatures.end(), k) == currentSetOfFeatures.end())
			{
				vector<int> testFeatures = currentSetOfFeatures;
				testFeatures.push_back(k);

				double accuracy = CrossValidation(data, testFeatures);

				cout << "\tUsing feature(s) {";
				for (unsigned int f = 0; f < testFeatures.size(); f++)
				{
					cout << testFeatures[f] << (f == testFeatures.size() - 1 ? "" : ",");
				}
				cout << "} accuracy is " << (accuracy * 100.0) << "%" << endl;

				if (accuracy > bestSoFarAccuracy)
				{
					bestSoFarAccuracy = accuracy;
					featureToAddAtThisLevel = k;
				}
			}
		}

		if (featureToAddAtThisLevel != -1)
		{
			currentSetOfFeatures.push_back(featureToAddAtThisLevel);

			// Track overall peak performance
			if (bestSoFarAccuracy > bestOverallAccuracy)
			{
				bestOverallAccuracy = bestSoFarAccuracy;
				bestOverallFeatures = currentSetOfFeatures;
			}
			else
			{
				cout << endl
						 << "(Warning, Accuracy has decreased! Continuing search in case of local maxima)" << endl;
			}

			cout << endl
					 << "Feature set {";
			for (unsigned int f = 0; f < currentSetOfFeatures.size(); f++)
			{
				cout << currentSetOfFeatures[f] << (f == currentSetOfFeatures.size() - 1 ? "" : ",");
			}
			cout << "} was best, accuracy is " << (bestSoFarAccuracy * 100.0) << "%" << endl
					 << endl;
		}
	}

	cout << "Finished search!! The best feature subset is {";
	for (unsigned int f = 0; f < bestOverallFeatures.size(); f++)
	{
		cout << bestOverallFeatures[f] << (f == bestOverallFeatures.size() - 1 ? "" : ",");
	}
	cout << "}, which has an accuracy of " << (bestOverallAccuracy * 100.0) << "%" << endl;
}

void NearestNeighborAlgorithm::NNBackwardEliminationSearch(const vector<vector<double>> &data)
{
	int numberOfFeatures = data.empty() ? 0 : (int)data[0].size() - 1;
	vector<int> currentSetOfFeatures;

	for (int i = 1; i <= numberOfFeatures; i++)
		currentSetOfFeatures.push_back(i);

	// Establish baseline accuracy using all features
	double initialAccuracy = CrossValidation(data, currentSetOfFeatures);
	vector<int> bestOverallFeatures = currentSetOfFeatures;
	double bestOverallAccuracy = initialAccuracy;

	cout << "Initial set {all features} accuracy: " << (initialAccuracy * 100.0) << "%" << endl
			 << endl;

	for (int i = 1; i < numberOfFeatures; i++)
	{
		int featureToRemoveAtThisLevel = -1;
		double bestSoFarAccuracy = -1.0;

		// Evaluate the removal of each current feature
		for (int k : currentSetOfFeatures)
		{
			vector<int> testFeatures = currentSetOfFeatures;
			testFeatures.erase(remove(testFeatures.begin(), testFeatures.end(), k), testFeatures.end());

			double accuracy = CrossValidation(data, testFeatures);

			cout << "\tUsing feature(s) {";
			for (unsigned int f = 0; f < testFeatures.size(); f++)
			{
				cout << testFeatures[f] << (f == testFeatures.size() - 1 ? "" : ",");
			}
			cout << "} accuracy is " << (accuracy * 100.0) << "%" << endl;

			if (accuracy > bestSoFarAccuracy)
			{
				bestSoFarAccuracy = accuracy;
				featureToRemoveAtThisLevel = k;
			}
		}

		if (featureToRemoveAtThisLevel != -1)
		{
			// Remove the selected feature from the working set
			currentSetOfFeatures.erase(
					remove(currentSetOfFeatures.begin(), currentSetOfFeatures.end(), featureToRemoveAtThisLevel),
					currentSetOfFeatures.end());

			if (bestSoFarAccuracy > bestOverallAccuracy)
			{
				bestOverallAccuracy = bestSoFarAccuracy;
				bestOverallFeatures = currentSetOfFeatures;
			}
			else
			{
				cout << endl
						 << "(Warning, Accuracy has decreased! Continuing search in case of local maxima)" << endl;
			}

			cout << endl
					 << "Feature set {";
			for (unsigned int f = 0; f < currentSetOfFeatures.size(); f++)
			{
				cout << currentSetOfFeatures[f] << (f == currentSetOfFeatures.size() - 1 ? "" : ",");
			}
			cout << "} was best, accuracy is " << (bestSoFarAccuracy * 100.0) << "%" << endl
					 << endl;
		}
	}

	cout << "Finished search!! The best feature subset is {";
	for (unsigned int f = 0; f < bestOverallFeatures.size(); f++)
	{
		cout << bestOverallFeatures[f] << (f == bestOverallFeatures.size() - 1 ? "" : ",");
	}
	cout << "}, which has an accuracy of " << (bestOverallAccuracy * 100.0) << "%" << endl;
}

void NearestNeighborAlgorithm::KNNSearch(
		const unsigned int objectToClassifyIdx,
		const vector<vector<double>> &data)
{
	nnDistance = INFINITE;
	nnLocation = -1;
	nnLabel = -1;

	// Bounds checking
	if (objectToClassifyIdx >= data.size())
		return;

	vector<double> objectToClassify = data[objectToClassifyIdx];

	// Extract all valid feature indices (skipping class label at 0)
	vector<int> allFeatures;
	for (unsigned int i = 1; i < objectToClassify.size(); i++)
		allFeatures.push_back((int)i);

	// Find nearest neighbor
	for (unsigned int k = 0; k < data.size(); ++k)
	{
		if (k != objectToClassifyIdx) // Skip self-comparison
		{
			double distance = CalculateDistance(objectToClassify, data[k], allFeatures);

			if (distance < nnDistance)
			{
				nnDistance = distance;
				nnLocation = (double)k;
				nnLabel = data[k][0];
			}
		}
	}
}