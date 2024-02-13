#ifndef WAITER_GTEST_HPP_
#define WAITER_GTEST_HPP_

#include "waiter.hpp"
#include <gtest/gtest.h>
#include <iostream>

class waiterTest : public testing::Test {
    protected:
        void SetUp() override {
            std::cout << "setup!" << std::endl;
        }

        waiter waiter_;
};

#endif