#include "helper_functions.h"
#include "../differentFunctions/screenshoter.h"
#include "hotSeat/createBattleResult.h"
#include <windows.h>
#include <fstream>
#include <filesystem>
#include <imgui.h>
#include <imgui_notify.h>
#include "../differentFunctions/stringThings.h"
#include <process.h>
#include <miniz/miniz.h>
#include "hotSeat/createBattle.h"
#include "hotSeat/hotSeatCampaign.h"
using namespace std;

namespace helper_functions
{
	bool callGameConsoleCommand(const char* name, const char* arg)
	{
		char errorBuffer[100]{};
		errorBuffer[0] = '\0';
		consoleCommands* cmd = reinterpret_cast<consoleCommands*>(0x02763240);
		for (int i = 0; i < cmd->size; i++)
		{
			auto currCom = cmd->commands[i];
			if (strcmp(currCom->name, name) != 0)
			{
				continue;
			}
			return (**currCom->function)(arg, errorBuffer);
		}

		string notif = "Command not found: " + string(name);
		LOG_ALWAYS(RELEASE, notif);
		ImGui::InsertNotification({ ImGuiToastType_Error, 5000, notif.c_str() });

		return false;
	}


	bool callGameConsoleCommand(const char* name)
	{
		const char* arg = "";
		char errorBuffer[100]{};
		errorBuffer[0] = '\0';
		consoleCommands* cmd = reinterpret_cast<consoleCommands*>(0x02763240);
		for (int i = 0; i < cmd->size; i++)
		{
			auto currCom = cmd->commands[i];
			if (strcmp(currCom->name, name) != 0)
			{
				continue;
			}
			return (**currCom->function)(arg, errorBuffer);
		}

		string notif = "Command not found: " + string(name);
		LOG_ALWAYS(RELEASE, notif);
		ImGui::InsertNotification({ ImGuiToastType_Error, 5000, notif.c_str() });

		return false;
	}


	void printGameConsoleCommands()
	{
		string printText = "'Rome: Total War - Alexander' console commands list: \n\n";
		consoleCommands* cmd = reinterpret_cast<consoleCommands*>(0x02763240);
		for (int i = 0; i < cmd->size; i++)
		{
			console_command* currCom = cmd->commands[i];

			printText = printText 
				+ "Number: " + to_string(i) + "\n" 
				+ string(currCom->name) + "\n"
				+ string(currCom->description) + "\n\n";
			//	+ to_string(currCom->type) + "\n"
			//	+ to_string(currCom->idk)
			//	+ "\n\n";
		}

		string file = "dmData/console_commands.dm";
		ofstream out;
		out.open(file, ios::out);
		if (out.is_open())
		{
			out << printText << endl;
		}
		out.close();

		LOG_ALWAYS(RELEASE, printText);
	}


	gameDataAllStruct* getGameDataAll()
	{
		if (qa.gDataAll) return qa.gDataAll;

		LOG_ALWAYS(RELEASE, "getGameDataAll()");
		qa.gDataAll = reinterpret_cast<gameDataAllStruct*>(memory::Read(gameWindow.RomeTW_ALX_exe + offsets.gDataAll));
		return qa.gDataAll;
	}

	factionStruct* getFactionByName(string facName)
	{
		for (int f = 0; f < 21; f++)
		{
			factionStruct* faction = qa.gDataAll->campaignData->factionsSortedByID[f];
			if (faction && facName == faction->factSmDescr->facName)
			{
				return faction;
			}
		}
		return nullptr;
	}

	character* getCharacterByCoords(int x, int y)
	{
		for (int f = 0; f < 21; f++)
		{
			if (factionStruct* faction = qa.gDataAll->campaignData->factionsSortedByID[f])
			{
				for (int c = 0; c < faction->numOfCharacters; c++)
				{
					character* ch = faction->characters[c];
					if (ch->xCoord == x && ch->yCoord == y)
					{
						return ch;
					}
				}
			}
		}
		return nullptr;
	}

	character* getCharacterByCoords(int x, int y, characterType t)
	{
		for (int f = 0; f < 21; f++)
		{
			if (factionStruct* faction = qa.gDataAll->campaignData->factionsSortedByID[f])
			{
				for (int c = 0; c < faction->numOfCharacters; c++)
				{
					character* ch = faction->characters[c];
					if (ch->xCoord == x && ch->yCoord == y && t == ch->genType->type)
					{
						return ch;
					}
				}
			}
		}
		return nullptr;
	}

	settlementStruct* getSettlementByCoords(int x, int y)
	{
		for (int f = 0; f < 21; f++)
		{
			if (factionStruct* faction = qa.gDataAll->campaignData->factionsSortedByID[f])
			{
				for (int s = 0; s < faction->settlementsNum; s++)
				{
					settlementStruct* sett = faction->settlements[s];
					if (sett->xCoord == x && sett->yCoord == y)
					{
						return sett;
					}
				}
			}
		}
		return nullptr;
	}

