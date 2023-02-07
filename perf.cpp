//
// Created by Max Benson on 9/6/2021.
//

#include <assert.h>
#include <iostream>
#include <random>
#include <chrono>
using std::cout;
using std::endl;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;
using std::default_random_engine;
using std::uniform_int_distribution;

#include "Sort.h"

#define NUMBER_TIMINGS      100

void TestInsertionSort(List<int>& list, default_random_engine& g);
void TestSelectionSort(List<int>& list, default_random_engine& g);
void TestShellSort(List<int>& list, default_random_engine& g);
void TestQuickSort(List<int>& list, default_random_engine& g);
void TestMergeSort(List<int>& list, default_random_engine& g);
#if defined (SINGLY_LINKED_LIST_IMPLEMENTED)
void TestInsertionSortLL(SinglyLinkedList<int>& list, default_random_engine& g);
void TestSelectionSortLL(SinglyLinkedList<int>& list, default_random_engine& g);
void TestMergeSortLL(SinglyLinkedList<int>& list, default_random_engine& g);
#endif
void Shuffle(List<int>& list, default_random_engine& g);

void TestSortType(SortType sortType) {
    default_random_engine g;
    int nToTest[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000 };
    bool sortTypeIsLL = (InsertionSortLL == sortType ||SelectionSortLL == sortType ||MergeSortLL == sortType);

    // Display Title
    string startTitle = "Performance Comparison of ";
    string endTitle = " between List Implementations";

    switch (sortType) {
#if defined(INSERTION_SORT_IMPLEMENTED)
        case InsertionSort:
            cout << startTitle << "Insertion Sort" << endTitle << endl;
            break;
#endif
#if defined(SELECTION_SORT_IMPLEMENTED)
        case SelectionSort:
            cout << startTitle << "Selection Sort" << endTitle << endl;
            break;
#endif
#if defined(SHELL_SORT_IMPLEMENTED)
        case ShellSort:
            cout << startTitle << "Shell Sort" << endTitle << endl;
            break;
#endif
#if defined(QUICK_SORT_IMPLEMENTED)
        case QuickSort:
            cout << startTitle << "Quick Sort" << endTitle << endl;
            break;
#endif
#if defined(MERGE_SORT_IMPLEMENTED)
        case MergeSort:
            cout << startTitle << "Merge Sort" << endTitle << endl;
            break;
#endif
#if defined(INSERTION_SORT_LL_IMPLEMENTED)
        case InsertionSortLL:
            break;
#endif
#if defined(SELECTION_SORT_LL_IMPLEMENTED)
        case SelectionSortLL:
            break;
#endif
#if defined(MERGE_SORT_LL_IMPLEMENTED)
        case MergeSortLL:
            break;
#endif
        default:
            cout <<"No Sort Types Implemented" << endl;
            return;
    }

    // Output table
    for (int i = 0; i < sizeof(nToTest)/sizeof(nToTest[0]); i ++) {
        int N = nToTest[i];

        // Print column headers
        if (0 == i) {
            cout << "N";
        }

        // Cut offs
        switch(sortType) {
            case InsertionSort:
            case SelectionSort:
                if (N > 500) {
                    return;
                }
                break;
            case ShellSort:
            case MergeSort:
                if (N > 1000) {
                    return;
                }
                break;
            case QuickSort:
                if (N > 2000) {
                    return;
                }
                break;
        }
        VariableArrayList<int> listVAL;
        if (0 == i  && !sortTypeIsLL) {
            cout << '\t' << "Array";
        }
        // Load list with sequence 0..n-1
        for (int i = 0; i < N; i++) {
            listVAL.Insert(listVAL.Size(), i);
        }
#if defined(SINGLY_LINKED_LIST_IMPLEMENTED)
        SinglyLinkedList<int> listSLL;
        if (0 == i) {
           cout << '\t' << "SinglyLinked";
        }
        // Load list with sequence 0..n-1
        for (int i = 0; i < N; i++) {
            listSLL.Insert(listSLL.Size(), i);
        }
#endif
        if (0 == i) {
           cout << endl;
        }

        cout << N;
        switch(sortType) {
            case InsertionSort:
                TestInsertionSort(listVAL, g);
#if defined(SINGLY_LINKED_LIST_IMPLEMENTED)
                TestInsertionSort(listSLL, g);
#endif
                break;
            case SelectionSort:
                TestSelectionSort(listVAL, g);
#if defined(SINGLY_LINKED_LIST_IMPLEMENTED)
                TestSelectionSort(listSLL, g);
#endif
                break;
            case ShellSort:
                TestShellSort(listVAL, g);
#if defined(SINGLY_LINKED_LIST_IMPLEMENTED)
                TestShellSort(listSLL, g);
#endif
                break;
            case QuickSort:
                TestQuickSort(listVAL, g);
#if defined(SINGLY_LINKED_LIST_IMPLEMENTED)
                TestQuickSort(listSLL, g);
#endif
                break;
            case MergeSort:
                TestMergeSort(listVAL, g);
#if defined(SINGLY_LINKED_LIST_IMPLEMENTED)
                TestMergeSort(listSLL, g);
#endif
                break;
            case InsertionSortLL:
#if defined(INSERTION_SORT_LL_IMPLEMENTED)
#if defined(SINGLY_LINKED_LIST_IMPLEMENTED)
                TestInsertionSortLL(listSLL, g);
#endif
#endif
                break;
            case SelectionSortLL:
#if defined(SELECTION_SORT_LL_IMPLEMENTED)
#if defined(SINGLY_LINKED_LIST_IMPLEMENTED)
                TestSelectionSortLL(listSLL, g);
#endif
#endif
                break;
            case MergeSortLL:
#if defined(MERGE_SORT_LL_IMPLEMENTED)
#if defined(SINGLY_LINKED_LIST_IMPLEMENTED)
                TestMergeSortLL(listSLL, g);
#endif
#endif
                break;
            default:
                assert(false);
                break;
        }
        cout << endl;
    }
}

