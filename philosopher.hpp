#ifndef PHILOSOPHER_HPP_
#define PHILOSOPHER_HPP_

#include <iostream>
#include "waiter.hpp"
#include "fork.hpp"

//1. Philosopher asks waiter if its required forks are free.
//2. Waiter checks these 2 forks
//3. If the 2 forks are free, the philosopher locks them
//4. After the philosopher finishes eating they unlock the forks

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
            if (waiter_.get_mutex().try_lock()) {
                if (waiter_.check_philosphers_forks(id_)) {
                    std::cout << "Forks free!" << std::endl;
                    eat();
                }
                else {
                    std::cout << "Forks taken" << std::endl;
                }
                waiter_.get_mutex().unlock();
            }
            else {
                std::cout << "Waiter busy" << std::endl;
            }
        }

        void eat() {
            std::cout << id_ << ": Eating" << std::endl;
            switch(id_) {
                case 1:
                    waiter_.lock_fork(1);
                    waiter_.lock_fork(2);
                    waiter_.unlock_fork(1);
                    waiter_.unlock_fork(2);
                    break;
                case 2:
                    waiter_.lock_fork(2);
                    // waiter_.lock_fork(3);
                    waiter_.unlock_fork(2);
                    // waiter_.unlock_fork(3);
                    break;
                case 3:
                    waiter_.lock_fork(3);
                    waiter_.lock_fork(4);
                    waiter_.unlock_fork(3);
                    waiter_.unlock_fork(4);
                    break;
                case 4:
                    waiter_.lock_fork(4);
                    waiter_.lock_fork(5);
                    waiter_.unlock_fork(4);
                    waiter_.unlock_fork(5);
                    break;
                case 5:
                    waiter_.lock_fork(1);
                    waiter_.lock_fork(5);
                    waiter_.unlock_fork(1);
                    waiter_.unlock_fork(5);
                    break;
            }
            std::cout << "eaten" << std::endl;
        }

    private:
        waiter& waiter_;
        int id_;
};

#endif