	settlementStruct* getSettlementByName(string name)
	{
		for (int f = 0; f < 21; f++)
		{
			if (factionStruct* faction = qa.gDataAll->campaignData->factionsSortedByID[f])
			{
				for (int s = 0; s < faction->settlementsNum; s++)
				{
					settlementStruct* sett = faction->settlements[s];
					if (strcmp(sett->name, name.c_str()) == 0)
					{
						return sett;
					}
				}
			}
		}
		return nullptr;
	}

	fortStruct* getFortByCoords(int x, int y)
	{
		for (int f = 0; f < 21; f++)
		{
			if (factionStruct* faction = qa.gDataAll->campaignData->factionsSortedByID[f])
			{
				for (int i = 0; i < faction->fortsNum; i++)
				{
					fortStruct* fort = faction->forts[i];
					if (fort->xCoord == x && fort->yCoord == y)
					{
						return fort;
					}
				}
			}
		}
		return nullptr;
	}

	portBuildingStruct* getPortByCoords(int x, int y)
	{
		for (int f = 0; f < 21; f++)
		{
			if (factionStruct* faction = qa.gDataAll->campaignData->factionsSortedByID[f])
			{
				for (int p = 0; p < faction->settlementsNum; p++)
				{
					portBuildingStruct* port = faction->settlements[p]->port;
					if (port && port->xCoord == x && port->yCoord == y)
					{
						return port;
					}
				}
			}
		}
		return nullptr;
	}

	allRegions* getAllRegions()
	{
		return reinterpret_cast<allRegions*>(0x0166C558);
	}

	regionStruct* getRegionByIndex(const int index)
	{
		allRegions* regions = getAllRegions();
		if (index < 0 || index >= 200)
			return nullptr;
		return &regions->regions[index];
	}

	regionStruct* getRegionByName(const char* name)
	{
		allRegions* regions = getAllRegions();
		for (int i = 0; i < 200; i++)
		{
			regionStruct* region = &regions->regions[i];
			if (region && strcmp(region->regionName, name) == 0)
			{
				return region;
			}
		}
		return nullptr;
	}
	
	regionStruct* getRegionByID(int regionID)
	{
		allRegions* regions = getAllRegions();
		for (int i = 0; i < 200; i++)
		{
			regionStruct* region = &regions->regions[i];
			if (region && region->regionID==regionID)
			{
				return region;
			}
		}
		return nullptr;
	}

	void setHashedString(char** targetS, const char* newS)
	{
		GAME_FUNC(void(__thiscall*)(char**, const char*), offsets.stringCryptFunc)(targetS, newS);
	}

	void setHashedString(const char** targetS, const char* newS)
	{
		GAME_FUNC(void(__thiscall*)(const char**, const char*), offsets.stringCryptFunc)(targetS, newS);
	}

	void setHashedStringGame(stringWithHash* str, const char* newS)
	{
		GAME_FUNC(void(__thiscall*)(stringWithHash*, const char*), offsets.stringCryptFunc)(str, newS);
	}

	oneTile* getTile(const int x, const int y)
	{
		stratMap* map = reinterpret_cast<stratMap*>(offsets.stratMap);
		if (map->isOpen)
			return map->getTile(x, y);
		return nullptr;
	}


	wchar_t* StrToWstr2(const std::string& aString)
	{
		// чтобы не делать каждый раз new создадим некоторый буфер заранее
		const int maxSize = 1024 * 1024; // 1ћб символов
		static wchar_t buff[maxSize];

		int nSize = ::MultiByteToWideChar(CP_UTF8, 0, aString.c_str(), static_cast<int>(aString.length() + 1), NULL, NULL);

		wchar_t* tBuff = buff;
		if (nSize > maxSize)
		{
			// пытаемс€ выделить пам€ть только если не хватило
			tBuff = new wchar_t[nSize];
		}
		if (nSize <= 0 && tBuff == NULL)
			return (wchar_t*)L"";

		::MultiByteToWideChar(CP_UTF8, 0, aString.c_str(), static_cast<int>(aString.length() + 1), buff, nSize);

		wchar_t* result(tBuff);

		if (tBuff != buff)
			delete[] tBuff;

		return result;
	}

