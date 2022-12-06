#include "Dataset.h"
#include <iostream>
#include <map>
using namespace std;
/*================ Main constructors =====================*/

Dataset::Dataset() : jobTypes() {}

/*====================== The Big Three ===================*/
// Helpers for te big three
/**
 * Copies the actual data in jobTypes from another dataset.
 * @param other The other dataset
 */
void Dataset::CopySet(const Dataset& other) {
    // Need to make copies of each and add in pointer to new data
    ClearData();
    jobTypes = vector<Datapoint*>(other.jobTypes.size(), nullptr);

    for (int i = 0; i < other.jobTypes.size(); i++) {
        Datapoint* newJobType = new Datapoint(*other.jobTypes[i]);
        jobTypes[i] = newJobType;
    }
}

/**
 * The the data currently in the dataset.
 */
void Dataset::ClearData() {
    for (int i = 0; i < jobTypes.size(); i++)
        delete jobTypes[i];
    
    jobTypes.clear();
}

// The Big Three

/**
 * Copy constructor for the dataset.
 * @param other The dataset to copy from
*/
Dataset::Dataset(const Dataset& other) : jobTypes() {
    CopySet(other);
}

/**
 * The copy assignment operator
 * @param other The other dataset to copy from
 */
Dataset& Dataset::operator=(const Dataset& other) {
    if (&other != this)
        CopySet(other);
    
    return *this;
}

/**
 * The destructor
 */
Dataset::~Dataset() {
    ClearData();
}


/*============================= Accessors and Manipulators ==========================*/
// Add in data (will need to modify this with Datapoint.h)

/**
 * Add in a data point to the dataset.
 * @param SOC The occupation code
 * @param NAICS The industry code
 * @param averageSalary The average salary
 * @param projectedGrowth The projected growth
 * @param edu The minimum education level
 * @param work The work experience needed
 */
void Dataset::addDatapoint(string SOC, string NAICS, double averageSalary, double projectedGrowth, int edu,
int work)
{
    Datapoint* newJobType = new Datapoint(SOC, NAICS, averageSalary, projectedGrowth, edu, work);
    jobTypes.push_back(newJobType);

}

/**
 * Get a reference to the jobTypes vector, which stores the data.
 * @return A non-constant reference
*/
vector<Datapoint*>& Dataset::getJobTypes()
{
    return jobTypes;
}

/**
 * Get a non-constant reference to the occupation map.
 * @return A non-constant reference
 */
map<string, string>& Dataset::getOccupations()
{
    return occupationMap;
}


/**
 * Rank all the datapoints in the dataset according to closeness
 * to certain values
 * @param salaryRange Specifier for the target salary range (0 to 5)
 * @param jobGrowth The importance placed on job growth
 * @param edu The minimum education level
 * @param workExp The needed work experience
*/
void Dataset::rankAll(int salaryRange, int jobGrowth, int edu, int workExp) {
    
    map<int, pair<int, int>> salaryRanges;
    salaryRanges = {
        {0, make_pair(0, 19999)},
        {1, make_pair(20000, 39999)},
        {2, make_pair(40000, 79999)},
        {3, make_pair(80000, 99999)},
        {4, make_pair(100000, 149999)},
        {5, make_pair(150000, INT_MAX)},
    };

    int minSalary = salaryRanges[salaryRange].first;
    int maxSalary = salaryRanges[salaryRange].second;

    for (int i = 0; i < jobTypes.size(); i++) {
        Datapoint curr = *jobTypes[i];
        double eduRanking = 0, salaryRanking = 0, jobGrowthRanking = 0, 
        workExpRanking = 0;

        if (jobTypes[i]->avgSalary < minSalary)
        {
            salaryRanking = (1.0 / jobTypes[i]->avgSalary) * -5.0;
        }
        else if (jobTypes[i]->avgSalary > maxSalary)
        {
            salaryRanking = jobTypes[i]->avgSalary * 2.0;
        }
        else
        {
            salaryRanking = jobTypes[i]->avgSalary * 10;
        }
        salaryRanking /= 1000.0;

        jobGrowthRanking = curr.projJobGrowth * jobGrowth;

        if (jobTypes[i]->education == edu)
        {
            eduRanking = 10;
        }
        else if (jobTypes[i]->education < edu)
        {
            eduRanking = 5;
        }
        else
        {
            eduRanking = 1;
        }
        if (jobTypes[i]->workExperience == workExp)
        {
            workExpRanking = 10;
        }
        else if (jobTypes[i]->workExperience < workExp)
        {
            workExpRanking = 5;
        }
        else
        {
            workExpRanking = 0;
        }
        jobTypes[i]->ranking = salaryRanking + jobGrowthRanking + eduRanking + workExpRanking;

    }
}

