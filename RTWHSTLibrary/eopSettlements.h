#pragma once
#include "memory/gameStructures.h"
#include <map>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


#ifdef FACTION_LIMIT_TESTS
struct EOP_FACTION
{
	map<int, factionStruct*> m_faction;

//	factionStruct* getFactionByID(int facID) { return m_faction[facID]; }
	factionStruct* getFactionByID(int facID);

	bool is_new_faction_turn = false;
};
extern EOP_FACTION eop_faction;
#endif // FACTION_LIMIT_TESTS


struct minor_settlement
{
	bool        m_is_minor;
	std::string m_settlement_name;
	std::string m_region_capital_name;
	int         m_settlement_owner_id;
	int         m_region_owner_id;
	int         m_region_id;
	int         m_region_capital_x;
	int         m_region_capital_y;

	void        add(settlementStruct* settlement)
	{
		regionStruct* region = helper_functions::getRegionByID(settlement->regionID);

		m_is_minor              = true;
		m_settlement_name       = settlement->name;
		m_region_capital_name   = region->settlementName;
		m_settlement_owner_id   = settlement->faction->dipNum;
		m_region_owner_id       = region->factionOwner->dipNum;
		m_region_id             = settlement->regionID;
		m_region_capital_x      = region->settlement->xCoord;
		m_region_capital_y      = region->settlement->yCoord;
	}
};


struct EOP_NEW_SETTLEMENTS
{
	int                           m_minor_settlement_count = 0;
	bool                          m_is_save_load = false;
	json                          m_buffer_json;

//	std::vector<minor_settlement> settlement;
	std::map<std::string, minor_settlement> m_settlement;

	void                          onRestorePointers(settlementStruct* settlement);
	void                          onSave();
	bool                          onLoad(campaign* camp);
	void                          onNewGameStart(campaign* camp);
	bool                          onAttachRegionSettlement(int regionID, settlementStruct* settlement);
};
extern EOP_NEW_SETTLEMENTS EOP_SETTLEMENTS;

namespace eop_settlements
{
	settlementStruct* addSettlements(int xCoord, int yCoord, const char* name, const char* locName, factionStruct* faction);
	void changeSettlementName(settlementStruct* sett, const char* newName);
}

factionStruct* createFactionTEST(int facID);










