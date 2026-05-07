#include "monitor_event.h"
#include "../hotSeat/hotSeatCampaign.h"
#include "../hotSeat/createBattleResult.h"
#include "../../eopSettlements.h"
using namespace std;


using tFactionTurnStart                       = HRESULT(__fastcall*)(void* _this, int stub, factionStruct* faction);
using tFactionWarDeclared                     = HRESULT(__fastcall*)(void* _this, int stub, factionStruct* faction, factionStruct* targetfac);
using tHordeFormed                            = HRESULT(__fastcall*)(void* _this, int stub, factionStruct* faction);
using tFactionTurnEnd                         = HRESULT(__fastcall*)(void* _this, int stub, factionStruct* faction);
using tHireMercenaries                        = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tGeneralCaptureResidence                = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tGeneralCaptureWonder                   = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tGeneralCaptureSettlement               = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character, settlementStruct* settlement);
using tLeaderDestroyedFaction                 = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tDisaster                               = HRESULT(__fastcall*)(void* _this, int stub, int_32 disasterType);
using tCharacterDamagedByDisaster             = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character, int_32 disasterType);
using tGeneralAssaultsResidence               = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tOfferedForAdoption                     = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tLesserGeneralOfferedForAdoption        = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tOfferedForMarriage                     = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tBrotherAdopted                         = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tBecomesFactionLeader                   = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tBecomesFactionHeir                     = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tBecomeQuaestor                         = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tBecomeAedile                           = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tBecomePraetor                          = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tBecomeConsul                           = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tBecomeCensor                           = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tBecomePontifexMaximus                  = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tCeasedFactionLeader                    = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tCeasedFactionHeir                      = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tCeasedQuaestor                         = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tCeasedAedile                           = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tCeasedPraetor                          = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tCeasedConsul                           = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tCeasedCensor                           = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tCeasedPontifexMaximus                  = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tUngarrisonedFort                       = HRESULT(__fastcall*)(void* _this, int stub, fortStruct* fort);
using tLostLegionaryEagle                     = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tCapturedLegionaryEagle                 = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
//using tRecapturedLegionaryEagle             = HRESULT(__fastcall*)(void* _this, int stub, );
using tSenateExposure                         = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tQuaestorInvestigationMinor             = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tQuaestorInvestigation                  = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tQuaestorInvestigationMajor             = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
//using tPopularSupportForOverthrow           = HRESULT(__fastcall*)(void* _this, int stub, );
using tSenateReadyToOutlawFaction             = HRESULT(__fastcall*)(void* _this, int stub, factionStruct* faction);
using tSenateOutlawsFaction                   = HRESULT(__fastcall*)(void* _this, int stub, factionStruct* faction);

tFactionTurnStart                               oFactionTurnStart                     = nullptr;
tFactionWarDeclared                             oFactionWarDeclared                   = nullptr;
tHordeFormed                                    oHordeFormed                          = nullptr;
tFactionTurnEnd                                 oFactionTurnEnd                       = nullptr;
tHireMercenaries                                oHireMercenaries                      = nullptr;
tGeneralCaptureResidence                        oGeneralCaptureResidence              = nullptr;
tGeneralCaptureWonder                           oGeneralCaptureWonder                 = nullptr;
tGeneralCaptureSettlement                       oGeneralCaptureSettlement             = nullptr;
tLeaderDestroyedFaction                         oLeaderDestroyedFaction               = nullptr;
tDisaster                                       oDisaster                             = nullptr;
tCharacterDamagedByDisaster                     oCharacterDamagedByDisaster           = nullptr;
tGeneralAssaultsResidence                       oGeneralAssaultsResidence             = nullptr;
tOfferedForAdoption                             oOfferedForAdoption                   = nullptr;
tLesserGeneralOfferedForAdoption                oLesserGeneralOfferedForAdoption      = nullptr;
tOfferedForMarriage                             oOfferedForMarriage                   = nullptr;
tBrotherAdopted                                 oBrotherAdopted                       = nullptr;
tBecomesFactionLeader                           oBecomesFactionLeader                 = nullptr;
tBecomesFactionHeir                             oBecomesFactionHeir                   = nullptr;
tBecomeQuaestor                                 oBecomeQuaestor                       = nullptr;
tBecomeAedile                                   oBecomeAedile                         = nullptr;
tBecomePraetor                                  oBecomePraetor                        = nullptr;
tBecomeConsul                                   oBecomeConsul                         = nullptr;
tBecomeCensor                                   oBecomeCensor                         = nullptr;
tBecomePontifexMaximus                          oBecomePontifexMaximus                = nullptr;
tCeasedFactionLeader                            oCeasedFactionLeader                  = nullptr;
tCeasedFactionHeir                              oCeasedFactionHeir                    = nullptr;
tCeasedQuaestor                                 oCeasedQuaestor                       = nullptr;
tCeasedAedile                                   oCeasedAedile                         = nullptr;
tCeasedPraetor                                  oCeasedPraetor                        = nullptr;
tCeasedConsul                                   oCeasedConsul                         = nullptr;
tCeasedCensor                                   oCeasedCensor                         = nullptr;
tCeasedPontifexMaximus                          oCeasedPontifexMaximus                = nullptr;
tUngarrisonedFort                               oUngarrisonedFort                     = nullptr;
tLostLegionaryEagle                             oLostLegionaryEagle                   = nullptr;
tCapturedLegionaryEagle                         oCapturedLegionaryEagle               = nullptr;
//tRecapturedLegionaryEagle                     oRecapturedLegionaryEagle             = nullptr;
tSenateExposure                                 oSenateExposure                       = nullptr;
tQuaestorInvestigationMinor                     oQuaestorInvestigationMinor           = nullptr;
tQuaestorInvestigation                          oQuaestorInvestigation                = nullptr;
tQuaestorInvestigationMajor                     oQuaestorInvestigationMajor           = nullptr;
//tPopularSupportForOverthrow                   oPopularSupportForOverthrow           = nullptr;
//tSenateReadyToOutlawFaction                   oSenateReadyToOutlawFaction           = nullptr;
tSenateOutlawsFaction                           oSenateOutlawsFaction                 = nullptr;


using tCharacterSelected                      = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* selectedChar, int_32 action, coords* coords, int_32 region_id);
using tSettlementSelected                     = HRESULT(__fastcall*)(void* _this, int stub, settlementStruct* settlement);
using tMultiTurnMove                          = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tCharacterPanelOpen                     = HRESULT(__fastcall*)(void* _this, int stub, settlementStruct* settlement);
using tSettlementPanelOpen                    = HRESULT(__fastcall*)(void* _this, int stub, factionStruct* faction);
using tFinancesPanelOpen                      = HRESULT(__fastcall*)(void* _this, int stub, factionStruct* faction);
using tFactionSummaryPanelOpen                = HRESULT(__fastcall*)(void* _this, int stub, factionStruct* faction);
using tFamilyTreePanelOpen                    = HRESULT(__fastcall*)(void* _this, int stub, factionStruct* faction);
//using tDiplomaticStandingPanelOpen          = HRESULT(__fastcall*)(void* _this, int stub);
//using tSenateMissionsPanelOpen              = HRESULT(__fastcall*)(void* _this, int stub, factionStruct* faction);
//using tSenateOfficesPanelOpen               = HRESULT(__fastcall*)(void* _this, int stub);
using tDiplomacyPanelOpen                     = HRESULT(__fastcall*)(void* _this, int stub, factionStruct* faction);
using tPreBattlePanelOpen                     = HRESULT(__fastcall*)(void* _this, int stub, factionStruct* faction);
//using tRecruitmentPanelOpen                 = HRESULT(__fastcall*)(void* _this, int stub, settlementStruct* settlement);
//using tConstructionPanelOpen                = HRESULT(__fastcall*)(void* _this, int stub, settlementStruct* settlement);
using tTradePanelOpen                         = HRESULT(__fastcall*)(void* _this, int stub, settlementStruct* settlement);
//using tHireMercenariesPanelOpen             = HRESULT(__fastcall*)(void* _this, int stub);
//using tNavalAutoResolvePanelOpen            = HRESULT(__fastcall*)(void* _this, int stub);
using tIncomingMessage                        = HRESULT(__fastcall*)(void* _this, int stub, int eventID);
using tMessageOpen                            = HRESULT(__fastcall*)(void* _this, int stub, int eventID);
using tRequestBuildingAdvice                  = HRESULT(__fastcall*)(void* _this, int stub, settlementStruct* settlement, char* resourceDescription);
using tRequestTrainingAdvice                  = HRESULT(__fastcall*)(void* _this, int stub, settlementStruct* settlement, char* resourceDescription);
//using tRequestMercenariesAdvice             = HRESULT(__fastcall*)(void* _this, int stub, stackStruct* army);
using tButtonPressed                          = HRESULT(__fastcall*)(void* _this, int stub, char* resourceDescription);
using tShortcutTriggered                      = HRESULT(__fastcall*)(void* _this, int stub, char* resourceDescription1, char* resourceDescription2);
using tScrollOpened                           = HRESULT(__fastcall*)(void* _this, int stub, char* resourceDescription);
using tScrollClosed                           = HRESULT(__fastcall*)(void* _this, int stub, char* resourceDescription);
//using tAdviceSupressed                      = HRESULT(__fastcall*)(void* _this, int stub, char* resourceDescription);
using tScrollAdviceRequested                  = HRESULT(__fastcall*)(void* _this, int stub, char* resourceDescription);
//using tPreBattleScrollAdviceRequested       = HRESULT(__fastcall*)(void* _this, int stub);
//using tNavalPreBattleScrollAdviceRequested  = HRESULT(__fastcall*)(void* _this, int stub);
using tSettlementScrollAdviceRequested        = HRESULT(__fastcall*)(void* _this, int stub, settlementStruct* settlement);
//using tIdle                                 = HRESULT(__fastcall*)(void* _this, int stub);
//using tAbandonShowMe                        = HRESULT(__fastcall*)(void* _this, int stub);
//using tScriptedAdvice                       = HRESULT(__fastcall*)(void* _this, int stub);
//using tDeclineAutomatedSettlementManagement = HRESULT(__fastcall*)(void* _this, int stub, factionStruct* faction, settlementStruct* settlement);
//using tEscPressed                           = HRESULT(__fastcall*)(void* _this, int stub);
using tGameReloaded                           = HRESULT(__fastcall*)(void* _this, int stub);

