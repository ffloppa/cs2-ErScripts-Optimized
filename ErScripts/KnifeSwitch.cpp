#include "ErScripts.h"

void ErScripts::KnifeSwitch() {
        if (cfg->knifeSwitchState) {
            if (ErScripts::GetWindowState() && ErScripts::GetCursorState()) {
                if (globals::knifeState != oldKnifeState) {
                    CommandsSender(4, "switchhands");
                    oldKnifeState = globals::knifeState;
                }
            }
        }
}