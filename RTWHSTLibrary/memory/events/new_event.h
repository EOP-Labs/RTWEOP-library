#pragma once
#include "../memoryWork.h"
#include <vector>

using t_onGameInit = HRESULT(__cdecl*)();
using t_onReadEDU = bool(__fastcall*)(eduEntry* _this, int stub, descrFile* file);
using t_onGetUnitFormationString = HRESULT(__cdecl*)(const char* formation);
using t_onAutosave = HRESULT(__fastcall*)(campaign* _this, int stub, bool turn_end);
using t_onQuickLoading = HRESULT(__cdecl*)(UNICODE_STRING**& savePath);
using t_onSaveCreate = HRESULT(__fastcall*)(gameSaveStruct* _this, int stub, UNICODE_STRING**& savePath, bool param_2);
using t_onSaveLoad = HRESULT(__fastcall*)(void* _this, int stub, UNICODE_STRING**& savePath);
using t_onKillFaction = HRESULT(__fastcall*)(factionStruct* fac);
using t_onKillUnitInArmy = HRESULT(__fastcall*)(stackStruct* _this, int stub, unit* kUnit);
using t_onKillUnit = HRESULT(__fastcall*)(unit* _this);
using t_onKillCharacter = HRESULT(__fastcall*)(character* _this);
using t_onConsoleError = HRESULT(__cdecl*)(char* param_1, char* param_2);
using t_onTeleport = HRESULT(__fastcall*)(character* _this, int stub, int x, int y);
using t_onAttackArmy = HRESULT(__fastcall*)(stackStruct* _this, int stub, character* general, character_action* action);
using t_onAttackFort = HRESULT(__fastcall*)(stackStruct* _this, int stub, fortStruct* fort, character_action* action);
using t_onAttackSettlement = HRESULT(__fastcall*)(stackStruct* _this, int stub, settlementStruct* settlement, character_action* action);
using t_onAttackPort = HRESULT(__fastcall*)(stackStruct* _this, int stub, portBuildingStruct* port, character_action* action);
using t_onDisembark = HRESULT(__fastcall*)(character* _this, int stub, int x, int y);
using t_onUnitLeavesArmy = HRESULT(__fastcall*)(factionStruct* _this, int stub, unit**& leaveUnits, coords* targetCoords, bool merge);
using t_onActionMove = HRESULT(__fastcall*)(character* _this, int stub, character_action* action);
using t_onBattleStateChange = HRESULT(__fastcall*)(battleDataS* battle);
using t_onBattleEnd = HRESULT(__fastcall*)(battleDataS* _this, int stub, int param_2);
using t_onHistoricAndNewGameArmyLoading = HRESULT(__fastcall*)(campaign* _this, int stub, descrFile* bFile, stackStruct* st, character* general, characterType charType, int factionID, stackStruct**& st2);
using t_onBeginSiege = HRESULT(__fastcall*)(character* _this, int stub, settlementStruct* settlement);
using t_onHistoricBattleAndNewGameLoading = HRESULT(__fastcall*)(campaign* _this, int stub, descrFile* bFile, stackStruct**& siegeStacks);
using t_getRegionByCoords = regionStruct*(__fastcall*)(campaign* _this, int stub, coords* coords);
using t_onMap_rwmLoaded = HRESULT(__fastcall*)(campaign* _this, int stub, UNICODE_STRING**& savePath);
using t_onCheckUnitBattleStatus = HRESULT(__fastcall*)(unit* _this, int stub, battleStatus* status);
using t_onCharacterCreated = character*(__cdecl*)(characterType charType, factionStruct* faction, int age, const char* name, const char* surname, int subFaction, const char* portrait, int x, int y);
using t_onCharacterCreated2 = character*(__cdecl*)(descrFile* bFile, factionStruct* faction, int age, const char* name, const char* surname, int subFaction, const char* portrait, int x, int y);
using t_onRebelGarrisonCreated = stackStruct*(__fastcall*)(settlementStruct* _this, int stub, int param_1, bool param_2, int param_3, int originalFactionId);
using t_onCreateAllScripts = HRESULT(__fastcall*)(scriptClass* _this, int stub, descrFile* file, const char* endWord);
using t_onCreateScriptFromFile = scriptClass*(__fastcall*)(scriptClass* _this, int stub, descrFile* file);
using t_onExecuteScript = scriptResult(__fastcall*)(scriptClass* script);
using t_onConsoleExecute = bool(__fastcall*)(void* _this, int stub, const char* cmd, char* param_3);
using t_onCreateDescrFile = HRESULT(__fastcall*)(descrFile* _this, int stub, UNICODE_STRING**& file, int param_2);
using t_onNewGameStart = HRESULT(__fastcall*)(campaign* camp);
using t_onCampaignMapLoaded = bool(__fastcall*)(campaign* _this, int stub, int param_2);
using t_onChangeTurnNum = HRESULT(__fastcall*)(campaign* camp);
using t_onSetVassal = void(__fastcall*)(void* _this, int stub, int vassalID, int suzerainID);
using t_onPseudoPreFactionTurnStart = void(__fastcall*)(factionStruct* _this, int stub);
using t_onCreateCandidateMarrying = namedCharacter*(__fastcall*)(namedCharacter* daughter, int stub);
using t_onDaughterReadyMarryHusband = int(__cdecl*)(namedCharacter* daughter, namedCharacter* new_husband, marriageOption* mo);
using t_onStartFamilyRound = void(__fastcall*)(family* family);
using t_onLoadEDU = bool(__fastcall*)(unitDb* _this, int stub, const char* file);
using t_onTransitionToBattleFromStratMap = int(__fastcall*)(void* _this, int stub, int type);
using t_onOpenFile = HRESULT(__cdecl*)(char* file);
using t_onGiveUnitToArmy = HRESULT(__fastcall*)(stackStruct* _this, int stub, unit* un, unit* add_after);
using t_onCreateUnit = unit*(__fastcall*)(unitDb* _this, int stub, regionStruct* region, int index, int factionID, int ability, int soldiers, int armour_lvl, int weapon_lvl);
using t_onCreateUnit2 = unit*(__fastcall*)(unitDb* _this, int stub, regionStruct* region, int index, int factionID, int ability, int soldiers);
using t_onCreateUnit3 = unit*(__fastcall*)(unitDb* _this, int stub, regionStruct* region, nameAndHash* ID, int factionID, int ability);
using t_onCreateUnit4 = unit*(__fastcall*)(unitDb* _this, int stub, regionStruct* region, nameAndHash* ID, int factionID, int ability, int soldiers, int armour_lvl, int weapon_lvl);
using t_onSetBattleUnitModels = HRESULT(__fastcall*)(unitDb* _this, int stub);
using t_onCreateArmy = stackStruct*(__fastcall*)(factionStruct* _this, int stub, character* general, bool isNavy);
using t_onSetBodyguardUnit = unit*(__fastcall*)(stackStruct* _this, int stub, character* general, int exp, int weapon_lvl, int armour_lvl, eduEntry* ud);
using t_onRestorePointers = void(__fastcall*)(settlementStruct* _this, int stub);
using t_onAttachRegionSettlement = void(__fastcall*)(stratMap* _this, int stub, int regionID, settlementStruct* settlement);
using t_onSetPreBattleWithdrawal = void(__fastcall*)(battleDataS* _this, int stub, bool withdraw);
using t_onBattleInstigate = void(__fastcall*)(battleDataS* _this, int stub, character* attacker, character* defender, battleType type, bool nightBattle, bool withdraw);


