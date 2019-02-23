#include <iostream>
#include <omp.h>
#include <stdio.h>
#include "openmp/run.h"

using namespace std;

int main() {
    cout << " ::: Main ::: " << endl;
    run();

    cout << endl << " ::: HAPPY END :::" <<endl;
    return 0;
}



