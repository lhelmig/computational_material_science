#include<iostream>
#include<vector>
#include"util.h"

void testLeftBorder(){
    vector<int> state(L*L);

    for(int i = 0; i < state.size(); i++){
        if(isLeftBorder(i)){
            state[i]=1;
        }
    }

    visualizeState(state);
}
void testUpperBorder(){
    vector<int> state(L*L);

    for(int i = 0; i < state.size(); i++){
        if(isUpperBorder(i)){
            state[i]=1;
        }
    }

    visualizeState(state);
}
void testRightBorder(){
    vector<int> state(L*L);

    for(int i = 0; i < state.size(); i++){
        if(isRightBorder(i)){
            state[i]=1;
        }
    }

    visualizeState(state);
}
void testLowerBorder(){
    vector<int> state(L*L);

    for(int i = 0; i < state.size(); i++){
        if(isLowerBorder(i)){
            state[i]=1;
        }
    }

    visualizeState(state);
}
void testAdjacentSides(){
    
    vector<int> state(L*L);

    for(int i = 0; i < state.size(); i++){
        vector<int> adjacents = adjacentSides(i);
        for(int j = 0; j < adjacents.size();j++){
            state[adjacents[j]]+=1;
        }
    }

    visualizeState(state);
}
int main(){

    /* testLeftBorder();
    cout << endl;
    testUpperBorder();
    cout << endl;
    testRightBorder();
    cout << endl;
    testLowerBorder(); */

    testAdjacentSides();

    return 0;
}