namespace new_events
{
    extern t_onGameInit o_onGameInit;
    extern t_onReadEDU o_onReadEDU;
    extern t_onGetUnitFormationString o_onGetUnitFormationString;
    extern t_onAutosave o_onAutosave;
    extern t_onQuickLoading o_onQuickLoading;
    extern t_onSaveCreate o_onSaveCreate;
    extern t_onSaveLoad o_onSaveLoad;
    extern t_onKillFaction o_onKillFaction;
    extern t_onKillUnitInArmy o_onKillUnitInArmy;
    extern t_onKillUnit o_onKillUnit;
    extern t_onKillCharacter o_onKillCharacter;
    extern t_onConsoleError o_onConsoleError;
    extern t_onTeleport o_onReposition;
    extern t_onAttackArmy o_onAttackArmy;
    extern t_onAttackFort o_onAttackFort;
    extern t_onAttackSettlement o_onAttackSettlement;
    extern t_onAttackPort o_onAttackPort;
    extern t_onDisembark o_onDisembark;
    extern t_onUnitLeavesArmy o_onUnitLeavesArmy;
    extern t_onActionMove o_onActionMove;
    extern t_onBattleStateChange o_onBattleStateChange;
    extern t_onBattleEnd o_onBattleEnd;
    extern t_onHistoricAndNewGameArmyLoading o_onHistoricAndNewGameArmyLoading;
    extern t_onBeginSiege o_onBeginSiege;
    extern t_onHistoricBattleAndNewGameLoading o_onHistoricBattleAndNewGameLoading;
    extern t_getRegionByCoords o_getRegionByCoords;
    extern t_onMap_rwmLoaded o_onMap_rwmLoaded;
    extern t_onCheckUnitBattleStatus o_onCheckUnitBattleStatus;
    extern t_onCharacterCreated o_onCharacterCreated;
    extern t_onCharacterCreated2 o_onCharacterCreated2;
    extern t_onRebelGarrisonCreated o_onRebelGarrisonCreated;
    extern t_onCreateAllScripts o_onCreateAllScripts;
    extern t_onCreateScriptFromFile o_onCreateScriptFromFile;
    extern t_onExecuteScript o_onExecuteScript;
    extern t_onConsoleExecute o_onConsoleExecute;
    extern t_onCreateDescrFile o_onCreateDescrFile;
    extern t_onNewGameStart o_onNewGameStart;
    extern t_onCampaignMapLoaded o_onCampaignMapLoaded;
    extern t_onChangeTurnNum o_onChangeTurnNum;
    extern t_onSetVassal o_onSetVassal;
    extern t_onPseudoPreFactionTurnStart o_onPseudoPreFactionTurnStart;
    extern t_onCreateCandidateMarrying o_onCreateCandidateMarrying;
    extern t_onDaughterReadyMarryHusband o_onDaughterReadyMarryHusband;
    extern t_onStartFamilyRound o_onStartFamilyRound;
    extern t_onLoadEDU o_onLoadEDU;
    extern t_onTransitionToBattleFromStratMap o_onTransitionToBattleFromStratMap;
    extern t_onOpenFile o_onOpenFile;
    extern t_onGiveUnitToArmy o_onGiveUnitToArmy;
    extern t_onCreateUnit o_onCreateUnit;
    extern t_onCreateUnit2 o_onCreateUnit2;
    extern t_onCreateUnit3 o_onCreateUnit3;
    extern t_onCreateUnit4 o_onCreateUnit4;
    extern t_onSetBattleUnitModels o_onSetBattleUnitModels;
    extern t_onCreateArmy o_onCreateArmy;
    extern t_onSetBodyguardUnit o_onSetBodyguardUnit;
    extern t_onRestorePointers o_onRestorePointers;
    extern t_onAttachRegionSettlement o_onAttachRegionSettlement;
    extern t_onSetPreBattleWithdrawal o_onSetPreBattleWithdrawal;
    extern t_onBattleInstigate o_onBattleInstigate;

