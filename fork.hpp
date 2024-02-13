#ifndef FORK_HPP_
#define FORK_HPP_

#include <mutex>
#include <iostream>

namespace dining {
    
class fork {
    public:
        fork() {}
        //Return true if the fork is unlocked, returns false it is locked
        virtual int check_fork() {
            if (fork_.try_lock()) {
                fork_.unlock();
                return true;
            }
            else {
                return false;
            }
        }

        virtual std::mutex& get_mutex() {
            return fork_;
        }
        
    private:
        std::mutex fork_;
};

}

#endif