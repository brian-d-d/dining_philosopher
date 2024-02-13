#ifndef WAITER_GTEST_HPP_
#define WAITER_GTEST_HPP_

#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <vector>
#include "waiter.hpp"
#include "fork.hpp"

class waiterTest : public testing::Test {
    protected:
        void SetUp() override {
            fork_vec_ = waiter_.get_vec();
        }

        dining::waiter waiter_;
        dining::fork fork_;

        std::vector<std::shared_ptr<dining::fork>> fork_vec_;
};

#endif