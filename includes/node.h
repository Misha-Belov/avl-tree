#pragma once

namespace avl_tree {
namespace _node {

template <typename KeyT>
class node_t
{
public:
    node_t(KeyT key) : key(key)
    {};

    node_t *left = nullptr;
    node_t *right = nullptr;
    node_t *parent = nullptr;
    int height = 1;
    KeyT key;
};

}
}
