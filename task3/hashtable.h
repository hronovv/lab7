#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "stack.h"
#include <iostream>
#include <functional>
#include <memory>
#include <utility>

template <typename Key, typename Value>
class GoodHashTable {
private:
    static constexpr int TABLE_SIZE = 10;
    std::unique_ptr<GoodStack<std::pair<Key, Value>>> table[TABLE_SIZE];

    int hash(const Key& key) const {
        return std::hash<Key>{}(key) % TABLE_SIZE;
    }

public:
    GoodHashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = std::make_unique<GoodStack<std::pair<Key, Value>>>();
        }
    }


    GoodHashTable(const GoodHashTable& other) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = std::make_unique<GoodStack<std::pair<Key, Value>>>(*other.table[i]);
        }
    }

    GoodHashTable& operator=(const GoodHashTable& other) {
        if (this != &other) {
            for (int i = 0; i < TABLE_SIZE; ++i) {
                table[i] = std::make_unique<GoodStack<std::pair<Key, Value>>>(*other.table[i]);
            }
        }
        return *this;
    }

    void insert(const Key& key, const Value& value) {
        int index = hash(key);
        StackNode<std::pair<Key, Value>>* current = table[index]->getTop();
        while (current) {
            if (current->data.first == key) {
                current->data.second = value;
                return;
            }
            current = current->next;
        }
        table[index]->push(std::make_pair(key, value));
    }

    Value search(const Key& key) const {
        int index = hash(key);
        StackNode<std::pair<Key, Value>>* current = table[index]->getTop();
        while (current) {
            if (current->data.first == key) {
                return current->data.second;
            }
            current = current->next;
        }
        throw std::runtime_error("Key not found");
    }


    void erase(const Key& key) {
        int index = hash(key);
        StackNode<std::pair<Key, Value>>* current = table[index]->getTop();
        while (current) {
            if (current->data.first == key) {
                table[index]->eraseByValue(current->data);
                return;
            }
            current = current->next;
        }
    }

    void display() const {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            std::cout << "Bucket " << i << ": ";
            StackNode<std::pair<Key, Value>>* current = table[i]->getTop();
            while (current) {
                std::cout << "{" << current->data.first << ": " << current->data.second << "} ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }

    GoodStack<std::pair<Key, Value>>* getBucket(int index) {
        if (index < 0 || index >= TABLE_SIZE) {
            std::cerr << "Invalid index" << std::endl;
            return nullptr;
        }
        return table[index].get();
    }

    static int getTableSize() {
        return TABLE_SIZE;
    }

    void clear() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i]->clear();
        }
    }

};

#endif // HASHTABLE_H
