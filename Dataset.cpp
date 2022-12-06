#include "Dataset.h"
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

/*================ Main constructors and initializer =====================*/

Dataset::Dataset() : jobTypes(), occupationMap(), industryMap() {
    educationMap = map<string, int>();
    educationMap.insert({"No formal educational credential", 0});
    educationMap.insert({"High school diploma or equivalent", 1});
    educationMap.insert({"Postsecondary nondegree award", 2});
    educationMap.insert({"Some college no degree", 3});
    educationMap.insert({"Associate's degree", 4});
    educationMap.insert({"Bachelor's degree", 5});
    educationMap.insert({"Master's degree", 6});
    educationMap.insert({"Doctoral or professional degree", 7});

    workExpMap =
    {
        {"None", 0},
        {"Less than 5 years", 1},
        {"5 years or more", 2},
    };
}

/**
 * Read in the data for the project.
*/
bool Dataset::readInData(string fileName) {
    ifstream myfile(fileName);
    cout << fileName << endl;
    if (!myfile.is_open()) {
        return false;
    }

    string row;
    int count = 0;
    
    while (!myfile.fail()) {
        vector<string> data;
        count++;
        getline(myfile, row);
        if (count < 3 || row.length() == 0) {
            continue;
        }

        // Create and use string stream from the string
        istringstream s_stream(row);
        while(s_stream.good()) {
            string substr;
            getline(s_stream, substr, ',');  // get delimited by comma
            
            if (substr.find("\"") != string::npos) {
                string substr2;
                getline(s_stream, substr2, ',');
                substr += substr2;
                while (substr2.find("\"") == string::npos) {
                    substr += ',';
                    getline(s_stream, substr2, ',');
                    substr += substr2;
                }         
                substr = substr.substr(1, substr.length()-2); 
            }
            data.push_back(substr);
        }

        string soc = data.at(2);
        
        // 00-0000 refers to all occupations in a certain industry.
        // These datapoints are not needed.
        if (soc == "00-0000") {
            continue;
        }

        // Occupation codes repeat, so only need to insert them once.
        if (count < 1115) {
            occupationMap.insert({data[2], data[3]});
        }
        
        // Adding NAICS codes to their corresponding descriptions.
        if (industryMap.find(data[4]) == industryMap.end()) {
            industryMap.insert({data[4], data[5]});
        }

        int edu = 0, work = 0;

        // Maps the education level to a number
        if (educationMap.find(data.at(24)) != educationMap.end())
            edu = educationMap[data[24]];

        // Maps work experience to a number
        work = workExpMap[data[25]];
        
        addDatapoint(soc, data[4], stod(data[14]), stod(data[13]), edu, work);
    }
    
    if (!myfile.eof())
        cout << "Something went wrong. counter = " << count << endl;

    myfile.close();
    return true;
}

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
int work) {
    Datapoint* newJobType = new Datapoint(SOC, NAICS, averageSalary, projectedGrowth, edu, work);
    jobTypes.push_back(newJobType);

}

/**
 * Get a reference to the jobTypes vector, which stores the data.
 * @return A non-constant reference
*/
vector<Datapoint*>& Dataset::getJobTypes() {
    return jobTypes;
}

/**
 * Get a non-constant reference to the occupation map.
 * @return A non-constant reference
 */
map<string, string>& Dataset::getOccupations() {
    return occupationMap;
}

/**
 * Get a non-constant reference to the industry map.
 * @return A non-constant reference
 */
map<string, string>& Dataset::getIndustries() {
    return industryMap;
}


vector<vector<string>> Dataset::getLastN(int n) {
    vector<vector<string>> returnVector;
    for (int i = jobTypes.size() - 1; i >= 0 && n > 0; i--) {
        vector<string> temp;
        temp.push_back(occupationMap[jobTypes[i]->occupationCode]);
        temp.push_back(industryMap[jobTypes[i]->industryNAICS]);
        temp.push_back(to_string(jobTypes[i]->avgSalary));
        temp.push_back(to_string(jobTypes[i]->projJobGrowth));
        temp.push_back(to_string(jobTypes[i]->education));
        returnVector.push_back(temp);
        n--;
    }
    return returnVector;

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
            // If the salary is less than the minimum salary, it 
            // gets the inverse to decrease the ranking.
            salaryRanking = (1.0 / jobTypes[i]->avgSalary) * -5.0;
        }
        else if (jobTypes[i]->avgSalary > maxSalary)
        {
            // Only a slight boost in the ranking if the salary
            // is above the maximum salary desired.
            salaryRanking = jobTypes[i]->avgSalary * 2.0;
        }
        else
        {
            // If the salary is in the range, then it gets
            // the greatest boost in ranking.
            salaryRanking = jobTypes[i]->avgSalary * 10;
        }
        salaryRanking /= 1000.0; // Equalizes the weight of the salaryRanking.

        // Multiplies the job growth by the importance selected by the user
        jobGrowthRanking = curr.projJobGrowth * jobGrowth;

        // If the education matches the user selected education,
        // then the ranking gets the greatest boost
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
            eduRanking = 0;
        }

        // The work functions the same way as education level.
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
    // Base case: 0 or 1 elements
    if ((endIndex - startIndex) < 2)
        return;

    // Otherwise, split the left and right and merge
    int midIndex = (startIndex + endIndex) / 2;
    mergeSortDivide(startIndex, midIndex);
    mergeSortDivide(midIndex + 1, endIndex);
    
    mergeSortMerge(startIndex, midIndex, endIndex);
}


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
    vector<Datapoint*> temp2; 
	
	for (int i = 0; i < n1; i++)
		temp1.push_back(jobTypes[left + i]);
	for (int j = 0; j < n2; j++)
		temp2.push_back(jobTypes[mid + 1 + j]);
    
    // merge vectors temp1 and temp2 into the jobTypes vector
	int i, j, k;
	i = 0;
	j = 0;
	k = left;
	
	while (i < n1 && j < n2)
    {
		if (temp1[i]->ranking <= temp2[j]->ranking)
        {
			jobTypes[k] = temp1[i];
			i++;
        }
        else
        {
			jobTypes[k] = temp2[j];
			j++;
        }
        k++;
    }
        
    //when we run out of elements in either temp1 or temp2, add them to jobTypes
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
}

/**
 * Function to perform a merge sort
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
