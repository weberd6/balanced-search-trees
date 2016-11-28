
#include <stdexcept>
#include <iostream>
#include <cassert>

template <typename T>
void TwoThreeTree<T>::insert(T key) {
    root_ = insert(root_, key);
    if (root_->num_items_ == 3) {
        root_ = split(root_, root_);
    }
}

template <typename T>
void TwoThreeTree<T>::remove(T key) {
    root_ = remove(root_, key);
    if (root_->num_items_ == 0) {
        TwoThreeNode<T>* temp = root_;
        root_ = root_->middle_child_;
        delete temp;
    }
}

template <typename T>
T TwoThreeTree<T>::pop() {
    TwoThreeNode<T>* min_node = inorder_successor(root_);
    T key = min_node->small_key_;
    remove(key);
    return key;
}

template <typename T>
bool TwoThreeTree<T>::is_leaf(TwoThreeNode<T>* N) {
    return ((N->left_child_ == nullptr) &&
            (N->middle_child_ == nullptr) &&
            (N->right_child_ == nullptr));
}

template <typename T>
void TwoThreeTree<T>::add_key(TwoThreeNode<T>* N, T key) {

    if ((N->num_items_ == 2) && (key > N->large_key_)) {
        N->temp_key_ = key;
    } else if (key > N->small_key_) {
        N->temp_key_ = N->large_key_;
        N->large_key_ = key;
    } else {
        N->temp_key_ = N->large_key_;
        N->large_key_ = N->small_key_;
        N->small_key_ = key;
    }
    ++N->num_items_;
}

template <typename T>
TwoThreeNode<T>* TwoThreeTree<T>::fix_insert(TwoThreeNode<T>* P, T key) {

    if (key < P->small_key_) {
        if (P->left_child_->num_items_ == 3) {
            return split(P, P->left_child_);
        }
    } else if ((P->num_items_ == 2) && (key > P->large_key_)) {
        if (P->right_child_->num_items_ == 3) {
            return split(P, P->right_child_);
        }
    } else {
        if (P->middle_child_->num_items_ == 3) {
            return split(P, P->middle_child_);
        }
    }

    // Nothing needs to be fixed

    return P;
}

template <typename T>
TwoThreeNode<T>* TwoThreeTree<T>::split(TwoThreeNode<T>* P, TwoThreeNode<T>* N) {

    TwoThreeNode<T>* R1 = new TwoThreeNode<T>(N->small_key_);
    R1->left_child_ = N->left_child_;
    R1->middle_child_ = N->middle_child_;

    TwoThreeNode<T>* R2 = new TwoThreeNode<T>(N->temp_key_);
    R2->left_child_ = N->right_child_;
    R2->middle_child_ = N->temp_child_;

    if (N == root_) {
        P = new TwoThreeNode<T>(N->large_key_);
        P->left_child_ = R1;
        P->middle_child_ = R2;
    } else {
        add_key(P, N->large_key_);
        if (N->large_key_ == P->small_key_) {
            if (P->num_items_ == 3) {
                P->temp_child_ = P->right_child_;
            }
            P->right_child_ = P->middle_child_;
            P->middle_child_ = R2;
            P->left_child_ = R1;
        } else if (N->large_key_ == P->large_key_) {
            if (P->num_items_ == 3) {
                P->temp_child_ = P->right_child_;
            }
            P->right_child_ = R2;
            P->middle_child_ = R1;
        } else {
            P->temp_child_ = R2;
            P->right_child_ = R1;
        }
    }

    delete N;

    return P;
}

template <typename T>
TwoThreeNode<T>* TwoThreeTree<T>::insert(TwoThreeNode<T>* N, T key) {

    if (N == nullptr) {
        assert(root_ == nullptr);
        return new TwoThreeNode<T>(key);
    }

    if (is_leaf(N)) {
        add_key(N, key);
        return N;
    } else {
        if (key < N->small_key_) {
            N->left_child_ = insert(N->left_child_, key);
        } else if ((N->num_items_ == 2) && (key > N->large_key_)) {
            N->right_child_ = insert(N->right_child_, key);
        } else {
            N->middle_child_ = insert(N->middle_child_, key);
        }
    }

    return fix_insert(N, key);
}

