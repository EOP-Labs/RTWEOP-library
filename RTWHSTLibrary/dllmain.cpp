#include "Hook.h"
#include "memory/memoryWork.h"
#include "differentFunctions/screenshoter.h"
#include "differentFunctions/dm_assert.h"

BOOL WINAPI DllMain(const HINSTANCE hinstDLL, const DWORD fdwReason, LPVOID lpReserved)
{
	if (Hook::isReset)
	{
		Hook::isReset = false;
		getWindowRect();
	}

	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		while (fileExists("dmData\\configs\\isDebugDll.dm") && !IsDebuggerPresent())
		{
			Sleep(100);
		}

		LOG.openLogFile(1);
		LOG_ALWAYS(RELEASE, "DllMain(DLL_PROCESS_ATTACH)");
		DisableThreadLibraryCalls(hinstDLL);
		new_events::onDllProcessAttach();
		setLanguageDLL();
		Hook::hDDLModule = hinstDLL;
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Hook::HookDirectX, nullptr, 0, nullptr);
		getAddresses();
	}

	if (fdwReason == DLL_PROCESS_DETACH)
	{
		Hook::UnHookDirectX();
		new_events::onDllProcessDetach();
		LOG_ALWAYS(RELEASE, "DllMain(DLL_PROCESS_DETACH)");
		LOG.close();
	}

	return TRUE;
}










