#ifndef MONITOR_HPP_
#define MONITOR_HPP_

#include <iostream>
#include <chrono>
#include <thread>
#include "waiter.hpp"

class monitor : public waiter {
    public:
        monitor(fork& fork1_p, fork& fork2_p, fork& fork3_p, fork& fork4_p, fork& fork5_p) : 
            waiter(fork1_p, fork2_p, fork3_p, fork4_p, fork5_p) {}  

        void print_fork_status() {
            for (;;) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "1 2 3 4 5" << std::endl;

                if (fork1_.get_mutex().try_lock())  {
                    std::cout << "f ";
                    fork1_.get_mutex().unlock();
                }
                else {
                    std::cout << "n ";
                }
                if (fork2_.get_mutex().try_lock())  {
                    std::cout << "f ";
                    fork2_.get_mutex().unlock();
                }
                else {
                    std::cout << "n ";
                }
                if (fork3_.get_mutex().try_lock())  {
                    std::cout << "f ";
                    fork3_.get_mutex().unlock();
                }
                else {
                    std::cout << "n ";
                }
                if (fork4_.get_mutex().try_lock())  {
                    std::cout << "f ";
                    fork4_.get_mutex().unlock();
                }
                else {
                    std::cout << "n ";
                }
                if (fork5_.get_mutex().try_lock())  {
                    std::cout << "f ";
                    fork5_.get_mutex().unlock();
                }
                else {
                    std::cout << "n ";
                }
                std::cout << std::endl << std::endl;
            }
            
        }

        void print_philosopher_status() {

        }

};

#endif