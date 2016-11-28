
#include <iostream>

template <typename T>
void BinarySearchTree<T>::insert (const T key) {
    root_ = insert(root_, key);
}

template <typename T>
void BinarySearchTree<T>::remove (const T key) {
    root_ = remove(root_, key);
}

template <typename T>
BinarySearchNode<T>* BinarySearchTree<T>::insert(BinarySearchNode<T>* N, const T key) {

    if (N == nullptr) {
        return new BinarySearchNode<T>(key);
    }

    if (key < N->key_) {
        N->left_child_  = insert(N->left_child_, key);
    } else {
        N->right_child_ = insert(N->right_child_, key);
    }

    return N;
}

template <typename T>
T BinarySearchTree<T>::pop () {
    BinarySearchNode<T>* min_node = inorder_successor(root_);
    T key = min_node->key_;
    remove(key);
    return key;
}

template <typename T>
BinarySearchNode<T>* BinarySearchTree<T>::inorder_successor(BinarySearchNode<T>* N) {
    BinarySearchNode<T>* current = N;
    while (current->left_child_ != nullptr) {
        current = current->left_child_;
    }
    return current;
}

template <typename T>
BinarySearchNode<T>* BinarySearchTree<T>::remove(BinarySearchNode<T>* N, const T key) {

    if (N == nullptr) {
        return N;
    }

    if (key < N->key_) {
        N->left_child_ = remove(N->left_child_, key);
    } else if(key > N->key_) {
        N->right_child_ = remove(N->right_child_, key);
    } else {

        // node with only one child or no child
        if( (N->left_child_ == nullptr) || (N->right_child_ == nullptr) ) {
            BinarySearchNode<T>* temp = N->left_child_ ? N->left_child_ : N->right_child_;
            delete N;
            return temp;
        }

        BinarySearchNode<T>* temp = inorder_successor(N->right_child_);
        N->key_ = temp->key_;
        N->right_child_ = remove(N->right_child_, temp->key_);
    }

    return N;
}

template <typename T>
void BinarySearchTree<T>::inorder_print() {
    inorder_print(root_);
}

template <typename T>
void BinarySearchTree<T>::inorder_print(BinarySearchNode<T>* N) {
    if(N != nullptr) {
        inorder_print(N->left_child_);
        std::cout << N->key_ << std::endl;
        inorder_print(N->right_child_);
    }
}

