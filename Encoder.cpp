#include "Encoder.h"
#include <unordered_map>
#include <string>
using namespace std;

vector<int> Encoder::zip(vector<char> fileText)
{
    unordered_map<string, int> Dictionary;
    int cnt = 0;
    while (cnt < 256)
    {
        Dictionary[to_string(char(cnt))] = cnt;
        cnt++;
    }
    string p, c;
    vector<int> code;
    p += fileText[0];
    for (int i = 0; i < fileText.size(); i++)
    {
        if (i != fileText.size() - 1)
        {
            c += fileText[i + 1];
        }
        if (Dictionary.find(p + c) != Dictionary.end())
        {
            p = p + c;
        }
        else
        {
            code.push_back(Dictionary[p]);
            Dictionary[p + c] = cnt;
            cnt++;
            p = c;
        }
        c.clear();
    }
    code.push_back(Dictionary[p]);
    return code;
}