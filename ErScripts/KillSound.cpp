#include "ErScripts.h"
#include "SimpleSound.h"
#include "SoundsShellcodes.h"

void ErScripts::KillSound(SimpleSound& sound) {
        if (cfg->killSoundState) {
            if (cfg->killSoundFileName != lastCustomFile) {
                sound.secondBuffer(cfg->killSoundFileName);

                lastCustomFile = cfg->killSoundFileName;
            }

            if (globals::localPlayerKills != oldKillsSound) {
                if (globals::localPlayerKills > oldKillsSound && globals::localPlayerKills) {
                    sound.setVolume(cfg->killSoundVolume);
                    sound.play();
                }
                oldKillsSound = globals::localPlayerKills;
            }
        }
}