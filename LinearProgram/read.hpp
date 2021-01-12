#ifndef _READ
#define _READ

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream> 
#include <algorithm>  
#include <iostream>   
#include <string>
#include<chrono>
#include<vector>
#include<unordered_map>

using namespace std;
using namespace boost;

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