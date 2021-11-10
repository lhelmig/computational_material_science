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
void testEnergyChange(){

    vector<int> state = createState(0.5);

    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(0,L*L-1);

    int side = dist6(rng);
    double delta_E = getEnergyChange(side,state);
    double E1 = calcEnergy(state);
    state[side] = flipSide(state[side]);
    double E2 = calcEnergy(state);
    if(delta_E==E2-E1){
        cout << "Test:EnergyChange:True" << endl;
    }else{
        cout << "Test:EnergyChange:False" << endl;
        cout << E2-E1 << endl;
        cout << delta_E << endl;
    }
}

void testFlipping(){

    vector<int> state = createState(1.0);

    bool mistake = false;

    for(int i = 0; i < 100;i++){
        
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<mt19937::result_type> dist6(0,L*L);
        
        int side = dist6(rng);

        if(isFlipped(side,state)==false){
            mistake = true;
        }
    }

    if(mistake){
        cout << "Test:Flipping:False" << endl;
    }else{
        cout << "Test:Flipping:True" << endl;
    }
}
int main(){

    /* testLeftBorder();
    cout << endl;
    testUpperBorder();
    cout << endl;
    testRightBorder();
    cout << endl;
    testLowerBorder(); */

    //testAdjacentSides();

    testEnergyChange();
    testFlipping();

    return 0;
}