
#include "memory/hotSeat/hotSeatCampaign.h"
#include "memory/hotSeat/createBattle.h"
#include "eopSettlements.h"
#include <fstream>
#include "differentFunctions/dm_assert.h"

using namespace std;

EOP_NEW_SETTLEMENTS EOP_SETTLEMENTS;

namespace eop_settlements
{
	settlementStruct* addSettlements(int xCoord, int yCoord, const char* name, const char* locName, factionStruct* faction)
	{
		LOG_ALWAYS(RELEASE, "addSettlements(coords: " + to_string(xCoord) + "," + to_string(yCoord) + ", name: " + string(name) + ", locName: " + string(locName)  + ", faction: " + string(faction->factSmDescr->facName) + ")");

	//	FUN_00896eb0 - addSettlementInEmptyRegion   

		oneTile* tile = helper_functions::getTile(xCoord, yCoord);
	//	if (tile->settlement || tile->fort || tile->port || !tile->isLand)
	//	{
	//		LOG_ALWAYS(RELEASE, "[ERROR] addSettlements(this tile is not free, coords: " + to_string(xCoord) + "," + to_string(yCoord) + ")");
	//		return nullptr;
	//	}


		regionStruct* region = helper_functions::getRegionByID(tile->regionId);

		planSet* plan = GAME_FUNC(planSet*(__thiscall*)(DWORD _this), 0x008ca9a8)(0x0018358c); // getPlanSet getPlanSet2

		int local_50 = 0xffffffff;
		settlementStruct* new_settlement = new settlementStruct;
		GAME_FUNC(settlementStruct*(__thiscall*)(settlementStruct* _this, planSet* plan_set, int level, int* capabilities, int facID), 0x005c4148)(new_settlement, plan, 0, &local_50, region->loyaltyFactionID); // settlementConstructor   

		helper_functions::setHashedString(&new_settlement->name, name);

		coords* c = new coords(xCoord, yCoord);
		stratPathFinding* stratPath = reinterpret_cast<stratPathFinding*>(0x01682ce4); // stratPathFinding 
		GAME_FUNC(void(__thiscall*)(stratPathFinding* _this, settlementStruct* sett, coords* c), 0x004c4af4)(stratPath, new_settlement, c); // spawnCreatedObject 

		const auto nameMem = new UNICODE_STRING*;
		new_settlement->localizedName = nameMem;
		createUniString(new_settlement->localizedName, locName);
	
		GAME_FUNC(void(__thiscall*)(settlementStruct* _this, factionStruct* fac), 0x005c86f0)(new_settlement, faction); // settAttachFaction 

		new_settlement->yearFounded = qa.campaignStruct->currentDate;
		new_settlement->regionID = tile->regionId;
		new_settlement->factionID = faction->dipNum;
		new_settlement->stats.faction = faction;
		new_settlement->faction = faction;
		new_settlement->smthingPosX = static_cast<float>(c->xCoord) + 0.5f;
		new_settlement->smthingPosY = static_cast<float>(c->yCoord) + 0.5f;
		new_settlement->subFactionID = faction->dipNum;
		new_settlement->turnsOwned = 10;
		new_settlement->settlementTaxLevel = 1;
		new_settlement->faction_creator = faction->dipNum;
		new_settlement->cultureID = faction->cultureID;
	//	new_settlement->isMinorSettlement = true;

	//	GAME_FUNC(void(__thiscall*)(settlementStatsManager* _this, unsigned int), 0x005dbbec)(&new_settlement->stats, 999);	// setPopulation   
		new_settlement->setPopulation(999);

		GAME_FUNC(void(__thiscall*)(settlementStruct* _this), 0x005c5ae8)(new_settlement); // createRallyPoint   
		GAME_FUNC(void(__thiscall*)(settlementStruct* _this, unsigned int* c), 0x005d13ac)(new_settlement, &new_settlement->xCoord); // initRallyPoint 

		GAME_FUNC(void(__thiscall*)(stratPathFinding*, settlementStruct*), 0x004cc75c)(stratPath, new_settlement); // areaOfInfluence   

		GAME_FUNC(void(__thiscall*)(settlementList* _this, settlementStruct* sett), 0x005d7e30)(&qa.campaignStruct->settlementList, new_settlement); // addToSettlementList   
		bool result = GAME_FUNC(bool(__thiscall*)(settlementStruct* _this), 0x004b0ab0)(new_settlement); // checkTileCharactersAlready   

	//	new_settlement->triumph = 1; // minorSettlementIndex  // ++ 

		GAME_FUNC(void(__thiscall*)(settlementStatsManager*, bool), 0x005d8e14)(&new_settlement->stats, true);	// recalculateSettlement   
	//	GAME_FUNC(void(__thiscall*)(settlementStruct*), 0x005c5f70)(new_settlement);	// restorePointers   


	#ifdef _DEBUG
		string nsl = uniStringToStr(new_settlement->localizedName);
		string rsl = uniStringToStr(region->localizedSettlementName);
		string rl = uniStringToStr(region->localizedRegionName);
		string rrl = uniStringToStr(region->localizedRebelsName);
		LOG_ALWAYS(RELEASE, "addSettlements(localizedName: " + nsl + ", region->localizedSettlementName: " + rsl + ", region->localizedRegionName: " + rl + ", region->localizedRebelsName: " + rrl + ", region->settlement->xCoord: " + to_string(region->settlement->xCoord) + ", region->settlement->yCoord: " + to_string(region->settlement->yCoord) + ")");
	#endif // _DEBUG

		string key = to_string(new_settlement->xCoord) + "_" + to_string(new_settlement->yCoord);
		EOP_SETTLEMENTS.m_minor_settlement_count++;
		EOP_SETTLEMENTS.m_settlement[key].add(new_settlement);

		return new_settlement;
	}