template <typename T>
TwoThreeNode<T>* TwoThreeTree<T>::inorder_successor(TwoThreeNode<T>* N) {
    TwoThreeNode<T>* current = N;
    while (current->left_child_ != nullptr) {
        current = current->left_child_;
    }
    return current;
}

template <typename T>
void TwoThreeTree<T>::remove_key(TwoThreeNode<T>* N, T key) {
    if (key == N->small_key_) {
        N->small_key_ = N->large_key_;
    }
    --N->num_items_;
}

template <typename T>
void TwoThreeTree<T>::redistribute_right(TwoThreeNode<T>* P, TwoThreeNode<T>* E,
        TwoThreeNode<T>* B, bool small) {

    if (small) {
        E->small_key_ = P->small_key_;
        P->small_key_ = B->large_key_;
    } else {
        E->small_key_ = P->large_key_;
        P->large_key_ = B->large_key_;
    }

    E->left_child_ = B->right_child_;
    B->right_child_ = nullptr;

    ++E->num_items_;
    --B->num_items_;
}

template <typename T>
void TwoThreeTree<T>::merge_right(TwoThreeNode<T>* P, TwoThreeNode<T>* E,
        TwoThreeNode<T>* B, bool small) {

    B->large_key_ = B->small_key_;
    if (small) {
        B->small_key_ = P->small_key_;
    } else {
        B->small_key_ = P->large_key_;
    }

    B->right_child_ = B->middle_child_;
    B->middle_child_ = B->left_child_;
    B->left_child_ = E->middle_child_;

    ++B->num_items_;
    --P->num_items_;
}

template <typename T>
void TwoThreeTree<T>::redistribute_left(TwoThreeNode<T>* P, TwoThreeNode<T>* E,
        TwoThreeNode<T>* B, bool small) {

    if (small) {
        E->small_key_ = P->small_key_;
        P->small_key_ = B->small_key_;
    } else {
        E->small_key_ = P->large_key_;
        P->large_key_ = B->small_key_;
    }
    B->small_key_ = B->large_key_;

    E->left_child_ = E->middle_child_;
    E->middle_child_ = B->left_child_;
    B->left_child_ = B->middle_child_;
    B->middle_child_ = B->right_child_;
    B->right_child_ = nullptr;

    ++E->num_items_;
    --B->num_items_;
}

template <typename T>
void TwoThreeTree<T>::merge_left(TwoThreeNode<T>* P, TwoThreeNode<T>* E,
        TwoThreeNode<T>* B, bool small) {

    if (small) {
        B->large_key_ = P->small_key_;
    } else {
        B->large_key_ = P->large_key_;
    }

    B->right_child_ = E->middle_child_;

    ++B->num_items_;
    --P->num_items_;
}

