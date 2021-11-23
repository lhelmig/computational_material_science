#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "util.h"

using namespace std;
using namespace constants;


int main(){

    //Parameters for the simulation
    
    double beta_min = 2;                    //minimum beta
    double beta_max = 5;                 //maximum beta
    int N = 100000;                           //measurements
    int k = L*L;                            //steps bevor measurement
    int number_discrete_points = 100;       //number of betas between max and min
    double precision = 0.00001;                       // precision of the energy


    vector<double> state = createState(1);

    algoMetropolisTemperature(state,beta_min, beta_max, N, k, number_discrete_points, precision);

    //algoMetropolisMultithread(state,0,2,100000,1);
}