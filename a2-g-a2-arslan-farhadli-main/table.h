/**************************************************************************/
/*                                                                        */
/*  Starter file for a2                                                   */ 
/*                                                                        */
/*  Author1 Name: <Zulfiyya Farhadli>                                     */
/* -ChainingTable(const ChainingTable& other);                            */
/* -ChainingTable(ChainingTable&& other);                                 */
/* -virtual int numRecords() const;                                       */
/* -virtual int capacity() const;                                         */
/* -virtual bool find(const std::string& key, TYPE& value);               */
/* -virtual const ChainingTable& operator=(const ChainingTable& other);   */
/* -void destruct()                                                       */
/* -void copy(ChainingTable const& other)                                 */
/* -int hash(std::string const& key) const noexcept                       */
/* -SearchRes search                                                      */
/*  Author2 Name: <Gozde Arslan>                                          */
/*                                                                        */
/* - virtual void update(const std::string& key, const TYPE& value);      */
/* - virtual bool remove(const std::string& key);                         */
/* - virtual ~ChainingTable();                                            */
/* - virtual bool isEmpty() const;                                        */
/* - virtual const ChainingTable& operator=(ChainingTable&& other);       */
/* - bool needsRehash() const noexcept                                    */
/* - void move(ChainingTable&& other) noexcept                            */
/* - void rehash()                                                        */
/* - struct SearchRes()                                                   */
/* -struct Record                                                         */
/**************************************************************************/

#include <string>
#include <utility>
#include <functional>
#include "mylist.h"

template <class TYPE>
class Table {
public:
    Table() {}
    virtual void update(const std::string& key, const TYPE& value) = 0;
    virtual bool remove(const std::string& key) = 0;
    virtual bool find(const std::string& key, TYPE& value) = 0;
    virtual int numRecords() const = 0;
    virtual bool isEmpty() const = 0;
    virtual int capacity() const = 0;
    virtual ~Table() {}
};




template <class TYPE>
class SimpleTable :public Table<TYPE> {

    struct Record {
        TYPE data_;
        std::string key_;
        Record(const std::string& key, const TYPE& data) {
            key_ = key;
            data_ = data;
        }

    };

    Record** records_;   //the table
    int capacity_;       //capacity of the array

    void grow() {
        Record** tmp = new Record * [capacity_ * 2 + 1];
        for (int i = 0; i < capacity_; i++) {
            tmp[i] = records_[i];
        }
        for (int i = capacity_; i < capacity_ * 2 + 1; i++) {
            tmp[i] = nullptr;
        }
        delete[] records_;
        records_ = tmp;
        capacity_ *= 2;
    }
public:
    SimpleTable(int capacity);
    SimpleTable(const SimpleTable& rhs);
    SimpleTable(SimpleTable&& rhs);
    virtual void update(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const SimpleTable& operator=(const SimpleTable& rhs);
    virtual const SimpleTable& operator=(SimpleTable&& rhs);
    virtual ~SimpleTable();
    virtual bool isEmpty() const { return numRecords() == 0; }
    virtual int numRecords() const;
    virtual int capacity() const { return capacity_; }

};

// numRecords runtime :	- O(n)


template <class TYPE>
int SimpleTable<TYPE>::numRecords() const {
    int rc = 0; // 1
    for (int i = 0; records_[i] != nullptr; i++) { // n
        rc++; // n
    }
    return rc; // 1

   \
}


//runtime :O(n)

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity) : Table<TYPE>() {
    records_ = new Record * [capacity + 1]; // O(n)
    capacity_ = capacity; // 1
    for (int i = 0; i < capacity_ + 1; i++) { // n
        records_[i] = nullptr; // n
    }

    // O(n)
}
// copy ctor runtime :		- O(n^2)


template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& rhs) {
    records_ = new Record * [rhs.capacity_ + 1]; // O(n)
    capacity_ = rhs.capacity_; // 1
    for (int i = 0; i < capacity_ + 1; i++) { // n
        records_[i] = nullptr; // n
    }
    for (int i = 0; i < rhs.numRecords(); i++) { // n*n
        update(rhs.records_[i]->key_, rhs.records_[i]->data_); // n * n
    }
}



template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& rhs) {
    capacity_ = rhs.capacity_;
    records_ = rhs.records_;
    rhs.records_ = nullptr;
    rhs.capacity_ = 0;
}

// update (1) runtime : O(n^2)

