#pragma once

bool BassInitialized = false;

HSTREAM BassStream;
int     BassVolume = 30; // Default volume 30%

// Define the real function template for registering cvars
//typedef char* (__cdecl* pfnRegisterCvar_t)(cvar_t* cvar_to_register);
typedef void(__cdecl* pfnHookCmd_t)(char* cmd_name, void(*function_pointer)(void));
typedef int(__cdecl* pfnReadArgc_t)(void);
typedef char* (__cdecl* pfnReadArgv_t)(int arg);
//typedef char* (__cdecl* pfnReadArgs_t)(void);
typedef void(__cdecl* pfnPrintToConsole_t)(char* message, ...);


// Static offset for the RegisterCvar function in hw.dll
//uintptr_t registerCvarOffset	= 0x0002E960;
uintptr_t hookCmdOffset			= 0x000281a0;
uintptr_t readArgcOffset		= 0x00027ee0;
uintptr_t readArgvOffset		= 0x00027ef0;
//uintptr_t readArgsOffset		= 0x00027f20;
uintptr_t printToConsoleOffset  = 0x0002cb70;

//pfnRegisterCvar_t RegisterCvar;
pfnHookCmd_t HookCmd;
pfnReadArgc_t ReadArgc;
pfnReadArgv_t ReadArgv;
//pfnReadArgs_t ReadArgs;
pfnPrintToConsole_t PrintToConsole;

void InitializeReferences()
{
	// hw.dll is the main module for Half-Life (Engine)
	HMODULE hModule = GetModuleHandleA("hw.dll");

	if (hModule == NULL)
	{
		MessageBoxA(NULL, "[Radio] hw.dll not found!", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	uintptr_t baseAddress = (uintptr_t)hModule;

	//uintptr_t registerCvarAddress = baseAddress + registerCvarOffset;
	uintptr_t hookCmdAddress = baseAddress + hookCmdOffset;
	uintptr_t readArgcAddress = baseAddress + readArgcOffset;
	uintptr_t readArgvAddress = baseAddress + readArgvOffset;
	//uintptr_t readArgsAddress = baseAddress + readArgsOffset;
	uintptr_t printToConsoleAddress = baseAddress + printToConsoleOffset;

	//RegisterCvar = (pfnRegisterCvar_t)registerCvarAddress;
	HookCmd = (pfnHookCmd_t)hookCmdAddress;
	ReadArgc = (pfnReadArgc_t)readArgcAddress;
	ReadArgv = (pfnReadArgv_t)readArgvAddress;
	//ReadArgs = (pfnReadArgs_t)readArgsAddress;
	PrintToConsole = (pfnPrintToConsole_t)printToConsoleAddress;
}