#pragma once
#include <vector>
#include<fstream>
#include<cmath>

using namespace std;

class Encoder
{
public:
	void Encode (string, string);
	void combine (string fileName1, string fileName2, string archiveName);
private:
	vector<int> zip(vector<char>, int&);
};
