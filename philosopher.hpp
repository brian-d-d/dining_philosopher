#ifndef PHILOSOPHER_HPP_
#define PHILOSOPHER_HPP_

#include <iostream>
#include <chrono>
#include "waiter.hpp"
#include "fork.hpp"

class philosopher {
    public:
        philosopher(waiter& waiter_p, int id_p) : 
            waiter_(waiter_p),
            id_(id_p) {
        }
        
        philosopher(waiter& waiter_p) : 
            waiter_(waiter_p) {
        }

        //Can only ask waiter if no other threads are asking it
        //Locks the waiter and then unlocks the waiter if the waiter is free in the first place
        void ask_waiter() {
            for (;;) {
                std::this_thread::sleep_for(std::chrono::seconds(2));
                if (waiter_.get_mutex().try_lock()) {
                    if (waiter_.check_philosphers_forks(id_)) {
                        eat();
                    }
                    waiter_.get_mutex().unlock();
                }
                else {
                }
            }
        }

        void eat() {
            switch(id_) {
                case 1:
                    waiter_.lock_fork(1);
                    waiter_.lock_fork(2);
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    waiter_.unlock_fork(1);
                    waiter_.unlock_fork(2);
                    break;
                case 2:
                    waiter_.lock_fork(2);
                    waiter_.lock_fork(3);
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    waiter_.unlock_fork(2);
                    waiter_.unlock_fork(3);
                    break;
                case 3:
                    waiter_.lock_fork(3);
                    waiter_.lock_fork(4);
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    waiter_.unlock_fork(3);
                    waiter_.unlock_fork(4);
                    break;
                case 4:
                    waiter_.lock_fork(4);
                    waiter_.lock_fork(5);
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    waiter_.unlock_fork(4);
                    waiter_.unlock_fork(5);
                    break;
                case 5:
                    waiter_.lock_fork(1);
                    waiter_.lock_fork(5);
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    waiter_.unlock_fork(1);
                    waiter_.unlock_fork(5);
                    break;
            }
            std::cout << id_ << ": eaten" << std::endl;
        }

    private:
        waiter& waiter_;
        int id_;
};

#endif