//
// Test Program for the SinglyLinkedList Class
// Author: Max Benson
// Date: 07/23/2021
//

#include <assert.h>
#include <string.h>
#include <iostream>
#include <random>

#include "Sort.h"

using std::string;
using std::cout;
using std::endl;
using std::default_random_engine;
using std::uniform_int_distribution;

extern void TestSortType(SortType sortType);
extern void TestListType(ListType listType);
extern void Shuffle(List<int>& list, default_random_engine& g);

void TestCorrectness();
void TestSortIncreasingSequence(size_t length, default_random_engine& g);
void TestSortDoubledSequence(size_t length, default_random_engine& g);
void TestSortAllZeroSequence(size_t length, default_random_engine& g);
void TestAllSorts(const VariableArrayList<int>& sortedAscending, default_random_engine& g);
void TestArraySort(SortType type, VariableArrayList<int> toSort, const VariableArrayList<int>& correctlySorted);
void TestSLLSort(SortType type, SinglyLinkedList<int> toSort, const SinglyLinkedList<int>& correctlySorted);
void CheckSortOK(SortType type, const List<int>& toSort, const List<int>& correctlySorted);

int main(int argc, char* argv[]) {
    if (argc > 1) {
        SortType type;

        if (2 == argc) {
            if (strcmp(argv[1], "-perf:InsertionSort") == 0) {
#if defined(INSERTION_SORT_IMPLEMENTED)
                TestSortType(InsertionSort);
#else
                cout << "Insertion Sort not implemented"  << endl;
#endif
                return 0;
            }
            if (strcmp(argv[1], "-perf:SelectionSort") == 0) {
#if defined(SELECTION_SORT_IMPLEMENTED)
                TestSortType(SelectionSort);
#else
                cout << "Selection Sort not implemented"  << endl;
#endif
                return 0;
            }
            if (strcmp(argv[1], "-perf:ShellSort") == 0) {
#if defined(SHELL_SORT_IMPLEMENTED)
                TestSortType(ShellSort);
#else
                cout << "Shell Sort not implemented"  << endl;
#endif
                return 0;
            }
            if (strcmp(argv[1], "-perf:QuickSort") == 0) {
#if defined(QUICK_SORT_IMPLEMENTED)
                TestSortType(QuickSort);
#else
                cout << "Quick Sort not implemented"  << endl;
#endif
                return 0;
            }
            if (strcmp(argv[1], "-perf:MergeSort") == 0) {
#if defined(MERGE_SORT_IMPLEMENTED)
                TestSortType(MergeSort);
#else
                cout << "Mege Sort not implemented"  << endl;
#endif
                return 0;
            }
            if (strcmp(argv[1], "-perf:InsertionSortLL") == 0) {
#if defined(INSERTION_SORT_LL_IMPLEMENTED)
                TestSortType(InsertionSortLL);
#else
            cout << "Insertion Sort LL not implemented"  << endl;
#endif
                return 0;
            }
            if (strcmp(argv[1], "-perf:SelectionSortLL") == 0) {
#if defined(SELECTION_SORT_LL_IMPLEMENTED)
                TestSortType(SelectionSortLL);
#else
        cout << "Selection Sort LL not implemented"  << endl;
#endif
                return 0;
            }
            if (strcmp(argv[1], "-perf:MergeSortLL") == 0) {
#if defined(MERGE_SORT_LL_IMPLEMENTED)
                TestSortType(MergeSortLL);
#else
                cout << "Merge Sort LL not implemented"  << endl;
#endif
                return 0;
            }
            if (strcmp(argv[1], "-perf:ArrayList") == 0) {
                TestListType(Array);
                return 0;
            }
            if (strcmp(argv[1], "-perf:SinglyLinkedList") == 0) {
                TestListType(SinglyLinked);
                return 0;
            }
        }
        cout << "Usage: Sorting [-perf:<SortType>|-perf:<ListType>]" << endl;
        cout << "   where <SortType> can be InsertionSort, SelectionSort, ShellSort, QuickSort, MergeSort, InsertSortLL, SelectionSortLL, or MergeSortLL" << endl;
        cout << "   and <ListType> can be ArrayList or SinglyLinkedList" << endl;
        return 1;
    }
    else {
        TestCorrectness();
    }
    return 0;
}

