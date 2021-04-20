#include<iostream>
#include"work_with_file.h"
#include "Encoder.h"
#include "Decoder.h"
#include <vector>
using namespace std;

void Encode (string inputName, string outputName) {
	int dictionarySize, fileSize;
	vector<char> fileText;
	vector<int> code;

	fileSize = file_size(inputName);

	char *bytes = new char[fileSize];

	read_uncoded (bytes, inputName, fileSize);

	for (int i = 0; i < fileSize; i++) {
		fileText.push_back(bytes[i]);
	}

	code = Encoder::zip(fileText, dictionarySize);

	int *numbers = new int[code.size()];

	for (int i = 0; i < code.size(); i++) {
		numbers[i] = code[i];
	}

	Write_coded (numbers, dictionarySize, code.size(), outputName);
}

void Decode (string fileName) {
	int fileSize;
	vector<char> fileText;
	vector<int> code;

	fileSize = file_size(fileName);

	Read_coded (code, fileName, fileSize);

	fileText = Decoder::unzip(code);

	char *bytes = new char[fileText.size()];

	for (int i = 0; i < fileText.size(); i++) {
		bytes[i] = fileText[i];
	}

	write_decoded (bytes, fileName, fileText.size());
}

int main()
{
	//Encode ("test.png", "test2.png"); 
	//Decode ("test2.png");
}