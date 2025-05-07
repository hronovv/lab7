#include <stdexcept>
#include <vector>
#include <functional>
#include "iostream"

template <typename Key, typename Value>
class GoodHashTable {
private:
    struct HashNode {
        Key key;
        Value value;
        bool occupied = false;
        bool deleted = false;
    };

    std::vector<HashNode> table;
    int table_size;
    int current_size;

    int hash(const Key& key) const {
        return std::hash<Key>{}(key) % table_size;
    }

    int probe(int index, int i) const {
        const int c1 = 1;
        const int c2 = 1;
        return (index + c1 * i + c2 * i * i) % table_size;
    }

    void rehash() {
        int new_size = table_size * 2;
        std::vector<HashNode> new_table(new_size);

        for (const auto& node : table) {
            if (node.occupied && !node.deleted) {
                int index = std::hash<Key>{}(node.key) % new_size;
                for (int i = 0; i < new_size; ++i) {
                    int probeIndex = probe(index, i);
                    if (!new_table[probeIndex].occupied) {
                        new_table[probeIndex] = node;
                        break;
                    }
                }
            }
        }

        table = std::move(new_table);
        table_size = new_size;
    }

public:
    GoodHashTable(int size) : table_size(size), current_size(0) {
        table.resize(table_size);
    }


    void insert(const Key& key, const Value& value) {
        int index = hash(key);


        if (current_size >= table_size / 2) {
            rehash();
        }

        for (int i = 0; i < table_size; ++i) {
            int probeIndex = probe(index, i);


            if (!table[probeIndex].occupied || table[probeIndex].deleted) {
                table[probeIndex].key = key;
                table[probeIndex].value = value;
                table[probeIndex].occupied = true;
                table[probeIndex].deleted = false;
                ++current_size;
                return;
            }
        }


        throw std::runtime_error("Table is full");
    }


    Value search(const Key& key) const {
        int index = hash(key);
        for (int i = 0; i < table_size; ++i) {
            int probeIndex = probe(index, i);
            if (!table[probeIndex].occupied) {
                break;
            }
            if (table[probeIndex].key == key && !table[probeIndex].deleted) {
                return table[probeIndex].value;
            }
        }
        throw std::runtime_error("Key not found");
    }


    void erase(const Key& key) {
        int index = hash(key);
        for (int i = 0; i < table_size; ++i) {
            int probeIndex = probe(index, i);
            if (!table[probeIndex].occupied) {
                break; 
            }
            if (table[probeIndex].key == key && !table[probeIndex].deleted) {
                table[probeIndex].deleted = true;
                --current_size;
                return;
            }
        }
    }


    void display() const {
        for (int i = 0; i < table_size; ++i) {
            if (table[i].occupied && !table[i].deleted) {
                std::cout << "Index " << i << ": {" << table[i].key << ": " << table[i].value << "}\n";
            }
        }
    }


    int getTableSize() const {
        return table_size;
    }


    void clear() {
        for (int i = 0; i < table_size; ++i) {
            table[i].occupied = false;
            table[i].deleted = false;
        }
        current_size = 0;
    }

    std::string toString() const {
        std::ostringstream oss;
        for (int i = 0; i < table_size; ++i) {
            if (table[i].occupied && !table[i].deleted) {
                oss << "Index " << i << ": {" << table[i].key << ": " << table[i].value << "}\n";
            }
        }
        return oss.str();
    }
};