void TestCorrectness() {
    default_random_engine g;

    cout << "Begin Correctness Testing" << endl;
    cout << "List Types Enabled:";
    cout << " ARRAY";
    cout << " SINGLY-LINKED";
    cout << endl;
    cout << "Sort Types Enabled:";
#if defined(INSERTION_SORT_IMPLEMENTED)
     cout << " INSERTION";
#endif
#if defined(SELECTION_SORT_IMPLEMENTED)
    cout << " SELECTION";
#endif
#if defined(SHELL_SORT_IMPLEMENTED)
    cout << " SHELL";
#endif
#if defined(QUICK_SORT_IMPLEMENTED)
    cout << " QUICK";
#endif
#if defined(MERGE_SORT_IMPLEMENTED)
    cout << " MERGE";
#endif
#if defined(INSERTION_SORT_LL_IMPLEMENTED)
    cout << " INSERTION-LL";
#endif
#if defined(SELECTION_SORT_LL_IMPLEMENTED)
    cout << " SELECTION-LL";
#endif
#if defined(MERGE_SORT_LL_IMPLEMENTED)
    cout << " MERGE-LL";
#endif
    cout << endl;

    // Short lists
    TestSortIncreasingSequence(10, g);
    TestSortDoubledSequence(10, g);
    TestSortAllZeroSequence(10, g);
    cout << "->Sort Testing Successful for Lists of length = 10" << endl;

    // Medium lists
    TestSortIncreasingSequence(100, g);
    TestSortDoubledSequence(100, g);
    TestSortAllZeroSequence(100, g);
    cout << "->Sort Testing Successful for Lists of length = 100" << endl;

    // Longer lists
    TestSortIncreasingSequence(500, g);
    TestSortDoubledSequence(500, g);
    TestSortAllZeroSequence(500, g);
    cout << "->Sort Testing Successful for Lists of length = 500" << endl;

    // Very Long lists
    TestSortIncreasingSequence(1000, g);
    TestSortDoubledSequence(1000, g);
    TestSortAllZeroSequence(1000, g);
    cout << "->Sort Testing Successful for Lists of length = 1000" << endl;

    cout << "Correctness Testing Complete" << endl;
}

void TestSortIncreasingSequence(size_t length, default_random_engine& g) {
    VariableArrayList<int> sortedListAscending;

    // Load list with sequence 0..length-1
    for (int i = 0; i < length; i++) {
        sortedListAscending.Insert(sortedListAscending.Size(), i);
    }
    TestAllSorts(sortedListAscending, g);
}

void TestSortDoubledSequence(size_t length, default_random_engine& g) {
    VariableArrayList<int> sortedListAscending;

    // Load list with doubled sequence 0 0 1 1 ..length-1 length-1
    for (int i = 0; i < length; i ++) {
        sortedListAscending.Insert(sortedListAscending.Size(), i);
        sortedListAscending.Insert(sortedListAscending.Size(), i);
    }
    TestAllSorts(sortedListAscending, g);
}

void TestSortAllZeroSequence(size_t length, default_random_engine& g) {
    VariableArrayList<int> allZeroList;

    // Load list with all zeroes
    for (int i = 0; i < length; i ++) {
        allZeroList.Insert(i, 0);
    }
    TestAllSorts(allZeroList, g);
}

#define NUMBER_SHUFFLES    50

void TestAllSorts(const VariableArrayList<int>& sortedAscending, default_random_engine& g) {
    SinglyLinkedList<int> sortedAscendingSLL;

    // Replicate correct lists into linked lists
    for (size_t pos = 0; pos < sortedAscending.Size(); pos ++) {
        int item;

        sortedAscending.Get(pos, item);
        sortedAscendingSLL.Insert(pos, item);
    }

    VariableArrayList<int> shuffled = sortedAscending;
    SinglyLinkedList<int> shuffledSLL = sortedAscendingSLL;

    // Shuffle and sort
    for (int i = 0; i < NUMBER_SHUFFLES; i ++) {
#if defined(INSERTION_SORT_IMPLEMENTED)
        TestArraySort(InsertionSort, shuffled, sortedAscending);
        if (sortedAscending.Size() <= 500) {
            TestSLLSort(InsertionSort, shuffledSLL, sortedAscendingSLL);
        }
#endif
#if defined(SELECTION_SORT_IMPLEMENTED)
        TestArraySort(SelectionSort, shuffled, sortedAscending);
        if (sortedAscending.Size() <= 500) {
#if defined(SINGLY_LINKED_LIST_IMPLEMENTED)
            TestSLLSort(SelectionSort, shuffledSLL, sortedAscendingSLL);
#endif
        }
#endif
#if defined(SHELL_SORT_IMPLEMENTED)
        TestArraySort(ShellSort, shuffled, sortedAscending);
        if (sortedAscending.Size() <= 500) {
#if defined(SINGLY_LINKED_LIST_IMPLEMENTED)
            TestSLLSort(ShellSort, shuffledSLL, sortedAscendingSLL);
#endif
        }
#endif
#if defined(QUICK_SORT_IMPLEMENTED)
        TestArraySort(QuickSort, shuffled, sortedAscending);
        if (sortedAscending.Size() <= 500) {
#if defined(SINGLY_LINKED_LIST_IMPLEMENTED)
            TestSLLSort(QuickSort, shuffledSLL, sortedAscendingSLL);
#endif
        }
#endif
#if defined(MERGE_SORT_IMPLEMENTED)
        TestArraySort(MergeSort, shuffled, sortedAscending);
        if (sortedAscending.Size() <= 500) {
#if defined(SINGLY_LINKED_LIST_IMPLEMENTED)
            TestSLLSort(MergeSort, shuffledSLL, sortedAscendingSLL);
#endif
        }
#endif
#if defined(INSERTION_SORT_LL_IMPLEMENTED)
        TestSLLSort(InsertionSortLL, shuffledSLL, sortedAscendingSLL);
#endif
#if defined(SELECTION_SORT_LL_IMPLEMENTED)
        TestSLLSort(SelectionSortLL, shuffledSLL, sortedAscendingSLL);
#endif
#if defined(MERGE_SORT_LL_IMPLEMENTED)
        TestSLLSort(MergeSortLL, shuffledSLL, sortedAscendingSLL);
#endif
        // Don't shuffle first time to check sorted list gets sorted
        Shuffle(shuffled, g);
        Shuffle(shuffledSLL, g);
    }
}

