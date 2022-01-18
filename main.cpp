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
    double beta_max = 2;                 //maximum beta
    int N = 10000;                           //measurements
    int k = L*L;                            //steps bevor measurement
    int number_discrete_points = 10;       //number of betas between max and min
    double precision = 0.001;                       // precision of the energy


    vector<double> state = createState(1);

    //calcProbDistrMagnetization(state,0.5,100000,L*L,precision);
    //calcProbDistrMagnetization(state,0.88,100000,L*L,precision);
    //calcProbDistrMagnetization(state,1,100000,L*L,precision);
    //algoMetropolisTemperature(state,beta_min, beta_max, N, k, number_discrete_points, precision);
    //algoMetropolis(state,N,k);
    //algoMetropolisMultithread(state,0,2,100000,1);
}