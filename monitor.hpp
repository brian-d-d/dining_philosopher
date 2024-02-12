#ifndef MONITOR_HPP_
#define MONITOR_HPP_

#include <iostream>
#include <chrono>
#include <thread>
#include "waiter.hpp"

class monitor {
    public:
        monitor(waiter& waiter_p) : 
            waiter_(waiter_p) {}
        
        void print_fork_status() {
            for (;;) {
                std::this_thread::sleep_for(std::chrono::seconds(2));
                std::cout << "1 2 3 4 5" << std::endl;
                for (std::shared_ptr<fork> fork_p : waiter_.get_vec()) {
                    if (fork_p.get()->get_mutex().try_lock()) {
                        std::cout << "y ";
                        fork_p.get()->get_mutex().unlock();
                    }
                    else {
                        std::cout << "n ";
                    }
                }
                std::cout << std::endl << std::endl;
            }
        }

        void print_philosopher_status() {

        }
    
    private:
        waiter& waiter_;

};

#endif