#pragma once

#include <iostream>
#include <queue>
#include "node.h"

namespace avl_tree {

template <typename KeyT>
class avl_tree_t
{
public:
    using iterator = _node::node_t<KeyT> *;

    ~avl_tree_t()
    {
        if (!root_) return;

        std::queue<iterator> nodes;
        nodes.push(root_);
        while (!nodes.empty()) {
            iterator cur = nodes.front();
            nodes.pop();
            if (cur->left)
                nodes.push(cur->left);
            if (cur->right)
                nodes.push(cur->right);
            delete cur;
        }
    }

    iterator insert_key(KeyT key)
    {
        iterator *cur_node = &root_;
        iterator parent = nullptr;

        while (*cur_node != nullptr) {
            parent = *cur_node;
            if (key < (*cur_node)->key) {
                cur_node = &(*cur_node)->left;
            } else if (key == (*cur_node)->key) {
                return *cur_node;
            } else {
                cur_node = &(*cur_node)->right;
            }
        }

        *cur_node = new _node::node_t<KeyT>(key);
        (*cur_node)->parent = parent;

        balance_tree_(*cur_node);

        return *cur_node;
    }

    bool is_balanced()
    {
        std::queue<iterator> nodes;
        nodes.push(root_);
        while (!nodes.empty()) {
            iterator cur_node = nodes.front();
            nodes.pop();

            if (!cur_node)
                continue;

            int height_diff = height_diff_(cur_node);
            if (height_diff > 1 || height_diff < -1)
                return false;

            nodes.push(cur_node->left);
            nodes.push(cur_node->right);
        }
        return true;
    }

    template<typename Iterator>
    void insert_keys(Iterator begin, Iterator end)
    {
        for (auto it = begin; it != end; ++it)
            insert_key(*it);
    }

    void print(std::ostream& out)
    {
        print_recursive_(out, root_, 0);
    }

    void print_interval(KeyT a, KeyT b)
    {
        print_interval_recursive_(a, b, root_);
        std::cout << "\n";
    }

    
private:
    _node::node_t<KeyT> *root_ = nullptr;

    void print_interval_recursive_(KeyT a, KeyT b, iterator cur_node) {
        if (!cur_node) {
            return;
        }

        if (cur_node->left && cur_node->key >= a) {
            print_interval_recursive_(a, b, cur_node->left);
        }

        if (cur_node->key >= a && cur_node->key <= b)
            std::cout << cur_node->key << " ";

        if (cur_node->right && cur_node->key <= b) {
            print_interval_recursive_(a, b, cur_node->right);
        }

        return;
    }

    void print_recursive_(std::ostream& out, iterator node, size_t level)
    {
        if (!root_) return;

        if (node->right)
            print_recursive_(out, node->right, level + 1);

        for (size_t i = 0; i < level; ++i)
            out << "        ";
        out << node->key << "(H: " << node->height << ")" << "\n";

        if (node->left)
            print_recursive_(out, node->left, level + 1);
        
    }

    int height_diff_(iterator node)
    {
        int l_height = 0, r_height = 0;
        if (node->left)
            l_height = node->left->height;
        if (node->right)
            r_height = node->right->height;
        return l_height - r_height;
    }

    void balance_tree_(iterator new_node)
    {
        iterator cur_node = new_node;
        while (cur_node != nullptr) {
            int l_height = 0, r_height = 0;
            if (cur_node->left)
                l_height = cur_node->left->height;
            if (cur_node->right)
                r_height = cur_node->right->height;

            cur_node->height = std::max(r_height, l_height) + 1;
            cur_node = cur_node->parent;
        }
        
        cur_node = new_node;
        while (cur_node != nullptr) {
            int height_diff = height_diff_(cur_node);
            if (height_diff > 1 || height_diff < -1) {
                if (!cur_node->parent)
                    balance_subtree_(&root_);
                else if (cur_node->parent->left == cur_node)
                    balance_subtree_(&cur_node->parent->left);
                else
                    balance_subtree_(&cur_node->parent->right);
            }
            cur_node = cur_node->parent;
        }
    }

    void balance_subtree_(iterator *subtree)
    {
        int diff = height_diff_(*subtree);
        if (diff > 1) {
            int left_diff = height_diff_((*subtree)->left);
            if (left_diff >= 0) {
                rotate_right_(subtree);
                return;
            } else {
                rotate_left_(&(*subtree)->left);
                rotate_right_(subtree);
                return;
            }
        } else {
            int right_diff = height_diff_((*subtree)->right);
            if (right_diff <= 0) {
                rotate_left_(subtree);
                return;
            } else {
                rotate_right_(&(*subtree)->right);
                rotate_left_(subtree);
                return;
            }
        }
    }

    void rotate_right_(iterator *subtree)
    {
        iterator pivot = *subtree;
        iterator new_pivot = pivot->left;

        *subtree = new_pivot;
        new_pivot->parent = pivot->parent;

        pivot->left = new_pivot->right;
        if (pivot->left)
            pivot->left->parent = pivot;

        new_pivot->right = pivot;
        new_pivot->right->parent = new_pivot;

        pivot->height = 1;
        if (pivot->right)
            pivot->height = pivot->right->height + 1;
        if (pivot->left)
            pivot->height = pivot->left->height + 1;

        new_pivot->height = pivot->height + 1;
        if (new_pivot->left)
            new_pivot->height = new_pivot->left->height + 1;
    }

    void rotate_left_(iterator *subtree)
    {
        iterator pivot = *subtree;
        iterator new_pivot = pivot->right;

        *subtree = new_pivot;
        new_pivot->parent = pivot->parent;

        pivot->right = new_pivot->left;
        if (pivot->right)
            pivot->right->parent = pivot;

        new_pivot->left = pivot;
        new_pivot->left->parent = new_pivot;

        pivot->height = 1;
        if (pivot->left)
            pivot->height = pivot->left->height + 1;
        if (pivot->right)
            pivot->height = std::max(pivot->height, pivot->right->height + 1);

        new_pivot->height = pivot->height + 1;
        if (new_pivot->right)
            new_pivot->height = std::max(new_pivot->height, 
                new_pivot->right->height + 1);
    }
};

}