    HRESULT __cdecl onGameInit();
    bool __fastcall onReadEDU(eduEntry* _this, int stub, descrFile* file);
    HRESULT __cdecl onGetUnitFormationString(const char* formation);
    HRESULT __fastcall onAutosave(campaign* _this, int stub, bool turn_end);
    HRESULT __cdecl onQuickLoading(UNICODE_STRING**& savePath);
    HRESULT __fastcall onSaveCreate(gameSaveStruct* _this, int stub, UNICODE_STRING**& savePath, bool param_2);
    HRESULT __fastcall onSaveLoad(void* _this, int stub, UNICODE_STRING**& savePath);
    HRESULT __fastcall onKillFaction(factionStruct* fac);
    HRESULT __fastcall onKillUnitInArmy(stackStruct* _this, int stub, unit* kUnit);
    HRESULT __fastcall onKillUnit(unit* _this);
    HRESULT __fastcall onKillCharacter(character* _this);
    HRESULT __cdecl onConsoleError(char* param_1, char* param_2);
    HRESULT __fastcall onTeleport(character* _this, int stub, int x, int y);
    HRESULT __fastcall onAttackArmy(stackStruct* _this, int stub, character* general, character_action* action);
    HRESULT __fastcall onAttackFort(stackStruct* _this, int stub, fortStruct* fort, character_action* action);
    HRESULT __fastcall onAttackSettlement(stackStruct* _this, int stub, settlementStruct* settlement, character_action* action);
    HRESULT __fastcall onAttackPort(stackStruct* _this, int stub, portBuildingStruct* port, character_action* action);
    HRESULT __fastcall onDisembark(character* _this, int stub, int x, int y);
    HRESULT __fastcall onUnitLeavesArmy(factionStruct* _this, int stub, unit**& leaveUnits, coords* targetCoords, bool merge);
    HRESULT __fastcall onActionMove(character* _this, int stub, character_action* action);
    HRESULT __fastcall onBattleStateChange(battleDataS* param_1);
    HRESULT __fastcall onBattleEnd(battleDataS* _this, int stub, int param_2);
    HRESULT __fastcall onHistoricAndNewGameArmyLoading(campaign* _this, int stub, descrFile* bFile, stackStruct* st, character* general, characterType charType, int factionID, stackStruct**& st2);
    HRESULT __fastcall onBeginSiege(character* _this, int stub, settlementStruct* settlement);
    HRESULT __fastcall onHistoricBattleAndNewGameLoading(campaign* _this, int stub, descrFile* bFile, stackStruct**& siegeStacks);
    regionStruct* __fastcall getRegionByCoords(campaign* _this, int stub, coords* coords);
    HRESULT __fastcall onMap_rwmLoaded(campaign* _this, int stub, UNICODE_STRING**& savePath);
    HRESULT __fastcall onCheckUnitBattleStatus(unit* _this, int stub, battleStatus* status);
    character* __cdecl onCharacterCreated(characterType charType, factionStruct* faction, int age, const char* name, const char* surname, int subFaction, const char* portrait, int x, int y);
    character* __cdecl onCharacterCreated2(descrFile* bFile, factionStruct* faction, int age, const char* name, const char* surname, int subFaction, const char* portrait, int x, int y);
    stackStruct* __fastcall onRebelGarrisonCreated(settlementStruct* _this, int stub, int param_1, bool param_2, int param_3, int originalFactionId);
    HRESULT __fastcall onCreateAllScripts(scriptClass* _this, int stub, descrFile* file, const char* endWord);
    scriptClass* __fastcall onCreateScriptFromFile(scriptClass* _this, int stub, descrFile* file);
    scriptResult __fastcall onExecuteScript(scriptClass* script);
    bool __fastcall onConsoleExecute(void* _this, int stub, const char* cmd, char* param_3);
    HRESULT __fastcall onCreateDescrFile(descrFile* _this, int stub, UNICODE_STRING**& file, int param_2);
    HRESULT __fastcall onNewGameStart(campaign* camp);
    bool __fastcall onCampaignMapLoaded(campaign* _this, int stub, int param_2);
    HRESULT __fastcall onChangeTurnNum(campaign* camp);
    void __fastcall onSetVassal(void* _this, int stub, int vassalID, int suzerainID);
    void __fastcall onPseudoPreFactionTurnStart(factionStruct* _this, int stub);
    namedCharacter* __fastcall onCreateCandidateMarrying(namedCharacter* daughter, int stub);
    int __cdecl onDaughterReadyMarryHusband(namedCharacter* daughter, namedCharacter* new_husband, marriageOption* mo);
    void __fastcall onStartFamilyRound(family* family);
    bool __fastcall onLoadEDU(unitDb* _this, int stub, const char* file);
    int __fastcall onTransitionToBattleFromStratMap(void* _this, int stub, int type);
    HRESULT __cdecl onOpenFile(char* file);
    HRESULT __fastcall onGiveUnitToArmy(stackStruct* _this, int stub, unit* un, unit* add_after);
    unit* __fastcall onCreateUnit(unitDb* _this, int stub, regionStruct* region, int index, int factionID, int ability, int soldiers, int armour_lvl, int weapon_lvl);
    unit* __fastcall onCreateUnit2(unitDb* _this, int stub, regionStruct* region, int index, int factionID, int ability, int soldiers); 
    unit* __fastcall onCreateUnit3(unitDb* _this, int stub, regionStruct* region, nameAndHash* ID, int factionID, int ability);
    unit* __fastcall onCreateUnit4(unitDb* _this, int stub, regionStruct* region, nameAndHash* ID, int factionID, int ability, int soldiers, int armour_lvl, int weapon_lvl);
    HRESULT __fastcall onSetBattleUnitModels(unitDb* _this, int stub);
    stackStruct* __fastcall onCreateArmy(factionStruct* _this, int stub, character* general, bool isNavy);
    unit* __fastcall onSetBodyguardUnit(stackStruct* _this, int stub, character* general, int exp, int weapon_lvl, int armour_lvl, eduEntry* ud);
    void __fastcall onRestorePointers(settlementStruct* _this, int stub);
    void __fastcall onAttachRegionSettlement(stratMap* _this, int stub, int regionID, settlementStruct* settlement);
    void __fastcall onSetPreBattleWithdrawal(battleDataS* _this, int stub, bool withdraw);
    void __fastcall onBattleInstigate(battleDataS* _this, int stub, character* attacker, character* defender, battleType type, bool nightBattle, bool withdraw);

	void initNewEvents();
	void deInitNewEvents();

	void onDllProcessAttach();
	void onDllProcessDetach();
	bool onInit(bool result);
	void onCampaignMapUnloaded();

    void setAncLimit(uint8_t limit);
    void callSaveLoad(UNICODE_STRING**& savePath);
    void callSaveCreate(UNICODE_STRING**& savePath);
    void callSaveLoad(const char* savePath);
    void callSaveCreate(const char* savePath);
    character* createCharacter(characterType charType, factionStruct* faction, int age, const char* name, const char* surname, int subFaction, const char* portrait, int xCoord, int yCoord);
    namedCharacter* createCandidateMarrying(namedCharacter* daughter);
    void callScript(const char* scriptName);
    void callScriptFromFile(const char* fileName);
    void quitGame();

    void scriptCommand(const char* scriptName, const char* arg);

    bool createEOPunit(const char* fileName, int newIdx);
    extern bool sap_point_fix;

    void testGameEvents();

#ifdef FACTION_LIMIT_TESTS
    void test_onCampaignMapLoaded(campaign* _this, int stub, int file);
#endif // FACTION_LIMIT_TESTS
}





















