#ifndef BST_H
#define BST_H
#include "iostream"

/*
 *
 * 1. BST = Binary search tree
 * 2. Diff from binary tree:
 * 2.1 Left node is smaller than the root
 * 2.2 Right node is larger than the root
 *
 */


template <typename Key, typename Value>
struct TreeNode {
    Key key;
    Value value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(const Key& key, const Value& value) : key(key), value(value), left(nullptr), right(nullptr) {}
};

template<typename Key, typename Value>
class GoodBST {

    TreeNode<Key, Value>* root;

public:
    GoodBST() : root(nullptr) {}

    ~GoodBST() {
        clear();
    }


    TreeNode<Key, Value>* getRoot() const {
        return root;
    }

    void insert(const Key& key_to_insert, const Value& value) {
        root = insert(root, key_to_insert, value);
    }

    TreeNode<Key, Value>* search(const Key& key_to_search) {
        return search(root,key_to_search);
    }

    void deleteNode(const Key& key_to_delete) {
        root = deleteNode(root, key_to_delete);
    }

    void balance() {
        root = balance(root);
    }

    void clear() {
        clearHelper(root);
        root = nullptr;
    }

    Value getValueByKey(const Key& key) {
        TreeNode<Key, Value>* node = search(root, key);
        if (node == nullptr) {
            throw std::invalid_argument("Key not found in the tree!");
        }
        return node->value;
    }

    std::string preorder() const {
        std::string result;
        preorder(root, result);
        return result;
    }

    std::string postorder() const {
        std::string result;
        postorder(root, result);
        return result;
    }

    std::string inorder() const {
        std::string result;
        inorder(root, result);
        return result;
    }

    TreeNode<Key, Value>* getMinNode() {
        return getMinNode(root);
    }

    TreeNode<Key, Value>* getMaxNode() {
        return getMaxNode(root);
    }

    void swapValues(TreeNode<Key, Value>* node1,TreeNode<Key, Value>* node2) {
        if (node1 && node2) {
            std::swap(node1->value, node2->value);
        }
    }



private:

    void preorder(TreeNode<Key, Value>* node, std::string& result) const {
        if (node != nullptr) {
            result += std::to_string(node->key) + ": " + node->value + "\n";
            preorder(node->left, result);
            preorder(node->right, result);
        }
    }

    void postorder(TreeNode<Key, Value>* node, std::string& result) const {
        if (node != nullptr) {
            postorder(node->left, result);
            postorder(node->right, result);
            result += std::to_string(node->key) + ": " + node->value + "\n";
        }
    }

    void inorder(TreeNode<Key, Value>* node, std::string& result) const {
        if (node != nullptr) {
            inorder(node->left, result);
            result += std::to_string(node->key) + ": " + node->value + "\n";
            inorder(node->right, result);
        }
    }

    TreeNode<Key,Value>* insert(TreeNode<Key,Value>* node, const Key& key_to_insert, const Value& value)  {
        if (node == nullptr) {
            return new TreeNode<Key,Value>(key_to_insert, value);
        }

        if (node->key == key_to_insert) {
            return node;
        }

        if (node->key > key_to_insert) {
            node->left = insert(node->left, key_to_insert, value);
        } else {
            node->right = insert(node->right, key_to_insert, value);
        }

        return node;
    }

    TreeNode<Key,Value>* search(TreeNode<Key,Value>* node, const Key& key_to_search) {
        if (node == nullptr || node->key == key_to_search) {
            return node;
        }

        if (node->key > key_to_search) {
           return search(node->left,key_to_search);
        } else {
            return search(node->right,key_to_search);
        }
    }

    TreeNode<Key,Value>* deleteNode(TreeNode<Key,Value>* node, const Key& key_to_delete) {
        if (node == nullptr) {
            return node;
        }

        if (node->key > key_to_delete) {
            node->left = deleteNode(node->left, key_to_delete);
        }
        else if (node->key < key_to_delete) {
            node->right = deleteNode(node->right, key_to_delete);
        } else {
            if (node->left == nullptr) {
                TreeNode<Key, Value>* temp = node->right;
                delete node;
                return temp;
            }

            if (node->right == nullptr) {
                TreeNode<Key,Value>* temp = node->left;
                delete node;
                return temp;
            }
            TreeNode<Key,Value>* succ = getSuccessor(node);
            node->key = succ->key;
            node->value = succ->value;
            node->right = deleteNode(node->right, succ->key);
        }
        return node;
    }

    TreeNode<Key,Value>* getSuccessor(TreeNode<Key,Value>* current_node){
        current_node = current_node->right;
        while (current_node != nullptr && current_node->left != nullptr)
            current_node = current_node->left;
        return current_node;
    }

    void storeInorder(TreeNode<Key, Value>* root, std::vector<std::pair<Key, Value>>& nodes) {
        if (root == nullptr) {
            return;
        }

        storeInorder(root->left, nodes);
        nodes.push_back({root->key, root->value});
        storeInorder(root->right, nodes);
    }


    TreeNode<Key, Value>* BalanceTree(const std::vector<std::pair<Key, Value>>& nodes, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = (start + end) / 2;
        TreeNode<Key, Value>* root = new TreeNode<Key, Value>(nodes[mid].first, nodes[mid].second);

        root->left = BalanceTree(nodes, start, mid - 1);
        root->right = BalanceTree(nodes, mid + 1, end);

        return root;
    }


    TreeNode<Key, Value>* balance(TreeNode<Key, Value>* node) {
        std::vector<std::pair<Key, Value>> nodes;
        storeInorder(node, nodes);
        return BalanceTree(nodes, 0, nodes.size() - 1);
    }


    void clearHelper(TreeNode<Key,Value>* node) {
        if (node == nullptr) {
            return;
        }

        clearHelper(node->left);
        clearHelper(node->right);

        delete node;
    }

    TreeNode<Key, Value>* getMinNode(TreeNode<Key, Value>* node) {
        if (node == nullptr) {
            return nullptr;
        }
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    TreeNode<Key, Value>* getMaxNode(TreeNode<Key, Value>* node) {
        if (node == nullptr) {
            return nullptr;
        }
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }
};


#endif //BST_H
