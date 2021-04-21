#pragma once
#include <vector>
#include<fstream>
#include<cmath>

using namespace std;

class FileReader {
public:
    int file_size (string);
    void Read_encode_file (char *, string, int);
    void Read_decoded_file (vector<int> &code, string file_name, int file_size);
};