#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

template <typename T>
struct BinarySearchNode {
    BinarySearchNode(T key) : key_(key) {}
    T key_;
    BinarySearchNode* left_child_ = nullptr;
    BinarySearchNode* right_child_ = nullptr;
};

template <typename T>
class BinarySearchTree {
public:
    
    void insert (const T key);
    
    void remove (const T key);

    T pop ();

    void inorder_print();

protected:

    BinarySearchNode<T>* inorder_successor(BinarySearchNode<T>* N);

    BinarySearchNode<T>* insert(BinarySearchNode<T>* N, const T key);

    BinarySearchNode<T>* remove(BinarySearchNode<T>* N, const T key);

    void inorder_print(BinarySearchNode<T>* N);

private:

    BinarySearchNode<T>* root_ = nullptr;

};

#include "BinarySearchTree.tcc"

#endif // BINARY_SEARCH_TREE

