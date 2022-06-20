#pragma once

void SetAbsAngles(void* ecx, float x, float y, float z)
{
	using Fn = void(__thiscall*)(void*, const float& anglesx, const float& anglesy, const float& anglesz);
	static Fn AbsAngles = (Fn)(patternscan("client.dll", "55 8B EC 83 E4 F8 83 EC 64 53"));

	AbsAngles(ecx, x, y, z);
}

void __stdcall hkFrameStageNotify(int curStage) {

	static auto original = minhook::framestagenotify.GetOriginal<decltype(&hkFrameStageNotify)>();

	//if (curStage == 5) {

	//	const auto clientdll = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("client.dll"));
	//	const auto enginedll = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("engine.dll"));
	//	const auto clientstate = *reinterpret_cast<std::uintptr_t*>(enginedll + 0x58BFDC);
	//	const auto local = *reinterpret_cast<std::uintptr_t*>(clientdll + 0xDBB5CC);
	//	const auto animstate = reinterpret_cast<std::uintptr_t*>((std::uintptr_t)local + 0x9960);

	//	if (local) {

	//		const auto animlayer = *reinterpret_cast<void**>(local + 0x2990);

	//		if (*reinterpret_cast<std::uintptr_t*>(local + 0x9960)) {
	//			if (*reinterpret_cast<std::uintptr_t*>(local + 0x100) > 0) {

	//				static void* animoverlay = 0;
	//				static float goalfeetyaw = 0;
	//				// TODO: check if new tick

	//				memcpy(animoverlay, animlayer, 0x38 * 13);

	//				if (!*(int*)(std::uintptr_t(clientstate) + 0x4D30)) {


	//					goalfeetyaw = *reinterpret_cast<std::uintptr_t*>(animstate + 0x80);
	//				}

	//				auto setabsangles = [](void* ecx, float x, float y, float z) {

	//					using Fn = void(__thiscall*)(void*, const float& anglesx, const float& anglesy, const float& anglesz);
	//					static Fn AbsAngles = (Fn)(patternscan("client.dll", "55 8B EC 83 E4 F8 83 EC 64 53"));

	//					AbsAngles(ecx, x, y, z);
	//				};
	//				setabsangles((void*)local, 0.f, goalfeetyaw, 0.f);

	//				memcpy(animlayer, animoverlay, 0x38 * 13);
	//			}
	//		}
	//	}

	//}

	original(curStage);
}