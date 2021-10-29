#include<iostream>
#include<fstream>
#include<vector>

namespace constants{
    char name[]="single_state.txt";
    char steps_name[]="steps_state.txt";
}

using namespace std;

void exportState(vector<int> state){
    
    ofstream file;
    file.open(constants::name);

    for(int i = 0; i < state.size();i++){
        file << state[i] << "\t";
    }

    file << endl;

    file.close();
}

void exportSteps(vector<vector<int>> steps){

    ofstream file;
    file.open(constants::steps_name);

    for(int j = 0; j <steps.size();j++){

        vector<int> state = steps[j];

        for(int i = 0; i < state.size();i++){
            
            file << state[i] << "\t";
            
            }
            
        file << endl;
    }

    file.close();
}