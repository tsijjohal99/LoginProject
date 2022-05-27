#pragma once
#include <chrono>
#include <iostream>

namespace Login {
    class User {
       private:
        std::string _username;
        std::string _password;
        std::string _secret_message;
        bool _admin;
        int _no_of_attempts{0};
        std::chrono::steady_clock::time_point _start;

       public:
        explicit User(std::string username, std::string password);
        explicit User(std::string username, std::string password, bool admin, std::string secret_message);

        std::string get_username();
        std::string get_password();
        std::string get_secret_message();
        void set_secret_message(const std::string& secret_message);
        bool get_admin();
        int get_no_of_attempts();
        void set_no_of_attempts(int no_of_attempts);
        std::chrono::steady_clock::time_point get_start();
        void set_start(std::chrono::steady_clock::time_point start);

        User& operator++();
        User operator++(int);
    };
}  // namespace Login