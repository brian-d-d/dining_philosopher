#ifndef WAITER_HPP_
#define WAITER_HPP_

#include <mutex>
#include "fork.hpp"

class waiter {
    public:
        waiter(fork& fork1_p, fork& fork2_p, fork& fork3_p, fork& fork4_p, fork& fork5_p) : 
            fork1_(fork1_p),
            fork2_(fork2_p),
            fork3_(fork3_p),
            fork4_(fork4_p),
            fork5_(fork5_p) {}

        //Checks if the forks for the specific philosopher are free
        int check_philosphers_forks(int philosopher_id) {
            if (philosopher_id == 1) {
                return (fork1_.check_fork() && fork2_.check_fork());
            }
            else if (philosopher_id == 2) {
                return (fork2_.check_fork() && fork3_.check_fork());
            }
            else if (philosopher_id == 3) {
                return (fork3_.check_fork() && fork4_.check_fork());
            }
            else if (philosopher_id == 4) {
                return (fork4_.check_fork() && fork5_.check_fork());
            }
            else if (philosopher_id == 5) {
                return (fork1_.check_fork() && fork5_.check_fork());
            }
            else {
                return false;
            }
        }

        void lock_fork(int id) {
            switch(id) {
                case 1:
                    fork1_.get_mutex().lock(); break;
                case 2:
                    fork2_.get_mutex().lock(); break;
                case 3:
                    fork3_.get_mutex().lock(); break;
                case 4:
                    fork4_.get_mutex().lock(); break;
                case 5:
                    fork5_.get_mutex().lock(); break;
            }
        }

        void unlock_fork(int id) {
            switch(id) {
                case 1:
                    fork1_.get_mutex().unlock(); break;
                case 2:
                    fork2_.get_mutex().unlock(); break;
                case 3:
                    fork3_.get_mutex().unlock(); break;
                case 4:
                    fork4_.get_mutex().unlock(); break;
                case 5:
                    fork5_.get_mutex().unlock(); break;
            }
        }

        std::mutex& get_mutex() {
            return waiter_;
        }

    private:
        //So only one philospher can talk to this waiter at a time
        std::mutex waiter_;
        //So the waiter is able to check if each fork is in use
        fork& fork1_;
        fork& fork2_;
        fork& fork3_;
        fork& fork4_;
        fork& fork5_;
};

#endif