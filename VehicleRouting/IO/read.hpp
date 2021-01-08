#pragma once
#ifndef _READ
#define _READ

#include<iostream>
#include<string>
#include<fstream>
#include<chrono>
#include<boost/unordered/unordered_set.hpp>

#include<boost/numeric/ublas/vector.hpp>

using namespace std;

class Read {

public:
	/* class attributes */
	string fileName;
	string instanceName;
	int numVehicle, capacity, numCustomer;
	vector<vector<int>> customer;

	/* constructor of Read */
	Read(string inputFileName) 
	{
		fileName = inputFileName;
		ifstream instance;
		instance.open(fileName);
		if (!instance.is_open()) {
			cout << "instance " << fileName << " is not valid!" << endl;
			return;
		}
	}

	/* class methods */
	string getFileName(void);
	void read(void);
	void printCustomer(void);

};
#endif // !_READ

