#include "new_event.h"
#include "../../differentFunctions/stringThings.h"
#include "../hotSeat/createBattle.h"
#include "../helper_functions.h"
#include "../hotSeat/hotSeatCampaign.h"
#include <regex>
#include <fstream>
#include "../hotSeat/createBattleResult.h"
#include "../../differentFunctions/dm_assert.h"
#include "../../differentFunctions/encryption.h"
#include "../../eopUnits.h"
#include "../../tacticalMapViewer.h"
#include "../../eopSettlements.h"

using namespace std;

namespace new_events
{
    t_onGameInit o_onGameInit = nullptr;
    t_onReadEDU o_onReadEDU = nullptr;
    t_onGetUnitFormationString o_onGetUnitFormationString = nullptr;
    t_onAutosave o_onAutosave = nullptr;
    t_onQuickLoading o_onQuickLoading = nullptr;
    t_onSaveCreate o_onSaveCreate = nullptr;
    t_onSaveLoad o_onSaveLoad = nullptr;
    t_onKillFaction o_onKillFaction = nullptr;
    t_onKillUnitInArmy o_onKillUnitInArmy = nullptr;
    t_onKillUnit o_onKillUnit = nullptr;
    t_onKillCharacter o_onKillCharacter = nullptr;
    t_onConsoleError o_onConsoleError = nullptr;
    t_onTeleport o_onReposition = nullptr;
    t_onAttackArmy o_onAttackArmy = nullptr;
    t_onAttackFort o_onAttackFort = nullptr;
    t_onAttackSettlement o_onAttackSettlement = nullptr;
    t_onAttackPort o_onAttackPort = nullptr;
    t_onDisembark o_onDisembark = nullptr;
    t_onUnitLeavesArmy o_onUnitLeavesArmy = nullptr;
    t_onActionMove o_onActionMove = nullptr;
    t_onBattleStateChange o_onBattleStateChange = nullptr;
    t_onBattleEnd o_onBattleEnd = nullptr;
    t_onHistoricAndNewGameArmyLoading o_onHistoricAndNewGameArmyLoading = nullptr;
    t_onBeginSiege o_onBeginSiege = nullptr;
    t_onHistoricBattleAndNewGameLoading o_onHistoricBattleAndNewGameLoading = nullptr;
    t_getRegionByCoords o_getRegionByCoords = nullptr;
    t_onMap_rwmLoaded o_onMap_rwmLoaded = nullptr;
    t_onCheckUnitBattleStatus o_onCheckUnitBattleStatus = nullptr;
    t_onCharacterCreated o_onCharacterCreated = nullptr;
    t_onCharacterCreated2 o_onCharacterCreated2 = nullptr;
    t_onRebelGarrisonCreated o_onRebelGarrisonCreated = nullptr;
    t_onCreateAllScripts o_onCreateAllScripts = nullptr;
    t_onCreateScriptFromFile o_onCreateScriptFromFile = nullptr;
    t_onExecuteScript o_onExecuteScript = nullptr;
    t_onConsoleExecute o_onConsoleExecute = nullptr;
    t_onCreateDescrFile o_onCreateDescrFile = nullptr;
    t_onNewGameStart o_onNewGameStart = nullptr;
    t_onCampaignMapLoaded o_onCampaignMapLoaded = nullptr;
    t_onChangeTurnNum o_onChangeTurnNum = nullptr;
    t_onSetVassal o_onSetVassal = nullptr;
    t_onPseudoPreFactionTurnStart o_onPseudoPreFactionTurnStart = nullptr;
    t_onCreateCandidateMarrying o_onCreateCandidateMarrying = nullptr;
    t_onDaughterReadyMarryHusband o_onDaughterReadyMarryHusband = nullptr;
    t_onStartFamilyRound o_onStartFamilyRound = nullptr;
    t_onLoadEDU o_onLoadEDU = nullptr;
    t_onTransitionToBattleFromStratMap o_onTransitionToBattleFromStratMap = nullptr;
    t_onOpenFile o_onOpenFile = nullptr;
    t_onGiveUnitToArmy o_onGiveUnitToArmy = nullptr;
    t_onCreateUnit o_onCreateUnit = nullptr;
    t_onCreateUnit2 o_onCreateUnit2 = nullptr;
    t_onCreateUnit3 o_onCreateUnit3 = nullptr;
    t_onCreateUnit4 o_onCreateUnit4 = nullptr;
    t_onSetBattleUnitModels o_onSetBattleUnitModels = nullptr;
    t_onCreateArmy o_onCreateArmy = nullptr;
    t_onSetBodyguardUnit o_onSetBodyguardUnit = nullptr;
    t_onRestorePointers o_onRestorePointers = nullptr;
    t_onAttachRegionSettlement o_onAttachRegionSettlement = nullptr;
    t_onSetPreBattleWithdrawal o_onSetPreBattleWithdrawal = nullptr;
    t_onBattleInstigate o_onBattleInstigate = nullptr;