void TestArraySort(SortType type, VariableArrayList<int> toSort, const VariableArrayList<int>& correctlySorted) {
    Sort<int> sorter;

    switch(type) {
#if defined(INSERTION_SORT_IMPLEMENTED)
        case InsertionSort:
            sorter.InsertionSort(toSort);
            break;
#endif
#if defined(SELECTION_SORT_IMPLEMENTED)
        case SelectionSort:
            sorter.SelectionSort(toSort);
            break;
#endif
#if defined(SHELL_SORT_IMPLEMENTED)
        case ShellSort:
            sorter.ShellSort(toSort);
            break;
#endif
#if defined(QUICK_SORT_IMPLEMENTED)
        case QuickSort:
            sorter.QuickSort(toSort, 0, toSort.Size()-1);
            break;
#endif
#if defined(MERGE_SORT_IMPLEMENTED)
        case MergeSort:
            sorter.MergeSort(toSort);
            break;
#endif
        default:
            assert(false);
            break;
    }

    CheckSortOK(type, toSort, correctlySorted);
}

void TestSLLSort(SortType type, SinglyLinkedList<int> toSort, const SinglyLinkedList<int>& correctlySorted) {
    Sort<int> sorter;

    switch(type) {
#if defined(INSERTION_SORT_IMPLEMENTED)
        case InsertionSort:
            sorter.InsertionSort(toSort);
            break;
#endif
#if defined(SELECTION_SORT_IMPLEMENTED)
        case SelectionSort:
            sorter.SelectionSort(toSort);
            break;
#endif
#if defined(SHELL_SORT_IMPLEMENTED)
        case ShellSort:
            sorter.ShellSort(toSort);
            break;
#endif
#if defined(QUICK_SORT_IMPLEMENTED)
        case QuickSort:
            sorter.QuickSort(toSort, 0, toSort.Size()-1);
            break;
#endif
#if defined(MERGE_SORT_IMPLEMENTED)
        case MergeSort:
            sorter.MergeSort(toSort);
            break;
#endif
#if defined(INSERTION_SORT_LL_IMPLEMENTED)
        case InsertionSortLL:
            toSort.InsertionSort();
            break;
#endif
#if defined(SELECTION_SORT_LL_IMPLEMENTED)
        case SelectionSortLL:
            toSort.SelectionSort();
            break;
#endif
#if defined(MERGE_SORT_LL_IMPLEMENTED)
        case MergeSortLL:
            toSort.MergeSort();
            break;
#endif
        default:
            assert(false);
            break;
    }

    CheckSortOK(type, toSort, correctlySorted);
}

void CheckSortOK(SortType type, const List<int>& toSort, const List<int>& correctlySorted) {
    assert(toSort.Size() == correctlySorted.Size());
    for (int i = 0; i < toSort.Size(); i ++) {
        int item1;
        int item2;

        toSort.Get(i, item1);
        correctlySorted.Get(i, item2);
        if (item1 != item2) {
            cout << "Not sorted: ";
            switch (type) {
                case InsertionSort:
                    cout << "SortType = InsertionSort";
                    break;
                case SelectionSort:
                    cout << "SortType = SelectionSort";
                    break;
                case ShellSort:
                    cout << "SortType = ShellSort";
                    break;
                case QuickSort:
                    cout << "SortType = QuickSort";
                    break;
                case MergeSort:
                    cout << "SortType = MergeSort";
                    break;
                case InsertionSortLL:
                    cout << "SortType = InsertionSortLL";
                    break;
                case SelectionSortLL:
                    cout << "SortType = SelectionSortLL";
                    break;
                case MergeSortLL:
                    cout << "SortType = MergeSortLL";
                    break;
                default:
                    assert(false);
                    break;
            }
            cout << "\tYour Sort: " << toSort << endl;
            cout << "\tExpected Sort: " << correctlySorted << endl;
            assert(false);
        }
    }
}
