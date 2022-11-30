#include <vector>
#include <iostream>
#include "Dataset.h"
using namespace std;

void quickSort(vector<int>& toSort, int start, int end);

int main() {
    // vector<int> testVector{2, 5, 9, 1, 20, 10, 13, 15};
    // // vector<int> testVector{2, 3, 9, 1};
    // for (int& el : testVector)
    //     cout << el << ", ";
    // cout << endl;

    // quickSort(testVector, 0, testVector.size() - 1);
    // for (int& el : testVector)
    //     cout << el << ", ";
    // cout << endl;
    Dataset newDataset;
    newDataset.addDatapoint("hello", "goodbye", "hello", "goodbye", 200, 1.3, "bachelor's");
    newDataset.addDatapoint("helo", "goodbye", "hello", "goodbye", 200, 1.3, "bachelor's");
    newDataset.mergeSort();
    newDataset.quickSort();
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