void TestListType(ListType listType) {
    default_random_engine g;
    int nToTest[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000 };
    string startTitle = "Performance Times for ";
    string endTitle = " Sort Methods";

    // Display heading
    switch(listType) {
        case Array:
            cout << startTitle << "Array List" << endTitle << endl;
            break;
#if defined(SINGLY_LINKED_LIST_IMPLEMENTED)
        case SinglyLinked:
            cout << startTitle << "Singly Linked List" << endTitle << endl;
            break;
#endif
        default:
            cout << "No list types implemented" << endl;
            return;
    }

    for (int i = 0; i < sizeof(nToTest)/sizeof(nToTest[0]); i ++) {
        int N = nToTest[i];
        List<int>* listToTest;

        // Exit early for singly linked list -- executes too slowly
        if (SinglyLinked == listType && N > 600) {
            break;
        }

        VariableArrayList<int> listVAL;
        // Load list with sequence 0..n-1
        for (int i = 0; i < N; i++) {
            listVAL.Insert(listVAL.Size(), i);
        }
        if (Array == listType) {
            listToTest = &listVAL;
        }
#if defined(SINGLY_LINKED_LIST_IMPLEMENTED)
        SinglyLinkedList<int> listSLL;
        // Load list with sequence 0..n-1
        for (int i = 0; i < N; i++) {
            listSLL.Insert(listSLL.Size(), i);
        }
        if (SinglyLinked == listType) {
            listToTest = &listSLL;
        }
#endif
#if defined(DOUBLY_LINKED_LINKED_IMPLEMENTED)
        DoublyLinkedList<int> listDLL;
        // Load list with sequence 0..n-1
        for (int i = 0; i < n; i++) {
            listDLL.Insert(listDLL.Size(), i);
        }
        if (DoublyLinked == listType) {
            listToTest = &listDLL;
        }
#endif

        // Print column headers
        if (0 == i) {
            cout << "N";
#if defined(INSERTION_SORT_IMPLEMENTED)
            cout << '\t' << "Insertion";
#endif
#if defined(SELECTION_SORT_IMPLEMENTED)
            cout << '\t' << "Selection";
#endif
#if defined(SHELL_SORT_IMPLEMENTED)
            cout << '\t' << "Shell";
#endif
#if defined(QUICK_SORT_IMPLEMENTED)
            cout << '\t' << "Quick";
#endif
#if defined(MERGE_SORT_IMPLEMENTED)
            cout << '\t' << "Merge";
#endif
#if defined(INSERTION_SORT_LL_IMPLEMENTED)
            if (SinglyLinked == listType) {
                cout << '\t' << "InsertionLL";
            }
#endif
#if defined(SELECTION_SORT_LL_IMPLEMENTED)
            if (SinglyLinked == listType) {
                cout << '\t' << "SelectionLL";
            }
#endif
#if defined(MERGE_SORT_LL_IMPLEMENTED)
            if (SinglyLinked == listType) {
                cout << '\t' << "MergeLL";
            }
#endif
            cout << endl;
        }

        cout << N;
#if defined(INSERTION_SORT_IMPLEMENTED)
        TestInsertionSort(*listToTest, g);
#endif
#if defined(SELECTION_SORT_IMPLEMENTED)
        TestSelectionSort(*listToTest, g);
#endif
#if defined(SHELL_SORT_IMPLEMENTED)
        TestShellSort(*listToTest, g);
#endif
#if defined(QUICK_SORT_IMPLEMENTED)
        TestQuickSort(*listToTest, g);
#endif
#if defined(MERGE_SORT_IMPLEMENTED)
        TestMergeSort(*listToTest, g);
#endif
#if defined(INSERTION_SORT_LL_IMPLEMENTED)
        if (SinglyLinked == listType) {
            TestInsertionSortLL(listSLL, g);
        }
#endif
#if defined(SELECTION_SORT_LL_IMPLEMENTED)
        if (SinglyLinked == listType) {
            TestSelectionSortLL(listSLL, g);
        }
#endif
#if defined(MERGE_SORT_LL_IMPLEMENTED)
        if (SinglyLinked == listType) {
            TestMergeSortLL(listSLL, g);
        }
#endif
        cout << endl;
    }
}

