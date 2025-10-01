#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "bass.h"
#include "defines.h"

// TO:DO after finishing, move all offsets to a separate header file (Done)
#define RADIO_CMD "radio"

static void InitializeBass()
{
	if (!BASS_Init(-1, 44100, 0, 0, NULL)) {
		PrintToConsole("BASS_Init error: %d\n", BASS_ErrorGetCode());
		return;
	}

	BassInitialized = true;
	PrintToConsole("BASS initialized successfully!\n");
}

static void PrintAvailableCommands(void)
{
	PrintToConsole("Usage: %s <vol/play/stop>\n", RADIO_CMD);
}

static void RadioCmdHandler(void)
{
	if(!BassInitialized)
	{
		PrintToConsole("Radio system failed to initialize. %d\n", BASS_ErrorGetCode());
		return;
	}

	// ARGC is tricky! (It also count the command executed) + 1
	int argc = ReadArgc();
	const char* Command = ReadArgv(1); // First argument after the command
	const char* Value = ReadArgv(2); // Second argument after the command

	if (argc <= 1)
	{
		PrintAvailableCommands();
		return;
	}
	else
	{
		if (strcmp(Command, "vol") == 0)
		{
			if (argc != 3)
			{
				PrintToConsole("Usage: %s vol <0-100>\n", RADIO_CMD);
				return;
			}
			int volume = atoi(Value);

			if (volume < 0 || volume > 100)
			{
				PrintToConsole("Volume must be between 0 and 100.\n");
				return;
			}
			PrintToConsole("Radio volume set to %d%%\n", volume);

			BassVolume = volume;
			BASS_ChannelSetAttribute(BassStream, BASS_ATTRIB_VOL, BassVolume / 100.0f);
		}
		else if (strcmp(Command, "play") == 0)
		{
			if (argc != 3)
			{
				PrintToConsole("Usage: %s play <url>\n", RADIO_CMD);
				return;
			}

			if (BassStream)
			{
				BASS_StreamFree(BassStream);
				BassStream = 0;
			}

			BassStream = BASS_StreamCreateURL(Value, 0, 0, 0, 0);

			if (!BassStream) {
				PrintToConsole("Stream error: %d\n", BASS_ErrorGetCode());
				return;
			}

			BASS_ChannelSetAttribute(BassStream, BASS_ATTRIB_VOL, BassVolume / 100.0f);
			BASS_ChannelPlay(BassStream, FALSE);

			PrintToConsole("Connected to radio %s.\n", Value);
			
		}
		else if (strcmp(Command, "stop") == 0)
		{
			// Stop radio logic here
			PrintToConsole("Radio stopped.\n");

			if (BassStream)
			{
				BASS_StreamFree(BassStream);
				BassStream = 0;
			}
		}
		else
		{
			PrintToConsole("Unknown subcommand: %s\n", Command);
			PrintAvailableCommands();
		}
	}
}

static void Initialize()
{
	InitializeReferences();
	InitializeBass();

	HookCmd(RADIO_CMD, &RadioCmdHandler);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Initialize, NULL, 0, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		if (lpReserved == NULL) {
			if (BassStream) BASS_StreamFree(BassStream);
			if (BassInitialized) BASS_Free();
		}
		break;
    }
    return TRUE;
}

