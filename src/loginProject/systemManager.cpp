#include "loginProject/systemManager.h"

namespace Login {
    SystemManager::SystemManager() {
        System sys;
        system("cls");
        sys.login();
    }
}  // namespace Login