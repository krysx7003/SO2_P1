#include <iostream>
#include <pthread.h>
#include <vector>
#include <random>
#include <unistd.h>
#include <mutex>
#include "Philosopher.h"
#include "draw.h"

using namespace std;
const int MAX_TIME = 5;
const int US_TO_S = 1000000;
mutex out;
bool threadAssigned = false;
bool contiuneRunning = true;

vector<Chopstick*> chopsticks;
vector<pthread_t> threads;
vector<Philosopher> philosophers; 

string header(){
    ostringstream oss; 
    oss << "Philosopher: " << setw(3) << "ID" << " | " 
        << setw(3) << "ID" << " | " 
        << setw(3) << "ID" << " | " 
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
    philosophers[i].myState = State::THINKING;
    {
        lock_guard<mutex> lock(out);
        cout<<philosophers[i].id<<"\n";
        draw();
    }
    usleep(( rand()%MAX_TIME+1 ) * US_TO_S );
}
void takeChop(int i){
    philosophers[i].myState = State::HUNGRY;
    {
        lock_guard<mutex> lock(out);
        cout<<philosophers[i].id<<"\n";
        draw();
    }
    draw();
}
void eat(int i){
    philosophers[i].myState = State::EATING;
    {
        lock_guard<mutex> lock(out);
        cout<<philosophers[i].id<<"\n";
        draw();
    }
    usleep(( rand()%MAX_TIME+1 ) * US_TO_S );
}
void returnChop(int i){

}
void* run(void* arg){
    int i = *( static_cast<int*>(arg) );
    delete static_cast<int*>(arg); 
    while (contiuneRunning){
        think(i);
        takeChop(i);
        eat(i);
        returnChop(i);
    }
}
void cleanup(vector<pthread_t> threads) {
    for (auto thread : threads) {
        pthread_join(thread, nullptr);
    }
}
int main(int argc,char ** argv){
    if(argc>1){    
        try{
            int numOfPhil = stoi( argv[1] );
            if( numOfPhil > 0 ){
                int numOfChops = numOfPhil;
                threads.resize(numOfPhil);
                threadAssigned = true;
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
    contiuneRunning = false;
    cleanup(threads);
    return 0;
}

