#include <string>
#include <unordered_map>
#include "Decoder.h"
#include"FileReader.h"
#include"FileWriter.h"

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

void Decoder::Decode (string fileName) {
	int fileSize;
	vector<char> fileText;
	vector<int> code;
    FileReader fr;
    FileWriter fw;

	fileSize = fr.file_size(fileName);

	fr.Read_decoded_file(code, fileName, fileSize);

	fileText = Decoder::unzip(code);

	char *bytes = new char[fileText.size()];

	for (int i = 0; i < fileText.size(); i++) {
		bytes[i] = fileText[i];
	}

	fw.Write_decoded_file (bytes, fileName, fileText.size());
}

void Decoder::decombine (string archiveName, string *fileName1, string *fileName2) {
    ofstream file1, file2;
    ifstream archive;
    int size1, size2; 
    char nameSize1, nameSize2;

    archive.open(archiveName, ios::binary);

    archive.read(&nameSize1, 1);
    archive.read(&nameSize2, 1);

    archive.read((char*)&size1, 4);
    archive.read((char*)&size2, 4);

    char *nameChar1 = new char[nameSize1];
    char *nameChar2 = new char[nameSize2];

    archive.read(nameChar1, nameSize1);
    archive.read(nameChar2, nameSize2);

    *fileName1 = nameChar1;
    *fileName2 = nameChar2;

    file1.open(*fileName1, ios::binary);
    file2.open(*fileName2, ios::binary);

    char *fileChar1 = new char[size1];
    char *fileChar2 = new char[size2];

    archive.read(fileChar1, size1);
    archive.read(fileChar2, size2);

    file1.write(fileChar1, size1);
    file2.write(fileChar2, size2);

    //cout << size2 << endl;

    delete nameChar1;
    delete nameChar2;
    delete fileChar1;
    delete fileChar2;

    file1.close();
    file2.close();
    archive.close();
}