#include "pch.h"

HelperFunctions HelperFunctionsGlobal;
std::string modpath;

extern "C" {
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{

		HelperFunctionsGlobal = helperFunctions; // Save the helper pointer for external use
		modpath = path;

		ReadConfig(path, helperFunctions);
	}


	__declspec(dllexport) void __cdecl OnFrame()
	{

	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}