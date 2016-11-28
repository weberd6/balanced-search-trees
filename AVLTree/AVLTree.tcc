
#include <iostream>
#include <algorithm>

template <typename T>
void AVLTree<T>::insert (const T key) {
    root_ = insert(root_, key);
}

template <typename T>
void AVLTree<T>::remove (const T key) {
    root_ = remove(root_, key);
}

template <typename T>
int AVLTree<T>::height(AVLNode<T>* N) {
    if (N == nullptr) {
        return 0;
    }
    return N->height_;
}

template <typename T>
int AVLTree<T>::get_balance_factor(AVLNode<T>* N) {
    if (N == nullptr) {
        return 0;
    }
    return height(N->left_child_) - height(N->right_child_);
}

template <typename T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T>* N, const T key) {

    if (N == nullptr) {
        return new AVLNode<T>(key);
    }

    if (key < N->key_) {
        N->left_child_  = insert(N->left_child_, key);
    } else {
        N->right_child_ = insert(N->right_child_, key);
    }

    N->height_ = std::max(height(N->left_child_), height(N->right_child_)) + 1;

    int balance = get_balance_factor(N);

    // Left Left Case
    if ((balance > 1) && (key < N->left_child_->key_)) {
        return rotate_right(N);
    }
         
    // Right Right Case
    if ((balance < -1) && (key > N->right_child_->key_)) {
        return rotate_left(N);
    }
             
    // Left Right Case
    if ((balance > 1) && (key > N->left_child_->key_)) {
        N->left_child_ = rotate_left(N->left_child_);
        return rotate_right(N);
    }
                 
    // Right Left Case
    if ((balance < -1) && (key < N->right_child_->key_)) {
        N->right_child_ = rotate_right(N->right_child_);
        return rotate_left(N);
    }

    return N;
}

template <typename T>
T AVLTree<T>::pop () {
    AVLNode<T>* min_node = inorder_successor(root_);
    T key = min_node->key_;
    remove(key);
    return key;
}

template <typename T>
AVLNode<T>* AVLTree<T>::inorder_successor(AVLNode<T>* N) {
    AVLNode<T>* current = N;
    while (current->left_child_ != nullptr) {
        current = current->left_child_;
    }
    return current;
}

template <typename T>
AVLNode<T>* AVLTree<T>::remove(AVLNode<T>* N, const T key) {

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
        
            struct AVLNode<T>* temp = N->left_child_ ? N->left_child_ : N->right_child_;

            // No child case
            if(temp == nullptr) {
                temp = N;
                N = NULL;
            } else {// One child case
                *N = *temp; // Copy the contents of the non-empty child
            }

            delete temp;
            
        } else {

            AVLNode<T>* temp = inorder_successor(N->right_child_);
            
            N->key_ = temp->key_;
            
            // Delete the inorder successor
            N->right_child_ = remove(N->right_child_, temp->key_);
        }
    }
    
    // If the tree had only one node then return
    if (N == NULL)
        return N;
        
    N->height_ = std::max(height(N->left_child_), height(N->right_child_)) + 1;
    
    int balance = get_balance_factor(N);
    
    // Left Left Case
    if ((balance > 1) && (get_balance_factor(N->left_child_) >= 0)) {
        return rotate_right(N);
    }
        
    // Left Right Case
    if ((balance > 1) && (get_balance_factor(N->left_child_) < 0)) {
        N->left_child_ = rotate_left(N->left_child_);
        return rotate_right(N);
    }
    
    // Right Right Case
    if ((balance < -1) && (get_balance_factor(N->right_child_) <= 0)) {
        return rotate_left(N);
    }
        
    // Right Left Case
    if ((balance < -1) && (get_balance_factor(N->right_child_) > 0)) {
        N->right_child_ = rotate_right(N->right_child_);
        return rotate_left(N);
    }

    return N;
}

template <typename T>
AVLNode<T>* AVLTree<T>::rotate_right(AVLNode<T>* P) {

    AVLNode<T>* N = P->left_child_;
    AVLNode<T>* B = N->right_child_;

    // Perform rotation
    N->right_child_ = P;
    P->left_child_ = B;
             
    // Update heights
    P->height_ = std::max(height(P->left_child_), height(P->right_child_))+1;
    N->height_ = std::max(height(N->left_child_), height(N->right_child_))+1;

    return N;
}

template <typename T>
AVLNode<T>* AVLTree<T>::rotate_left(AVLNode<T>* P) {
 
    AVLNode<T>* N = P->right_child_;
    AVLNode<T>* B = N->left_child_;

    // Perform rotation
    N->left_child_ = P;
    P->right_child_ = B;
             
    // Update heights
    P->height_ = std::max(height(P->left_child_), height(P->right_child_))+1;
    N->height_ = std::max(height(N->left_child_), height(N->right_child_))+1;

    return N;
}

template <typename T>
void AVLTree<T>::inorder_print() {
    inorder_print(root_);
}

template <typename T>
void AVLTree<T>::inorder_print(AVLNode<T>* N) {
    if(N != nullptr) {
        inorder_print(N->left_child_);
        std::cout << N->key_ << std::endl;
        inorder_print(N->right_child_);
    }
}

