#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>
#include "/Users/hronov/Lab4/Task5/vector.h"

template <typename T>
struct StackNode {
    T data;
    StackNode* next;
    StackNode(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class GoodStack {
private:
    StackNode<T>* top;

    void copyFrom(const GoodStack& other) {
        if (other.top == nullptr) {
            top = nullptr;
            return;
        }

        GoodVector<const StackNode<T>*> nodes;
        StackNode<T>* current = other.top;
        while (current) {
            nodes.push_back(current);
            current = current->next;
        }

        top = new StackNode<T>(nodes.back()->data);
        StackNode<T>* last = top;
        for (int i = static_cast<int>(nodes.size()) - 2; i >= 0; --i) {
            last->next = new StackNode<T>(nodes[i]->data);
            last = last->next;
        }
    }


public:
    GoodStack() : top(nullptr) {}

    GoodStack(const GoodStack& other) : top(nullptr) {
        copyFrom(other);
    }

    GoodStack& operator=(const GoodStack& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    ~GoodStack() {
        clear();
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(const T& value) {
        StackNode<T>* newNode = new StackNode<T>(value);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        StackNode<T>* temp = top;
        top = top->next;
        delete temp;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return top->data;
    }

    StackNode<T>* getTop() const {
        return top;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool eraseByValue(const T& value) {
        StackNode<T>* current = top;
        StackNode<T>* prev = nullptr;

        while (current) {
            if (current->data == value) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    top = current->next;
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }
};

#endif // STACK_H
