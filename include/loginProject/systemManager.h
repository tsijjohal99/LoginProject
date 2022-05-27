#pragma once
#include "system.h"

namespace Login {
    class SystemManager {
       private:
        System sys;
        bool system_online{true};

       public:
        SystemManager();
        ~SystemManager();

        void mainLoop();
    };
}  // namespace Login