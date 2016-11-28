#ifndef AVL_TREE
#define AVL_TREE

template <typename T>
struct AVLNode {
    AVLNode(T key) : key_(key) {}
    T key_;
    AVLNode* left_child_ = nullptr;
    AVLNode* right_child_ = nullptr;
    int height_ = 1;
};

template <typename T>
class AVLTree {
public:
    
    void insert (const T key);
    
    void remove (const T key);

    T pop ();

    void inorder_print();

protected:


    int get_balance_factor(AVLNode<T>* N);

    int height(AVLNode<T>* N);

    AVLNode<T>* insert(AVLNode<T>* N, const T key);

    AVLNode<T>* inorder_successor(AVLNode<T>* N);

    AVLNode<T>* remove(AVLNode<T>* N, const T key);

    AVLNode<T>* rotate_right(AVLNode<T>* P);

    AVLNode<T>* rotate_left(AVLNode<T>* P);

    void inorder_print(AVLNode<T>* N);

private:

    AVLNode<T>* root_ = nullptr;

};

#include "AVLTree.tcc"

#endif // AVL_TREE

