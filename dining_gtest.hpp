#ifndef DINING_GTEST_HPP_
#define DINING_GTEST_HPP_

#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <vector>
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

class diningTest : public testing::Test {
    protected:
        void SetUp() {
            for (int id = 1; id < 6; id++) {
                philosopher_vec_.push_back(std::make_shared<dining::philosopher>(waiter_, id));
            }
        }

        dining::waiter waiter_;
        std::vector<std::shared_ptr<dining::philosopher>> philosopher_vec_;
};

#endif