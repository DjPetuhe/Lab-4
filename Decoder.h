#pragma once
#include <vector>
#include<fstream>
#include<cmath>
using namespace std;

class Decoder
{
public:
	int file_size (string);
	void Decode (string);
private:
	vector<char> unzip(vector<int>);
};