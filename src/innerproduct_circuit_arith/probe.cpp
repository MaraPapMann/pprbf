#include <iostream>
using namespace std;


int main(int argc, char const *argv[])
{
    int* a = new int[10];
    for(int i=0; i<10; i++){
        a[i] = i;
    }
    for(int i=0; i<10; i++){
        cout<<a[i]<<", ";
    }
    return 0;
}
