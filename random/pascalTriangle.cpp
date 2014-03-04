#include <iostream>

using namespace std;

void printPascal(int n)
{
    int C = 1;
    for(int line = 0; line < n; line++){
        C = 1;
        for(int i = 0; i <= line; i++){
            if(i > 0){
                C = C * (line - i + 1)/i;                
            } else {
                C = 1;
            }
            cout << C << " ";
        }
        cout << endl;    
    }    
}

int main()
{
    int n = 6;
    printPascal(n);
}
