#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <map>

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

void exportSteps(vector<vector<double> > steps){

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

void dumpStates(vector<vector<double> > states,double B, double J, double beta){

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

void dump_average_Energy_Magnetization(vector<double> beta,vector<double> average_energy,vector<double> average_magnetization, double B, double J){

    string name = "beta_energy+magnetization_B=" + to_string(B) + "_J=" + to_string(J) + ".txt";

    ofstream log(name, ios_base::app | ios_base::out);

    int i = 0;

    while(i<=average_energy.size()-1){

        log << beta[i] << "\t" << average_energy[i] << "\t" << average_magnetization[i] << endl;

        i++;

    }
}

void dump_average_Energy_MagnetizationMultithread(vector<double> beta,vector<double> average_energy,vector<double> average_magnetization, double B, double J,string additional_identifier){

    string name = additional_identifier + "_beta_energy+magnetization_B=" + to_string(B) + "_J=" + to_string(J) + ".txt";

    ofstream log(name, ios_base::app | ios_base::out);

    int i = 0;

    while(i<=average_energy.size()-1){

        log << beta[i] << "\t" << average_energy[i] << "\t" << average_magnetization[i] << endl;

        i++;

    }
}
void dump_Prob_Distr(int prob_distr[],double B, double J, double beta, int total_number_measurements){

    string name = "prob_distr_magnetization_N="+ to_string(total_number_measurements)+ "_beta="+ to_string(beta) + "_B=" + to_string(B) + "_J=" + to_string(J) + ".txt";

    ofstream log(name, ios_base::app | ios_base::out);

    for(int i =-512;i<=512;i++){

        cout << "this is " << i << "\t" << prob_distr[i+512] <<endl;

        log << i << "\t" << float(prob_distr[i+512])/float(total_number_measurements) << endl;
        
    }
}


