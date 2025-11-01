#pragma once

#include <stdexcept>

class Node {
public:
    int id; 
    Node* next;
    Node* prev;
    Node(int id, Node* prev_node = nullptr, Node* next_node = nullptr) 
        : id(id), prev(prev_node), next(next_node) {}
};

class Path {
public:
    Node* top; 
    Node* tail; 

    Path(int initial_id) : top(nullptr), tail(nullptr) {
        Node* initialNode = new Node(initial_id);

        top = initialNode;
        tail = initialNode;
        
        top->next = top; 
        top->prev = top;
    }

    void append_node(int new_id) {
        if (!top) {
            return; 
        }

        Node* newNode = new Node(new_id, tail, top); 

        tail->next = newNode;
        top->prev = newNode;
    
        tail = newNode;
    }

    ~Path() {
        if (!top) return;

        Node* current = top->next;
        Node* temp;

        tail->next = nullptr; 
        top->prev = nullptr;

        while (current != nullptr) {
            temp = current;
            current = current->next;
            delete temp;
        }
        delete top;
        top = nullptr;
        tail = nullptr;
    }
};