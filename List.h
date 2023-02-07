//
// Interface Definition for the List Base Class
// Author: Max Benson
// Date: 08/06/2021
//

#ifndef LIST_H
#define LIST_H


template <typename ItemType>
class List {
public:
    virtual ~List() {
    };

    // Other methods
    virtual bool Get(size_t position, ItemType& item) const = 0;
    virtual int Find(const ItemType& item, size_t start = 0) const = 0;
    virtual bool Insert(size_t position, const ItemType& item) = 0;
    virtual bool Replace(size_t position, const ItemType& item) = 0;
    virtual bool Swap(size_t position1, size_t position2) = 0;
    virtual bool Remove(size_t position, ItemType& item) = 0;
    virtual void Clear() = 0;

    size_t Size() const {
        return _size;
    }

    virtual bool CheckConsistency() const = 0;

    friend ostream& operator<<(ostream& os, const List& list) {
        list.ToOstream(os);
        return os;
    }

protected:
    virtual void ToOstream(ostream& os) const = 0;

    size_t _size;
};


#endif //LIST_H
