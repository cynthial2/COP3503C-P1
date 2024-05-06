// COP3503C: Project 1 (Linked Lists)
// Pt3: LinkedList.h
// Last edited: 10/12/22

#include <iostream>
#include <vector>
#include <string>
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
    unsigned int NodeCount() const;
    void PrintForward() const;

    Node* Find(const T& info);
    Node* GetNode(unsigned int index);
    const Node* GetNode(unsigned int index) const;

    // Class member functions (NEW)
    void InsertAfter(Node* node, const T& info);
    void InsertBefore(Node* node, const T& info);
    void InsertAt(const T& info, unsigned int index);

    // Operators
    const T& operator[](unsigned int index) const;
    T& operator[](unsigned int index);

    // Operators (NEW)
    bool operator==(const LinkedList<T>& rhs) const;

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
unsigned int LinkedList<T>::NodeCount() const {
    return node_count;
}

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

// Operators
template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
    return GetNode(index)->data;
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
    return GetNode(index)->data;
}




// Class member functions (NEW)
template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& info) {        //changed data to info
    // create new node
    Node* temp = new Node;
    temp->data = info;
    // set temp's prev to given node, set temp's next to given node's next
    temp->prev = node;
    temp->next = node->next;
    // set given node's next to temp, set temp's next node's prev to temp
    node->next = temp;
    if (temp->next != nullptr) {
        temp->next->prev = temp;
    }
    else {
        tail = temp;
    }
    // inc node count
    node_count += 1;
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& info) {      //changed data to info
    // create new node
    Node* temp = new Node;
    temp->data = info;
    // set temp's prev to given node's prev, set temp's next to given node
    temp->prev = node->prev;
    temp->next = node;
    // set given node's prev to temp, set temp's prev node's next to temp
    node->prev = temp;
    if (temp->prev != nullptr) {
        temp->prev->next = temp;
    }
    else {
        head = temp;
    }
    // inc node count
    node_count += 1;
}

template <typename T>
void LinkedList<T>::InsertAt(const T& info, unsigned int index) {    //changed data to info
    if (index > node_count) {
        throw std::out_of_range("An error has occurred.");
    }
    else if (index == node_count) {
        AddTail(info);
    }
    else {
        Node *ptr = GetNode(index);
        InsertBefore(ptr, info);
    }
}


// Operators (NEW)
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
    // compare sizes (count rhs nodes)
    unsigned int count = 0;
    Node* current_rhs = rhs.head;
    while (current_rhs != nullptr) {
        count += 1;
        current_rhs = current_rhs->next;
    }
    if (count != node_count) {
        return false;
    }
    // compare each value in linked list (loop through each value)
    current_rhs = rhs.head;
    Node* current_lhs = head;
    while (current_rhs != nullptr) {
        if (current_rhs->data != current_lhs->data) {
            return false;
        }
        current_rhs = current_rhs->next;
        current_lhs = current_lhs->next;
    }
    return true;
}