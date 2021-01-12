#ifndef _READ
#define _READ

#include <boost/iostreams/device/mapped_file.hpp> 
#include <algorithm>  
#include <iostream>   
#include <cstring>
#include<chrono>

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