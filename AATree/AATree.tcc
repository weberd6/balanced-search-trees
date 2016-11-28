
#include <iostream>
#include <stdexcept>
#include <cassert>

template <typename T>
void AATree<T>::insert(T key) {
    root_ = insert(root_, key);
}

template <typename T>
void AATree<T>::remove(T key) {
    root_ = remove(root_, key);
}

template <typename T>
T AATree<T>::pop() {
    AANode<T>* min_node = inorder_successor(root_);
    T key = min_node->key_;
    remove(key);
    return key;
}

template <typename T>
AANode<T>* AATree<T>::skew(AANode<T>* P) {
    
    if ((P == nullptr) || (P->left_child_ == nullptr)) {
        return P;
    }

    if (P->level_ == P->left_child_->level_) {
        AANode<T>* L = P->left_child_;
        P->left_child_ = L->right_child_;
        L->right_child_ = P;
        return L;
    }

    return P;
}

template <typename T>
AANode<T>* AATree<T>::split(AANode<T>* P) {

    if ((P == nullptr) || (P->right_child_ == nullptr) || (P->right_child_->right_child_ == nullptr)) {
        return P;
    }

    if (P->level_ == P->right_child_->right_child_->level_) {
        AANode<T>* M = P->right_child_;
        P->right_child_ = M->left_child_;
        M->left_child_ = P;
        ++M->level_;
        return M;
    }

    return P;
}

template <typename T>
AANode<T>* AATree<T>::insert(AANode<T>* N, T key) {
    
    if (N == nullptr) {
        return new AANode<T>(key);
    }

    if (key < N->key_) {
        N->left_child_ = insert(N->left_child_, key);
    } else if (key > N->key_) {
       N->right_child_ = insert(N->right_child_, key); 
    } else {
        throw std::runtime_error("No duplicate keys allowed");
    }

    N = skew(N);
    N = split(N);

    return N;
}

template <typename T>
AANode<T>* AATree<T>::inorder_successor(AANode<T>* N) {
    AANode<T>* current = N;
    while (current->left_child_ != nullptr) {
        current = current->left_child_;
    }
    return current;
}

template <typename T>
AANode<T>* AATree<T>::inorder_predecessor(AANode<T>* N) {
    AANode<T>* current = N;
    while (current->right_child_ != nullptr) {
        current = current->right_child_;
    }
    return current;
}


template <typename T>
unsigned int AATree<T>::level(AANode<T>* N) {
    if (N == nullptr) {
        return 0;
    }
    return N->level_;
}

template <typename T>
AANode<T>* AATree<T>::remove(AANode<T>* N, T key) {

    if (N == nullptr) {
        return N;
    }

    if (key < N->key_) {
        N->left_child_ = remove(N->left_child_, key);
    } else if(key > N->key_) {
        N->right_child_ = remove(N->right_child_, key);
    } else {

        if ((N->left_child_ == nullptr) && (N->right_child_ == nullptr) ) {
            delete N;
            return nullptr;
        } else if (N->left_child_ == nullptr) {
            AANode<T>* temp = inorder_successor(N->right_child_);
            N->key_ = temp->key_;
            N->right_child_ = remove(N->right_child_, temp->key_);
        } else {
            AANode<T>* temp = inorder_predecessor(N->left_child_);
            N->key_ = temp->key_;
            N->left_child_ = remove(N->left_child_, temp->key_);
        }
    }

    unsigned int L = std::min(level(N->left_child_), level(N->right_child_)) + 1;
    if (level(N) > L) {
        N->level_ = L;
        if (level(N->right_child_) > L) {
            N->right_child_->level_ = L;
        }
    }

    N = skew(N);
    N->right_child_ = skew(N->right_child_);
    if (N->right_child_ != nullptr) N->right_child_->right_child_ = skew(N->right_child_->right_child_);

    N = split(N);
    N->right_child_ = split(N->right_child_);

    return N;
}

template <typename T>
void AATree<T>::inorder_print() {
    inorder_print(root_);
}

template <typename T>
void AATree<T>::inorder_print(AANode<T>* N) {
    if(N != nullptr) {
        inorder_print(N->left_child_);
        std::cout << N->key_ << std::endl;
        inorder_print(N->right_child_);
    }
}

