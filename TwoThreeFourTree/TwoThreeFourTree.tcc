
#include <iostream>
#include <cassert>
#include <stdexcept>

template <typename T>
void TwoThreeFourTree<T>::insert(T key) {
    if ((root_ != nullptr) && (root_->num_items_ == 3)) {
        root_ = split(nullptr, root_);
    }
    insert(root_, key);
}

template <typename T>
void TwoThreeFourTree<T>::remove(T key) {
    root_ = remove(root_, key);
}

template <typename T>
T TwoThreeFourTree<T>::pop() {
    TwoThreeFourNode<T>* min_node = inorder_successor(root_);
    T key = min_node->small_key_;
    remove(key);
    return key;
}

template <typename T>
bool TwoThreeFourTree<T>::is_leaf(TwoThreeFourNode<T>* N) {
    return ((N->left_child_ == nullptr) &&
            (N->left_middle_child_ == nullptr) &&
            (N->right_middle_child_ == nullptr) &&
            (N->right_child_ == nullptr));
}

template <typename T>
TwoThreeFourNode<T>* TwoThreeFourTree<T>::split(TwoThreeFourNode<T>* P, TwoThreeFourNode<T>* C) {

    TwoThreeFourNode<T>* R1 = new TwoThreeFourNode<T>(C->small_key_);
    R1->left_child_ = C->left_child_;
    R1->left_middle_child_ = C->left_middle_child_;

    TwoThreeFourNode<T>* R2 = new TwoThreeFourNode<T>(C->large_key_);
    R2->left_child_ = C->right_middle_child_;
    R2->left_middle_child_ = C->right_child_;

    if (P == nullptr) {
        P = new TwoThreeFourNode<T>(C->mid_key_);
        P->left_middle_child_ = R2;
        P->left_child_ = R1;
    } else {
        add_key(P, C->mid_key_);
        if (C->mid_key_ == P->small_key_) {
            if (P->num_items_ == 3) {
                P->right_child_ = P->right_middle_child_;
            }
            P->right_middle_child_ = P->left_middle_child_;
            P->left_middle_child_ = R2;
            P->left_child_ = R1;
        } else if (C->mid_key_ == P->mid_key_) {
            if (P->num_items_ == 3) {
                P->right_child_ = P->right_middle_child_;
            }
            P->right_middle_child_ = R2;
            P->left_middle_child_ = R1;
        } else if ((P->num_items_ == 3) && (C->mid_key_ == P->large_key_)) {
            P->right_child_ = R2;
            P->right_middle_child_ = R1;
        }
    }

    delete C;

    return P;
}

template <typename T>
void TwoThreeFourTree<T>::add_key(TwoThreeFourNode<T>* N, T key) {

    assert(N->num_items_ != 3);

    if ((N->num_items_ == 2) && (key > N->mid_key_)) {
        N->large_key_ = key;
    } else if (key > N->small_key_) {
        N->large_key_ = N->mid_key_;
        N->mid_key_ = key;
    } else {
        N->large_key_ = N->mid_key_;
        N->mid_key_ = N->small_key_;
        N->small_key_ = key;
    }
    ++N->num_items_;
}

template <typename T>
void TwoThreeFourTree<T>::insert(TwoThreeFourNode<T>* N, T key) {

    if (N == nullptr) {
        assert(root_ == nullptr);
        root_ = new TwoThreeFourNode<T>(key);
        return;
    }

    if (is_leaf(N)) {

        add_key(N, key);

    } else {

        if ((key < N->small_key_) && (N->left_child_->num_items_ == 3)) {
            split(N, N->left_child_);
        } else if ((N->num_items_ == 3) && (key > N->large_key_)
                    && (N->right_child_->num_items_ == 3)) {
            split(N, N->right_child_);
        } else if ((N->num_items_ >= 2) && (key > N->mid_key_)
                    && (N->right_middle_child_->num_items_ == 3)) {
            split(N, N->right_middle_child_);
        } else if (N->left_middle_child_->num_items_ == 3) {
            split(N, N->left_middle_child_);
        }

        if (key < N->small_key_) {
            insert(N->left_child_, key);
        } else if ((N->num_items_ == 3) && (key > N->large_key_)) {
            insert(N->right_child_, key);
        } else if ((N->num_items_ >= 2) && (key > N->mid_key_)) {
            insert(N->right_middle_child_, key);
        } else {
            insert(N->left_middle_child_, key);
        }
    }
}

