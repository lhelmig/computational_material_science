#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

namespace constants{

    const int L = 32;
    const double B=0;

}

using namespace std;
using namespace constants;

/*
* creates the Ground state with every spin=0 (spin-down)
* Args:
* Returns: vector<int>
*/

vector<int> createGroundState(){

    vector<int> ground_state(L*L);

    return ground_state;
}
/*
*Creates a random state with a specific composition
*Args: p is a double between 0 and 1
*Returns: a state as a vector<32>
*/
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
/*
* visualizes the State by printing out
*Args: State as a vector<int>
*
*/
void visualizeState(vector<int> state){
    for(int i = 0;i < state.size();i++){
        cout<<state[i];
        if((i+1)%L==0){
            cout<<endl;
        }
    }
}
bool isLeftBorder(int i ){
    if(i%L==0){
        return true;
    }
    return false;
}
bool isRightBorder(int i ){
    if((i+1)%L==0){
        return true;
    }
    return false;
}
bool isUpperBorder(int i){
    if(i<L){
        return true;
    }
    return false;
}
bool isLowerBorder(int i){
    if(L*(L-1)<=i && i<L*L){
        return true;
    }
    return false;
}
vector<int> adjacentSides(int i){
    
    vector<int> adjacents;

    if(isLeftBorder(i)){
        adjacents.push_back(i+L-1);
    }else{
        adjacents.push_back(i-1);
    }

    if(isRightBorder(i)){
        adjacents.push_back(i-(L-1));
    }else{
        adjacents.push_back(i+1);
    }

    if(isUpperBorder(i)){
        adjacents.push_back(L*(L-1)+i);
    }else{
        adjacents.push_back(i-L);
    }

    if(isLowerBorder(i)){
        adjacents.push_back(i-L*(L-1));
    }else{
        adjacents.push_back(i+L);
    }

    return adjacents;
}
double calcEnergy(vector<int> state){

    for(int i = 0; i < state.size(); i++){

    }

    return 0;
}