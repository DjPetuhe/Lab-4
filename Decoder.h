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
	void Read_file (vector<int> &code, string file_name, int file_size);
	void Write_file (char *, string, int);
};