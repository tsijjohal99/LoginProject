#include "loginProject/user.h"

namespace Login {
    User::User(std::string username, std::string password)
        : _username(username), _password(password) {}

    User::User(std::string username, std::string password, bool admin, std::string secret_message)
        : _username(username), _password(password), _admin(admin), _secret_message(secret_message) {}

    std::string User::get_username() { return _username; }

    std::string User::get_password() { return _password; }

    std::string User::get_secret_message() { return _secret_message; }

    void User::set_secret_message(const std::string& secret_message) { _secret_message = secret_message; }

    bool User::get_admin() { return _admin; }

    int User::get_no_of_attempts() { return _no_of_attempts; }

    void User::set_no_of_attempts(int no_of_attempts) { _no_of_attempts = no_of_attempts; }

    std::chrono::steady_clock::time_point User::get_start() { return _start; }

    void User::set_start(std::chrono::steady_clock::time_point start) { _start = start; }

    User& User::operator++() {
        ++_no_of_attempts;
        return *this;
    }

    User User::operator++(int) {
        User orig = *this;
        operator++();
        return orig;
    }
}  // namespace Login