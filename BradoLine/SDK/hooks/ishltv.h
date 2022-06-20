#pragma once
#include <intrin.h>

bool __fastcall hkIsHltv(void* this_pointer) {

	static auto original = minhook::ishltv.GetOriginal<decltype(&hkIsHltv)>();

	static const auto ret1 = patternscan("client.dll", "84 C0 75 38 8B 0D ? ? ? ? 8B 01 8B 80 ? ? ? ? FF D0"); //84 C0 75 38 8B 0D ? ? ? ? 8B 01 8B 80
	static const auto ret2 = patternscan("client.dll", "84 C0 75 0D F6 87"); //84 C0 75 0D F6 87

	if (_ReturnAddress() == (uint32_t*)(ret1))
		return true;

	if (_ReturnAddress() == (uint32_t*)(ret2))
		return true;

	return original(this_pointer);

}