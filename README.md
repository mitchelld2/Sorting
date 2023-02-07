# lab3-sorting-f21

In this lab assignment, you will code the following:

1) QuickSort using the public methods of our List ADT
2) MergeSort as a method of the SinglyLinkedList class

In addition you may receive extra credit for coding MergeSort using the public methods of our List ADT.


## Starter Repo

The starter repo contains a number of files, but the only ones you should modify are:

- `List_Sorting.h`  You will implement the QuickSort, PickPivot, and Partition methods of the Sort class here.  In addition if you choose to do the extra credit work, then you will implement MergeSort, DoMergeSort, and MergeSortedLists here as well.

- `SLL_Sorting.h`  You will implement the MergeSort, DoMergeSort, SplitIntoTwo, and MergeSortedLists methods of the SinglyLinkedList class here.

- 'Sort.h' When you finish implementing QuickSort, you will uncomment line 14, when you finish implementing MergeSort for SinglyLinkedList, you will uncomment line 15, and if you choose to do the extra credit work, then when you complete that you will uncomment line 18.

Note that the source code contains declarations of other sort methods.  You are not asked to implement them, and as long as you keep the corresponding line at the top of `Sort.h` commented out out the compiler will ignore them and they should not cause any you problems.
 	
## Quick Sort

Code the implementations of the following methods of the `Sort` class:

- `QuickSort`
- `PickPivot`
- `Partition`


The outline of `QuickSort` has been given in class:

1. Pick a “middle” value called the pivot
2. Partition the array
3. Use `QuickSort` to recursively sort left side
4. Use `QuickSort` to recursively sort right side

`PickPivot` should pick the median of the first, middle, and last elements for the pivot.

It is recommended that the follow the algorithm presented in class:

```
left = index which starts at the first item of the sublist and moves rightward (increases)
right = index which starts at the last item of the sublist and moves leftward (decreases)
Loop until right > left:
	Advance left rightward until you hit an item > pivot
	Advance right leftward until you hit an item < pivot
	if left <= right 
		Swap the items at left and right 
		Increment left
		Decrement right
If the item at left = pivot, move rightward until hit the last item or you hit an item > pivot => this will be the first index of the right subarray
If the item at right = pivot, move leftward until hit the last item or you hit an item < pivot => this will be the last index of the left subarray
``` 

## Linked List Merge Sort
Code the implementations of the following methods of the `SinglyLinkedList` class:

- `MergeSort`
- `DoMergeSort`
- `SplitIntoTwo`
- `MergeSortedLists`


The `MergeSort` method should call the `DoMergeSort` method with the head of the linked list and the size.  

As presented in class, the outline for `DoMergeSort` is:

```
DoMergeSort( nodeChain, length ) 
	if length > 1
		Split nodeChain into two chains of “equal” length
		Call DoMergeSort on first chain
		Call DoMergeSort on second chain
		Return sorted merge of first and second chain
	else
		Return nodeChain
```

Use `SplitIntoTwo` to split the nodeChain into two chains of approximately equal length.  Note that the method is defined and should be implemented to split at any specified position, not just at the middle.

Use `MergeSortedLists` to perform the sorted merge.

## Extra Credit: List ADT Merge Sort

Code the implementations of the following methods of the `Sort` class:

- `MergeSort`
- `DoMergeSort`
- `MergeSortedLists`

Your code goes in the file `List_Sorting.h`

You may wish to refer to the outline given in class on 2021 Oct 18.  

##  Make sure it works

Make sure your code compiles and runs, passing the validation tests.

Then make runs on the command line with -perf:ArrayList and then with -perf:SinglyLinkedList to make sure that it runs successfully and the timings seem reasonable.

Finally, run it with `valgrind --leak-check=full` to make sure it does not report any memory problems.




`
