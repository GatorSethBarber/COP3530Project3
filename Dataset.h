#pragma once
#include <vector>
#include "Datapoint.h"


// The following is the main grist of the program. It handles
class Dataset {
    // The data will be stored in memory. A vector provides at least some definite access to the
    //  Datapoints, and is what will be sorted on.
    vector<Datapoint*> jobTypes;

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


        // Add in data (will need to modify this with Datapoint.h)
        void addDatapoint(string SOC, string NAICS, double averageSalary, double projectedGrowth, int edu);
        void addDatapoint(Datapoint* dp);
        vector<Datapoint*>& getJobTypes();
        // Add in data (will need to modify this with Datapoint.h)
        /*
        void addDatapoint(string NAICS, string industryDesc, string SOC, string occupationDesc, 
        int averageSalary, double projectedGrowth, string educationLevel);
        */
        // May need to add in function pointer or use weights
        void rankAll(vector<Datapoint*>& myData);

        void mergeSort();
        void quickSort();

};