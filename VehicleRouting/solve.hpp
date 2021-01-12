#pragma
#ifndef _PREPROCESS
#define _PREPROCESS

#include"IO/read.hpp"
#include"utils.hpp"

class Solve : public Read {
	
	using Read::Read;/* constructor from Read class */

public:

	vector<vector<float>> preprocess();
	vector<float> coord2angle();
	vector<int> argsort();
	void printAngle();
};


#endif // !_PREPROCESS