template <typename T>
TwoThreeFourNode<T>* TwoThreeFourTree<T>::inorder_successor(TwoThreeFourNode<T>* N) {
    TwoThreeFourNode<T>* current = N;
    while (current->left_child_ != nullptr) {
        current = current->left_child_;
    }
    return current;
}

template <typename T>
void TwoThreeFourTree<T>::remove_key(TwoThreeFourNode<T>* N, T key) {

    if (key == N->small_key_) {
        N->small_key_ = N->mid_key_;
        N->mid_key_ = N->large_key_;
    } else if (key == N->mid_key_) {
        N->mid_key_ = N->large_key_;
    }
    --N->num_items_;

    if (N->num_items_ == 0) {
        assert(N == root_);
    }
}

template <typename T>
TwoThreeFourNode<T>* TwoThreeFourTree<T>::fuse(TwoThreeFourNode<T>* P, TwoThreeFourNode<T>* L, TwoThreeFourNode<T>* R,
        unsigned int pos) {

    TwoThreeFourNode<T>* M;

    if (pos == 0) {
        M = new TwoThreeFourNode<T>(L->small_key_, P->small_key_, R->small_key_);
        P->left_child_ = M;
        if (P->num_items_ == 2) {
            P->small_key_ = P->mid_key_;
            P->left_middle_child_ = P->right_middle_child_;
            P->right_middle_child_ = nullptr;
        } else if (P->num_items_ == 3) {
            P->small_key_ = P->mid_key_;
            P->mid_key_ = P->large_key_;
            P->left_middle_child_ = P->right_middle_child_;
            P->right_middle_child_ = P->right_child_;
            P->right_child_ = nullptr;
        }
    } else if (pos == 1) {
        M = new TwoThreeFourNode<T>(L->small_key_, P->mid_key_, R->small_key_);
        P->left_middle_child_ = M;
        if (P->num_items_ == 2) {
            P->right_middle_child_ = nullptr;
        } else if (P->num_items_ == 3) {
            P->mid_key_ = P->large_key_;
            P->right_middle_child_ = P->right_child_;
            P->right_child_ = nullptr;
        }
    } else {
        M = new TwoThreeFourNode<T>(L->small_key_, P->large_key_, R->small_key_);
        P->right_middle_child_ = M;
        P->right_child_ = nullptr;
    }

    M->left_child_ = L->left_child_;
    M->left_middle_child_ = L->left_middle_child_;
    M->right_middle_child_ = R->left_child_;
    M->right_child_ = R->left_middle_child_;

    delete L;
    delete R;

    --P->num_items_;
    if (P->num_items_ == 0) {
        assert(P == root_);
        delete P;
        return M;
    }

    assert(M->num_items_ == 3);

    return P;
}

template <typename T>
void TwoThreeFourTree<T>::redistribute_right(TwoThreeFourNode<T>* P, TwoThreeFourNode<T>* L,
        TwoThreeFourNode<T>* R, unsigned int pos) {

    assert(L->num_items_ >= 2);
    assert(R->num_items_ == 1);

    R->mid_key_ = R->small_key_;
    R->right_middle_child_ = R->left_middle_child_;
    R->left_middle_child_ = R->left_child_;
    if (L->num_items_ == 2) {
        R->left_child_ = L->right_middle_child_;
        L->right_middle_child_ = nullptr;
    } else {
        R->left_child_ = L->right_child_;
        L->right_child_ = nullptr;
    }

    if (pos == 0) {
        R->small_key_ = P->small_key_;
        if (L->num_items_ == 2) {
            P->small_key_ = L->mid_key_;
        } else {
            P->small_key_ = L->large_key_;
        }
    } else if (pos == 1) {
        R->small_key_ = P->mid_key_;
        if (L->num_items_ == 2) {
            P->mid_key_ = L->mid_key_;
        } else {
            P->mid_key_ = L->large_key_;
        }
    } else {
        R->small_key_ = P->large_key_;
        if (L->num_items_ == 2) {
            P->large_key_ = L->mid_key_;
        } else {
            P->large_key_ = L->large_key_;
        }
    }

    ++R->num_items_;
    --L->num_items_;
}

