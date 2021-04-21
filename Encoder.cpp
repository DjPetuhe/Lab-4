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

void Encoder::Encode (string inputName1, string outputName) {
	int dictionarySize, fileSize;
	vector<char> fileText;
	vector<int> code;
    FileReader fr;
    FileWriter fw;

	fileSize = fr.file_size(inputName1);

	char *bytes = new char[fileSize];

	fr.Read_encode_file(bytes, inputName1, fileSize);

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

void Encoder::combine (string fileName1, string fileName2, string archiveName) {
    ifstream file1, file2;
    ofstream archive;
    FileReader fr;
    int size1, size2; 
    char nameSize1, nameSize2;
    //const char n = 2;

    nameSize1 = fileName1.size();
    nameSize2 = fileName2.size();

    file1.open(fileName1, ios::binary);
    file2.open(fileName2, ios::binary);

    size1 = fr.file_size(fileName1);
    size2 = fr.file_size(fileName2);

    archive.open(archiveName);

    //archive.write(&n, 1);

    archive.write(&nameSize1, 1);
    archive.write(&nameSize2, 1);

    archive.write((char*)&size1, 4);
    archive.write((char*)&size2, 4);

    char *nameChar1 = new char[nameSize1];

    for (int i = 0; i < nameSize1; i++) {
        nameChar1[i] = fileName1[i];
    }

    char *nameChar2 = new char[nameSize2];

    for (int i = 0; i < nameSize2; i++) {
        nameChar2[i] = fileName2[i];
    }

    char *fileChar1 = new char[size1];
    file1.read(fileChar1, size1);

    char *fileChar2 = new char[size2];
    file2.read(fileChar2, size2);

    archive.write(nameChar1, nameSize1);
    archive.write(nameChar2, nameSize2);

    archive.write(fileChar1, size1);
    archive.write(fileChar2, size2);

    //cout << size2 << endl;

    delete nameChar1;
    delete nameChar2;
    delete fileChar1;
    delete fileChar2;

    file1.close();
    file2.close();
    archive.close();
}