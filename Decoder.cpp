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