tCharacterSelected                              oCharacterSelected                    = nullptr;
tSettlementSelected                             oSettlementSelected                   = nullptr;
tMultiTurnMove                                  oMultiTurnMove                        = nullptr;
tCharacterPanelOpen                             oCharacterPanelOpen                   = nullptr;
tSettlementPanelOpen                            oSettlementPanelOpen                  = nullptr;
tFinancesPanelOpen                              oFinancesPanelOpen                    = nullptr;
tFactionSummaryPanelOpen                        oFactionSummaryPanelOpen              = nullptr;
tFamilyTreePanelOpen                            oFamilyTreePanelOpen                  = nullptr;
//tDiplomaticStandingPanelOpen                  oDiplomaticStandingPanelOpen          = nullptr;
//tSenateMissionsPanelOpen                      oSenateMissionsPanelOpen              = nullptr;
//tSenateOfficesPanelOpen                       oSenateOfficesPanelOpen               = nullptr;
tDiplomacyPanelOpen                             oDiplomacyPanelOpen                   = nullptr;
tPreBattlePanelOpen                             oPreBattlePanelOpen                   = nullptr;
//tRecruitmentPanelOpen                         oRecruitmentPanelOpen                 = nullptr;
//tConstructionPanelOpen                        oConstructionPanelOpen                = nullptr;
tTradePanelOpen                                 oTradePanelOpen                       = nullptr;
//tHireMercenariesPanelOpen                     oHireMercenariesPanelOpen             = nullptr;
//tNavalAutoResolvePanelOpen                    oNavalAutoResolvePanelOpen            = nullptr;
tIncomingMessage                                oIncomingMessage                      = nullptr;
tMessageOpen                                    oMessageOpen                          = nullptr;
tRequestBuildingAdvice                          oRequestBuildingAdvice                = nullptr;
tRequestTrainingAdvice                          oRequestTrainingAdvice                = nullptr;
//tRequestMercenariesAdvice                     oRequestMercenariesAdvice             = nullptr;
tButtonPressed                                  oButtonPressed                        = nullptr;
tShortcutTriggered                              oShortcutTriggered                    = nullptr;
tScrollOpened                                   oScrollOpened                         = nullptr;
tScrollClosed                                   oScrollClosed                         = nullptr;
//tAdviceSupressed                              oAdviceSupressed                      = nullptr;
tScrollAdviceRequested                          oScrollAdviceRequested                = nullptr;
//tPreBattleScrollAdviceRequested               oPreBattleScrollAdviceRequested       = nullptr;
//tNavalPreBattleScrollAdviceRequested          oNavalPreBattleScrollAdviceRequested  = nullptr;
tSettlementScrollAdviceRequested                oSettlementScrollAdviceRequested      = nullptr;
//tIdle                                         oIdle                                 = nullptr;
//tAbandonShowMe                                oAbandonShowMe                        = nullptr;
//tScriptedAdvice                               oScriptedAdvice                       = nullptr;
//tDeclineAutomatedSettlementManagement         oDeclineAutomatedSettlementManagement = nullptr;
//tEscPressed                                   oEscPressed                           = nullptr;
tGameReloaded                                   oGameReloaded                         = nullptr;


using tSettlementTurnStart                    = HRESULT(__fastcall*)(void* _this, int stub, settlementStruct* settlement);
using tSettlementTurnEnd                      = HRESULT(__fastcall*)(void* _this, int stub, settlementStruct* settlement);
using tNewAdmiralCreated                      = HRESULT(__fastcall*)(void* _this, int stub, settlementStruct* settlement, namedCharacter* character);
using tUnitTrained                            = HRESULT(__fastcall*)(void* _this, int stub, factionStruct* faction, settlementStruct* settlement, unit* trainedUnit);
using tGovernorUnitTrained                    = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character, settlementStruct* settlement, unit* trainedUnit);
using tBuildingCompleted                      = HRESULT(__fastcall*)(void* _this, int stub, settlementStruct* settlement, factionStruct* faction, eventBuild* evBuild);
using tGovernorBuildingCompleted              = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character, settlementStruct* settlement, eventBuild* evBuild);
//using tPlugInCompleted                      = HRESULT(__fastcall*)(void* _this, int stub, settlementStruct* settlement, eventBuild* evBuild);
//using tGovernorPlugInCompleted              = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character, eventBuild* evBuild);
using tAgentCreated                           = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character, enum characterType type, settlementStruct* settlement);
using tGovernorAgentCreated                   = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character, enum characterType type, settlementStruct* settlement);
using tBuildingDestroyed                      = HRESULT(__fastcall*)(void* _this, int stub);
using tGovernorBuildingDestroyed              = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tCityRiots                              = HRESULT(__fastcall*)(void* _this, int stub, settlementStruct* settlement, factionStruct* faction);
using tGovernorCityRiots                      = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character, settlementStruct* settlement, factionStruct* faction);
using tCityRebels                             = HRESULT(__fastcall*)(void* _this, int stub, settlementStruct* settlement, factionStruct* faction);
using tGovernorCityRebels                     = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character, settlementStruct* settlement, factionStruct* faction);
using tGovernorThrowGames                     = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character, settlementStruct* settlement);
using tGovernorThrowRaces                     = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character, settlementStruct* settlement);
using tUngarrisonedSettlement                 = HRESULT(__fastcall*)(void* _this, int stub, settlementStruct* settlement);
using tEnslavePopulation                      = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character, factionStruct* faction);
using tExterminatePopulation                  = HRESULT(__fastcall*)(void* _this, int stub, namedCharacter* character);
using tCitySacked                             = HRESULT(__fastcall*)(void* _this, int stub, settlementStruct* settlement, factionStruct* faction);

tSettlementTurnStart                            oSettlementTurnStart                  = nullptr;
tSettlementTurnEnd                              oSettlementTurnEnd                    = nullptr;
tNewAdmiralCreated                              oNewAdmiralCreated                    = nullptr;
tUnitTrained                                    oUnitTrained                          = nullptr;
tGovernorUnitTrained                            oGovernorUnitTrained                  = nullptr;
tBuildingCompleted                              oBuildingCompleted                    = nullptr;
tGovernorBuildingCompleted                      oGovernorBuildingCompleted            = nullptr;
//tPlugInCompleted                              oPlugInCompleted                      = nullptr;
//tGovernorPlugInCompleted                      oGovernorPlugInCompleted              = nullptr;
tAgentCreated                                   oAgentCreated                         = nullptr;
tGovernorAgentCreated                           oGovernorAgentCreated                 = nullptr;
tBuildingDestroyed                              oBuildingDestroyed                    = nullptr;
tGovernorBuildingDestroyed                      oGovernorBuildingDestroyed            = nullptr;
tCityRiots                                      oCityRiots                            = nullptr;
tGovernorCityRiots                              oGovernorCityRiots                    = nullptr;
tCityRebels                                     oCityRebels                           = nullptr;
tGovernorCityRebels                             oGovernorCityRebels                   = nullptr;
tGovernorThrowGames                             oGovernorThrowGames                   = nullptr;
tGovernorThrowRaces                             oGovernorThrowRaces                   = nullptr;
tUngarrisonedSettlement                         oUngarrisonedSettlement               = nullptr;
tEnslavePopulation                              oEnslavePopulation                    = nullptr;
tExterminatePopulation                          oExterminatePopulation                = nullptr;
tCitySacked                                     oCitySacked                           = nullptr;


