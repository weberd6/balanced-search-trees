#ifndef TWO_THREE_FOUR_TREE_HPP
#define TWO_THREE_FOUR_TREE_HPP

template <typename T>
struct TwoThreeFourNode {

    TwoThreeFourNode(T small_key) : small_key_(small_key), num_items_(1) {}

    TwoThreeFourNode(T small_key, T mid_key, T large_key) :
        small_key_(small_key), mid_key_(mid_key), large_key_(large_key), num_items_(3) {}

    unsigned int num_items_;

    T small_key_;
    T mid_key_;
    T large_key_;

    TwoThreeFourNode* left_child_ = nullptr;
    TwoThreeFourNode* left_middle_child_ = nullptr;
    TwoThreeFourNode* right_middle_child_ = nullptr;
    TwoThreeFourNode* right_child_ = nullptr;
};

template <typename T>
class TwoThreeFourTree {
public:

    void insert(T key);

    void remove(T key);

    void inorder_print();

    T pop();

protected:

    void inorder_print(TwoThreeFourNode<T>* N);

    bool is_leaf(TwoThreeFourNode<T>* N);

    void add_key(TwoThreeFourNode<T>* N, T key);

    TwoThreeFourNode<T>* split(TwoThreeFourNode<T>* P, TwoThreeFourNode<T>* C);

    void insert(TwoThreeFourNode<T>* N, T key);

    TwoThreeFourNode<T>* inorder_predecessor(TwoThreeFourNode<T>* N);

    TwoThreeFourNode<T>* inorder_successor(TwoThreeFourNode<T>* N);

    TwoThreeFourNode<T>* fuse(TwoThreeFourNode<T>* P, TwoThreeFourNode<T>* L, TwoThreeFourNode<T>* R, unsigned int pos);

    void redistribute_right(TwoThreeFourNode<T>* P, TwoThreeFourNode<T>* L, TwoThreeFourNode<T>* R,
            unsigned int pos);

    void redistribute_left(TwoThreeFourNode<T>* P, TwoThreeFourNode<T>* L, TwoThreeFourNode<T>* R,
            unsigned int pos);

    void remove_key(TwoThreeFourNode<T>* N, T key);

    TwoThreeFourNode<T>* fix(TwoThreeFourNode<T>* N, T key);

    TwoThreeFourNode<T>* innode_fix(TwoThreeFourNode<T>* P, T key);

    TwoThreeFourNode<T>* remove(TwoThreeFourNode<T>* N, T key);

private:

    TwoThreeFourNode<T>* root_ = nullptr;

};

#include "TwoThreeFourTree.tcc"

#endif
