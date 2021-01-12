#include"solution.hpp"

void Solution::insertCustomer(int customerIndex, int routeIndex, int position)
{
	aRoute[routeIndex].insert(aRoute[routeIndex].begin() + position, customerIndex);
}

void Solution::printRoute(int begin, int end)
{
	int i, j;
	for (i = begin; i < end; i++) {
		cout << "route" << i << " : ";
		for (j = 0; j < aRoute[i].size(); j++) {
			cout << j << " ";
		}
		cout << endl;
	}
}
