#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <memory>
#include "dining_gtest.hpp"

using ::testing::AtLeast;  

//Checks that all forks are unlocked on construction of waiter class
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

//Tests that each fork is locked and unlocked properly
TEST_P(paramwaiterTest, lockunlockeachfork) {
    waiter_.lock_fork(GetParam());
    EXPECT_EQ(fork_vec_[GetParam() - 1].get()->check_fork(), false);
    waiter_.unlock_fork(GetParam());
    EXPECT_EQ(fork_vec_[GetParam() - 1].get()->check_fork(), true);
}

//Tests that after a waiter locks 2 forks for a philosopher its id is saved in the eating_id_ variable
TEST_P(paramwaiterTest, checkeatingids) {
    waiter_.check_philosophers_forks(GetParam());
    EXPECT_EQ(waiter_.get_eating_id(), GetParam());
}

//Checks that the ids were set properly for each philosopher
TEST_F(diningTest, checkids) {
    for (int id = 0; id < 5; id++) {
        EXPECT_EQ(philosopher_vec_[id].get()->get_id(), id + 1);
    }
}

TEST(gmockwaiterTest, test) {
    waiterMock waiterMock_v;
    EXPECT_CALL(waiterMock_v, get_eating_id()).Times(1);
    waiterMock_v.get_eating_id();
}

TEST(gmockforkTest, test) {
    forkMock forkMock_v;
    EXPECT_CALL(forkMock_v, check_fork).Times(1);
    forkMock_v.check_fork();
}

TEST(gmockdiningTest, test) {
    waiterMock waiterMock_v;
    
}

INSTANTIATE_TEST_SUITE_P(paramtesting, paramwaiterTest, testing::Values(1, 2, 3, 4, 5));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();

    
    
}