template <typename T>
void TwoThreeFourTree<T>::redistribute_left(TwoThreeFourNode<T>* P, TwoThreeFourNode<T>* L,
            TwoThreeFourNode<T>* R, unsigned int pos) {

    assert(R->num_items_ >= 2);
    assert(L->num_items_ == 1);

    if (pos == 0) {
        L->mid_key_ = P->small_key_;
        P->small_key_ = R->small_key_;
    } else if (pos == 1) {
        L->mid_key_ = P->mid_key_;
        P->mid_key_ = R->small_key_;
    } else {
        L->mid_key_ = P->large_key_;
        P->large_key_ = R->small_key_;
    }

    L->right_middle_child_ = R->left_child_;
    R->left_child_ = R->left_middle_child_;
    R->left_middle_child_ = R->right_middle_child_;
    if (R->num_items_ == 3) {
        R->small_key_ = R->mid_key_;
        R->mid_key_ = R->large_key_;
        R->right_middle_child_ = R->right_child_;
        R->right_child_ = nullptr;
    } else {
        R->small_key_ = R->mid_key_;
        R->right_middle_child_ = nullptr;
    }

    ++L->num_items_;
    --R->num_items_;
}

template <typename T>
TwoThreeFourNode<T>* TwoThreeFourTree<T>::fix(TwoThreeFourNode<T>* N, T key) {

    if (key < N->small_key_ && (N->left_child_->num_items_ == 1)) {

        if (N->left_middle_child_->num_items_ >= 2) {
            redistribute_left(N, N->left_child_, N->left_middle_child_, 0);
        } else {
            return fuse(N, N->left_child_, N->left_middle_child_, 0);
        }

    } else if ((N->num_items_ == 1) && (key > N->small_key_) && (N->left_middle_child_->num_items_ == 1)) {

        if (N->left_child_->num_items_ >= 2) {
            redistribute_right(N, N->left_child_, N->left_middle_child_, 0);
        } else {
            return fuse(N, N->left_child_, N->left_middle_child_, 0);
        }

    } else if ((N->num_items_ >= 2) && (key > N->small_key_) && (key < N->mid_key_) && (N->left_middle_child_->num_items_ == 1)) {

        if (N->left_child_->num_items_ >= 2) {
            redistribute_right(N, N->left_child_, N->left_middle_child_, 0);
        } else if (N->right_middle_child_->num_items_ >= 2) {
            redistribute_left(N, N->left_middle_child_, N->right_middle_child_, 1);
        } else {
            return fuse(N, N->left_middle_child_, N->right_middle_child_, 1);
        }

    } else if ((N->num_items_ == 2) && (key > N->mid_key_) && (N->right_middle_child_->num_items_ == 1)) {
    
        if (N->left_middle_child_->num_items_ >= 2) {
            redistribute_right(N, N->left_middle_child_, N->right_middle_child_, 1);
        } else {
            return fuse(N, N->left_middle_child_, N->right_middle_child_, 1);
        }

    } else if ((N->num_items_ == 3) && (key > N->mid_key_) && (key < N->large_key_) && (N->right_middle_child_->num_items_ == 1)) {
    
        if (N->left_middle_child_->num_items_ >= 2) {
            redistribute_right(N, N->left_middle_child_, N->right_middle_child_, 1);
        } else if (N->right_child_->num_items_ >= 2) {
            redistribute_left(N, N->right_middle_child_, N->right_child_, 2);
        } else {
            return fuse(N, N->right_middle_child_, N->right_child_, 2);
        }

    } else if ((N->num_items_ == 3) && (key > N->large_key_) && (N->right_child_->num_items_ == 1)) {
    
        if (N->right_middle_child_->num_items_ >= 2) {
            redistribute_right(N, N->right_middle_child_, N->right_child_, 2);
        } else {
            return fuse(N, N->right_middle_child_, N->right_child_, 2);
        }

    }

    return N;
}

