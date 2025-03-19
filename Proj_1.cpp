#include <iostream>
#include <pthread.h>
using namespace std;

pthread_t* philosophers;

void draw(int numOfPhil){
    cout<<"==============================================\n";
    for( int i = 0; i < numOfPhil; i++){
        cout<<"Philosopher "<<i+1<<" : Waiting"<<"\n";
    }
    cout<<"==============================================\n";
}

void* test(void* arg){

    pthread_detach(pthread_self());
    
    cout<<arg<<"\n";

    pthread_exit(NULL);
}

void init(int numOfPhil,int numOfForks){
    for( int i = 0; i < numOfPhil; i++){
        //pthread_create(philosophers[i],NULL,&test,i);       
    } 
    draw(numOfPhil);
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
    cout<<"Press ENTER to continue...";
    cin.get();
    return 0;
}