void monitor_event::initGameEvents()
{
	LOG_ALWAYS(RELEASE, "initGameEvents()");

	oFactionTurnStart                                            = (tFactionTurnStart)offsets.onFactionTurnStart;
	oFactionWarDeclared                                          = (tFactionWarDeclared)offsets.onFactionWarDeclared;
	oHordeFormed                                                 = (tHordeFormed)offsets.onHordeFormed;
	oFactionTurnEnd                                              = (tFactionTurnEnd)offsets.onFactionTurnEnd;
	oHireMercenaries                                             = (tHireMercenaries)offsets.onHireMercenaries;
	oGeneralCaptureResidence                                     = (tGeneralCaptureResidence)offsets.onGeneralCaptureResidence;
	oGeneralCaptureWonder                                        = (tGeneralCaptureWonder)offsets.onGeneralCaptureWonder;
	oGeneralCaptureSettlement                                    = (tGeneralCaptureSettlement)offsets.onGeneralCaptureSettlement;
	oLeaderDestroyedFaction                                      = (tLeaderDestroyedFaction)offsets.onLeaderDestroyedFaction;
	oDisaster                                                    = (tDisaster)offsets.onDisaster;
	oCharacterDamagedByDisaster                                  = (tCharacterDamagedByDisaster)offsets.onCharacterDamagedByDisaster;
	oGeneralAssaultsResidence                                    = (tGeneralAssaultsResidence)offsets.onGeneralAssaultsResidence;
	oOfferedForAdoption                                          = (tOfferedForAdoption)offsets.onOfferedForAdoption;
	oLesserGeneralOfferedForAdoption                             = (tLesserGeneralOfferedForAdoption)offsets.onLesserGeneralOfferedForAdoption;
	oOfferedForMarriage                                          = (tOfferedForMarriage)offsets.onOfferedForMarriage;
	oBrotherAdopted                                              = (tBrotherAdopted)offsets.onBrotherAdopted;
	oBecomesFactionLeader                                        = (tBecomesFactionLeader)offsets.onBecomesFactionLeader;
	oBecomesFactionHeir                                          = (tBecomesFactionHeir)offsets.onBecomesFactionHeir;
	oBecomeQuaestor                                              = (tBecomeQuaestor)offsets.onBecomeQuaestor;
	oBecomeAedile                                                = (tBecomeAedile)offsets.onBecomeAedile;
	oBecomePraetor                                               = (tBecomePraetor)offsets.onBecomePraetor;
	oBecomeConsul                                                = (tBecomeConsul)offsets.onBecomeConsul;
	oBecomeCensor                                                = (tBecomeCensor)offsets.onBecomeCensor;
	oBecomePontifexMaximus                                       = (tBecomePontifexMaximus)offsets.onBecomePontifexMaximus;
	oCeasedFactionLeader                                         = (tCeasedFactionLeader)offsets.onCeasedFactionLeader;
	oCeasedFactionHeir                                           = (tCeasedFactionHeir)offsets.onCeasedFactionHeir;
	oCeasedQuaestor                                              = (tCeasedQuaestor)offsets.onCeasedQuaestor;
	oCeasedAedile                                                = (tCeasedAedile)offsets.onCeasedAedile;
	oCeasedPraetor                                               = (tCeasedPraetor)offsets.onCeasedPraetor;
	oCeasedConsul                                                = (tCeasedConsul)offsets.onCeasedConsul;
	oCeasedCensor                                                = (tCeasedCensor)offsets.onCeasedCensor;
	oCeasedPontifexMaximus                                       = (tCeasedPontifexMaximus)offsets.onCeasedPontifexMaximus;
	oUngarrisonedFort                                            = (tUngarrisonedFort)offsets.onUngarrisonedFort;
	oLostLegionaryEagle                                          = (tLostLegionaryEagle)offsets.onLostLegionaryEagle;
	oCapturedLegionaryEagle                                      = (tCapturedLegionaryEagle)offsets.onCapturedLegionaryEagle;
//	oRecapturedLegionaryEagle                                    = (tRecapturedLegionaryEagle)offsets.onRecapturedLegionaryEagle;
	oSenateExposure                                              = (tSenateExposure)offsets.onSenateExposure;
	oQuaestorInvestigationMinor                                  = (tQuaestorInvestigationMinor)offsets.onQuaestorInvestigationMinor;
	oQuaestorInvestigation                                       = (tQuaestorInvestigation)offsets.onQuaestorInvestigation;
	oQuaestorInvestigationMajor                                  = (tQuaestorInvestigationMajor)offsets.onQuaestorInvestigationMajor;
//	oPopularSupportForOverthrow                                  = (tPopularSupportForOverthrow)offsets.onPopularSupportForOverthrow;
//	oSenateReadyToOutlawFaction                                  = (tSenateReadyToOutlawFaction)offsets.onSenateReadyToOutlawFaction;
	oSenateOutlawsFaction                                        = (tSenateOutlawsFaction)offsets.onSenateOutlawsFaction;

	DETOUR_ATTACH(&(PVOID&)oFactionTurnStart                     , onFactionTurnStart);
	DETOUR_ATTACH(&(PVOID&)oFactionWarDeclared                   , onFactionWarDeclared);
	DETOUR_ATTACH(&(PVOID&)oHordeFormed                          , onHordeFormed);
	DETOUR_ATTACH(&(PVOID&)oFactionTurnEnd                       , onFactionTurnEnd);
	DETOUR_ATTACH(&(PVOID&)oHireMercenaries                      , onHireMercenaries);
	DETOUR_ATTACH(&(PVOID&)oGeneralCaptureResidence              , onGeneralCaptureResidence);
	DETOUR_ATTACH(&(PVOID&)oGeneralCaptureWonder                 , onGeneralCaptureWonder);
	DETOUR_ATTACH(&(PVOID&)oGeneralCaptureSettlement             , onGeneralCaptureSettlement);
	DETOUR_ATTACH(&(PVOID&)oLeaderDestroyedFaction               , onLeaderDestroyedFaction);
	DETOUR_ATTACH(&(PVOID&)oDisaster                             , onDisaster);
	DETOUR_ATTACH(&(PVOID&)oCharacterDamagedByDisaster           , onCharacterDamagedByDisaster);
	DETOUR_ATTACH(&(PVOID&)oGeneralAssaultsResidence             , onGeneralAssaultsResidence);
	DETOUR_ATTACH(&(PVOID&)oOfferedForAdoption                   , onOfferedForAdoption);
	DETOUR_ATTACH(&(PVOID&)oLesserGeneralOfferedForAdoption      , onLesserGeneralOfferedForAdoption);
	DETOUR_ATTACH(&(PVOID&)oOfferedForMarriage                   , onOfferedForMarriage);
	DETOUR_ATTACH(&(PVOID&)oBrotherAdopted                       , onBrotherAdopted);
	DETOUR_ATTACH(&(PVOID&)oBecomesFactionLeader                 , onBecomesFactionLeader);
	DETOUR_ATTACH(&(PVOID&)oBecomesFactionHeir                   , onBecomesFactionHeir);
	DETOUR_ATTACH(&(PVOID&)oBecomeQuaestor                       , onBecomeQuaestor);
	DETOUR_ATTACH(&(PVOID&)oBecomeAedile                         , onBecomeAedile);
	DETOUR_ATTACH(&(PVOID&)oBecomePraetor                        , onBecomePraetor);
	DETOUR_ATTACH(&(PVOID&)oBecomeConsul                         , onBecomeConsul);
	DETOUR_ATTACH(&(PVOID&)oBecomeCensor                         , onBecomeCensor);
	DETOUR_ATTACH(&(PVOID&)oBecomePontifexMaximus                , onBecomePontifexMaximus);
	DETOUR_ATTACH(&(PVOID&)oCeasedFactionLeader                  , onCeasedFactionLeader);
	DETOUR_ATTACH(&(PVOID&)oCeasedFactionHeir                    , onCeasedFactionHeir);
	DETOUR_ATTACH(&(PVOID&)oCeasedQuaestor                       , onCeasedQuaestor);
	DETOUR_ATTACH(&(PVOID&)oCeasedAedile                         , onCeasedAedile);
	DETOUR_ATTACH(&(PVOID&)oCeasedPraetor                        , onCeasedPraetor);
	DETOUR_ATTACH(&(PVOID&)oCeasedConsul                         , onCeasedConsul);
	DETOUR_ATTACH(&(PVOID&)oCeasedCensor                         , onCeasedCensor);
	DETOUR_ATTACH(&(PVOID&)oCeasedPontifexMaximus                , onCeasedPontifexMaximus);
	DETOUR_ATTACH(&(PVOID&)oUngarrisonedFort                     , onUngarrisonedFort);
	DETOUR_ATTACH(&(PVOID&)oLostLegionaryEagle                   , onLostLegionaryEagle);
	DETOUR_ATTACH(&(PVOID&)oCapturedLegionaryEagle               , onCapturedLegionaryEagle);
//	DETOUR_ATTACH(&(PVOID&)oRecapturedLegionaryEagle             , onRecapturedLegionaryEagle);
	DETOUR_ATTACH(&(PVOID&)oSenateExposure                       , onSenateExposure);
	DETOUR_ATTACH(&(PVOID&)oQuaestorInvestigationMinor           , onQuaestorInvestigationMinor);
	DETOUR_ATTACH(&(PVOID&)oQuaestorInvestigation                , onQuaestorInvestigation);
	DETOUR_ATTACH(&(PVOID&)oQuaestorInvestigationMajor           , onQuaestorInvestigationMajor);
//	DETOUR_ATTACH(&(PVOID&)oPopularSupportForOverthrow           , onPopularSupportForOverthrow);
//	DETOUR_ATTACH(&(PVOID&)oSenateReadyToOutlawFaction           , onSenateReadyToOutlawFaction);
	DETOUR_ATTACH(&(PVOID&)oSenateOutlawsFaction                 , onSenateOutlawsFaction);


	oCharacterSelected                                           = (tCharacterSelected)offsets.onCharacterSelected;
	oSettlementSelected                                          = (tSettlementSelected)offsets.onSettlementSelected;
	oMultiTurnMove                                               = (tMultiTurnMove)offsets.onMultiTurnMove;
	oCharacterPanelOpen                                          = (tCharacterPanelOpen)offsets.onCharacterPanelOpen;
	oSettlementPanelOpen                                         = (tSettlementPanelOpen)offsets.onSettlementPanelOpen;
	oFinancesPanelOpen                                           = (tFinancesPanelOpen)offsets.onFinancesPanelOpen;
	oFactionSummaryPanelOpen                                     = (tFactionSummaryPanelOpen)offsets.onFactionSummaryPanelOpen;
	oFamilyTreePanelOpen                                         = (tFamilyTreePanelOpen)offsets.onFamilyTreePanelOpen;
//	oDiplomaticStandingPanelOpen                                 = (tDiplomaticStandingPanelOpen)offsets.onDiplomaticStandingPanelOpen;
//	oSenateMissionsPanelOpen                                     = (tSenateMissionsPanelOpen)offsets.onSenateMissionsPanelOpen;
//	oSenateOfficesPanelOpen                                      = (tSenateOfficesPanelOpen)offsets.onSenateOfficesPanelOpen;
	oDiplomacyPanelOpen                                          = (tDiplomacyPanelOpen)offsets.onDiplomacyPanelOpen;
	oPreBattlePanelOpen                                          = (tPreBattlePanelOpen)offsets.onPreBattlePanelOpen;
//	oRecruitmentPanelOpen                                        = (tRecruitmentPanelOpen)offsets.onRecruitmentPanelOpen;
//	oConstructionPanelOpen                                       = (tConstructionPanelOpen)offsets.onConstructionPanelOpen;
	oTradePanelOpen                                              = (tTradePanelOpen)offsets.onTradePanelOpen;
//	oHireMercenariesPanelOpen                                    = (tHireMercenariesPanelOpen)offsets.onHireMercenariesPanelOpen;
//	oNavalAutoResolvePanelOpen                                   = (tNavalAutoResolvePanelOpen)offsets.onNavalAutoResolvePanelOpen;
	oIncomingMessage                                             = (tIncomingMessage)offsets.onIncomingMessage;
	oMessageOpen                                                 = (tMessageOpen)offsets.onMessageOpen;
	oRequestBuildingAdvice                                       = (tRequestBuildingAdvice)offsets.onRequestBuildingAdvice;
	oRequestTrainingAdvice                                       = (tRequestTrainingAdvice)offsets.onRequestTrainingAdvice;
//	oRequestMercenariesAdvice                                    = (tRequestMercenariesAdvice)offsets.onRequestMercenariesAdvice;
	oButtonPressed                                               = (tButtonPressed)offsets.onButtonPressed;
	oShortcutTriggered                                           = (tShortcutTriggered)offsets.onShortcutTriggered;
	oScrollOpened                                                = (tScrollOpened)offsets.onScrollOpened;
	oScrollClosed                                                = (tScrollClosed)offsets.onScrollClosed;
//	oAdviceSupressed                                             = (tAdviceSupressed)offsets.onAdviceSupressed;
	oScrollAdviceRequested                                       = (tScrollAdviceRequested)offsets.onScrollAdviceRequested;
//	oPreBattleScrollAdviceRequested                              = (tPreBattleScrollAdviceRequested)offsets.onPreBattleScrollAdviceRequested;
//	oNavalPreBattleScrollAdviceRequested                         = (tNavalPreBattleScrollAdviceRequested)offsets.onNavalPreBattleScrollAdviceRequested;
	oSettlementScrollAdviceRequested                             = (tSettlementScrollAdviceRequested)offsets.onSettlementScrollAdviceRequested;
//	oIdle                                                        = (tIdle)offsets.onIdle;
//	oAbandonShowMe                                               = (tAbandonShowMe)offsets.onAbandonShowMe;
//	oScriptedAdvice                                              = (tScriptedAdvice)offsets.onScriptedAdvice;
//	oDeclineAutomatedSettlementManagement                        = (tDeclineAutomatedSettlementManagement)offsets.onDeclineAutomatedSettlementManagement;
//	oEscPressed                                                  = (tEscPressed)offsets.onEscPressed;
	oGameReloaded                                                = (tGameReloaded)offsets.onGameReloaded;

	DETOUR_ATTACH(&(PVOID&)oCharacterSelected                    , onCharacterSelected);
	DETOUR_ATTACH(&(PVOID&)oSettlementSelected                   , onSettlementSelected);
	DETOUR_ATTACH(&(PVOID&)oMultiTurnMove                        , onMultiTurnMove);
	DETOUR_ATTACH(&(PVOID&)oCharacterPanelOpen                   , onCharacterPanelOpen);
	DETOUR_ATTACH(&(PVOID&)oSettlementPanelOpen                  , onSettlementPanelOpen);
	DETOUR_ATTACH(&(PVOID&)oFinancesPanelOpen                    , onFinancesPanelOpen);
	DETOUR_ATTACH(&(PVOID&)oFactionSummaryPanelOpen              , onFactionSummaryPanelOpen);
	DETOUR_ATTACH(&(PVOID&)oFamilyTreePanelOpen                  , onFamilyTreePanelOpen);
//	DETOUR_ATTACH(&(PVOID&)oDiplomaticStandingPanelOpen          , onDiplomaticStandingPanelOpen);
//	DETOUR_ATTACH(&(PVOID&)oSenateMissionsPanelOpen              , onSenateMissionsPanelOpen);
//	DETOUR_ATTACH(&(PVOID&)oSenateOfficesPanelOpen               , onSenateOfficesPanelOpen);
	DETOUR_ATTACH(&(PVOID&)oDiplomacyPanelOpen                   , onDiplomacyPanelOpen);
	DETOUR_ATTACH(&(PVOID&)oPreBattlePanelOpen                   , onPreBattlePanelOpen);
//	DETOUR_ATTACH(&(PVOID&)oRecruitmentPanelOpen                 , onRecruitmentPanelOpen);
//	DETOUR_ATTACH(&(PVOID&)oConstructionPanelOpen                , onConstructionPanelOpen);
	DETOUR_ATTACH(&(PVOID&)oTradePanelOpen                       , onTradePanelOpen);
//	DETOUR_ATTACH(&(PVOID&)oHireMercenariesPanelOpen             , onHireMercenariesPanelOpen);
//	DETOUR_ATTACH(&(PVOID&)oNavalAutoResolvePanelOpen            , onNavalAutoResolvePanelOpen);
	DETOUR_ATTACH(&(PVOID&)oIncomingMessage                      , onIncomingMessage);
	DETOUR_ATTACH(&(PVOID&)oMessageOpen                          , onMessageOpen);
	DETOUR_ATTACH(&(PVOID&)oRequestBuildingAdvice                , onRequestBuildingAdvice);
	DETOUR_ATTACH(&(PVOID&)oRequestTrainingAdvice                , onRequestTrainingAdvice);
//	DETOUR_ATTACH(&(PVOID&)oRequestMercenariesAdvice             , onRequestMercenariesAdvice);
	DETOUR_ATTACH(&(PVOID&)oButtonPressed                        , onButtonPressed);
	DETOUR_ATTACH(&(PVOID&)oShortcutTriggered                    , onShortcutTriggered);
	DETOUR_ATTACH(&(PVOID&)oScrollOpened                         , onScrollOpened);
	DETOUR_ATTACH(&(PVOID&)oScrollClosed                         , onScrollClosed);
//	DETOUR_ATTACH(&(PVOID&)oAdviceSupressed                      , onAdviceSupressed);
	DETOUR_ATTACH(&(PVOID&)oScrollAdviceRequested                , onScrollAdviceRequested);
//	DETOUR_ATTACH(&(PVOID&)oPreBattleScrollAdviceRequested       , onPreBattleScrollAdviceRequested);
//	DETOUR_ATTACH(&(PVOID&)oNavalPreBattleScrollAdviceRequested  , onNavalPreBattleScrollAdviceRequested);
	DETOUR_ATTACH(&(PVOID&)oSettlementScrollAdviceRequested      , onSettlementScrollAdviceRequested);
//	DETOUR_ATTACH(&(PVOID&)oIdle                                 , onIdle);
//	DETOUR_ATTACH(&(PVOID&)oAbandonShowMe                        , onAbandonShowMe);
//	DETOUR_ATTACH(&(PVOID&)oScriptedAdvice                       , onScriptedAdvice);
//	DETOUR_ATTACH(&(PVOID&)oDeclineAutomatedSettlementManagement , onDeclineAutomatedSettlementManagement);
//	DETOUR_ATTACH(&(PVOID&)oEscPressed                           , onEscPressed);
	DETOUR_ATTACH(&(PVOID&)oGameReloaded                         , onGameReloaded);


	oSettlementTurnStart                                         = (tSettlementTurnStart)offsets.onSettlementTurnStart;
	oSettlementTurnEnd                                           = (tSettlementTurnEnd)offsets.onSettlementTurnEnd;
	oNewAdmiralCreated                                           = (tNewAdmiralCreated)offsets.onNewAdmiralCreated;
	oUnitTrained                                                 = (tUnitTrained)offsets.onUnitTrained;
	oGovernorUnitTrained                                         = (tGovernorUnitTrained)offsets.onGovernorUnitTrained;
	oBuildingCompleted                                           = (tBuildingCompleted)offsets.onBuildingCompleted;
	oGovernorBuildingCompleted                                   = (tGovernorBuildingCompleted)offsets.onGovernorBuildingCompleted;
//	oPlugInCompleted                                             = (tPlugInCompleted)offsets.onPlugInCompleted;
//	oGovernorPlugInCompleted                                     = (tGovernorPlugInCompleted)offsets.onGovernorPlugInCompleted;
	oAgentCreated                                                = (tAgentCreated)offsets.onAgentCreated;
	oGovernorAgentCreated                                        = (tGovernorAgentCreated)offsets.onGovernorAgentCreated;
	oBuildingDestroyed                                           = (tBuildingDestroyed)offsets.onBuildingDestroyed;
	oGovernorBuildingDestroyed                                   = (tGovernorBuildingDestroyed)offsets.onGovernorBuildingDestroyed;
	oCityRiots                                                   = (tCityRiots)offsets.onCityRiots;
	oGovernorCityRiots                                           = (tGovernorCityRiots)offsets.onGovernorCityRiots;
	oCityRebels                                                  = (tCityRebels)offsets.onCityRebels;
	oGovernorCityRebels                                          = (tGovernorCityRebels)offsets.onGovernorCityRebels;
	oGovernorThrowGames                                          = (tGovernorThrowGames)offsets.onGovernorThrowGames;
	oGovernorThrowRaces                                          = (tGovernorThrowRaces)offsets.onGovernorThrowRaces;
	oUngarrisonedSettlement                                      = (tUngarrisonedSettlement)offsets.onUngarrisonedSettlement;
	oEnslavePopulation                                           = (tEnslavePopulation)offsets.onEnslavePopulation;
	oExterminatePopulation                                       = (tExterminatePopulation)offsets.onExterminatePopulation;
	oCitySacked                                                  = (tCitySacked)offsets.onCitySacked;

	DETOUR_ATTACH(&(PVOID&)oSettlementTurnStart                  , onSettlementTurnStart);
	DETOUR_ATTACH(&(PVOID&)oSettlementTurnEnd                    , onSettlementTurnEnd);
	DETOUR_ATTACH(&(PVOID&)oNewAdmiralCreated                    , onNewAdmiralCreated);
	DETOUR_ATTACH(&(PVOID&)oUnitTrained                          , onUnitTrained);
	DETOUR_ATTACH(&(PVOID&)oGovernorUnitTrained                  , onGovernorUnitTrained);
	DETOUR_ATTACH(&(PVOID&)oBuildingCompleted                    , onBuildingCompleted);
	DETOUR_ATTACH(&(PVOID&)oGovernorBuildingCompleted            , onGovernorBuildingCompleted);
//	DETOUR_ATTACH(&(PVOID&)oPlugInCompleted                      , onPlugInCompleted);
//	DETOUR_ATTACH(&(PVOID&)oGovernorPlugInCompleted              , onGovernorPlugInCompleted);
	DETOUR_ATTACH(&(PVOID&)oAgentCreated                         , onAgentCreated);
	DETOUR_ATTACH(&(PVOID&)oGovernorAgentCreated                 , onGovernorAgentCreated);
	DETOUR_ATTACH(&(PVOID&)oBuildingDestroyed                    , onBuildingDestroyed);
	DETOUR_ATTACH(&(PVOID&)oGovernorBuildingDestroyed            , onGovernorBuildingDestroyed);
	DETOUR_ATTACH(&(PVOID&)oCityRiots                            , onCityRiots);
	DETOUR_ATTACH(&(PVOID&)oGovernorCityRiots                    , onGovernorCityRiots);
	DETOUR_ATTACH(&(PVOID&)oCityRebels                           , onCityRebels);
	DETOUR_ATTACH(&(PVOID&)oGovernorCityRebels                   , onGovernorCityRebels);
	DETOUR_ATTACH(&(PVOID&)oGovernorThrowGames                   , onGovernorThrowGames);
	DETOUR_ATTACH(&(PVOID&)oGovernorThrowRaces                   , onGovernorThrowRaces);
	DETOUR_ATTACH(&(PVOID&)oUngarrisonedSettlement               , onUngarrisonedSettlement);
	DETOUR_ATTACH(&(PVOID&)oEnslavePopulation                    , onEnslavePopulation);
	DETOUR_ATTACH(&(PVOID&)oExterminatePopulation                , onExterminatePopulation);
	DETOUR_ATTACH(&(PVOID&)oCitySacked                           , onCitySacked);
}