    void initNewEvents()
    {
        LOG_ALWAYS(RELEASE, "initNewEvents()");


        o_onGameInit = (t_onGameInit)offsets.onGameInit;
        DETOUR_ATTACH(&(PVOID&)o_onGameInit, onGameInit);

        o_onReadEDU = (t_onReadEDU)offsets.onReadEDU;
        DETOUR_ATTACH(&(PVOID&)o_onReadEDU, onReadEDU);

        o_onGetUnitFormationString = (t_onGetUnitFormationString)offsets.onGetUnitFormationString;
        DETOUR_ATTACH(&(PVOID&)o_onGetUnitFormationString, onGetUnitFormationString);

        o_onAutosave = (t_onAutosave)offsets.onAutosave;
        DETOUR_ATTACH(&(PVOID&)o_onAutosave, onAutosave);

        o_onQuickLoading = (t_onQuickLoading)offsets.onQuickLoading;
        DETOUR_ATTACH(&(PVOID&)o_onQuickLoading, onQuickLoading);

        o_onSaveCreate = (t_onSaveCreate)offsets.onSaveCreate;
        DETOUR_ATTACH(&(PVOID&)o_onSaveCreate, onSaveCreate);

        o_onSaveLoad = (t_onSaveLoad)offsets.onSaveLoad;
        DETOUR_ATTACH(&(PVOID&)o_onSaveLoad, onSaveLoad);

        o_onKillFaction = (t_onKillFaction)offsets.onKillFaction;
        DETOUR_ATTACH(&(PVOID&)o_onKillFaction, onKillFaction);

        o_onKillUnitInArmy = (t_onKillUnitInArmy)offsets.onKillUnitInArmy;
        DETOUR_ATTACH(&(PVOID&)o_onKillUnitInArmy, onKillUnitInArmy);

        o_onKillUnit = (t_onKillUnit)offsets.onKillUnit;
        DETOUR_ATTACH(&(PVOID&)o_onKillUnit, onKillUnit);

        o_onKillCharacter = (t_onKillCharacter)offsets.onKillCharacter;
        DETOUR_ATTACH(&(PVOID&)o_onKillCharacter, onKillCharacter);

        o_onReposition = (t_onTeleport)offsets.onTeleport;
        DETOUR_ATTACH(&(PVOID&)o_onReposition, onTeleport);

        o_onActionMove = (t_onActionMove)offsets.onActionMove;
        DETOUR_ATTACH(&(PVOID&)o_onActionMove, onActionMove);

        o_onAttackSettlement = (t_onAttackSettlement)offsets.onAttackSettlement;
        DETOUR_ATTACH(&(PVOID&)o_onAttackSettlement, onAttackSettlement);

        o_onAttackPort = (t_onAttackPort)offsets.onAttackPort;
        DETOUR_ATTACH(&(PVOID&)o_onAttackPort, onAttackPort);

        o_onAttackFort = (t_onAttackFort)offsets.onAttackFort;
        DETOUR_ATTACH(&(PVOID&)o_onAttackFort, onAttackFort);

        o_onAttackArmy = (t_onAttackArmy)offsets.onAttackArmy;
        DETOUR_ATTACH(&(PVOID&)o_onAttackArmy, onAttackArmy);

        o_onUnitLeavesArmy = (t_onUnitLeavesArmy)offsets.onUnitLeavesArmy;
        DETOUR_ATTACH(&(PVOID&)o_onUnitLeavesArmy, onUnitLeavesArmy);

        o_onDisembark = (t_onDisembark)offsets.onDisembark;
        DETOUR_ATTACH(&(PVOID&)o_onDisembark, onDisembark);

        o_onBattleStateChange = (t_onBattleStateChange)offsets.onBattleStateChange;
        DETOUR_ATTACH(&(PVOID&)o_onBattleStateChange, onBattleStateChange);

        o_onBattleEnd = (t_onBattleEnd)offsets.onBattleEnd;
        DETOUR_ATTACH(&(PVOID&)o_onBattleEnd, onBattleEnd);

        o_onHistoricAndNewGameArmyLoading = (t_onHistoricAndNewGameArmyLoading)offsets.onHistoricAndNewGameArmyLoading;
        DETOUR_ATTACH(&(PVOID&)o_onHistoricAndNewGameArmyLoading, onHistoricAndNewGameArmyLoading);

        o_onBeginSiege = (t_onBeginSiege)offsets.onBeginSiege;
        DETOUR_ATTACH(&(PVOID&)o_onBeginSiege, onBeginSiege);

        o_onHistoricBattleAndNewGameLoading = (t_onHistoricBattleAndNewGameLoading)offsets.onHistoricBattleAndNewGameLoading;
        DETOUR_ATTACH(&(PVOID&)o_onHistoricBattleAndNewGameLoading, onHistoricBattleAndNewGameLoading);

        o_getRegionByCoords = (t_getRegionByCoords)offsets.getRegionByCoords;
        DETOUR_ATTACH(&(PVOID&)o_getRegionByCoords, getRegionByCoords);

        o_onMap_rwmLoaded = (t_onMap_rwmLoaded)offsets.onMap_rwmLoaded;
        DETOUR_ATTACH(&(PVOID&)o_onMap_rwmLoaded, onMap_rwmLoaded);

        o_onCheckUnitBattleStatus = (t_onCheckUnitBattleStatus)offsets.onCheckUnitBattleStatus;
        DETOUR_ATTACH(&(PVOID&)o_onCheckUnitBattleStatus, onCheckUnitBattleStatus);

        o_onCharacterCreated = (t_onCharacterCreated)offsets.onCharacterCreated;
        DETOUR_ATTACH(&(PVOID&)o_onCharacterCreated, onCharacterCreated);

        o_onCharacterCreated2 = (t_onCharacterCreated2)offsets.onCharacterCreated2;
        DETOUR_ATTACH(&(PVOID&)o_onCharacterCreated2, onCharacterCreated2);

        o_onRebelGarrisonCreated = (t_onRebelGarrisonCreated)offsets.onRebelGarrisonCreated;
        DETOUR_ATTACH(&(PVOID&)o_onRebelGarrisonCreated, onRebelGarrisonCreated);

        o_onExecuteScript = (t_onExecuteScript)offsets.onExecuteScript;
        DETOUR_ATTACH(&(PVOID&)o_onExecuteScript, onExecuteScript);

        o_onConsoleError = (t_onConsoleError)offsets.onConsoleError;
        DETOUR_ATTACH(&(PVOID&)o_onConsoleError, onConsoleError);

        o_onConsoleExecute = (t_onConsoleExecute)offsets.onConsoleExecute;
        DETOUR_ATTACH(&(PVOID&)o_onConsoleExecute, onConsoleExecute);

        o_onCreateScriptFromFile = (t_onCreateScriptFromFile)offsets.onCreateScriptFromFile;
        DETOUR_ATTACH(&(PVOID&)o_onCreateScriptFromFile, onCreateScriptFromFile);

        o_onCreateAllScripts = (t_onCreateAllScripts)offsets.onCreateAllScripts;
        DETOUR_ATTACH(&(PVOID&)o_onCreateAllScripts, onCreateAllScripts);

        o_onCreateDescrFile = (t_onCreateDescrFile)offsets.onCreateDescrFile;
        DETOUR_ATTACH(&(PVOID&)o_onCreateDescrFile, onCreateDescrFile);

        o_onNewGameStart = (t_onNewGameStart)offsets.onNewGameStart;
        DETOUR_ATTACH(&(PVOID&)o_onNewGameStart, onNewGameStart);

        o_onCampaignMapLoaded = (t_onCampaignMapLoaded)offsets.onCampaignMapLoaded;
        DETOUR_ATTACH(&(PVOID&)o_onCampaignMapLoaded, onCampaignMapLoaded);

        o_onChangeTurnNum = (t_onChangeTurnNum)offsets.onChangeTurnNum;
        DETOUR_ATTACH(&(PVOID&)o_onChangeTurnNum, onChangeTurnNum);

        o_onSetVassal = (t_onSetVassal)offsets.onSetVassal;
        DETOUR_ATTACH(&(PVOID&)o_onSetVassal, onSetVassal);

        o_onPseudoPreFactionTurnStart = (t_onPseudoPreFactionTurnStart)offsets.onPseudoPreFactionTurnStart;
        DETOUR_ATTACH(&(PVOID&)o_onPseudoPreFactionTurnStart, onPseudoPreFactionTurnStart);

        o_onLoadEDU = (t_onLoadEDU)offsets.onLoadEDU;
        DETOUR_ATTACH(&(PVOID&)o_onLoadEDU, onLoadEDU);

        o_onCreateCandidateMarrying = (t_onCreateCandidateMarrying)offsets.onCreateCandidateMarrying;
        DETOUR_ATTACH(&(PVOID&)o_onCreateCandidateMarrying, onCreateCandidateMarrying);

        o_onDaughterReadyMarryHusband = (t_onDaughterReadyMarryHusband)offsets.onDaughterReadyMarryHusband;
        DETOUR_ATTACH(&(PVOID&)o_onDaughterReadyMarryHusband, onDaughterReadyMarryHusband);

        o_onStartFamilyRound = (t_onStartFamilyRound)offsets.onStartFamilyRound;
        DETOUR_ATTACH(&(PVOID&)o_onStartFamilyRound, onStartFamilyRound);

        o_onTransitionToBattleFromStratMap = (t_onTransitionToBattleFromStratMap)offsets.onTransitionToBattleFromStratMap;
        DETOUR_ATTACH(&(PVOID&)o_onTransitionToBattleFromStratMap, onTransitionToBattleFromStratMap);

        o_onOpenFile = (t_onOpenFile)offsets.onOpenFile;
        DETOUR_ATTACH(&(PVOID&)o_onOpenFile, onOpenFile);

        o_onCreateUnit3 = (t_onCreateUnit3)offsets.onCreateUnit3;
        DETOUR_ATTACH(&(PVOID&)o_onCreateUnit3, onCreateUnit3);

        o_onCreateUnit4 = (t_onCreateUnit4)offsets.onCreateUnit4;
        DETOUR_ATTACH(&(PVOID&)o_onCreateUnit4, onCreateUnit4);

        o_onSetBattleUnitModels = (t_onSetBattleUnitModels)offsets.onSetBattleUnitModels;
        DETOUR_ATTACH(&(PVOID&)o_onSetBattleUnitModels, onSetBattleUnitModels);

        o_onCreateUnit2 = (t_onCreateUnit2)offsets.onCreateUnit2;
        DETOUR_ATTACH(&(PVOID&)o_onCreateUnit2, onCreateUnit2);

        o_onGiveUnitToArmy = (t_onGiveUnitToArmy)offsets.onGiveUnitToArmy;
        DETOUR_ATTACH(&(PVOID&)o_onGiveUnitToArmy, onGiveUnitToArmy);

        o_onCreateUnit = (t_onCreateUnit)offsets.onCreateUnit;
        DETOUR_ATTACH(&(PVOID&)o_onCreateUnit, onCreateUnit);

        o_onSetBodyguardUnit = (t_onSetBodyguardUnit)offsets.onSetBodyguardUnit;
        DETOUR_ATTACH(&(PVOID&)o_onSetBodyguardUnit, onSetBodyguardUnit);

        o_onCreateArmy = (t_onCreateArmy)offsets.onCreateArmy;
        DETOUR_ATTACH(&(PVOID&)o_onCreateArmy, onCreateArmy);

        o_onRestorePointers = (t_onRestorePointers)offsets.onRestorePointers;
        DETOUR_ATTACH(&(PVOID&)o_onRestorePointers, onRestorePointers);

        o_onAttachRegionSettlement = (t_onAttachRegionSettlement)offsets.onAttachRegionSettlement;
        DETOUR_ATTACH(&(PVOID&)o_onAttachRegionSettlement, onAttachRegionSettlement);

        o_onSetPreBattleWithdrawal = (t_onSetPreBattleWithdrawal)offsets.onSetPreBattleWithdrawal;
        DETOUR_ATTACH(&(PVOID&)o_onSetPreBattleWithdrawal, onSetPreBattleWithdrawal);

        o_onBattleInstigate = (t_onBattleInstigate)offsets.onBattleInstigate;
        DETOUR_ATTACH(&(PVOID&)o_onBattleInstigate, onBattleInstigate);


        saveFiles.deleteAll();
    }


