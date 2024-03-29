#ifndef WAITER_HPP_
#define WAITER_HPP_

#include <mutex>
#include <memory>
#include <vector>
#include "fork.hpp"

#define NO_ONE_EATING 9999

namespace dining {

class Waiter {
    public:
        Waiter() {
                vec_.push_back(std::make_shared<Fork>());
                vec_.push_back(std::make_shared<Fork>());
                vec_.push_back(std::make_shared<Fork>());
                vec_.push_back(std::make_shared<Fork>());
                vec_.push_back(std::make_shared<Fork>());
            }

        //Checks if the forks for the specific philosopher are free
        virtual int check_philosophers_forks(int philosopher_id) {
            if (philosopher_id == 1) {
                eating_id_ = philosopher_id;
                return vec_[0].get()->check_fork() && vec_[1].get()->check_fork();
            }
            else if (philosopher_id == 2) {
                eating_id_ = philosopher_id;
                return vec_[1].get()->check_fork() && vec_[2].get()->check_fork();
            }
            else if (philosopher_id == 3) {
                eating_id_ = philosopher_id;
                return vec_[2].get()->check_fork() && vec_[3].get()->check_fork();
            }
            else if (philosopher_id == 4) {
                eating_id_ = philosopher_id;
                return vec_[3].get()->check_fork() && vec_[4].get()->check_fork();
            }
            else if (philosopher_id == 5) {
                eating_id_ = philosopher_id;
                return vec_[0].get()->check_fork() && vec_[4].get()->check_fork();
            }
            else {
                return false;
            }
        }
        
        virtual void lock_fork(int id) {
            vec_[id - 1].get()->get_mutex().lock();
        }

        virtual void unlock_fork(int id) {
            vec_[id - 1].get()->get_mutex().unlock();
            eating_id_ = NO_ONE_EATING;
        }

        virtual std::mutex& get_mutex() {
            return waiter_;
        }

        virtual std::vector<std::shared_ptr<Fork>>& get_vec() {
            return vec_;
        }

        virtual int get_eating_id() {
            return eating_id_;
        }

    private:
        //So only one philosopher can talk to this waiter at a time
        std::mutex waiter_;
        //So the waiter is able to check if each fork is in use
        std::vector<std::shared_ptr<Fork>> vec_;
        //ID of the philosopher who is currently eating
        int eating_id_;
};

}

#endif