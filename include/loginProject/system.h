#pragma once
#include <iostream>
#include <memory>
#include <vector>

#include "user.h"

namespace Login {
    class System {
       private:
        std::vector<std::shared_ptr<User>> users;

       public:
        System();
        void login();
        void display(std::shared_ptr<Login::User> user);
    };
}  // namespace Login