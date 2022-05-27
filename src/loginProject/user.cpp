#include "loginProject/user.h"

namespace Login {
    User::User(std::string username, std::string password)
        : _username(username), _password(password) {}

    std::string User::get_username() { return _username; }

    std::string User::get_password() { return _password; }

    std::string User::get_secret_message() { return _secret_message; }

    void User::set_secret_message(const std::string& secret_message) { _secret_message = secret_message; }
}  // namespace Login