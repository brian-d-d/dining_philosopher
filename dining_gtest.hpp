#ifndef DINING_GTEST_HPP_
#define DINING_GTEST_HPP_

#include <gtest/gtest.h>
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

        dining::waiter waiter_;
        std::vector<std::shared_ptr<dining::fork>> fork_vec_;
};

class paramwaiterTest : public waiterTest, public testing::WithParamInterface<int> {

};

class diningTest : public testing::Test {
    protected:
        void SetUp() override {
            for (int id = 1; id < 6; id++) {
                philosopher_vec_.push_back(std::make_shared<dining::philosopher>(waiter_, id));
            }
            // std::cout << "here0";
            // std::shared_ptr<dining::philosopher> philosopher1_v = philosopher_vec_[0];
           
            // std::cout << "here1";
            // philosopher1 = std::thread( [philosopher1_v]() {philosopher1_v.get()->ask_waiter();} );
          
            // std::cout << "here2";
            // philosopher1.join();
        }

        dining::waiter waiter_;
        std::vector<std::shared_ptr<dining::philosopher>> philosopher_vec_;
        std::thread philosopher1;
        std::thread philosopher2;
        std::thread philosopher3;
        std::thread philosopher4;
        std::thread philosopher5;
};

#endif