#pragma once

void __fastcall hkUpdateClientSideAnimations(void* ecx, void* edx) {

	static int index = 0;
	static auto original = minhook::updateclientsideanimations.GetOriginal<decltype(&hkUpdateClientSideAnimations)>();

	if (!ecx)
		return original(ecx, edx);

	auto pEnt = reinterpret_cast<std::uintptr_t>(ecx);

	auto Health = *reinterpret_cast<int*>(pEnt + 0x100);

	if (!Health)
		return;

	auto SimulationTime = *reinterpret_cast<float*>(pEnt + 0x268);
	static std::pair<std::uintptr_t, float> playerpairs[65];

	if (playerpairs[index].second != SimulationTime)
		original(ecx, edx);
	else
		return;

	if (playerpairs[0].first == reinterpret_cast<std::uintptr_t>(ecx))
		index = 0;

	playerpairs[index].first = reinterpret_cast<std::uintptr_t>(ecx);
	playerpairs[index].second = SimulationTime;
}