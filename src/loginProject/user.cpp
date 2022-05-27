#include "loginProject/user.h"

namespace Login {
    User::User(std::string username, std::string password)
        : _username(username), _password_hash(std::hash<std::string>{}(password)) {
        add_old_password(std::hash<std::string>{}(password));
    }

    User::User(std::string username, std::string password, bool admin, std::string secret_message)
        : _username(username), _password_hash(std::hash<std::string>{}(password)), _admin(admin), _secret_message(secret_message) {
        add_old_password(std::hash<std::string>{}(password));
    }

    std::string User::get_username() { return _username; }

    std::size_t User::get_password_hash() { return _password_hash; }

    void User::set_password_hash(std::size_t password_hash) { _password_hash = password_hash; }

    std::string User::get_secret_message() { return _secret_message; }

    void User::set_secret_message(const std::string& secret_message) { _secret_message = secret_message; }

    bool User::get_admin() { return _admin; }

    int User::get_no_of_attempts() { return _no_of_attempts; }

    void User::set_no_of_attempts(int no_of_attempts) { _no_of_attempts = no_of_attempts; }

    std::chrono::steady_clock::time_point User::get_start() { return _start; }

    void User::set_start(std::chrono::steady_clock::time_point start) { _start = start; }

    std::list<std::size_t> User::get_old_passwords() { return _old_passwords; }

    void User::add_old_password(std::size_t password_hash) { _old_passwords.push_back(password_hash); }

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