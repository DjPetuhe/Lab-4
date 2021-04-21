#include "Encoder.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include"FileReader.h"
#include"FileWriter.h"

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

void Encoder::Encode (string inputName, string outputName) {
	int dictionarySize, fileSize;
	vector<char> fileText;
	vector<int> code;
    FileReader fr;
    FileWriter fw;

	fileSize = fr.file_size(inputName);

	char *bytes = new char[fileSize];

	fr.Read_encode_file(bytes, inputName, fileSize);

	for (int i = 0; i < fileSize; i++) {
		fileText.push_back(bytes[i]);
	}

	code = Encoder::zip(fileText, dictionarySize);

	int *numbers = new int[code.size()];

	for (int i = 0; i < code.size(); i++) {
		numbers[i] = code[i];
	}

	fw.Write_encoded_file(numbers, dictionarySize, code.size(), outputName);
}