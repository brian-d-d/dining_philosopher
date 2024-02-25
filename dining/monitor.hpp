#ifndef MONITOR_HPP_
#define MONITOR_HPP_

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "waiter.hpp"

namespace dining {

class Monitor {
    public:
        Monitor(Waiter& waiter_p) : 
            waiter_(waiter_p),
            philosopher_eat_count_(std::vector(5, 0)) {}
        
        void print_status() {
            for (;;) {
                std::this_thread::sleep_for(std::chrono::seconds(2));
                int philosopher_id = waiter_.get_eating_id();

                if (philosopher_id != NO_ONE_EATING) {
                    std::cout << "1 2 3 4 5 ";
                    print_philosopher_status(philosopher_id);
                    std::cout << std::endl;

                    for (std::shared_ptr<Fork> fork_p : waiter_.get_vec()) {
                        if (fork_p.get()->get_mutex().try_lock()) {
                            std::cout << "y ";
                            fork_p.get()->get_mutex().unlock();
                        }
                        else {
                            std::cout << "n ";
                        }
                    }
                    std::cout << std::endl << std::endl;

                    print_total_count();
                }
            }
        }

        void print_philosopher_status(int id) {
            std::cout << "Philosopher " << id << " is eating";
            philosopher_eat_count_[id - 1]++;
        }

        void print_total_count() {
            std::cout << "1  2  3  4  5 ";
            std::cout << "Eat count" << std::endl;
            for (int philosopher : philosopher_eat_count_) {
                std::cout << philosopher << " ";
            }
            std::cout << std::endl << std::endl;
        }
    
    private:
        Waiter& waiter_;
        std::vector<int> philosopher_eat_count_;
        

};

}

#endif