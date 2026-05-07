#pragma once
#include <string>
#include "gameStructures.h"
#include "events/new_event.h"
#include "../differentFunctions/log.h"

void log_always(std::string text);   
void log_always(bool print, std::string text);
void log_reminder(std::string text);

void getAddresses();
std::string getAndPrintStratPosition();
std::string getClickCharacterName();
void killPMOpercent(float percent);
std::string boolStr(bool result);
void draw_main();
void setLanguageDLL();

struct launchSettings
{
	bool        playMusic    = true;
	std::string language     = "RU";
	std::string mainHotSeat  = "";
	bool        hideLauncher = false;
	uint8_t     ancLimit     = 8;
	int         logLevel     = 0;
	bool        debugExe	 = false;
	bool        debugDll	 = false;
	int         gameVersion  = 1;
};
extern launchSettings startSettings;

namespace memory
{
	uint32_t Read(uint32_t address);
	uint32_t ReadF(uint32_t address);
	void Write(void* ptr, DWORD to, size_t size);
	LONG detourAttach(PVOID* ppPointer, PVOID pDetour);
	LONG detourAttach(PVOID* ppPointer, PVOID pDetour, std::string function);
	LONG detourDetach(PVOID* ppPointer, PVOID pDetour);
	LONG detourDetach(PVOID* ppPointer, PVOID pDetour, std::string function);
}

#define GET_VARIABLE_NAME(Variable) (#Variable)
#define DETOUR_ATTACH(ppPointer, pDetour) memory::detourAttach(ppPointer, pDetour, GET_VARIABLE_NAME(pDetour))
#define DETOUR_DETACH(ppPointer, pDetour) memory::detourDetach(ppPointer, pDetour, GET_VARIABLE_NAME(pDetour))














