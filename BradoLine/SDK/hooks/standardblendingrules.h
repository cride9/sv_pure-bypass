#pragma once

void __fastcall hkStandardBlendingRules(void* ecx, void* edx, void* hdr, void* pos, void* q, float current_time, int bone_mask) {

	static auto original = minhook::standardblendingrules.GetOriginal<decltype(&hkStandardBlendingRules)>();

	if (!ecx)
		return;

	auto effect = *reinterpret_cast<int*>(reinterpret_cast<std::uintptr_t>(ecx) + 0xF0);

	// fuck off interpolation
	if (!(effect & 8))
		effect |= 8;

	original(ecx, edx, hdr, pos, q, current_time, bone_mask);

	// aight you can come back now
	effect &= ~8;

}