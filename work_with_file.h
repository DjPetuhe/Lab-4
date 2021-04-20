#pragma once
#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

int file_size (string);

void read_uncoded (char *, string, int);

void Write_coded (int *, int, int, string);

void Read_coded (int *, string, int);

void write_decoded (char *, string, int);