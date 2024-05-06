// COP3503C: Project 1 (Linked Lists)
// Pt4: LinkedList.h
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
    void PrintReverse() const;

    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;
    Node* GetNode(unsigned int index);
    const Node* GetNode(unsigned int index) const;

    Node* Find(const T& info);

    // Class Member functions (NEW)
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T& info);
    bool RemoveAt(unsigned int index);
    void Clear();

    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;

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
unsigned int LinkedList<T>::NodeCount() const {
    return node_count;
}

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



// Class Member functions (NEW)
template <typename T>
bool LinkedList<T>::RemoveHead() {
    if (head != nullptr) {
        if (node_count == 1) {
            delete head;
            node_count -= 1;
            head = nullptr;
            tail = nullptr;
            return true;
        }
        // set new head to head's next, set head's next prev as null
        Node *new_head = head->next;
        new_head->prev = nullptr;
        // delete head node
        delete head;
        // set new_head's  as head
        head = new_head;
        // dec node count
        node_count -= 1;
        return true;
    }
    else {
        return false;
    }
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
    if (tail != nullptr) {
        if (node_count == 1) {
            delete tail;
            node_count -= 1;
            head = nullptr;
            tail = nullptr;
            return true;
        }
        // set new tail to tail's prev, set tail's prev next as null
        Node* new_tail = tail->prev;
        new_tail->next = nullptr;
        // delete tail node
        delete tail;
        // set new_tail as tail
        tail = new_tail;
        // dec node count
        node_count -= 1;
        return true;
    }
    else {
        return false;
    }
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T& info) {         //changed data to info
    int count = 0;
    Node* current = head;
    for (unsigned int i = 0; i < node_count; ++i) {
        if (current->data == info) {
            // set current's next prev to current's prev, set current's prev next to current's next
            if (current->next != nullptr) {
                current->next->prev = current->prev;
                if (current->prev == nullptr) {
                    current->next->prev = nullptr;
                }
            }
            else if ((current->next == nullptr) && (current->prev != nullptr)) {
                tail = current->prev;
                current->prev->next = nullptr;
            }
            if (current->prev != nullptr) {
                current->prev->next = current->next;
                if (current->next == nullptr) {
                    current->prev->next = nullptr;
                }
            }
            else if ((current->prev == nullptr) && (current->next != nullptr)) {
                    head = current->next;
                    current->next->prev = nullptr;
            }
            // delete current
            Node* temp = current->next;
            delete current;
            current = temp;
            // dec node_count
            node_count -= 1;
            // inc deleted count
            count += 1;
        }
        current = current->next;
    }
    return count;
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
    if (index > node_count) {
        return false;
    }
    else {
        Node* ptr = GetNode(index);
        // set pointer's next prev to pointer's prev, set pointer's prev next to pointer's next
        if (ptr->next != nullptr) {
            ptr->next->prev = ptr->prev;
        }
        else if ((ptr->next == nullptr) && (ptr->prev != nullptr)) {
            tail = ptr->prev;
        }
        if (ptr->prev != nullptr) {
            ptr->prev->next = ptr->next;
        }
        else if ((ptr->prev == nullptr) && (ptr->next != nullptr)) {
            head = ptr->next;
        }
        // delete ptr
        delete ptr;
        // dec node_count
        node_count -= 1;
        return true;
    }
}

template <typename T>
void LinkedList<T>::Clear() {
    for (unsigned int i = 0; i < node_count; ++i) {
        // set current to head's next, set head's next prev to null
        Node* current = head->next;
        current->prev = nullptr;
        // delete head, make new head
        delete head;
        head = current;
        // dec node_count
        node_count -= 1;
    }
    head = nullptr;
    tail = nullptr;
    node_count = 0;
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {
    const Node* current = node;
    if (current == tail) {
        std::cout << current->data << std::endl;
    }
    else {
        std::cout << current->data << std::endl;
        PrintForwardRecursive(current->next);
    }
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
    const Node* current = node;
    if (current == head) {
        std::cout << current->data << std::endl;
    }
    else {
        std::cout << current->data << std::endl;
        PrintReverseRecursive(current->prev);
    }
}
