#include <iostream>
#include <pthread.h>
#include <vector>
#include "Philosopher.h"
#include "draw.h"

using namespace std;
const int TIME = 3000;

mutex out;

vector<Chopstick*> chopsticks;
vector<Philosopher> philosophers; 

void draw(){
    // system("clear");
    cout<<"==============================================\n";
    for(Philosopher phil :philosophers){
        cout<<phil.toString();
    }
    cout<<"==============================================\n";
}

// void cleanup() {
//     for (auto thread : threads) {
//         pthread_join(*thread, nullptr);
//         delete thread;  
//     }
// }
int main(int argc,char ** argv){
    if(argc>1){    
        try{
            int numOfPhil = stoi( argv[1] );
            if( numOfPhil > 0 ){
                int numOfChops = numOfPhil;
                vector<pthread_t> threads(numOfPhil);
                for( int i = 0; i < numOfPhil; i++){
                    chopsticks.push_back(new Chopstick(i));
                    philosophers.push_back(Philosopher(i,numOfPhil,&out));
                }
                draw();
                for( int i = 0; i < numOfPhil; i++){
                    pthread_create(&threads[i],NULL,Philosopher::runThread,&philosophers[i]);  
                }
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

