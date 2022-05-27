#pragma once
#include <chrono>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>

namespace Login {
    class User {
       private:
        std::string _username;
        // std::string _password;
        std::size_t _password_hash;
        std::string _secret_message;
        bool _admin{false};
        int _no_of_attempts{0};
        std::chrono::steady_clock::time_point _start;
        std::list<std::size_t> _old_passwords;

       public:
        explicit User(std::string username, std::string password);
        explicit User(std::string username, std::string password, bool admin, std::string secret_message);

        std::string get_username();
        std::size_t get_password_hash();
        void set_password_hash(std::size_t password_hash);
        std::string get_secret_message();
        void set_secret_message(const std::string& secret_message);
        bool get_admin();
        int get_no_of_attempts();
        void set_no_of_attempts(int no_of_attempts);
        std::chrono::steady_clock::time_point get_start();
        void set_start(std::chrono::steady_clock::time_point start);
        std::list<std::size_t> get_old_passwords();

        void add_old_password(std::size_t password_hash);

        User& operator++();
        User operator++(int);
    };
}  // namespace Login