#ifndef RB_TREE
#define RB_TREE

enum class Color { BLACK, RED };

template <typename T>
struct RBNode {
    RBNode(T key) : key_(key) {}
    T key_;
    RBNode* left_child_ = nullptr;
    RBNode* right_child_ = nullptr;
    Color color_;
};

template <typename T>
class RBTree {
public:
    
    void insert (const T key);
    
    void remove (const T key);

    T pop ();

    void inorder_print();

protected:

    RBNode<T>* insert(RBNode<T>*& N, const T key);

    RBNode<T>* inorder_successor(RBNode<T>* N);

    RBNode<T>* remove(RBNode<T>*& N, const T key, bool& done);

    bool is_red(RBNode<T>* P);

    RBNode<T>* insert_rebalance(RBNode<T>* P, T key);

    RBNode<T>* remove_rebalance(RBNode<T>* P, T key, bool& done);

    RBNode<T>* rotate_right(RBNode<T>*& P);

    RBNode<T>* rotate_left(RBNode<T>*& P);

    void inorder_print(RBNode<T>* N);

private:

    RBNode<T>* root_ = nullptr;

};

#include "RBTree.tcc"

#endif // RB_TREE