/*================== Merge Sort =======================*/
/**
 * Private helper function that performs the main part of
 * merge sort.
 * @param startIndex The starting index for the merge sort
 * @param endIndex The ending index for the merge sort
 */
void Dataset::mergeSortDivide(int startIndex, int endIndex) {
    // Formerly, mergeSort the same except had if(startIndex >= endIndex)
    if ((endIndex - startIndex) < 2)
        return;

    // Otherwise, split the left and right and merge
    int midIndex = (startIndex + startIndex) / 2;
    mergeSortDivide(startIndex, midIndex);
    mergeSortDivide(midIndex + 1, endIndex);
    cout << startIndex << " " << midIndex << " " << endIndex << endl;
    mergeSortMerge(startIndex, midIndex, endIndex);
}

// todo: Check the indices out to make sure no conflicts exist (i.e., off by one errors)
/**
 * Works with mergeSortDivide. Merges the two parts of an array
 * @param left The beginning of the first subarray to merge
 * @param mid The beginning of the second subarray to merge
 * @param right The end of the second subarray
 */
void Dataset::mergeSortMerge(int left, int mid, int right) {
    int n1 = mid - left + 1;
	int n2 = right - mid;
	vector<Datapoint*> temp1;
    vector<Datapoint*> temp2; // where O(n) space comes from
	
	for (int i = 0; i < n1; i++)
		temp1.push_back(jobTypes[left + i]);
	for (int j = 0; j < n2; j++)
		temp2.push_back(jobTypes[mid + 1 + j]);
    	// merge arrays X and Y into arr
    /*
    cout << "Temp 1: " << endl;
    for (auto el : temp1)
    {
        cout << el->ranking << " ";
    }
    cout << endl;
    cout << "Temp 2: " << endl;
    for (auto el : temp2)
    {
        cout << el->ranking << " ";
    }
    cout << endl;
    */
	int i, j, k;
	i = 0;
	j = 0;
	k = left;
	
	while (i < n1 && j < n2)
    {
     
		if (temp1[i]->ranking <= temp2[j]->ranking)
        {
            //cout << temp1[i]->ranking << " <= " << temp2[j]->ranking << endl;
			jobTypes[k] = temp1[i];
			i++;
        }
        else
        {
            //cout << temp1[i]->ranking << " > " << temp2[j]->ranking << endl;
			jobTypes[k] = temp2[j];
			j++;
        }
        k++;
    }
        
    //when we run out of elements in either X or Y append the remaining elements
    while (i < n1)
    {
        jobTypes[k] = temp1[i];
        i++;
        k++;
    }
    while(j < n2)
    {
        jobTypes[k] = temp2[j];
        j++;
        k++;
    }
    /*
    cout << "New sort" << endl;
    for (int i = left; i < right; i++)
    {
        cout << i << " " << jobTypes[i]->ranking << endl;
    }
    */
}

/**
 * Wrapper function to perform a merge sort
 */
void Dataset::mergeSort() {
    mergeSortDivide(0, jobTypes.size() - 1);
}

/**
 * Recursively perform quick sort.
 * @param start The start index
 * @param end The end index (must be an actual index)
 */
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

/**
 * Forward facing function for calling QuickSort
*/
void Dataset::quickSort() {
    // Doing quicksort for the entire list
    // Use middle element as pivot
    quickSortRecursive(0, jobTypes.size() - 1);

}