void monitor_event::deInitGameEvents()
{
	LOG_ALWAYS(RELEASE, "deInitGameEvents()");

	DETOUR_DETACH(&(PVOID&)oFactionTurnStart                     , onFactionTurnStart);
	DETOUR_DETACH(&(PVOID&)oFactionWarDeclared                   , onFactionWarDeclared);
	DETOUR_DETACH(&(PVOID&)oHordeFormed                          , onHordeFormed);
	DETOUR_DETACH(&(PVOID&)oFactionTurnEnd                       , onFactionTurnEnd);
	DETOUR_DETACH(&(PVOID&)oHireMercenaries                      , onHireMercenaries);
	DETOUR_DETACH(&(PVOID&)oGeneralCaptureResidence              , onGeneralCaptureResidence);
	DETOUR_DETACH(&(PVOID&)oGeneralCaptureWonder                 , onGeneralCaptureWonder);
	DETOUR_DETACH(&(PVOID&)oGeneralCaptureSettlement             , onGeneralCaptureSettlement);
	DETOUR_DETACH(&(PVOID&)oLeaderDestroyedFaction               , onLeaderDestroyedFaction);
	DETOUR_DETACH(&(PVOID&)oDisaster                             , onDisaster);
	DETOUR_DETACH(&(PVOID&)oCharacterDamagedByDisaster           , onCharacterDamagedByDisaster);
	DETOUR_DETACH(&(PVOID&)oGeneralAssaultsResidence             , onGeneralAssaultsResidence);
	DETOUR_DETACH(&(PVOID&)oOfferedForAdoption                   , onOfferedForAdoption);
	DETOUR_DETACH(&(PVOID&)oLesserGeneralOfferedForAdoption      , onLesserGeneralOfferedForAdoption);
	DETOUR_DETACH(&(PVOID&)oOfferedForMarriage                   , onOfferedForMarriage);
	DETOUR_DETACH(&(PVOID&)oBrotherAdopted                       , onBrotherAdopted);
	DETOUR_DETACH(&(PVOID&)oBecomesFactionLeader                 , onBecomesFactionLeader);
	DETOUR_DETACH(&(PVOID&)oBecomesFactionHeir                   , onBecomesFactionHeir);
	DETOUR_DETACH(&(PVOID&)oBecomeQuaestor                       , onBecomeQuaestor);
	DETOUR_DETACH(&(PVOID&)oBecomeAedile                         , onBecomeAedile);
	DETOUR_DETACH(&(PVOID&)oBecomePraetor                        , onBecomePraetor);
	DETOUR_DETACH(&(PVOID&)oBecomeConsul                         , onBecomeConsul);
	DETOUR_DETACH(&(PVOID&)oBecomeCensor                         , onBecomeCensor);
	DETOUR_DETACH(&(PVOID&)oBecomePontifexMaximus                , onBecomePontifexMaximus);
	DETOUR_DETACH(&(PVOID&)oCeasedFactionLeader                  , onCeasedFactionLeader);
	DETOUR_DETACH(&(PVOID&)oCeasedFactionHeir                    , onCeasedFactionHeir);
	DETOUR_DETACH(&(PVOID&)oCeasedQuaestor                       , onCeasedQuaestor);
	DETOUR_DETACH(&(PVOID&)oCeasedAedile                         , onCeasedAedile);
	DETOUR_DETACH(&(PVOID&)oCeasedPraetor                        , onCeasedPraetor);
	DETOUR_DETACH(&(PVOID&)oCeasedConsul                         , onCeasedConsul);
	DETOUR_DETACH(&(PVOID&)oCeasedCensor                         , onCeasedCensor);
	DETOUR_DETACH(&(PVOID&)oCeasedPontifexMaximus                , onCeasedPontifexMaximus);
	DETOUR_DETACH(&(PVOID&)oUngarrisonedFort                     , onUngarrisonedFort);
	DETOUR_DETACH(&(PVOID&)oLostLegionaryEagle                   , onLostLegionaryEagle);
	DETOUR_DETACH(&(PVOID&)oCapturedLegionaryEagle               , onCapturedLegionaryEagle);
//	DETOUR_DETACH(&(PVOID&)oRecapturedLegionaryEagle             , onRecapturedLegionaryEagle);
	DETOUR_DETACH(&(PVOID&)oSenateExposure                       , onSenateExposure);
	DETOUR_DETACH(&(PVOID&)oQuaestorInvestigationMinor           , onQuaestorInvestigationMinor);
	DETOUR_DETACH(&(PVOID&)oQuaestorInvestigation                , onQuaestorInvestigation);
	DETOUR_DETACH(&(PVOID&)oQuaestorInvestigationMajor           , onQuaestorInvestigationMajor);
//	DETOUR_DETACH(&(PVOID&)oPopularSupportForOverthrow           , onPopularSupportForOverthrow);
//	DETOUR_DETACH(&(PVOID&)oSenateReadyToOutlawFaction           , onSenateReadyToOutlawFaction);
	DETOUR_DETACH(&(PVOID&)oSenateOutlawsFaction                 , onSenateOutlawsFaction);


	DETOUR_DETACH(&(PVOID&)oCharacterSelected                    , onCharacterSelected);
	DETOUR_DETACH(&(PVOID&)oSettlementSelected                   , onSettlementSelected);
	DETOUR_DETACH(&(PVOID&)oMultiTurnMove                        , onMultiTurnMove);
	DETOUR_DETACH(&(PVOID&)oCharacterPanelOpen                   , onCharacterPanelOpen);
	DETOUR_DETACH(&(PVOID&)oSettlementPanelOpen                  , onSettlementPanelOpen);
	DETOUR_DETACH(&(PVOID&)oFinancesPanelOpen                    , onFinancesPanelOpen);
	DETOUR_DETACH(&(PVOID&)oFactionSummaryPanelOpen              , onFactionSummaryPanelOpen);
	DETOUR_DETACH(&(PVOID&)oFamilyTreePanelOpen                  , onFamilyTreePanelOpen);
//	DETOUR_DETACH(&(PVOID&)oDiplomaticStandingPanelOpen          , onDiplomaticStandingPanelOpen);
//	DETOUR_DETACH(&(PVOID&)oSenateMissionsPanelOpen              , onSenateMissionsPanelOpen);
//	DETOUR_DETACH(&(PVOID&)oSenateOfficesPanelOpen               , onSenateOfficesPanelOpen);
	DETOUR_DETACH(&(PVOID&)oDiplomacyPanelOpen                   , onDiplomacyPanelOpen);
	DETOUR_DETACH(&(PVOID&)oPreBattlePanelOpen                   , onPreBattlePanelOpen);
//	DETOUR_DETACH(&(PVOID&)oRecruitmentPanelOpen                 , onRecruitmentPanelOpen);
//	DETOUR_DETACH(&(PVOID&)oConstructionPanelOpen                , onConstructionPanelOpen);
	DETOUR_DETACH(&(PVOID&)oTradePanelOpen                       , onTradePanelOpen);
//	DETOUR_DETACH(&(PVOID&)oHireMercenariesPanelOpen             , onHireMercenariesPanelOpen);
//	DETOUR_DETACH(&(PVOID&)oNavalAutoResolvePanelOpen            , onNavalAutoResolvePanelOpen);
	DETOUR_DETACH(&(PVOID&)oIncomingMessage                      , onIncomingMessage);
	DETOUR_DETACH(&(PVOID&)oMessageOpen                          , onMessageOpen);
	DETOUR_DETACH(&(PVOID&)oRequestBuildingAdvice                , onRequestBuildingAdvice);
	DETOUR_DETACH(&(PVOID&)oRequestTrainingAdvice                , onRequestTrainingAdvice);
//	DETOUR_DETACH(&(PVOID&)oRequestMercenariesAdvice             , onRequestMercenariesAdvice);
	DETOUR_DETACH(&(PVOID&)oButtonPressed                        , onButtonPressed);
	DETOUR_DETACH(&(PVOID&)oShortcutTriggered                    , onShortcutTriggered);
	DETOUR_DETACH(&(PVOID&)oScrollOpened                         , onScrollOpened);
	DETOUR_DETACH(&(PVOID&)oScrollClosed                         , onScrollClosed);
//	DETOUR_DETACH(&(PVOID&)oAdviceSupressed                      , onAdviceSupressed);
	DETOUR_DETACH(&(PVOID&)oScrollAdviceRequested                , onScrollAdviceRequested);
//	DETOUR_DETACH(&(PVOID&)oPreBattleScrollAdviceRequested       , onPreBattleScrollAdviceRequested);
//	DETOUR_DETACH(&(PVOID&)oNavalPreBattleScrollAdviceRequested  , onNavalPreBattleScrollAdviceRequested);
	DETOUR_DETACH(&(PVOID&)oSettlementScrollAdviceRequested      , onSettlementScrollAdviceRequested);
//	DETOUR_DETACH(&(PVOID&)oIdle                                 , onIdle);
//	DETOUR_DETACH(&(PVOID&)oAbandonShowMe                        , onAbandonShowMe);
//	DETOUR_DETACH(&(PVOID&)oScriptedAdvice                       , onScriptedAdvice);
//	DETOUR_DETACH(&(PVOID&)oDeclineAutomatedSettlementManagement , onDeclineAutomatedSettlementManagement);
//	DETOUR_DETACH(&(PVOID&)oEscPressed                           , onEscPressed);
	DETOUR_DETACH(&(PVOID&)oGameReloaded                         , onGameReloaded);


	DETOUR_DETACH(&(PVOID&)oSettlementTurnStart                  , onSettlementTurnStart);
	DETOUR_DETACH(&(PVOID&)oSettlementTurnEnd                    , onSettlementTurnEnd);
	DETOUR_DETACH(&(PVOID&)oNewAdmiralCreated                    , onNewAdmiralCreated);
	DETOUR_DETACH(&(PVOID&)oUnitTrained                          , onUnitTrained);
	DETOUR_DETACH(&(PVOID&)oGovernorUnitTrained                  , onGovernorUnitTrained);
	DETOUR_DETACH(&(PVOID&)oBuildingCompleted                    , onBuildingCompleted);
	DETOUR_DETACH(&(PVOID&)oGovernorBuildingCompleted            , onGovernorBuildingCompleted);
//	DETOUR_DETACH(&(PVOID&)oPlugInCompleted                      , onPlugInCompleted);
//	DETOUR_DETACH(&(PVOID&)oGovernorPlugInCompleted              , onGovernorPlugInCompleted);
	DETOUR_DETACH(&(PVOID&)oAgentCreated                         , onAgentCreated);
	DETOUR_DETACH(&(PVOID&)oGovernorAgentCreated                 , onGovernorAgentCreated);
	DETOUR_DETACH(&(PVOID&)oBuildingDestroyed                    , onBuildingDestroyed);
	DETOUR_DETACH(&(PVOID&)oGovernorBuildingDestroyed            , onGovernorBuildingDestroyed);
	DETOUR_DETACH(&(PVOID&)oCityRiots                            , onCityRiots);
	DETOUR_DETACH(&(PVOID&)oGovernorCityRiots                    , onGovernorCityRiots);
	DETOUR_DETACH(&(PVOID&)oCityRebels                           , onCityRebels);
	DETOUR_DETACH(&(PVOID&)oGovernorCityRebels                   , onGovernorCityRebels);
	DETOUR_DETACH(&(PVOID&)oGovernorThrowGames                   , onGovernorThrowGames);
	DETOUR_DETACH(&(PVOID&)oGovernorThrowRaces                   , onGovernorThrowRaces);
	DETOUR_DETACH(&(PVOID&)oUngarrisonedSettlement               , onUngarrisonedSettlement);
	DETOUR_DETACH(&(PVOID&)oEnslavePopulation                    , onEnslavePopulation);
	DETOUR_DETACH(&(PVOID&)oExterminatePopulation                , onExterminatePopulation);
	DETOUR_DETACH(&(PVOID&)oCitySacked                           , onCitySacked);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT __fastcall monitor_event::onFactionTurnStart(void* _this, int stub, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "onFactionTurnStart(" + string(faction->factSmDescr->facName) + ")");
	return oFactionTurnStart(_this, stub, faction);
}

