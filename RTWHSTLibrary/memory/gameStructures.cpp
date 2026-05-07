#include "memoryWork.h"
#include "../differentFunctions/stringThings.h"
#include "helper_functions.h"
#include "gameStructures.h"

using namespace std;


enumDescriptions ds;
formationType eduFormation;
factionLocName factionLocalizedName;


void unit::setExperience(const uint8_t exp)
{
	expScreen = exp;
	for (int i = 0; i < SoldierCountStrat; i++)
	{
		soldiersArr[i].experience = exp;
	}
}

battleStatus unit::checkUnitBattleStatus()
{
	LOG_ALWAYS(RELEASEFULL, "checkUnitBattleStatus(" + string(this->eduEntry->Type) + ")");

	battleStatus status{};
	new_events::o_onCheckUnitBattleStatus(this, 0, &status);

	return status;
}


std::string regionStruct::getLocalizedName()
{
	return uniStringToStr(localizedRegionName);
}

std::string regionStruct::getLocalizedRebelsName()
{
	return uniStringToStr(localizedRebelsName);
}


struct factionDiplomacyTest
{
public:
	int prevState;
	int32_t state;
	__int32 hasTradeRights : 1;
	__int32 hasMilitaryAccess : 1;
	__int8 isKnown : 1;
	__int8 lastDiplomaticResult : 1;
	__int8 isTrustWorthy : 1;
	__int8 isProtectorate : 1;
	int32_t aggressionLevel;
	int32_t protectoratePayment;
	int32_t numTurnsAllied;
	int32_t numTurnsWar;
	int numTreaties;
	int numAssists;
	int numAssistFailures;
	int numEmptyThreats;
	int numValidThreats;
	int32_t leaveTerritoryTimer;
	int winsInBattle;
	int tributeAmount;
	int tributeDuration;
	int preWarRegions[8];
	int turnsSinceLastMeeting;
	int32_t diplomaticSuccess;
	int diplomaticBalance;
	int32_t lastMapInfoTrade;
}; //Size: 0x0074

struct dipClassTest
{
	struct factionDiplomacyTest diplomaticStandings[21][21];
};

static dipClassTest* getDipStruct()
{
	return reinterpret_cast<dipClassTest*>(0x0165E4A4);
}

void campaign::setDipStance(const DipRelEnum dipType, const factionStruct* fac1, const factionStruct* fac2)
{
	if (!fac1 || !fac2 || !fac1->factSmDescr || !fac2->factSmDescr)
		return;

	if (dipType == Suzerain)
		return new_events::onSetVassal((void*)0x0165e4a4, 0, fac2->dipNum, fac1->dipNum);

	if (dipType == Trade)
	{
		dipClassTest* dip = getDipStruct();
		dip->diplomaticStandings[fac1->dipNum][fac2->dipNum].hasTradeRights = 1;
		dip->diplomaticStandings[fac2->dipNum][fac1->dipNum].hasTradeRights = 1;

		return;
	}

	if (dipType == MilitaryAccess)
	{
		dipClassTest* dip = getDipStruct();
		dip->diplomaticStandings[fac1->dipNum][fac2->dipNum].hasMilitaryAccess = 1;

		return;
	}


	string cmd = string(fac1->factSmDescr->facName) + " " + string(fac2->factSmDescr->facName) + " ";
	if (dipType == War)
		helper_functions::callGameConsoleCommand("diplomatic_stance", (cmd + "war").c_str());

	else if (dipType == Peace)
		helper_functions::callGameConsoleCommand("diplomatic_stance", (cmd + "neutral").c_str());

	else if (dipType == Alliance)
		helper_functions::callGameConsoleCommand("diplomatic_stance", (cmd + "allied").c_str());
}

bool campaign::checkDipStance(const DipRelEnum dipType, const factionStruct* fac1, const factionStruct* fac2)
{
	if (!fac1 || !fac2)
		return false;

	const auto facDiplomacy = diplomaticStandings[fac1->dipNum][fac2->dipNum];

	if (dipType == Trade)
		return getDipStruct()->diplomaticStandings[fac1->dipNum][fac2->dipNum].hasTradeRights;

	if (dipType == MilitaryAccess)
		return getDipStruct()->diplomaticStandings[fac1->dipNum][fac2->dipNum].hasMilitaryAccess;

	const auto state = facDiplomacy.state;
	if (dipType == War)
		return state == WarState;

	if (dipType == Peace)
		return state == PeaceState;

	if (dipType == Alliance)
		return state == AllianceState;

	if (dipType == Suzerain)
		return GAME_FUNC(bool(__thiscall*)(void* _this, int vassalID, int suzerainID), 0x005b2fa8)((void*)0x0165e4a4, fac2->dipNum, fac1->dipNum);	// onCheckVassal   

	return false;
}

UNICODE_STRING**& factionStruct::getLocalizedUnicodeName()
{
	return GAME_FUNC(UNICODE_STRING**&(__thiscall*)(factionStruct* _this), offsets.getLocalizedName)(this);
}

string factionStruct::getLocalizedNameAnsi()
{
	return uniToAnsi(getLocalizedUnicodeName());
}

string factionStruct::getLocalizedName()
{
	return uniStringToStr(getLocalizedUnicodeName());
}

factionLocName campaign::getLocalizedNames()
{
	LOG_ALWAYS(RELEASE, "campaign::getLocalizedNames()");

	if (factionLocalizedName.name[0].size() > 0)
		return factionLocalizedName;

	for (int f = 0; f < 21; f++)
	{
		if (factionsSortedByID[f])
		{
			factionLocalizedName.name[f]     = factionsSortedByID[f]->getLocalizedName();
		//	factionLocalizedName.nameAnsi[f] = factionsSortedByID[f]->getLocalizedNameAnsi();
		}
	}
	return factionLocalizedName;
}

factionStruct* campaign::getLocalFaction()
{
	return GAME_FUNC(factionStruct*(__thiscall*)(DWORD _this), offsets.getLocalFaction)(offsets.localFactionStruct);
}

void settlementStruct::setPopulation(unsigned int newPopulation)
{
	GAME_FUNC(void(__thiscall*)(settlementStatsManager* _this, unsigned int), offsets.setPopulation)(&this->stats, newPopulation);
}

stackStruct* settlementStruct::createArmyInSettlement()
{
	return GAME_FUNC(stackStruct*(__fastcall*)(settlementStruct* settlement), offsets.createArmyInSettlement)(this);
}
























