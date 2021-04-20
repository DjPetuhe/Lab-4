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
    int previous = code[0],
    int current;
    string a = Dictionary[previous];
    string b;
    b += a[0];
    for (int i = 0; i < code.size() - 1; i++)
    {
        current = code[i + 1];
        if (Dictionary.find(current) == Dictionary.end())
        {
            b = Dictionary[previous];
            b = b + a;
        }
        else 
        {
            b = Dictionary[current];
        }
        b.clear();
        b += a[0];
        Dictionary[cnt] = Dictionary[previous] + b;
        cnt++;
        previous = current;
    }
}