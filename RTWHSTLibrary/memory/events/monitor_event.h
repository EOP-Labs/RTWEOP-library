#pragma once
#include "../memoryWork.h"

namespace monitor_event
{
	void initGameEvents();
	void deInitGameEvents();
	void tests();

	extern namedCharacter* selectCharacter;
	extern settlementStruct* selectSettlement;


	HRESULT __fastcall onFactionTurnStart(void* _this, int stub, factionStruct* faction);
	HRESULT __fastcall onFactionWarDeclared(void* _this, int stub, factionStruct* faction, factionStruct* targetfac);
	HRESULT __fastcall onHordeFormed(void* _this, int stub, factionStruct* faction);
	HRESULT __fastcall onFactionTurnEnd(void* _this, int stub, factionStruct* faction);
	HRESULT __fastcall onHireMercenaries(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onGeneralCaptureResidence(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onGeneralCaptureWonder(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onGeneralCaptureSettlement(void* _this, int stub, namedCharacter* character, settlementStruct* settlement);
	HRESULT __fastcall onLeaderDestroyedFaction(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onDisaster(void* _this, int stub, int_32 disasterType);
	HRESULT __fastcall onCharacterDamagedByDisaster(void* _this, int stub, namedCharacter* character, int_32 disasterType);
	HRESULT __fastcall onGeneralAssaultsResidence(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onOfferedForAdoption(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onLesserGeneralOfferedForAdoption(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onOfferedForMarriage(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onBrotherAdopted(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onBecomesFactionLeader(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onBecomesFactionHeir(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onBecomeQuaestor(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onBecomeAedile(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onBecomePraetor(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onBecomeConsul(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onBecomeCensor(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onBecomePontifexMaximus(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onCeasedFactionLeader(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onCeasedFactionHeir(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onCeasedQuaestor(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onCeasedAedile(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onCeasedPraetor(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onCeasedConsul(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onCeasedCensor(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onCeasedPontifexMaximus(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onUngarrisonedFort(void* _this, int stub, fortStruct* fort);
	HRESULT __fastcall onLostLegionaryEagle(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onCapturedLegionaryEagle(void* _this, int stub, namedCharacter* character);
//	HRESULT __fastcall onRecapturedLegionaryEagle(void* _this, int stub, );
	HRESULT __fastcall onSenateExposure(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onQuaestorInvestigationMinor(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onQuaestorInvestigation(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onQuaestorInvestigationMajor(void* _this, int stub, namedCharacter* character);
//	HRESULT __fastcall onPopularSupportForOverthrow(void* _this, int stub, );
//	HRESULT __fastcall onSenateReadyToOutlawFaction(void* _this, int stub, factionStruct* faction);
	HRESULT __fastcall onSenateOutlawsFaction(void* _this, int stub, factionStruct* faction);


	HRESULT __fastcall onCharacterSelected(void* _this, int stub, namedCharacter* selectedChar, int_32 action, coords* coords, int_32 region_id);
	HRESULT __fastcall onSettlementSelected(void* _this, int stub, settlementStruct* settlement);
	HRESULT __fastcall onMultiTurnMove(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onCharacterPanelOpen(void* _this, int stub, settlementStruct* settlement);
	HRESULT __fastcall onSettlementPanelOpen(void* _this, int stub, factionStruct* faction);
	HRESULT __fastcall onFinancesPanelOpen(void* _this, int stub, factionStruct* faction);
	HRESULT __fastcall onFactionSummaryPanelOpen(void* _this, int stub, factionStruct* faction);
	HRESULT __fastcall onFamilyTreePanelOpen(void* _this, int stub, factionStruct* faction);
//	HRESULT __fastcall onDiplomaticStandingPanelOpen(void* _this, int stub);
//	HRESULT __fastcall onSenateMissionsPanelOpen(void* _this, int stub, factionStruct* faction);
//	HRESULT __fastcall onSenateOfficesPanelOpen(void* _this, int stub);
	HRESULT __fastcall onDiplomacyPanelOpen(void* _this, int stub, factionStruct* faction);
	HRESULT __fastcall onPreBattlePanelOpen(void* _this, int stub, factionStruct* faction);
//	HRESULT __fastcall onRecruitmentPanelOpen(void* _this, int stub, settlementStruct* settlement);
//	HRESULT __fastcall onConstructionPanelOpen(void* _this, int stub, settlementStruct* settlement);
	HRESULT __fastcall onTradePanelOpen(void* _this, int stub, settlementStruct* settlement);
//	HRESULT __fastcall onHireMercenariesPanelOpen(void* _this, int stub);
//	HRESULT __fastcall onNavalAutoResolvePanelOpen(void* _this, int stub);
	HRESULT __fastcall onIncomingMessage(void* _this, int stub, int eventID);
	HRESULT __fastcall onMessageOpen(void* _this, int stub, int eventID);
	HRESULT __fastcall onRequestBuildingAdvice(void* _this, int stub, settlementStruct* settlement, char* resourceDescription);
	HRESULT __fastcall onRequestTrainingAdvice(void* _this, int stub, settlementStruct* settlement, char* resourceDescription);
//	HRESULT __fastcall onRequestMercenariesAdvice(void* _this, int stub, stackStruct* army);
	HRESULT __fastcall onButtonPressed(void* _this, int stub, char* resourceDescription);
	HRESULT __fastcall onShortcutTriggered(void* _this, int stub, char* resourceDescription, char* id);
	HRESULT __fastcall onScrollOpened(void* _this, int stub, char* resourceDescription);
	HRESULT __fastcall onScrollClosed(void* _this, int stub, char* resourceDescription);
//	HRESULT __fastcall onAdviceSupressed(void* _this, int stub, char* resourceDescription);
	HRESULT __fastcall onScrollAdviceRequested(void* _this, int stub, char* resourceDescription);
//	HRESULT __fastcall onPreBattleScrollAdviceRequested(void* _this, int stub);
//	HRESULT __fastcall onNavalPreBattleScrollAdviceRequested(void* _this, int stub);
	HRESULT __fastcall onSettlementScrollAdviceRequested(void* _this, int stub, settlementStruct* settlement);
//	HRESULT __fastcall onIdle(void* _this, int stub);
//	HRESULT __fastcall onAbandonShowMe(void* _this, int stub);
//	HRESULT __fastcall onScriptedAdvice(void* _this, int stub);
//	HRESULT __fastcall onDeclineAutomatedSettlementManagement(void* _this, int stub, factionStruct* faction, settlementStruct* settlement);
//	HRESULT __fastcall onEscPressed(void* _this, int stub);
	HRESULT __fastcall onGameReloaded(void* _this, int stub);


	HRESULT __fastcall onSettlementTurnStart(void* _this, int stub, settlementStruct* settlement);
	HRESULT __fastcall onSettlementTurnEnd(void* _this, int stub, settlementStruct* settlement);
	HRESULT __fastcall onNewAdmiralCreated(void* _this, int stub, settlementStruct* settlement, namedCharacter* character);
	HRESULT __fastcall onUnitTrained(void* _this, int stub, factionStruct* faction, settlementStruct* settlement, unit* trainedUnit);
	HRESULT __fastcall onGovernorUnitTrained(void* _this, int stub, namedCharacter* character, settlementStruct* settlement, unit* trainedUnit);
	HRESULT __fastcall onBuildingCompleted(void* _this, int stub, settlementStruct* settlement, factionStruct* faction, eventBuild* evBuild);
	HRESULT __fastcall onGovernorBuildingCompleted(void* _this, int stub, namedCharacter* character, settlementStruct* settlement, eventBuild* evBuild);
//	HRESULT __fastcall onPlugInCompleted(void* _this, int stub, settlementStruct* settlement, eventBuild* evBuild);
//	HRESULT __fastcall onGovernorPlugInCompleted(void* _this, int stub, namedCharacter* character, eventBuild* evBuild);
	HRESULT __fastcall onAgentCreated(void* _this, int stub, namedCharacter* character, enum characterType type, settlementStruct* settlement);
	HRESULT __fastcall onGovernorAgentCreated(void* _this, int stub, namedCharacter* character, enum characterType type, settlementStruct* settlement);
	HRESULT __fastcall onBuildingDestroyed(void* _this, int stub);
	HRESULT __fastcall onGovernorBuildingDestroyed(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onCityRiots(void* _this, int stub, settlementStruct* settlement, factionStruct* faction);
	HRESULT __fastcall onGovernorCityRiots(void* _this, int stub, namedCharacter* character, settlementStruct* settlement, factionStruct* faction);
	HRESULT __fastcall onCityRebels(void* _this, int stub, settlementStruct* settlement, factionStruct* faction);
	HRESULT __fastcall onGovernorCityRebels(void* _this, int stub, namedCharacter* character, settlementStruct* settlement, factionStruct* faction);
	HRESULT __fastcall onGovernorThrowGames(void* _this, int stub, namedCharacter* character, settlementStruct* settlement);
	HRESULT __fastcall onGovernorThrowRaces(void* _this, int stub, namedCharacter* character, settlementStruct* settlement);
	HRESULT __fastcall onUngarrisonedSettlement(void* _this, int stub, settlementStruct* settlement);
	HRESULT __fastcall onEnslavePopulation(void* _this, int stub, namedCharacter* character, factionStruct* faction);
	HRESULT __fastcall onExterminatePopulation(void* _this, int stub, namedCharacter* character);
	HRESULT __fastcall onCitySacked(void* _this, int stub, settlementStruct* settlement, factionStruct* faction);
}