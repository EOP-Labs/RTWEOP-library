#include "eopUnits.h"

eduThingsG dataU;

namespace eop_unit
{
	bool readEduFile(const char* fileName, eduEntry* entryForFilling)
	{
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

		*entryForFilling = fakeUnitDb->unitEntries[0];

		return result;
	}

	eduEntry* getEDUEntryById(int id)
	{
		unitDb* EDB = reinterpret_cast<unitDb*>(0x013006c0);

		int unitsNum = EDB->numberOfEntries;
		for (int i = 0; i < unitsNum; i++)
		{
			if (EDB->unitEntries[i].Index == id)
			{
				return &EDB->unitEntries[i];
			}
		}
		return nullptr;
	}

	eduEntry* getEopEduEntry(int idx)
	{
		for (eopEduEntry& entry : dataU.eopEdu)
		{
			if (entry.data.edu.Index == idx)
			{
				return &entry.data.edu;
			}
		}
		return nullptr;
	}

	unitDb* getEopUnitDb(int idx)
	{
		for (eopEduEntry& entry : dataU.eopEdu)
		{
			if (entry.data.edu.Index == idx)
			{
				return &entry.data.db;
			}
		}
		return nullptr;
	}

	eduEntry* getEopEduEntryByName(char* Type)
	{
		for (eopEduEntry& entry : dataU.eopEdu)
		{
			if (strcmp(entry.data.edu.Type, Type) == 0)
			{
				LOG_ALWAYS(DEVELOPMENT, "getEopEduEntryByName(" + string(Type) + ")");

				return &entry.data.edu;
			}
		}
		return nullptr;
	}
};









