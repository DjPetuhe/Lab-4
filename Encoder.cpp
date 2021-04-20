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