//
// Interface Definition for the SinglyLinkedList Class
// Author: Max Benson
// Date: 07/23/2021
//

#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <iostream>
using std::ostream;

#include "List.h"

template <typename ItemType>
class SinglyLinkedList : public List<ItemType>  {
private:
    struct Node{
        ItemType item;
        Node* next;
    };
    Node* _head;
public:
    SinglyLinkedList();

    // Rule of Three
    ~SinglyLinkedList() override;
    SinglyLinkedList(const SinglyLinkedList&);
    const SinglyLinkedList& operator=(const SinglyLinkedList&);

    // Other methods
    bool Get(size_t position, ItemType& item) const override;
    int Find(const ItemType& item, size_t start = 0) const override;
    bool Insert(size_t position, const ItemType& item) override;
    bool Replace(size_t position, const ItemType& item) override;
    bool Swap(size_t position1, size_t position2) override;
    bool Remove(size_t position, ItemType& item) override;
    void Clear() override;
    bool CheckConsistency() const override;

    // Sort methods
    void InsertionSort();
    void SelectionSort();
    void MergeSort();

protected:
    //Stream output
    virtual void ToOstream(ostream& os) const override;

private:
    Node* GetPtrToNodeAtPosition(size_t position) const;

    // Sorting helper methods
    Node* DoMergeSort(Node* chain, size_t length);
    void SplitIntoTwo(Node* ptr, size_t position, Node** first, Node** second);
    Node* MergeSortedLists(Node* first, Node* second);
};

/**
 * Default constructor
 * Creates an empty list.
 */
template <typename ItemType>
SinglyLinkedList<ItemType>::SinglyLinkedList() {
    _head = nullptr;
    this->_size = 0;
}

/**
 * Destructor
 * Frees the dynamic memory allocated for the list
 */
template <typename ItemType>
SinglyLinkedList<ItemType>::~SinglyLinkedList() {
    Clear();
}

/**
 * Copy Constructor
 * Creates a deep copy of the list as it traverses through
 * the other list.  Because we keep a pointer to the link field
 * of the last node of the new list as we go, we can create
 * a new node and append it to the end of the list in O(1) time.
 * The running time of the whole method is O(N) time where N is the
 * length of the list
 * @param other the list to be copied
 */
template <typename ItemType>
SinglyLinkedList<ItemType>::SinglyLinkedList(const SinglyLinkedList& other) {
    Node** linkPptr = &_head;

    _head = nullptr;
    for (Node* nodePtr = other._head; nodePtr != nullptr; nodePtr = nodePtr->next) {
        Node* newNode;

        newNode = new Node;
        newNode->item = nodePtr->item;
        newNode->next = nullptr;
        *linkPptr = newNode;
        linkPptr = &(*linkPptr)->next;
    }
    this->_size = other._size;
}

/**
 * Copy assignment operator
 * Enables deep copy assignment using the operator = overload.
 * Uses the copy constructor to copy the rhs.  Then swaps internals of
 * the copy with this.  By doing it this way, the old contents
 * of this will be automatically freed when the method finishes.
 * The running time of this method is the same as the copy
 * constructor , i.e. O(N)
 * @param rhs the object to be copied into this
 * @return this to enable cascade assignments
 */
template <typename ItemType>
const SinglyLinkedList<ItemType>& SinglyLinkedList<ItemType>::operator=(const SinglyLinkedList& rhs) {
    if (this != &rhs) {
        Node** linkPptr = &_head;

        Clear();
        for (Node* nodePtr = rhs._head; nodePtr != nullptr; nodePtr = nodePtr->next) {
            Node* newNode;

            newNode = new Node;
            newNode->item = nodePtr->item;
            newNode->next = nullptr;
            *linkPptr = newNode;
            linkPptr = &(*linkPptr)->next;
        }
        this->_size = rhs._size;
    }
    return *this;
}

/**
 * Get  the item at a specified position
 * This method runs in O(position) time.
 * @param position the position of the element to retrieve.
 * @param item the item found at position
 * @return true if valid position given, false otherwise
 */
template <typename ItemType>
bool SinglyLinkedList<ItemType>::Get(size_t position, ItemType& item) const {
    if (position < this->_size) {
        Node* ptr = GetPtrToNodeAtPosition(position);

        item = ptr->item;
        return true;
    }
    return false;
}

/**
 * Searches for the position of the first matching item in the list starting
 * at position "start".  The method performs a linear search for the item.
 * If the element is found it returns the position, if it is not found it
 * returns -1.
 * The running time of this method depends on where the search starts
 * and where the item is found (if it is found)
 * @param item the object that the client is searching for.
 * @param start position at which to start the search
 * @return the position of the element if found, -1 otherwise.
 */
template <typename ItemType>
int SinglyLinkedList<ItemType>::Find(const ItemType& item, size_t start)  const {
    if (start < this->_size) {
        Node *ptr;

        // First navigate to start position
        ptr = GetPtrToNodeAtPosition(start);

        // Now search for the item, returning its position if found
        for (int curPosition = start; ptr != nullptr; ptr = ptr->next, curPosition++) {
            if (ptr->item == item) {
                return curPosition;
            }
        }
    }
    return -1;
}

