#include <iostream>
#include <thread>
#include "philosopher.hpp"
#include "waiter.hpp"
#include "fork.hpp"

// void test_func(int num) {
//     std::cout << num << "hello" << std::endl;
// }

int main() {
    try {
        fork fork1, fork2, fork3, fork4, fork5;
        waiter waiter_f (fork1, fork2, fork3, fork4, fork5);

        
        philosopher philosopher1(waiter_f, 1);
        std::thread t1( [&philosopher1]() {philosopher1.ask_waiter();});


        t1.join();

        // std::thread t3{ philosopher(waiter_f, 3) };
        // std::thread t4{ philosopher(waiter_f, 4) };
        // std::thread t5{ philosopher(waiter_f, 5) };
        
        // t2.join();
        // t3.join();
        // t4.join();
        // t5.join();

    }
    catch (std::system_error& ec) {
        std::cout << ec.what() << std::endl;
    }
}