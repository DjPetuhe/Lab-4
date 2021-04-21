#pragma once
#include <vector>
#include<fstream>
#include<cmath>

using namespace std;

class FileWriter {
public:
    void Write_encoded_file (int *, int, int, string);
    void Write_decoded_file (char *, string, int);
};