	void changeSettlementName(settlementStruct* sett, const char* newName)
	{
		const auto nameMem = new UNICODE_STRING*;
		sett->localizedName = nameMem;
		createUniString(sett->localizedName, newName);
		if (sett->triumph == 0)
		{
			if (const auto region = helper_functions::getRegionByID(sett->regionID); region)
				region->changeRegionSettlementName(newName);
		}
	}
}

void regionStruct::changeRegionSettlementName(const char* newName)
{
//	const auto nameMem = techFuncs::createGameClass<UNICODE_STRING*>();
	const auto nameMem = new UNICODE_STRING*;
	localizedSettlementName = nameMem;
	createUniString(localizedSettlementName, newName);
}

static bool checkJsonKey(json jsonArray, string key)
{
	if (jsonArray.is_object() || jsonArray.is_array())
	{
		for (auto& it : jsonArray.items())
		{
			auto k = it.key();
			auto v = it.value().type_name();
			if (key == k)
			{
				return true;
			}
		}
	}
	return false;
}

void EOP_NEW_SETTLEMENTS::onRestorePointers(settlementStruct* settlement)
{
#ifdef TEMPORARILY_DISABLE
	if (!m_is_save_load)
		return;


	string key = to_string(settlement->xCoord) + "_" + to_string(settlement->yCoord);
	if (!checkJsonKey(m_buffer_json, key))
		return;

	minor_settlement eop_settlement = m_settlement[key];
	m_buffer_json[key].at("is_minor").get_to(eop_settlement.m_is_minor);
	m_buffer_json[key].at("settlement_name").get_to(eop_settlement.m_settlement_name);
	m_buffer_json[key].at("region_capital_name").get_to(eop_settlement.m_region_capital_name);
	m_buffer_json[key].at("settlement_owner_id").get_to(eop_settlement.m_settlement_owner_id);
	m_buffer_json[key].at("region_id").get_to(eop_settlement.m_region_id);
	m_buffer_json[key].at("region_owner_id").get_to(eop_settlement.m_region_owner_id);
	m_buffer_json[key].at("region_capital_x").get_to(eop_settlement.m_region_capital_x);
	m_buffer_json[key].at("region_capital_y").get_to(eop_settlement.m_region_capital_y);
	m_settlement[key] = eop_settlement;

	regionStruct* region = helper_functions::getRegionByID(settlement->regionID);
	settlementStruct* capital = helper_functions::getSettlementByCoords(eop_settlement.m_region_capital_x, eop_settlement.m_region_capital_y);

	string settName = uniStringToStr(capital->localizedName);
	createUniString(region->localizedSettlementName, settName.c_str());

	region->factionOwner = helper_functions::getGameDataAll()->campaignData->factionsSortedByID[eop_settlement.m_region_owner_id];
	helper_functions::setHashedString(&settlement->name, eop_settlement.m_settlement_name.c_str());

//	region->settlement = capital;

	LOG_ALWAYS(RELEASE, "EOP_NEW_SETTLEMENTS::onRestorePointers(" + string(settlement->name) + ")");
#endif // TEMPORARILY_DISABLE


#ifdef FACTION_LIMIT_TESTS
	if (settlement->faction)
		return;

	// позже тут будет разные проверки   
//	factionStruct* new_faction = createFactionTEST(eop_settlement.m_settlement_owner_id);
//	factionStruct* new_faction = createFactionTEST(21);
	factionStruct* new_faction = eop_faction.getFactionByID(eop_settlement.m_settlement_owner_id);

	settlement->stats.faction = new_faction;
	settlement->faction = new_faction;

	LOG_ALWAYS(RELEASE, "onRestorePointers(" + string(settlement->faction->factSmDescr->facName) + ")");
#endif // FACTION_LIMIT_TESTS
}

