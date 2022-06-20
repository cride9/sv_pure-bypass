#pragma once

void __fastcall hkDoExtraBonesProcessing(void* ECX, void* EDX, void* unkn1, void* unkn2, void* unkn3, void* unkn4, void* unkn5, void* unkn6)
{
	static auto original = minhook::extraboneprocessing.GetOriginal<decltype(&hkDoExtraBonesProcessing)>();

	if (!ECX)
		original(ECX, EDX, unkn1, unkn2, unkn3, unkn4, unkn5, unkn6);

	auto Health = *reinterpret_cast<int*>(reinterpret_cast<std::uintptr_t>(ECX) + 0x100);

	if (Health)
	{
		// animoverlay + 0x30
		int* v1 = reinterpret_cast<int*>(*reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(ECX) + 0x2990) + 0x30);

		// number of animoverlays
		for (int i = 13; i; --i)
		{
			if (reinterpret_cast<void*>(v1) != ECX)
			{
				*v1 = reinterpret_cast<uintptr_t>(ECX);
			}

			v1 += 14;
		}
	}

	return;
}