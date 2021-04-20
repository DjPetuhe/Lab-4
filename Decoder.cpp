#include <string>
#include <unordered_map>
#include "Decoder.h"

vector<char> Decoder::unzip(vector<int> code)
{
    unordered_map<int, string> Dictionary;
    int cnt = 0;
    while (cnt < 256)
    {
        string tempChar = "";
        tempChar += char(cnt);
        Dictionary[cnt] = tempChar;
        cnt++;
    }
    vector<char> fileText;
    int previous = code[0];
    int current;
    string a = Dictionary[previous];
    string b;
    b += a[0];
    fileText.push_back(a[0]);
    for (int i = 0; i < code.size() - 1; i++)
    {
        current = code[i + 1];
        if (Dictionary.find(current) == Dictionary.end())
        {
            a = Dictionary[previous];
            a = a + b;
        }
        else 
        {   
            a = Dictionary[current];
        }
        for (int k = 0; k < a.size(); k++)
        {
            fileText.push_back(a[k]);
        }
        b.clear();
        b += a[0];
        Dictionary[cnt] = Dictionary[previous] + b;
        cnt++;
        previous = current;
    }
    return fileText;
}

int Decoder::file_size (string name) {
    ifstream file;
    int size;
    file.open(name, ios::binary);
    file.seekg(0,ios_base::end);
    size = file.tellg();
    file.close();
    return size;
}

void Decoder::Read_file (vector<int> &code, string file_name, int file_size) {
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

void Decoder::Write_file (char *bytes, string name, int size) {
    ofstream file;
    
    file.open(name, ios::binary);

    file.write(bytes, size);

    file.close();
}

void Decoder::Decode (string fileName) {
	int fileSize;
	vector<char> fileText;
	vector<int> code;

	fileSize = file_size(fileName);

	Read_file (code, fileName, fileSize);

	fileText = Decoder::unzip(code);

	char *bytes = new char[fileText.size()];

	for (int i = 0; i < fileText.size(); i++) {
		bytes[i] = fileText[i];
	}

	Write_file (bytes, fileName, fileText.size());
}