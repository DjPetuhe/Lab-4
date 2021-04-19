//#include<iostream>
//#include<fstream>
#include"work_with_file.h"

using namespace std;

int file_size (ifstream &file) {
    int size;
    file.seekg(0,ios_base::end);
    size = file.tellg();
    return size;
}

char* get_bytes (string name) {
    int size;
    char *bytes;
    ifstream file;
    
    file.open(name, ios::binary);

    size = file_size (file);

    bytes = new char[size];

    file.read(bytes, size);

    file.close();

    return bytes;
}