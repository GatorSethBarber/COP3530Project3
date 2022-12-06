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
    string salaryRange, jobGrowth, edu, workExp;
    // readFile(main);
    cout << main.getJobTypes().size() << endl;
    /*
    cout << "Choose a salary range: " << endl;
    cout << "0: Below $20,000" << endl;
    cout << "1: $20,000-$40,000" << endl;
    cout << "2: $40,000-80,000" << endl;
    cout << "3: 80,000-100,000" << endl;
    cout << "4: $100,000-$150,000" << endl;
    cout << "5: Above $150,000" << endl;
    cin >> salaryRange;
    cout << "How important is projected job growth to you?" << endl;
    cout << "0: Not important" << endl;
    cout << "1: Somewhat unimportant" << endl;
    cout << "2: Neutral" << endl;
    cout << "3: Somewhat important" << endl;
    cout << "4: Very important" << endl;
    cout << "5: Extremely important" << endl;
    cin >> jobGrowth;
    cout << "Choose your education level: " << endl;
    cout << "0: No formal educational credential" << endl;
    cout << "1: High school diploma or equivalent" << endl;
    cout << "2: Postsecondary nondegree award" << endl;
    cout << "3: Some college, no degree" << endl;
    cout << "4: Associate's degree" << endl;
    cout << "5: Bachelor's degree" << endl;
    cout << "6: Master's degree" << endl;
    cout << "7: Doctoral or professional" << endl;
    cin >> edu;
    cout << "Years of Work Experience" << endl;
    cout << "0: None" << endl;
    cout << "1: Less than 5 years" << endl;
    cout << "2: 5 years or more" << endl;
    cin >> workExp;
    cout << "" << endl;
    cout << "Recommended Careers:" << endl;
    */
    //main.rankAll(stoi(salaryRange), stoi(jobGrowth), stoi(edu), stoi(workExp)); 
    
    //main.mergeSort(0, main.getJobTypes().size() - 1);
    //main.quickSort();

     
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