template <class TYPE>
void SimpleTable<TYPE>::update(const std::string& key, const TYPE& value) {
    int idx = -1;
    int sz = numRecords(); // n
    for (int i = 0; i < sz; i++) { // n
        if (records_[i]->key_ == key) {
            idx = i;
        }
    }
    if (idx == -1) {
        if (numRecords() == capacity_) { // n
            grow();
        }
        records_[numRecords()] = new Record(key, value); // n
        for (int i = numRecords() - 1; i > 0 && records_[i]->key_ < records_[i - 1]->key_; i--) { // n
            Record* tmp = records_[i];
            records_[i] = records_[i - 1];
            records_[i - 1] = tmp;
        }

    }
    else {
        records_[idx]->data_ = value;
    }

}
// remove	runtime :		- O(n^2)

template <class TYPE>
bool SimpleTable<TYPE>::remove(const std::string& key) {
    int idx = -1;
    int size = numRecords();
    for (int i = 0; i < size; i++) { // n
        if (records_[i]->key_ == key) {
            idx = i;
        }
    }
    if (idx != -1) {

        delete records_[idx];
        for (int i = idx; i < numRecords() - 1; i++) { // n*n
            records_[i] = records_[i + 1];
        }
        records_[size - 1] = nullptr;
        return true;
    }
    else {
        return false;
    }
}
// find runtime :	- O(n^2)

template <class TYPE>
bool SimpleTable<TYPE>::find(const std::string& key, TYPE& value) {
    int idx = -1;
    for (int i = 0; i < numRecords(); i++) { // n*n
        if (records_[i]->key_ == key) {
            idx = i;
        }
    }
    if (idx == -1)
        return false;
    else {
        value = records_[idx]->data_;
        return true;
    }
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& rhs) {
    if (this != &rhs) {
        if (records_) {
            while (numRecords() != 0) {
                remove(records_[0]->key_);
            }
            delete[] records_;
        }
        records_ = new Record * [rhs.capacity_ + 1];
        capacity_ = rhs.capacity_;
        for (int i = 0; i < capacity_; i++) {
            records_[i] = nullptr;
        }
        for (int i = 0; i < rhs.numRecords(); i++) {
            update(rhs.records_[i]->key_, rhs.records_[i]->data_);
        }

    }
    return *this;
}
}
// move assign runtime :	 - O(n)
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& rhs) {
    if (records_) {
        while (numRecords() != 0) { // n*n
            remove(records_[0]->key_); // n * n^2
        }
        delete[] records_;
    }
    records_ = rhs.records_;
    capacity_ = rhs.capacity_;
    rhs.records_ = nullptr;
    rhs.capacity_ = 0;

    return *this;
}
// dtor	 runtime :	- O(n)
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable() {
    if (records_) {
        int sz = numRecords();
        for (int i = 0; i < sz; i++) { // n
            remove(records_[0]->key_);
        }
        delete[] records_;
    }
}




template <class TYPE>
class ChainingTable : public Table<TYPE> {
private:
    struct Record {
        std::string key;
        TYPE value;
    };

    using List = Sentinel<Record>;

    List* m_data = nullptr;
    int m_elemCount = 0;
    int m_capacity = 0;
    double m_maxLoadFactor = 0.5;


    bool needsRehash() const noexcept {
        return static_cast<double>(m_elemCount) / m_capacity > m_maxLoadFactor;
    }

    void destruct() {
        delete[] m_data;
        m_elemCount = 0;
        m_capacity = 0;
        m_maxLoadFactor = 0;
        m_data = nullptr;
    }

    void copy(ChainingTable const& other) {
        destruct();
        m_data = new List[other.capacity()];

        for (int i = 0; i < other.capacity(); ++i) {
            m_data[i] = other.m_data[i];
        }

        m_elemCount = other.m_elemCount;
        m_capacity = other.m_capacity;
        m_maxLoadFactor = other.m_maxLoadFactor;
    }

    void move(ChainingTable&& other) noexcept {
        m_data = other.m_data;
        m_elemCount = other.m_elemCount;
        m_capacity = other.m_capacity;
        m_maxLoadFactor = other.m_maxLoadFactor;

        other.m_data = nullptr;
        other.m_elemCount = 0;
        other.m_capacity = 0;
        other.m_maxLoadFactor = 0;
    }

    int hash(std::string const& key) const noexcept {
        return std::hash<std::string>{}(key) % m_capacity;
    }

