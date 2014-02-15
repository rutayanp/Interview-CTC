#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

int compressLength(string s)
{
    int count = 0;
    int size = 0;
    char last = s.at(0);
    for(int i = 0; i < s.length(); i++){
        if(s.at(i) == last){
            count++;
        } else {
            size += 1 + to_string(count).length();
            count = 1;
            last = s.at(i);
        }
    }

    size += 1 + to_string(count).length();
    return size;
}

string compress(string str)
{
    int compress_length = compressLength(str);
    if (compress_length > str.length()){
        return str;
    }
    
    char last = str.at(0);
    int count = 0;
    string result;
    result.reserve(compress_length);
    for(int i = 0; i < str.length(); i++){
        if(last == str.at(i)){
            count++;
        } else {
            result = result + last + to_string(count);
            count = 1;
            last = str.at(i);
        }
    }

    result += last + to_string(count);

    return result;
}

int main()
{
    string s = "HHHEEELLLLLLOOO";
    cout << s << endl;
    int l = compressLength(s);
    cout << l << endl;
    s = compress(s);
    cout << s << endl;
    return 0;
}

