#include<iostream>
#include<vector>
#include"util.h"

void testLeftBorder(){
    vector<double> state = createGroundState();

    for(int i = 0; i < state.size(); i++){
        if(isLeftBorder(i)){
            state[i]=0.5;
        }
    }

    visualizeState(state);
}
void testUpperBorder(){
    vector<double> state = createGroundState();

    for(int i = 0; i < state.size(); i++){
        if(isUpperBorder(i)){
            state[i]=0.5;
        }
    }

    visualizeState(state);
}
void testRightBorder(){
    vector<double> state = createGroundState();

    for(int i = 0; i < state.size(); i++){
        if(isRightBorder(i)){
            state[i]=0.5;
        }
    }

    visualizeState(state);
}
void testLowerBorder(){
    vector<double> state = createGroundState();

    for(int i = 0; i < state.size(); i++){
        if(isLowerBorder(i)){
            state[i]=0.5;
        }
    }

    visualizeState(state);
}
void testAdjacentSides(){
    
    vector<double> state = createGroundState();

    for(int i = 0; i < state.size(); i++){
        vector<int> adjacents = adjacentSides(i);
        for(int j = 0; j < adjacents.size();j++){
            state[adjacents[j]]+=1;
        }
    }

    visualizeState(state);
}
void testEnergyChange(){

    vector<double> state = createState(0.5);

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

    vector<double> state = createState(1.0);

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

void testExponentialArray(){

    vector<double> state = createGroundState();

    state[36] = 0.5;
    state[38] = 0.5;
    state[7]=0.5;
    state[9]=0.5;
    state[40]=0.5;
    state[42]=0.5;
    state[73]=0.5;

    // sides 33, 35, 37, 39, 41

    double e1 = getEnergyChange(33,state);
    double e2 = getEnergyChange(35,state);
    double e3 = getEnergyChange(37,state);
    double e4 = getEnergyChange(39,state);
    double e5 = getEnergyChange(41,state);

    //

    state[97] = 0.5;
    state[99] = 0.5;
    state[100] = 0.5;
    state[101] = 0.5;
    state[102] = 0.5;
    state[103] = 0.5;
    state[104] = 0.5;
    state[105] = 0.5;
    state[106] = 0.5;
    state[135] = 0.5;
    state[137] = 0.5;

    // sides  97, 99, 101, 103, 105

    double e6 = getEnergyChange(97,state);
    double e7 = getEnergyChange(99,state);
    double e8 = getEnergyChange(101,state);
    double e9 = getEnergyChange(103,state);
    double e10 = getEnergyChange(105,state);

    double beta = 1;

    initialized_exparray(beta);

    bool test_success = true;

    if(exparray[1][0]!=exp(-e1*beta)){
        test_success = false;
        cout << exparray[1][0] << "\t" << exp(-e1*beta) << endl;
    }
    if(exparray[1][1]!=exp(-e2*beta)){
        test_success = false;
        cout << exparray[1][1] << "\t" << exp(-e2*beta) << endl;
    }
    if(exparray[1][2]!=exp(-e3*beta)){
        test_success = false;
        cout << exparray[1][2] << "\t" << exp(-e3*beta) << endl;
    }
    if(exparray[1][3]!=exp(-e4*beta)){
        test_success = false;
        cout << exparray[1][3] << "\t" << exp(-e4*beta) << endl;
    }
    if(exparray[1][4]!=exp(-e5*beta)){
        test_success = false;
        cout << exparray[1][4] << "\t" << exp(-e5*beta) << endl;
    }
    if(exparray[0][0]!=exp(-e6*beta)){
        test_success = false;
        cout << exparray[0][0] << "\t" << exp(-e6*beta) << endl;
    }
    if(exparray[0][1]!=exp(-e7*beta)){
        test_success = false;
        cout << exparray[0][1] << "\t" << exp(-e7*beta) << endl;
    }
    if(exparray[0][2]!=exp(-e8*beta)){
        test_success = false;
        cout << exparray[0][2] << "\t" << exp(-e8*beta) << endl;
    }
    if(exparray[0][3]!=exp(-e9*beta)){
        test_success = false;
        cout << exparray[0][3] << "\t" << exp(-e9*beta) << endl;
    }
    if(exparray[0][4]!=exp(-e10*beta)){
        test_success = false;
        cout << exparray[0][4] << "\t" << exp(-e10*beta) << endl;
    }

    if(test_success){

        cout << "Test:ExpArray:True" << endl;

    }else{

        cout << "Test:ExpArray:False" << endl;

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
    testExponentialArray();

    return 0;
}