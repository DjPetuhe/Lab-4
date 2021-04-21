#include"FileReader.h"

int FileReader::file_size (string name) {
    ifstream file;
    int size;
    file.open(name, ios::binary);
    file.seekg(0,ios_base::end);
    size = file.tellg();
    file.close();
    return size;
}

void FileReader::Read_encode_file (char *bytes, string name, int size) {
    ifstream file;
    
    file.open(name, ios::binary);

    file.read(bytes, size);

    file.close();
}

void FileReader::Read_decoded_file (vector<int> &code, string file_name, int file_size) {
    int size, byte_size;
    char byte_size_char;

    ifstream file;
    file.open(file_name, ios::binary);

    file.read(&byte_size_char, 1);
    file.read((char*)&size, 4);

    int *numbers = new int[size];

    byte_size = byte_size_char;

    int bit_int = byte_size - 1;
    int bit_char = 7;
    int int_number = 0;
    int char_number = 0;
    int res;

    char *byte = new char [file_size - 5];

    file.read(byte, file_size - 5);

    for (int i = 0; i < byte_size * size; i++) {
        res = (byte[char_number] & (1 << bit_char)) >> bit_char;
        numbers[int_number] = numbers[int_number] | (res << bit_int);


        if (bit_int == 0) {
            bit_int = byte_size - 1;
            int_number++;
        } else {
            bit_int--;
        }

        if (bit_char == 0) {
            bit_char = 7;
            char_number++;
        } else {
            bit_char--;
        }
    }

    for (int i = 0; i < size; i++) {
        code.push_back(numbers[i]);
    }

    file.close();
}