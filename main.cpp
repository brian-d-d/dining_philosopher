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

        philosopher philosopher1(waiter_f, 1), 
                    philosopher2(waiter_f, 2), 
                    philosopher3(waiter_f, 3), 
                    philosopher4(waiter_f, 4), 
                    philosopher5(waiter_f, 5);

        std::thread t1( [&philosopher1]() {philosopher1.ask_waiter();});
        std::thread t2( [&philosopher2]() {philosopher2.ask_waiter();});
        std::thread t3( [&philosopher3]() {philosopher3.ask_waiter();});
        std::thread t4( [&philosopher4]() {philosopher4.ask_waiter();});
        std::thread t5( [&philosopher5]() {philosopher5.ask_waiter();});

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();

    }
    catch (std::system_error& ec) {
        std::cout << ec.what() << std::endl;
    }
}