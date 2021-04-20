#include "Encoder.h"
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

vector<int> Encoder::zip(vector<char> fileText,int &dictionarySize)
{
    unordered_map<string, int> Dictionary;
    int cnt = 0;
    while (cnt < 256)
    {
        string tempChar = "";
        tempChar += char(cnt);
        Dictionary[tempChar] = cnt;
        cnt++;
    }
    string current, next;
    vector<int> code;
    current += fileText[0];
    for (int i = 0; i < fileText.size(); i++)
    {
        if (i != fileText.size() - 1)
        {
            next += fileText[i + 1];
        }
        if (Dictionary.find(current + next) != Dictionary.end())
        {
            current = current + next;
        }
        else
        {
            code.push_back(Dictionary[current]);
            Dictionary[current + next] = cnt;
            cnt++;
            current = next;
        }
        next.clear();
    }
    code.push_back(Dictionary[current]);
    dictionarySize = Dictionary.size();
    return code;
}

int Encoder::file_size (string name) {
    ifstream file;
    int size;
    file.open(name, ios::binary);
    file.seekg(0,ios_base::end);
    size = file.tellg();
    file.close();
    return size;
}

void Encoder::Read_file (char *bytes, string name, int size) {
    ifstream file;
    
    file.open(name, ios::binary);

    file.read(bytes, size);

    file.close();
}

void Encoder::Write_file (int *numbers, int table_size, int num_size, string file_name) {
    int byte_size, bits_number, byte_number;
    char byte_size_char;

    ofstream file;
    file.open(file_name, ios::binary);

    if (log2(table_size) > (float)(int)log2(table_size)){
        byte_size = (int)log2(table_size) + 1;
    }
    else {
        byte_size = (int)log2(table_size);
    }

    byte_size_char = (char)byte_size;

    file.write(&byte_size_char, 1);
    file.write((char*)&(num_size), sizeof(int));

    bits_number = byte_size * num_size;
    
    if (bits_number % 8 != 0){
        byte_number = bits_number / 8 + 1;
    }
    else {
        byte_number = bits_number / 8;
    }

    char *byte = new char[byte_number];

    for (int i = 0; i < byte_number; i++) {
        byte[i] = 0;
    }

    int bit_int = byte_size - 1;
    int bit_char = 7;
    int int_number = 0;
    int char_number = 0;
    int res;

    for (int i = 0; i < bits_number; i++) {
        res = (numbers[int_number] & (1 << bit_int)) >> bit_int;
        byte[char_number] = byte[char_number] | (res << bit_char);


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

    file.write(byte, byte_number);

    file.close();
}

void Encoder::Encode (string inputName, string outputName) {
	int dictionarySize, fileSize;
	vector<char> fileText;
	vector<int> code;

	fileSize = file_size(inputName);

	char *bytes = new char[fileSize];

	Read_file (bytes, inputName, fileSize);

	for (int i = 0; i < fileSize; i++) {
		fileText.push_back(bytes[i]);
	}

	code = Encoder::zip(fileText, dictionarySize);

	int *numbers = new int[code.size()];

	for (int i = 0; i < code.size(); i++) {
		numbers[i] = code[i];
	}

	Write_file (numbers, dictionarySize, code.size(), outputName);
}