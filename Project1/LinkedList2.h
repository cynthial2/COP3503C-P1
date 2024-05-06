// COP3503C: Project 1 (Linked Lists)
// Pt2: LinkedList.h
// Last edited: 10/12/22

#include <iostream>
#include <vector>
#pragma once

template <typename T>
class LinkedList {

public:
    // Nested Node Class
    struct Node {
        T data;
        Node* next = nullptr;
        Node* prev = nullptr;
    };

private:

    unsigned int node_count;
    Node* head;
    Node* tail;

    void Set(const LinkedList<T>& list);

public:

    // Default constructor
    LinkedList();

    // Destructor
    ~LinkedList();

    // Copy Constructor
    LinkedList(const LinkedList<T>& list);

    // Copy Assignment Operator
    LinkedList<T> &operator=(const LinkedList<T>& list);

    // Class member functions
    void AddHead(const T& info);
    void AddTail(const T& info);
    void PrintForward() const;

    // Class member functions (NEW)

    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;
    Node* GetNode(unsigned int index);
    const Node* GetNode(unsigned int index) const;

    Node* Find(const T& info);
    const Node* Find(const T& info) const;
    void FindAll(std::vector<Node*>& outData, const T& value) const;

    // Operators (NEW)
    const T& operator[](unsigned int index) const;
    T& operator[](unsigned int index);

};

/// IMPLEMENTATION BELOW ///

// Constructor
template <typename T>
LinkedList<T>::LinkedList() {
    node_count = 0;
    head = nullptr;
    tail = nullptr;
}

// Destructor
template <typename T>
LinkedList<T>::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        current = head->next;
        delete head;
        head = current;
    }
}

// Repeated code in copy constructor/copy assignment operator
template <typename T>
void LinkedList<T>::Set(const LinkedList<T>& list) {
    // copy nodes from list
    head = nullptr;
    tail = nullptr;
    node_count = 0;
    Node* current = list.head;
    while (true) {
        AddTail(current->data);
        current = current->next;
        if (current == nullptr) {
            break;
        }
    }
}

// Copy Constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& list) {
    // copy data from list
    Set(list);
}

// Copy Assignment Operator
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list) {
    // delete all nodes and reset all values
    Node* temp = head;
    while (temp != nullptr) {
        temp = head->next;
        delete head;
        head = temp;
    }
    // Copy data over from list
    Set(list);
    return *this;
}

// Class member functions

template <typename T>
void LinkedList<T>::AddHead(const T& info) {         //changed data > info
    // create new node
    Node* temp = new Node;
    temp->data = info;
    // set temp's next to current head, set current head's prev to temp
    temp->next = head;
    if (head != nullptr) {
        head->prev = temp;
    }
    // set current head to temp node (set tail to new temp node is null)
    head = temp;
    if (tail == nullptr) {
        tail = temp;
    }
    // inc node count
    node_count += 1;
}

template <typename T>
void LinkedList<T>::AddTail(const T& info) {             //changed data > info
    // create new node
    Node* temp = new Node;
    temp->data = info;
    // set temp's prev to current tail, set current tail's next to temp
    temp->prev = tail;
    if (tail != nullptr) {
        tail->next = temp;
    }
    // set current tail to temp node (set head to new temp node if null)
    tail = temp;
    if (head == nullptr) {
        head = temp;
    }
    // inc node count
    node_count += 1;
}

template <typename T>
void LinkedList<T>::PrintForward() const {
    Node* current = head;
    for (unsigned int i = 0; i < node_count; ++i) {
        if (current != nullptr) {
            std::cout << current->data << std::endl;
            current = current->next;
        }
    }
}



// Class member functions (NEW)

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
    return head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
    return head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
    return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
    return tail;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
    if (index > node_count-1) {
        throw std::out_of_range("An error has occurred.");
    }
    Node* current = head;
    for (unsigned int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
    if (index > node_count-1) {
        throw std::out_of_range("An error has occurred.");
    }
    Node* current = head;
    for (unsigned int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& info) {        //changed data to info
    Node* current = head;
    for (unsigned int i = 0; i < node_count; ++i) {
        if (current->data == info) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& info) const {         //changed data to info
    Node* current = head;
    for (unsigned int i = 0; i < node_count; ++i) {
        if (current->data == info) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template <typename T>
void LinkedList<T>::FindAll(std::vector<Node*>& outData, const T& value) const {
    Node* current = head;
    for (unsigned int i = 0; i < node_count; ++i) {
        if (current->data == value) {
            outData.push_back(current);
        }
        current = current->next;
    }
}


// Operators (NEW)

template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
    return GetNode(index)->data;
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
    return GetNode(index)->data;
}





