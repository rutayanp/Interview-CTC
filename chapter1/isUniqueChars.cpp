#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

bool isUniqueChars(string s){
    int checker = 0;
    for(int i=0; i < s.length(); i++){
        int val = s.at(i) - 'a';
        if((checker & (1 << val)) > 0){
            cout << "false" << endl;
            return false;
        }
        checker |= 1 << val;
    }
    
    cout << "true" << endl;
    return true;
}

int main(){
    string s = "helo";
    isUniqueChars(s);
    return 0;
}
