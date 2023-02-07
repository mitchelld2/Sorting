//
// Implementation of List ADT sorting methods
// Author: Max Benson
// Modified by: 
// Date: 10/18/2021
// Modification Date: 
//

#ifndef LIST_SORTING_H
#define LIST_SORTING_H

/**
 * Perform insertion sort for range of list
 * Uses helper function shared with Shell short
 * @param list to sort
 */
template <typename ItemType>
void Sort<ItemType>::InsertionSort(List<ItemType>& list) {
    assert(false);
}

/**
 * Perform selection sort for range of list
 * @param list to sort
 */
template <typename ItemType>
void Sort<ItemType>::SelectionSort(List<ItemType>& list) {
    assert(false);
}

/**
 * Perform Shell sort for range of list
 * Uses helper function shared with insertion sort
 * performs "h-sort" using so-called Hibbard series
 * @param list to sort
 * @param lowIndex first element of range for sorting
 * @param highIndex last element of range for sorting
 */
template <typename ItemType>
void Sort<ItemType>::ShellSort(List<ItemType>& list) {
    assert(false);
}

/**
 * Perform quick sort for range of list
 * Picks pivot based on median of first, middle, and last element
 * @param list to sort
 * @param lowIndex first element of range for sorting
 * @param highIndex last element of range for sorting
 */
template <typename ItemType>
void Sort<ItemType>::QuickSort(List<ItemType>& list, int lowIndex, int highIndex)
{
    int left, right;

    if(lowIndex < highIndex)
    {
        ItemType pivot = PickPivot(list, lowIndex, highIndex);

        Partition(list,lowIndex, highIndex, pivot, left, right);

        QuickSort(list, lowIndex, right); //first half
        QuickSort(list, left, highIndex); //second half
    }
}

/**
 * Perform merge sort for range of list
 * @param list to sort
 * @param lowIndex first element of range for sorting
 * @param highIndex last element of range for sorting
 * @param fAscending if true sort in ascending order, else in descending order
 */
template <typename ItemType>
void Sort<ItemType>::MergeSort(List<ItemType>& list)
{

}

/**
 * Called by QuickSort to choose pivot value
 * Takes median of first, middle and last element
 * Assumes there are there element in the list
 * @param list to sort
 * @param lowIndex first element of range for sorting
 * @param highIndex last element of range for sorting
 * @return pivot item
 */
template <typename ItemType>
ItemType Sort<ItemType>::PickPivot(const List<ItemType>& list, int lowIndex, int highIndex )
{
    ItemType left, right, mid, pivot;
    int middleIndex = (lowIndex + highIndex)/2;

    list.Get(lowIndex, left);
    list.Get(highIndex, right);
    list.Get(middleIndex, mid);

    if( ( (left > mid) && (left < right) ) || ( (left > right) && (left < mid) ) )
    {
        pivot = left;
    }
    else if( ( (mid > left) && (mid < right) ) || ( (mid > right) && (mid < left) ) )
    {
        pivot = mid;
    }
    else
    {
        pivot = right;
    }

    return pivot;
}

/**
 * Called by QuickSort to find the partition point for recursive
 * calls to sort the left and the right halves of the array
 * @param list to sort
 * @param lowIndex first element of range for sorting
 * @param highIndex last element of range for sorting
 * @param pivot
 * @param left receives the final value of "left" which is the first index of the right subarray
 * @param right receives the final value of "right" which is the last index of the left subarray
 */
template <typename ItemType>
void Sort<ItemType>::Partition(List<ItemType>& list, int lowIndex, int highIndex, ItemType pivot, int& left, int& right)
{
    int leftIndex = lowIndex;   //left = index of first item of sublist and moves rightward
    int rightIndex = highIndex; //right = start at last item of sublist and moves leftward

    ItemType leftItem, rightItem;
    list.Get(lowIndex, leftItem);
    list.Get(highIndex, rightItem);

    while(leftIndex <= rightIndex)  //while(left > right) //Loop until right > left
    {
        while(leftItem < pivot) //Move left rightward until hit item > pivot
        {
            leftIndex++;
            list.Get(leftIndex, leftItem);
        }
        while(rightItem > pivot)   //Move right leftward until hit item < pivot
        {
            rightIndex--;
            list.Get(rightIndex, rightItem);
        }
        if(leftIndex <= rightIndex)   //if left <= right
        {
            list.Swap(leftIndex, rightIndex); //Swap items at left and right
            leftIndex++; //Increment left
            rightIndex--;    //Decrement right

            list.Get(rightIndex, rightItem);
            list.Get(leftIndex, leftItem);
        }
    }
    if(leftItem == pivot)//If item at left = pivot, move rightward until hit last item or item > pivot
    {
        while(leftIndex < highIndex && leftItem <= pivot)
        {
            leftIndex++;
            list.Get(leftIndex, leftItem);
        }
    }
    if(rightItem == pivot)//If item at right = pivot, move leftward until hit last item or item < pivot
    {
        while(rightIndex > lowIndex && rightItem >= pivot)
        {
            rightIndex--;
            list.Get(rightIndex, rightItem);
        }
    }
    left = leftIndex;
    right = rightIndex;
}

/**
 * Helper function for merge sort
 * Recursively sorts two halves of list, then merges those two lists
 * The auxillary list aux is use for the merging process
 * @param list to sort
 * @param aux auxillary array
 * @param left first element of range for sorting
 * @param right last element of range for sorting
 */
template <typename ItemType>
void Sort<ItemType>::DoMergeSort(List<ItemType>& list, ItemType* aux, int left, int right)
{

}

/**
 * Helper function for merge sort
 * Sorted merge of two sorted lists.
 * First list in positions left to center
 * Second list in positions center+1 to right
 * The auxillary list aux is used for the merging process
 * @param list we are sorting
 * @param aux auxillary array
 * @param left first element of range
 * @param center last element of first list
 * @param right last element of range for sorting
 */
template <typename ItemType>
void Sort<ItemType>::MergeSortedLists(List<ItemType>& list, ItemType* aux, int left, int center, int right) {
}


#endif //SORTING_H
