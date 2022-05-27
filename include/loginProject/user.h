#pragma once
#include <iostream>

namespace Login {
    class User {
       private:
        std::string _username;
        std::string _password;
        std::string _secret_message;
        // bool admin;

       public:
        explicit User(std::string username, std::string password);

        std::string get_username();
        std::string get_password();
        std::string get_secret_message();
        void set_secret_message(const std::string& secret_message);
    };
}  // namespace Login