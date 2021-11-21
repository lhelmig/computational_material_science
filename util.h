#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono> 
#include <ctime>
#include <thread>

#include"iofunc.h"

namespace constants{

    const int L = 32;                //Latice size
    const double B = 0;               //Magneticfield constant    
    const double J = 1;             //Spin-spin-coppling
    const double beta = 1;          //parameter for temperature
    const double time_between_logs = 100;   
    vector<vector<double>> exparray;
}

using namespace std;
using namespace constants;

/*


Convention exparray[0 for spin up, 1 for spin down][numbers of neighbors with Spin Up]
Initialize a vector for the differenze energy (exp(DeltaE*beta))
*/
void initialized_exparray(double beta){

    exparray={};      
    
    vector<vector<double>> delta_E{
        {-4 * 0.5 * -2 , -4 * 0.5 * -1 , -4 * 0.5 * 0 , -4 * 0.5 * 1 , -4 * 0.5 * 2},
        {-4 * -0.5 * -2 , -4 * -0.5 * -1 , -4 * -0.5 * 0 , -4 * -0.5 * 1 , -4 * -0.5 * 2}
    };

    for(int i = 0; i < 2; i++){
        vector<double>temp;
        for(int j = 0; j < 5; j++){
            temp.push_back(exp(-delta_E[i][j]*beta));
        }
        exparray.push_back(temp);
        
    }

}

//Function to flip the spin
double flipSide(double side_value){

    if(side_value== -0.5){
        return 0.5;
    }else{
        return -0.5;
    }
}

/*
* creates the Ground state with every spin=0 (spin-down)
* Args:
* Returns: vector<int>
*/