HRESULT __fastcall monitor_event::onFactionWarDeclared(void* _this, int stub, factionStruct* faction, factionStruct* targetfac)
{
	LOG_ALWAYS(RELEASEFULL, "onFactionWarDeclared(fac: " + string(faction->factSmDescr->facName) + ", targetfac: " + string(targetfac->factSmDescr->facName) + ")");
	return oFactionWarDeclared(_this, stub, faction, targetfac);
}

HRESULT __fastcall monitor_event::onHordeFormed(void* _this, int stub, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "onHordeFormed(" + string(faction->factSmDescr->facName) + ")");
	return oHordeFormed(_this, stub, faction);
}

HRESULT __fastcall monitor_event::onFactionTurnEnd(void* _this, int stub, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "onFactionTurnEnd(" + string(faction->factSmDescr->facName) + ")");
	HRESULT result = oFactionTurnEnd(_this, stub, faction);
	return result;
}

HRESULT __fastcall monitor_event::onHireMercenaries(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onHireMercenaries(" + string(character->fullName) + ")");
	return oHireMercenaries(_this, stub, character);
}

HRESULT __fastcall monitor_event::onGeneralCaptureResidence(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onGeneralCaptureResidence(" + string(character->fullName) + ")");
	return oGeneralCaptureResidence(_this, stub, character);
}

