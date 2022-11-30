#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "Datapoint.h"
#include "Dataset.h"
using namespace std;

void quickSort(vector<int>& toSort, int start, int end);
void readFile(Dataset& main);

int main() {
    Dataset main;
    readFile(main);


    /*
    vector<int> testVector{2, 5, 9, 1, 20, 10, 13, 15};
    // vector<int> testVector{2, 3, 9, 1};
    for (int& el : testVector)
        cout << el << ", ";
    cout << endl;

    quickSort(testVector, 0, testVector.size() - 1);
    for (int& el : testVector)
        cout << el << ", ";
    cout << endl;
    */
}

void readFile(Dataset& main)
{
    ifstream myfile; 
    int count = 0;
    string row;
    map<string, int> eduValues;
    eduValues.insert({"No formal educational credential", 0});
    eduValues.insert({"High school diploma or equivalent", 1});
    eduValues.insert({"Postsecondary nondegree award", 1});
    eduValues.insert({"Some college, no degree", 1});
    eduValues.insert({"Associate's degree", 1});
    eduValues.insert({"Bachelor's degree", 1});
    eduValues.insert({"Master's degree", 1});
    eduValues.insert({"Doctoral or professional degree", 1});

    myfile.open("dataForProjectCSV.csv");
    count = 0; // for testing only
    if (myfile.is_open())
    {
        while (!myfile.eof()) //!myfile.eof()
        {
            vector<string> data;
            count++;
            getline(myfile, row);
            if (count < 3 || row.length() == 0)
            {
                continue;
            }

            stringstream s_stream(row); //create string stream from the string
            while(s_stream.good()) 
            {
                string substr;
                getline(s_stream, substr, ','); //get first string delimited by comma
                if (substr.find("\"") != string::npos)
                {
                    string substr2;
                    getline(s_stream, substr2, ',');
                    substr += substr2;
                    while (substr2.find("\"") == string::npos)
                    {
                        substr += ',';
                        getline(s_stream, substr2, ',');
                        substr += substr2;
                    }         
                }
                data.push_back(substr);
            }

            //cout << "col1 " << row << " ";

            //cout << endl;
            string soc = data[2];
            
            if (soc.compare("00-0000") == 0)
            {
                continue;
            }
            int edu = 0;
            if (eduValues.find(data[15]) != eduValues.end())
                edu = eduValues[data[15]];

            //Datapoint* myData = new Datapoint(data[2], data[4], stod(data[14]), stod(data[13]), edu);
           
            main.addDatapoint(data[2], data[4], stod(data[14]), stod(data[13]), edu);
            //cout << data[14] << endl;

            for (int i = 0; i < data.size(); i++)
            {
                //cout << i << " " << data[i] << endl;
            }
        }
    }
    myfile.close();
}


// End uses the actual end approach (should start out with end = toSort.size() - 1)
void quickSort(vector<int>& toSort, int start, int end) {
    
    // Base case: if length is 0 or 1, return
    if (end - start + 1 < 2) {
        cout << "Passing over because length is : " << end - start + 1 << endl;
        return;
    }

    // Use mid for pivot, swapping it to the beginning to get it out of the way
    int pivot = (start + end) / 2;
    cout << "Start: " << start << "; End: " << end << "; Pivot: " << pivot << endl;
    int pivotValue = toSort[pivot];
    toSort[pivot] = toSort[start];
    toSort[start] = pivotValue;

    int moveDown = end;
    int moveUp = start + 1;
    cout << "Pivot is " << pivotValue << " originally at " << pivot << endl;
    while (moveUp < moveDown) {
        while (toSort[moveDown] >= pivotValue && moveDown > moveUp)
            moveDown--;
        while (toSort[moveUp] <= pivotValue && moveUp < moveDown)
            moveUp++;
        
        cout << "\tSwapping " << moveDown << ": " << toSort[moveDown] << " and " << moveUp << ": " << toSort[moveUp] << endl;
        // Now, can flip
        if (toSort[moveDown] < toSort[moveUp]) {
            // Swap
            int temp = toSort[moveDown];
            toSort[moveDown] = toSort[moveUp];
            toSort[moveUp] = temp;
        }
    }

    // Finally, swap pivot into its correct position (at moveDown, which will be less than pivot)
    // Several places to place the pivot

    // Whenever ending, moveUp == moveDown.
    // Basically, two cases: if everything is pivot less than what is at moveUp/moveDown, put in previous position
    // Otherwise, place at moveUp/moveDown
    int newPivotPos = moveDown - 1;
    if (toSort[moveDown] < pivotValue) {
        newPivotPos = moveDown;
        cout << "Used if " << endl;
    }

    // Swap values
    toSort[start] = toSort[newPivotPos];
    toSort[newPivotPos] = pivotValue;
    
    // Now, call recursively, ignoring at previous pivot position
    cout << "\tAt end: ";
    for (int& el : toSort)
        cout << el << ", ";
    cout << endl;
    // Problem is here with negative sizes
    quickSort(toSort, start, newPivotPos - 1);
    quickSort(toSort, newPivotPos + 1, end);

}