#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

bool isS3Valid(string s1, string s2, string s3) 
{
    if(s1.length() + s2.length() != s3.length())
        return false;
        
    if (s1.empty() == 1 || s2.empty() == 1 || s3.empty() == 1){ 
        if (s1.length() + s2.length() == s3.length())
            return true;
        else  
            return false;
    }   
        
    if (s1.at(0) != s3.at(0) && s2.at(0) != s3.at(0))
        return false;

    if (s1.at(0) == s3.at(0) && isS3Valid(s1.substr(1), s2, s3.substr(1))){
        return true;
    }   
    if (s2.at(0) == s3.at(0) && isS3Valid(s1, s2.substr(1), s3.substr(1))){
        return true;
    }   

    return false;
}

int main()
{
    string s1 = "dbc";
    string s2 = "def";
    string s3 = "daefdbc";
    bool result = isS3Valid(s1,s2,s3);
    cout << result << endl;
    s3 = "defdbc";
    result = isS3Valid(s1,s2,s3);
    cout << result << endl;
    return 0;
}
