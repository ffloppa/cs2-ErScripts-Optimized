#include "ErScripts.h"
void ErScripts::KillSay() {
    if (cfg->killSayState) {
        if (globals::localPlayerKills != oldKillsSay) {
            if (globals::localPlayerKills > oldKillsSay)
                CommandsSender(8, std::format("say {}", cfg->killSayText));
            oldKillsSay = globals::localPlayerKills;
        }
    }
}