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
    const double beta = 5;          //parameter for temperature
    const double time_between_logs = 100;   
    vector<vector<double> > exparray;
}

using namespace std;
using namespace constants;

/*


Convention exparray[0 for spin up, 1 for spin down][numbers of neighbors with Spin Up]
Initialize a vector for the differenze energy (exp(DeltaE*beta))
*/

/**
 * @brief initializes the exponential expression of the Metropolis algorithm to reduce computation time. array needs
 * to be initialized for each new temperature
 * 
 * @param beta temperature beta for the simulation
 */

void initialized_exparray(double beta){

    exparray={};      
    
    vector<vector<double> > delta_E{
        {(-2 * J )*(-1)*(-2) - B * (-1) , (-2*J) *(-1)*(-1) - B * (-1), (-2 * J )*(-1)*(0) - B * (-1), (-2 * J )*(-1)*(1) - B * (-1) , (-2 * J )*(-1)*(2) - B * (-1)},
        {(-2 * J )*(1)*(-2) - B * (1) , (-2 * J )*(1)*(-1) - B * (1) , (-2 * J )*(1)*(0) - B * (1), (-2 * J )*(1)*(1) - B * (1), (-2 * J )*(1)*(2) - B * (1)}
    };

    for(int i = 0; i < 2; i++){
        vector<double>temp;
        for(int j = 0; j < 5; j++){
            temp.push_back(exp(-delta_E[i][j]*beta));
        }
        exparray.push_back(temp);
        
    }

}

/**
 * @brief Creates a ground state, vector of doubles, -0.5 is spin down
 * 
 * @return vector<double> 
 */
vector<double> createGroundState(){

    vector<double> ground_state(L*L);

    for(int i = 0; i < ground_state.size(); i++){
        ground_state[i] = -0.5;
    }

    return ground_state;
}

/**
 * @brief Creates a system state as a 1d vector of doubles, mixed spin ups and downs
 * 
 * @param p occupation percentage of sites with spin up
 * @return vector<double> state with random distribution of spin ups and downs meeting the occupation percentage p
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

/**
 * @brief visualizes a state by printing it to the console
 * 
 * @param state state that is visualized
 */

void visualizeState(vector<double> state){
    for(int i = 0;i < state.size();i++){
        cout<<state[i]+0.5;
        if((i+1)%L==0){
            cout<<endl;
        }
    }
}

/**
 * @brief checks if a site is at the left border
 * 
 * @param i site to check
 * @return true is in the left border
 * @return false is not in the left border
 */

bool isLeftBorder(int i ){
    if(i%L==0){
        return true;
    }
    return false;
}

/**
 * @brief checks if a site is at the right border
 * 
 * @param i site to check
 * @return true is in the right border
 * @return false is not in the right border
 */

bool isRightBorder(int i ){
    if((i+1)%L==0){
        return true;
    }
    return false;
}

/**
 * @brief checks if a site is at the upper border
 * 
 * @param i site to check
 * @return true is in the upper border
 * @return false is not in the upper border
 */

bool isUpperBorder(int i){
    if(i<L){
        return true;
    }
    return false;
}

/**
 * @brief checks if a site is at the lower border
 * 
 * @param i site to check
 * @return true is in the lower border
 * @return false is not in the lower border
 */

bool isLowerBorder(int i){
    if(L*(L-1)<=i && i<L*L){
        return true;
    }
    return false;
}

/**
 * @brief Determines the adjacent sides of a side i, because the square lattice is represented as a 1d array
 * 
 * @param i site to calculate the neighbours
 * @return vector<int> array of adjacent sites in the lattice
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

/**
 * @brief count the number of adjacent (top, bottom, left, right) spin ups for a site
 * 
 * @param side specific site
 * @param state state to check the adjacent sites
 * @return int number of spin ups (min = 0, max = 4)
 */

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

/**
 * @brief Calculates the energy of the system using the Hamiltonian
 * 
 * @param state state that the energy is calculated for
 * @return double returns the energy of the state
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
    
    wwE = -wwE * J;
    
    return wwE-B*BE;
}

/**
 * @brief Calculates the magnetization of the system using the Hamiltonian
 * 
 * @param state state that the magnetization is calculated for
 * @return double magnetization of the state
 */

double calcMagnetization(vector<double> state){

     // Magnetisierung

    double m = 0;

    for(int i = 0; i < state.size(); i++){

        m += state[i];

    }
    
    return m;
}

/**
 * @brief calculates the energy and magnetization of a state, combined
 * 
 * @param state state that the energy and magnetization is calculated for
 * @return vector<double> returns at position 0 the energy and at position 1 the magnetization
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
    wwE = -wwE * J;

    double E = wwE - B*BE;

    m = BE;

    vector<double> results{E,m};
    
    return results;
}

/**
 * @brief calculates the energy change when one site is flipped
 * 
 * @param side position of the spin that is potentially flipped
 * @param state specific state to check for
 * @return double energy change that results from a spin flip for the state
 */

double getEnergyChange(int side, vector<double> state){

    double delta_E = 0;

    vector<int> adjacents = adjacentSides(side);

    double sum = 0;

    for(int j = 0; j < adjacents.size();j++){

        sum += state[adjacents[j]];

    }

    if(state[side]==0.5){
        delta_E = 2*J*sum-B;
    }else{
        delta_E = -2*J*sum+B;
    }

    return delta_E;
}

