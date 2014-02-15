#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

bool permutations(string s, string t)
{
    int letters[256];

    if (s.length() != t.length())
        return false;

    for (int i = 0; i < s.length(); i++){
        letters[s.at(i)]++;
    } 
    
    for (int i = 0; i < t.length(); i++){
        if(letters[t.at(i)] == 0)
            return false;
        else 
            letters[t.at(i)]--;
    }

    return true;
}

int main()
{
    string s = "man";
    string t = "amn";
    return permutations(s,t);
}
