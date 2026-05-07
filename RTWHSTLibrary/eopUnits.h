#pragma once
#include "memory/events/new_event.h"
using namespace std;

namespace eop_unit
{
	bool readEduFile(const char* fileName, eduEntry* entryForFilling);
	eduEntry* getEDUEntryById(int id);
	eduEntry* getEopEduEntry(int idx);
	unitDb* getEopUnitDb(int idx);
	eduEntry* getEopEduEntryByName(char* Type);
}

struct eopEduEntry
{
	eopEduEntry(int baseIdx, int newIdx)
	{
		eduEntry* oldEn = eop_unit::getEDUEntryById(baseIdx);
		if (oldEn == nullptr)
		{
			string errs = "Can`t create eop`s unit entry:\n";
			errs += to_string(newIdx);
			MessageBoxA(NULL, errs.c_str(), "ERROR!", NULL);
			exit(0);
		}
		data.edu = *oldEn;
		data.edu.Index = newIdx;

		eopTypeName = "EOPT";
		eopTypeName.append(data.edu.Type);
		eopTypeName.append(to_string(newIdx));//added to make typename unique
	}
	eopEduEntry(const char* fileName, int newIdx)
	{
	//  другой способ 
	//	bool result = eop_unit::readEduFile(fileName, &data.edu);

		unitDb* fakeUnitDb = new unitDb;
		fakeUnitDb->qq = reinterpret_cast<unitDb*>(0x013006c0)->qq;

		GAME_FUNC(void(__thiscall*)(eduEntry*), 0x008de64c)(&fakeUnitDb->unitEntries[0]);
		fakeUnitDb->unitEntries[0].modelIndex = -1;
		fakeUnitDb->unitEntries[0].ChargeDistance = 0.f;

		fakeUnitDb->numberOfEntries = 0;
		fakeUnitDb->maxEntryNum = 1;
		fakeUnitDb->indexLookUps = new indexLookUp("", 0);
		fakeUnitDb->minusOne = -1;
		fakeUnitDb->smthingCmparedForTypeLookup = nullptr;

		bool result = new_events::onLoadEDU(fakeUnitDb, 0, fileName);

		data.edu = fakeUnitDb->unitEntries[0];
		data.db = *fakeUnitDb;

		if (!result)
		{
			std::string errS = "Can`t read edu file: ";
			errS += fileName;
			MessageBoxA(NULL, errS.c_str(), "ERROR!", NULL);
			throw "not good";
		}

		data.edu.Index = newIdx;

		eopTypeName = "EOPT";
		eopTypeName.append(data.edu.Type);
		eopTypeName.append(to_string(newIdx));//added to make typename unique
	}

	std::string eopTypeName;
	std::string eopUnitLabel;
	std::string eopSoldierString;
	struct dataS
	{
		eduEntry edu;
		unitDb db;
	}data;
};
struct eduThingsG
{
	vector<eopEduEntry>eopEdu;
};
extern eduThingsG dataU;
















