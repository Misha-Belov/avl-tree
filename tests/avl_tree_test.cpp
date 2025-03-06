#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <vector>

#include "avl_tree.h"

using namespace avl_tree;

TEST(BalanceTest, Trivial) {
    std::vector<int> queries{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    avl_tree_t<int> t;
    for (auto q : queries)
        t.insert_key(q);
    EXPECT_TRUE(t.is_balanced());
}

TEST(BalanceTest, Equals) {
    std::vector<int> queries{1, 1, 1, 1, 1};
    avl_tree_t<int> t;
    for (auto q : queries)
        t.insert_key(q);
    EXPECT_TRUE(t.is_balanced());
}