HRESULT __fastcall monitor_event::onGeneralCaptureWonder(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onGeneralCaptureWonder(" + string(character->fullName) + ")");
	return oGeneralCaptureWonder(_this, stub, character);
}

HRESULT __fastcall monitor_event::onGeneralCaptureSettlement(void* _this, int stub, namedCharacter* character, settlementStruct* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "onGeneralCaptureSettlement(character: " + string(character->fullName) + ", settlement: " + string(settlement->name) + ")");
	return oGeneralCaptureSettlement(_this, stub, character, settlement);
}

HRESULT __fastcall monitor_event::onLeaderDestroyedFaction(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onLeaderDestroyedFaction(" + string(character->fullName) + ")");
	return oLeaderDestroyedFaction(_this, stub, character);
}

HRESULT __fastcall monitor_event::onDisaster(void* _this, int stub, int_32 disasterType)
{
	LOG_ALWAYS(RELEASEFULL, "onDisaster(" + to_string(disasterType) + ")");
	return oDisaster(_this, stub, disasterType);
}

HRESULT __fastcall monitor_event::onCharacterDamagedByDisaster(void* _this, int stub, namedCharacter* character, int_32 disasterType)
{
	LOG_ALWAYS(RELEASEFULL, "onCharacterDamagedByDisaster(" + string(character->fullName) + ", disasterType: " + to_string(disasterType) + ")");
	return oCharacterDamagedByDisaster(_this, stub, character, disasterType);
}

HRESULT __fastcall monitor_event::onGeneralAssaultsResidence(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onGeneralAssaultsResidence(" + string(character->fullName) + ")");
	return oGeneralAssaultsResidence(_this, stub, character);
}

HRESULT __fastcall monitor_event::onOfferedForAdoption(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onOfferedForAdoption(" + string(character->fullName) + ")");
	return oOfferedForAdoption(_this, stub, character);
}

HRESULT __fastcall monitor_event::onLesserGeneralOfferedForAdoption(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onLesserGeneralOfferedForAdoption(" + string(character->fullName) + ")");
	return oLesserGeneralOfferedForAdoption(_this, stub, character);
}

HRESULT __fastcall monitor_event::onOfferedForMarriage(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onOfferedForMarriage(" + string(character->fullName) + ")");
	return oOfferedForMarriage(_this, stub, character);
}

HRESULT __fastcall monitor_event::onBrotherAdopted(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onBrotherAdopted(" + string(character->fullName) + ")");
	return oBrotherAdopted(_this, stub, character);
}

HRESULT __fastcall monitor_event::onBecomesFactionLeader(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onBecomesFactionLeader(" + string(character->fullName) + ")");
	return oBecomesFactionLeader(_this, stub, character);
}

HRESULT __fastcall monitor_event::onBecomesFactionHeir(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onBecomesFactionHeir(" + string(character->fullName) + ")");
	return oBecomesFactionHeir(_this, stub, character);
}

HRESULT __fastcall monitor_event::onBecomeQuaestor(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onBecomeQuaestor(" + string(character->fullName) + ")");
	return oBecomeQuaestor(_this, stub, character);
}

HRESULT __fastcall monitor_event::onBecomeAedile(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onBecomeAedile(" + string(character->fullName) + ")");
	return oBecomeAedile(_this, stub, character);
}

HRESULT __fastcall monitor_event::onBecomePraetor(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onBecomePraetor(" + string(character->fullName) + ")");
	return oBecomePraetor(_this, stub, character);
}

HRESULT __fastcall monitor_event::onBecomeConsul(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onBecomeConsul(" + string(character->fullName) + ")");
	return oBecomeConsul(_this, stub, character);
}

HRESULT __fastcall monitor_event::onBecomeCensor(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onBecomeCensor(" + string(character->fullName) + ")");
	return oBecomeCensor(_this, stub, character);
}

HRESULT __fastcall monitor_event::onBecomePontifexMaximus(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onBecomePontifexMaximus(" + string(character->fullName) + ")");
	return oBecomePontifexMaximus(_this, stub, character);
}

HRESULT __fastcall monitor_event::onCeasedFactionLeader(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onCeasedFactionLeader(" + string(character->fullName) + ")");
	return oCeasedFactionLeader(_this, stub, character);
}

HRESULT __fastcall monitor_event::onCeasedFactionHeir(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "oCeasedFactionHeir(" + string(character->fullName) + ")");
	return oCeasedFactionHeir(_this, stub, character);
}

HRESULT __fastcall monitor_event::onCeasedQuaestor(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "oCeasedQuaestor(" + string(character->fullName) + ")");
	return oCeasedQuaestor(_this, stub, character);
}

HRESULT __fastcall monitor_event::onCeasedAedile(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onCeasedAedile(" + string(character->fullName) + ")");
	return oCeasedAedile(_this, stub, character);
}

HRESULT __fastcall monitor_event::onCeasedPraetor(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onCeasedPraetor(" + string(character->fullName) + ")");
	return oCeasedPraetor(_this, stub, character);
}

HRESULT __fastcall monitor_event::onCeasedConsul(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onCeasedConsul(" + string(character->fullName) + ")");
	return oCeasedConsul(_this, stub, character);
}

HRESULT __fastcall monitor_event::onCeasedCensor(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onCeasedCensor(" + string(character->fullName) + ")");
	return oCeasedCensor(_this, stub, character);
}

HRESULT __fastcall monitor_event::onCeasedPontifexMaximus(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onCeasedPontifexMaximus(" + string(character->fullName) + ")");
	return oCeasedPontifexMaximus(_this, stub, character);
}

HRESULT __fastcall monitor_event::onUngarrisonedFort(void* _this, int stub, fortStruct* fort)
{
	LOG_ALWAYS(RELEASEFULL, "onUngarrisonedFort(" + to_string(fort->xCoord) + ", " + to_string(fort->yCoord) + ")");
	return oUngarrisonedFort(_this, stub, fort);
}

HRESULT __fastcall monitor_event::onLostLegionaryEagle(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onLostLegionaryEagle(" + string(character->fullName) + ")");
	return oLostLegionaryEagle(_this, stub, character);
}

HRESULT __fastcall monitor_event::onCapturedLegionaryEagle(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onCapturedLegionaryEagle(" + string(character->fullName) + ")");
	return oCapturedLegionaryEagle(_this, stub, character);
}

HRESULT __fastcall monitor_event::onSenateExposure(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onSenateExposure(" + string(character->fullName) + ")");
	return oSenateExposure(_this, stub, character);
}

HRESULT __fastcall monitor_event::onQuaestorInvestigationMinor(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onQuaestorInvestigationMinor(" + string(character->fullName) + ")");
	return oQuaestorInvestigationMinor(_this, stub, character);
}

HRESULT __fastcall monitor_event::onQuaestorInvestigation(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onQuaestorInvestigation(" + string(character->fullName) + ")");
	return oQuaestorInvestigation(_this, stub, character);
}

