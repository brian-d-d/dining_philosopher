#ifndef WAITER_HPP_
#define WAITER_HPP_

#include <mutex>
#include <memory>
#include "fork.hpp"

class waiter {
    public:
        waiter() {
                vec_.push_back(std::make_shared<fork>());
                vec_.push_back(std::make_shared<fork>());
                vec_.push_back(std::make_shared<fork>());
                vec_.push_back(std::make_shared<fork>());
                vec_.push_back(std::make_shared<fork>());
                
                vec_.back().get()->test();
            }

        //Checks if the forks for the specific philosopher are free
        int check_philosphers_forks(int philosopher_id) {
            if (philosopher_id == 1) {
                return vec_[0].get()->check_fork() && vec_[1].get()->check_fork();
            }
            else if (philosopher_id == 2) {
                return vec_[1].get()->check_fork() && vec_[2].get()->check_fork();
            }
            else if (philosopher_id == 3) {

                return vec_[2].get()->check_fork() && vec_[3].get()->check_fork();
            }
            else if (philosopher_id == 4) {
                return vec_[3].get()->check_fork() && vec_[4].get()->check_fork();
            }
            else if (philosopher_id == 5) {
                return vec_[0].get()->check_fork() && vec_[4].get()->check_fork();
            }
            else {
                return false;
            }
        }

        void lock_fork(int id) {
            vec_[id - 1].get()->get_mutex().lock();
        }

        void unlock_fork(int id) {
            vec_[id - 1].get()->get_mutex().unlock();
        }

        std::mutex& get_mutex() {
            return waiter_;
        }

        std::vector<std::shared_ptr<fork>>& get_vec() {
            return vec_;
        }

    private:
        //So only one philospher can talk to this waiter at a time
        std::mutex waiter_;
        //So the waiter is able to check if each fork is in use
        std::vector<std::shared_ptr<fork>> vec_;
};

#endif