#include <iostream>
#include <stdlib.h>

using namespace std;

void replaceSpace(char *str, int len)
{
    int final_len = 0, spaces = 0;
    int j = len; 
    for(int i = 0; i < len; i++){
        if(str[i] == ' ')
            spaces++;
    }

    final_len = len + (2 * spaces);
    
    for(int i = final_len; i >= 0; i--){
        if(str[j] != ' '){
            str[i] = str[j];
        } else {
            str[i--] = '0';
            str[i--] = '2';
            str[i] = '%'; 
        }
        j--;
    }
}

int main()
{
    char s[] = "There are spaces in this line";
    char *str = s;
    int len = 0;
    for(int i = 0; str[i] != '\0'; i++)
        len++;  
    replaceSpace(str, len);
    cout << str << endl;
    return 0;  
}
