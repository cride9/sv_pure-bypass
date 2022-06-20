#pragma once
#include "globalvariables.h"

void __cdecl hkClMove(float fSamples, bool bFinalTick) {

	static auto original = minhook::clmove.GetOriginal<decltype(&hkClMove)>();

	// oh yes clmove calls createmove
	// so every tick is yessss
	// lets do it
	const auto clientdll = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("client.dll"));

	if (GetKeyState(VK_F2)) {

		const auto shooting = *reinterpret_cast<std::int32_t*>(clientdll + 0x3207FE8);

		if (GetAsyncKeyState(VK_LBUTTON) && g::Charged) {

			int tickshift = 0;
			while (tickshift != 16) {
				tickshift++;
				original(fSamples, bFinalTick);
			}
			g::Charged = false;
			g::Recharge = 17;
		}
		else if (!GetAsyncKeyState(VK_LBUTTON) && g::Recharge > 0 && !g::Charged) {

			g::Recharge--;

			if (g::Recharge == 0) {
				g::Charged = true;
			}

			return;
		}
	}

	return original(fSamples, bFinalTick);
}