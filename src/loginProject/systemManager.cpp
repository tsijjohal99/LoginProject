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
            sys.login();
            std::cout << "Would you like to shut down?\n";
            std::cout << "Press Y to shut down or any other key to log in again\n";
            char shut_down;
            std::cin >> shut_down;
            switch (shut_down) {
                case 'y':
                case 'Y': {
                    system_online = false;
                    break;
                }
            }
        }
    }
}  // namespace Login