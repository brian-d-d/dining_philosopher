#ifndef FORK_HPP_
#define FORK_HPP_

#include <mutex>
#include <iostream>

class fork {
    public:
        fork() {}
        //Return true if the fork is unlocked, returns false it is locked
        int check_fork() {
            if (fork_.try_lock()) {
                fork_.unlock();
                return true;
            }
            else {
                return false;
            }
        }

        std::mutex& get_mutex() {
            return fork_;
        }

        void test() {
            std::cout << "hello" << std::endl;
        }

    private:
        std::mutex fork_;
};

#endif