void EOP_NEW_SETTLEMENTS::onSave()
{
	if (m_settlement.empty())
		return;

	LOG_ALWAYS(RELEASE, "EOP_NEW_SETTLEMENTS::onSave()");

	json data;
	data["minor_settlement_count"] = m_minor_settlement_count;

	for (int f = 0; f < 21; f++)
	{
		if (factionStruct* faction = helper_functions::getGameDataAll()->campaignData->factionsSortedByID[f])
		{
			for (int s = 0; s < faction->settlementsNum; s++)
			{
				settlementStruct* settlement = faction->settlements[s];
				string key = to_string(settlement->xCoord) + "_" + to_string(settlement->yCoord);
				minor_settlement eop_settlement = m_settlement[key];
				if (eop_settlement.m_is_minor)
				{
					regionStruct* region = helper_functions::getRegionByID(settlement->regionID);

				//	eop_settlement.m_settlement_name       = settlement->name;
				//	eop_settlement.m_region_capital_name   = region->settlementName;
					eop_settlement.m_settlement_owner_id   = settlement->faction->dipNum;
				//	eop_settlement.m_region_id             = settlement->regionID;
					eop_settlement.m_region_owner_id       = region->factionOwner->dipNum;
				//	eop_settlement.m_region_capital_x      = region->settlement->xCoord;
				//	eop_settlement.m_region_capital_y      = region->settlement->yCoord;

					json sett;

					sett["is_minor"]            = eop_settlement.m_is_minor;
					sett["settlement_name"]     = eop_settlement.m_settlement_name;
					sett["region_capital_name"] = eop_settlement.m_region_capital_name;
					sett["settlement_owner_id"] = eop_settlement.m_settlement_owner_id;
					sett["region_id"]           = eop_settlement.m_region_id;
					sett["region_owner_id"]     = eop_settlement.m_region_owner_id;
					sett["region_capital_x"]    = eop_settlement.m_region_capital_x;
					sett["region_capital_y"]    = eop_settlement.m_region_capital_y;

					data[key] = sett;
				}
			}
		}
	}

	string jsonFile = "dmData\\temp\\eop_settlements.json";
	ofstream file(jsonFile);
	file << setw(4) << data;
	file.close();

	saveFiles.files.push_back(jsonFile);
}

bool EOP_NEW_SETTLEMENTS::onLoad(campaign* camp)
{
	LOG_ALWAYS(RELEASE, "EOP_NEW_SETTLEMENTS::onLoad()");

	string settFile = "dmData\\temp\\eop_settlements.json";
	if (!fileExists(settFile))
		return false;

	ifstream file(filesystem::u8path(settFile));
	json data = json::parse(file);
	file.close();
	m_buffer_json = data;

	data.at("minor_settlement_count").get_to(m_minor_settlement_count);

	if (m_settlement.empty())
		return false;

	return true;
}

bool EOP_NEW_SETTLEMENTS::onAttachRegionSettlement(int regionID, settlementStruct* settlement)
{
	if (m_settlement.empty())
		return false;

	settlement->regionID = regionID;

	string key = to_string(settlement->xCoord) + "_" + to_string(settlement->yCoord);
	if (!checkJsonKey(m_buffer_json, key))
		return false;

	minor_settlement eop_settlement = m_settlement[key];
	m_buffer_json[key].at("is_minor").get_to(eop_settlement.m_is_minor);
	m_buffer_json[key].at("settlement_name").get_to(eop_settlement.m_settlement_name);
	m_buffer_json[key].at("region_capital_name").get_to(eop_settlement.m_region_capital_name);
	m_buffer_json[key].at("settlement_owner_id").get_to(eop_settlement.m_settlement_owner_id);
	m_buffer_json[key].at("region_id").get_to(eop_settlement.m_region_id);
	m_buffer_json[key].at("region_owner_id").get_to(eop_settlement.m_region_owner_id);
	m_buffer_json[key].at("region_capital_x").get_to(eop_settlement.m_region_capital_x);
	m_buffer_json[key].at("region_capital_y").get_to(eop_settlement.m_region_capital_y);
	m_settlement[key] = eop_settlement;

	regionStruct* region = helper_functions::getRegionByID(settlement->regionID);
	settlementStruct* capital = helper_functions::getSettlementByCoords(eop_settlement.m_region_capital_x, eop_settlement.m_region_capital_y);

	string settName = uniStringToStr(capital->localizedName);
	createUniString(region->localizedSettlementName, settName.c_str());

	region->factionOwner = helper_functions::getGameDataAll()->campaignData->factionsSortedByID[eop_settlement.m_region_owner_id];
	helper_functions::setHashedString(&settlement->name, eop_settlement.m_settlement_name.c_str());

//	region->settlement = capital;

	LOG_ALWAYS(RELEASE, "EOP_NEW_SETTLEMENTS::onAttachRegionSettlement(" + string(settlement->name) + ")");

	return true;
}

void EOP_NEW_SETTLEMENTS::onNewGameStart(campaign* camp)
{
	m_minor_settlement_count = 0;
	m_is_save_load = false;
	m_buffer_json;
	m_settlement.clear();
}
















