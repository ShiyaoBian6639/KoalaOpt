#ifndef _SOLUTION
#define _SOLUTION

#include<string>
#include<vector>


using namespace std;
class Solution {

private:
	string solutionDataStructure;

	/* route represenetation */
	vector<vector<int>> route;
	vector<int> routeLength;

	/* capacity and slacks */
	vector<float> capacityViolation;
	vector<vector<float>> forwardCapacitySlack;
	vector<vector<float>> backwardCapacitySlack;

	/* timewindow and slacks */
	vector<float> timeViolation;
	vector<vector<float>> forwardTimeSlack;
	vector<vector<float>> backwardTimeSlack;

	/* dynamic attributes */
	int activateRouteIndex = 0;

public:
	Solution(vector<vector<int>> customer)
	{

	}
};
#endif // !_SOLUTION