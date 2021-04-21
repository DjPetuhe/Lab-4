#pragma once
#include<iostream>
#include <vector>
#include<fstream>
#include<cmath>
using namespace std;

class Decoder
{
public:
	int file_size (string);
	void Decode (string);
	void decombine (string archiveName, string *fileName1, string *fileName2);
private:
	vector<char> unzip(vector<int>);
};