void TestInsertionSort(List<int>& list, default_random_engine& g) {
#if defined(INSERTION_SORT_IMPLEMENTED)
    Sort<int> sorter;
    long long ns = 0;

    for (int i = 0; i < NUMBER_TIMINGS; i++) {
        steady_clock::time_point begin = steady_clock::now();
        sorter.InsertionSort(list);
        steady_clock::time_point end = steady_clock::now();
        ns += duration_cast<nanoseconds>(end - begin).count();
        Shuffle(list, g);
    }
    cout << '\t' << ns;
#else
    assert(false);
#endif
}

void TestSelectionSort(List<int>& list, default_random_engine& g) {
#if defined(SELECTION_SORT_IMPLEMENTED)
    Sort<int> sorter;
    long long ns = 0;

    for (int i = 0; i < NUMBER_TIMINGS; i++) {
        steady_clock::time_point begin = steady_clock::now();
        sorter.SelectionSort(list);
        steady_clock::time_point end = steady_clock::now();
        ns += duration_cast<nanoseconds>(end - begin).count();
        Shuffle(list, g);
    }
    cout << '\t' << ns;
#else
        assert(false);
#endif
}

void TestShellSort(List<int>& list, default_random_engine& g) {
#if defined(SHELL_SORT_IMPLEMENTED)
    Sort<int> sorter;
    long long ns = 0;

    for (int i = 0; i < NUMBER_TIMINGS; i++) {
        steady_clock::time_point begin = steady_clock::now();
        sorter.ShellSort(list);
        steady_clock::time_point end = steady_clock::now();
        ns += duration_cast<nanoseconds>(end - begin).count();
        Shuffle(list, g);
    }
    cout << '\t' << ns;
#else
    assert(false);
#endif
}

void TestQuickSort(List<int>& list, default_random_engine& g) {
#if defined(QUICK_SORT_IMPLEMENTED)
    Sort<int> sorter;
    long long ns = 0;

    for (int i = 0; i < NUMBER_TIMINGS; i++) {
        steady_clock::time_point begin = steady_clock::now();
        sorter.QuickSort(list, 0, list.Size()-1);
        steady_clock::time_point end = steady_clock::now();
        ns += duration_cast<nanoseconds>(end - begin).count();
        Shuffle(list, g);
    }
    cout << '\t' << ns;
#else
    assert(false);
#endif
}

void TestMergeSort(List<int>& list, default_random_engine& g) {
#if defined(MERGE_SORT_IMPLEMENTED)
    Sort<int> sorter;
    long long ns = 0;

    for (int i = 0; i < NUMBER_TIMINGS; i++) {
        steady_clock::time_point begin = steady_clock::now();
        sorter.MergeSort(list);
        steady_clock::time_point end = steady_clock::now();
        ns += duration_cast<nanoseconds>(end - begin).count();
        Shuffle(list, g);
    }
    cout << '\t' << ns;
#else
    assert(false);
#endif
}

#if defined(SINGLY_LINKED_LIST_IMPLEMENTED)
void TestInsertionSortLL(SinglyLinkedList<int>& list, default_random_engine& g) {
#if defined(INSERTION_SORT_LL_IMPLEMENTED)
    long long ns = 0;

    for (int i = 0; i < NUMBER_TIMINGS; i++) {
        steady_clock::time_point begin = steady_clock::now();
        list.InsertionSort();
        steady_clock::time_point end = steady_clock::now();
        ns += duration_cast<nanoseconds>(end - begin).count();
        Shuffle(list, g);
    }
    cout << '\t' << ns;
#else
    assert(false);
#endif
}

void TestSelectionSortLL(SinglyLinkedList<int>& list, default_random_engine& g) {
#if defined(SELECTION_SORT_LL_IMPLEMENTED)
    long long ns = 0;

    for (int i = 0; i < NUMBER_TIMINGS; i++) {
        steady_clock::time_point begin = steady_clock::now();
        list.SelectionSort();
        steady_clock::time_point end = steady_clock::now();
        ns += duration_cast<nanoseconds>(end - begin).count();
        Shuffle(list, g);
    }
    cout << '\t' << ns;
#else
    assert(false);
#endif
}

void TestMergeSortLL(SinglyLinkedList<int>& list, default_random_engine& g) {
#if defined(MERGE_SORT_LL_IMPLEMENTED)
    long long ns = 0;

    for (int i = 0; i < NUMBER_TIMINGS; i++) {
        steady_clock::time_point begin = steady_clock::now();
        list.MergeSort();
        steady_clock::time_point end = steady_clock::now();
        ns += duration_cast<nanoseconds>(end - begin).count();
        Shuffle(list, g);
    }
    cout << '\t' << ns;
#else
    assert(false);
#endif
}
#endif

void Shuffle(List<int>& list, default_random_engine& g) {
    for (int i = list.Size()-1; i > 0; i --) {
        uniform_int_distribution<int> d(0,i);
        int j = d(g);

        list.Swap(i, j);
    }
}
