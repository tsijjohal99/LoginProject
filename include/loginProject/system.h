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
        void addUser();
        bool ifAdmin(std::shared_ptr<Login::User> user);
        void adminMenu(std::shared_ptr<Login::User> user);
        void displayUsers();
        bool deleteUser(std::string username);
    };
}  // namespace Login