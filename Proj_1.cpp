#include <iostream>
#include <pthread.h>
#include <vector>
#include "Philosopher.h"
#include "draw.h"

using namespace std;
const int TIME = 3000;
pthread_t* thread;

vector<Philosopher> philosophers; 

void draw(){
    //TODO - Zablokować podczas pisania
    system("clear");
    cout<<"==============================================\n";
    for(Philosopher phil :philosophers){
        cout<<phil.toString();
    }
    cout<<"==============================================\n";
}

int main(int argc,char ** argv){
    if(argc>1){    
        try{
            int numOfPhil = stoi( argv[1] );
            if( numOfPhil > 0 ){
                int numOfChops = numOfPhil;
                for( int i = 0; i < numOfPhil; i++){
                    //TODO - Poprawnie zainicjować tablicę
                    philosophers.push_back(Philosopher());
                }
                draw();
                //TODO - To do pętli
                thread = new pthread_t;
                pthread_create(thread,NULL,Philosopher::runThread,&philosophers[0]);  
            }else{
                cout<<"The number of philosophers given was incorecct\n";
            }
        }catch( invalid_argument e ){
            cout<<"Provided value wasn't a number\n";
        }
    }else{
        cout<<"The number of philosophers was not provided\n";
    }
    // cleanup();
    cout<<"Press ENTER to continue...";
    cin.get();
    return 0;
}

// void cleanup() {
//     for (auto thread : philosophers) {
//         pthread_join(*thread, nullptr);
//         delete thread;  // Free memory allocated for the pthread_t
//     }
// }