HRESULT __fastcall monitor_event::onQuaestorInvestigationMajor(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onQuaestorInvestigationMajor(" + string(character->fullName) + ")");
	return oQuaestorInvestigationMajor(_this, stub, character);
}

//HRESULT __fastcall monitor_event::onSenateReadyToOutlawFaction(void* _this, int stub, factionStruct* faction)
//{
//	LOG(RELEASEFULL, "onSenateReadyToOutlawFaction(" + string(faction->factSmDescr->facName) + ")");
//	return oSenateReadyToOutlawFaction(_this, stub, faction);
//}

HRESULT __fastcall monitor_event::onSenateOutlawsFaction(void* _this, int stub, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "onSenateOutlawsFaction(" + string(faction->factSmDescr->facName) + ")");
	return oSenateOutlawsFaction(_this, stub, faction);
}

HRESULT __fastcall monitor_event::onCharacterSelected(void* _this, int stub, namedCharacter* selectedChar, int_32 action, coords* coords, int_32 region_id)
{
	LOG_ALWAYS(DEVELOPMENT, "onCharacterSelected(" + string(selectedChar->fullName) + ")");
//	monitor_event::selectCharacter = selectedChar;
	return oCharacterSelected(_this, stub, selectedChar, action, coords, region_id);
}

static bool print_capabilities = true;
HRESULT __fastcall monitor_event::onSettlementSelected(void* _this, int stub, settlementStruct* settlement)
{
	if (LOG.m_current_level == BUGTEST)
	{
		int _gate_strength = settlement->capabilities.settlementCapabilities[gate_strength].value;
		int _gate_defences = settlement->capabilities.settlementCapabilities[gate_defences].value;
		int _wall_level    = settlement->capabilities.settlementCapabilities[wall_level].value;
		int _tower_level   = settlement->capabilities.settlementCapabilities[tower_level].value;
		LOG_ALWAYS(BUGTEST, "onSettlementSelected(" + string(settlement->name) +
			", gate_strength: " + to_string(_gate_strength) +
			", gate_defences: " + to_string(_gate_defences) +
			", wall_level: "    + to_string(_wall_level)    +
			", tower_level: "   + to_string(_tower_level)   +
		")");
	}
	else
	{
		LOG_ALWAYS(DEVELOPMENT, "onSettlementSelected(" + string(settlement->name) + ")");
	}
//	monitor_event::selectSettlement = settlement;
	return oSettlementSelected(_this, stub, settlement);
}

HRESULT __fastcall monitor_event::onMultiTurnMove(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(DEVELOPMENT, "onMultiTurnMove(" + string(character->fullName) + ")");
	return oMultiTurnMove(_this, stub, character);
}

HRESULT __fastcall monitor_event::onCharacterPanelOpen(void* _this, int stub, settlementStruct* settlement)
{
	LOG_ALWAYS(DEVELOPMENT, "onCharacterPanelOpen(_this, stub, settlement)");
	return oCharacterPanelOpen(_this, stub, settlement);
}

HRESULT __fastcall monitor_event::onSettlementPanelOpen(void* _this, int stub, factionStruct* faction)
{
	LOG_ALWAYS(DEVELOPMENT, "onSettlementPanelOpen(_this, stub, factionStruct* faction)");
	return oSettlementPanelOpen(_this, stub, faction);
}

HRESULT __fastcall monitor_event::onFinancesPanelOpen(void* _this, int stub, factionStruct* faction)
{
	LOG_ALWAYS(DEVELOPMENT, "onFinancesPanelOpen(_this, stub, factionStruct* faction)");
	return oFinancesPanelOpen(_this, stub, faction);
}

HRESULT __fastcall monitor_event::onFactionSummaryPanelOpen(void* _this, int stub, factionStruct* faction)
{
	LOG_ALWAYS(DEVELOPMENT, "onFactionSummaryPanelOpen(_this, stub, factionStruct* faction)");
	return oFactionSummaryPanelOpen(_this, stub, faction);
}

HRESULT __fastcall monitor_event::onFamilyTreePanelOpen(void* _this, int stub, factionStruct* faction)
{
	LOG_ALWAYS(DEVELOPMENT, "onFamilyTreePanelOpen(_this, stub, factionStruct* faction)");
	return oFamilyTreePanelOpen(_this, stub, faction);
}

//HRESULT __fastcall monitor_event::onDiplomaticStandingPanelOpen(void* _this, int stub)
//{
//	LOG(RELEASEFULL, "onDiplomaticStandingPanelOpen(_this, stub)");
//	return oDiplomaticStandingPanelOpen(_this, stub);
//}
//
//HRESULT __fastcall monitor_event::onSenateMissionsPanelOpen(void* _this, int stub, factionStruct* faction)
//{
//	LOG(RELEASEFULL, "onSenateMissionsPanelOpen(_this, stub, factionStruct* faction)");
//	return oSenateMissionsPanelOpen(_this, stub, faction);
//}
//
//HRESULT __fastcall monitor_event::onSenateOfficesPanelOpen(void* _this, int stub)
//{
//	LOG(RELEASEFULL, "onSenateOfficesPanelOpen(_this, stub)");
//	return oSenateOfficesPanelOpen(_this, stub);
//}

HRESULT __fastcall monitor_event::onDiplomacyPanelOpen(void* _this, int stub, factionStruct* faction)
{
	LOG_ALWAYS(DEVELOPMENT, "onDiplomacyPanelOpen(_this, stub, factionStruct* faction)");
	return oDiplomacyPanelOpen(_this, stub, faction);
}

HRESULT __fastcall monitor_event::onPreBattlePanelOpen(void* _this, int stub, factionStruct* faction)
{
	LOG_ALWAYS(RELEASE, "onPreBattlePanelOpen(_this, stub, factionStruct* faction)");
	return oPreBattlePanelOpen(_this, stub, faction);
}

//HRESULT __fastcall monitor_event::onRecruitmentPanelOpen(void* _this, int stub, settlementStruct* settlement)
//{
//	LOG(RELEASEFULL, "onRecruitmentPanelOpen(_this, stub, settlement)");
//	return oRecruitmentPanelOpen(_this, stub, settlement);
//}
//
//HRESULT __fastcall monitor_event::onConstructionPanelOpen(void* _this, int stub, settlementStruct* settlement)
//{
//	LOG(RELEASEFULL, "onConstructionPanelOpen(_this, stub, settlement)");
//	return oConstructionPanelOpen(_this, stub, settlement);
//}

HRESULT __fastcall monitor_event::onTradePanelOpen(void* _this, int stub, settlementStruct* settlement)
{
	LOG_ALWAYS(DEVELOPMENT, "onTradePanelOpen(_this, stub, settlement)");
	return oTradePanelOpen(_this, stub, settlement);
}

//HRESULT __fastcall monitor_event::onHireMercenariesPanelOpen(void* _this, int stub)
//{
//	LOG(RELEASEFULL, "onHireMercenariesPanelOpen(_this, stub)");
//	return oHireMercenariesPanelOpen(_this, stub);
//}
//
//HRESULT __fastcall monitor_event::onNavalAutoResolvePanelOpen(void* _this, int stub)
//{
//	LOG(RELEASEFULL, "onNavalAutoResolvePanelOpen(_this, stub)");
//	return oNavalAutoResolvePanelOpen(_this, stub);
//}

HRESULT __fastcall monitor_event::onIncomingMessage(void* _this, int stub, int eventID)
{
	LOG_ALWAYS(DEVELOPMENT, "onIncomingMessage(_this, stub, eventID)");
	return oIncomingMessage(_this, stub, eventID);
}

HRESULT __fastcall monitor_event::onMessageOpen(void* _this, int stub, int eventID)
{
	LOG_ALWAYS(DEVELOPMENT, "onMessageOpen(_this, stub, eventID)");
	return oMessageOpen(_this, stub, eventID);
}

HRESULT __fastcall monitor_event::onRequestBuildingAdvice(void* _this, int stub, settlementStruct* settlement, char* resourceDescription)
{
	LOG_ALWAYS(DEVELOPMENT, "onRequestBuildingAdvice(_this, stub, settlement, resourceDescription)");
	return oRequestBuildingAdvice(_this, stub, settlement, resourceDescription);
}

HRESULT __fastcall monitor_event::onRequestTrainingAdvice(void* _this, int stub, settlementStruct* settlement, char* resourceDescription)
{
	LOG_ALWAYS(DEVELOPMENT, "onRequestTrainingAdvice(_this, stub, settlement, resourceDescription)");
	return oRequestTrainingAdvice(_this, stub, settlement, resourceDescription);
}

//HRESULT __fastcall monitor_event::onRequestMercenariesAdvice(void* _this, int stub, stackStruct* army)
//{
//	LOG(RELEASEFULL, "onRequestMercenariesAdvice(_this, stub, stackStruct* army)");
//	return oRequestMercenariesAdvice(_this, stub, army);
//}

HRESULT __fastcall monitor_event::onButtonPressed(void* _this, int stub, char* resourceDescription)
{
	LOG_ALWAYS(DEVELOPMENT, "onButtonPressed(" + string(resourceDescription) + ")");
	return oButtonPressed(_this, stub, resourceDescription);
}

HRESULT __fastcall monitor_event::onShortcutTriggered(void* _this, int stub, char* resourceDescription1, char* resourceDescription2)
{
	LOG_ALWAYS(DEVELOPMENT, "onShortcutTriggered(" + string(resourceDescription1) + "::" + string(resourceDescription2) + ")");
	return oShortcutTriggered(_this, stub, resourceDescription1, resourceDescription2);
}

HRESULT __fastcall monitor_event::onScrollOpened(void* _this, int stub, char* resourceDescription)
{
	LOG_ALWAYS(DEVELOPMENT, "onScrollOpened(" + string(resourceDescription) + ")");

	battle_result::onScrollOpened(resourceDescription);
	HOT_SEAT_CAMPAIGN.checkDiplomacyOverviewScroll(resourceDescription, true);
	return oScrollOpened(_this, stub, resourceDescription);
}

HRESULT __fastcall monitor_event::onScrollClosed(void* _this, int stub, char* resourceDescription)
{
	LOG_ALWAYS(DEVELOPMENT, "onScrollClosed(" + string(resourceDescription) + ")");

	battle_result::onScrollClosed(resourceDescription);
	HOT_SEAT_CAMPAIGN.checkDiplomacyOverviewScroll(resourceDescription, false);
	return oScrollClosed(_this, stub, resourceDescription);
}

