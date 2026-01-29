#include "ErScripts.h"

void ErScripts::AntiAfk() {
    if (cfg->antiAfkState) {
        if (ErScripts::GetWindowState() && ErScripts::GetCursorState()) {
            if (globals::roundStartState != oldRoundStartState) {
                oldRoundStartState = globals::roundStartState;
    
                if (globals::roundStartState) {
                    if (!(GetAsyncKeyState('W') & 0x8000)) {
                        Keyboard('W', true, false);
                        std::this_thread::sleep_for(std::chrono::milliseconds((std::rand() % 3) + 16));
                        Keyboard('W', false, false);
                    }
                }
            }
        }
    }
}