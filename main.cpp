#include <iostream>
#include <thread>
#include "philosopher.hpp"
#include "waiter.hpp"
#include "fork.hpp"
#include "monitor.hpp"

//1. Philosopher checks to see if waiter is free
//2. If the waiter is free it asks if its 2 forks are free
//2. Waiter checks these 2 forks
//3. If the 2 forks are free, the waiter locks them
//4. After the philosopher finishes eating the waiter unlocks the forks

using namespace dining;

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
        std::thread t6( [&monitor_f]() {monitor_f.print_status();});

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();

    }
    catch (std::system_error& se) {
        std::cout << se.what() << std::endl;
    }
}