#include <gtest/gtest.h>
#include <vector>
#include <memory>
#include "waiter_gtest.hpp"
#include "fork.hpp"

TEST_F(waiterTest, forksunlocked) {
    for(std::shared_ptr<dining::fork> fork : fork_vec_) {
        EXPECT_EQ(fork.get()->check_fork(), true);
    }
}

TEST_F(waiterTest, fork1locked) {
    waiter_.lock_fork(1);
    EXPECT_EQ(fork_vec_[0].get()->check_fork(), false);
    EXPECT_EQ(fork_vec_[1].get()->check_fork(), true);
    EXPECT_EQ(fork_vec_[2].get()->check_fork(), true);
    EXPECT_EQ(fork_vec_[3].get()->check_fork(), true);
    EXPECT_EQ(fork_vec_[4].get()->check_fork(), true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}