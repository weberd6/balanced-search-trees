
#include <iostream>

template <typename T>
void RBTree<T>::insert (const T key) {
    root_ = insert(root_, key);
    root_->color_ = Color::BLACK;
}

template <typename T>
void RBTree<T>::remove (const T key) {
    bool done = false;
    root_ = remove(root_, key, done);
    if (root_ != nullptr) {
        root_->color_ = Color::BLACK;
    }
}

template <typename T>
RBNode<T>* RBTree<T>::insert(RBNode<T>*& N, const T key) {

    if (N == nullptr) {
        return new RBNode<T>(key);
    }

    if (key < N->key_) {
        N->left_child_  = insert(N->left_child_, key);
    } else {
        N->right_child_ = insert(N->right_child_, key);
    }

    return insert_rebalance(N, key);
}

template <typename T>
T RBTree<T>::pop () {
    RBNode<T>* min_node = inorder_successor(root_);
    T key = min_node->key_;
    remove(key);
    return key;
}

template <typename T>
RBNode<T>* RBTree<T>::inorder_successor(RBNode<T>* N) {
    RBNode<T>* current = N;
    while (current->left_child_ != nullptr) {
        current = current->left_child_;
    }
    return current;
}

template <typename T>
RBNode<T>* RBTree<T>::remove(RBNode<T>*& N, const T key, bool& done) {

    if (N == nullptr) {
        return N;
    }

    if (key < N->key_) {
        N->left_child_ = remove(N->left_child_, key, done);
    } else if(key > N->key_) {
        N->right_child_ = remove(N->right_child_, key, done);
    } else {

        // node with only one child or no child
        if( (N->left_child_ == nullptr) || (N->right_child_ == nullptr) ) {

            RBNode<T>* temp = N->left_child_ ? N->left_child_ : N->right_child_;

            if (is_red(N)) {
                done = true; 
            } else if (is_red(temp)) {
                temp->color_ = Color::BLACK;
                done = true;
            }

            delete N;
            return temp;
        }

        RBNode<T>* temp = inorder_successor(N->right_child_);
        N->key_ = temp->key_;
        N->right_child_ = remove(N->right_child_, temp->key_, done);
    }

    if (!done) {
        return remove_rebalance(N, key, done);
    }

    return N;
}

template <typename T>
bool RBTree<T>::is_red(RBNode<T>* P) {
    return ((P != nullptr) && (P->color_ == Color::RED));
}

template <typename T>
RBNode<T>* RBTree<T>::insert_rebalance(RBNode<T>* P, T key) {

    if (is_red(P->left_child_)) {
        // In left subtree

        if (is_red(P->right_child_)) {
            // Red Uncle
            P->color_ = Color::RED;
            P->left_child_->color_ = Color::BLACK;
            P->right_child_->color_ = Color::BLACK;
        } else {
            // Black Uncle
            if (is_red(P->left_child_->left_child_)) {
                // Left Left
                P = rotate_right(P);
            } else if (is_red(P->left_child_->right_child_)) {
                // Left Right
                P->left_child_ = rotate_left(P->left_child_);
                P = rotate_right(P);
            }
        }
    } else if (is_red(P->right_child_)) {
        // Key lies in right subtree

        if (is_red(P->left_child_)) {
            // Red Uncle
            P->color_ = Color::RED;
            P->left_child_->color_ = Color::BLACK;
            P->right_child_->color_ = Color::BLACK;
        } else {
            // Black Uncle
            if (is_red(P->right_child_->left_child_)) {
                // Right Left
                P->right_child_ = rotate_right(P->right_child_);
                P = rotate_left(P);
            } else if (is_red(P->right_child_->right_child_)) {
                // Right Right
                P = rotate_left(P);
            }
        }
    }

    return P;
}

template <typename T>
RBNode<T>* RBTree<T>::remove_rebalance(RBNode<T>* P, T key, bool& done) {

    RBNode<T>* p = P;

    if (key < P->key_) {
        // null node is in left child

        RBNode<T>* sibling = P->right_child_;

        if (is_red(sibling)) {
            P = rotate_left(P);
            sibling = p->right_child_;
        }

        if (sibling != nullptr) {

            /* Black sibling cases */

            if (!is_red(sibling->left_child_) && !is_red(sibling->right_child_)) {

                if (is_red(p)) {
                    done = true;
                }

                p->color_ = Color::BLACK;
                sibling->color_ = Color::RED;

            } else {

                Color pcolor = p->color_;
                bool new_root = (P == p);
            
                if (is_red(sibling->right_child_)) {
                    // Right Right
                    p = rotate_left(p);
                } else {
                    // Right Left
                    p->right_child_ = rotate_right(p->right_child_);
                    p = rotate_left(p);
                }

                p->color_ = pcolor;
                p->left_child_->color_ = Color::BLACK;
                p->right_child_->color_ = Color::BLACK;

                if (new_root) {
                    P = p;
                } else {
                    P->left_child_ = p;
                }

                done = true;
            }
        }

    } else if (key > P->key_) {
        // null node is in right child

        RBNode<T>* sibling = P->left_child_;

        if (is_red(sibling)) {
            P = rotate_right(P);
            sibling = p->left_child_;
        }

        if (sibling != nullptr) {

            /* Black sibling cases */

            if (!is_red(sibling->left_child_) && !is_red(sibling->right_child_)) {

                if (is_red(p)) {
                    done = true;
                }

                p->color_ = Color::BLACK;
                sibling->color_ = Color::RED;

            } else {

                Color pcolor = p->color_;
                bool new_root = (P == p);
            
                if (is_red(sibling->left_child_)) {
                    // Left Left
                    p = rotate_right(p);
                } else {
                    // Left Right
                    p->left_child_ = rotate_left(p->left_child_);
                    p = rotate_right(p);
                }

                p->color_ = pcolor;
                p->left_child_->color_ = Color::BLACK;
                p->right_child_->color_ = Color::BLACK;

                if (new_root) {
                    P = p;
                } else {
                    P->right_child_ = p;
                }

                done = true;
            }
        }
    }

    return P;

}

template <typename T>
RBNode<T>* RBTree<T>::rotate_right(RBNode<T>*& P) {
    auto N = P->left_child_;

    P->left_child_ = N->right_child_;
    N->right_child_ = P;

    P->color_ = Color::RED;
    N->color_ = Color::BLACK;

    return N;
}

template <typename T>
RBNode<T>* RBTree<T>::rotate_left(RBNode<T>*& P) {
    auto N = P->right_child_;

    P->right_child_ = N->left_child_;
    N->left_child_ = P;

    P->color_ = Color::RED;
    N->color_ = Color::BLACK;

    return N;
}

template <typename T>
void RBTree<T>::inorder_print() {
    inorder_print(root_);
}

template <typename T>
void RBTree<T>::inorder_print(RBNode<T>* N) {
    if(N != nullptr) {
        inorder_print(N->left_child_);
        std::cout << N->key_ << std::endl;
        inorder_print(N->right_child_);
    }
}

