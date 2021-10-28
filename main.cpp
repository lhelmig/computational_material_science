

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "util.h"

namespace constants{

    //const int L = 32;
    //const int J = 1;

}

using namespace std;
using namespace constants;

/*
* creates the Ground state with every spin=0 (spin-down)
* Args:
* Returns: vector<int>
*/
/*
vector<int> createGroundState(){

    vector<int> ground_state(L*L);

    return ground_state;
}
*/
/*
*Creates a random state with a specific composition
*Args: p is a double between 0 and 1
*Returns: a state as a vector<32>
*/
/*
vector<int> createState(double p){
   vector<int> state(L*L);

    for(int i = 0; i <p*L*L;i++){
        state[i]=1;
    }

    random_device rd;
    mt19937 g(rd());
    shuffle(state.begin(), state.end(), g);

    return state;
}
*/
/*
* visualizes the State by printing out
*Args: State as a vector<int>
*
*/
/*
void visualizeState(vector<int> state){
    for(int i = 0;i < state.size();i++){
        cout<<state[i];
        if((i+1)%L==0){
            cout<<endl;
        }
    }
}
*/


int main(){
    vector<int> state = createState(0.5);
    visualizeState(state);
}