#include <iostream>
#include <thread>
#include "philosopher.hpp"
#include "waiter.hpp"
#include "fork.hpp"
#include "monitor.hpp"

//1. Philosopher asks waiter if its required forks are free.
//2. Waiter checks these 2 forks
//3. If the 2 forks are free, the philosopher locks them
//4. After the philosopher finishes eating they unlock the forks

int main() {
    try {
        waiter waiter_f;
        monitor monitor_f(waiter_f);

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
        std::thread t6( [&monitor_f]() {monitor_f.print_fork_status();});

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();

    }
    catch (std::system_error& ec) {
        std::cout << ec.what() << std::endl;
    }
}