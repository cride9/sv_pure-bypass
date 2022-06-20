#pragma once

#define INRANGE(x,a,b)   (x >= a && x <= b)
#define GET_BYTE( x )    (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))

namespace g {

	inline int Tickshift = 0;
	inline int Recharge = 0;
	inline bool Charged = true;
}

namespace minhook {
	inline CDetourHook createmove;
	inline CDetourHook clmove;
    inline CDetourHook sendnetmsg;
	inline CDetourHook ispaused;
	inline CDetourHook shouldkipanimationframe;
	inline CDetourHook doproceduralfootplant;
	inline CDetourHook ishltv;
    inline CDetourHook updateclientsideanimations;
    inline CDetourHook standardblendingrules;
    inline CDetourHook extraboneprocessing;
    inline CDetourHook framestagenotify;
}
static uintptr_t patternscan(const char* szModule, const char* szSignature)
{
    const char* pat = szSignature;
    DWORD firstMatch = 0;
    DWORD rangeStart = (DWORD)GetModuleHandleA(szModule);
    MODULEINFO miModInfo;
    GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
    DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
    for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
    {
        if (!*pat)
            return firstMatch;

        if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == GET_BYTE(pat))
        {
            if (!firstMatch)
                firstMatch = pCur;

            if (!pat[2])
                return firstMatch;

            if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
                pat += 3;

            else
                pat += 2;
        }
        else
        {
            pat = szSignature;
            firstMatch = 0;
        }
    }
    return 0u;
}