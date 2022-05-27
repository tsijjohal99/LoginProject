#include "loginProject/system.h"

#include <iostream>

namespace Login {
    System::System() {
        std::string username, password, secret_message;
        std::cout << "Please set a username: ";
        std::cin >> username;
        std::cout << "Please set a password: ";
        std::cin >> password;
        users.push_back(std::make_shared<User>(username, password));
        std::cout << "Please set a secret message: ";
        std::cin >> secret_message;
        users.back()->set_secret_message(secret_message);
    }

    void System::login() {
        while (true) {
            std::string username, password;
            std::cout << "Please enter a username: ";
            std::cin >> username;
            auto user_match = [&](std::shared_ptr<User> user) { return username == user->get_username(); };

            std::cout << "Please enter a password: ";
            std::cin >> password;
            auto pass_match = [&](std::shared_ptr<User> user) { return password == user->get_password(); };

            auto username_iterator = std::find_if(users.begin(), users.end(), user_match);
            auto password_iterator = std::find_if(users.begin(), users.end(), pass_match);
            if (username_iterator == password_iterator && username_iterator != users.end()) {
                display(*username_iterator);
                break;
            } else {
                std::cout << "Username or Password is incorrect.\n";
                std::cout << "Please try again.\n";
            }
        }
    }

    void System::display(std::shared_ptr<Login::User> user) {
        std::cout << user->get_secret_message() << '\n';
    }
}  // namespace Login