

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "util.h"
#include "iofunc.h"

using namespace std;
using namespace constants;

int main(){
    vector<int> state = createState(0.5);
    visualizeState(state);
    exportState(state);
}