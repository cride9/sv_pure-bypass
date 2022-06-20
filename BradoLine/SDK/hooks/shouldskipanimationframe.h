#pragma once

bool __fastcall hkShouldSkipAnimationFrame(void* this_pointer, void* edx) {

	// the function is only called by SetupBones so there is no need to check for return address
	// returning false prevents copying of cached bone data

	return false;
}
