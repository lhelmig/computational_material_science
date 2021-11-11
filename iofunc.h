#include<iostream>
#include<fstream>
#include<vector>
#include<string>

namespace constants{
    char name[]="single_state.txt";
    char steps_name[]="steps_state.txt";
}

using namespace std;

void exportState(vector<double> state){
    
    ofstream file;
    file.open(constants::name);

    for(int i = 0; i < state.size();i++){
        file << state[i] << "\t";
    }

    file << endl;

    file.close();
}

void exportSteps(vector<vector<double>> steps){

    ofstream file;
    file.open(constants::steps_name);

    for(int j = 0; j <steps.size();j++){

        vector<double> state = steps[j];

        for(int i = 0; i < state.size();i++){
            
            file << state[i] << "\t";
            
            }
            
        file << endl;
    }

    file.close();
}

void dumpStates(vector<vector<double>> states,double B, double J, double beta){

    string name = "states_B=" + to_string(B) + "_J=" + to_string(J) + "_beta=" + to_string(beta) + ".txt";

    ofstream log(name, ios_base::app | ios_base::out);

    int i = 0;

    while(i<=states.size()-1){

        vector<double> state = states[i];

        for(int j = 0; j < state.size();j++){
            
            log << state[j] << "\t";
            
            }
            
        log << endl;

        i++;

    }
}

void dumpEnergy(vector<double> energy, double B, double J, double beta){

    string name = "energy_B=" + to_string(B) + "_J=" + to_string(J) + "_beta=" + to_string(beta) + ".txt";

    ofstream log(name, ios_base::app | ios_base::out);

    int i = 0;

    while(i<=energy.size()-1){

        log << energy[i] << endl;

        i++;

    }
}

void dumpMagnetization(vector<double> magnetization, double B, double J, double beta){

    string name = "magnetization_B=" + to_string(B) + "_J=" + to_string(J) + "_beta=" + to_string(beta) + ".txt";

    ofstream log(name, ios_base::app | ios_base::out);

    int i = 0;

    while(i<=magnetization.size()-1){

        log << magnetization[i] << endl;

        i++;

    }
}

void dump_Energy_Magnetization(vector<double> energy,vector<double> magnetization, double B, double J, double beta){

    string name = "energy+magnetization_B=" + to_string(B) + "_J=" + to_string(J) + "_beta=" + to_string(beta) + ".txt";

    ofstream log(name, ios_base::app | ios_base::out);

    int i = 0;

    while(i<=energy.size()-1){

        log << energy[i] <<"\t" << magnetization[i] << endl;

        i++;

    }
}
