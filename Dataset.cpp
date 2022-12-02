#include "Dataset.h"
#include <iostream>
using namespace std;
/*================ Main constructors =====================*/

Dataset::Dataset() : jobTypes(10, nullptr) {}

/*====================== The Big Three ===================*/
// Helpers
void Dataset::CopySet(const Dataset& other) {
    // Need to make copies of each and add in pointer to new data
    ClearData();
    jobTypes = vector<Datapoint*>(other.jobTypes.size(), nullptr);

    for (int i = 0; i < other.jobTypes.size(); i++) {
        Datapoint* newJobType = new Datapoint(*other.jobTypes[i]);
        jobTypes[i] = newJobType;
    }
}

void Dataset::ClearData() {
    for (int i = 0; i < jobTypes.size(); i++)
        delete jobTypes[i];
    
    jobTypes.clear();
}

// The Big Three

Dataset::Dataset(const Dataset& other) : jobTypes() {
    CopySet(other);
}


Dataset& Dataset::operator=(const Dataset& other) {
    if (&other != this)
        CopySet(other);
    
    return *this;
}


Dataset::~Dataset() {
    ClearData();
}


/*============================= Accessors and Manipulators ==========================*/
// Add in data (will need to modify this with Datapoint.h)

void Dataset::addDatapoint(string SOC, string NAICS, double averageSalary, double projectedGrowth, int edu)
{
    Datapoint* newJobType = new Datapoint(SOC, NAICS, averageSalary, projectedGrowth, edu);
    jobTypes.push_back(newJobType);
}

void Dataset::addDatapoint(Datapoint* dp)
{
    jobTypes.push_back(dp);
}
/*
void Dataset::addDatapoint(string NAICS, string industryDesc, string SOC, string occupationDesc, 
int averageSalary, double projectedGrowth, string educationLevel) {
    Datapoint* newJobType = new Datapoint(NAICS, industryDesc, SOC, occupationDesc, 
                                          averageSalary, projectedGrowth, educationLevel);
    jobTypes.push_back(newJobType);
}
*/

vector<Datapoint*>& Dataset::getJobTypes()
{
    return jobTypes;
}


// May need to add in function pointer or use weights
void Dataset::rankAll(vector<Datapoint*>& myData) {
    //vector<Datapoint*> myData = this->getJobTypes();
    for (int i = 0; i < 10; i++) {
        // Do ranking
        // Not sure how to access the object from the vector of pointers --Angelina
        myData[i]->print();
        //cout << jobTypes[i] << endl;
    }
}

/*================== Merge Sort =======================*/
// Private helper functions that actually perform the sort
void Dataset::mergeSortDivide(int startIndex, int endIndex) {
    if ((endIndex - startIndex) < 2)
        return;

    // Otherwise, split the left and right and merge
    int midIndex = (startIndex + endIndex) / 2;
    mergeSortDivide(startIndex, midIndex);
    mergeSortDivide(midIndex, endIndex);
    mergeSortMerge(startIndex, midIndex, endIndex);
}

// todo: Check the indices out to make sure no conflicts exist (i.e., off by one errors)
void Dataset::mergeSortMerge(int startIndexOne, int startIndexTwo, int endIndex) {
    auto mergedSection = vector<Datapoint*>();

    int leftIndex = startIndexOne, rightIndex = startIndexTwo;
    // While the left part is not empty and the right part is not empty
    while ((startIndexOne - leftIndex) > 1 && (endIndex - rightIndex) > 1) {
        if (*jobTypes[leftIndex] <= *jobTypes[rightIndex]) {                           // Need to dereference for comparison
            mergedSection.push_back(jobTypes[leftIndex]);
            leftIndex++;
        }
        else {
            mergedSection.push_back(jobTypes[rightIndex]);
            rightIndex++;
        }
    }

    // Now, add in anything remaining from the left part
    while (leftIndex < startIndexTwo) {
        mergedSection.push_back(jobTypes[leftIndex]);
        leftIndex++;
    }
    while (rightIndex < endIndex) {
        mergedSection.push_back(jobTypes[rightIndex]);
        rightIndex++;
    }

    // Finally, copy the data back into the list
    for (int i = 0; i < mergedSection.size(); i++)
        jobTypes[i + startIndexOne] = mergedSection[i];
}

void Dataset::mergeSort() {
    mergeSortDivide(0, jobTypes.size());
}

void Dataset::quickSortRecursive(int start, int end) {
    
    // Base case: if length is 0 or 1, return
    if (end - start + 1 < 2)
        return;

    // Use mid for pivot, swapping it to the beginning to get it out of the way
    int pivot = (start + end) / 2;
    auto pivotPtr = jobTypes[pivot];
    jobTypes[pivot] = jobTypes[start];
    //  jobTypes[start] = pivotValue;

    int moveDown = end;
    int moveUp = start + 1;
    while (moveUp < moveDown) {
        while (*jobTypes[moveDown] >= *pivotPtr && moveDown > moveUp)
            moveDown--;
        while (*jobTypes[moveUp] <= *pivotPtr && moveUp < moveDown)
            moveUp++;
        
        // Now, can flip
        if (*jobTypes[moveDown] < *jobTypes[moveUp]) {
            // Swap
            auto temp = jobTypes[moveDown];
            jobTypes[moveDown] = jobTypes[moveUp];
            jobTypes[moveUp] = temp;
        }
    }

    // Finally, place pivot into its correct position (at moveDown, which will be less than pivot)
    // Several places to place the pivot

    // Whenever ending, moveUp == moveDown.
    // Basically, two cases: if pivot greater (as in less than all) than what is at moveUp/moveDown, put in previous position
    // Otherwise, place at moveUp/moveDown
    int newPivotPos = moveDown - 1;
    if (*jobTypes[moveDown] < *pivotPtr)
        newPivotPos = moveDown;

    // Swap values
    jobTypes[start] = jobTypes[newPivotPos];
    jobTypes[newPivotPos] = pivotPtr;
    
    // Now, call recursively, ignoring at previous pivot position
    // Problem is here with negative sizes
    quickSortRecursive(start, newPivotPos - 1);
    quickSortRecursive(newPivotPos + 1, end);

}

void Dataset::quickSort() {
    // Doing quicksort for the entire list
    // Use middle element as pivot
    quickSortRecursive(0, jobTypes.size() - 1);

}
