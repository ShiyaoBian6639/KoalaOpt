#ifndef _READ
#define _READ


#include <fstream> 
#include <algorithm>  
#include <iostream>   
#include <string>
#include <sstream> 
#include<chrono>
#include<vector>
#include<boost/algorithm/string.hpp>
#include<boost/tokenizer.hpp>
#include<unordered_map>

using namespace std;

class Read {

private:
	string aInstanceName;
	string aFileName;
	ifstream file;
	string line;
	vector<string> result;
	int NUM_NNZ = 0;  // number of non-zeros
	int NUM_LINE = 0;  // number of lines in file
	int NUM_VARS = 0;  // number of variables (columns)
	int NUM_CONSTRAINTS = 0;  // number of constraints (rows)


public:
	Read(string rFileName);

	void read(void);
	void getInstanceName(void);
};



#endif // !_READ