template <typename T>
TwoThreeNode<T>* TwoThreeTree<T>::fix_remove(TwoThreeNode<T>* P, T key) {

    if (P->num_items_ == 1) {

        if (P->left_child_->num_items_ == 0) {
            // Left is empty
            if (P->middle_child_->num_items_ == 2) {
                redistribute_left(P, P->left_child_, P->middle_child_, true);
            } else {
                merge_right(P, P->left_child_, P->middle_child_, true);
                delete P->left_child_;
                P->left_child_ = nullptr;
            }
        } else if (P->middle_child_->num_items_ == 0) {
            // Right is empty
            if (P->left_child_->num_items_ == 2) {
                redistribute_right(P, P->middle_child_, P->left_child_, true);
            } else {
                merge_left(P, P->middle_child_, P->left_child_, true);
                delete P->middle_child_;
                P->middle_child_ = P->left_child_;
                P->left_child_ = nullptr;
            }
        }

    } else {

        if (P->left_child_->num_items_ == 0) {
            // Left is empty
            if (P->middle_child_->num_items_ == 2) {
                redistribute_left(P, P->left_child_, P->middle_child_, true);
            } else {
                merge_right(P, P->left_child_, P->middle_child_, true);
                delete P->left_child_;
                P->left_child_ = P->middle_child_;
                P->middle_child_ = P->right_child_;
                P->right_child_ = nullptr;
                P->small_key_ = P->large_key_;
            }
        } else if (P->right_child_->num_items_ == 0) {
            // Right is empty
            if (P->middle_child_->num_items_ == 2) {
               redistribute_right(P, P->right_child_, P->middle_child_, false);
            } else {
                merge_left(P, P->right_child_, P->middle_child_, false);
                delete P->right_child_;
                P->right_child_ = nullptr;
            }
        } else if (P->middle_child_->num_items_ == 0) {
            // Middle is empty
            if (P->left_child_->num_items_ == 2) {
                redistribute_right(P, P->middle_child_, P->left_child_, true);
            } else if (P->right_child_->num_items_ == 2) {
                redistribute_left(P, P->middle_child_, P->right_child_, false);
            } else {
                merge_left(P, P->middle_child_, P->left_child_, true);
                delete P->middle_child_;
                P->middle_child_ = P->right_child_;
                P->right_child_ = nullptr;
                P->small_key_ = P->large_key_;
            }
        }

    }

    return P;
}

template <typename T>
TwoThreeNode<T>* TwoThreeTree<T>::remove(TwoThreeNode<T>* N, T key) {

    if (N == nullptr) {
        throw std::runtime_error("Key not found in tree: "+std::to_string(key));
    }

    if (key < N->small_key_) {
        N->left_child_ = remove(N->left_child_, key);
    } else if ((N->num_items_ == 2) && (key > N->large_key_)) {
        N->right_child_ = remove(N->right_child_, key);
    } else if ((N->num_items_ == 1) && (key != N->small_key_)) {
        N->middle_child_ = remove(N->middle_child_, key);
    } else if ((N->num_items_ == 2) && (key != N->small_key_) && (key != N->large_key_)) {
        N->middle_child_ = remove(N->middle_child_, key);
    } else {

        if(is_leaf(N)) {
            remove_key(N, key);
            return N;
        }

        if (N->small_key_ == key) {
            TwoThreeNode<T>* temp = inorder_successor(N->middle_child_);
            N->small_key_ = temp->small_key_;
            N->middle_child_ = remove(N->middle_child_, temp->small_key_);
        } else if ((N->num_items_ == 2) && (N->large_key_ == key)) {
            TwoThreeNode<T>* temp = inorder_successor(N->right_child_);
            N->large_key_ = temp->small_key_;
            N->right_child_ = remove(N->right_child_, temp->small_key_);
        } else {
            std::cout << "Number keys: " << N->num_items_ << std::endl;
            std::cout << "Key: " << key << std::endl;
            std::cout << "Node: " << N->small_key_ << " " << N->large_key_ << " " << N->temp_key_ << std::endl;
            std::cout << N->left_child_ << " " << N->middle_child_ << " " << N->left_child_ << std::endl;
            throw std::runtime_error("Didn't find key in node");
        }
    }

    return fix_remove(N, key);
}

template <typename T>
void TwoThreeTree<T>::inorder_print() {
    inorder_print(root_);
    std::cout << std::endl;
}

template <typename T>
void TwoThreeTree<T>::inorder_print(TwoThreeNode<T>* N) {
    if(N != nullptr) {
        inorder_print(N->left_child_);
        std::cout << N->small_key_ << std::endl;
        inorder_print(N->middle_child_);
        if (N->num_items_ == 2) std::cout << N->large_key_ << std::endl;
        inorder_print(N->right_child_);
    }
}

