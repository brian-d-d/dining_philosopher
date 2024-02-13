#include <gtest/gtest.h>
#include <vector>
#include <memory>
#include "dining_gtest.hpp"

TEST_F(waiterTest, forksunlocked) {
    for (std::shared_ptr<dining::fork> fork : fork_vec_) {
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

TEST_F(waiterTest, lockunlockfork) {
    waiter_.lock_fork(1);
    EXPECT_EQ(fork_vec_[0].get()->check_fork(), false);
    waiter_.unlock_fork(1);
    EXPECT_EQ(fork_vec_[0].get()->check_fork(), true);
}

TEST_F(waiterTest, checkeatingid) {
    waiter_.check_philosphers_forks(3);
    EXPECT_EQ(waiter_.get_eating_id(), 3);
}

TEST_F(diningTest, checkids) {
    for (int id = 1; id < 6; id++) {
        EXPECT_EQ(philosopher_vec_[id - 1].get()->get_id(), id);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}