    void rehash() {
        auto const old_data = m_data;
        auto const old_size = m_capacity;

        m_capacity *= 2;

        m_data = new List[m_capacity];
        for (int i = 0; i < old_size; ++i)
        {
            for (auto it = old_data[i].begin(); it != old_data[i].end(); ) {
                auto const key_hash = hash(it->key);


                m_data[key_hash].splice_back(it++, old_data[i]);
            }
        }
        delete[] old_data;
    }

    struct SearchRes {
        List* list = nullptr;
        typename List::iterator it{};
        SearchRes(List* lst, typename List::iterator it) :list(lst), it(it) {};
        bool isFound() const {
            return list && list->end() != it;
        }
    };

    SearchRes search(std::string const& key) const {
        auto const key_hash = hash(key);

        auto& list = m_data[key_hash];

        SearchRes res{ &list, list.end() };

        for (auto it = list.begin(); it != list.end(); ++it)
        {
            if (it->key == key) {
                res.it = it;
                break;
            }
        }

        return res;
    }

public:
    ChainingTable(int maxExpected, double maxLoadFactor);
    ChainingTable(const ChainingTable& other);
    ChainingTable(ChainingTable&& other);
    virtual void update(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const ChainingTable& operator=(const ChainingTable& other);
    virtual const ChainingTable& operator=(ChainingTable&& other);
    virtual ~ChainingTable();
    virtual bool isEmpty() const;
    virtual int numRecords() const;
    virtual int capacity() const;
};
//constructor for the ChanningTable class.It would construct a table and initialize an list of
//records based on the provided arguments: adouble maxLoadFactor and int capacity.
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int capacity, double maxLoadFactor)
    : Table<TYPE>()
    , m_data(new List[capacity])
    , m_elemCount(0)
    , m_capacity(capacity)
    , m_maxLoadFactor(maxLoadFactor)
{ }
// Copy Constructor that constructs a new table by copying another table
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other) {
    copy(other);
}
//Move Constructor which constructs a new table by moving records from another table to this one.
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other) {
    move(static_cast<ChainingTable<TYPE>&&>(other));
}

//This function takes two arguments: a string called key and a templated data type called value. 
//The key is used to decide the clash key as well as to confirm if the key already exists within the table of records. 
//The value will be used to either change an existing record with matching keys or to add a new record into the table with the key and value arguments.
//This function returns void
template <class TYPE>
void ChainingTable<TYPE>::update(const std::string& key, const TYPE& value) {
    auto search_res = search(key);

    if (search_res.isFound()) {
        search_res.it->value = value;
    }
    else {
        ++m_elemCount;
        search_res.list->push_back(Record{ key, value });
        if (needsRehash())
            rehash();
    }
}
//function takes in one argument: a string called key.
//The key is used to determine the collision key as well as confirm if the key already exists within the table of records and is ready for removal. 
//This function will return a boolean: True - if the key has been found within the table of records
//False - if the key has not been found within the table of records
template <class TYPE>
bool ChainingTable<TYPE>::remove(const std::string& key) {
    auto search_res = search(key);

    if (!search_res.isFound())
        return false;

    --m_elemCount;
    search_res.list->erase(search_res.it);

    return true;
}
//This function takes in two arguments: a string called key and a templated data type called value. 
//The key is used to determine the collision key as well as confirm if it already exists within the table of records. 
//The value will be changed and sent back if the key has been found within the records.
//This function will return a boolean : True - if an search record with a matching key has been found.
//False - if the search recond will not found 

template <class TYPE>
bool ChainingTable<TYPE>::find(const std::string& key, TYPE& value) {
    auto const search_res = search(key);
    if (!search_res.isFound()) return false;

    value = search_res.it->value;
    return true;
}
//Copy Operator which returns the the copied table
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other) {
    if (this != &other)
        copy(other);
    return *this;

}
// Move Operator which returns the moved table
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other) {
    if (this != &other)
        move(static_cast<ChainingTable<TYPE>&&>(other));
    return *this;

}
//Destructor
template <class TYPE>
ChainingTable<TYPE>::~ChainingTable() {
    destruct();
}
//checks the list elements if its empty
template <class TYPE>
bool ChainingTable<TYPE>::isEmpty() const {
    return m_elemCount == 0;
}
//returns number of elements 
template <class TYPE>
int ChainingTable<TYPE>::numRecords() const {
    return m_elemCount;
}
//returns capacity of list 
template <class TYPE>
int ChainingTable<TYPE>::capacity() const {
    return m_capacity;
}

