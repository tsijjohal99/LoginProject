#include "loginProject/systemManager.h"

namespace Login {
    SystemManager::SystemManager() {
        mainLoop();
    }

    SystemManager::~SystemManager() {
        std::cout << "System shut down\n";
    }

    void SystemManager::mainLoop() {
        while (system_online) {
            system("cls");

            std::cout << "Press 1 to add an user\n";
            std::cout << "Press 0 to shut down\n";
            std::cout << "Press Any other key to log in again\n ";
            char shut_down;
            std::cin >> shut_down;
            switch (shut_down) {
                case '1': {
                    sys.addUser();
                    break;
                }
                case '0': {
                    system_online = false;
                    break;
                }
                default: {
                    sys.login();
                }
            }
        }
    }
}  // namespace Login