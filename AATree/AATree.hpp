#ifndef AATREE_HPP
#define AATREE_HPP

template <typename T>
struct AANode {
    AANode(T key) : key_(key) {}

    T key_;
    AANode* left_child_ = nullptr;
    AANode* right_child_ = nullptr;

    unsigned int level_ = 1;
};

template <typename T>
class AATree {
public:

    void insert(T key);

    void remove(T key);

    void inorder_print();

    T pop();

protected:

    AANode<T>* skew(AANode<T>* P);

    AANode<T>* split(AANode<T>* P);

    AANode<T>* insert(AANode<T>* N, T key);

    AANode<T>* inorder_successor(AANode<T>* N);

    AANode<T>* inorder_predecessor(AANode<T>* N);

    unsigned int level(AANode<T>* N);

    AANode<T>* remove(AANode<T>* N, T key);

    void inorder_print(AANode<T>* N);

private:

    AANode<T>* root_ = nullptr;

};

#include "AATree.tcc"

#endif