template <typename T>
TwoThreeFourNode<T>* TwoThreeFourTree<T>::innode_fix(TwoThreeFourNode<T>* P, T key) {

    if (key == P->small_key_) {

        if (P->left_middle_child_->num_items_ == 1) {
            if (P->left_child_->num_items_ >= 2) {
                redistribute_right(P, P->left_child_, P->left_middle_child_, 0);
                P->left_middle_child_ = remove(P->left_middle_child_, key);
            } else {
                TwoThreeFourNode<T>* OP = P;
                P = fuse(P, P->left_child_, P->left_middle_child_, 0);
                if (P != OP) {
                    P = remove(P, key);
//                    assert(is_leaf(P));
                } else {
                    P->left_child_ = remove(P->left_child_, key);
                }
            }
        } else {
            TwoThreeFourNode<T>* succ = inorder_successor(P->left_middle_child_);
            P->small_key_ = succ->small_key_;
            P->left_middle_child_ = remove(P->left_middle_child_, succ->small_key_);
        }

    } else if ((P->num_items_ >= 2) && (key == P->mid_key_)) {

        if (P->right_middle_child_->num_items_ == 1) {
            if (P->left_middle_child_->num_items_ >= 2) {
                redistribute_right(P, P->left_middle_child_, P->right_middle_child_, 1);
                P->right_middle_child_ = remove(P->right_middle_child_, key);
            } else {
                fuse(P, P->left_middle_child_, P->right_middle_child_, 1);
                P->left_middle_child_ = remove(P->left_middle_child_, key);
            }
        } else {
            TwoThreeFourNode<T>* succ = inorder_successor(P->right_middle_child_);
            P->mid_key_ = succ->small_key_;
            P->right_middle_child_ = remove(P->right_middle_child_, succ->small_key_);
        }

    } else if ((P->num_items_ == 3) && (key == P->large_key_)) {

        if (P->right_child_->num_items_ == 1) {
           if (P->right_middle_child_->num_items_ >= 2) {
                redistribute_right(P, P->right_middle_child_, P->right_child_, 2);
                P->right_child_ = remove(P->right_child_, key);
           } else {
                fuse(P, P->right_middle_child_, P->right_child_, 2);
                P->right_middle_child_ = remove(P->right_middle_child_, key);
            }
        } else {
            TwoThreeFourNode<T>* succ = inorder_successor(P->right_child_);
            P->large_key_ = succ->small_key_;
            P->right_child_ = remove(P->right_child_, succ->small_key_);
        }

    } else {
        std::cout << "Key: " << key << std::endl;
        std::cout << "Node(" << P->num_items_ << "): " << P->small_key_ << " " << P->mid_key_ << " " << P->large_key_ << std::endl;
        std::cout << P->left_child_ << " " << P->left_middle_child_ << " " << P->right_middle_child_ << " " << P->right_child_ << std::endl;
        throw std::runtime_error("Key not found");
    }

    return P;
}

template <typename T>
TwoThreeFourNode<T>* TwoThreeFourTree<T>::remove(TwoThreeFourNode<T>* N, T key) {

    if (N == nullptr) {
        throw std::runtime_error("Key not found in tree: "+std::to_string(key));
    }

    TwoThreeFourNode<T>* P = N;
    if (!is_leaf(N)) {
        P = fix(N, key);

        // Fix again if root was fused with children
        if (P != N) {
            P = fix(P, key);
        }
    }

    if (key < P->small_key_) {

        P->left_child_ = remove(P->left_child_, key);

    } else if ((P->num_items_ == 1) && (key > P->small_key_)) {

        P->left_middle_child_ = remove(P->left_middle_child_, key);

    } else if ((P->num_items_ >= 2) && (key > P->small_key_) && (key < P->mid_key_)) {

        P->left_middle_child_ = remove(P->left_middle_child_, key);

    } else if ((P->num_items_ == 2) && (key > P->mid_key_)) {

        P->right_middle_child_ = remove(P->right_middle_child_, key);

    } else if ((P->num_items_ == 3) && (key > P->mid_key_) && (key < P->large_key_)) {

        P->right_middle_child_ = remove(P->right_middle_child_, key);

    } else if ((P->num_items_ == 3) && (key > P->large_key_)) {

        P->right_child_ = remove(P->right_child_, key);

    } else {

        if(is_leaf(P)) {
            remove_key(P, key);
            return P;
        }

        P = innode_fix(P, key);

    }

    return P;
}

template <typename T>
void TwoThreeFourTree<T>::inorder_print() {
    inorder_print(root_);
    std::cout << std::endl;
}

template <typename T>
void TwoThreeFourTree<T>::inorder_print(TwoThreeFourNode<T>* N) {
    if(N != nullptr) {
        inorder_print(N->left_child_);
        std::cout << N->small_key_ << std::endl;
        inorder_print(N->left_middle_child_);
        if (N->num_items_ >= 2) std::cout << N->mid_key_ << std::endl;
        inorder_print(N->right_middle_child_);
        if (N->num_items_ == 3) std::cout << N->large_key_ << std::endl;
        inorder_print(N->right_child_);
    }
}

