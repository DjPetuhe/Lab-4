#pragma once
#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>

using namespace std;

int file_size (string);

void read_uncoded (char *, string, int);

void Write_coded (int *, int, int, string);

void Read_coded (vector<int> &code, string file_name, int file_size);

void write_decoded (char *, string, int);