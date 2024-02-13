#ifndef PHILOSOPHER_HPP_
#define PHILOSOPHER_HPP_

#include <iostream>
#include <chrono>
#include <thread>
#include "waiter.hpp"

namespace dining {

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
        //Locks the waiter and then unlocks the waiter if the waiter is free
        virtual void ask_waiter() {
            for (;;) {
                // std::cout << "hello";
                std::this_thread::get_id();
                std::this_thread::sleep_for(std::chrono::seconds(2));
                if (waiter_.get_mutex().try_lock()) {
                    if (waiter_.check_philosophers_forks(id_)) {
                        eat();
                    }
                    waiter_.get_mutex().unlock();
                }
            }
        }

        virtual void eat() {
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
        }

        virtual int get_id() {
            return id_;
        }

    private:
        waiter& waiter_;
        int id_;
};

}

#endif