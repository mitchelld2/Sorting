//
// Implementation of methods for sorting singly linked lists
// Author: Max Benson
// Modified by:
// Date: 09/10/2021
// Modification Date:
//

#ifndef SLL_SORTING_H
#define SLL_SORTING_H

/**
 * Perform insertion sort on a linked list
 */
template <typename ItemType>
void SinglyLinkedList<ItemType>::InsertionSort() {
    assert(false);
}

/**
 * Perform selection sort on a linked list
 */
template <typename ItemType>
void SinglyLinkedList<ItemType>::SelectionSort() {
    assert(false);
}

/**
 * Perform merge sort on a linked list
 */
template <typename ItemType>
void SinglyLinkedList<ItemType>::MergeSort()
{
    _head = DoMergeSort(_head, this->_size);
}

/**
 * Recursive merge sort routine
 * @param chain - linked chain of nodes to sort
 * @param length - number of nodes in chain
 */
template <typename ItemType>
typename SinglyLinkedList<ItemType>::Node* SinglyLinkedList<ItemType>::DoMergeSort(Node* chain, size_t length)
{
    Node* sorted;

    if(length > 1)
    {
        _head = chain;
        Node* first = nullptr;
        Node* second = nullptr;
        size_t position = length/2;

        Node* temp;
        temp = GetPtrToNodeAtPosition(position - 1);
        first = chain;
        second = temp->next;
        SplitIntoTwo(chain, position, &first, &second);  //Split nodeChain into two chains of “equal” length

        Node* postFirst = DoMergeSort(first,  position);    //Call DoMergeSort on first chain
        Node* postSecond = DoMergeSort(second,length - position);   //Call DoMergeSort on second chain

        sorted = MergeSortedLists(postFirst, postSecond);
    }
    else
    {
        return chain;
    }
    return sorted;   //Return sorted merge of first and second chain
}

/**
 * Break a chain of nodes into two chains
 * @param ptr - start of linked chain of nodes
 * @param position - position to break the chain
 * @param first - receives a pointer to a chain of nodes at positions 0 to position-1
 * @param second - receives a pointer to a chain of nodes at positions position through the end
 */
template <typename ItemType>                                  //partition
void SinglyLinkedList<ItemType>::SplitIntoTwo(Node* ptr, size_t position, Node** first, Node** second)
{
    Node* temp;
    temp = GetPtrToNodeAtPosition(position - 1);
    //first = &ptr;
    //second = &temp->next;
    temp->next = nullptr;
}

/**
 * Returns sorted merge of two sorted chains of nodes
 * @param first - receives a pointer to a sorted chain of  of nodes
 * @param second - receives a pointer to a sorted chain of nodes
 * @return sorted merge of two linked lists
 */
template <typename ItemType>
typename SinglyLinkedList<ItemType>::Node* SinglyLinkedList<ItemType>::MergeSortedLists(Node* first, Node* second)
{
    Node* sorted;

    if(first == nullptr)
    {
        return second;
    }
    else if(second == nullptr)
    {
        return first;
    }
    if(first->item <= second->item)
    {
        sorted = first;
        sorted->next = MergeSortedLists(first->next, second);
    }
    else//(second->item < first->item)
    {
        sorted = second;
        sorted->next = MergeSortedLists(first, second->next);
    }
    return sorted;
}

#endif //SLL_SORTING_H
