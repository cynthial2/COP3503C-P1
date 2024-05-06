// COP3503C: Project 1 (Linked Lists)
// Pt1: LinkedList.h
// Last edited: 10/12/22

#include <iostream>
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
    LinkedList &operator=(const LinkedList<T>& list);

    // Class member functions
    void AddHead(const T& info);
    void AddTail(const T& info);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);

    unsigned int NodeCount() const;

    void PrintForward() const;
    void PrintReverse() const;

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
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
    for (int i = count-1; i >= 0; --i) {
        AddHead(data[i]);
    }
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
    for (unsigned int i = 0; i < count; ++i) {
        AddTail(data[i]);
    }
}

template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
    return node_count;
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

template <typename T>
void LinkedList<T>::PrintReverse() const {
    Node* current = tail;
    for (unsigned int i = 0; i < node_count; ++i) {
        if (current != nullptr) {
            std::cout << current->data << std::endl;
            current = current->prev;
        }
    }
}