	std::vector<std::string>unzip(std::string const& zipFile, std::string const& path)
	{
		filesystem::path fPath = path;
		std::vector<std::string> files = {};
		mz_zip_archive zipArchive = {};

		if (auto status = mz_zip_reader_init_file(&zipArchive, zipFile.c_str(), 0); !status)
			return files;
		int fileCount = static_cast<int>(mz_zip_reader_get_num_files(&zipArchive));
		if (fileCount == 0)
		{
			mz_zip_reader_end(&zipArchive);
			return files;
		}
		mz_zip_archive_file_stat fileStat;
		if (!mz_zip_reader_file_stat(&zipArchive, 0, &fileStat))
		{
			mz_zip_reader_end(&zipArchive);
			return files;
		}
		// Get root folder
		string base = fileStat.m_filename; // path delim on end
		base += "\\";

		// Get and print information about each file in the archive.
		for (int i = 0; i < fileCount; i++)
		{
			string lastDir;
			if (!mz_zip_reader_file_stat(&zipArchive, i, &fileStat)) continue;
			if (mz_zip_reader_is_file_a_directory(&zipArchive, i)) continue; // skip directories for now
			auto fileName = filesystem::path(fileStat.m_filename); // make path relative

			auto destFile = fPath;
			auto newPath = destFile.append(fileName.string()).string();
			//string destFile = combine_path(path, fileName); // make full dest path
			if (auto newDir = fileName.remove_filename(); newDir != lastDir)
			{
				auto newD = fPath;
				newD.append(newDir.string());
				if (!create_directory(newD)) // creates the directory
				{

				}
			}
			if (mz_zip_reader_extract_to_file(&zipArchive, i, destFile.string().c_str(), 0))
			{
				files.emplace_back(destFile.string());
			}
		}

		// Close the archive, freeing any resources it was using
		mz_zip_reader_end(&zipArchive);
		return files;
	}

	std::string readFile(const std::filesystem::path& path)
	{
		// Open the stream to 'lock' the file.
		std::ifstream f(path, std::ios::in | std::ios::binary);
		// Obtain the size of the file.
		const auto sz = file_size(path);
		// Create a buffer.
		std::string result(static_cast<size_t>(sz), '\0');
		// Read the whole file into the buffer.
		f.read(result.data(), sz);
		return result;
	}

	bool zip(std::string const& zipFile, std::vector<std::string>& files, const std::string& saveFile, const std::string& nameOfSaveFile)
	{
		mz_zip_archive zipArchive = {};
		mz_bool status = mz_zip_writer_init_file(&zipArchive, zipFile.c_str(), 0);
		if (!status)
		{
			MessageBoxA(nullptr, "1 Cannot create M2TWEOP save file.", "ERROR", NULL);
			return false;
		//	exit(0);
		}
		for (string& file : files)
		{
			status = mz_zip_writer_add_file(&zipArchive, filesystem::path(file).filename().string().c_str(), file.c_str(), nullptr, 0, MZ_DEFAULT_COMPRESSION);
			if (!status)
			{
				MessageBoxA(nullptr, "2 Cannot create M2TWEOP save file.", "ERROR", NULL);
				return false;
			//	exit(0);
			}
		}
	//	status = mz_zip_writer_add_file(&zipArchive, nameOfSaveFile.c_str(), saveFile.c_str(), nullptr, 0, MZ_DEFAULT_COMPRESSION);
	//	if (!status)
	//	{
	//		MessageBoxA(nullptr, "3 Cannot create M2TWEOP save file.", "ERROR", NULL);
	//		return false;
	//	//	exit(0);
	//	}
		status = mz_zip_writer_finalize_archive(&zipArchive);
		if (!status)
		{
			MessageBoxA(nullptr, "4 Cannot create M2TWEOP save file.", "ERROR", NULL);
			return false;
		//	exit(0);
		}
		status = mz_zip_writer_end(&zipArchive);
		if (!status)
		{
			MessageBoxA(nullptr, "5 Cannot create M2TWEOP save file.", "ERROR", NULL);
			return false;
		//	exit(0);
		}

		return true;
	}

	void packRarArchive(const string& archiveName, const string& password, const vector<string>& files)
	{
		string command = "\"dmData\\winrar\\rar.exe\" a -p" + password + " " + archiveName;
	
		for (const auto& file : files) {
			command += " " + file;
		}

		system(command.c_str());
	}

	void unpackRarArchive(const string& archiveName, const string& password)
	{
		string command = "\"dmData\\winrar\\unrar.exe\" x -p" + password + " " + archiveName;
		system(command.c_str());
	}


	// void * __cdecl _malloc(size_t _Size)
	// size_t lenS = strlen("test"); allocateGameMem(lenS);
	DWORD allocateGameMem(size_t amount)
	{
		typedef DWORD __cdecl func(size_t _Size);
		func* f = (func*)0x00f911b7;
		DWORD retMem = f(amount);

		return retMem;
	}

	const char* getModPatchName()
	{
		const char* mod = reinterpret_cast<const char*>(offsets.mod);
		return mod;
	}

	bool disableShortcuts(bool disable)
	{
		return GAME_FUNC(bool(__thiscall*)(DWORD, const char*, bool), offsets.disableShortcuts1)(offsets.disableShortcuts2, NULL, disable);
	}

	void disableShortcutsIsWindowFocused()
	{
		if (!gameWindow.controlsDisabled && ImGui::IsWindowFocused())
		{
			gameWindow.controlsDisabled = true;
			disableShortcuts(true);
		}
		else if (gameWindow.controlsDisabled && !ImGui::IsWindowFocused())
		{
			gameWindow.controlsDisabled = false;
			disableShortcuts(false);
		}
	}

	bool randomPercent(int percent) 
	{
		return percent >= (std::rand() % 100 + 1);
	}




}
