//HRESULT __fastcall monitor_event::onAdviceSupressed(void* _this, int stub, char* resourceDescription)
//{
//	LOG(RELEASEFULL, "onAdviceSupressed(_this, stub, resourceDescription)");
//	return oAdviceSupressed(_this, stub, resourceDescription);
//}

HRESULT __fastcall monitor_event::onScrollAdviceRequested(void* _this, int stub, char* resourceDescription)
{
	LOG_ALWAYS(DEVELOPMENT, "onScrollAdviceRequested(_this, stub, resourceDescription)");
	return oScrollAdviceRequested(_this, stub, resourceDescription);
}

//HRESULT __fastcall monitor_event::onPreBattleScrollAdviceRequested(void* _this, int stub)
//{
//	LOG(RELEASEFULL, "onPreBattleScrollAdviceRequested(_this, stub)");
//	return oPreBattleScrollAdviceRequested(_this, stub);
//}
//
//HRESULT __fastcall monitor_event::onNavalPreBattleScrollAdviceRequested(void* _this, int stub)
//{
//	LOG(RELEASEFULL, "onNavalPreBattleScrollAdviceRequested(_this, stub)");
//	return oNavalPreBattleScrollAdviceRequested(_this, stub);
//}

HRESULT __fastcall monitor_event::onSettlementScrollAdviceRequested(void* _this, int stub, settlementStruct* settlement)
{
	LOG_ALWAYS(DEVELOPMENT, "onSettlementScrollAdviceRequested(_this, stub, settlement, factionStruct* faction, int_32 region_id, resourceDescription)");
	return oSettlementScrollAdviceRequested(_this, stub, settlement);
}

//HRESULT __fastcall monitor_event::onIdle(void* _this, int stub)
//{
//	LOG(RELEASEFULL, "onIdle(_this, stub)");
//	return oIdle(_this, stub);
//}
//
//HRESULT __fastcall monitor_event::onAbandonShowMe(void* _this, int stub)
//{
//	LOG(RELEASEFULL, "onAbandonShowMe(_this, stub)");
//	return oAbandonShowMe(_this, stub);
//}
//
//HRESULT __fastcall monitor_event::onScriptedAdvice(void* _this, int stub)
//{
//	LOG(RELEASEFULL, "onScriptedAdvice(_this, stub)");
//	return oScriptedAdvice(_this, stub);
//}
//
//HRESULT __fastcall monitor_event::onDeclineAutomatedSettlementManagement(void* _this, int stub, factionStruct* faction, settlementStruct* settlement)
//{
//	LOG(RELEASEFULL, "onDeclineAutomatedSettlementManagement(_this, stub, factionStruct* faction, settlement)");
//	return oDeclineAutomatedSettlementManagement(_this, stub, faction, settlement);
//}
//
//HRESULT __fastcall monitor_event::onEscPressed(void* _this, int stub)
//{
//	LOG(RELEASEFULL, "onEscPressed(_this, stub)");
//	return oEscPressed(_this, stub);
//}

HRESULT __fastcall monitor_event::onGameReloaded(void* _this, int stub)
{
	LOG_ALWAYS(RELEASE, "onGameReloaded(_this, stub)");
	EOP_SETTLEMENTS.m_is_save_load = false;
	campaign* camp = helper_functions::getGameDataAll()->campaignData;
	return oGameReloaded(_this, stub);
}

HRESULT __fastcall monitor_event::onSettlementTurnStart(void* _this, int stub, settlementStruct* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "onSettlementTurnStart(" + string(settlement->name) + ")");
	return oSettlementTurnStart(_this, stub, settlement);
}

HRESULT __fastcall monitor_event::onSettlementTurnEnd(void* _this, int stub, settlementStruct* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "onSettlementTurnEnd(" + string(settlement->name) + ")");
	return oSettlementTurnEnd(_this, stub, settlement);
}

HRESULT __fastcall monitor_event::onNewAdmiralCreated(void* _this, int stub, settlementStruct* settlement, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onNewAdmiralCreated(_this, stub, settlement, character)");
	return oNewAdmiralCreated(_this, stub, settlement, character);
}

HRESULT __fastcall monitor_event::onUnitTrained(void* _this, int stub, factionStruct* faction, settlementStruct* settlement, unit* trainedUnit)
{
	LOG_ALWAYS(RELEASEFULL, "onUnitTrained(faction: " + string(faction->factSmDescr->facName) + ", settlement: " + string(settlement->name) + ", unit: " + string(trainedUnit->eduEntry->Type) + ")");
	return oUnitTrained(_this, stub, faction, settlement, trainedUnit);
}

HRESULT __fastcall monitor_event::onGovernorUnitTrained(void* _this, int stub, namedCharacter* character, settlementStruct* settlement, unit* trainedUnit)
{
	LOG_ALWAYS(RELEASEFULL, "onGovernorUnitTrained(character: " + string(character->fullName) + ", settlement: " + string(settlement->name) + ", unit: " + string(trainedUnit->eduEntry->Type) + ")");
	return oGovernorUnitTrained(_this, stub, character, settlement, trainedUnit);
}

HRESULT __fastcall monitor_event::onBuildingCompleted(void* _this, int stub, settlementStruct* settlement, factionStruct* faction, eventBuild* evBuild)
{
	LOG_ALWAYS(RELEASEFULL, "onBuildingCompleted(settlement: " + string(settlement->name) + ", faction: " + string(faction->factSmDescr->facName) + ", building: " + string(evBuild->edbEntry->type) + ", level: " + to_string(evBuild->newLevel) + ")");
	return oBuildingCompleted(_this, stub, settlement, faction, evBuild);
}

HRESULT __fastcall monitor_event::onGovernorBuildingCompleted(void* _this, int stub, namedCharacter* character, settlementStruct* settlement, eventBuild* evBuild)
{
	LOG_ALWAYS(RELEASEFULL, "onGovernorBuildingCompleted(character: " + string(character->fullName) + ", settlement: " + string(settlement->name) + ", building: " + string(evBuild->edbEntry->type) + ", level: " + to_string(evBuild->newLevel) + ")");
	return oGovernorBuildingCompleted(_this, stub, character, settlement, evBuild);
}

//HRESULT __fastcall monitor_event::onPlugInCompleted(void* _this, int stub, settlementStruct* settlement, eventBuild* evBuild)
//{
//	LOG(RELEASEFULL, "onPlugInCompleted(_this, stub, settlement, building)");
//	return oPlugInCompleted(_this, stub, settlement, building);
//}
//
//HRESULT __fastcall monitor_event::onGovernorPlugInCompleted(void* _this, int stub, namedCharacter* character, eventBuild* evBuild)
//{
//	LOG(RELEASEFULL, "onGovernorPlugInCompleted(_this, stub, character, building)");
//	return oGovernorPlugInCompleted(_this, stub, character, building);
//}

HRESULT __fastcall monitor_event::onAgentCreated(void* _this, int stub, namedCharacter* character, enum characterType type, settlementStruct* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "onAgentCreated(_this, stub, character, characterType, settlement)");
	return oAgentCreated(_this, stub, character, type, settlement);
}

HRESULT __fastcall monitor_event::onGovernorAgentCreated(void* _this, int stub, namedCharacter* character, enum characterType type, settlementStruct* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "onGovernorAgentCreated(_this, stub, character, characterType, settlement)");
	return oGovernorAgentCreated(_this, stub, character, type, settlement);
}

HRESULT __fastcall monitor_event::onBuildingDestroyed(void* _this, int stub)
{
	LOG_ALWAYS(RELEASEFULL, "onBuildingDestroyed(_this, stub)");
	return oBuildingDestroyed(_this, stub);
}

HRESULT __fastcall monitor_event::onGovernorBuildingDestroyed(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onGovernorBuildingDestroyed(_this, stub, character)");
	return oGovernorBuildingDestroyed(_this, stub, character);
}

HRESULT __fastcall monitor_event::onCityRiots(void* _this, int stub, settlementStruct* settlement, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "onCityRiots(_this, stub, settlement, faction)");
	return oCityRiots(_this, stub, settlement, faction);
}

HRESULT __fastcall monitor_event::onGovernorCityRiots(void* _this, int stub, namedCharacter* character, settlementStruct* settlement, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "onGovernorCityRiots(_this, stub, character, settlement, faction)");
	return oGovernorCityRiots(_this, stub, character, settlement, faction);
}

HRESULT __fastcall monitor_event::onCityRebels(void* _this, int stub, settlementStruct* settlement, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "onCityRebels(_this, stub, settlement, faction)");
	return oCityRebels(_this, stub, settlement, faction);
}

HRESULT __fastcall monitor_event::onGovernorCityRebels(void* _this, int stub, namedCharacter* character, settlementStruct* settlement, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "onGovernorCityRebels(_this, stub, character, settlement, faction)");
	return oGovernorCityRebels(_this, stub, character, settlement, faction);
}

HRESULT __fastcall monitor_event::onGovernorThrowGames(void* _this, int stub, namedCharacter* character, settlementStruct* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "onGovernorThrowGames(_this, stub, character, settlement)");
	return oGovernorThrowGames(_this, stub, character, settlement);
}

HRESULT __fastcall monitor_event::onGovernorThrowRaces(void* _this, int stub, namedCharacter* character, settlementStruct* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "onGovernorThrowRaces(_this, stub, character, settlement)");
	return oGovernorThrowRaces(_this, stub, character, settlement);
}

HRESULT __fastcall monitor_event::onUngarrisonedSettlement(void* _this, int stub, settlementStruct* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "onUngarrisonedSettlement(_this, stub, settlement)");
	return oUngarrisonedSettlement(_this, stub, settlement);
}

HRESULT __fastcall monitor_event::onEnslavePopulation(void* _this, int stub, namedCharacter* character, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "onEnslavePopulation(_this, stub, character, faction)");
	return oEnslavePopulation(_this, stub, character, faction);
}

HRESULT __fastcall monitor_event::onExterminatePopulation(void* _this, int stub, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "onExterminatePopulation(_this, stub, character)");
	return oExterminatePopulation(_this, stub, character);
}

HRESULT __fastcall monitor_event::onCitySacked(void* _this, int stub, settlementStruct* settlement, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "onCitySacked(_this, stub, settlement, faction)");
	return oCitySacked(_this, stub, settlement, faction);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void monitor_event::tests()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////





















