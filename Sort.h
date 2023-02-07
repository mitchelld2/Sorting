//
// Interface Definition for the Sort Class
// Author: Max Benson
// Date: 09/04/2021
//

#ifndef SORT_H
#define SORT_H

// Remove the corresponding comment line when you implement a sorting method
//#define INSERTION_SORT_IMPLEMENTED
//#define SELECTION_SORT_IMPLEMENTED
//#define SHELL_SORT_IMPLEMENTED

//#define QUICK_SORT_IMPLEMENTED

#define SINGLY_LINKED_LIST_IMPLEMENTED
#define MERGE_SORT_LL_IMPLEMENTED

//#define MERGE_SORT_IMPLEMENTED
//#define INSERTION_SORT_LL_IMPLEMENTED
//#define SELECTION_SORT_LL_IMPLEMENTED


#include <iostream>
using std::cout;
using std::endl;
using std::string;

#include "VariableArrayList.h"
#include "SinglyLinkedList.h"

// These are powers of two because they are bits in the testMask
// They should be always defined even if the method has not been implemented
enum SortType {
    InsertionSort,
    SelectionSort,
    ShellSort,
    QuickSort,
    MergeSort,
    InsertionSortLL,
    SelectionSortLL,
    MergeSortLL
};

enum ListType {
    Array,
    SinglyLinked
};

template <typename ItemType>
class Sort {
public:
    void InsertionSort(List<ItemType>& list);
    void SelectionSort(List<ItemType>& list);
    void ShellSort(List<ItemType>& list);
    void QuickSort(List<ItemType>& list, int lowIndex, int highIndex);
    void MergeSort(List<ItemType>& list);
private:
    ItemType PickPivot(const List<ItemType>& list, int lowIndex, int highIndex );
    void Partition(List<ItemType>& list, int lowIndex, int highIndex, ItemType pivot, int& left, int& right);
    void DoMergeSort(List<ItemType>& list, ItemType* aux, int lowIndex, int highIndex);
	void MergeSortedLists(List<ItemType>& list, ItemType* aux, int lowIndex, int center, int right);
};

#include "List_Sorting.h"

#endif //SORT_H
