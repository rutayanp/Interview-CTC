#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef map<string, vector<string> >::iterator map_it;

vector<string> printAnagrams(string *words, int len)
{
    map<string, vector<string> > anagrams;
    vector<string> result;
    for(int i = 0; i < len; i++){
        string temp = words[i];
        sort(temp.begin(), temp.begin() + temp.length());
        anagrams[temp].push_back(words[i]);
    }

    for( map_it it = anagrams.begin(); it != anagrams.end(); it++){
        for(unsigned int i = 0; i < it->second.size(); i++){
            result.push_back(it->second[i]);
        } 
    }

    return result;
}

int main()
{
    string words[] = {"rats", "cats", "bats", "abc", "bac", "cba", "tacs", "tars", "tabs"};
    vector<string> result = printAnagrams(words, 9);
    for(unsigned int i = 0; i < result.size(); i++){
        cout << result[i] << ", ";
    }
    cout<< endl;
}
