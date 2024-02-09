#include <iostream>
#include <thread>
#include "philosopher.hpp"
#include "waiter.hpp"
#include "fork.hpp"

void test_func(int num) {
    std::cout << num << "hello" << std::endl;
}

int main() {
    try {
        fork fork1, fork2, fork3, fork4, fork5;
        waiter waiter_f (fork1, fork2, fork3, fork4, fork5);

        // philosopher philosopher1(waiter_f, 1), philosopher2(waiter_f, 2), philosopher3(waiter_f, 3), philosopher4(waiter_f, 4), philosopher5(waiter_f, 5);
        philosopher philosopher_test(waiter_f, 2);
        // std::lock_guard<std::mutex> lock(fork1.get_mutex());
        // std::thread t1 = std::thread(philosopher(waiter_f));
        std::thread t2( [&philosopher_test]() {philosopher_test.ask_waiter();});
        // std::thread t3{ philosopher(waiter_f, 3) };
        // std::thread t4{ philosopher(waiter_f, 4) };
        // std::thread t5{ philosopher(waiter_f, 5) };
        t2.join();
        // t2.join();
        // t3.join();
        // t4.join();
        // t5.join();

        // philosopher1.ask_waiter();
        // philosopher2.ask_waiter();
        // philosopher3.ask_waiter();
        // philosopher4.ask_waiter();
        // philosopher5.ask_waiter();

        std::thread test_thread(test_func, 5);
        test_thread.join();

    }
    catch (std::system_error& ec) {
        std::cout << ec.what() << std::endl;
    }
}