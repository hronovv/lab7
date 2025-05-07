#ifndef DEQUEUE_H
#define DEQUEUE_H

#include <cstddef>
#include <stdexcept>
#include <iostream>

inline constexpr short kBlockSize = 64;
inline constexpr size_t kInitialMapSize = 8;

template<typename T, size_t BlockSize = kBlockSize>
struct Block {
    T elements[BlockSize];
};

template<typename T, size_t BlockSize = kBlockSize>
class GoodDeque {
private:
    Block<T, BlockSize>** blocks;
    size_t map_capacity;
    size_t start_block;
    size_t start_index;
    size_t end_block;
    size_t end_index;
    size_t size_;

    void reserve() {
        size_t new_map_capacity = map_capacity * 2;
        size_t new_center = new_map_capacity / 2;

        Block<T, BlockSize>** new_blocks = new Block<T, BlockSize>*[new_map_capacity];
        for (size_t i = 0; i < new_map_capacity; ++i) {
            new_blocks[i] = nullptr;
        }

        size_t num_blocks = end_block - start_block + 1;

        size_t new_start_block = new_center - num_blocks / 2;

        for (size_t i = 0; i < num_blocks; ++i) {
            new_blocks[new_start_block + i] = blocks[start_block + i];
        }

        start_block = new_start_block;
        end_block = start_block + num_blocks - 1;

        map_capacity = new_map_capacity;

        delete[] blocks;
        blocks = new_blocks;

        for (size_t i = 0; i < map_capacity; ++i) {
            if (blocks[i] == nullptr) {
                blocks[i] = new Block<T, BlockSize>();
            }
        }

    }




public:
    GoodDeque()
        : map_capacity(kInitialMapSize),
          start_block(kInitialMapSize / 2),
          start_index(0),
          end_block(kInitialMapSize / 2),
          end_index(0),
          size_(0)
    {
        blocks = new Block<T, BlockSize>*[map_capacity];
        for (size_t i = 0; i < map_capacity; ++i) {
            blocks[i] = nullptr;
        }
        blocks[start_block] = new Block<T, BlockSize>();
    }

    ~GoodDeque() {
        for (size_t i = 0; i < map_capacity; ++i) {
            delete blocks[i];
        }
        delete[] blocks;
    }

    GoodDeque(const GoodDeque& other)
        : map_capacity(other.map_capacity),
          start_block(other.start_block),
          start_index(other.start_index),
          end_block(other.end_block),
          end_index(other.end_index),
          size_(other.size_)
    {
        blocks = new Block<T, BlockSize>*[map_capacity];
        for (size_t i = 0; i < map_capacity; ++i) {
            blocks[i] = other.blocks[i] ? new Block<T, BlockSize>(*other.blocks[i]) : nullptr;
        }
    }

    GoodDeque& operator=(const GoodDeque& other) {
        if (this == &other) return *this;

        for (size_t i = 0; i < map_capacity; ++i) {
            delete blocks[i];
        }
        delete[] blocks;

        map_capacity = other.map_capacity;
        start_block = other.start_block;
        start_index = other.start_index;
        end_block = other.end_block;
        end_index = other.end_index;
        size_ = other.size_;

        blocks = new Block<T, BlockSize>*[map_capacity];
        for (size_t i = 0; i < map_capacity; ++i) {
            blocks[i] = other.blocks[i] ? new Block<T, BlockSize>(*other.blocks[i]) : nullptr;
        }

        return *this;
    }

    T& front() {
        if (empty()) throw std::runtime_error("Deque is empty");
        return blocks[start_block]->elements[start_index];
    }

    const T& front() const {
        if (empty()) throw std::runtime_error("Deque is empty");
        return blocks[start_block]->elements[start_index];
    }

    T& back() {
        if (empty()) throw std::runtime_error("Deque is empty");
        size_t idx = (end_index == 0) ? BlockSize - 1 : end_index - 1;
        size_t blk = (end_index == 0) ? end_block - 1 : end_block;
        return blocks[blk]->elements[idx];
    }

    const T& back() const {
        if (empty()) throw std::runtime_error("Deque is empty");
        size_t idx = (end_index == 0) ? BlockSize - 1 : end_index - 1;
        size_t blk = (end_index == 0) ? end_block - 1 : end_block;
        return blocks[blk]->elements[idx];
    }

    void push_back(const T& value) {
        if (end_block >= map_capacity) {
            reserve();
        }
        if (blocks[end_block] == nullptr) {
            blocks[end_block] = new Block<T, BlockSize>();
        }
        blocks[end_block]->elements[end_index] = value;
        ++end_index;
        ++size_;
        if (end_index == BlockSize) {
            end_index = 0;
            ++end_block;
            if (end_block >= map_capacity) {
                reserve();
            }

            if (blocks[end_block] == nullptr) {
                blocks[end_block] = new Block<T, BlockSize>();
            }
        }

    }

    void push_front(const T& value) {
        if ((start_block == 0 && start_index == 0) || blocks[start_block] == nullptr) {
            reserve();
        }

        if (start_index == 0) {
            --start_block;
            if (blocks[start_block] == nullptr) {
                blocks[start_block] = new Block<T, BlockSize>();
            }
            start_index = BlockSize;
        }

        --start_index;
        blocks[start_block]->elements[start_index] = value;
        ++size_;
    }


    void pop_back() {
        if (empty()) throw std::runtime_error("Deque is empty");

        if (end_index == 0) {
            --end_block;
            end_index = BlockSize;
        }

        --end_index;
        blocks[end_block]->elements[end_index] = T(); // Optional clear
        --size_;

        if (size_ == 0) {
            start_block = end_block;
            start_index = end_index;
        }
    }

    void pop_front() {
        if (empty()) throw std::runtime_error("Deque is empty");

        blocks[start_block]->elements[start_index] = T(); // Optional clear
        ++start_index;
        if (start_index == BlockSize) {
            ++start_block;
            start_index = 0;
        }

        --size_;

        if (size_ == 0) {
            start_block = end_block;
            start_index = end_index;
        }
    }

    void clear() {
        for (size_t i = 0; i < map_capacity; ++i) {
            delete blocks[i];
            blocks[i] = nullptr;
        }
        start_block = map_capacity / 2;
        end_block = map_capacity / 2;
        start_index = 0;
        end_index = 0;
        size_ = 0;
    }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
};

#endif // DEQUEUE_H
