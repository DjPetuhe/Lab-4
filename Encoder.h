#pragma once
#include <vector>
#include<fstream>
#include<cmath>

using namespace std;

class Encoder
{
public:
	int file_size (string);
	void Encode (string, string);

private:
	vector<int> zip(vector<char>, int&);
	void Read_file (char *, string, int);
	void Write_file (int *, int, int, string);
};
