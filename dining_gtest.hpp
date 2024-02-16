#ifndef DINING_GTEST_HPP_
#define DINING_GTEST_HPP_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include "waiter.hpp"
#include "fork.hpp"
#include "philosopher.hpp"

class waiterTest : public testing::Test {
    protected:
        void SetUp() override {
            fork_vec_ = waiter_.get_vec();
        }

        dining::Waiter waiter_;
        std::vector<std::shared_ptr<dining::Fork>> fork_vec_;
};

class waiterMock : public dining::Waiter {
    public:
        MOCK_METHOD(int, check_philosophers_forks, (int philosopher_id), (override));
        MOCK_METHOD(void, lock_fork, (int id), (override));
        MOCK_METHOD(void, unlock_fork, (int id), (override));
        MOCK_METHOD(std::mutex&, get_mutex, (), (override));
        MOCK_METHOD(std::vector<std::shared_ptr<dining::Fork>>&, get_vec, (), (override));
        MOCK_METHOD(int, get_eating_id, (), (override));
};

class forkMock : public dining::Fork {
    public:
        MOCK_METHOD(int, check_fork, (), (override));
        MOCK_METHOD(std::mutex&, get_mutex, (), (override));
};

class philosopherMock : public dining::Philosopher {
    public:
        MOCK_METHOD(void, ask_waiter, (), (override));
        MOCK_METHOD(void, eat, (), (override));
        MOCK_METHOD(int, get_id, (), (override));
};

class paramwaiterTest : public waiterTest, public testing::WithParamInterface<int> {};

class diningTest : public testing::Test {
    protected:
        void SetUp() override {
            for (int id = 1; id < 6; id++) {
                philosopher_vec_.push_back(std::make_shared<dining::Philosopher>(waiter_, id));
            }
            // std::cout << "here0";
            // std::shared_ptr<dining::philosopher> philosopher1_v = philosopher_vec_[0];
           
            // std::cout << "here1";
            // philosopher1 = std::thread( [philosopher1_v]() {philosopher1_v.get()->ask_waiter();} );
          
            // std::cout << "here2";
            // philosopher1.join();
        }

        dining::Waiter waiter_;
        std::vector<std::shared_ptr<dining::Philosopher>> philosopher_vec_;
        // std::thread philosopher1;
        // std::thread philosopher2;
        // std::thread philosopher3;
        // std::thread philosopher4;
        // std::thread philosopher5;
};

#endif