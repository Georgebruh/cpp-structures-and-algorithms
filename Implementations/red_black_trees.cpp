#pragma once
#include "../Interfaces/sorted_set.hpp"
#include "../Base_Structures/bt_node.hpp"

enum NodeColor { RED, BLACK };

template <typename T>
struct RBNode : public BTNode<T> {
    NodeColor color;

    RBNode(T val) : BTNode<T>(val) {
        color = RED;
    }
};

template <typename T>
class RedBlackTree : public SortedSet<T> {
protected:
    RBNode<T>* root;
    int count;

    RBNode<T>* rb(BTNode<T>* node) const {
        return static_cast<RBNode<T>*>(node);
    }

    void rotateLeft(RBNode<T>* pt) {
        RBNode<T>* pt_right = rb(pt->right);
        pt->right = pt_right->left;

        if (pt->right != nullptr) {
            pt->right->parent = pt;
        }

        pt_right->parent = pt->parent;

        if (pt->parent == nullptr) {
            root = pt_right;
        } else if (pt == rb(pt->parent)->left) {
            pt->parent->left = pt_right;
        } else {
            pt->parent->right = pt_right;
        }

        pt_right->left = pt;
        pt->parent = pt_right;
    }

    void rotateRight(RBNode<T>* pt) {
        RBNode<T>* pt_left = rb(pt->left);
        pt->left = pt_left->right;

        if (pt->left != nullptr) {
            pt->left->parent = pt;
        }

        pt_left->parent = pt->parent;

        if (pt->parent == nullptr) {
            root = pt_left;
        } else if (pt == rb(pt->parent)->left) {
            pt->parent->left = pt_left;
        } else {
            pt->parent->right = pt_left;
        }

        pt_left->right = pt;
        pt->parent = pt_left;
    }

    void fixInsert(RBNode<T>* pt) {
        RBNode<T>* parent_pt = nullptr;
        RBNode<T>* grand_parent_pt = nullptr;

        while ((pt != root) && (pt->color != BLACK) && (rb(pt->parent)->color == RED)) {
            parent_pt = rb(pt->parent);
            grand_parent_pt = rb(pt->parent->parent);

            if (parent_pt == grand_parent_pt->left) {
                RBNode<T>* uncle_pt = rb(grand_parent_pt->right);

                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->right) {
                        rotateLeft(parent_pt);
                        pt = parent_pt;
                        parent_pt = rb(pt->parent);
                    }
                    rotateRight(grand_parent_pt);
                    NodeColor t = parent_pt->color;
                    parent_pt->color = grand_parent_pt->color;
                    grand_parent_pt->color = t;
                    pt = parent_pt;
                }
            } else {
                RBNode<T>* uncle_pt = rb(grand_parent_pt->left);

                if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->left) {
                        rotateRight(parent_pt);
                        pt = parent_pt;
                        parent_pt = rb(pt->parent);
                    }
                    rotateLeft(grand_parent_pt);
                    NodeColor t = parent_pt->color;
                    parent_pt->color = grand_parent_pt->color;
                    grand_parent_pt->color = t;
                    pt = parent_pt;
                }
            }
        }
        root->color = BLACK;
    }

    RBNode<T>* insertBST(RBNode<T>* currentNode, RBNode<T>* pt) {
        if (currentNode == nullptr) return pt;

        if (pt->data < currentNode->data) {
            currentNode->left = insertBST(rb(currentNode->left), pt);
            currentNode->left->parent = currentNode;
        } else if (pt->data > currentNode->data) {
            currentNode->right = insertBST(rb(currentNode->right), pt);
            currentNode->right->parent = currentNode;
        }
        return currentNode;
    }

    void destroyTree(RBNode<T>* node) {
        if (node != nullptr) {
            destroyTree(rb(node->left));
            destroyTree(rb(node->right));
            delete node;
        }
    }

public:
    RedBlackTree() {
        root = nullptr;
        count = 0;
    }

    ~RedBlackTree() override {
        destroyTree(root);
    }

    bool add(T x) override {
        if (contains(x)) {
            return false;
        }

        RBNode<T>* pt = new RBNode<T>(x);
        root = insertBST(root, pt);
        fixInsert(pt);
        count++;
        return true;
    }

    bool remove(T x) override {
        return false;
    }

    bool contains(T x) const override {
        RBNode<T>* current = root;
        while (current != nullptr) {
            if (x == current->data) {
                return true;
            } else if (x < current->data) {
                current = rb(current->left);
            } else {
                current = rb(current->right);
            }
        }
        return false;
    }

    int size() const override {
        return count;
    }
};