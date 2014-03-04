#include <iostream>
#include <stdlib.h>

using namespace std;

void reverse(char *str){
    char *t1, *t2;
    char temp;
    t1 = t2 = str;
    for(int i = 0; *t2 != '\0'; i++){
        t2++;
    }
    t2--;

    while(t1 != t2){
        temp = *t1;
        *t1 = *t2;
        *t2 = temp;
        t1++;
        t2--;
    }
    
}

int main(){
    char s1[] = "I am reversed";
    char *str = s1; 
    cout << str << endl;
    reverse(str);
    cout << "reversed : " << str << endl;
    return 0;
}
