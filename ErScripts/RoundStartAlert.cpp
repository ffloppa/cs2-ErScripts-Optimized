#include "ErScripts.h"

void ErScripts::RoundStartAlert(SimpleSound& sound) {
        assert(sound);
        if (cfg->roundStartAlertState) {
            if (cfg->roundStartAlertFileName != lastCustomFile) {
                sound.secondBuffer(cfg->roundStartAlertFileName);

                lastCustomFile = cfg->roundStartAlertFileName;
            }

            if (globals::roundStartState != oldRoundStartState) {
                oldRoundStartState = globals::roundStartState;

                if (globals::roundStartState) {
                    if (!ErScripts::GetWindowState()) {
                        sound.setVolume(cfg->roundStartAlertVolume);
                        sound.play();
                    }
                }
            }
        }
}