#include <iostream>
#include <pthread.h>
#include <vector>
using namespace std;

vector<pthread_t*> philosophers;

void draw(int numOfPhil){
    cout<<"==============================================\n";
    for( int i = 0; i < numOfPhil; i++){
        cout<<"Philosopher "<<i+1<<" : Waiting"<<"\n";
    }
    cout<<"==============================================\n";
}

void* test(void* arg){
    int id = *(int*)arg;
    cout<<"Phil"<<id<<"\n";
    return nullptr;
}

void init(int numOfPhils,int numOfForks){
    vector<int> phillIDs;
    for( int i = 0; i < numOfPhils; i++){
        phillIDs.push_back(i);
    }
    for( int i = 0; i < numOfPhils; i++){
        philosophers.push_back(new pthread_t);
        pthread_create(philosophers.at(i),NULL,&test,&phillIDs[i]);       
    } 
    draw(numOfPhils);
}

void cleanup() {
    for (auto thread : philosophers) {
        pthread_join(*thread, nullptr);
        delete thread;  // Free memory allocated for the pthread_t
    }
}

int main(int argc,char ** argv){
    if(argc>1){    
        try{
            int numOfPhil = stoi( argv[1] );
            if( numOfPhil > 0 ){
                int numOfForks = numOfPhil;
                init(numOfPhil,numOfForks);
            }else{
                cout<<"The number of philosophers given was incorecct\n";
            }
        }catch( invalid_argument e ){
            cout<<"Provided value wasn't a number\n";
        }
    }else{
        cout<<"The number of philosophers was not provided\n";
    }
    cleanup();
    cout<<"Press ENTER to continue...";
    cin.get();
    return 0;
}
