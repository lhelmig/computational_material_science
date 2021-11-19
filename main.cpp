

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "util.h"

using namespace std;
using namespace constants;


int main(){

    //Parameters for the simulation
    double beta_min = 0;                    //minimum beta
    double beta_max = 0.75;                 //maximum beta
    int N = 10000;                           //measurements
    int k = L*L;                            //steps bevor measurement
    int number_discrete_points = 100;       //number of betas between max and min
    double dE = 20;                       //energiededifference for the termination condition
    int deviationcount = 30;                //number of consecutive successful derivations


    vector<double> state = createState(0.5);

    algoMetropolisTemperature(state,beta_min, beta_max, N, k, number_discrete_points, dE, deviationcount);

    //algoMetropolisMultithread(state,0,2,100000,1);
}