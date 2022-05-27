#include "loginProject/system.h"

#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>

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
            // std::cout << '\n';

            std::cout << "Please enter a password: ";
            std::cin >> password;
            // std::cout << '\n';

            auto user_match = [&](std::shared_ptr<User> user) { return username == user->get_username(); };
            auto pass_match = [&](std::shared_ptr<User> user) { return std::hash<std::string>{}(password) == user->get_password_hash(); };

            auto username_iterator = std::find_if(users.begin(), users.end(), user_match);
            auto password_iterator = std::find_if(users.begin(), users.end(), pass_match);

            if (username_iterator != users.end()) {
                if ((*username_iterator)->get_no_of_attempts() >= 3) {
                    auto end = std::chrono::steady_clock::now();
                    std::chrono::duration<double> seconds = end - (*username_iterator)->get_start();
                    if (seconds.count() < 60) {
                        std::cout << "You are locked out of your account for " << 60 - (int)seconds.count() << " seconds\n";
                        continue;
                    }
                }
            }

            if (username_iterator == password_iterator && username_iterator != users.end()) {
                (*username_iterator)->set_no_of_attempts(0);
                bool logged_in = true;
                while (logged_in) {
                    display(*username_iterator);
                    if (ifAdmin(*username_iterator))
                        adminMenu(*username_iterator);
                    std::cout << "Press 1 to change password\n";
                    std::cout << "Press 0 to logout\n";
                    std::cout << "Press any other key to stay logged in\n";
                    char logout;
                    std::cin >> logout;
                    switch (logout) {
                        case '1': {
                            changePassword(*username_iterator);
                            break;
                        }
                        case '0': {
                            logged_in = false;
                            break;
                        }
                    }
                }
                break;
            } else {
                std::cout << "Username or Password is incorrect.\n";
                if (username_iterator != users.end()) {
                    (*username_iterator)->operator++();
                    std::cout << "Attempt: " << (*username_iterator)->get_no_of_attempts() << '\n';
                    if ((*username_iterator)->get_no_of_attempts() >= 3) {
                        (*username_iterator)->set_start(std::chrono::steady_clock::now());
                    }
                }
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
            std::cout << "Press 3 to unlock user\n";
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
                case 3: {
                    bool choose_username = true;
                    while (choose_username) {
                        std::string username_unlock;
                        std::cout << "Enter the username of the user you would like to unlock: ";
                        std::cin >> username_unlock;
                        choose_username = unlockUser(username_unlock);
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

    bool System::unlockUser(std::string username) {
        auto user_match = [&](std::shared_ptr<User> user) { return username == user->get_username(); };
        auto username_iterator = std::find_if(users.begin(), users.end(), user_match);
        if (username_iterator != users.end()) {
            (*username_iterator)->set_no_of_attempts(0);
            return false;
        }
        std::cout << "Not a valid username\n";
        return true;
    }

    void System::changePassword(std::shared_ptr<Login::User> user) {
        while (true) {
            std::string password;
            std::cout << "Enter a new password: ";
            std::cin >> password;
            std::size_t password_hash = std::hash<std::string>{}(password);

            auto old_passwords = user->get_old_passwords();
            auto pass_match = [&](std::size_t old_password) { return password_hash == old_password; };
            auto password_iterator = std::find_if(old_passwords.begin(), old_passwords.end(), pass_match);

            if (password_iterator != old_passwords.end()) {
                system("cls");
                std::cout << "You've already used that password\n";
            } else {
                user->add_old_password(password_hash);
                user->set_password_hash(password_hash);
                std::cout << "You're password has been changed\n";
                break;
            }
        }
    }
}  // namespace Login