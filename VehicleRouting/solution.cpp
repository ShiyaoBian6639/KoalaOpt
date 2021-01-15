#include"solution.hpp"

int Solution::insertCustomer(int customerIndex, int routeIndex, int position)
{
	aCapacity[routeIndex] += aCustomer[routeIndex][2];
	if aCapacity[routeIndex] < aCapacity
	aRoute[routeIndex].insert(aRoute[routeIndex].begin() + position, customerIndex);
	
}

void Solution::printRoute(int begin, int end)
{
	int i, j;
	cout << endl;
	for (i = begin; i < end; i++) {
		cout << "route" << i << " : ";
		for (j = 0; j < aRoute[i].size(); j++) {
			cout << aRoute[i][j] << " ";
		}
		cout << endl;
	}
}
