#pragma once
#include <intrin.h>

bool __stdcall hkIsPaused() {

	static auto original = minhook::ispaused.GetOriginal<decltype(&hkIsPaused)>();

	static auto ret = reinterpret_cast<std::uintptr_t*>(patternscan("client.dll", "0F B6 0D ? ? ? ? 84 C0 0F 44"));

	if (_ReturnAddress() == (void*)ret)
		return true;

	return original();
}