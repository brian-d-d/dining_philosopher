#include <gtest/gtest.h>
#include <vector>
#include <memory>
#include "dining_gtest.hpp"

TEST_F(waiterTest, forksunlocked) {
    for (std::shared_ptr<dining::fork> fork : fork_vec_) {
        EXPECT_EQ(fork.get()->check_fork(), true);
    }
}

//Checks that each fork can be locked properly
TEST_P(paramwaiterTest, eachforklock) {
    waiter_.lock_fork(GetParam());
    for (int i = 0; i < 5; i++) {
        if (i + 1 != GetParam()) {
            EXPECT_EQ(fork_vec_[i].get()->check_fork(), true);
        }
        else {  
            EXPECT_EQ(fork_vec_[i].get()->check_fork(), false);
        }
    }
}

//Tests that each for is locked and unlocked properly
TEST_P(paramwaiterTest, lockunlockeachfork) {
    waiter_.lock_fork(GetParam());
    EXPECT_EQ(fork_vec_[GetParam() - 1].get()->check_fork(), false);
    waiter_.unlock_fork(GetParam());
    EXPECT_EQ(fork_vec_[GetParam() - 1].get()->check_fork(), true);
}

TEST_P(paramwaiterTest, checkeatingids) {
    waiter_.check_philosphers_forks(GetParam());
    EXPECT_EQ(waiter_.get_eating_id(), GetParam());
}

TEST_F(diningTest, checkids) {
    for (int id = 1; id < 6; id++) {
        EXPECT_EQ(philosopher_vec_[id - 1].get()->get_id(), id);
    }
}

INSTANTIATE_TEST_SUITE_P(paramtesting, paramwaiterTest, testing::Values(1, 2, 3, 4, 5));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}