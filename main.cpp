

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "util.h"

using namespace std;
using namespace constants;


int main(){

    //Parameters for the simulation
    double beta_min = 0.4;                    //minimum beta
    double beta_max = 5;                 //maximum beta
    int N = 10000;                           //measurements
    int k = L*L;                            //steps bevor measurement
    int number_discrete_points = 500;       //number of betas between max and min
    double dE = 0.01;                       //percentage energy deviation from the average for the termination condition
    int deviationcount = 20;                //number of consecutive successful derivations


    vector<double> state = createState(1);

    algoMetropolisTemperature(state,beta_min, beta_max, N, k, number_discrete_points, dE, deviationcount);
    //algoMetropolis(state, N, k);
    //algoMetropolisMultithread(state,0,2,100000,1);
}