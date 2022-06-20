#include <Windows.h>
#include <thread>
#include <process.h>
#include <iostream>
#include <Psapi.h>
#include "hooking/minhook.h"
#include "hooking/trampoline.h"
#include "hooking/detour.hpp"
#include "globalvariables.h"
#include "hooks/ishltv.h"
#include "hooks/ispaused.h"
#include "hooks/proceduralfootplant.h"
#include "hooks/shouldskipanimationframe.h"
#include "hooks/clmove.h"
#include "hooks/updateclientsideanimations.h"
#include "hooks/standardblendingrules.h"
#include "hooks/extraboneprocessing.h"
#include "hooks/framestagenotify.h"
#include "hooks/sendnetmsg.h"

bool pressed = false;
void DllAttach(HINSTANCE hinstDLL) {

    // avoid crashing when we load the dll too early in the game
    while (!GetModuleHandleA("serverbrowser.dll"))
        Sleep(200);

    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONIN$", "r", stdin);
    freopen_s(&file, "CONOUT$", "w", stderr);
    freopen_s(&file, "CONOUT$", "w", stdout);

    std::cout << "Injected! HF" << std::endl;

    const auto enginedll = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("engine.dll"));
    const auto clientdll = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("client.dll"));

    std::cout << "Initializing Minhook..." << std::endl;

    if (MH_init() != MH_OK)
        std::cout << "Failed to initialize MinHook!" << std::endl;

    std::cout << "Minhook Initialized" << std::endl;

    while (true) {

        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(1s);

        // that's just the Skinny model for fun (m_flModelScale)
        const auto local = *reinterpret_cast<std::uintptr_t*>(clientdll + 0xDBB5CC);
        if (local && GetKeyState(VK_F2))
            *reinterpret_cast<float_t*>(local + 0x274C) = 0.5f;
         
        const auto clientstate = *reinterpret_cast<std::uintptr_t*>(enginedll + 0x58BFDC);
        const auto netchannel = *reinterpret_cast<std::uintptr_t*>(clientstate + 0x9C);

        if (netchannel) {

            if (!minhook::sendnetmsg.IsHooked()) {
                minhook::sendnetmsg.Create((void*)patternscan("engine.dll", "55 8B EC 83 EC 08 56 8B F1 8B 4D 04"), &hkSendNetMsg);
            }
        }
    }

    // those are working, but you cannot really inject any other cheat that has those hooks...
    // since that's a standalone sv_pure bypass we dont need anything else
    // if you hook clmove back you will have an instant teleport dt when pressing the mouse button (since im lazy to do shooting check)
    // (clientdll + 0x3207FE8) dwForceAttack (5 == shooting, 4 == not shooting)

    //if (!minhook::clmove.Create((void*)patternscan("engine.dll", "55 8B EC 81 EC ? ? ? ? 53 56 8A F9"), &hkClMove))
    //    std::cout << "Failed to initialize hkClMove!" << std::endl;

    //if (!minhook::ishltv.Create((void*)patternscan("engine.dll", "A1 ? ? ? ? 80 ? ? ? ? ? ? 75 0C"), &hkIsHltv))
    //    std::cout << "Failed to initialize hkIsHltv!" << std::endl;

    //if (!minhook::doproceduralfootplant.Create((void*)patternscan("client.dll", "55 8B EC 83 E4 F0 83 EC 78 56 8B F1 57 8B 56"), &hkDoProceduralFootPlant))
    //    std::cout << "Failed to initialize hkDoProceduralFootPlant!" << std::endl;

    //if (!minhook::shouldkipanimationframe.Create((void*)patternscan("client.dll", "57 8B F9 8B 07 8B ? ? ? ? ? FF D0 84 C0 75 02"), &hkShouldSkipAnimationFrame))
    //    std::cout << "Failed to initialize hkShouldSkipAnimationFrame!" << std::endl;

    //if (!minhook::standardblendingrules.Create((void*)patternscan("client.dll", "55 8B EC 83 E4 F0 B8 ? ? ? ? E8 ? ? ? ? 56 8B 75 08 57 8B F9 85"), &hkStandardBlendingRules))
    //    std::cout << "Failed to initialize hkStandardBlendingRules!" << std::endl;

    //if (!minhook::extraboneprocessing.Create((void*)patternscan("client.dll", "55 8B EC 83 E4 F8 81 ? ? ? ? ? 53 56 8B F1 57 89 74 24 1C"), &hkDoExtraBonesProcessing))
    //    std::cout << "Failed to initialize hkDoExtraBonesProcessing!" << std::endl;

    //if (!minhook::framestagenotify.Create((void*)patternscan("client.dll", "55 8B EC 8B 0D ? ? ? ? 8B 01 8B 80 ? ? ? ? FF D0 A2"), &hkFrameStageNotify))
    //    std::cout << "Failed to initialize hkFrameStageNotify!" << std::endl;

    // client.dll -> "55 8B EC 8B 0D ? ? ? ? 8B 01 8B 80 ? ? ? ? FF D0 A2" framestage


    //if (!minhook::updateclientsideanimations.Create((void*)patternscan("client.dll", "55 8B EC 51 56 8B F1 80 BE ? ? ? ? ? 74"), &hkUpdateClientSideAnimations))
    //    std::cout << "Failed to initialize hkUpdateClientSideAnimations!" << std::endl;

}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    // Perform actions based on the reason for calling.

    if (fdwReason == DLL_PROCESS_ATTACH) {

        DisableThreadLibraryCalls(hinstDLL);

        HANDLE Thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(DllAttach), hinstDLL, 0, nullptr);

        if (Thread)
            CloseHandle(Thread);
    }

    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}