#include <vector>
#include <iostream>
#include <assert.h>

#include "avl_tree.h"

using namespace avl_tree;

int main()
{
    // avl_tree_t<int> t;
    avl_tree_t<int> T;

    // std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9};
    // for (int i = 0; i < data.size(); i++)
    //     t.insert_key(data[i]);

    // t.print(std::cout);
    // t.print_interval(2, 8);

    while (std::cin.good())
    {
        char command = '\0';
        std::cin >> command;

        if (command == 'k') {
            int key = 0;
            std::cin >> key;

            T.insert_key(key);
        } else if (command == 'q') {
            int val1 = 0, val2 = 0;
            std::cin >> val1 >> val2;

            assert(val1 <= val2);

            T.print_interval(val1, val2);
        } else {
            std::cout << "wrong request \n";
            break;
        }
    }
    
    T.print(std::cout);
    return 0;
}
