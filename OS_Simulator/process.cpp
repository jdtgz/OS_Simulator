#include "process.h"

// For debugging only
void printProcessSet(vector<Process>& processVector){
    cout << "AT | DT | RQPT | PT | S | IO" << endl;
    for(auto & Proc : processVector)
    {
        Proc.printProcess();
    }
}