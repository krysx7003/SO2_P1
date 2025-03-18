#include <iostream>
#include <pthread.h>
#include "ncurses.h"
using namespace std;
int main(){
    int i = 0;
    cout<<"Hello World\n";
    i++;
    cout<<"Press ENTER to exit...";
    cout<<i;
    cin.get();
}
