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
/*
checks if side i is at the left border
Args: position of side i in the vector
*/
bool isLeftBorder(int i ){
    if(i%L==0){
        return true;
    }
    return false;
}
/*
checks if side i is at the right border
Args: position of side i in the vector
*/
bool isRightBorder(int i ){
    if((i+1)%L==0){
        return true;
    }
    return false;
}
/*
checks if side i is at the upper border
Args: position of side i in the vector
*/
bool isUpperBorder(int i){
    if(i<L){
        return true;
    }
    return false;
}
/*
checks if side i is at the lower border
Args: position of side i in the vector
*/
bool isLowerBorder(int i){
    if(L*(L-1)<=i && i<L*L){
        return true;
    }
    return false;
}
/*
Determines the adjacent sides of a side i
Args: Side i at position i in the vector
Returns: indices of the four adjacent sides
*/
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

/*
Calculate the eigenvaluese regarding /sigma_z (pauli)
Args: state as a vector<int>
returns a vector named eigenvalues
*/
vector<float> getEigenvalues(vector<int> state){

    vector<float> eigenvalues(L*L);

    for(int i = 0; i < state.size(); i++){
        
        if(state[i] == 1){
            eigenvalues[i] = 0.5;
        }
        else{
            eigenvalues[i] = -0.5;
        }
    }

    return eigenvalues;
}


/*
Calculate the energy of the system using the Hamilton function


*/
double calcEnergy(vector<int> state){

    for(int i = 0; i < state.size(); i++){

    }

    return 0;
}
