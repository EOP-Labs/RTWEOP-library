///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "memory/memoryWork.h"
#include "ImGui/backends/imgui_impl_dx9.h"
#include "ImGui/imgui_notify.h"
#include <imgui_stdlib.h>
#include "differentFunctions/dm_assert.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include "differentFunctions/screenshoter.h"
#include <ImFileDialog.h>
#include <gl/GL.h>
#include "Impl.h"
#include "memory/helper_functions.h"
#include "memory/hotSeat/hotSeatCampaign.h"
#include "Drawing.h"
#include "differentFunctions/stringThings.h"
#include "memory/events/monitor_event.h"
#include "memory/hotSeat/createBattle.h"
#include "differentFunctions/encryption.h"
#include <textures.h>
#include "eopUnits.h"
#include "tacticalMapViewer.h"
#include "eopSettlements.h"
#include "Hook.h"

using json = nlohmann::json;

launchSettings startSettings;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NOINLINE __declspec(noinline)
#define EOP_EXPORT extern "C" __declspec(dllexport)
NOINLINE EOP_EXPORT bool callDll(std::string fullPath, launchSettings settings, LOG_LEVEL loglevel, descriptionTab dt);

bool debuggCallDll = false;
NOINLINE EOP_EXPORT bool callDll(string fullPath, launchSettings settings, LOG_LEVEL loglevel, descriptionTab dt)
{
    while (debuggCallDll && !IsDebuggerPresent())
    {
        Sleep(100);
    }

//  string file = "dmData/callDll.log.dm";
//  ofstream out;
//  out.open(file, ios::app);
//  // out.open(file, ios::out);
//  if (out.is_open())
//  {
//      out << LOG.getTime(false) + " [.dll] " + "callDll()" << endl;
//  }
//  out.close();

    qa.fullPatch        = fullPath;
    startSettings       = settings;
    LOG.m_current_level = loglevel;
    desTab              = dt;

    LOG_ALWAYS(RELEASE, 
        "callDll(fullPath: " + fullPath + 
        ", playMusic: "      + boolStr(startSettings.playMusic) +
        ", language: "       + startSettings.language +
        ", mainHotSeat: "    + startSettings.mainHotSeat +
        ", hideLauncher: "   + boolStr(startSettings.hideLauncher) +
        ", ancLimit: "       + to_string(startSettings.ancLimit) +
        ", logLevel: "       + LOG.m_log_level_str[startSettings.logLevel] +
    ")");

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef OTHER_TESTS
// call game NEW ||| создает new классы   
//char* FUN_00ee12b0(int param_1,char *param_2,char *param_3,undefined4 param_4,undefined4 param_5)
using t_classCreatorNEW = marriageOption*(__cdecl*)(int param_1, char* param_2, char* param_3, undefined4 param_4, undefined4 param_5);
t_classCreatorNEW o_classCreatorNEW = nullptr;
marriageOption* __cdecl classCreatorNEW(int param_1, char* param_2, char* param_3, undefined4 param_4, undefined4 param_5)
{
//	LOG_ALWAYS(BUGTEST, "classCreatorNEW()");

	marriageOption* result = o_classCreatorNEW(param_1, param_2, param_3, param_4, param_5);

	return result;
}

static struct triggerStruct
{
	void* triggers;
	const char* triggerName;
};
//void __fastcall FUN_00846af0(int *param_1)
using t_onEventTrigger = void(__cdecl*)(triggerStruct* _this);
t_onEventTrigger o_onEventTrigger = nullptr;
void __cdecl onEventTrigger(triggerStruct* _this)
{
	LOG_ALWAYS(BUGTEST, "onEventTrigger(" + string(_this->triggerName) + ")");
	o_onEventTrigger(_this);
}

// createUniString
//void __fastcall FUN_00ec99b0(undefined4 *param_1)
using t_onCreateUniString = HRESULT(__fastcall*)(UNICODE_STRING**& param_1, int stub, char* param_3);
t_onCreateUniString o_onCreateUniString = nullptr;
HRESULT __fastcall onCreateUniString(UNICODE_STRING**& param_1, int stub, char* param_3)
{
	HRESULT result = o_onCreateUniString(param_1, stub, param_3);

#ifdef _DEBUG_UNI
	string save1 = uniStringToStr(param_1);
	string save2 = uniToAnsi(param_1);

	//	createUniString(param_1, save2.c_str());

	string text = param_3;
	if (text.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_/.,{:#%	- \\()\n[]!<>") != string::npos)
	{
		LOG_ALWAYS(BUGTEST, "onCreateUniString(" + text + ")");
	}

	if (strcmp(text.c_str(), "testname") == 0 || strcmp(save2.c_str(), "testname") == 0)
	{
		LOG_ALWAYS(BUGTEST, "onCreateUniString(" + text + ")");
	}
#endif // __DEBUG

	return result;
}

bool podmena = false;
//void onCreateUniStringFromSharedTxtFile(undefined4 param_1)
using t_onCreateUniStringFromSharedTxtFile = UNICODE_STRING * *&(__cdecl*)(int param_1);
t_onCreateUniStringFromSharedTxtFile o_onCreateUniStringFromSharedTxtFile = nullptr;
UNICODE_STRING**& __cdecl onCreateUniStringFromSharedTxtFile(int param_1)
{
	UNICODE_STRING**& result = o_onCreateUniStringFromSharedTxtFile(param_1);

	if (podmena)
	{
		string text = uniToAnsi(result);
		if (strcmp(text.c_str(), "Адмирал") == 0)
		{
			string u8str = u8"слово";
			createUniString(result, u8str.c_str());
			//	createUniString(result, "BLA BLA BLA");
			LOG_ALWAYS(BUGTEST, "podmena: Адмирал -> BLA BLA BLA");
		}
	}

	return result;
}

// UNIT RENDER 
//void __thiscall FUN_009c2188(int param_1,int param_2)   
using t_onUnitRender = HRESULT(__fastcall*)(unit* _this, int stub, unit* param_1);
t_onUnitRender o_onUnitRender = nullptr;
HRESULT __fastcall onUnitRender(unit* _this, int stub, unit* param_1)
{
	return o_onUnitRender(_this, stub, param_1);
}

// void __thiscall FUN_005dbbec(int param_1,uint param_2)  
using t_onSetPopulation = int(__fastcall*)(settlementStatsManager* _this, int stub, unsigned int population);
t_onSetPopulation o_onSetPopulation = nullptr;
int __fastcall onSetPopulation(settlementStatsManager* _this, int stub, unsigned int population)
{
	LOG_ALWAYS(BUGTEST, "onSetPopulation()");
	return o_onSetPopulation(_this, stub, population);
}

using t_game_begin_scene = HRESULT(__cdecl*)(char param_1, char param_2);
t_game_begin_scene o_game_begin_scene = nullptr;
HRESULT __cdecl game_begin_scene(char param_1, char param_2)
{
	return o_game_begin_scene(param_1, param_2);
}

using t_game_end_scene = HRESULT(__cdecl*)();
t_game_end_scene o_game_end_scene = nullptr;
HRESULT __cdecl game_end_scene()   // -- game::end_scene()   
{
	return o_game_end_scene();
}

// onMoveToTile(undefined4* param_1, int* param_2, undefined4 param_3, undefined4 param_4, byte param_5)
using t_onMoveToTile = HRESULT(__fastcall*)(void* _this, int stub, character* character, int x, int y, BYTE param_5);
t_onMoveToTile o_onMoveToTile = nullptr;

HRESULT __fastcall onMoveToTile(void* _this, int stub, character* character, int x, int y, BYTE param_5)
{
//	LOG_ALWAYS(BUGTEST, "onMoveToTile()");

	HRESULT result = o_onMoveToTile(_this, stub, character, x, y, param_5);

	return result;
}

// undefined4 __thiscall FUN_0059b27c(int param_1,int *param_2)
using t_onMoveToTile_2 = HRESULT(__fastcall*)(character* _this, int x, int y);
t_onMoveToTile_2 o_onMoveToTile_2 = nullptr;
HRESULT __fastcall onMoveToTile_2(character* _this, int x, int y)
{
//	LOG_ALWAYS(BUGTEST, "onMoveToTile_2()");

	HRESULT result = o_onMoveToTile_2(_this, x, y);

	return result;
}

// void __thiscall FUN_004cd61c(int param_1,undefined4 param_2,undefined4 param_3)
// просто записывает-обновляет координаты 
using t_onMoveToTile_3 = HRESULT(__fastcall*)(character* _this, int stub, int x, int y);
t_onMoveToTile_3 o_onMoveToTile_3 = nullptr;
HRESULT __fastcall onMoveToTile_3(character* _this, int stub, int x, int y)
{
//	LOG_ALWAYS(BUGTEST, "onMoveToTile_3()");

	HRESULT result = o_onMoveToTile_3(_this, stub, x, y);

	return result;
}

//void __thiscall FUN_006086c8(int param_1,int param_2,char param_3)
using t_onPreBattleEnd = HRESULT(__fastcall*)(battleDataS* _this, int stub, int param_2, char param_3);
t_onPreBattleEnd o_onPreBattleEnd = nullptr;
HRESULT __fastcall onPreBattleEnd(battleDataS* _this, int stub, int param_2, char param_3)
{
	LOG_ALWAYS(BUGTEST, "onPreBattleEnd()");
	return o_onPreBattleEnd(_this, stub, param_2, param_3);
}

//void __fastcall UndefinedFunction_00c3370c(int *param_1)   
using t_onMarriageOptionAccept = int(__fastcall*)(marriageOption* mo);
t_onMarriageOptionAccept o_onMarriageOptionAccept = nullptr;
int __fastcall onMarriageOptionAccept(marriageOption* mo)
{
	LOG_ALWAYS(BUGTEST, "onMarriageOptionAccept()");

	int result = o_onMarriageOptionAccept(mo);

	return result;
}
#endif // OTHER_TESTS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef FACTION_BUTTON_TEST
// banner при загрузке  param_4 == ID фракции 
//void __thiscall FUN_00869934(int param_1,undefined *param_2,int param_3,undefined4 param_4)
using t_FUN_00869934 = HRESULT(__fastcall*)(int _this, int stub, int param_2, int param_3, int param_4);
t_FUN_00869934 o_FUN_00869934 = nullptr;
HRESULT __fastcall FUN_00869934(int _this, int stub, int param_2, int param_3, int param_4)
{
	LOG_ALWAYS(BUGTEST, "FUN_00869934()");

	HRESULT result = o_FUN_00869934(_this, stub, param_2, param_3, param_4);

	return result;
}

//void __fastcall FUN_00d0bf1c(undefined4 param_1,int param_2)
using t_FUN_00d0bf1c = HRESULT(__fastcall*)(UNICODE_STRING**& param_1, int param_2);
t_FUN_00d0bf1c o_FUN_00d0bf1c = nullptr;
HRESULT __fastcall FUN_00d0bf1c(UNICODE_STRING**& param_1, int param_2)
{
	LOG_ALWAYS(BUGTEST, "FUN_00d0bf1c()");

	HRESULT result = o_FUN_00d0bf1c(param_1, param_2);

	return result;
}

struct fb
{
    int data[999]; // 86 - facID   
};
static fb* remember_fb;
//undefined4 * __thiscall FUN_00c3293c(undefined4 *param_1,undefined4 param_2,undefined4 *param_3)
using t_onSetFactionButton = fb*(__fastcall*)(fb* _this, int stub, int facID, coords* coords);
t_onSetFactionButton o_onSetFactionButton = nullptr;
fb* __fastcall onSetFactionButton(fb* _this, int stub, int facID, coords* coords)
{
	LOG_ALWAYS(BUGTEST, "onSetFactionButton()");
    remember_fb = _this;

    fb* result = o_onSetFactionButton(_this, stub, facID, coords);

	return result;
}

static DWORD remember_onFactionStartTurnNotify = 0;
//void __thiscall FUN_00c45134(int param_1,int param_2)
using t_onFactionStartTurnNotify = void(__fastcall*)(DWORD _this, int stub, factionStruct* faction);
t_onFactionStartTurnNotify o_onFactionStartTurnNotify = nullptr;
void __fastcall onFactionStartTurnNotify(DWORD _this, int stub, factionStruct* faction)
{
    //  helper_functions::callGameConsoleCommand("control", "romans_brutii");

    remember_onFactionStartTurnNotify = _this;

    o_onFactionStartTurnNotify(_this, stub, faction);

    LOG_ALWAYS(BUGTEST, "onFactionStartTurnNotify(" + string(faction->factSmDescr->facName) + ")");
}

//void __fastcall FUN_00c48a18(int param_1)
using t_FUN_00c48a18 = void(__fastcall*)(void* _this, int stub);
t_FUN_00c48a18 o_FUN_00c48a18 = nullptr;
void __fastcall FUN_00c48a18(void* _this, int stub)
{
    o_FUN_00c48a18(_this, stub);

    LOG_ALWAYS(BUGTEST, "FUN_00c48a18()");
}

//void __fastcall UndefinedFunction_00868790(int param_1)
using t_FUN_00868790 = void(__fastcall*)(void* _this, int stub);
t_FUN_00868790 o_FUN_00868790 = nullptr;
void __fastcall FUN_00868790(void* _this, int stub)
{
    o_FUN_00868790(_this, stub);

    LOG_ALWAYS(BUGTEST, "FUN_00868790()");
}
#endif // FACTION_BUTTON_TEST
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef FACTION_LIMIT_TESTS
/// FACTION LIMIT TESTS ///

EOP_FACTION eop_faction;

bool is_faction_limit_test = true;

//int FUN_008af7b4(int param_1)
using t_createFaction = factionStruct*(__cdecl*)(int factionID);
t_createFaction o_createFaction = nullptr;
factionStruct* __cdecl createFaction(int factionID)
{
    factionStruct* result = o_createFaction(factionID);

    LOG_ALWAYS(BUGTEST, "createFaction(factionID: " + to_string(factionID) + ", faction: " + string(result->factSmDescr->facName) + ")");

    return result;
}

struct factionDB // проверить это descr_sm_factions_list   
{
    // пу-пу-пу...   
};

//undefined4 FUN_008aba40(void)
using t_onReadDescrSmFactions = bool(__cdecl*)(factionDB* db);
t_onReadDescrSmFactions o_onReadDescrSmFactions = nullptr;
bool __cdecl onReadDescrSmFactions(factionDB* db)
{
    while (is_faction_limit_test && !IsDebuggerPresent())
    {
        Sleep(100);
    }

    LOG_ALWAYS(BUGTEST, "onReadDescrSmFactions()");

    // +1 при проверке при чтении descr_sm_factions.txt   
    //  | cmp eax, 15 |  008ac876 |    0|008AC878:15->16   
    uint8_t* oldLimit = reinterpret_cast<uint8_t*>(0x008AC878);
    uint8_t limit = *oldLimit + 1;
    const DWORD address = 0x008AC878;
    memory::Write(&limit, address, 1);
    
    bool result = o_onReadDescrSmFactions(db);

    // пока нужно обратно вернуть "счетчик сравнений" и максимальную численность DB к стандартному 21   
    int standard21 = 21;
    const DWORD facCount = 0x012ea29c;
    const DWORD checkCount = 0x012ea28c;
    memory::Write(&standard21, facCount, 1);
    memory::Write(&standard21, checkCount, 1);

    return result;
}

//int FUN_008af97c(int param_1)
using t_getFactionDescription = factionStratMapDescrS*(__cdecl*)(int facID);
t_getFactionDescription o_getFactionDescription = nullptr;
factionStratMapDescrS* __cdecl getFactionDescription(int facID)
{
    if (facID == 21)
    {
        LOG_ALWAYS(BUGTEST, "getFactionDescription(facID == 21)");
    //  facID = 1;
    }

    factionStratMapDescrS* result = o_getFactionDescription(facID);

    return result;
}

//undefined4 FUN_004dbd6c(void)
using t_getLocalizedName = UNICODE_STRING * *&(__fastcall*)(factionStruct* _this, int stub);
t_getLocalizedName o_getLocalizedName = nullptr;
UNICODE_STRING**& __fastcall onGetLocalizedName(factionStruct* _this, int stub)
{
    LOG_ALWAYS(BUGTEST, "onGetLocalizedName(" + string(_this->factSmDescr->facName) + ")");

//  кажись больше не нужно   
    if (_this->dipNum == 21)
    {
        const char* locName = "faction22";
        auto locNameUni = new UNICODE_STRING*;
        createUniString(locNameUni, locName);
        LOG_ALWAYS(BUGTEST, "onGetLocalizedName(" + string(locName) + ")");
        return locNameUni;
    }

    UNICODE_STRING**& result = o_getLocalizedName(_this, stub);

    return result;
}

//### - undefined4 * __thiscall FUN_00ecac30(undefined4 *param_1,undefined4 *param_2)
using t_onGetUniStringFromData = UNICODE_STRING**&(__fastcall*)(void* _this, int stub, UNICODE_STRING** p);
t_onGetUniStringFromData o_onGetUniStringFromData = nullptr;
UNICODE_STRING**& __fastcall onGetUniStringFromData(void* _this, int stub, UNICODE_STRING** p)
{
    if (p == 0)
    {
        UNICODE_STRING** uni = new UNICODE_STRING*;

        const char* locName = "faction22";
    //  createUniString(uni, locName);
        createUniString(p, locName);
    //  p = uni;
        LOG_ALWAYS(BUGTEST, "onGetUniStringFromData(" + uniToAnsi(p) + ")");

        return p;
    }

    UNICODE_STRING**& result = o_onGetUniStringFromData(_this, stub, p);

    return result;
}

//undefined4 FUN_00ece3c0(undefined4 param_1,int *param_2)
using t_FUN_00ece3c0 = UNICODE_STRING**&(__fastcall*)(UNICODE_STRING p, UNICODE_STRING p2, UNICODE_STRING p3, UNICODE_STRING p4);
t_FUN_00ece3c0 o_FUN_00ece3c0 = nullptr;
UNICODE_STRING**& __fastcall FUN_00ece3c0(UNICODE_STRING p, UNICODE_STRING p2, UNICODE_STRING p3, UNICODE_STRING p4)
{
    while (is_faction_limit_test && !IsDebuggerPresent())
    {
        Sleep(100);
    }

    UNICODE_STRING**& result = o_FUN_00ece3c0(p, p2, p3, p4);

    return result;
}


//int __fastcall FUN_005cd8bc(int *param_1)
using t_onCreateArmyInSettlement = stackStruct*(__fastcall*)(settlementStruct* sett);
t_onCreateArmyInSettlement o_onCreateArmyInSettlement = nullptr;
stackStruct* __fastcall onCreateArmyInSettlement(settlementStruct* sett)
{

    stackStruct* result = o_onCreateArmyInSettlement(sett);

    return result;
}

//void __thiscall FUN_004e9e40(int param_1,int param_2)
using t_onAttachRegion = void(__fastcall*)(factionStruct* _this, int stub, int regionID);
t_onAttachRegion o_onAttachRegion = nullptr;
void __fastcall onAttachRegion(factionStruct* _this, int stub, int regionID)
{
    if (!_this)
    {
        LOG_ALWAYS(BUGTEST, "onAttachRegion(if (_this == 0))");
//        auto reg = helper_functions::getRegionByID(regionID);
//    //  _this = reg->factionOwner;
//    //  _this = reg->settlement->faction;
//    //  _this = helper_functions::getGameDataAll()->campaignData->factionsSortedByDescrStrat[0];
//        _this = createFaction(21);
        return;
    }

    o_onAttachRegion(_this, stub, regionID);

    LOG_ALWAYS(BUGTEST, "onAttachRegion(" + to_string(regionID) + ")");
}

//void __thiscall FUN_00497910(int param_1,int param_2,int param_3)
using t_onAttachRegionFaction = void(__fastcall*)(stratMap* _this, int stub, int regionID, factionStruct* faction);
t_onAttachRegionFaction o_onAttachRegionFaction = nullptr;
void __fastcall onAttachRegionFaction(stratMap* _this, int stub, int regionID, factionStruct* faction)
{
    if (!faction)
    {
        LOG_ALWAYS(BUGTEST, "onAttachRegionFaction(if (!factionStruct))");
        faction = eop_faction.getFactionByID(21);
        return;
    }

    o_onAttachRegionFaction(_this, stub, regionID, faction);

    LOG_ALWAYS(BUGTEST, "onAttachRegionFaction()");
}

//int FUN_0040dec0(uint param_1)
using t_onGetInstance = factionStruct*(__cdecl*)(factionStruct* faction);
t_onGetInstance o_onGetInstance = nullptr;
factionStruct* __cdecl onGetInstance(factionStruct* faction)
{
    if (!faction)
    {
        LOG_ALWAYS(BUGTEST, "onGetInstance(if (!factionStruct))");
    }

    factionStruct* result = o_onGetInstance(faction);

    if (result == nullptr)
    {
    //  result = helper_functions::getGameDataAll()->campaignData->factionsSortedByID[1];
    //  result = createFactionTEST(21);
        result = eop_faction.getFactionByID(21);

        LOG_ALWAYS(BUGTEST, "onGetInstance(" + string(result->factSmDescr->facName) + ")");
    }

    return result;
}

//undefined4 __thiscall FUN_00455b84(int param_1,int param_2)
using t_onGetFactionByID = factionStruct*(__fastcall*)(campaign* _this, int stub, int factionID);
t_onGetFactionByID o_onGetFactionByID = nullptr;
factionStruct* __fastcall onGetFactionByID(campaign* _this, int stub, int factionID)
{
//  LOG_ALWAYS(BUGTEST, "onGetFactionByID()");

    if (factionID >= 21)
    {
    //  result = helper_functions::getGameDataAll()->campaignData->factionsSortedByID[1];
    //  factionStruct* result = createFactionTEST(21);
        factionStruct* result = eop_faction.getFactionByID(21);
    //  LOG_ALWAYS(BUGTEST, "onGetFactionByID(" + string(result->factSmDescr->facName) + ")");
        return result;
    }



    factionStruct* result = o_onGetFactionByID(_this, stub, factionID);

    return result;
}

static struct factionDiplomacyTest
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

static struct dipClassTest
{
    struct factionDiplomacyTest diplomaticStandings[21][21];
};

//byte __thiscall FUN_005b2f30(int param_1,int param_2,int param_3)
using t_onHasTradeRights = bool(__fastcall*)(dipClassTest* _this, int stub, int aID, int bID);
t_onHasTradeRights o_onHasTradeRights = nullptr;
bool __fastcall onHasTradeRights(dipClassTest* _this, int stub, int aID, int bID)
{
    LOG_ALWAYS(BUGTEST, "onHasTradeRights()");

    if (aID >= 21 || bID >= 21)
    {
        return false;
    }


    bool result = o_onHasTradeRights(_this, stub, aID, bID);

    return result;
}

bool is_SaveNewFaction = false;
int number_of_triggered = 0;
//undefined4 __thiscall FUN_004f0b24(int param_1,undefined4 param_2)
using t_onSaveFaction = bool(__fastcall*)(factionStruct* _this, int stub, int file);
t_onSaveFaction o_onSaveFaction = nullptr;
bool __fastcall onSaveFaction(factionStruct* _this, int stub, int file)
{
    LOG_ALWAYS(BUGTEST, "onSaveFaction(" + string(_this->factSmDescr->facName) + ")");

    bool result = o_onSaveFaction(_this, stub, file);
    number_of_triggered++;

//    if (number_of_triggered == helper_functions::getGameDataAll()->campaignData->factionCount)
//    {
//        bool test_result = onSaveFaction(eop_faction.getFactionByID(21), stub, file);
//        number_of_triggered = 0;
//        return test_result;
//    }


//    if (is_SaveNewFaction && _this->dipNum == 20)
//    {
//        factionStruct* new_faction = eop_faction.getFactionByID(21);
//        new_faction->aiFaction = helper_functions::getGameDataAll()->campaignData->factionsSortedByID[19]->aiFaction;
//        new_faction->aiFaction->faction = new_faction;
//        bool test_result = onSaveFaction(new_faction, stub, file);
//        LOG_ALWAYS(BUGTEST, "onSaveFaction(is_SaveNewFaction && _this->dipNum == 20)");
//    }

    return result;
}

//undefined4 __thiscall FUN_004ee4ec(int param_1,int *param_2)
using t_onLoadFaction = bool(__fastcall*)(factionStruct* _this, int stub, int file);
t_onLoadFaction o_onLoadFaction = nullptr;
bool __fastcall onLoadFaction(factionStruct* _this, int stub, int file)
{
    LOG_ALWAYS(BUGTEST, "onLoadFaction(" + string(_this->factSmDescr->facName) + ")");

    bool result = o_onLoadFaction(_this, stub, file);
    number_of_triggered++;

//    if (number_of_triggered == helper_functions::getGameDataAll()->campaignData->factionCount)
//    {
//        auto fac = eop_faction.getFactionByID(21);
//    //  fac->dipNum = 1;
//        bool test_result = onLoadFaction(fac, stub, file);
//        number_of_triggered = 0;
//        return test_result;
//    }


//    if (is_SaveNewFaction && _this->dipNum == 20)
//    {
//        factionStruct* new_faction = eop_faction.getFactionByID(21);
//        bool test_result = o_onLoadFaction(new_faction, stub, file);
//        LOG_ALWAYS(BUGTEST, "onLoadFaction(is_SaveNewFaction && _this->dipNum == 20)");
//    }

    return result;
}


void new_events::test_onCampaignMapLoaded(campaign* _this, int stub, int file)
{
    if (is_SaveNewFaction)
    {
        factionStruct* new_faction = eop_faction.getFactionByID(21);
        bool test_result = o_onLoadFaction(new_faction, stub, file);
        LOG_ALWAYS(BUGTEST, "onLoadFaction(is_SaveNewFaction && _this->dipNum == 20)");
    }
}


//undefined4 __thiscall FUN_00457754(int param_1,undefined4 param_2)
using t_onCampaignMapSaved = bool(__fastcall*)(campaign* _this, int stub, int file);
t_onCampaignMapSaved o_onCampaignMapSaved = nullptr;
bool __fastcall onCampaignMapSaved(campaign* _this, int stub, int file)
{
    LOG_ALWAYS(BUGTEST, "onCampaignMapSaved()");

    bool result = o_onCampaignMapSaved(_this, stub, file);

    if (is_SaveNewFaction)
    {
        factionStruct* new_faction = eop_faction.getFactionByID(21);
        new_faction->aiFaction = _this->factionsSortedByID[19]->aiFaction;
        new_faction->aiFaction->faction = new_faction;
        bool test_result = onSaveFaction(new_faction, stub, file);
        LOG_ALWAYS(BUGTEST, "onSaveFaction(is_SaveNewFaction && _this->dipNum == 20)");
    }

    return result;
}

//undefined4 __fastcall UndefinedFunction_00591bf8(int param_1)
using t_FUN_00591bf8 = int(__fastcall*)(character* _this, int stub);
t_FUN_00591bf8 o_FUN_00591bf8 = nullptr;
int __fastcall FUN_00591bf8(character* _this, int stub)
{
    LOG_ALWAYS(BUGTEST, "FUN_00591bf8()");

    int result = o_FUN_00591bf8(_this, stub);


    return result;
}

// название фракции под символом фракции при переходе хода   
//undefined4 __thiscall FUN_00cc7b78(int param_1,undefined4 param_2,int param_3,int param_4)
using t_FUN_00cc7b78 = UNICODE_STRING**&(__fastcall*)(void* _this, int stub, int param_2, int param_3, UNICODE_STRING**& param_4);
t_FUN_00cc7b78 o_FUN_00cc7b78 = nullptr;
UNICODE_STRING**& __fastcall FUN_00cc7b78(void* _this, int stub, int param_2, int param_3, UNICODE_STRING**& param_4)
{
    LOG_ALWAYS(BUGTEST, "FUN_00cc7b78()");

    if (eop_faction.is_new_faction_turn)
    {
        eop_faction.is_new_faction_turn = false;

        UNICODE_STRING** uni = new UNICODE_STRING*;
        const char* locName = "faction22";
        createUniString(param_4, locName);

        LOG_ALWAYS(BUGTEST, "FUN_00cc7b78(faction22)");
    }

    UNICODE_STRING** result = o_FUN_00cc7b78(_this, stub, param_2, param_3, param_4);

    return result;
}

// я не помню что это, но что-то связанное с отображением даты   
//void __fastcall UndefinedFunction_00c488c8(int param_1)
using t_FUN_00c488c8 = void(__fastcall*)(DWORD param_1);
t_FUN_00c488c8 o_FUN_00c488c8 = nullptr;
void __fastcall FUN_00c488c8(DWORD param_1)
{
//    character* v1 = reinterpret_cast<character*>(param_1);
//    namedCharacter* v2 = reinterpret_cast<namedCharacter*>(param_1);
//    coords* v3 = reinterpret_cast<coords*>(param_1);
//    const char* v4 = reinterpret_cast<const char*>(param_1);
//    campaign* v6 = reinterpret_cast<campaign*>(param_1);
//    stratMap* v8 = reinterpret_cast<stratMap*>(param_1);
//    oneTile* v9 = reinterpret_cast<oneTile*>(param_1);

    if (eop_faction.is_new_faction_turn 
        || qa.campaignStruct->getLocalFaction() == eop_faction.getFactionByID(21)
        || helper_functions::getGameDataAll()->campaignData->currentFactionTurn == eop_faction.getFactionByID(21)
    )
    {
        return;
    }
    else
    {
        return o_FUN_00c488c8(param_1);
    }
//  LOG_ALWAYS(BUGTEST, "FUN_00c488c8(" + to_string(result) + ")");
//  return -270;
}

//void __fastcall FUN_004f4864(int param_1)
using t_addFactionSettlementsForRender = void(__fastcall*)(factionStruct* _this, int stub);
t_addFactionSettlementsForRender o_addFactionSettlementsForRender = nullptr;
void __fastcall addFactionSettlementsForRender(factionStruct* _this, int stub)
{
//  LOG_ALWAYS(BUGTEST, "addFactionSettlementsForRender(" + string(_this->factSmDescr->facName) + ")");

    o_addFactionSettlementsForRender(_this, stub);

    //нужно сделать отрисовку в onDisplayDraw - см. файл Q:\revers\рим1\важно\faction_limit.cpp   
    if (_this->dipNum == 20)
    {
        factionStruct* new_faction = eop_faction.getFactionByID(21);
        addFactionSettlementsForRender(new_faction, stub);

        //void __fastcall FUN_004f43b4(int param_1)
        GAME_FUNC(void(__thiscall*)(factionStruct* _this), 0x004f43b4)(new_faction); //addFactionCharactersForRender 
    }
}

enum fogOfWar
{
    NO_SEEN,
    WAS_SEEN,
    SEEN,
    MANY_TIMES_SEEN
};
bool seen_all = false;
//undefined1 FUN_004c6df8(int param_1, int param_2)
using t_getPlayerObjectSeen = fogOfWar(__fastcall*)(void* _this, int stub, int x, int y);
t_getPlayerObjectSeen o_getPlayerObjectSeen = nullptr;
fogOfWar __fastcall getPlayerObjectSeen(void* _this, int stub, int x, int y)
{
    if (seen_all)
        return SEEN;

    fogOfWar result = o_getPlayerObjectSeen(_this, stub, x, y);
 
    return result;
}

//undefined4 FUN_008b13a4(undefined4 param_1)
using t_onReadDescrRegions = bool(__fastcall*)(void* _this, int stub, UNICODE_STRING**& f, int param_3);
t_onReadDescrRegions o_onReadDescrRegions = nullptr;
bool __fastcall onReadDescrRegions(void* _this, int stub, UNICODE_STRING**& f, int param_3)
{
    LOG_ALWAYS(BUGTEST, "onReadDescrRegions()");

    string str1 = uniToAnsi(f);

    bool result = o_onReadDescrRegions(_this, stub, f, param_3);

    return result;
}

//undefined4 __fastcall FUN_008bb25c(int param_1)
using t_FUN_008bb25c = int(__fastcall*)(void* _this, int stub);
t_FUN_008bb25c o_FUN_008bb25c = nullptr;
int __fastcall FUN_008bb25c(void* _this, int stub)
{
    return o_FUN_008bb25c(_this, stub);;
}

//void FUN_008bb1fc(void)
using t_getRandomNameIndices = int(__cdecl*)(void* rand, int facID, bool male, int& name, int& surname);
t_getRandomNameIndices o_getRandomNameIndices = nullptr;
int __cdecl getRandomNameIndices(void* rand, int facID, bool male, int& name, int& surname)
{
    if (facID >= 21)
    {
        facID = 1;
        LOG_ALWAYS(BUGTEST, "getRandomNameIndices()");
    }

    int result = o_getRandomNameIndices(rand, facID, male, name, surname);

    return result;
}

enum nameType
{
    CHARACTER,
    WOMEN,
    SURNAME,
};

//undefined4 FUN_008bb050(undefined4 param_1,undefined4 param_2,int param_3)
using t_getRandomName = const char*(__cdecl*)(nameType type, int facID, int index);
t_getRandomName o_getRandomName = nullptr;
const char* __cdecl getRandomName(nameType type, int facID, int index)
{
    if (facID >= 21)
    {
    //  factionStruct* new_faction = eop_faction.getFactionByID(facID);
    //  new_faction->dipNum = 1;
        facID = 1;
        LOG_ALWAYS(BUGTEST, "getRandomName()");
    }

    const char* result = o_getRandomName(type, facID, index);

    return result;
}
															
struct descrCharacter
{
    characterType type;
    nameAndHash model_id;
    int model;
    nameAndHash card;
    nameAndHash portrait;
    nameAndHash card_rebel;
    nameAndHash portrait_rebel;
    int d1;
    int d2;
};

// undefined4* __thiscall FUN_0059162c(undefined4* param_1, int param_2, int* param_3)
using t_characterConstructor = character*(__fastcall*)(character* _this, int stub, namedCharacter* param_1, descrCharacter* param_2);
t_characterConstructor o_characterConstructor = nullptr;
character* __fastcall characterConstructor(character* _this, int stub, namedCharacter* param_1, descrCharacter* param_2)
{
    LOG_ALWAYS(BUGTEST, "characterConstructor()");

    character* result = o_characterConstructor(_this, stub, param_1, param_2);

    return result;
}

//int __fastcall FUN_00890730(undefined4 param_1,int param_2)
using t_FUN_00890730 = character*(__cdecl*)(characterType charType, factionStruct* faction, int age, const char* name, const char* surname, int originalFactionId);
t_FUN_00890730 o_FUN_00890730 = nullptr;
character* __cdecl FUN_00890730(characterType charType, factionStruct* faction, int age, const char* name, const char* surname, int originalFactionId)
{
    LOG_ALWAYS(BUGTEST, "FUN_00890730()");

//    if (faction->dipNum >= 21)
//        faction->dipNum = 1;


    character* result = o_FUN_00890730(charType, faction, age, name, surname, originalFactionId);

    return result;
}

// int __fastcall FUN_00890730(undefined4 param_1,int param_2)   
//  using t_FUN_00890730 = HRESULT(__fastcall*)(int age, factionStruct* faction, int charType, int param_1, int param_2, const char* name, const char* surname, int originalFactionId, const char* portrait, int x, int y);
//  t_FUN_00890730 o_FUN_00890730 = nullptr;
//  HRESULT __fastcall FUN_00890730(int age, factionStruct* faction, int charType, int param_1, int param_2, const char* name, const char* surname, int originalFactionId, const char* portrait, int x, int y)
//  {
//      LOG_ALWAYS(BUGTEST, "FUN_00890730()");
//  
//      //	auto s0 = bFile->stub2[0];
//      //	auto s1 = bFile->stub2[1];
//      //	string fileName = uniStringToStr(bFile->file);
//  
//      HRESULT result = o_FUN_00890730(age, faction, charType, param_1, param_2, name, surname, originalFactionId, portrait, x, y);
//  
//      return result;
//  }

//undefined4 __fastcall UndefinedFunction_005a2094(int param_1)
using t_getCharacterFactionID = int(__fastcall*)(character* c);
t_getCharacterFactionID o_getCharacterFactionID = nullptr;
int __fastcall getCharacterFactionID(character* c)
{
    if (c->genChar->faction->dipNum >= 21)
        c->genChar->faction = helper_functions::getFactionByName("slave");
        return 1;


    int result = o_getCharacterFactionID(c);

    return result;
}

//void __thiscall FUN_004a6330(int *param_1,int *param_2,undefined4 *param_3,float param_4)
using t_FUN_004a6330 = int(__fastcall*)(int param_1, int stub, int* param_2, undefined4* param_3, float param_4);
t_FUN_004a6330 o_FUN_004a6330 = nullptr;
int __fastcall FUN_004a6330(int param_1, int stub, int* param_2, undefined4* param_3, float param_4)
{
    if (param_1 == 0)
        return 0;


    int result = o_FUN_004a6330(param_1, stub, param_2, param_3, param_4);

    return result;
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


factionStruct* createFactionTEST(int facID)
{
    factionStruct* new_faction = createFaction(facID);
//  new_faction->deadStatus = 0; // мы живы   
//  new_faction->aiFaction = helper_functions::getGameDataAll()->campaignData->factionsSortedByDescrStrat[0]->aiFaction;
    eop_faction.m_faction[facID] = new_faction;
    return new_faction;
}

factionStruct* EOP_FACTION::getFactionByID(int facID) 
{
    auto fac = m_faction[facID];
    if (!fac)
    {
        fac = createFactionTEST(facID);
    }
    return fac;
}

factionStruct* createNewFaction(const char* name, int facID)
{
//getFactionDescription(int param_1)
//factionStratMapDescrS* factSmDescr = GAME_FUNC(factionStratMapDescrS*(__thiscall*)(DWORD _this, int facID), 0x008af97c)(0x00193708, 0); //    
//factionStratMapDescrS* factSmDescr = GAME_FUNC(factionStratMapDescrS*(__thiscall*)(int facID), 0x008af97c)(0); //    

//  // задаем имя и ID   
//  const char* name = "faction22";
//  int facID = 21;


    // лучше делать это при "оригинальном" чтении descr_sm_factions.txt 
#ifdef ReadDescrSmFactions
    //---
    // +1 при проверке при чтении descr_sm_factions.txt   
    //  | cmp eax, 15 |  008ac876 |    0|008AC878:15->16   
    uint8_t* oldLimit = reinterpret_cast<uint8_t*>(0x008AC878);
    uint8_t limit = *oldLimit + 1;
    const DWORD address = 0x008AC878;
    memory::Write(&limit, address, 1);
    
    
    // вновь читаем файл descr_sm_factions.txt и создаем DB нашей фракции(в будущем нужно будет подменять файл на наш с новой фракцией)   
    factionDB* dbFac = reinterpret_cast<factionDB*>(0x00193708);
    onReadDescrSmFactions(dbFac);


    // наверно это не нужно, но я сделал на всякий случай - просто приравниваю "счетчик" сравнений к максимальной численности DB   
    int* facCount = reinterpret_cast<int*>(0x012ea28c);
    const DWORD checkCount = 0x012ea29c;
    memory::Write(facCount, checkCount, 1);
#endif // ReadDescrSmFactions

    // просто для отладки - посмотреть что тут у нас получилось   
    factionStratMapDescrS* factSmDescrNEW = getFactionDescription(facID);
    //---
    
    
    
    //---
    // создаем фракцию. createFaction вызывает конструктор фракции и заполняет поле factionDB нашим DB выше   
    factionStruct* new_faction = createFaction(facID);
    new_faction->deadStatus = 0; // мы живы   
    eop_faction.m_faction[facID] = new_faction;
    //---


    // это было нужно, пока не научился создавать DB выше. Потом удалю   
//  factionStruct* roman = qa.gDataAll->campaignData->factionsSortedByID[1];

//  factionStratMapDescrS* factSmDescrNEW = new factionStratMapDescrS;
//  factSmDescrNEW = getFactionDescription(0);
//  new_faction->factSmDescr = factSmDescrNEW;

//  new_faction->factSmDescr = roman->factSmDescr;
//  new_faction->factSmDescr->facName = roman->factSmDescr->facName;

/*
    helper_functions::setHashedString(&new_faction->factSmDescr->facName, name);
    new_faction->factSmDescr->id = facID;
    
    new_faction->factSmDescr->shadowedByID                    = roman->factSmDescr->shadowedByID;
    new_faction->factSmDescr->shadowedBy                      = roman->factSmDescr->shadowedBy;
                                                    
    new_faction->factSmDescr->shadowingID                     = roman->factSmDescr->shadowingID;
    new_faction->factSmDescr->shadowing                       = roman->factSmDescr->shadowing;
                                                    
    new_faction->factSmDescr->spawnsOnRevoltID                = roman->factSmDescr->spawnsOnRevoltID;
    new_faction->factSmDescr->spawnsOnRevolt                  = roman->factSmDescr->spawnsOnRevolt;
                                                    
    new_faction->factSmDescr->otherId                         = roman->factSmDescr->otherId;
                                                    
    new_faction->factSmDescr->culture                         = roman->factSmDescr->culture;
    new_faction->factSmDescr->symbol                          = roman->factSmDescr->symbol;
    new_faction->factSmDescr->symbolPath                      = roman->factSmDescr->symbolPath;
    new_faction->factSmDescr->symbolPathHash                  = roman->factSmDescr->symbolPathHash;
    new_faction->factSmDescr->rebel_symbol                    = roman->factSmDescr->rebel_symbol;
    new_faction->factSmDescr->rebel_symbolPath                = roman->factSmDescr->rebel_symbolPath;
    new_faction->factSmDescr->rebel_symbolPathHash            = roman->factSmDescr->rebel_symbolPathHash;
                                                    
    new_faction->factSmDescr->loading_logo                    = roman->factSmDescr->loading_logo;
    new_faction->factSmDescr->loading_logoHash                = roman->factSmDescr->loading_logoHash;
    new_faction->factSmDescr->primary_colour_blue             = roman->factSmDescr->primary_colour_blue;
    new_faction->factSmDescr->primary_colour_green            = roman->factSmDescr->primary_colour_green;
    new_faction->factSmDescr->primary_colour_red              = roman->factSmDescr->primary_colour_red;
    new_faction->factSmDescr->secondary_colour_blue           = roman->factSmDescr->secondary_colour_blue;
    new_faction->factSmDescr->secondary_colour_green          = roman->factSmDescr->secondary_colour_green;
    new_faction->factSmDescr->secondary_colour_red            = roman->factSmDescr->secondary_colour_red;
                                                    
    new_faction->factSmDescr->triumph_value                   = roman->factSmDescr->triumph_value;
    new_faction->factSmDescr->standard_index                  = roman->factSmDescr->standard_index;
    new_faction->factSmDescr->logo_index                      = roman->factSmDescr->logo_index;
    new_faction->factSmDescr->small_logo_index                = roman->factSmDescr->small_logo_index;
    new_faction->factSmDescr->movieIntro                      = roman->factSmDescr->movieIntro;
    new_faction->factSmDescr->movieVictory                    = roman->factSmDescr->movieVictory;
    new_faction->factSmDescr->movieDefeat                     = roman->factSmDescr->movieDefeat;
    new_faction->factSmDescr->movieDeath                      = roman->factSmDescr->movieDeath;
    new_faction->factSmDescr->roman                           = roman->factSmDescr->roman;
    new_faction->factSmDescr->barbarian                       = roman->factSmDescr->barbarian;
    new_faction->factSmDescr->eastern                         = roman->factSmDescr->eastern;
    new_faction->factSmDescr->slave                           = roman->factSmDescr->slave;
    new_faction->factSmDescr->hordeUnitNames                  = roman->factSmDescr->hordeUnitNames;
    new_faction->factSmDescr->hordeUnitNamesSize              = roman->factSmDescr->hordeUnitNamesSize;
    new_faction->factSmDescr->hordeUnitNamesCount             = roman->factSmDescr->hordeUnitNamesCount;
    new_faction->factSmDescr->hordeMinUnits                   = roman->factSmDescr->hordeMinUnits;
    new_faction->factSmDescr->hordeMaxUnits                   = roman->factSmDescr->hordeMaxUnits;
    new_faction->factSmDescr->reductionPerHorde               = roman->factSmDescr->reductionPerHorde;
    new_faction->factSmDescr->hordeUnitPerSettlementPop       = roman->factSmDescr->hordeUnitPerSettlementPop;
    new_faction->factSmDescr->hordeMinNamedCharacters         = roman->factSmDescr->hordeMinNamedCharacters;
    new_faction->factSmDescr->hordeMaxPercentArmyStack        = roman->factSmDescr->hordeMaxPercentArmyStack;
    new_faction->factSmDescr->N00008DBD                       = roman->factSmDescr->N00008DBD;
    new_faction->factSmDescr->N00008DBE                       = roman->factSmDescr->N00008DBE;
    new_faction->factSmDescr->N00008DBF                       = roman->factSmDescr->N00008DBF;
    new_faction->factSmDescr->customBattleAvailability        = roman->factSmDescr->customBattleAvailability;
                                                    
    new_faction->factSmDescr->canHorde                        = roman->factSmDescr->canHorde;
    new_faction->factSmDescr->canSap                          = roman->factSmDescr->canSap;
                                                    
    new_faction->factSmDescr->prefersNavalInvasions           = roman->factSmDescr->prefersNavalInvasions;
*/

    //---
    // устанавливаем dipNum в пределах лимита, пока это нужно чтоб создавать персонажей, поселения и т.п.   
//    new_faction->dipNum = 1;
    
    
    // что-то тут создаем, тестируем, наблюдаем   
//  character* new_character = new_events::createCharacter(DIPLOMAT, new_faction, 17, "Amulius", "Acilius", facID, "fernando", qa.xLocCoord, qa.yLocCoord);
//  character* new_character = new_events::onCharacterCreated(DIPLOMAT, new_faction, 17, "Amulius", "Acilius", facID, "fernando", qa.xLocCoord + 2, qa.yLocCoord);

    string nameS = "eop_sett_" + to_string(qa.xLocCoord) + "_" + to_string(qa.yLocCoord);
    string locName = "New Settlement " + to_string(EOP_SETTLEMENTS.m_minor_settlement_count + 1);
    settlementStruct* new_settlement = eop_settlements::addSettlements(qa.xLocCoord, qa.yLocCoord, nameS.c_str(), locName.c_str(), new_faction);
    //---

    //0x005cd8bc
//  stackStruct* army = ononCreateArmyInSettlement(new_settlement);
    stackStruct* army = new_settlement->createArmyInSettlement();

    regionStruct* region = helper_functions::getRegionByID(army->regionID);
    unitDb* db = reinterpret_cast<unitDb*>(0x013006c0);
    unit* un = new_events::onCreateUnit2(db, 0, region, 100, new_faction->dipNum, 0, 210);
    new_events::onGiveUnitToArmy(army, 0, un, nullptr);
    //---


    // устанавливаем обратно на ID   
//    new_faction->dipNum = facID;
//    new_faction->factSmDescr->id = facID;

//  new_settlement->factionID = new_faction->dipNum;
//  //new_settlement->stats.faction = new_faction;
//  new_settlement->subFactionID = new_faction->dipNum;
//  new_settlement->faction_creator = new_faction->dipNum;



    string locNameStr = "no_name";
    UNICODE_STRING**& locNameUni = new_faction->getLocalizedUnicodeName();
    if (locNameUni)
    {
        locNameStr = uniStringToStr(locNameUni);
    }
    LOG_ALWAYS(BUGTEST, "createNewFaction(" + string(name) + ", " + to_string(facID) + ", " + locNameStr + ")");


    // понимаем, что это всё хрень   


    return new_faction;
}
#endif // FACTION_LIMIT_TESTS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ФИКС ДЛЯ ХОТ-СИТ КАМПАНИИ - непонятный вылет при выгрузке карты кампании.   
//void __thiscall FUN_004a9634(int param_1, int param_2, char param_3)
using t_FUN_004a9634 = int(__fastcall*)(int param_1, int stub, int param_2, char param_3);
t_FUN_004a9634 o_FUN_004a9634 = nullptr;
int __fastcall FUN_004a9634(int param_1, int stub, int param_2, char param_3)
{
    if (param_1 == 0)
    {
        LOG_REMINDER("FUN_004a9634(ФИКС ДЛЯ ХОТ-СИТ КАМПАНИИ)");
        return 0;
    }


    int result = o_FUN_004a9634(param_1, stub, param_2, param_3);

    return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

stratMapCursor* gameCursor = NULL;
void new_events::testGameEvents()
{
    LOG_ALWAYS(RELEASE, "testGameEvents()");

#ifdef _DEBUG
    LOG_REMINDER("!!! eduFormation для стим версии!!!");
#endif // _DEBUG

    if (!gameCursor && offsets.stratMapCursor)
	{
		gameCursor = reinterpret_cast<stratMapCursor*>(offsets.stratMapCursor);
	}

    if (startSettings.ancLimit != 8 && startSettings.ancLimit >= 1 && startSettings.ancLimit <= 127)
    {
        new_events::setAncLimit(startSettings.ancLimit);
    }



#ifdef OTHER_TESTS
//	o_game_begin_scene = (t_game_begin_scene)offsets.game_begin_scene;
//	DETOUR_ATTACH(&(PVOID&)o_game_begin_scene, game_begin_scene);

//	o_game_end_scene = (t_game_end_scene)offsets.game_end_scene;
//	DETOUR_ATTACH(&(PVOID&)o_game_end_scene, game_end_scene);

	o_onCreateUniString = (t_onCreateUniString)offsets.onCreateUniString;
	DETOUR_ATTACH(&(PVOID&)o_onCreateUniString, onCreateUniString);

	o_onCreateUniStringFromSharedTxtFile = (t_onCreateUniStringFromSharedTxtFile)offsets.onCreateUniStringFromSharedTxtFile;
	DETOUR_ATTACH(&(PVOID&)o_onCreateUniStringFromSharedTxtFile, onCreateUniStringFromSharedTxtFile);

	o_onPreBattleEnd = (t_onPreBattleEnd)offsets.onPreBattleEnd;
	DETOUR_ATTACH(&(PVOID&)o_onPreBattleEnd, onPreBattleEnd);

	o_onMoveToTile = (t_onMoveToTile)offsets.onMoveToTile;
	DETOUR_ATTACH(&(PVOID&)o_onMoveToTile, onMoveToTile);

	o_onMoveToTile_2 = (t_onMoveToTile_2)offsets.onMoveToTile_2;
	DETOUR_ATTACH(&(PVOID&)o_onMoveToTile_2, onMoveToTile_2);

	o_onMoveToTile_3 = (t_onMoveToTile_3)offsets.onMoveToTile_3;
	DETOUR_ATTACH(&(PVOID&)o_onMoveToTile_3, onMoveToTile_3);

	o_classCreatorNEW = (t_classCreatorNEW)offsets.classCreatorNEW;
	DETOUR_ATTACH(&(PVOID&)o_classCreatorNEW, classCreatorNEW);

    o_onSetPopulation = (t_onSetPopulation)offsets.setPopulation;
    DETOUR_ATTACH(&(PVOID&)o_onSetPopulation, onSetPopulation);

	o_onUnitRender = (t_onUnitRender)offsets.onUnitRender;
	DETOUR_ATTACH(&(PVOID&)o_onUnitRender, onUnitRender);

	o_onMarriageOptionAccept = (t_onMarriageOptionAccept)offsets.onMarriageOptionAccept;
	DETOUR_ATTACH(&(PVOID&)o_onMarriageOptionAccept, onMarriageOptionAccept);

	o_onEventTrigger = (t_onEventTrigger)offsets.onEventTrigger;
	DETOUR_ATTACH(&(PVOID&)o_onEventTrigger, onEventTrigger);
#endif // OTHER_TESTS


#ifdef FACTION_LIMIT_TESTS
    o_createFaction = (t_createFaction)offsets.createFaction;
	DETOUR_ATTACH(&(PVOID&)o_createFaction, createFaction);
  
  	o_onReadDescrSmFactions = (t_onReadDescrSmFactions)offsets.onReadDescrSmFactions;
	DETOUR_ATTACH(&(PVOID&)o_onReadDescrSmFactions, onReadDescrSmFactions);
  
   	o_onGetUniStringFromData = (t_onGetUniStringFromData)offsets.onGetUniStringFromData;
	DETOUR_ATTACH(&(PVOID&)o_onGetUniStringFromData, onGetUniStringFromData);
  
//  o_FUN_00ece3c0 = (t_FUN_00ece3c0)offsets.FUN_00ece3c0;
//	DETOUR_ATTACH(&(PVOID&)o_FUN_00ece3c0, FUN_00ece3c0);
  
    o_onAttachRegion = (t_onAttachRegion)offsets.onAttachRegion;
	DETOUR_ATTACH(&(PVOID&)o_onAttachRegion, onAttachRegion);
  
    o_onAttachRegionFaction = (t_onAttachRegionFaction)offsets.onAttachRegionFaction;
	DETOUR_ATTACH(&(PVOID&)o_onAttachRegionFaction, onAttachRegionFaction);
  
    o_onGetInstance = (t_onGetInstance)offsets.onGetInstance;
	DETOUR_ATTACH(&(PVOID&)o_onGetInstance, onGetInstance);
  
    o_onGetFactionByID = (t_onGetFactionByID)offsets.onGetFactionByID;
	DETOUR_ATTACH(&(PVOID&)o_onGetFactionByID, onGetFactionByID);
  
    o_onHasTradeRights = (t_onHasTradeRights)offsets.onHasTradeRights;
	DETOUR_ATTACH(&(PVOID&)o_onHasTradeRights, onHasTradeRights);
  
    o_onCampaignMapSaved = (t_onCampaignMapSaved)offsets.onCampaignMapSaved;
	DETOUR_ATTACH(&(PVOID&)o_onCampaignMapSaved, onCampaignMapSaved);
  
    o_onSaveFaction = (t_onSaveFaction)offsets.onSaveFaction;
	DETOUR_ATTACH(&(PVOID&)o_onSaveFaction, onSaveFaction);
  
    o_onLoadFaction = (t_onLoadFaction)offsets.onLoadFaction;
	DETOUR_ATTACH(&(PVOID&)o_onLoadFaction, onLoadFaction);
  
//  o_FUN_00591bf8 = (t_FUN_00591bf8)offsets.FUN_00591bf8;
//	DETOUR_ATTACH(&(PVOID&)o_FUN_00591bf8, FUN_00591bf8);
  
    o_FUN_00cc7b78 = (t_FUN_00cc7b78)offsets.FUN_00cc7b78;
	DETOUR_ATTACH(&(PVOID&)o_FUN_00cc7b78, FUN_00cc7b78);
  
    o_FUN_00c488c8 = (t_FUN_00c488c8)offsets.FUN_00c488c8;
	DETOUR_ATTACH(&(PVOID&)o_FUN_00c488c8, FUN_00c488c8);
  
 	o_getFactionDescription = (t_getFactionDescription)offsets.getFactionDescription;
	DETOUR_ATTACH(&(PVOID&)o_getFactionDescription, getFactionDescription);
  
   	o_getLocalizedName = (t_getLocalizedName)offsets.onGetLocalizedName;
   	DETOUR_ATTACH(&(PVOID&)o_getLocalizedName, onGetLocalizedName);

    o_onCreateArmyInSettlement = (t_onCreateArmyInSettlement)offsets.onCreateArmyInSettlement;
    DETOUR_ATTACH(&(PVOID&)o_onCreateArmyInSettlement, onCreateArmyInSettlement);

    o_addFactionSettlementsForRender = (t_addFactionSettlementsForRender)offsets.addFactionSettlementsForRender;
    DETOUR_ATTACH(&(PVOID&)o_addFactionSettlementsForRender, addFactionSettlementsForRender);

    o_getPlayerObjectSeen = (t_getPlayerObjectSeen)offsets.getPlayerObjectSeen;
    DETOUR_ATTACH(&(PVOID&)o_getPlayerObjectSeen, getPlayerObjectSeen);

//  o_FUN_008bb25c = (t_FUN_008bb25c)offsets.FUN_008bb25c;
//  DETOUR_ATTACH(&(PVOID&)o_FUN_008bb25c, FUN_008bb25c);

    o_getRandomNameIndices = (t_getRandomNameIndices)offsets.getRandomNameIndices;
    DETOUR_ATTACH(&(PVOID&)o_getRandomNameIndices, getRandomNameIndices);

    o_getRandomName = (t_getRandomName)offsets.getRandomName;
    DETOUR_ATTACH(&(PVOID&)o_getRandomName, getRandomName);

	o_characterConstructor = (t_characterConstructor)offsets.characterConstructor;
	DETOUR_ATTACH(&(PVOID&)o_characterConstructor, characterConstructor);

//	o_FUN_00890730 = (t_FUN_00890730)offsets.FUN_00890730;
//	DETOUR_ATTACH(&(PVOID&)o_FUN_00890730, FUN_00890730);

	o_getCharacterFactionID = (t_getCharacterFactionID)offsets.getCharacterFactionID;
	DETOUR_ATTACH(&(PVOID&)o_getCharacterFactionID, getCharacterFactionID);

//	o_FUN_004a6330 = (t_FUN_004a6330)offsets.FUN_004a6330;
//	DETOUR_ATTACH(&(PVOID&)o_FUN_004a6330, FUN_004a6330);

//  o_onReadDescrRegions = (t_onReadDescrRegions)offsets.onReadDescrRegions;
//  DETOUR_ATTACH(&(PVOID&)o_onReadDescrRegions, onReadDescrRegions);
#endif // FACTION_LIMIT_TESTS


#ifdef FACTION_BUTTON_TEST
    o_onSetFactionButton = (t_onSetFactionButton)offsets.onSetFactionButton;
    DETOUR_ATTACH(&(PVOID&)o_onSetFactionButton, onSetFactionButton);

	o_onFactionStartTurnNotify = (t_onFactionStartTurnNotify)offsets.onFactionStartTurnNotify;
	DETOUR_ATTACH(&(PVOID&)o_onFactionStartTurnNotify, onFactionStartTurnNotify);

    o_FUN_00c48a18 = (t_FUN_00c48a18)offsets.FUN_00c48a18;
    DETOUR_ATTACH(&(PVOID&)o_FUN_00c48a18, FUN_00c48a18);

    o_FUN_00868790 = (t_FUN_00868790)offsets.FUN_00868790;
    DETOUR_ATTACH(&(PVOID&)o_FUN_00868790, FUN_00868790);
#endif // FACTION_BUTTON_TEST

    

    //ФИКС ДЛЯ ХОТ-СИТ КАМПАНИИ - непонятный вылет при выгрузке карты кампании.   
    o_FUN_004a9634 = (t_FUN_004a9634)offsets.FUN_004a9634;
	DETOUR_ATTACH(&(PVOID&)o_FUN_004a9634, FUN_004a9634);


    //...   
}


void setLanguageDLL()
{
    LOG_ALWAYS(RELEASE, "setLanguage()");

    /**/
	ifstream fl("dmData/configs/launchSettings.json");
	json dataL = json::parse(fl);
	dataL.at("playMusic"     ).get_to(startSettings.playMusic);
	dataL.at("language"      ).get_to(startSettings.language);
	dataL.at("mainHotSeat"   ).get_to(startSettings.mainHotSeat);
	dataL.at("ancillaryLimit").get_to(startSettings.ancLimit);
	dataL.at("logLevel"      ).get_to(startSettings.logLevel);
    dataL.at("debugExe"      ).get_to(startSettings.debugExe);
    dataL.at("debugDll"      ).get_to(startSettings.debugDll);
    dataL.at("gameVersion"   ).get_to(startSettings.gameVersion);

    LOG.setLogLevel(LOG_LEVEL(startSettings.logLevel));
    /**/


    while (startSettings.debugDll && !IsDebuggerPresent())
    {
        Sleep(100);
    }


    offsets.init(startSettings.gameVersion);


    json data = NULL;
	if (startSettings.language == "RU")
	{
		ifstream f("dmData/configs/languageRU.json");
		data = json::parse(f);
		f.close();
	}
	else
	{
		ifstream f("dmData/configs/languageENG.json");
		data = json::parse(f);
		f.close();
	}
    LOG_ASSERT(data!=NULL, "Failed to install language.");

    data.at("RTWHST"             ).get_to(desTab.RTWHST);
	data.at("battle1"            ).get_to(desTab.battle1);
	data.at("battle2"            ).get_to(desTab.battle2);
	data.at("kConsole"           ).get_to(desTab.kConsole);
	data.at("consVer"            ).get_to(desTab.consVer);
	data.at("stratCoords"        ).get_to(desTab.stratCoords);
	data.at("selCoords"          ).get_to(desTab.selCoords);
	data.at("selChar"            ).get_to(desTab.selChar);
	data.at("PMOpercent"         ).get_to(desTab.PMOpercent);
	data.at("currHotSeat"        ).get_to(desTab.currHotSeat);
	data.at("battResult"         ).get_to(desTab.battResult);
	data.at("failedRes"          ).get_to(desTab.failedRes);
	data.at("transferRes"        ).get_to(desTab.transferRes);
	data.at("fileMissing"        ).get_to(desTab.fileMissing);
	data.at("resultsDone"        ).get_to(desTab.resultsDone);
	data.at("close"              ).get_to(desTab.close);
	data.at("createBattle"       ).get_to(desTab.createBattle);
	data.at("errNumUnits"        ).get_to(desTab.errNumUnits);
	data.at("errTypeUnits"       ).get_to(desTab.errTypeUnits);
	data.at("logLevel"           ).get_to(desTab.logLevel);

    data.at("playersList"        ).get_to(desTab.playersList);      
    data.at("incomingMessage"    ).get_to(desTab.incomingMessage);  
    data.at("writeMessage"       ).get_to(desTab.writeMessage);     
    data.at("reply"              ).get_to(desTab.reply);            
    data.at("deleteMessage"      ).get_to(desTab.deleteMessage);    
    data.at("sendMessage"        ).get_to(desTab.sendMessage);      
    data.at("quitGame"           ).get_to(desTab.quitGame);         
    data.at("loadSave"           ).get_to(desTab.loadSave);         
    data.at("start"              ).get_to(desTab.start);            
    data.at("setNickname"        ).get_to(desTab.setNickname);      
    data.at("setPlayer"          ).get_to(desTab.setPlayer);        
    data.at("deletePlayer"       ).get_to(desTab.deletePlayer);     
    data.at("nickname"           ).get_to(desTab.nickname);         
    data.at("password"           ).get_to(desTab.password);         
    data.at("isKeymaster"        ).get_to(desTab.isKeymaster);      
    data.at("husbands"           ).get_to(desTab.husbands);         
    data.at("updateFiles"        ).get_to(desTab.updateFiles);      
    data.at("updKeyPass"         ).get_to(desTab.updKeyPass);       
    data.at("setKeyPass"         ).get_to(desTab.setKeyPass);       
    data.at("openHS"             ).get_to(desTab.openHS);   
    data.at("neverWithdraw"      ).get_to(desTab.neverWithdraw);
    data.at("player"             ).get_to(desTab.player);

	if (fileExists("dmData/configs/isKeymaster.dm"))
	{
		gameWindow.isKeymaster = true;
	}

	getWindowRect();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
static struct helperMenu
{
    string inputConsole                 = "";
    string inputScript                  = "";
    string inputScriptFile              = "";
    string inputKillFaction             = "";
    string inputAlias                   = "";
    string inputSuzerain                = "";
    string inputVassal                  = "";

    int inputKillUnit[19]               = {};
    int inputAncillary[128]             = {};
    int inputUnitAlias[19]              = {};
    int inputDipStance[9]               = {};

    bool isNamedCharacter               = false;
    string coordsClick                  = "";
    string ClickCharacter               = "null";

    namedCharacter* targetSelectGeneral = NULL;
    int xTargetCoord, yTargetCoord;

    helperMenu() :
        inputConsole                    (""),
        inputScript                     (""),
        inputScriptFile                 (""),
        inputKillFaction                (""),
        inputAlias                      (""),
        inputSuzerain                   (""),
        inputVassal                     (""),

        inputKillUnit                   (),
        inputAncillary                  (),
        inputUnitAlias                  (),
        inputDipStance                  (),

        isNamedCharacter                (false),
        coordsClick                     (""),
        ClickCharacter                  ("null"),

        targetSelectGeneral             (NULL),
        xTargetCoord                    (0),
        yTargetCoord                    (0)
    {
    }

}helper;

static void check_bShowWindow()
{
    if (ImGui::IsKeyPressed(ImGuiKey_GraveAccent) && ImGui::IsKeyDown(ImGuiKey_LeftCtrl))
    {
        gameWindow.bShowWindow = !gameWindow.bShowWindow;
        if (gameWindow.bShowWindow)
        {
        //  helper = helperMenu();    // Нужно подумать, где лучше обнулять - может при загрузке/выгрузке карты кампании???   
        }
    }

    gameWindow.isLeftAlt = false;
    if (GetKeyState(VK_LMENU) & 0x8000)
    {
        gameWindow.isLeftAlt = true;
    }
}

void draw_main()
{
	if (gameWindow.controlsDisabled && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow))
	{
		gameWindow.controlsDisabled = false;
		helper_functions::disableShortcuts(false);
	}



    battle_create::drawBattle();
	check_bShowWindow();
	HOT_SEAT_CAMPAIGN.drawMenu();
	mapView.tacticalMapViewerDraw();

	if (!HOT_SEAT_CAMPAIGN.m_show_keymaster_console)
		return;

	if (!(gameWindow.bShowWindow && gameWindow.isKeymaster))
		return;



    ImGui::SetNextWindowPos({ 0,0 }, ImGuiCond_Always);
    DWORD dwFlag = ImGuiWindowFlags_None;	//  | ImGuiWindowFlags_NoTitleBar
    ImGui::SetNextWindowSize(ImVec2(450.0f, 400.0f), ImGuiCond_Once);
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.9f);
    string hsName = desTab.currHotSeat + startSettings.mainHotSeat;
    ImGui::Begin(hsName.c_str(), &gameWindow.bShowWindow, dwFlag);
    ImGui::PopStyleVar(1);

	helper_functions::disableShortcutsIsWindowFocused();

#if _DEBUG
    ImVec2 ImGuiRect = ImGui::GetMainViewport()->WorkSize;
    ImVec2 ImGuiSize = ImGui::GetMainViewport()->Size;
    string r_s = to_string(ImGuiRect.x) + ", " + to_string(ImGuiRect.y) + " | " + to_string(ImGuiSize.x) + ", " + to_string(ImGuiSize.y);
    ImGui::Text(r_s.c_str());
#endif

    ImGui::TextColored(ImColor(44, 234, 86),  desTab.kConsole.c_str()); 
    ImGui::SameLine();
    ImGui::TextColored(ImColor(122, 145, 120, 100), desTab.consVer.c_str());
    ImGui::Separator();
    
    string coordsStr = getAndPrintStratPosition();
    ImGui::TextColored(ImColor(44, 234, 86, 255), desTab.stratCoords.c_str());
    ImGui::SameLine();
    ImGui::TextColored(ImColor(208, 206, 92, 255), coordsStr.c_str());

#if _DEBUG
    string coordsMStr = to_string(gameCursor->previousPosition.xCoord) + ", " + to_string(gameCursor->previousPosition.yCoord);
    ImGui::TextColored(ImColor(44, 234, 86, 255), "Monitor cursor pos");
    ImGui::SameLine();
    ImGui::TextColored(ImColor(208, 206, 92, 255), coordsMStr.c_str());
#endif

    if (!gameWindow.mouseAtImgui && coordsStr != "null, null" && ImGui::IsMouseClicked(0))
    {
        helper.coordsClick = to_string(qa.xLocCoord) + ", " + to_string(qa.yLocCoord);
        LOG_ALWAYS(BUGTEST, "click on the map: " + helper.coordsClick);
        helper.ClickCharacter = getClickCharacterName();
        helper.isNamedCharacter = qa.selectGeneral && qa.selectGeneral->gen &&(qa.selectGeneral->gen->genType->type == NAMED_CHARACTER || qa.selectGeneral->gen->genType->type == GENERAL);
    }
    if (qa.selectGeneral && ImGui::IsMouseClicked(2))
    {
    	helper.targetSelectGeneral = qa.selectGeneral;
    	helper.xTargetCoord        = qa.xLocCoord;
    	helper.yTargetCoord        = qa.yLocCoord;
    }
    if (helper.coordsClick != "")
    {
    	ImGui::TextColored(ImColor(44, 234, 86, 255), desTab.selCoords.c_str());
    	ImGui::SameLine();
    	ImGui::TextColored(ImColor(208, 206, 92, 255), helper.coordsClick.c_str());
    }
    if (helper.ClickCharacter != "null")
    {
    	ImGui::TextColored(ImColor(44, 234, 86, 255), desTab.selChar.c_str());
    	ImGui::SameLine();
    	ImGui::TextColored(ImColor(208, 206, 92, 255), helper.ClickCharacter.c_str());
    	
    	if (helper.isNamedCharacter)
    	{
            if (ImGui::Button(desTab.PMOpercent.c_str()))
            {
                LOG_ALWAYS(BUGTEST, desTab.PMOpercent);
                killPMOpercent(10.0f);
    		}
    	}
    }
    ImGui::Separator();
    
    
    gameWindow.bShowWindow = HOT_SEAT_CAMPAIGN.drawSettings();
    ImGui::Separator();
    
    
    ImGui::InputText("##1", &helper.inputConsole);
    ImGui::SameLine();
    if (ImGui::Button("Run Console"))
    {
        LOG_ALWAYS(BUGTEST, "Console Run: " + helper.inputConsole);
        
        int pos     = helper.inputConsole.find(",");
        string name = helper.inputConsole.substr(0, pos);
        string arg  = helper.inputConsole.substr(pos + 1);
        
        helper_functions::callGameConsoleCommand(name.c_str(), arg.c_str());
    }
    
    ImGui::InputText("##2", &helper.inputScript);
    ImGui::SameLine();
    if (ImGui::Button("Run Script"))
    {
        new_events::callScript(helper.inputScript.c_str());
        LOG_ALWAYS(BUGTEST, "Button: Script Run");
    }
    
    ImGui::InputText("##8", &helper.inputScriptFile);
    ImGui::SameLine();
    if (ImGui::Button("Run Script from file"))
    {
    	new_events::callScriptFromFile(helper.inputScriptFile.c_str());//"zoom_strat_camera.txt"
    	LOG_ALWAYS(BUGTEST, "Button: Run Script from file");
    }


#ifdef OTHER_TESTS
    if (ImGui::Button("Run Script TEST"))
    {
    
        new_events::callScript("spawn_army\n"
            "faction	gauls\n"
            "character Brycham, general, age 23, , x 130, y 18\n"
    		 
            "unit		barb cavalry gaul				soldiers 45 exp 3 armour 0 weapon_lvl 0\n"
            "unit		barb cavalry gaul				soldiers 32 exp 3 armour 0 weapon_lvl 0\n"
            "unit		barb cavalry gaul				soldiers 45 exp 3 armour 0 weapon_lvl 0\n"
            "unit		barb cavalry gaul				soldiers 50 exp 3 armour 0 weapon_lvl 0\n"
            "unit		barb cavalry gaul				soldiers 50 exp 3 armour 0 weapon_lvl 0\n"
            "unit		barb cavalry gaul				soldiers 7 exp 3 armour 0 weapon_lvl 0\n"
            "unit		barb cavalry gaul				soldiers 1 exp 5 armour 0 weapon_lvl 0\n"
            "unit		barb cavalry gaul				soldiers 15 exp 3 armour 0 weapon_lvl 0\n"
            "unit		barb cavalry gaul				soldiers 6 exp 1 armour 0 weapon_lvl 0\n"
            "unit		barb cavalry gaul				soldiers 15 exp 1 armour 0 weapon_lvl 0\n"
            "unit		barb cavalry gaul				soldiers 4 exp 4 armour 0 weapon_lvl 0\n"
            "unit		barb cavalry gaul				soldiers 14 exp 3 armour 0 weapon_lvl 0\n"
            "unit		barb cavalry gaul				soldiers 52 exp 3 armour 0 weapon_lvl 0\n"
            "unit		barb cavalry gaul				soldiers 38 exp 1 armour 0 weapon_lvl 0\n"
            "unit		barb peltast gaul				soldiers 46 exp 1 armour 0 weapon_lvl 0\n"
            "unit		barb druids gaul				soldiers 27 exp 4 armour 0 weapon_lvl 0\n"
            "unit		merc spanish infantry				soldiers 43 exp 3 armour 0 weapon_lvl 0\n"
            "unit		barb peltast gaul				soldiers 22 exp 1 armour 0 weapon_lvl 0\n"
            "unit		barb peltast gaul				soldiers 4 exp 1 armour 0 weapon_lvl 0\n"
    //      "unit		test_unit				soldiers 17 exp 1 armour 0 weapon_lvl 0\n"
            "end\n"
            );

        LOG_ALWAYS(BUGTEST, "Button: Run Script TEST");
    }
#endif // OTHER_TESTS

	ImGui::Separator();
/////////////////////


#if _DEBUG
    ImGui::InputInt("##4", &helper.inputAncillary[0], 1);
    ImGui::SameLine();
    if (ImGui::Button("set ancillary limit"))
    {
    	uint8_t l = helper.inputAncillary[0];
    	LOG_ALWAYS(BUGTEST, "setAncLimit(" + to_string(l) + ")");
    	new_events::setAncLimit(l);
    }
#endif // _DEBUG

    if (qa.selectGeneral && qa.selectGeneral->gen && qa.selectGeneral->gen->armyLeaded)
    {
    	ImGui::InputInt("##3", &helper.inputKillUnit[0], 1);
    	ImGui::SameLine();
    	if (ImGui::Button("kill this unit"))
    	{
            LOG_ALWAYS(BUGTEST, "kill this unit: " + to_string(helper.inputKillUnit[0]));
    
            int u = helper.inputKillUnit[0];
            unit* targetUnit = NULL;
    
            if (u >= 0 && u <= qa.selectGeneral->gen->armyLeaded->numOfUnits)
                targetUnit = qa.selectGeneral->gen->armyLeaded->units[u];
    
            if (targetUnit && !targetUnit->general)
                new_events::o_onKillUnit(targetUnit);
    		 // selectCharacter->deathType = 1;
        }
    }

    ImGui::InputText("##5", &helper.inputKillFaction);
    ImGui::SameLine();
    if (ImGui::Button("kill this faction"))
    {
    	LOG_ALWAYS(BUGTEST, "kill this faction: " + helper.inputKillFaction);
    	if (factionStruct* fac = helper_functions::getFactionByName(helper.inputKillFaction))
        {
            new_events::o_onKillFaction(fac);
        }
    }
    
    if (qa.selectGeneral && qa.selectGeneral->gen && ImGui::Button("kill this character"))
    {
    	LOG_ALWAYS(BUGTEST, "kill this character: " + string(qa.selectGeneral->fullName));
    //	selectCharacter->deathType = 1; // мирно скончался(onKillCharacter не сработает), по умолчанию - погиб в бою   
    	new_events::o_onKillCharacter(qa.selectGeneral->gen);
    }
    
    if (qa.selectGeneral && qa.selectGeneral->gen && ImGui::Button("Reposition"))
    {
    	LOG_ALWAYS(BUGTEST, "Reposition");
    	new_events::o_onReposition(qa.selectGeneral->gen, 1, qa.xLocCoord, qa.yLocCoord);
    }
    
    if (helper.targetSelectGeneral && helper.targetSelectGeneral->gen && helper.targetSelectGeneral->gen->armyLeaded && ImGui::Button("Attack"))
    {
    	LOG_ALWAYS(BUGTEST, "Attack");
    	if (character* ch = helper_functions::getCharacterByCoords(qa.xLocCoord, qa.yLocCoord))
    	{
    	    new_events::o_onAttackArmy(helper.targetSelectGeneral->gen->armyLeaded, 1, ch, 0);
    	    LOG_ALWAYS(BUGTEST, "attacker: " + string(helper.targetSelectGeneral->fullName) + ", defender: " + string(ch->genChar->fullName));
    	}
    }
    
    if (helper.targetSelectGeneral && helper.targetSelectGeneral->gen && helper.targetSelectGeneral->gen->armyLeaded && ImGui::Button("Attack settlement"))
    {
    	LOG_ALWAYS(BUGTEST, "Attack settlement");
    	if (settlementStruct* s = helper_functions::getSettlementByCoords(qa.xLocCoord, qa.yLocCoord))
    	{
    	    new_events::o_onAttackSettlement(helper.targetSelectGeneral->gen->armyLeaded, 1, s, 0);
    	    LOG_ALWAYS(BUGTEST, "settlement attacker: " + string(helper.targetSelectGeneral->fullName) + ", settlement: " + string(s->name));
    	}
    }
    
    if (helper.targetSelectGeneral && helper.targetSelectGeneral->gen && helper.targetSelectGeneral->gen->armyLeaded && ImGui::Button("Attack fort"))
    {
    	LOG_ALWAYS(BUGTEST, "Attack fort");
    	if (fortStruct* f = helper_functions::getFortByCoords(qa.xLocCoord, qa.yLocCoord))
    	{
    	    new_events::o_onAttackFort(helper.targetSelectGeneral->gen->armyLeaded, 1, f, 0);
    	    LOG_ALWAYS(BUGTEST, "fort attacker: " + string(helper.targetSelectGeneral->fullName) + ", fort coords: " + to_string(qa.xLocCoord) + "," + to_string(qa.yLocCoord));
    	}
    }
    
    if (helper.targetSelectGeneral && helper.targetSelectGeneral->gen && helper.targetSelectGeneral->gen->armyLeaded && ImGui::Button("Attack port"))
    {
    	LOG_ALWAYS(BUGTEST, "Attack port");
    	if (portBuildingStruct* p = helper_functions::getPortByCoords(qa.xLocCoord, qa.yLocCoord))
    	{
            new_events::o_onAttackPort(helper.targetSelectGeneral->gen->armyLeaded, 1, p, 0);
            LOG_ALWAYS(BUGTEST, "fort attacker: " + string(helper.targetSelectGeneral->fullName) + ", fort coords: " + to_string(qa.xLocCoord) + "," + to_string(qa.yLocCoord));
    	}
    }
    
    if (helper.targetSelectGeneral && ImGui::Button("Disembark"))
    {
    	if (character* ch = helper_functions::getCharacterByCoords(helper.xTargetCoord, helper.yTargetCoord, ADMIRAL))
    	{
    	    new_events::o_onDisembark(ch, 1, qa.xLocCoord, qa.yLocCoord);
    	}
    }
    
    ImGui::Separator();
    /*
    	War = 1,
    	Peace = 2,
    	Alliance = 3,
    	Suzerain = 4,
    	MilitaryAccess = 5,
    	Trade = 6
    */
    ImGui::PushItemWidth(200.F);
    ImGui::InputText("##9", &helper.inputSuzerain);
    ImGui::SameLine();
    ImGui::InputText("##10", &helper.inputVassal);
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(100.F);
    ImGui::InputInt("##11", &helper.inputDipStance[0], 1);
    ImGui::PopItemWidth();
    if (ImGui::Button("setDipStance"))
    {
    	if (factionStruct* fac1 = helper_functions::getFactionByName(helper.inputSuzerain);
    		factionStruct* fac2 = helper_functions::getFactionByName(helper.inputVassal))
    	{
    		qa.campaignStruct->setDipStance(DipRelEnum(helper.inputDipStance[0]), fac1, fac2);
    		LOG_ALWAYS(BUGTEST, "setDipStance");
    	}
    }
#if _DEBUG

    if (ImGui::Button("checkDipStance"))
    {
    	if (factionStruct* fac1 = helper_functions::getFactionByName(helper.inputSuzerain);
    		factionStruct* fac2 = helper_functions::getFactionByName(helper.inputVassal))
    	{
    		bool result = qa.campaignStruct->checkDipStance(DipRelEnum(helper.inputDipStance[0]), fac1, fac2);
    		LOG_ALWAYS(BUGTEST, "checkDipStance");
    	}
    }
    ImGui::Separator();
    
    
    if (ImGui::Button("printGameConsoleCommands"))
    {
    	LOG_ALWAYS(BUGTEST, "printGameConsoleCommands");
    	helper_functions::printGameConsoleCommands();
    }
    
    
    ImGui::InputText("##7", &helper.inputAlias);
    ImGui::InputInt("##6", &helper.inputUnitAlias[0], 1);
    ImGui::SameLine();
    if (ImGui::Button("test_alias") && qa.selectGeneral)
    {
    	string s2 = u8"" + helper.inputAlias;
    	uint8_t l = helper.inputAncillary[0];
    
    	createUniString(qa.selectGeneral->gen->armyLeaded->units[helper.inputUnitAlias[0]]->alias, s2.c_str());
    
    	string notif = "alias: " + helper.inputAlias;
    	LOG_ALWAYS(BUGTEST, notif);
    	ImGui::InsertNotification({ ImGuiToastType_None, 5000, notif.c_str() });
    
    	LOG_ALWAYS(BUGTEST, "Button: test_alias");
    }
    if (ImGui::Button("test_locName") && qa.selectGeneral)
    {
    	uint8_t l = helper.inputAncillary[0];
    
    	string _localizedFullName = uniStringToStr(qa.selectGeneral->localizedFullName);
    	createUniString(qa.selectGeneral->localizedFullName, helper.inputAlias.c_str());
    
    	string notif = "locName: " + helper.inputAlias;
    	LOG_ALWAYS(BUGTEST, notif);
    	ImGui::InsertNotification({ ImGuiToastType_None, 5000, notif.c_str() });
    
    	LOG_ALWAYS(BUGTEST, "Button: test_alias");
    }
    
    if (ImGui::Button("onCharacterCreated"))
    {
    	factionStruct* faction = helper_functions::getFactionByName("romans_julii");
    	int facID = faction->dipNum;
    	character* new_character = new_events::createCharacter(DIPLOMAT, faction, 17, "Amulius", "Acilius", facID, "fernando", qa.xLocCoord, qa.yLocCoord);
    //	character* new_character = new_events::createCharacter(DIPLOMAT, faction, 17, "Amulius", "Acilius", facID, "fernando/portrait_young.tga", xLocCoord, yLocCoord);
    //	character* new_character = new_events::createCharacter(DIPLOMAT, faction, 17, "Amulius", "Acilius", facID, xLocCoord, yLocCoord);
    
    	/*
    	typedef character* __cdecl func(characterType charType, factionStruct* faction, int age, const char* name, const char* surname, int originalFactionId);
    	func* f = (func*)0x00890724;
    	factionStruct* faction = helper_functions::getFactionByName("romans_julii");
    	character* new_character = f(NAMED_CHARACTER, faction, 17, "Amulius", "Acilius", 0);
    	new_events::o_onReposition(new_character, 0, xLocCoord, yLocCoord);
    	*/
    
    	LOG_ALWAYS(BUGTEST, "Button: onCharacterCreated");
    }

    if (ImGui::Button("onCharacterCreated general"))
    {
    	factionStruct* faction = helper_functions::getFactionByName("romans_julii");
    	int facID = faction->dipNum;
    
    	character* new_character = new_events::createCharacter(NAMED_CHARACTER, faction, 17, "Amulius", "Acilius", facID, "fernando", qa.xLocCoord, qa.yLocCoord);
    	stackStruct* army = new_events::onCreateArmy(faction, 0, new_character, false);
    
    	unitDb* db = reinterpret_cast<unitDb*>(0x013006c0);
    	coords xy = coords(qa.xLocCoord, qa.yLocCoord);
    	coords* xy2 = &xy;

    	auto edu = eop_unit::getEopEduEntry(1000);
    
    	unit* bodyg = new_events::onSetBodyguardUnit(army, 0, new_character, 9, 2, 3, edu);
    
        LOG_ALWAYS(BUGTEST, "Button: onCharacterCreated 2");
    }

    if (ImGui::Button("onCreateUnit"))
    {
    	if (settlementStruct* sett = helper_functions::getSettlementByCoords(qa.xLocCoord, qa.yLocCoord))
    	{
    		stackStruct* army = sett->army;
    
    	 //	regionStruct* region1 = helper_functions::getRegionByIndex(army->regionID);
    	 //	regionStruct* region2 = helper_functions::getRegionByName("Etruria");
    		regionStruct* region3 = helper_functions::getRegionByID(army->regionID);
    
    		factionStruct* faction = sett->faction;
    
    		unitDb* db = reinterpret_cast<unitDb*>(0x013006c0);
    	 //	unit* un = new_events::onCreateUnit(db, 0, region3, 0, faction->dipNum, 0, 1000, 2, 3);
    	 //	unit* un = new_events::onCreateUnit(db, 0, region3, 0, faction->dipNum, 0, 177, 2, 3);
    
    	 //	unit* un = new_events::onCreateUnit2(db, 0, region3, 177, faction->dipNum, 0, 100);
    	 // unit* un = new_events::onCreateUnit2(db, 0, region3, 500, faction->dipNum, 0, 100);
    		unit* un = new_events::onCreateUnit2(db, 0, region3, 1000, faction->dipNum, 0, 210);
    
			new_events::onGiveUnitToArmy(army, 0, un, nullptr);
    
    		LOG_ALWAYS(BUGTEST, "Button: onCharacterCreated 2");
    	}
    }

    if (ImGui::Button("eopEduEntry"))
    {
    //	eopEduEntry newEntry("test_unit.txt", 1000);
    //	dataU.eopEdu.push_back(newEntry);
        new_events::createEOPunit("test_unit.txt", 1000);
    	auto edu = eop_unit::getEopEduEntry(1000);
    }

#ifdef OTHER_TESTS
   ImGui::Checkbox("sap_point_fix", &new_events::sap_point_fix);
#endif // OTHER_TESTS

    if (qa.selectGeneral && ImGui::Button("setExperience"))
    {
    	stackStruct* army = qa.selectGeneral->gen->armyLeaded;
    
    	for (int u = army->numOfUnits; u >= 0; u--)
    	{
    		unit* un = army->units[u];
    		army->units[u]->setExperience(9);
    	}
    }

	if (ImGui::Button("QuickSave"))
	{
		new_events::callSaveCreate("alexander/saves/savePath_123.sav");
	}
	if (ImGui::Button("QuickLoad"))
	{
		new_events::callSaveLoad("alexander/saves/savePath_123.sav");
	}

#ifdef FACTION_BUTTON_TEST
	if (ImGui::Button("faction button"))
	{
    //  iVar2 = classCreatorNEW(0x15c, s_C:\barbi_daily\code\ui\strat_v2__01023294,
    //      s_C:\barbi_daily\code\ui\strat_v2__02a5acf0, 0xe6, 1);
        char* param_2 = reinterpret_cast<char*>(0x01023294);
        char* param_3 = reinterpret_cast<char*>(0x02a5acf0);
        fb* gameClass = GAME_FUNC(fb*(__cdecl*)(int param_1, char* param_2, char* param_3, undefined4 param_4, undefined4 param_5), 0x00ee12b0)(0x15c, param_2, param_3, 0xe6, 1); //classCreatorNEW  

	//  coords* c = new coords(900, 122);
		coords* c = new coords(700, 122); 
        
        int id = qa.gDataAll->campaignData->currentFactionTurn->dipNum;
        id = 19;
		onSetFactionButton(gameClass, 0, id, c); //   
	}
	if (ImGui::Button("faction button 2"))
	{
        LOG_ALWAYS(BUGTEST, "faction button 2 start");

    //  iVar2 = classCreatorNEW(0x1a0, s_C:\barbi_daily\code\game_strat_h_0101fb8c,
    //      s_C:\barbi_daily\code\game_strat_h_029df9a0, 0xdf, 1);
        char* param_2 = reinterpret_cast<char*>(0x0101fb8c);
        char* param_3 = reinterpret_cast<char*>(0x029df9a0);
        DWORD gameClass = GAME_FUNC(DWORD(__cdecl*)(int param_1, char* param_2, char* param_3, undefined4 param_4, undefined4 param_5), 0x00ee12b0)(0x1a0, param_2, param_3, 0xdf, 1); //classCreatorNEW  

		//undefined4 * __fastcall FUN_00c35688(undefined4 *param_1)
        GAME_FUNC(int(__thiscall*)(DWORD _this), 0x00c35688)(gameClass); // 

   //   FUN_00c48a18(gameClass, 0);

        LOG_ALWAYS(BUGTEST, "faction button 2 end");
	}
	if (ImGui::Button("faction button 3"))
	{
        LOG_ALWAYS(BUGTEST, "faction button 3 start");

        FUN_00868790((void*)0x01685e7c, 0);

        LOG_ALWAYS(BUGTEST, "faction button 3 end");
	}
	if (ImGui::Button("faction button 4"))
	{
        LOG_ALWAYS(BUGTEST, "faction button 4 start");

        remember_fb->data[86] = helper_functions::getGameDataAll()->campaignData->currentFactionTurn->dipNum;

        LOG_ALWAYS(BUGTEST, "faction button 4 end");
	}
	if (ImGui::Button("faction button 5"))
	{
        LOG_ALWAYS(BUGTEST, "faction button 5 start");

        factionStruct* faction = helper_functions::getGameDataAll()->campaignData->currentFactionTurn;
        onFactionStartTurnNotify(remember_onFactionStartTurnNotify, 0, faction);

        LOG_ALWAYS(BUGTEST, "faction button 5 end");
	}
	if (ImGui::Button("faction button 6"))
	{
        LOG_ALWAYS(BUGTEST, "faction button 6 start");

        //0040a938
        DWORD gameClass = GAME_FUNC(DWORD(__cdecl*)(), 0x0040a938)(); // getEventHandler   

        auto off = gameClass + 0xc;
        GAME_FUNC(DWORD(__fastcall*)(DWORD _this), off)(gameClass); // openDisplay   

    //  auto off = gameClass + 0x10;
    //  GAME_FUNC(DWORD(__fastcall*)(DWORD _this), off)(gameClass); // closeDisplay   

        LOG_ALWAYS(BUGTEST, "faction button 6 end");
	}
#endif // FACTION_BUTTON_TEST

#ifdef OTHER_TESTS
	if (ImGui::Button("encryption test"))
	{
		string targetFile = ("dmData\\temp\\hs.json");
		string newFile = "dmData\\temp\\output.txt";
		encryption::encryptionString(targetFile, newFile, 17);
	}
	if (ImGui::Button("decryption test"))
	{
		string targetFile = ("dmData\\temp\\hs.json");
		string newFile = "dmData\\temp\\output.txt";
		encryption::encryptionString(newFile, targetFile, 17);
	}

    if (ImGui::Button("sapPoint"))
    {
        for (int s = 0; s < qa.battle->sidesNum; s++)
        {
            battleSide& side = qa.battle->sides[s];
            for (int a = 0; a < side.armiesNum; a++)
            {
                stackStruct* army = side.armies[a].stack;
                for (int p = 0; p < army->sapPoints; p++)
                {
                    sapPoint* sapPointArray = army->sapPointArray[p];
                    LOG_ALWAYS(BUGTEST, "sapPoint");
                }
            }
        }
    }

    // некоторые тултипы игры   
    if (ImGui::Button("gameCursor"))
    {
        auto cursor = gameCursor;
        if (cursor && cursor->action && cursor->action->tooltip)
        {
            UNICODE_STRING**& uni = *cursor->action->tooltip;
            string str = uniToAnsi(uni);
            string str2 = uniToAcp(uni);
            string str3 = uniStringToStr(uni);
            string str4 = uniToAnsi_2(uni);

            LOG_ALWAYS(BUGTEST, "gameCursor: " + str + " | " + str2 + " | " + str3 + " | " + str4);
        }
    }
    if (gameCursor && gameCursor->action && gameCursor->action->tooltip)
    {
        createUniString(*gameCursor->action->tooltip, "new tooltip");
    }
#endif // OTHER_TESTS

	if (ImGui::Button("onCreateCandidateMarrying"))
	{
		if (character* ch = helper_functions::getCharacterByCoords(qa.xLocCoord, qa.yLocCoord))
		{
			namedCharacter* daughter    = ch->genChar->childs[0];
            namedCharacter* new_husband = new_events::createCandidateMarrying(daughter);
            
            
        //  namedCharacter* new_husband = new_events::onCreateCandidateMarrying(daughter, 0);
        //
		//	char* param_2 = reinterpret_cast<char*>(0x0101cf14);
		//	char* param_3 = reinterpret_cast<char*>(0x029b66b4);
		//	marriageOption* mo = GAME_FUNC(marriageOption*(__cdecl*)(int param_1, char* param_2, char* param_3, undefined4 param_4, undefined4 param_5), 0x00ee12b0)(0x10, param_2, param_3, 0x1ff4, 1); //classCreatorNEW    
        //
		//	mo->yesNoClass      = reinterpret_cast<void*>(0x029b6670);//puVar8 = &PTR_LAB_029b6670;
		//	mo->madeChoice      = false;
		//	mo->accepted        = false;
		//	mo->possibleHusband = new_husband;
		//	mo->wife            = daughter;
		//	daughter->faction->facFamily.marriageOption = mo;
        //
		//	new_events::onDaughterReadyMarryHusband(daughter, new_husband, daughter->faction->facFamily.marriageOption);

			LOG_ALWAYS(BUGTEST, "onCreateCandidateMarrying");
		}
	}

	if (qa.xLocCoord > 0 && qa.yLocCoord > 0 && ImGui::Button("NEW SETTLEMENT click"))
	{
		string name    = "eop_sett_" + to_string(qa.xLocCoord) + "_" + to_string(qa.yLocCoord);
		string locName = "New Settlement " + to_string(EOP_SETTLEMENTS.m_minor_settlement_count + 1);
        eop_settlements::addSettlements(qa.xLocCoord, qa.yLocCoord, name.c_str(), locName.c_str(), helper_functions::getFactionByName("romans_julii"));
	}

	if (ImGui::Button("setPopulation"))
	{
		if (settlementStruct* s = helper_functions::getSettlementByCoords(qa.xLocCoord, qa.yLocCoord))
		{
			s->setPopulation(33333);
		}
	}

    if (ImGui::Button("currentFaction"))
    {
        factionStruct* currentFaction = helper_functions::getGameDataAll()->campaignData->currentFactionTurn;

        factionStruct* localFaction = qa.campaignStruct->getLocalFaction();

        LOG_ALWAYS(BUGTEST, "currentFaction = " + string(currentFaction->factSmDescr->facName));
    }
#endif // _DEBUG 


#ifdef FACTION_LIMIT_TESTS
    if (ImGui::Button("createFaction"))
	{
    //  const char* name = "faction22";
    //  int facID = 21;
        createNewFaction("faction22", 21);
    }

    if (ImGui::Button("factionCount"))
	{
        auto c = helper_functions::getGameDataAll()->campaignData->factionCount;
        helper_functions::getGameDataAll()->campaignData->factionCount = 22;
        LOG_ALWAYS(BUGTEST, "onCreateCandidateMarrying");
    }


    if (ImGui::Button("factionStruct main menu"))
	{
        factionStruct* new_faction = createFaction(21);
        new_faction->deadStatus = 0; // мы живы   
        eop_faction.m_faction[21] = new_faction;
    }

    if (ImGui::Button("faction22 onCharacterCreated"))
    {
    //  factionStruct* faction = helper_functions::getFactionByName("macedon");
        factionStruct* faction = eop_faction.getFactionByID(21);
        faction->dipNum = 0;
    	int facID = faction->dipNum;
    //	character* new_character = new_events::createCharacter(DIPLOMAT, faction, 17, "Amulius", "Acilius", facID, "fernando", qa.xLocCoord, qa.yLocCoord);
    	character* new_character = new_events::onCharacterCreated(DIPLOMAT, faction, 17, "Amulius", "Acilius", facID, "fernando", qa.xLocCoord, qa.yLocCoord);

        coords* c = new coords(qa.xLocCoord, qa.yLocCoord);
        stratPathFinding* stratPath = reinterpret_cast<stratPathFinding*>(0x01682ce4); // stratPathFinding 
        GAME_FUNC(void(__thiscall*)(stratPathFinding* _this, character* new_character, coords* c), 0x004c4af4)(stratPath, new_character, c); // spawnCreatedObject 

        faction->dipNum = 21;
    
    	LOG_ALWAYS(BUGTEST, "Button: faction22 onCharacterCreated");
    }

    if (ImGui::Button("faction22 onCharacterCreated general"))
    {
    	LOG_ALWAYS(BUGTEST, "Button: onCharacterCreated 2");
    
    	factionStruct* faction = eop_faction.getFactionByID(21);
        faction->dipNum = 0;
        int facID = faction->dipNum;


    //	character* new_character = new_events::createCharacter(NAMED_CHARACTER, faction, 17, "Amulius", "Acilius", facID, "fernando", qa.xLocCoord, qa.yLocCoord);
    	character* new_character = new_events::onCharacterCreated(NAMED_CHARACTER, faction, 17, "Amulius", "Acilius", facID, "fernando", qa.xLocCoord, qa.yLocCoord);

        coords* c = new coords(qa.xLocCoord, qa.yLocCoord);
        stratPathFinding* stratPath = reinterpret_cast<stratPathFinding*>(0x01682ce4); // stratPathFinding 
        GAME_FUNC(void(__thiscall*)(stratPathFinding* _this, character* new_character, coords* c), 0x004c4af4)(stratPath, new_character, c); // spawnCreatedObject 
        
        stackStruct* army = new_events::onCreateArmy(faction, 0, new_character, false);
    
    	unitDb* db = reinterpret_cast<unitDb*>(0x013006c0);
    	coords xy = coords(qa.xLocCoord, qa.yLocCoord);
    	coords* xy2 = &xy;

    	auto edu = eop_unit::getEDUEntryById(11);
    	unit* bodyg = new_events::onSetBodyguardUnit(army, 0, new_character, 9, 2, 3, edu);
    
        regionStruct* region = helper_functions::getRegionByID(army->regionID);

        unit* un1 = new_events::onCreateUnit2(db, 0, region, 1, faction->dipNum, 0, 210);
        new_events::onGiveUnitToArmy(army, 0, un1, nullptr);

        unit* un2 = new_events::onCreateUnit2(db, 0, region, 7, faction->dipNum, 0, 210);
        new_events::onGiveUnitToArmy(army, 0, un2, nullptr);

        unit* un3 = new_events::onCreateUnit2(db, 0, region, 17, faction->dipNum, 0, 210);
        new_events::onGiveUnitToArmy(army, 0, un3, nullptr);


        faction->dipNum = 21;
        LOG_ALWAYS(BUGTEST, "Button: faction22 onCharacterCreated 2");
    }

    if (ImGui::Button("characterChangeFaction"))
    {
        if (character* ch = helper_functions::getCharacterByCoords(qa.xLocCoord, qa.yLocCoord))
        {
       //   factionStruct* faction = helper_functions::getFactionByName("macedon");

            factionStruct* faction = eop_faction.getFactionByID(21);
            faction->dipNum = 0;

            //00593374
            GAME_FUNC(void(__thiscall*)(character* character, factionStruct* faction), 0x00593374)(ch, faction); // characterChangeFaction 



            faction->dipNum = 21;
            LOG_ALWAYS(BUGTEST, "Button: faction22 onCharacterCreated 2");
        }
    }

    if (ImGui::Button("regionStruct* region"))
	{
        regionStruct* region = helper_functions::getRegionByID(36);
        LOG_ALWAYS(BUGTEST, "regionStruct* region");

        string nsl = uniStringToStr(region->settlement->localizedName);
        string rsl = uniStringToStr(region->localizedSettlementName);
        string rl = uniStringToStr(region->localizedRegionName);
        string rrl = uniStringToStr(region->localizedRebelsName);
        LOG_ALWAYS(BUGTEST, "regionStruct* region(localizedName: " + nsl + ", region->localizedSettlementName: " + rsl + ", region->localizedRegionName: " + rl + ", region->localizedRebelsName: " + rrl + ")");

    }

    if (ImGui::Button("setFactionOwner"))
    {
    //  factionStruct* faction = helper_functions::getFactionByName("macedon");
        factionStruct* faction = eop_faction.getFactionByID(21);
        factionStruct* localFaction = qa.campaignStruct->getLocalFaction();

        GAME_FUNC(void(__thiscall*)(factionStruct* faction, int aiOrPlayer), 0x004db760)(localFaction, 0); // setFactionAiOrPlayer 
        GAME_FUNC(void(__thiscall*)(factionStruct* faction, int aiOrPlayer), 0x004db760)(faction, 1); // setFactionAiOrPlayer 

        GAME_FUNC(factionStruct*(__thiscall*)(DWORD _this, int oldID, int newID), 0x00b1ae68)(offsets.localFactionStruct, localFaction->dipNum, faction->dipNum); // resetPlayerFaction 
        eop_faction.is_new_faction_turn = true;

        LOG_ALWAYS(BUGTEST, "setFactionOwner");
    }

    if (ImGui::Button("startRound"))
    {
    //  factionStruct* faction = helper_functions::getFactionByName("macedon");
        factionStruct* faction = eop_faction.getFactionByID(21);
        factionStruct* localFaction = qa.campaignStruct->getLocalFaction();

        GAME_FUNC(void(__thiscall*)(factionStruct* faction), 0x004dbe64)(localFaction); // startRound 
        GAME_FUNC(void(__thiscall*)(factionStruct* faction), 0x004dbe64)(faction); // startRound 

        LOG_ALWAYS(BUGTEST, "startRound");
    }

    if (ImGui::Button("onPseudoPreFactionTurnStart"))
    {
    //  factionStruct* faction = helper_functions::getFactionByName("macedon");
        factionStruct* new_faction = eop_faction.getFactionByID(21);
        factionStruct* localFaction = qa.campaignStruct->getLocalFaction();

        eop_faction.is_new_faction_turn = true;
        new_events::onPseudoPreFactionTurnStart(new_faction, 0);

        GAME_FUNC(void(__thiscall*)(factionStruct* faction, int aiOrPlayer), 0x004db760)(localFaction, 0); // setFactionAiOrPlayer 
        GAME_FUNC(void(__thiscall*)(factionStruct* faction, int aiOrPlayer), 0x004db760)(new_faction, 1); // setFactionAiOrPlayer 

    //  GAME_FUNC(factionStruct* (__thiscall*)(DWORD _this, int oldID, int newID), 0x00b1ae68)(offsets.localFactionStruct, localFaction->dipNum, new_faction->dipNum); // resetPlayerFaction 

        helper_functions::getGameDataAll()->campaignData->currentFactionTurn = new_faction;

        LOG_ALWAYS(BUGTEST, "onPseudoPreFactionTurnStart");
    }

    if (ImGui::Button("currentFactionTurn"))
    {
        auto c = helper_functions::getGameDataAll()->campaignData->currentFactionTurn;
        factionStruct* faction = eop_faction.getFactionByID(21);
        helper_functions::getGameDataAll()->campaignData->currentFactionTurn = faction;

        LOG_ALWAYS(BUGTEST, "currentFactionTurn");
    }

    if (ImGui::Button("onSaveFaction"))
    {
        factionStruct* fac = eop_faction.getFactionByID(21);
        string newFile = string(fac->factSmDescr->facName) + ".sav";

        ofstream nFile;
        nFile.open(newFile, ios::binary | ofstream::out);

        nFile.write(reinterpret_cast<char*>(&fac), sizeof(factionStruct*));

        nFile.close();


        LOG_ALWAYS(BUGTEST, "onSaveFaction");
    }
    if (ImGui::Button("onLoadFaction"))
    {
        factionStruct* fac = eop_faction.getFactionByID(21);
        string newFile = string(fac->factSmDescr->facName) + ".sav";


        std::fstream binaryFile(newFile, std::ios::in | std::ios::binary);

        binaryFile.read(reinterpret_cast<char*>(&fac), sizeof(factionStruct*));

        binaryFile.close();


        LOG_ALWAYS(BUGTEST, "onLoadFaction");
    }
#endif // FACTION_LIMIT_TESTS

    if (ImGui::Button("Quit"))
    {
        new_events::quitGame();
    }

//	setNewCursor();
	ImGui::End();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
































