#include "loginProject/system.h"

#include <iostream>

namespace Login {
    System::System() {
        users.push_back(std::make_shared<User>("admin", "password", true, "I am the admin"));
        addUser();
    }

    void System::login() {
        while (true) {
            std::string username, password;
            std::cout << "Please enter a username: ";
            std::cin >> username;
            std::cout << '\n';

            std::cout << "Please enter a password: ";
            std::cin >> password;
            std::cout << '\n';

            auto user_match = [&](std::shared_ptr<User> user) { return username == user->get_username(); };
            auto pass_match = [&](std::shared_ptr<User> user) { return password == user->get_password(); };

            auto username_iterator = std::find_if(users.begin(), users.end(), user_match);
            auto password_iterator = std::find_if(users.begin(), users.end(), pass_match);

            if (username_iterator == password_iterator && username_iterator != users.end()) {
                bool logged_in = true;
                while (logged_in) {
                    display(*username_iterator);
                    if (ifAdmin(*username_iterator))
                        adminMenu(*username_iterator);
                    std::cout << "Would you like to log out?\n";
                    std::cout << "Press Y to logout or any other key to stay logged in\n";
                    char logout;
                    std::cin >> logout;
                    switch (logout) {
                        case 'y':
                        case 'Y': {
                            logged_in = false;
                            break;
                        }
                    }
                }
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

    void System::addUser() {
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

    bool System::ifAdmin(std::shared_ptr<Login::User> user) { return user->get_admin(); }

    void System::adminMenu(std::shared_ptr<Login::User> user) {
        bool admin_logged_in = true;
        while (admin_logged_in) {
            int input;
            std::cout << "Press 1 to display users\n";
            std::cout << "Press 2 to delete user\n";
            std::cout << "Press 0 to log out\n";
            std::cin >> input;
            switch (input) {
                case 1: {
                    displayUsers();
                    break;
                }
                case 2: {
                    bool choose_username = true;
                    while (choose_username) {
                        std::string username_delete;
                        std::cout << "Enter the username of the user you would like to delete: ";
                        std::cin >> username_delete;
                        choose_username = deleteUser(username_delete);
                    }
                    break;
                }
                case 0: {
                    admin_logged_in = false;
                    break;
                }
                default:
                    std::cout << "Not a valid input\n";
                    break;
            }
        }
    }

    void System::displayUsers() {
        for (const auto& user : users)
            std::cout << user->get_username() << '\n';
    }

    bool System::deleteUser(std::string username) {
        auto user_match = [&](std::shared_ptr<User> user) { return username == user->get_username(); };
        auto username_iterator = std::find_if(users.begin(), users.end(), user_match);
        if (username_iterator != users.end()) {
            users.erase(username_iterator);
            return false;
        }
        std::cout << "Not a valid username\n";
        return true;
    }
}  // namespace Login