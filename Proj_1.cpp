#include <iostream>
#include <pthread.h>
#include <vector>
#include <random>
#include <signal.h>
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

void signalHandler(int signum) {
    pthread_exit(nullptr); 
}
string header(){
    ostringstream oss; 
    oss << "Philosopher: " << setw(3) << "ID" << " | " 
        << setw(5) << "ID_C1" << " | " 
        << setw(5) << "ID_C2" << " | " 
        << setw(12) << "STATE" << " | "
        << setw(5) << "T" << " | " 
        << setw(5) << "E" << " | " 
        << setw(5) << "H" << " |\n" ;
    return oss.str();
}
void draw(){
    system("clear");
    cout<<"=========================================================================\n";
    cout<<header();
    cout<<"=========================================================================\n";
    for(Philosopher phil :philosophers){
        cout<<phil.toString();
    }
    cout<<"=========================================================================\n";
    cout<<"Press ENTER to stop...\n";
}
void think(int i){
    philosophers[i].myState = PhilState::THINKING;
    philosophers[i].timesThinking++;
    {
        lock_guard<mutex> lock(out);
        draw();
    }
    usleep(( rand()%MAX_TIME+1 ) * US_TO_S );
}
void takeChop(int i){
    philosophers[i].myState = PhilState::HUNGRY;
    philosophers[i].timesHungry++;
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
    {
        lock_guard<mutex> lock(out);
        draw();
    }
}
void eat(int i){
    philosophers[i].myState = PhilState::EATING;
    philosophers[i].timesEating++;
    {
        lock_guard<mutex> lock(out);
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
        draw();
    }
}
void* run(void* arg){
    int i = *( static_cast<int*>(arg) );
    delete static_cast<int*>(arg);
    signal(SIGTERM, signalHandler); 
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
        pthread_kill(thread,SIGTERM);
    }
    for (auto thread : threads) {
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

