#include <iostream>
#include <stack>
#include <map>

using namespace std;

bool isBracketsBalanced(string s)
{

    map<char, char> brackets_map;
    brackets_map['}'] = '{';
    brackets_map[']'] = '[';
    brackets_map[')'] = '(';
    stack<char> brackets;

    for(unsigned int i = 0; i < s.length(); i++){

        if(s.at(i) == '[' || s.at(i) == '{' || s.at(i) == '('){
            brackets.push(s.at(i));
        } else {
            if (brackets_map[s.at(i)] == brackets.top())
                brackets.pop();
            else
                return false;
        }
            
    }

    return true;
}

int main()
{
    string s = "{[(])]}";
    bool result = isBracketsBalanced(s);
    cout << result << endl;
}
