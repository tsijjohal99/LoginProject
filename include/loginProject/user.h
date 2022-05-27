#pragma once
#include <iostream>

namespace Login {
    class User {
       private:
        std::string _username;
        std::string _password;
        std::string _secret_message;
        bool _admin;

       public:
        explicit User(std::string username, std::string password);
        explicit User(std::string username, std::string password, bool admin, std::string secret_message);

        std::string get_username();
        std::string get_password();
        std::string get_secret_message();
        void set_secret_message(const std::string& secret_message);
        bool get_admin();
    };
}  // namespace Login