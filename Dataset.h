#pragma once
#include <vector>
#include <map>
#include "Datapoint.h"



class Dataset {

    vector<Datapoint*> jobTypes;
    map<string, string> occupationMap;

    // Helpers associated with the big three
    void CopySet(const Dataset& other);
    void ClearData();

    void mergeSortDivide(int startIndex, int endIndex);
    void mergeSortMerge(int startIndexOne, int startIndexTwo, int endIndex);    // No need to specify end of section one
    void quickSortRecursive(int start, int end);

    public:
        // Main constructors
        Dataset();
        
        // The big three
        Dataset(const Dataset& other);
        Dataset& operator=(const Dataset& other);
        ~Dataset();


        // Add in data 
        void addDatapoint(string SOC, string NAICS, double averageSalary, double projectedGrowth, 
        int edu, int work);
        vector<Datapoint*>& getJobTypes();
        map<string, string>& getOccupations();
        void rankAll(int salaryRange, int jobGrowth, int edu, int workExp);
        void mergeSort();
        void quickSort();

};