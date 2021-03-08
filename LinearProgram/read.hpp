#ifndef _READ
#define _READ
#define _CRT_SECURE_NO_WARNINGS

#include <fstream> 
#include <iostream>   
#include <string>
#include<chrono>
#include<vector>

#include<unordered_map>

using namespace std;

const int STR_SIZE = 256;
const int WORD_SIZE = 64;

class Read {

private:
	string aInstanceName;
	const char* aFileName;
	ifstream file;
	string line;
	unordered_map<char*, int> aRowMap;
	int NUM_NNZ = 0;  // number of non-zeros
	int NUM_LINE = 0;  // number of lines in file
	int NUM_VARS = 0;  // number of variables (columns)
	int NUM_CONSTRAINTS = 0;  // number of constraints (rows)


public:
	Read(const char* rFileName);

	void read(void);
	void getInstanceName(void);
	void getRows(void);
	vector<string> string2vec(string line);
};



#endif // !_READ