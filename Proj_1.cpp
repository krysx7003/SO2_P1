#include <iostream>
#include <pthread.h>
#include <vector>
#include <random>
#include <unistd.h>
#include <mutex>
#include "Chopstick.h"
#include "Philosopher.h"

using namespace std;
const int MAX_TIME = 5;
const int US_TO_S = 1000000;

mutex out;
int numOfPhil = 5;
int numOfChops = numOfPhil;
bool threadAssigned = false;

vector<mutex> chopMtx;
vector<Chopstick*> chopsticks;
vector<pthread_t> threads;
vector<Philosopher> philosophers; 

string header(){
    ostringstream oss; 
    oss << "Philosopher: " << setw(3) << "ID" << " | " 
        << setw(5) << "ID_C1" << " | " 
        << setw(5) << "ID_C1" << " | " 
        << setw(12) << "STATE" << " |\n";
    return oss.str();
}
void draw(){
    system("clear");
    cout<<"=============================================\n";
    cout<<header();
    cout<<"=============================================\n";
    for(Philosopher phil :philosophers){
        cout<<phil.toString();
    }
    cout<<"=============================================\n";
    cout<<"Press ENTER to stop...\n";
}
void think(int i){
    philosophers[i].myState = PhilState::THINKING;
    {
        lock_guard<mutex> lock(out);
        cout<<philosophers[i].id<<"\n";
        draw();
    }
    usleep(( rand()%MAX_TIME+1 ) * US_TO_S );
}
void takeChop(int i){
    philosophers[i].myState = PhilState::HUNGRY;
    if(!philosophers[i].boothLocked){
        int leftId = philosophers[i].left;
        int rightId = philosophers[i].right;
        chopMtx[leftId].lock();
        philosophers[i].setLeftChop(leftId);
        while( chopMtx[rightId].try_lock() == false ){
            chopMtx[leftId].unlock();
            philosophers[i].setLeftChop(-1);
            usleep(1000);
            chopMtx[leftId].lock();
        }
        philosophers[i].setLeftChop(leftId);
        philosophers[i].setRightChop(rightId);
        philosophers[i].boothLocked = true;
    }
    {
        lock_guard<mutex> lock(out);
        cout<<philosophers[i].id<<"\n";
        draw();
    }
}
void eat(int i){
    philosophers[i].myState = PhilState::EATING;
    {
        lock_guard<mutex> lock(out);
        cout<<philosophers[i].id<<"\n";
        draw();
    }
    usleep(( rand()%MAX_TIME+1 ) * US_TO_S );
}
void returnChop(int i){
    philosophers[i].setLeftChop(-1);
    chopMtx[philosophers[i].left].unlock();

    philosophers[i].setRightChop(-1);
    chopMtx[philosophers[i].right].unlock();
    philosophers[i].boothLocked = false;
    {
        lock_guard<mutex> lock(out);
        cout<<philosophers[i].id<<"\n";
        draw();
    }
}
void* run(void* arg){
    int i = *( static_cast<int*>(arg) );
    delete static_cast<int*>(arg); 
    if( i == 0 ){
        philosophers[0].setLeftChop(philosophers[0].left);
        chopMtx[philosophers[0].left].lock();
        philosophers[0].setRightChop(philosophers[0].right);
        chopMtx[philosophers[0].right].lock();
        philosophers[0].boothLocked = true;
        draw();
    }
    while (true){
        think(i);
        takeChop(i);
        eat(i);
        returnChop(i);
    }
    return nullptr; 
}
void cleanup(vector<pthread_t> threads) {
    for (auto thread : threads) {
        pthread_cancel(thread);
        pthread_join(thread, nullptr);
    }
    cout<<"Threads stopped\n";
}
int main(int argc,char ** argv){
    if(argc>1){    
        try{
            numOfPhil = stoi( argv[1] );
            if( numOfPhil > 0 ){
                numOfChops = numOfPhil;
                threads.resize(numOfPhil);
                threadAssigned = true;
                vector<mutex> newMtxs(numOfPhil);
                chopMtx.swap(newMtxs);
                for( int i = 0; i < numOfPhil; i++){
                    chopsticks.push_back(new Chopstick(i));
                    philosophers.push_back(Philosopher(i,numOfPhil));
                }
                draw();
                for( int i = 0; i < numOfPhil; i++){
                    int* id = new int(i); 
                    pthread_create(&threads[i],NULL,run,id);  
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
    cin.get();
    if(threadAssigned){
        cleanup(threads);
    }
    cout<<"Press ENTER to exit...\n";
    cin.get();
    return 0;
}

