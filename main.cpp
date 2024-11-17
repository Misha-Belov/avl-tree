#include <vector>
#include <iostream>
#include "avl_tree.h"

using namespace avl_tree;

int main()
{
    avl_tree_t<int> t;

    std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    for (int i = 0; i < data.size(); i++)
        t.insert_key(data[i]);

    t.print(std::cout);

    return 0;
}
