#ifndef _READ
#define _READ


#include <fstream> 
#include <algorithm>  
#include <iostream>   
#include <string>
#include<chrono>
#include<vector>
#include<unordered_map>

using namespace std;

class Read {

private:
	string aInstanceName;
	string aFileName;


public:
	Read(string rFileName)
	{
		aFileName = rFileName;
	}

	void read(void);
};



#endif // !_READ