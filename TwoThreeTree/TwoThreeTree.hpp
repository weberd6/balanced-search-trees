#ifndef TWO_THREE_TREE_HPP
#define TWO_THREE_TREE_HPP

// For now, the key is the value being stored

template <typename T>
struct TwoThreeNode {
    TwoThreeNode() = default;
    TwoThreeNode(T small) : small_key_(small) {}

    T small_key_;
    T large_key_;
    T temp_key_;

    TwoThreeNode* left_child_ = nullptr;
    TwoThreeNode* middle_child_ = nullptr;
    TwoThreeNode* right_child_ = nullptr;
    TwoThreeNode* temp_child_ = nullptr;

    unsigned int num_items_ = 1;
};

template <typename T>
class TwoThreeTree {
public:

    void insert(T key);

    void remove(T key);

    void inorder_print();

    T pop();

protected:

    TwoThreeNode<T>* inorder_successor(TwoThreeNode<T>* N);

    bool is_leaf(TwoThreeNode<T>* N);

    void add_key(TwoThreeNode<T>* N, T key);

    TwoThreeNode<T>* fix_insert(TwoThreeNode<T>* P, T key);

    TwoThreeNode<T>* split(TwoThreeNode<T>* P, TwoThreeNode<T>* N);

    TwoThreeNode<T>* insert(TwoThreeNode<T>* N, T key);

    void remove_key(TwoThreeNode<T>* N, T key);

    TwoThreeNode<T>* fix_remove(TwoThreeNode<T>* P, T key);

    void redistribute_left(TwoThreeNode<T>* P, TwoThreeNode<T>* E, TwoThreeNode<T>* B, bool small);

    void merge_left(TwoThreeNode<T>* P, TwoThreeNode<T>* E, TwoThreeNode<T>* B, bool small);

    void redistribute_right(TwoThreeNode<T>* P, TwoThreeNode<T>* E, TwoThreeNode<T>* B, bool small);

    void merge_right(TwoThreeNode<T>* P, TwoThreeNode<T>* E, TwoThreeNode<T>* B, bool small);

    TwoThreeNode<T>* remove(TwoThreeNode<T>* N, T key);

    void inorder_print(TwoThreeNode<T>* N);

private:

    TwoThreeNode<T> *root_ = nullptr;

};

#include "TwoThreeTree.tcc"

#endif

