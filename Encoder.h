#pragma once
#include <vector>
#include<fstream>
#include<cmath>

using namespace std;

class Encoder
{
public:
	void Encode (string, string);
private:
	vector<int> zip(vector<char>, int&);
};
