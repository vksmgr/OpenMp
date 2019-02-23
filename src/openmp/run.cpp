//
// Created by v on 23/2/19.
//

#include "run.h"
#include <omp.h>
#include <iostream>

using namespace std;



void example1() {
    int data, id, total;
    int num_threads;
    cout << "Enter the number of threads :: " << endl;
    cin >> num_threads;

    /*Starting the parallel section */
#pragma omp parallel private(data, id, total) num_threads(num_threads)
    {

        id = omp_get_thread_num();  //this will get the thread id

// executing the program using cretical section
#pragma omp critical
        {
            cout << "single thread at a time " << endl;
            cout << "thread id " << omp_get_thread_num();
            data = id;

        };

        total = omp_get_num_threads();  // This will give the total number of threads executing

//    cout << "Hello world form the process : " << id << "out of " << total << "With the data :: " << data << endl;
//    cout << "Tid "<< id << "data : "<< data << endl;
        cout << data << endl;
    };

    cout << "Exit from parallel section ";
}

// we will parallalize the for loop
/*solving the equestion y <- ax + y */
void example2() {
    const int num = 10;
    float y[num], x[num], a;
    a = 1;

    /*initailizing the values in the loop using parallel loop*/
#pragma omp parallel for
    for (int i = 0; i < num; ++i) {
        y[i] = 10.1;
    }
#pragma opm parallel for
    for (int j = 0; j < num; ++j) {
        x[j] = 10.1;
    }


/*now we just add the equation*/
#pragma opm parallel for
    for (int k = 0; k < num; ++k) {
        y[k] = a * x[k] + y[k];
    }

    /*finally we will print the values of the array*/
#pragma omp parallel for
    for (int l = 0; l < num; ++l) {
        cout << y[l] << " ";
    }
}


/* we will work on the reduction of the values*/
/*write a program to add numbers using the redunction*/
void example3() {
    int num;
    cout << "enter the numner : " << endl;
    cin >> num;

/*we need to use the reduction int the openmp*/
int x = 10;
int data[] = {1, 2, 3, 4, 5, 6 ,7 ,8 ,90 ,10};
#pragma omp parallel for reduction(max: x)
    for (int i = 0; i < num; ++i) {
        x = max(x, data[i]);
    }
    cout << "the value of X : "<< x;
}

/*write a program to add number form n integers using reduction directive*/
void example4(){
    int input= 0;

#pragma omp parallel for num_threads(10) reduction(+: input)
    /*this for loop will be parallalozed meaning, each iteration will be executed on a processor*/
        for (int i = 0; i < 10; i++) {
            input = input + i;
    }
    cout << "addition of the 10   : "<< input << endl;
}

/*simple basic directives and fuctions in openmp*/
void example5(){
    int num;
    num = omp_get_max_threads();
    cout << "the maximum threads can be : "<<num<<endl;
    omp_set_num_threads(20);
    num = omp_get_max_threads();
    cout << "the maximum threads can be : "<<num<<endl;

    /*number of threads int the parallel region*/
#pragma omp parallel
    {
        num = omp_get_max_threads();
        cout << "the max Paralle : "<< num;
    };
}

/*setting number of threads based on the conditions of the if condition*/
void example6(){
    int num_thr = 5;
#pragma omp parallel if (omp_get_max_threads() < num_thr) num_threads(num_thr)
    {
        cout << " the num threads : "<< omp_get_num_threads();
    }
}

/*calculating time requred for execution or working with the time*/
void example7(){
    double stime, etime;
    stime = omp_get_wtime();
#pragma omp parallel for num_threads(4)
    for (int i = 0; i < 100000; ++i) {
        cout << "Just 1 : "<< endl;
    }
    etime = omp_get_wtime();
    cout << endl << "total Execution time : "<< etime-stime << endl;
}

/*working with variables or scope of the variables*/
void example8(){
    //we will be doig addition with the shared variable
    /*shared variables*/
    int sum = 0;
    int sum2 = 0;

    /*private variables*/
    int prt1 = 1;

    /*First private variable*/
    int first_private = 10;

    /*the default scope of the variable*/
    int def_variable = 20;
    //each tread will try to read it and increament it by one by precious value
    cout << "Orignal value of the varible is  : "<< sum <<endl;
#pragma omp parallel  shared(sum, sum2) private(prt1) firstprivate( first_private) num_threads(5)
    {
        /*shared*/
        sum = sum + 1;  // as this is the shared memory race condition can happen

        /*to avoid race condition we will use the cretical section*/
#pragma omp critical
        {
            sum2 = sum2 + 1;
        };


        /*private*/
        cout <<endl<<"My private copy : "<<prt1 << endl;
        /* update to the private variable */
        prt1 = prt1+11;

        /*first private*/
        cout << "the value of me " << first_private;

        /*the default variable is */
        cout << endl << "the default value of the variable is : "<< def_variable<<endl;
        /* what happen if i update the value of the default variable */
        def_variable = def_variable + 10;
        cout << "default variables" <<def_variable <<endl;
    }

    cout << "modified values of sum " <<sum <<endl;
    cout << "modified values with critical section of sum " <<sum2 <<endl;
    cout <<endl<<"the update lost " << prt1;
    cout <<"the default value stayes same or chages ; "<< def_variable <<endl;
}

/*multiplocation using reduction*/
void example9(){
    int r = 1;
#pragma omp parallel reduction( * : r)
    {
      r = r * 2;
    };
    cout <<endl << "Reduced value : "<<r;
}

int run() {
//    example1();
//    example2();
//example3();
//example4();
//example5();
//example6();
//example7();
//example8();
example9();
    return 0;

}
