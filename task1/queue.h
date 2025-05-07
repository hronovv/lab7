#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include <iostream>

/*
 *
 *  1.Queue supports FIFO principle, basically reailed with the doubly linked list
 *  2.Linked list contains struct Node
 *  3.Node itself has a value(element)
 *
*/

template <typename T>
struct Node {
    T value; // contatins value
    Node* next; // pointer to the next node(element) in the queue
    Node* prev; // pointer to the previous node (used for doubly linked queue)


    explicit Node(T data) : value(data), next(nullptr), prev(nullptr) {} // if last -> nullptr

    ~Node() = default;
};
// struct that defines 1 element of the queue


template <typename T>
class GoodQueue {
private:
    Node<T>* head; // pointer to the 1st element in the queue
    Node<T>* tail; // pointer to the last element in the queue
    size_t size_ = 0;

public:

    //constructors && destructor

    GoodQueue() : head(nullptr), tail(nullptr) {}

    explicit GoodQueue(T data) : head(nullptr), tail(nullptr), size_(0) {
        push(data);
    }

    GoodQueue(std::initializer_list<T> list) : head(nullptr), tail(nullptr), size_(0) {
        for (const T& value : list) {
            push(value);
        }
    }

    GoodQueue(const GoodQueue& other) : head(nullptr), tail(nullptr), size_(0) {
        Node<T>* current = other.head;
        while (current) {
            push(current->value);
            current = current->next;
        }
    }

    ~GoodQueue() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    //assignment operator

    GoodQueue& operator=(const GoodQueue& other) {
        if (this == &other) {
            return *this;
        }

        clear();

        Node<T>* current = other.head;
        while (current) {
            push(current->value);
            current = current->next;
        }

        return *this;
    }

    // basic functions of the queue

    T& front() {
        if (empty()) {
            throw std::runtime_error("Queue has no elements");
        }
        return head->value;
    }

    const T& front() const {
        if (empty()) {
            throw std::runtime_error("Queue has no elements");
        }
        return head->value;
    }

    T& back() {
        if (empty()) {
            throw std::runtime_error("Queue has no elements");
        }
        return tail->value;
    }

    const T& back() const {
        if (empty()) {
            throw std::runtime_error("Queue has no elements");
        }
        return tail->value;
    }


    [[nodiscard]] bool empty() const {
        return head == nullptr;
    }

    [[nodiscard]] size_t size() const {
        return size_;
    }

    void push(T data) {
        auto* new_node = new Node<T>(data);

        if (empty()) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        size_++;
    }

    void pop() {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node<T>* temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
        }
        size_--;
    }

    void clear() {
        while (!empty()) {
            pop();
        }
    }

    //for debugging

    void print() const {
        Node<T>* current = head;
        while (current) {
            std::cout << "Element of queue - " << current->value << std::endl;
            current = current->next;
        }
        std::cout << std::endl;
    }
};


#endif //QUEUE_H
