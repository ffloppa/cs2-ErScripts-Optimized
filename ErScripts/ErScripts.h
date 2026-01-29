#pragma once

#include "FileMonitor.h"
#include "GradientManager.h"
#include "Logger.h"
#include "Config.h"
#include "Globals.h"
#include <windows.h>
#include <string>
#include "SimpleSound.h"
#include "SoundsShellcodes.h"

class ErScripts {
public:
    void Initalization();
    void ConsoleLogStream(FileMonitor& monitor);
    static const bool GetCursorState();
    static const bool GetWindowState();
    static const void GetWindowInfo(int& width, int& height, int& posX, int& posY);
    static void CommandsSender(const int num, const std::string& command);
    static const void Keyboard(int wScan, bool isPressed, bool useScanCode = true);

    void InitBinds();
    void AutoAccept();
    void PixelTrigger();
    void Crosshair();
    void BombTimer();
    void RGBCrosshair();
    void KnifeSwitch();
    void AutoPistol();
    void AntiAfk();
    void CS2Binds();
    void KillSay();
    void KillSound(SimpleSound& sound);
    void RoundStartAlert(SimpleSound& sound);
    void AutoStop();
    void ChatSpammer();
	std::thread highUpdateThread;
	std::thread lowUpdateThread;
private:
    static HWND hwnd;

    std::wstring path;          // CS2 installation path
    static std::wstring config; // Path to cfg file
    std::wstring gsi;           // Path to gamestate_integration file
    std::wstring consoleLog;    // Path to console.log file

    bool foundMatch = false;    // For Auto Accept

    static bool bindsInit;      // Init Binds

    bool setPaths();            // Returns true if path is found and set
    bool configsValidation();   // Configs validation if not exist create

    const std::vector<int> GetPixelColor(int x, int y);
    const bool isColorSimilar(const std::vector<int>& color, const std::vector<int>& targetColor, int range);

    std::string lastCustomFile;
    int oldKills;
    int oldKillsSay;
    int oldKillsSound;
    bool oldKnifeState = false;
    bool oldRoundStartState = false;
    HDC hScreenDC;
    bool oldRecoilCrosshairState = false;

	// AutoStop members
    std::vector<int> recentDelays;
    bool aWasPressed = false;
    bool dWasPressed = false;

    bool state = false;
    bool statePrev = false;

    std::wsmatch match;
    SteamTools::Config config_default;

    void onHighUpdate() {
        FileMonitor monitor(consoleLog);
        monitor.start();
        while (!globals::finish) {
            std::this_thread::sleep_for(std::chrono::microseconds(15625));
			ConsoleLogStream(monitor);
            std::this_thread::sleep_for(std::chrono::microseconds(15625));
            CS2Binds();
            std::this_thread::sleep_for(std::chrono::microseconds(15625));
			PixelTrigger();
            std::this_thread::sleep_for(std::chrono::microseconds(15625));
            Crosshair();
            std::this_thread::sleep_for(std::chrono::microseconds(15625));
            RGBCrosshair();
            std::this_thread::sleep_for(std::chrono::microseconds(15625));
            AutoAccept();
            std::this_thread::sleep_for(std::chrono::microseconds(15625));
            AntiAfk();
        }
        ReleaseDC(nullptr, hScreenDC);
        monitor.stop();
    }

    void onLowUpdate() {
        SimpleSound m_soundround = SimpleSound(alertSound, alertSoundLen);
        m_soundround.secondBuffer(cfg->roundStartAlertFileName);
        lastCustomFile = cfg->roundStartAlertFileName;
        oldRoundStartState = globals::roundStartState;

        SimpleSound m_soundkill = SimpleSound(hitSound, hitSoundLen);
        m_soundkill.secondBuffer(cfg->killSoundFileName);
        lastCustomFile = cfg->killSoundFileName;
        oldKillsSound = globals::localPlayerKills;

        while (!globals::finish) {
            AutoStop();
            std::this_thread::sleep_for(std::chrono::microseconds(9000));
            RoundStartAlert(m_soundround);
            std::this_thread::sleep_for(std::chrono::microseconds(9000));
            KillSound(m_soundkill);
            std::this_thread::sleep_for(std::chrono::microseconds(9000));
            BombTimer();
            std::this_thread::sleep_for(std::chrono::microseconds(9000));
            KillSay();
            std::this_thread::sleep_for(std::chrono::microseconds(9000));
            KnifeSwitch();
            std::this_thread::sleep_for(std::chrono::microseconds(9000));
            AutoPistol();
            std::this_thread::sleep_for(std::chrono::microseconds(9000));
        }
	}
};