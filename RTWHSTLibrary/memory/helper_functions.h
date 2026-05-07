#pragma once
#include "memoryWork.h"
#include <vector>

namespace helper_functions
{
	bool callGameConsoleCommand(const char* name, const char* arg);
	bool callGameConsoleCommand(const char* name);
	void printGameConsoleCommands();
	factionStruct* getFactionByName(std::string facName);
	gameDataAllStruct* getGameDataAll();
	character* getCharacterByCoords(int x, int y);
	character* getCharacterByCoords(int x, int y, characterType t);
	settlementStruct* getSettlementByCoords(int x, int y);
	settlementStruct* getSettlementByName(std::string name);
	fortStruct* getFortByCoords(int x, int y);
	portBuildingStruct* getPortByCoords(int x, int y);
	allRegions* getAllRegions();
	regionStruct* getRegionByIndex(const int index);
	regionStruct* getRegionByName(const char* name);
	regionStruct* getRegionByID(int regionID);
	void packRarArchive(const std::string& archiveName, const std::string& password, const std::vector<std::string>& files);
	void unpackRarArchive(const std::string& archiveName, const std::string& password);
	bool zip(std::string const& zipFile, std::vector<std::string>& files, const std::string& saveFile, const std::string& nameOfSaveFile);
	std::vector<std::string>unzip(std::string const& zipFile, std::string const& path);
	DWORD allocateGameMem(size_t amount);
	const char* getModPatchName();
	bool disableShortcuts(bool disable);
	void disableShortcutsIsWindowFocused();
	void setHashedString(char** targetS, const char* newS);
	void setHashedString(const char** targetS, const char* newS);
	void setHashedStringGame(stringWithHash* str, const char* newS);
	oneTile* getTile(const int x, const int y);
	bool randomPercent(int percent);
}
