vector<double> createGroundState(){

    vector<double> ground_state(L*L);

    for(int i = 0; i < ground_state.size(); i++){
        ground_state[i] = -0.5;
    }

    return ground_state;
}
/*
*Creates a random state with a specific composition
*Args: p is a double between 0 and 1
*Returns: a state as a vector<32>
*/
vector<double> createState(double p){
    
    vector<double> state = createGroundState();

    for(int i = 0; i <p*L*L;i++){
        state[i]+=1;
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
void visualizeState(vector<double> state){
    for(int i = 0;i < state.size();i++){
        cout<<state[i]+0.5;
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
//count the adjacent spin up's for a side
int countAdjacentSpinUps(int side, vector<double> state){

    vector<int> adjacent = adjacentSides(side);

    int k=0;

    for(int i = 0; i < adjacent.size(); i++){
        if(state[adjacent[i]]==0.5){
            k += 1;
        }
    }

    return k;
}

/*
Calculate the energy of the system using the Hamilton function

Energie: E= J [m_si * m_sj + m_si * m_sk ......]
hbar=1 ;
Args: state as a vector<int>
Returns the Energie of the whole system

*/
double calcEnergy(vector<double> state){

    // Wechselwirkungsenergie der Spins

    double wwE = 0;

    // potentielle Energie im Magnetfeld B
    
    double BE = 0; //
    
    //vector<float> eigenvalues = getEigenvalues(state);

    for(int i = 0; i < state.size(); i++){

        BE += state[i];
        
        vector<int> adjacents = adjacentSides(i);

        for(int j = 0; j < adjacents.size(); j++){

            wwE = wwE + state[i] * state[adjacents[j]];

        }  
    }
    wwE = wwE * J;
    
    return wwE+B*BE;
}

/*
Calculate the magnetization of the system using the Hamilton function
Args: state as a vector<int>
Returns the magnetization of the whole system

*/
double calcMagnetization(vector<double> state){

     // Magnetisierung

    double m = 0;

    for(int i = 0; i < state.size(); i++){

        m += state[i];

    }
    
    return m;
}

/*
Combined function to reduce runtime

*/
vector<double> calc_Energy_Magnetization(vector<double> state){

    // Magnetisierung

    double m = 0;

    // Wechselwirkungsenergie der Spins

    double wwE = 0;

    // potentielle Energie im Magnetfeld B
    
    double BE = 0; //
    
    //vector<float> eigenvalues = getEigenvalues(state);

    for(int i = 0; i < state.size(); i++){

        BE += state[i];
        
        vector<int> adjacents = adjacentSides(i);

        for(int j = 0; j < adjacents.size(); j++){

            wwE = wwE + state[i] * state[adjacents[j]];

        }  
    }
    wwE = wwE * J;

    double E = wwE + B*BE;

    m = BE;

    vector<double> results{E,m};
    
    return results;
}

/**
 calculates the energy change when one side is flipped
 Args: side to be flipped as an integer, current state as a vector
 Returns the energy change as a double 
 */

double getEnergyChange(int side, vector<double> state){

    double delta_E = 0;

    vector<int> adjacents = adjacentSides(side);

    double sum = 0;

    for(int j = 0; j < adjacents.size();j++){

        sum += state[adjacents[j]];

    }

    if(state[side]==0.5){
        delta_E = -2*sum;
    }else{
        delta_E = 2*sum;
    }

    return delta_E;
}

/*
determines if the spin on a side is flipped or not
Args: index of side as an integer, state as a vector
Returns a boolean: true when the spin is flipped and false if not
*/
bool isFlipped(int side, vector<double> state){
    
    double delta_E = getEnergyChange(side, state);

    random_device dev;
    mt19937 rng(dev());
    uniform_real_distribution<> dist(0.0,1.0);

    float r = dist(rng);

    if(r<exp(-delta_E*constants::beta)){
        return true;
    }else{
        return false;
    }

}

/*
determines if the spin on a side is flipped or not
Args: index of side as an integer, state as a vector
Returns a boolean: true when the spin is flipped and false if not
*/

bool isFlipped(int side, vector<double> state, double beta){

    int k = countAdjacentSpinUps(side,state);
    
    double exp;

    if(state[side] == 0.5){
        exp = exparray[0][k];
    }else{
        exp = exparray[1][k];
    }

    random_device dev;
    mt19937 rng(dev());
    uniform_real_distribution<> dist(0.0,1.0);

    float r = dist(rng);

    if(r<exp){
        return true;
    }else{
        return false;
    }

}

/*



*/
void algoMetropolis(vector<double> state, int N, int k){

    vector<double> energy;
    vector<double> magnetization;
    vector<vector<double> > states;
     
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(0,L*L-1);

    auto start = chrono::system_clock::now();
    initialized_exparray(constants::beta);

    for(int i = 0; i < N;i++){

        for(int j = 0; j < k; j++){

            // Choose an initial side

            int side = dist6(rng);

            if(isFlipped(side,state)){
                state[side]= flipSide(state[side]);
            }

        }
        //Ladebalken
        cout << i << "/" << N << endl;
        // Measure

        vector<double> copystate = state;
        states.push_back(copystate);

        vector<double> results = calc_Energy_Magnetization(state);
        
        energy.push_back(results[0]);
        magnetization.push_back(results[1]);

        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end-start;

        if(elapsed_seconds.count() > time_between_logs){

            start = end;

            dump_Energy_Magnetization(energy, magnetization,B,J,constants::beta);
            //dumpStates(states,B,J,constants::beta);

            energy = {};
            magnetization = {};
            states = {};

        }


    }

    dump_Energy_Magnetization(energy, magnetization,B,J,constants::beta);
    //dumpStates(states,B,J,constants::beta);
}


/*



*/

vector<double> algoMetropolisDirectAveraging(vector<double> state, double beta, int N, int k, double dE, int deviationcount){

    double energy = 0;
    double magnetization = 0;
    int g = 0;
    double average_energy = 0;
     
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(0,L*L-1);
    initialized_exparray(beta);
    for(int i = 0; i < N;i++){


        for(int j = 0; j < k; j++){

            // Choose an initial side

            int side = dist6(rng);

            if(isFlipped(side,state,beta)){
                state[side]= flipSide(state[side]);
            }

        }
        // Measure
        vector<double> results = calc_Energy_Magnetization(state);
            
        energy+=results[0];
        magnetization+=results[1];

        //Abbruchbedingung

        double average_energy_before = average_energy;
        average_energy = energy/(i+1);
        double measure_dE = abs(average_energy_before - average_energy);
        double percentage_deviation = measure_dE / abs(average_energy);

        //cout << percentage_deviation << endl;
        
            if(percentage_deviation < dE){
                g = g + 1;
            }else{
                g=0;
            }
        
        if(g == deviationcount){
            cout << i << endl;
            i=N;
        }
    }
    energy = energy/(N);
    magnetization = magnetization/(N);

    vector<double> result{energy,magnetization};

    return result;
}

void algoMetropolisTemperature(vector<double> state,double beta_min, double beta_max, int N, int k, int number_discrete_points, double dE, int deviationcount){

    double delta_beta = (beta_max-beta_min)/number_discrete_points;

    vector<double> interval_beta;
    vector<double> average_energy;
    vector<double> average_magnetization;

    for(int i = 0; i < number_discrete_points; i++){

        double actual_beta = beta_min + i * delta_beta;

        vector<double> result = algoMetropolisDirectAveraging(state,actual_beta,N,k,dE,deviationcount);

        cout << i << "/" << number_discrete_points << endl;

        interval_beta.push_back(actual_beta);
        average_energy.push_back(result[0]);
        average_magnetization.push_back(result[1]);
    }

    dump_average_Energy_Magnetization(interval_beta,average_energy,average_magnetization,constants::B,constants::J);

}
/*
void algoMetropolisTemperatureMultithread(vector<double> state,double beta_min, double beta_max, int N, int k, string additional_identifier){

    int number_discrete_points = 100;

    double delta_beta = (beta_max-beta_min)/number_discrete_points;

    vector<double> interval_beta;
    vector<double> average_energy;
    vector<double> average_magnetization;

    for(int i = 0; i < number_discrete_points; i++){

        double actual_beta = beta_min + i * delta_beta;

        vector<double> result = algoMetropolisDirectAveraging(state,actual_beta,N,k);

        cout << i << "/" << number_discrete_points << endl;

        interval_beta.push_back(actual_beta);
        average_energy.push_back(result[0]);
        average_magnetization.push_back(result[1]);
    }

    dump_average_Energy_MagnetizationMultithread(interval_beta,average_energy,average_magnetization,constants::B,constants::J,additional_identifier);

}

void algoMetropolisMultithread(vector<double> state,double beta_min, double beta_max, int N, int k){

    const auto processor_count = std::thread::hardware_concurrency();

    cout << processor_count << endl;

    int max_processor_count = 6;

    int number_threads = 0;

    if(((int)processor_count)<max_processor_count){

        max_processor_count=(int)processor_count;

    }

    double beta_diff = (beta_max-beta_min)/(max_processor_count);

    vector<thread> threads(max_processor_count);

    for(int i = 0; i < max_processor_count;i++){

        string name = "thread" + to_string(i);

        double thread_beta_min = beta_min + i*beta_diff;
        double thread_beta_max = beta_min + (i+1)*beta_diff;

        threads[i]= thread(algoMetropolisTemperatureMultithread,state,thread_beta_min,thread_beta_max,N,k,name);
    }

    for (auto& th : threads) {
        th.join();
    }
}
*/