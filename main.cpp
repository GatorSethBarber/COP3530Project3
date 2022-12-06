#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "Dataset.h"
using namespace std;

int main() {
    Dataset main;
    bool success = main.readInData("dataForProject.csv");
    if (!success) {
        cout << "Could not find file: dataForProject.csv" << endl;
        return -1;
    }
    
    int salaryRange, jobGrowh, edu, workExp;    
    main.rankAll(3, 4, 3, 3); 
    
    main.quickSort();

     
    vector<vector<string>> lastOnes = main.getLastN(10);
    for (int i = 0; i < lastOnes.size(); i++) {
        for (int j = 0; j < lastOnes[i].size(); j++) {
            cout << lastOnes[i][j] << " ";
        }
        cout << endl;
    }
    // for (int i = main.getJobTypes().size() - 1; i > main.getJobTypes().size() - 10; i--)
    // {
    //     std::cout << i << " ";
    //     main.getJobTypes()[i]->print(main.getOccupations());
    //     std::cout << endl;
    // }
   
   return 0;
}