/**
 * @brief determines if the flip attempt of a spin at a position is successful
 * 
 * @param side position of the spin in the lattice (from 0 to L^2)
 * @param state specific state to check
 * @return true the spin is flipped
 * @return false the spin remains unflipped
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

/**
 * @brief determines if the flip attempt of a spin at a position is successful, shorter calculation
 * 
 * @param side position of the spin in the lattice (from 0 to L^2)
 * @param state specific state to check
 * @param beta temperature
 * @return true the spin is flipped
 * @return false the spin remains unflipped
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

/**
 * @brief Simulation of the system for a fixed temperature beta, uses the original Metropolis algorithm, writes the result to a file
 * 
 * @param state the simulation starts with this state. Vector of doubles with size 1024
 * @param N number of measurements
 * @param k number of attempted spin flips between each measurement
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

                // Wert invertieren

                state[side]= -state[side];
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

/**
 * @brief Uses the original Metropolis algorithm to simulate the Ising-Model, stops simulation when the energy after a specific amount of
spin flips and when the precision is met
 * 
 * @param state the simulation starts with this state. Vector of doubles with size 1024
 * @param beta temperature of the simulation
 * @param N number of measurements
 * @param k number of attempted spin flips between each measurement
 * @param precision precision of the energy, simulation is stopped when the goal is reached
 * @return vector<double> returns an array where position 0 holds the energy and position 1 the magnetization
 */

vector<double> algoMetropolisDirectAveraging(vector<double> state, double beta, int N, int k, double precision){

    int check_if_near_eq = 10; // nach 10 lines überprüfen ob in der Nähe des Eq
    int stop = 20; // stops the simulation after being near eq 5 times in a row
    double energy = 0;
    double magnetization = 0;

    int number_of_flips = 0;
    
    int conseq_near_eq = 0;

    double average_energy = 0;

    bool near_eq = false;
     
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(0,L*L-1);
    initialized_exparray(beta);
    for(int i = 0; i < N && !near_eq;i++){


        for(int j = 0; j < k; j++){

            // Choose an initial side

            int side = dist6(rng); // checked, immer zufällige Spins

            if(isFlipped(side,state,beta)){

                // Wert invertieren

                state[side]= -state[side];
            }

        }
        // Measure
        vector<double> results = calc_Energy_Magnetization(state);

        if(i%check_if_near_eq==0 && number_of_flips > L*L){

            average_energy = energy/(i);

            double rel_err = abs(results[0]-average_energy)/average_energy;

            if(rel_err < precision){
                
                
                conseq_near_eq += 1;

            }else{

                conseq_near_eq = 0;

            }
        }

        if (conseq_near_eq == stop ){
            
            near_eq = true;

            cout << "near eq: continuing with next beta" << endl;
            
            }
        
            
        energy+=results[0];
        magnetization+=results[1];
        
    }
    energy = energy/(N);
    magnetization = magnetization/(N);

    vector<double> result{energy,magnetization};

    return result;
}
/**
 * @brief calculates the average magnetization and energy for a temperature interval, uses the Metropolis algorithm, writes 
 * the result to a file
 * 
 * @param state the simulation starts with this state. Vector of doubles with size 1024
 * @param beta_min lower bound of the temperature interval
 * @param beta_max upper bound of the temperature interval
 * @param N number of measurements
 * @param k number of attempted spin flips between each measurement
 * @param number_discrete_points number of datapoints in the interval
 * @param precision  precision of the energy, simulation is stopped when the goal is reached
 */

void algoMetropolisTemperature(vector<double> state,double beta_min, double beta_max, int N, int k, int number_discrete_points, double precision){

    double delta_beta = (beta_max-beta_min)/number_discrete_points;

    vector<double> interval_beta;
    vector<double> average_energy;
    vector<double> average_magnetization;

    for(int i = 0; i < number_discrete_points; i++){

        double actual_beta = beta_min + i * delta_beta;

        vector<double> result = algoMetropolisDirectAveraging(state,actual_beta,N,k,precision);

        cout << i << "/" << number_discrete_points << endl;

        interval_beta.push_back(actual_beta);
        average_energy.push_back(result[0]);
        average_magnetization.push_back(result[1]);
    }

    dump_average_Energy_Magnetization(interval_beta,average_energy,average_magnetization,constants::B,constants::J);

}
/**
 * @brief Calculates the probability distribution of the magnetization for a fixed beta
 * 
 * @param state simulation starts with this. Vector of double with size 1024
 * @param beta inverse temperature of the simulation
 * @param N number of measurements
 * @param k attempted spin flips between each measurements
 * @param precision precision of the energy, simulation is stopped when the goal is reached
 */
void calcProbDistrMagnetization(vector<double> state, double beta, int N, int k, double precision){

    int check_if_near_eq = 10; // nach 10 lines überprüfen ob in der Nähe des Eq
    int stop = 20; // stops the simulation after being near eq 5 times in a row
    double energy = 0;
    double magnetization = 0;
    
    int conseq_near_eq = 0;

    double average_energy = 0;

    bool near_eq = false;
    int total_number_measurements = 0;

    int prob_distr[1025]= {0};
     
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(0,L*L-1);
    initialized_exparray(beta);

    for(int i = 0; i < N ;i++){


        for(int j = 0; j < k; j++){

            // Choose an initial side

            int side = dist6(rng);

            if(isFlipped(side,state,beta)){
                state[side]= -state[side];
            }

        }
        // Measure
        vector<double> results = calc_Energy_Magnetization(state);
        
        if(i > L*L){

            total_number_measurements += 1;
            int index = results[1]+512;
            prob_distr[index]=prob_distr[index]+1;
        }
        
    }

    dump_Prob_Distr(prob_distr,B,J,beta,total_number_measurements);
}