    void deInitNewEvents()
    {
        LOG_ALWAYS(RELEASE, "deInitNewEvents()");


        DETOUR_DETACH(&(PVOID&)o_onGameInit, onGameInit);
        DETOUR_DETACH(&(PVOID&)o_onReadEDU, onReadEDU);
        DETOUR_DETACH(&(PVOID&)o_onGetUnitFormationString, onGetUnitFormationString);
        DETOUR_DETACH(&(PVOID&)o_onAutosave, onAutosave);
        DETOUR_DETACH(&(PVOID&)o_onQuickLoading, onQuickLoading);
        DETOUR_DETACH(&(PVOID&)o_onSaveCreate, onSaveCreate);
        DETOUR_DETACH(&(PVOID&)o_onSaveLoad, onSaveLoad);
        DETOUR_DETACH(&(PVOID&)o_onKillFaction, onKillFaction);
        DETOUR_DETACH(&(PVOID&)o_onKillUnitInArmy, onKillUnitInArmy);
        DETOUR_DETACH(&(PVOID&)o_onKillUnit, onKillUnit);
        DETOUR_DETACH(&(PVOID&)o_onKillCharacter, onKillCharacter);
        DETOUR_DETACH(&(PVOID&)o_onReposition, onTeleport);
        DETOUR_DETACH(&(PVOID&)o_onConsoleError, onConsoleError);
        DETOUR_DETACH(&(PVOID&)o_onActionMove, onActionMove);
        DETOUR_DETACH(&(PVOID&)o_onAttackSettlement, onAttackSettlement);
        DETOUR_DETACH(&(PVOID&)o_onAttackPort, onAttackPort);
        DETOUR_DETACH(&(PVOID&)o_onAttackFort, onAttackFort);
        DETOUR_DETACH(&(PVOID&)o_onAttackArmy, onAttackArmy);
        DETOUR_DETACH(&(PVOID&)o_onUnitLeavesArmy, onUnitLeavesArmy);
        DETOUR_DETACH(&(PVOID&)o_onDisembark, onDisembark);
        DETOUR_DETACH(&(PVOID&)o_onBattleStateChange, onBattleStateChange);
        DETOUR_DETACH(&(PVOID&)o_onBattleEnd, onBattleEnd);
        DETOUR_DETACH(&(PVOID&)o_onHistoricAndNewGameArmyLoading, onHistoricAndNewGameArmyLoading);
        DETOUR_DETACH(&(PVOID&)o_onBeginSiege, onBeginSiege);
        DETOUR_DETACH(&(PVOID&)o_onHistoricBattleAndNewGameLoading, onHistoricBattleAndNewGameLoading);
        DETOUR_DETACH(&(PVOID&)o_getRegionByCoords, getRegionByCoords);
        DETOUR_DETACH(&(PVOID&)o_onMap_rwmLoaded, onMap_rwmLoaded);
        DETOUR_DETACH(&(PVOID&)o_onCheckUnitBattleStatus, onCheckUnitBattleStatus);
        DETOUR_DETACH(&(PVOID&)o_onCharacterCreated, onCharacterCreated);
        DETOUR_DETACH(&(PVOID&)o_onCharacterCreated2, onCharacterCreated2);
        DETOUR_DETACH(&(PVOID&)o_onRebelGarrisonCreated, onRebelGarrisonCreated);
        DETOUR_DETACH(&(PVOID&)o_onExecuteScript, onExecuteScript);
        DETOUR_DETACH(&(PVOID&)o_onConsoleExecute, onConsoleExecute);
        DETOUR_DETACH(&(PVOID&)o_onCreateScriptFromFile, onCreateScriptFromFile);
        DETOUR_DETACH(&(PVOID&)o_onCreateAllScripts, onCreateAllScripts);
        DETOUR_DETACH(&(PVOID&)o_onCreateDescrFile, onCreateDescrFile);
        DETOUR_DETACH(&(PVOID&)o_onNewGameStart, onNewGameStart);
        DETOUR_DETACH(&(PVOID&)o_onCampaignMapLoaded, onCampaignMapLoaded);
        DETOUR_DETACH(&(PVOID&)o_onChangeTurnNum, onChangeTurnNum);
        DETOUR_DETACH(&(PVOID&)o_onSetVassal, onSetVassal);
        DETOUR_DETACH(&(PVOID&)o_onPseudoPreFactionTurnStart, onPseudoPreFactionTurnStart);
        DETOUR_DETACH(&(PVOID&)o_onLoadEDU, onLoadEDU);
        DETOUR_DETACH(&(PVOID&)o_onCreateCandidateMarrying, onCreateCandidateMarrying);
        DETOUR_DETACH(&(PVOID&)o_onDaughterReadyMarryHusband, onDaughterReadyMarryHusband);
        DETOUR_DETACH(&(PVOID&)o_onStartFamilyRound, onStartFamilyRound);
        DETOUR_DETACH(&(PVOID&)o_onTransitionToBattleFromStratMap, onTransitionToBattleFromStratMap);
        DETOUR_DETACH(&(PVOID&)o_onOpenFile, onOpenFile);
        DETOUR_DETACH(&(PVOID&)o_onCreateUnit3, onCreateUnit3);
        DETOUR_DETACH(&(PVOID&)o_onCreateUnit4, onCreateUnit4);
        DETOUR_DETACH(&(PVOID&)o_onSetBattleUnitModels, onSetBattleUnitModels);
        DETOUR_DETACH(&(PVOID&)o_onCreateUnit2, onCreateUnit2);
        DETOUR_DETACH(&(PVOID&)o_onGiveUnitToArmy, onGiveUnitToArmy);
        DETOUR_DETACH(&(PVOID&)o_onCreateUnit, onCreateUnit);
        DETOUR_DETACH(&(PVOID&)o_onSetBodyguardUnit, onSetBodyguardUnit);
        DETOUR_DETACH(&(PVOID&)o_onCreateArmy, onCreateArmy);
        DETOUR_DETACH(&(PVOID&)o_onRestorePointers, onRestorePointers);
        DETOUR_DETACH(&(PVOID&)o_onAttachRegionSettlement, onAttachRegionSettlement);
        DETOUR_DETACH(&(PVOID&)o_onSetPreBattleWithdrawal, onSetPreBattleWithdrawal);
        DETOUR_DETACH(&(PVOID&)o_onBattleInstigate, onBattleInstigate);


        saveFiles.deleteAll();
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool testEDU = false;
    bool unlockUnitSizelimit = true;
    bool sap_point_fix = false;
    int settCoordX = 0;
    int settCoordY = 0;
    descrFile* testbFile = nullptr;
    scriptClass* rememberScriptClass = nullptr;
    


    HRESULT __cdecl onGameInit()
    {
        LOG_ALWAYS(RELEASE, "onGameInit()");

        HRESULT result = o_onGameInit();

        encryption::getFilesSum();

        return result;
    }

    bool __fastcall onReadEDU(eduEntry* _this, int stub, descrFile* file)
    {
        while (testEDU && !IsDebuggerPresent())
        {
            Sleep(100);
        }

 //     if (qa.isUnitLimitTest)
 //     {
 //         qa.isUnitLimitTest = false;
 //     }


        if (unlockUnitSizelimit)
        {
            unlockUnitSizelimit = false;
            LOG_ALWAYS(RELEASEFULL, "unlockUnitSizelimit");
 
            BYTE fixMin = 0x01; // 1 in EDU, 4 in game at maximum settings   
            const DWORD addressMin = 0x008D3E1C;
            memory::Write(&fixMin, addressMin, 1);

            BYTE fixMax = 0x78; // 120 in EDU, 480 in game at maximum settings   
            const DWORD addressMax = 0x008D3E25;
            memory::Write(&fixMax, addressMax, 1);


            // total limit 
            BYTE fixTot = 0xE0; // 480 in game at maximum settings   
            const DWORD addressTot1 = 0x0044CA66;
            const DWORD addressTot2 = 0x0044CA7C;
            const DWORD addressTot3 = 0x008D3E4B;
            memory::Write(&fixTot, addressTot1, 1);
            memory::Write(&fixTot, addressTot2, 1);
            memory::Write(&fixTot, addressTot3, 1);
        }

        bool result = o_onReadEDU(_this, stub, file);

        eduFormation.type[_this->Index] = eduFormation.buffer;

        LOG_ALWAYS(DEBUG, "onReadEDU(" + string(_this->Type) +  ", index: " + to_string(_this->Index) + ", formation: " + string(eduFormation.buffer) + ")");
        LOG_ALWAYS(RELEASEFULL, "onReadEDU(" + string(_this->Type) + ")");

        return result;
    }

    HRESULT __cdecl onGetUnitFormationString(const char* formation)
    {
        LOG_ALWAYS(BUGTEST, "onGetUnitFormationString(" + string(formation) + ")");

        eduFormation.buffer = string(formation);

        return o_onGetUnitFormationString(formation);
    }

    HRESULT __fastcall onAutosave(campaign* _this, int stub, bool turn_end)
    {
        HRESULT result = o_onAutosave(_this, stub, turn_end);

        string        save_type = "turn_start";
        if (turn_end) save_type = "turn_end";

        LOG_ALWAYS(RELEASEFULL, "onAutosave(" + save_type + ", currentDate: " + to_string(_this->currentDate) + ")");

        return result;
    }

    HRESULT __cdecl onQuickLoading(UNICODE_STRING**& savePath)
    {
        string save = uniToAnsi(savePath);

        LOG_ALWAYS(RELEASEFULL, "onQuickLoading(" + save + ")");

        return o_onQuickLoading(savePath);
    }

    HRESULT __fastcall onSaveCreate(gameSaveStruct* _this, int stub, UNICODE_STRING**& savePath, bool param_2)
    {
        string save = uniToAnsi(savePath);

        if (HOT_SEAT_CAMPAIGN.m_file_requester_scroll)
        {
           string saveStr = uniStringToStr(savePath);
            if (checNonStandardChar2(saveStr))
            {
                if (checNonStandardChar2(save))
                {
                    qa.modPatch = helper_functions::getModPatchName();
                    save = string(qa.modPatch) + "/saves/Last save - Use standard characters to save.sav";
                }
                createUniString(savePath, save.c_str());
                LOG_ALWAYS(RELEASEFULL, "[ERROR] onSaveCreate(" + saveStr + " >>> FIX >>> " + save + ")");
            }
        }
        HOT_SEAT_CAMPAIGN.m_file_requester_scroll = false;
        HOT_SEAT_CAMPAIGN.brokenSaveOnPreSave();


        LOG_ALWAYS(RELEASEFULL, "onSaveCreate(" + save + ")");
        HRESULT result = o_onSaveCreate(_this, stub, savePath, param_2);


        if (MoveFileExA(save.c_str(), "dmData\\temp\\temp_file", MOVEFILE_REPLACE_EXISTING))
        {
            saveFiles = saveFilesS();
            bool isHotSeatCampaign = HOT_SEAT_CAMPAIGN.onSave(save);
            EOP_SETTLEMENTS.onSave();

            saveFiles.files.push_back("dmData\\temp\\temp_file");
            if (!helper_functions::zip(save, saveFiles.files, save, save))
            {

            }
        }
        else
        {
            MessageBoxA(nullptr, save.c_str(), "save 1", MB_ICONWARNING);
        }
        saveFiles.deleteFiles();

        return result;
    }

    HRESULT __fastcall onSaveLoad(void* _this, int stub, UNICODE_STRING**& savePath)
    {
        string save = uniToAnsi(savePath);
        UNICODE_STRING** uniStr = NULL;
        LOG_ALWAYS(RELEASEFULL, "onSaveLoad(" + save + ")");

        saveFiles.deleteFiles();
 
        saveFiles.files = helper_functions::unzip(save, "dmData\\temp");
        createUniString(uniStr, "dmData\\temp\\temp_file");
        savePath = uniStr;

        EOP_SETTLEMENTS.m_is_save_load = true;

        bool isHotSeatCampaign = HOT_SEAT_CAMPAIGN.onLoad(save);
        HRESULT result = o_onSaveLoad(_this, stub, savePath);

        return result;
    }

    HRESULT __fastcall onKillFaction(factionStruct* fac)
    {
        HRESULT result = o_onKillFaction(fac);

        LOG_ALWAYS(RELEASEFULL, "onKillFaction(" + string(fac->factSmDescr->facName) + ")");

        return result;
    }

    HRESULT __fastcall onKillUnitInArmy(stackStruct* _this, int stub, unit* kUnit)
    {
        HRESULT result = o_onKillUnitInArmy(_this, stub, kUnit);

        LOG_ALWAYS(RELEASEFULL, "onKillUnitInArmy(" + string(kUnit->eduEntry->Type) + ")");

        return result;
    }

    HRESULT __fastcall onKillUnit(unit* _this)
    {
        HRESULT result = o_onKillUnit(_this);

        LOG_ALWAYS(RELEASEFULL, "onKillUnit(" + string(_this->eduEntry->Type) + ")");

        return result;
    }

    HRESULT __fastcall onKillCharacter(character* _this)
    {
        HRESULT result = o_onKillCharacter(_this);

        LOG_ALWAYS(RELEASEFULL, "onKillCharacter(" + string(_this->genChar->fullName) + ")");

        return result;
    }

    HRESULT __fastcall onTeleport(character* _this, int stub, int x, int y)
    {
        LOG_ALWAYS(DEVELOPMENT, "onTeleport()");
        return o_onReposition(_this, stub, x, y);
    }

    HRESULT __fastcall onAttackArmy(stackStruct* _this, int stub, character* general, character_action* action)
    {
        LOG_ALWAYS(RELEASEFULL, "onAttackArmy()");
        return o_onAttackArmy(_this, stub, general, action);
    }

    HRESULT __fastcall onAttackFort(stackStruct* _this, int stub, fortStruct* fort, character_action* action)
    {
        LOG_ALWAYS(RELEASEFULL, "onAttackFort()");
        return o_onAttackFort(_this, stub, fort, action);
    }

    HRESULT __fastcall onAttackSettlement(stackStruct* _this, int stub, settlementStruct* settlement, character_action* action)
    {
        LOG_ALWAYS(RELEASEFULL, "onAttackSettlement()");
        return o_onAttackSettlement(_this, stub, settlement, action);
    }

    HRESULT __fastcall onAttackPort(stackStruct* _this, int stub, portBuildingStruct* port, character_action* action)
    {
        LOG_ALWAYS(RELEASEFULL, "onAttackPort()");
        return o_onAttackPort(_this, stub, port, action);
    }

    // ВЫСАДКА 
    HRESULT __fastcall onDisembark(character* _this, int stub, int x, int y)
    {
        LOG_ALWAYS(RELEASEFULL, "onDisembark()");
        return o_onDisembark(_this, stub, x, y);
    }

    // юнит покидает армию   
    HRESULT __fastcall onUnitLeavesArmy(factionStruct* _this, int stub, unit**& leaveUnits, coords* targetCoords, bool merge)
    {
        LOG_ALWAYS(DEVELOPMENT, "onUnitLeavesArmy()");
        return o_onUnitLeavesArmy(_this, stub, leaveUnits, targetCoords, merge);
    }

    HRESULT __fastcall onActionMove(character* _this, int stub, character_action* action)
    {
    //	character_action* action_test = reinterpret_cast<character_action*>(0x006fdce8);

        LOG_ALWAYS(DEVELOPMENT, "onActionMove()");

        HRESULT result = o_onActionMove(_this, stub, action);
        return result;
    }

    /// BATTLE ///   
    HRESULT __fastcall onBattleStateChange(battleDataS* battle)
    {
        LOG_ALWAYS(RELEASEFULL, "onBattleStateChange(battleType: " + ds.battleTypeStr[battle->battleType] + ", battleState: " + ds.battleStateStr[battle->battleState] + ")");
        HRESULT result = o_onBattleStateChange(battle);

        if (!qa.gDataAll)
            helper_functions::getGameDataAll();

        battle_create::onBattleStateChange(battle);
        sap_point_fix = false;

        return result;
    }

    HRESULT __fastcall onBattleEnd(battleDataS* _this, int stub, int param_2)
    {
        LOG_ALWAYS(RELEASEFULL, "onBattleEnd(battleType: " + ds.battleTypeStr[_this->battleType] + ", battleState: " + ds.battleStateStr[_this->battleState] + ")");
        HRESULT result = o_onBattleEnd(_this, stub, param_2);

        battle_create::onBattleEnd(_this);
        sap_point_fix = false;

        return result;
    }

    static void getBattleCoords(char* text)
    {
        battleDataS* battle = helper_functions::getGameDataAll()->battleHandler;

        string line = text;
        string strCoords;
        smatch match;
        regex pattern(";;;coords(.*)");

        if (regex_search(line, match, pattern)) 
        {
            strCoords = match[1];

            strCoords.erase(std::remove(strCoords.begin(), strCoords.end(), '('), strCoords.end());
            strCoords.erase(std::remove(strCoords.begin(), strCoords.end(), ')'), strCoords.end());

            int pos = strCoords.find(",");
            settCoordX = stoi(strCoords.substr(0, pos));
            settCoordY = stoi(strCoords.substr(pos + 1));

            LOG_ALWAYS(RELEASE, "getBattleCoords(" + strCoords + ")");
        }
    }

    HRESULT __fastcall onHistoricAndNewGameArmyLoading(campaign* _this, int stub, descrFile* bFile, stackStruct* st, character* general, characterType charType, int factionID, stackStruct**& st2)
    {
        string fileName = uniStringToStr(bFile->file);
        LOG_ALWAYS(RELEASE, "onHistoricAndNewGameArmyLoading(faction: " + string(general->genChar->faction->factSmDescr->facName) + ", general: " + string(general->genChar->fullName) + ", generalType: " + ds.characterTypeStr[charType] + ", file: " + fileName + ")");
        HRESULT result = o_onHistoricAndNewGameArmyLoading(_this, stub, bFile, st, general, charType, factionID, st2);

        if (fileName.find("descr_battle.txt") != std::string::npos) 
        {
            if (general->armyLeaded->sapPoints > 0)
            {
                sap_point_fix = true;
                getBattleCoords(bFile->buffer);
            }

            battle_result::createMinorCharacters(general, fileName, testbFile);
        }

        return result;
    }

    HRESULT __fastcall onBeginSiege(character* _this, int stub, settlementStruct* settlement)
    {
        LOG_ALWAYS(RELEASEFULL, "onBeginSiege(character: " + string(_this->genChar->fullName) + ", settlement: " + string(settlement->name) + ")");

        return o_onBeginSiege(_this, stub, settlement);
    }

    HRESULT __fastcall onHistoricBattleAndNewGameLoading(campaign* _this, int stub, descrFile* bFile, stackStruct**& siegeStacks)
    {
        string fileName = uniStringToStr(bFile->file);
        LOG_ALWAYS(RELEASE, "onHistoricBattleAndNewGameLoading(" + fileName + ")");
        return o_onHistoricBattleAndNewGameLoading(_this, stub, bFile, siegeStacks);
    }

    HRESULT __fastcall onCheckUnitBattleStatus(unit* _this, int stub, battleStatus* status)
    {
        return o_onCheckUnitBattleStatus(_this, stub, status);
    }

    regionStruct* __fastcall getRegionByCoords(campaign* _this, int stub, coords* coords)
    {
        if (sap_point_fix)
        {
            coords->xCoord = settCoordX;
            coords->yCoord = settCoordY;
        }

        return o_getRegionByCoords(_this, stub, coords);
    }
    /// END BATTLE ///   


    HRESULT __fastcall onMap_rwmLoaded(campaign* _this, int stub, UNICODE_STRING**& savePath)
    {
        HRESULT result = o_onMap_rwmLoaded(_this, stub, savePath);

        string map_rwm = uniStringToStr(savePath);
        LOG_ALWAYS(RELEASEFULL, "onMap_rwmLoaded(" + map_rwm + ")");

        return result;
    }

    character* __cdecl onCharacterCreated(characterType charType, factionStruct* faction, int age, const char* name, const char* surname, int subFaction, const char* portrait, int x, int y)
    {
        string _name    = "NULL"; if (name)    _name    = name;
        string _surname = "NULL"; if (surname) _surname = surname;
        LOG_ALWAYS(RELEASEFULL, "onCharacterCreated(faction: " + string(faction->factSmDescr->facName) + ", characterType: " + ds.characterTypeStr[charType] + ", name: " + _name + ", surname: " + _surname + ")");

        character* result = o_onCharacterCreated(charType, faction, age, name, surname, subFaction, portrait, x, y);
        return result;
    }

    character* __cdecl onCharacterCreated2(descrFile* bFile, factionStruct* faction, int age, const char* name, const char* surname, int subFaction, const char* portrait, int x, int y)
    {
        string _name    = "NULL"; if (name)    _name    = name;
        string _surname = "NULL"; if (surname) _surname = surname;
        LOG_ALWAYS(RELEASEFULL, "onCharacterCreated2(faction: " + string(faction->factSmDescr->facName) + ", name: " + _name + ", surname: " + _surname + ")");

        testbFile = bFile;

        character* result = o_onCharacterCreated2(bFile, faction, age, name, surname, subFaction, portrait, x, y);
        return result;
    }

    stackStruct* __fastcall onRebelGarrisonCreated(settlementStruct* _this, int stub, int param_1, bool param_2, int param_3, int originalFactionId)
    {
        stackStruct* result = o_onRebelGarrisonCreated(_this, stub, param_1, param_2, param_3, originalFactionId);

        LOG_ALWAYS(RELEASEFULL, "onRebelGarrisonCreated(settlement: " + string(_this->name) + ", originalFactionId: " + to_string(originalFactionId) + ")");

        return result;
    }

    HRESULT __fastcall onCreateAllScripts(scriptClass* _this, int stub, descrFile* file, const char* endWord)
    {
        HRESULT result = o_onCreateAllScripts(_this, stub, file, endWord);
        rememberScriptClass = _this;

#ifdef _DEBUG
    	string fileName = uniToAnsi(file->file);
        LOG_ALWAYS(DEBUG, "onCreateAllScripts(" + fileName + ")");
#endif // _DEBUG

        return result;
    }

    scriptClass* __fastcall onCreateScriptFromFile(scriptClass* _this, int stub, descrFile* file)
    {
        string fileName = uniToAnsi(file->file);
        LOG_ALWAYS(RELEASEFULL, "onCreateScriptFromFile(" + fileName + ")");

        HOT_SEAT_CAMPAIGN.onCreateScriptFromFile(fileName);

        return o_onCreateScriptFromFile(_this, stub, file);
    }

    scriptResult __fastcall onExecuteScript(scriptClass* script)
    {
        LOG_ALWAYS(DEBUG, "onExecuteScript()");
        
        scriptResult result = o_onExecuteScript(script);
        return result;
    }

    HRESULT __cdecl onConsoleError(char* param_1, char* param_2)
    {
        LOG_ALWAYS(RELEASEFULL, "onConsoleError()");

        return o_onConsoleError(param_1, param_2);
    }

    // работает только при вызове через консоль игры - не через консоль проги(и скриптов игры?)   
    // undefined4 __thiscall FUN_00d911fc(int *param_1,char *param_2,int param_3) 
    bool __fastcall onConsoleExecute(void* _this, int stub, const char* cmd, char* param_3)
    {
	    if (!HOT_SEAT_CAMPAIGN.m_block_game_console || strcmp(cmd, "show_cursorstat") == 0)
	    {
            if (HOT_SEAT_CAMPAIGN.m_is_hot_seat_campaign)
            {
                HOT_SEAT_CAMPAIGN.log("CONSOLE(" + string(cmd) + " | " + HOT_SEAT_CAMPAIGN.m_faction_name[HOT_SEAT_CAMPAIGN.m_current_faction_id] + ")");
            }
            return o_onConsoleExecute(_this, stub, cmd, param_3);
	    }

	    if (HOT_SEAT_CAMPAIGN.m_keymaster_password_hash == stringToHash(cmd))
	    {
		    HOT_SEAT_CAMPAIGN.m_show_keymaster_console = true;
		    HOT_SEAT_CAMPAIGN.m_block_game_console     = false;

		    new_events::onConsoleError((char*)"Welcome, keymaster!", param_3);
		    return false;
	    }
	    else
	    {
            HOT_SEAT_CAMPAIGN.log("CONSOLE(" + string(cmd) + " | " + HOT_SEAT_CAMPAIGN.m_faction_name[HOT_SEAT_CAMPAIGN.m_current_faction_id] + " | CHEATER!)");
		    new_events::onConsoleError((char*)"CHEATER! :=) ", param_3);
		    return false;
	    }


        if (HOT_SEAT_CAMPAIGN.m_is_hot_seat_campaign)
        {
            HOT_SEAT_CAMPAIGN.log("CONSOLE(" + string(cmd) + " | " + HOT_SEAT_CAMPAIGN.m_faction_name[HOT_SEAT_CAMPAIGN.m_current_faction_id] + ")");
        }

        bool result = o_onConsoleExecute(_this, stub, cmd, param_3);
        LOG_ALWAYS(RELEASEFULL, "onConsoleExecute(" + string(cmd) + ")");
	    return result;
    }

    HRESULT __fastcall onCreateDescrFile(descrFile* _this, int stub, UNICODE_STRING**& file, int param_2)
    {
#ifdef _DEBUG
        string fileStr = uniToAnsi(file);
        LOG_ALWAYS(DEBUG, "onCreateDescrFile(" + fileStr + ")");
#endif // _DEBUG

        return o_onCreateDescrFile(_this, stub, file, param_2);
    }

    HRESULT __fastcall onNewGameStart(campaign* camp)
    {
        LOG_ALWAYS(RELEASE, "onNewGameStart()");

        battle_create::onCampaignMapLoaded(camp);
        HOT_SEAT_CAMPAIGN.onNewGameStart(camp);
        EOP_SETTLEMENTS.onNewGameStart(camp);

        return o_onNewGameStart(camp);
    }

    bool __fastcall onCampaignMapLoaded(campaign* _this, int stub, int param_2)
    {
        bool result = o_onCampaignMapLoaded(_this, stub, param_2);
        LOG_ALWAYS(RELEASE, "onCampaignMapLoaded(turnNumber: " + to_string(_this->turnNumber) + ")");

        battle_create::onCampaignMapLoaded(_this);
        HOT_SEAT_CAMPAIGN.onCampaignMapLoaded(_this);
        EOP_SETTLEMENTS.onLoad(_this);

        saveFiles.deleteFiles();

#ifdef FACTION_LIMIT_TESTS
        test_onCampaignMapLoaded(_this, stub, param_2);
#endif // FACTION_LIMIT_TESTS

        return result;
    }

    HRESULT __fastcall onChangeTurnNum(campaign* camp)
    {
        HRESULT result = o_onChangeTurnNum(camp);
        LOG_ALWAYS(RELEASE, "onChangeTurnNum(" + to_string(camp->turnNumber) + ")");
    //  string file = uniStringToStr(camp->currentDescrFile);
        return result;
    }

    void __fastcall onSetVassal(void* _this, int stub, int vassalID, int suzerainID)
    {
        LOG_ALWAYS(RELEASEFULL, "onSetVassal(vassalID: " + to_string(vassalID) + ", suzerainID: " + to_string(suzerainID) + ")");
        return o_onSetVassal(_this, stub, vassalID, suzerainID);
    }

    void __fastcall onPseudoPreFactionTurnStart(factionStruct* _this, int stub)
    {
        LOG_ALWAYS(RELEASEFULL, "onPseudoPreFactionTurnStart(" + string(_this->factSmDescr->facName) + ")");

        HOT_SEAT_CAMPAIGN.onPseudoPreFactionTurnStart(_this);

#ifdef FACTION_LIMIT_TESTS
        if (_this->dipNum == 20)
        {
            eop_faction.is_new_faction_turn = true;
            factionStruct* new_faction = eop_faction.getFactionByID(21);
        //  new_events::onPseudoPreFactionTurnStart(new_faction, stub);
            o_onPseudoPreFactionTurnStart(new_faction, stub);
        }
        else if (_this->dipNum > 20)
        {

        }
        else 
        {
        //    eop_faction.is_new_faction_turn = false;
        }
#endif // FACTION_LIMIT_TESTS

        //ДО onFactionTurnStart 
        o_onPseudoPreFactionTurnStart(_this, stub);
        //onFactionTurnStart 
    }

    namedCharacter* __fastcall onCreateCandidateMarrying(namedCharacter* daughter, int stub)
    {
	    LOG_ALWAYS(RELEASEFULL, "onCreateCandidateMarrying(" + string(daughter->fullName) + ")");

	    namedCharacter* new_husband = o_onCreateCandidateMarrying(daughter, stub);

	    return new_husband;
    }

    int __cdecl onDaughterReadyMarryHusband(namedCharacter* daughter, namedCharacter* new_husband, marriageOption* mo)
    {
	    LOG_ALWAYS(RELEASEFULL, "onDaughterReadyMarryHusband()");


	    int result = o_onDaughterReadyMarryHusband(daughter, new_husband, mo);

	    return result;
    }

    void __fastcall onStartFamilyRound(family* family)
    {
	    LOG_ALWAYS(RELEASEFULL, "onStartFamilyRound(" + string(family->faction->factSmDescr->facName) + ")");

	    o_onStartFamilyRound(family);
    }

//  bool test_createEOPunits = false;
    bool __fastcall onLoadEDU(unitDb* _this, int stub, const char* file)
    {
	    LOG_ALWAYS(RELEASEFULL, "onLoadEDU(" + string(file) + ")");
	    bool result = o_onLoadEDU(_this, stub, file);

	//  if (test_createEOPunits)
	//  {
	//    test_createEOPunits = false;
	//    new_events::createEOPunit();
	//  }

	    return result;
    }

    int __fastcall onTransitionToBattleFromStratMap(void* _this, int stub, int type)
    {
        LOG_ALWAYS(RELEASEFULL, "onTransitionToBattleFromStratMap(" + to_string(type) + ")");

        mapView.onTransitionToBattleFromStratMap();

        return o_onTransitionToBattleFromStratMap(_this, stub, type);
    }

    HRESULT __cdecl onOpenFile(char* file)
    {
	    HRESULT result = o_onOpenFile(file);

	    LOG_ALWAYS(DEBUG, "onOpenFile(" + string(file) + ")");

	    return result;
    }

    HRESULT __fastcall onGiveUnitToArmy(stackStruct* _this, int stub, unit* un, unit* add_after)
    {
	    return o_onGiveUnitToArmy(_this, stub, un, add_after);
    }

    // не знаю в какой момент срабатывает при создании юнитов; создает первый юнит, если передан неверный индекс; следующим вызывается onCreateUnit2   
    unit* __fastcall onCreateUnit(unitDb* _this, int stub, regionStruct* region, int index, int factionID, int ability, int soldiers, int armour_lvl, int weapon_lvl)
    {
        LOG_ALWAYS(DEBUG, "onCreateUnit(" + to_string(index) + ")");
        return o_onCreateUnit(_this, stub, region, index, factionID, ability, soldiers, armour_lvl, weapon_lvl);
    }

    // срабатывает всегда при создании юнитов; не создает первый юнит, если передан неверный индекс; вызывается из onCreateUnit3 и onCreateUnit4   
    unit* __fastcall onCreateUnit2(unitDb* _this, int stub, regionStruct* region, int index, int factionID, int ability, int soldiers)
    {
        LOG_ALWAYS(DEBUG, "onCreateUnit2(" + to_string(index) + ")");

        unit* result = nullptr;
        if (index >= 500)
        {
            if (eduEntry* edu = eop_unit::getEopEduEntry(index); edu)
            {
                unitDb* EOPunitDb = eop_unit::getEopUnitDb(index);
                result = o_onCreateUnit2(EOPunitDb, stub, region, 0, factionID, ability, soldiers);

                LOG_ALWAYS(RELEASEFULL, "onCreateUnit2(EOP unit: " + string(edu->Type) + ")");
            }
            else
            {
                LOG_ALWAYS(RELEASE, "[ERROR] onCreateUnit2(unit with index " + to_string(index) + " not found.)");
            }
        }
        else
        {
            result = o_onCreateUnit2(_this, stub, region, index, factionID, ability, soldiers);
        }

        return result;
    }

    // срабатывает всегда при создании юнитов; не создает первый юнит, если передан неверный индекс   
    unit* __fastcall onCreateUnit3(unitDb* _this, int stub, regionStruct* region, nameAndHash* ID, int factionID, int ability)
    {
        LOG_ALWAYS(DEBUG, "onCreateUnit3(" + string(ID->name) + ")");

        unit* result = nullptr;
        if (eduEntry* edu = eop_unit::getEopEduEntryByName(ID->name); edu)
        {
            result = onCreateUnit2(_this, stub, region, edu->Index, factionID, ability, 100);
        }
        else
        {
            result = o_onCreateUnit3(_this, stub, region, ID, factionID, ability);
        }

        return result;
    }

    // срабатывает при загрузке исторической битвы   
    unit* __fastcall onCreateUnit4(unitDb* _this, int stub, regionStruct* region, nameAndHash* ID, int factionID, int ability, int soldiers, int armour_lvl, int weapon_lvl)
    {
    #ifdef _DEBUG
        LOG_ALWAYS(RELEASEFULL, "onCreateUnit4(" + string(ID->name) + ")");
    #endif

        unit* result = nullptr;
        if (eduEntry* edu = eop_unit::getEopEduEntryByName(ID->name); edu)
        {
            result = onCreateUnit2(_this, stub, region, edu->Index, factionID, ability, 100);
        }
        else
        {
            result = o_onCreateUnit4(_this, stub, region, ID, factionID, ability, soldiers, armour_lvl, weapon_lvl);
        }

        return result;
    }

    HRESULT __fastcall onSetBattleUnitModels(unitDb* _this, int stub)
    {
        LOG_ALWAYS(RELEASEFULL, "onSetBattleUnitModels()");
        HRESULT result = o_onSetBattleUnitModels(_this, stub);

        if (dataU.eopEdu.size() > 0)
        {
            for (eopEduEntry& entry : dataU.eopEdu)
            {
                o_onSetBattleUnitModels(&entry.data.db, stub);
            }

        }

        return result;
    }

    stackStruct* __fastcall onCreateArmy(factionStruct* _this, int stub, character* general, bool isNavy)
    {
	    return o_onCreateArmy(_this, stub, general, isNavy);
    }

    unit* __fastcall onSetBodyguardUnit(stackStruct* _this, int stub, character* general, int exp, int weapon_lvl, int armour_lvl, eduEntry* ud)
    {
	    return o_onSetBodyguardUnit(_this, stub, general, exp, weapon_lvl, armour_lvl, ud);
    }
  
    void __fastcall onRestorePointers(settlementStruct* _this, int stub)
    {
        LOG_ALWAYS(RELEASEFULL, "onRestorePointers(" + string(_this->name) + ")");

        o_onRestorePointers(_this, stub);

        EOP_SETTLEMENTS.onRestorePointers(_this);
    }

    void __fastcall onAttachRegionSettlement(stratMap* _this, int stub, int regionID, settlementStruct* settlement)
    {
        if (EOP_SETTLEMENTS.onAttachRegionSettlement(regionID, settlement))
            return;

        LOG_ALWAYS(RELEASEFULL, "onAttachRegionSettlement(" + string(settlement->name) + ")");
        o_onAttachRegionSettlement(_this, stub, regionID, settlement);
    }

    void __fastcall onSetPreBattleWithdrawal(battleDataS* _this, int stub, bool withdraw)
    {
        LOG_ALWAYS(RELEASEFULL, "onSetPreBattleWithdrawal()");
        o_onSetPreBattleWithdrawal(_this, stub, withdraw);
    }

    void __fastcall onBattleInstigate(battleDataS* _this, int stub, character* attacker, character* defender, battleType type, bool nightBattle, bool withdraw)
    {
        LOG_ALWAYS(RELEASEFULL, "onBattleInstigate(attacker: " + string(attacker->genChar->fullName) + ", defender: " + string(defender->genChar->fullName) + ")");

        bool change = false;
        if (HOT_SEAT_CAMPAIGN.m_is_hot_seat_campaign && HOT_SEAT_CAMPAIGN.m_never_withdraw && 
            defender->genChar->faction->isPlayerControlled == 0 && 
            HOT_SEAT_CAMPAIGN.m_player_faction[defender->genChar->faction->dipNum]
        )
        {
            BYTE EDX = 0x00;
            memory::Write(&EDX, offsets.neverWithdraw, 1);
            change = true;

            LOG_ALWAYS(DEBUG, "onBattleInstigate(change 0x00)");
        }

        o_onBattleInstigate(_this, stub, attacker, defender, type, nightBattle, withdraw);

        if (change)
        {
            BYTE EDX = 0x01;
            memory::Write(&EDX, offsets.neverWithdraw, 1);

            LOG_ALWAYS(DEBUG, "onBattleInstigate(return 0x01)");
        }
    }


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void onDllProcessAttach()
    {
        LOG_ALWAYS(RELEASE, "new_events::onDllProcessAttach()");
    }

    void onDllProcessDetach()
    {
        LOG_ALWAYS(RELEASE, "new_events::onDllProcessDetach()");
    }

    bool new_events::onInit(bool result)
    {
        LOG_ALWAYS(RELEASE, "new_events::onInit(" + boolStr(result) + ")");
        return result;
    }

//  void onCampaignMapLoaded(campaign* campaignStruct)
//  {
//      LOG(RELEASE, "new_events::onCampaignMapLoaded(" + boolStr(campaignStruct) + ")");
//  }

    void onCampaignMapUnloaded()
    {
        LOG_ALWAYS(RELEASE, "new_events::onCampaignMapUnloaded()");
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void setAncLimit(uint8_t limit)
    {
        LOG_ALWAYS(RELEASE, "setAncLimit(" + to_string(limit) + ")");

        const DWORD ancillaries1 = 0x005A6EA1;
        const DWORD ancillaries2 = 0x005A71B9;
        const DWORD ancillaries3 = 0x005A74DF;

        memory::Write(&limit, ancillaries1, 1);
        memory::Write(&limit, ancillaries2, 1);
        memory::Write(&limit, ancillaries3, 1);
    }

    void callSaveLoad(UNICODE_STRING**& savePath)
    {
        onQuickLoading(savePath);
    }

    void callSaveCreate(UNICODE_STRING**& savePath)
    {
        gameSaveStruct* g = reinterpret_cast<gameSaveStruct*>(offsets.gameSaveStruct);
        onSaveCreate(g, 0, savePath, false);
    }

    void callSaveLoad(const char* savePath)
    {
        UNICODE_STRING** uniSavePath = NULL;
        createUniString(uniSavePath, savePath);
        onQuickLoading(uniSavePath);
    }

    void callSaveCreate(const char* savePath)
    {
        UNICODE_STRING** uniSavePath = NULL;
        createUniString(uniSavePath, savePath);
        callSaveCreate(uniSavePath);
    }

    character* createCharacter(characterType charType, factionStruct* faction, int age, const char* name, const char* surname, int subFaction, const char* portrait, int xCoord, int yCoord)
    {
        /*
        typedef character* __cdecl func(characterType charType, factionStruct* faction, int age, const char* name, const char* surname, int subFaction);
        func* f = (func*)0x00890724;
        character* new_character = f(charType, faction, age, name, surname, subFaction);
        */
        character* new_character = onCharacterCreated(charType, faction, age, name, surname, subFaction, portrait, xCoord, yCoord);
        o_onReposition(new_character, 0, xCoord, yCoord);

        // Нужна нормальная функция установки портрета!!!   
    #ifdef _DEBUG
        LOG_REMINDER("createCharacter(Нужна нормальная функция установки портрета)");
    #endif // _DEBUG

        return new_character;
    }

    namedCharacter* createCandidateMarrying(namedCharacter* daughter)
    {
        namedCharacter* new_husband = onCreateCandidateMarrying(daughter, 0);
        if (!new_husband)
            return nullptr;

		char* param_2 = reinterpret_cast<char*>(0x0101cf14);
		char* param_3 = reinterpret_cast<char*>(0x029b66b4);
		marriageOption* mo = GAME_FUNC(marriageOption*(__cdecl*)(int param_1, char* param_2, char* param_3, undefined4 param_4, undefined4 param_5), 0x00ee12b0)(0x10, param_2, param_3, 0x1ff4, 1); //classCreatorNEW    

		mo->yesNoClass      = reinterpret_cast<void*>(0x029b6670);//puVar8 = &PTR_LAB_029b6670;
		mo->madeChoice      = false;
		mo->accepted        = false;
		mo->possibleHusband = new_husband;
		mo->wife            = daughter;
		daughter->faction->facFamily.marriageOption = mo;

		onDaughterReadyMarryHusband(daughter, new_husband, daughter->faction->facFamily.marriageOption);
        return new_husband;
    }

    void callScript(const char* scriptName)
    {
        LOG_ALWAYS(RELEASEFULL, "callScript(scriptName: " + string(scriptName) + ")");

        string file = "dmData\\temp\\temp_file2";
        ofstream out;
        out.open(file, ios::out);
        if (out.is_open())
        {
            out << scriptName << endl;
        }
        out.close();

        char* c = const_cast<char*>(scriptName);
        UNICODE_STRING** uniFileName = NULL;
        createUniString(uniFileName, file.c_str());
        descrFile* dFile = new descrFile(c, c, uniFileName, c, c, 1);

        onCreateDescrFile(dFile, 0, uniFileName, 0);
        scriptClass* script = onCreateScriptFromFile(rememberScriptClass, 0, dFile);

        onExecuteScript(script);
        delete dFile;

        remove("dmData\\temp\\temp_file2");

    //  LOG(RELEASEFULL, "Command not found: " + string(scriptName));
    }

    void callScriptFromFile(const char* fileName)
    {
        LOG_ALWAYS(RELEASEFULL, "callScriptFromFile(fileName: " + string(fileName) + ")");

        char* c = const_cast<char*>(fileName);
        UNICODE_STRING** uniFileName = NULL;
        createUniString(uniFileName, fileName);
        descrFile* dFile = new descrFile(c, c, uniFileName, c, c, 1);

        onCreateDescrFile(dFile, 0, uniFileName, 0);
        scriptClass* script = onCreateScriptFromFile(rememberScriptClass, 0, dFile);

        onExecuteScript(script);
        delete dFile;

    //  LOG(RELEASEFULL, "Command not found: " + string(fileName));
    }

    void scriptCommand(const char* scriptName, const char* arg)
    {
        LOG_ALWAYS(RELEASEFULL, "callScript(scriptName: " + string(scriptName) + ", " + string(arg) + ")");

        string fullCommand = string(scriptName) + " " + arg;
        scriptClass* script = new scriptClass;

        char* c = const_cast<char*>(scriptName);
        const string scriptPath = "luaCommand";
        UNICODE_STRING** uniFileName = new UNICODE_STRING*;
        createUniString(uniFileName, scriptPath.c_str());

        descrFile* dFile = new descrFile(c, c, uniFileName, c, c, 1);

        char* condition   = const_cast<char*>(fullCommand.c_str());
        dFile->buffer     = condition;
        dFile->end        = condition + strlen(condition);
        dFile->line1      = condition;
        dFile->line2      = condition;
        dFile->lineNumber = 1;

        onCreateScriptFromFile(script, 0, dFile);
        onExecuteScript(script);
    }

    //new_events::createEOPunit("test_unit.txt", 1000)
    bool createEOPunit(const char* fileName, int newIdx)
    {
        eopEduEntry newEntry(fileName, newIdx);
        dataU.eopEdu.push_back(newEntry);

        return true;
    }

    void quitGame()
    {
        typedef void __cdecl func();
        func* f = (func*)0x0040d918;
        f();
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
}// new_events 

void saveFilesS::deleteFiles()
{
    std::vector<std::string>::size_type i = 0;
    while (i < files.size()) 
    {
        int success = remove(files[i].c_str());
        if (success == 0) 
        {
            LOG_ALWAYS(DEBUG, "saveFilesS::deleteFiles(" + files[i] + ")");
            files.erase(files.begin() + i);
        }
        else 
        {
            ++i;
        }
    }

    everything_deleted = files.size();

    if (everything_deleted == 0)
    {
        saveFiles = saveFilesS();
    }
}

void saveFilesS::deleteAgain()
{
    if (everything_deleted > 0)
    {
        LOG_ALWAYS(DEBUG, "saveFilesS::deleteAgain()");
        deleteFiles();
    }
}
void saveFilesS::deleteAll()
{
    remove("dmData\\temp\\temp_file");
    remove("dmData\\temp\\temp_file.bin");
    remove("dmData\\temp\\temp_file2");
    remove("dmData\\temp\\temp_file3");
    remove("dmData\\temp\\hs.json");
    remove("dmData\\temp\\hs.bin");
    remove("dmData\\temp\\temp_screenshot.png");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

























