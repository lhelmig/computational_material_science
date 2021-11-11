

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "util.h"

using namespace std;
using namespace constants;

int main(){

    vector<double> state = createState(0);

    
    //visualizeState(state);

    /* vector<vector<int>> states;
    
    for(int i=0; i <= 10; i++){

        states.push_back(createState(1.0*i/10));

    }

    dumpStates(states,0,0,1); */

    algoMetropolis(state,2000,100);
}