/**
 * Inserts an element into a given position so long as the position is valid.
 * This method runs in O(position) time.
 * @param item what the client wants to insert into the list
 * @param position the position where the element is to be inserted
 * @return true if it was possible to insert, false otherwise.
 */
template <typename ItemType>
bool SinglyLinkedList<ItemType>::Insert(size_t position, const ItemType& item) {
    if (position > this->_size) {
        return false;
    }
    else {
        Node* newNode;

        newNode = new Node;
        newNode->item = item;
        if (0 == position) {
            newNode->next = _head;
            _head = newNode;
        }
        else {
            Node* prevNode;

            prevNode = GetPtrToNodeAtPosition(position-1);
            newNode->next = prevNode->next;
            prevNode->next = newNode;
        }
        this->_size ++;
        return true;
    }
}

/**
 * Replace  the item at a specified position
 * @param position the position of the element to retrieve.
 * @param item the new item to insert in the old one's place
 * @return true if valid position given, false otherwise
 */
template <typename ItemType>
bool SinglyLinkedList<ItemType>::Replace(size_t position, const ItemType& item) {
    if (position < this->_size) {
        Node* ptr = GetPtrToNodeAtPosition(position);

        ptr->item = item;
        return true;
    }
    return false;
}

/**
 * Swap elements in specified positions
 * @param position1 the position of the first element
 * @param position2 the position of the second element
 * @return true if valid positions were given, false otherwise
 */
template <typename ItemType>
bool SinglyLinkedList<ItemType>::Swap(size_t position1, size_t position2) {
    if (position1 < this->_size && position2 < this->_size) {
        Node* ptr1 = GetPtrToNodeAtPosition(position1);
        Node* ptr2 = GetPtrToNodeAtPosition(position2);
        ItemType tmp;

        tmp = ptr1->item;
        ptr1->item = ptr2->item;
        ptr2->item = tmp;
        return true;
    }
    return false;
}

/**
 * Removes the item at position, so long as the position is valid. The item previously
 * stored in the list is returned in the supplied parameter.
 * This method runs in O(position) time.
 * @param position the position of the element to be removed.
 * @param item the item previously stored in the list
 * @return true if node could be deleted, false if position at end of list or invalid,
 */
template <typename ItemType>
bool SinglyLinkedList<ItemType>::Remove(size_t position, ItemType& item) {
    if (position >= this->_size) {
        return false;
    }
    else {
        Node *nodeToZap;

        if (0 == position) {
            nodeToZap = _head;
            _head = _head->next;
        }
        else {
            Node *prevNode;

            prevNode = GetPtrToNodeAtPosition(position-1);
            nodeToZap = prevNode->next;
            prevNode->next = nodeToZap->next;
        }

        item = nodeToZap->item;
        delete nodeToZap;
        this->_size--;
        return true;
    }
}

/**
 * Clear the list, freeing the dynamic memory allcoated for the list
 * and then resetting _head to nullptr.
 * This method runs in O(N) time where N is the length of the list.
 */
template <typename ItemType>
void SinglyLinkedList<ItemType>::Clear() {
    size_t numberToRemove = this->_size;

    for (size_t i = 0; i < numberToRemove; i ++) {
        ItemType item;

        Remove(0, item);
    }
}

/**
 * Checks if list has correct number of nodes and is linked properly
 * This method runs in O(N) time where N is the number of items in list
 * @return true if list consistent, false otherwise
 */
template <typename ItemType>
bool SinglyLinkedList<ItemType>::CheckConsistency() const {
    size_t position;
    Node* ptr;

    for (position = 0, ptr = _head; position < this->_size && ptr != nullptr; position ++, ptr = ptr->next) {
    }
    return position == this->_size && ptr == nullptr;
};

/**
 * Output list to an ostream
 */
template <typename ItemType>
void SinglyLinkedList<ItemType>::ToOstream(ostream& os) const {
    os << "[";
    for (Node* ptr = _head; ptr != nullptr; ptr = ptr->next) {
        if (ptr  != _head) {
            os << ", ";
        }
        os << ptr->item;
    }
    os << "]";
}

/**
 * Iterate through nodes of list to get pointer to node at a particular position.
 * Used for implementation of Get and Find methods.  Since those methods are
 * declared const, this method is as well.  Since this method id private, it assumes
 * that caller will pass a position of an actual item in the list..
 * @param position index in list between 0 and number of items-1
 * @return pointer to node corresponding to that position
 */
template <typename ItemType>
typename SinglyLinkedList<ItemType>::Node* SinglyLinkedList<ItemType>::GetPtrToNodeAtPosition(size_t position) const {
    Node *ptr;
    size_t curPosition;

    assert(position < this->_size);
    for (ptr = _head,  curPosition = 0, ptr = _head ; curPosition < position; curPosition ++, ptr = ptr->next ) {
    }
    return ptr;
}

#include "SLL_Sorting.h"

#endif //SINGLYLINKEDLIST_H
