#ifndef _SOLUTION
#define _SOLUTION

#include<string>
#include<vector>
#include<iostream>

using namespace std;
class Solution {

public:

	/* route represenetation */
	vector<vector<int>> aRoute;
	vector<int> aRouteLength;

	/* capacity and slacks */
	vector<float> aCapacityViolation;
	vector<vector<float>> aForwardCapacitySlack;
	vector<vector<float>> aBackwardCapacitySlack;

	/* timewindow and slacks */
	vector<float> aTimeViolation;
	vector<vector<float>> aForwardTimeSlack;
	vector<vector<float>> aBackwardTimeSlack;

	/* dynamic attributes */
	int aActivateRouteIndex = 0;

public:
	Solution(vector<vector<int>> customer,  int numVehicle) /* constructor */
	{
		vector<int> currentRoute = { 0, 0 };
		int currentRouteLength = 0;
		float currentViolation = 0.0;
		vector<float> currentSlack = { 0.0 };
		int i;
		for (i = 0; i < numVehicle; i++) {
			/* route */
			aRoute.push_back(currentRoute);
			aRouteLength.push_back(currentRouteLength);
			/* capacity */
			aCapacityViolation.push_back(currentViolation);
			aForwardCapacitySlack.push_back(currentSlack);
			aBackwardCapacitySlack.push_back(currentSlack);
			/* time window */
			aTimeViolation.push_back(currentViolation);
			aForwardTimeSlack.push_back(currentSlack);
			aBackwardTimeSlack.push_back(currentSlack);
		}
	}

	void insertCustomer(int customerIndex, int routeIndex, int position);
	void printRoute(int begin, int end);
};
#endif // !_SOLUTION