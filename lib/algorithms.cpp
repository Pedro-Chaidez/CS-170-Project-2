#include "../Headers/algorithms.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Helper function to calculate Euclidean distance based on a subset of features
double NearestNeighborAlgorithm::calculate_distance(const vector<double> &instance1, const vector<double> &instance2, const vector<int> &features_to_use)
{
	double distance = 0.0;
	for (int feature : features_to_use)
	{
		// Assuming the class label is at index 0, features start at index 1
		double diff = instance1[feature] - instance2[feature];
		distance += diff * diff;
	}
	return sqrt(distance);
}

// Helper function for Leave-One-Out Cross-Validation
double NearestNeighborAlgorithm::cross_validation(const vector<vector<double>> &data, const vector<int> &current_set_of_features)
{
	if (current_set_of_features.empty())
		return 0.0;

	int correct_predictions = 0;

	for (size_t i = 0; i < data.size(); ++i)
	{
		double nearest_neighbor_distance = INFINITE;
		double nearest_neighbor_label = -1;

		for (size_t j = 0; j < data.size(); ++j)
		{
			if (i == j)
				continue; // Don't compare the object to itself

			double distance = calculate_distance(data[i], data[j], current_set_of_features);
			if (distance < nearest_neighbor_distance)
			{
				nearest_neighbor_distance = distance;
				nearest_neighbor_label = data[j][0]; // Class label of the nearest neighbor
			}
		}

		if (nearest_neighbor_label == data[i][0])
		{
			correct_predictions++;
		}
	}

	return (double)correct_predictions / data.size();
}

void NearestNeighborAlgorithm::NNForwardSelectionSearch(const vector<vector<double>> &data)
{
	vector<int> current_set_of_features;
	vector<int> best_overall_features;
	double best_overall_accuracy = 0.0;
	int number_of_features = data.empty() ? 0 : data[0].size() - 1;

	for (int i = 1; i <= number_of_features; i++)
	{
		int feature_to_add_at_this_level = -1;
		double best_so_far_accuracy = -1.0;

		for (int k = 1; k <= number_of_features; k++)
		{
			// If feature k is NOT already in current_set_of_features
			if (find(current_set_of_features.begin(), current_set_of_features.end(), k) == current_set_of_features.end())
			{
				vector<int> test_features = current_set_of_features;
				test_features.push_back(k);

				double accuracy = cross_validation(data, test_features);

				cout << "\tUsing feature(s) {";
				for (size_t f = 0; f < test_features.size(); f++)
				{
					cout << test_features[f] << (f == test_features.size() - 1 ? "" : ",");
				}
				cout << "} accuracy is " << (accuracy * 100.0) << "%" << endl;

				if (accuracy > best_so_far_accuracy)
				{
					best_so_far_accuracy = accuracy;
					feature_to_add_at_this_level = k;
				}
			}
		}

		if (feature_to_add_at_this_level != -1)
		{
			current_set_of_features.push_back(feature_to_add_at_this_level);

			if (best_so_far_accuracy > best_overall_accuracy)
			{
				best_overall_accuracy = best_so_far_accuracy;
				best_overall_features = current_set_of_features;
			}
			else
			{
				cout << endl
						 << "(Warning, Accuracy has decreased! Continuing search in case of local maxima)" << endl;
			}

			cout << endl
					 << "Feature set {";
			for (size_t f = 0; f < current_set_of_features.size(); f++)
			{
				cout << current_set_of_features[f] << (f == current_set_of_features.size() - 1 ? "" : ",");
			}
			cout << "} was best, accuracy is " << (best_so_far_accuracy * 100.0) << "%" << endl
					 << endl;
		}
	}

	cout << "Finished search!! The best feature subset is {";
	for (size_t f = 0; f < best_overall_features.size(); f++)
	{
		cout << best_overall_features[f] << (f == best_overall_features.size() - 1 ? "" : ",");
	}
	cout << "}, which has an accuracy of " << (best_overall_accuracy * 100.0) << "%" << endl;
}

void NearestNeighborAlgorithm::NNBackwardEliminationSearch(const vector<vector<double>> &data)
{
	int number_of_features = data.empty() ? 0 : data[0].size() - 1;
	vector<int> current_set_of_features;

	for (int i = 1; i <= number_of_features; i++)
		current_set_of_features.push_back(i);

	// Evaluate initial set (all features)
	double initial_accuracy = cross_validation(data, current_set_of_features);
	vector<int> best_overall_features = current_set_of_features;
	double best_overall_accuracy = initial_accuracy;

	cout << "Initial set {all features} accuracy: " << (initial_accuracy * 100.0) << "%" << endl
			 << endl;

	for (int i = 1; i < number_of_features; i++)
	{
		int feature_to_remove_at_this_level = -1;
		double best_so_far_accuracy = -1.0;

		for (int k : current_set_of_features)
		{
			vector<int> test_features = current_set_of_features;
			test_features.erase(remove(test_features.begin(), test_features.end(), k), test_features.end());

			double accuracy = cross_validation(data, test_features);

			cout << "\tUsing feature(s) {";
			for (size_t f = 0; f < test_features.size(); f++)
			{
				cout << test_features[f] << (f == test_features.size() - 1 ? "" : ",");
			}
			cout << "} accuracy is " << (accuracy * 100.0) << "%" << endl;

			if (accuracy > best_so_far_accuracy)
			{
				best_so_far_accuracy = accuracy;
				feature_to_remove_at_this_level = k;
			}
		}

		if (feature_to_remove_at_this_level != -1)
		{
			current_set_of_features.erase(remove(current_set_of_features.begin(), current_set_of_features.end(), feature_to_remove_at_this_level), current_set_of_features.end());

			if (best_so_far_accuracy > best_overall_accuracy)
			{
				best_overall_accuracy = best_so_far_accuracy;
				best_overall_features = current_set_of_features;
			}
			else
			{
				cout << endl
						 << "(Warning, Accuracy has decreased! Continuing search in case of local maxima)" << endl;
			}

			cout << endl
					 << "Feature set {";
			for (size_t f = 0; f < current_set_of_features.size(); f++)
			{
				cout << current_set_of_features[f] << (f == current_set_of_features.size() - 1 ? "" : ",");
			}
			cout << "} was best, accuracy is " << (best_so_far_accuracy * 100.0) << "%" << endl
					 << endl;
		}
	}

	cout << "Finished search!! The best feature subset is {";
	for (size_t f = 0; f < best_overall_features.size(); f++)
	{
		cout << best_overall_features[f] << (f == best_overall_features.size() - 1 ? "" : ",");
	}
	cout << "}, which has an accuracy of " << (best_overall_accuracy * 100.0) << "%" << endl;
}

void NearestNeighborAlgorithm::KNNSearch(const unsigned int object_to_classify_idx, const vector<vector<double>> &data)
{
	nnDistance = INFINITE;
	nnLocation = -1;
	nnLabel = -1;
	if (object_to_classify_idx >= data.size())
		return;
	vector<double> object_to_classify = data[object_to_classify_idx];
	vector<int> all_features;
	for (size_t i = 1; i < object_to_classify.size(); i++)
		all_features.push_back(i);
	for (size_t k = 0; k < data.size(); ++k)
	{
		if (k != object_to_classify_idx)
		{
			double distance = calculate_distance(object_to_classify, data[k], all_features);
			if (distance < nnDistance)
			{
				nnDistance = distance;
				nnLocation = k;
				nnLabel = data[k][0];
			}
		}
	}
}