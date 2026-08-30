#include "monitor_event.h"
#include "../hotSeat/hotSeatCampaign.h"
#include "../hotSeat/createBattleResult.h"
#include "../../eopSettlements.h"
using namespace std;


using t_FactionTurnStart                                 = void(__thiscall*)(void* _this, factionStruct* faction);
using t_FactionWarDeclared                               = void(__thiscall*)(void* _this, factionStruct* faction, factionStruct* targetfac);
using t_HordeFormed                                      = void(__thiscall*)(void* _this, factionStruct* faction);
using t_FactionTurnEnd                                   = void(__thiscall*)(void* _this, factionStruct* faction);
using t_HireMercenaries                                  = void(__thiscall*)(void* _this, namedCharacter* character);
using t_GeneralCaptureResidence                          = void(__thiscall*)(void* _this, namedCharacter* character);
using t_GeneralCaptureWonder                             = void(__thiscall*)(void* _this, namedCharacter* character);
using t_GeneralCaptureSettlement                         = void(__thiscall*)(void* _this, namedCharacter* character, settlementStruct* settlement);
using t_LeaderDestroyedFaction                           = void(__thiscall*)(void* _this, namedCharacter* character);
using t_Disaster                                         = void(__thiscall*)(void* _this, int_32 disasterType);
using t_CharacterDamagedByDisaster                       = void(__thiscall*)(void* _this, namedCharacter* character, int_32 disasterType);
using t_GeneralAssaultsResidence                         = void(__thiscall*)(void* _this, namedCharacter* character);
using t_OfferedForAdoption                               = void(__thiscall*)(void* _this, namedCharacter* character);
using t_LesserGeneralOfferedForAdoption                  = void(__thiscall*)(void* _this, namedCharacter* character);
using t_OfferedForMarriage                               = void(__thiscall*)(void* _this, namedCharacter* character);
using t_BrotherAdopted                                   = void(__thiscall*)(void* _this, namedCharacter* character);
using t_BecomesFactionLeader                             = void(__thiscall*)(void* _this, namedCharacter* character);
using t_BecomesFactionHeir                               = void(__thiscall*)(void* _this, namedCharacter* character);
using t_BecomeQuaestor                                   = void(__thiscall*)(void* _this, namedCharacter* character);
using t_BecomeAedile                                     = void(__thiscall*)(void* _this, namedCharacter* character);
using t_BecomePraetor                                    = void(__thiscall*)(void* _this, namedCharacter* character);
using t_BecomeConsul                                     = void(__thiscall*)(void* _this, namedCharacter* character);
using t_BecomeCensor                                     = void(__thiscall*)(void* _this, namedCharacter* character);
using t_BecomePontifexMaximus                            = void(__thiscall*)(void* _this, namedCharacter* character);
using t_CeasedFactionLeader                              = void(__thiscall*)(void* _this, namedCharacter* character);
using t_CeasedFactionHeir                                = void(__thiscall*)(void* _this, namedCharacter* character);
using t_CeasedQuaestor                                   = void(__thiscall*)(void* _this, namedCharacter* character);
using t_CeasedAedile                                     = void(__thiscall*)(void* _this, namedCharacter* character);
using t_CeasedPraetor                                    = void(__thiscall*)(void* _this, namedCharacter* character);
using t_CeasedConsul                                     = void(__thiscall*)(void* _this, namedCharacter* character);
using t_CeasedCensor                                     = void(__thiscall*)(void* _this, namedCharacter* character);
using t_CeasedPontifexMaximus                            = void(__thiscall*)(void* _this, namedCharacter* character);
using t_UngarrisonedFort                                 = void(__thiscall*)(void* _this, fortStruct* fort);
using t_LostLegionaryEagle                               = void(__thiscall*)(void* _this, namedCharacter* character);
using t_CapturedLegionaryEagle                           = void(__thiscall*)(void* _this, namedCharacter* character);
//using t_RecapturedLegionaryEagle                       = void(__thiscall*)(void* _this, );
using t_SenateExposure                                   = void(__thiscall*)(void* _this, namedCharacter* character);
using t_QuaestorInvestigationMinor                       = void(__thiscall*)(void* _this, namedCharacter* character);
using t_QuaestorInvestigation                            = void(__thiscall*)(void* _this, namedCharacter* character);
using t_QuaestorInvestigationMajor                       = void(__thiscall*)(void* _this, namedCharacter* character);
//using t_PopularSupportForOverthrow                     = void(__thiscall*)(void* _this, );
using t_SenateReadyToOutlawFaction                       = void(__thiscall*)(void* _this, factionStruct* faction);
using t_SenateOutlawsFaction                             = void(__thiscall*)(void* _this, factionStruct* faction);
using t_CharacterSelected                                = void(__thiscall*)(void* _this, namedCharacter* selectedChar, int_32 action, coords* coords, int_32 region_id);
using t_SettlementSelected                               = void(__thiscall*)(void* _this, settlementStruct* settlement);
using t_MultiTurnMove                                    = void(__thiscall*)(void* _this, namedCharacter* character);
using t_CharacterPanelOpen                               = void(__thiscall*)(void* _this, settlementStruct* settlement);
using t_SettlementPanelOpen                              = void(__thiscall*)(void* _this, factionStruct* faction);
using t_FinancesPanelOpen                                = void(__thiscall*)(void* _this, factionStruct* faction);
using t_FactionSummaryPanelOpen                          = void(__thiscall*)(void* _this, factionStruct* faction);
using t_FamilyTreePanelOpen                              = void(__thiscall*)(void* _this, factionStruct* faction);
//using t_DiplomaticStandingPanelOpen                    = void(__thiscall*)(void* _this);
//using t_SenateMissionsPanelOpen                        = void(__thiscall*)(void* _this, factionStruct* faction);
using t_SenateOfficesPanelOpen                           = void(__thiscall*)(void* _this, int param_2);
using t_DiplomacyPanelOpen                               = void(__thiscall*)(void* _this, factionStruct* faction);
using t_PreBattlePanelOpen                               = void(__thiscall*)(void* _this, factionStruct* faction);
//using t_RecruitmentPanelOpen                           = void(__thiscall*)(void* _this, settlementStruct* settlement);
//using t_ConstructionPanelOpen                          = void(__thiscall*)(void* _this, settlementStruct* settlement);
using t_TradePanelOpen                                   = void(__thiscall*)(void* _this, settlementStruct* settlement);
//using t_HireMercenariesPanelOpen                       = void(__thiscall*)(void* _this);
//using t_NavalAutoResolvePanelOpen                      = void(__thiscall*)(void* _this);
using t_IncomingMessage                                  = void(__thiscall*)(void* _this, int eventID);
using t_MessageOpen                                      = void(__thiscall*)(void* _this, int eventID);
using t_RequestBuildingAdvice                            = void(__thiscall*)(void* _this, settlementStruct* settlement, char* resourceDescription);
using t_RequestTrainingAdvice                            = void(__thiscall*)(void* _this, settlementStruct* settlement, char* resourceDescription);
//using t_RequestMercenariesAdvice                       = void(__thiscall*)(void* _this, stackStruct* army);
using t_ButtonPressed                                    = void(__thiscall*)(void* _this, char* resourceDescription);
using t_ShortcutTriggered                                = void(__thiscall*)(void* _this, char* resourceDescription1, char* resourceDescription2);
using t_ScrollOpened                                     = void(__thiscall*)(void* _this, char* resourceDescription);
using t_ScrollClosed                                     = void(__thiscall*)(void* _this, char* resourceDescription);
//using t_AdviceSupressed                                = void(__thiscall*)(void* _this, char* resourceDescription);
using t_ScrollAdviceRequested                            = void(__thiscall*)(void* _this, char* resourceDescription);
//using t_PreBattleScrollAdviceRequested                 = void(__thiscall*)(void* _this);
//using t_NavalPreBattleScrollAdviceRequested            = void(__thiscall*)(void* _this);
using t_SettlementScrollAdviceRequested                  = void(__thiscall*)(void* _this, settlementStruct* settlement);
//using t_Idle                                           = void(__thiscall*)(void* _this);
//using t_AbandonShowMe                                  = void(__thiscall*)(void* _this);
//using t_ScriptedAdvice                                 = void(__thiscall*)(void* _this);
//using t_DeclineAutomatedSettlementManagement           = void(__thiscall*)(void* _this, factionStruct* faction, settlementStruct* settlement);
//using t_EscPressed                                     = void(__thiscall*)(void* _this);
using t_GameReloaded                                     = void(__thiscall*)(void* _this);
using t_SettlementTurnStart                              = void(__thiscall*)(void* _this, settlementStruct* settlement);
using t_SettlementTurnEnd                                = void(__thiscall*)(void* _this, settlementStruct* settlement);
using t_NewAdmiralCreated                                = void(__thiscall*)(void* _this, settlementStruct* settlement, namedCharacter* character);
using t_UnitTrained                                      = void(__thiscall*)(void* _this, factionStruct* faction, settlementStruct* settlement, unit* trainedUnit);
using t_GovernorUnitTrained                              = void(__thiscall*)(void* _this, namedCharacter* character, settlementStruct* settlement, unit* trainedUnit);
using t_BuildingCompleted                                = void(__thiscall*)(void* _this, settlementStruct* settlement, factionStruct* faction, eventBuild* evBuild);
using t_GovernorBuildingCompleted                        = void(__thiscall*)(void* _this, namedCharacter* character, settlementStruct* settlement, eventBuild* evBuild);
//using t_PlugInCompleted                                = void(__thiscall*)(void* _this, settlementStruct* settlement, eventBuild* evBuild);
//using t_GovernorPlugInCompleted                        = void(__thiscall*)(void* _this, namedCharacter* character, eventBuild* evBuild);
using t_AgentCreated                                     = void(__thiscall*)(void* _this, namedCharacter* character, enum characterType type, settlementStruct* settlement);
using t_GovernorAgentCreated                             = void(__thiscall*)(void* _this, namedCharacter* character, enum characterType type, settlementStruct* settlement);
using t_BuildingDestroyed                                = void(__thiscall*)(void* _this, namedCharacter* settlement);
using t_GovernorBuildingDestroyed                        = void(__thiscall*)(void* _this, namedCharacter* character);
using t_CityRiots                                        = void(__thiscall*)(void* _this, settlementStruct* settlement, factionStruct* faction);
using t_GovernorCityRiots                                = void(__thiscall*)(void* _this, namedCharacter* character, settlementStruct* settlement, factionStruct* faction);
using t_CityRebels                                       = void(__thiscall*)(void* _this, settlementStruct* settlement, factionStruct* faction);
using t_GovernorCityRebels                               = void(__thiscall*)(void* _this, namedCharacter* character, settlementStruct* settlement, factionStruct* faction);
using t_GovernorThrowGames                               = void(__thiscall*)(void* _this, namedCharacter* character, settlementStruct* settlement);
using t_GovernorThrowRaces                               = void(__thiscall*)(void* _this, namedCharacter* character, settlementStruct* settlement);
using t_UngarrisonedSettlement                           = void(__thiscall*)(void* _this, settlementStruct* settlement);
using t_EnslavePopulation                                = void(__thiscall*)(void* _this, namedCharacter* character, factionStruct* faction);
using t_ExterminatePopulation                            = void(__thiscall*)(void* _this, namedCharacter* character);
using t_CitySacked                                       = void(__thiscall*)(void* _this, settlementStruct* settlement, factionStruct* faction);
using t_PreBattle										 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_PreBattleWithdrawal								 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_BattleAiCommenced								 = void(__thiscall*)(void* _this, factionStruct* faction);
using t_BattleDelayPhaseCommenced						 = void(__thiscall*)(void* _this, factionStruct* faction);
using t_BattleDeploymentPhaseCommenced					 = void(__thiscall*)(void* _this, factionStruct* faction);
using t_BattleConflictPhaseCommenced					 = void(__thiscall*)(void* _this, factionStruct* faction);
using t_BattlePlayerUnitAttacksEnemyUnit				 = void(__thiscall*)(void* _this, unit* attacker, unit* defender);
using t_BattleEnemyUnitAttacksPlayerUnit				 = void(__thiscall*)(void* _this, unit* attacker, unit* defender);
using t_BattlePlayerAttacksSettlementBuilding			 = void(__thiscall*)(void* _this, unit* unit, buildingBattle* building);
using t_BattleEnemyAttacksSettlementBuilding			 = void(__thiscall*)(void* _this, unit* unit, buildingBattle* building);
using t_BattleUnitGoesBerserk							 = void(__thiscall*)(void* _this, unit* unit);
using t_BattlePlayerUnitGoesBerserk						 = void(__thiscall*)(void* _this, unit* unit);
using t_BattleEnemyUnitGoesBerserk						 = void(__thiscall*)(void* _this, unit* unit);
using t_BattleUnitRouts									 = void(__thiscall*)(void* _this, unit* unit);
using t_BattlePlayerUnitRouts							 = void(__thiscall*)(void* _this, unit* unit);
using t_BattleEnemyUnitRouts							 = void(__thiscall*)(void* _this, unit* unit);
using t_BattlePlayerSiegeEngineDestroyed				 = void(__thiscall*)(void* _this, siegeEngine* engine);
using t_BattleEnemySiegeEngineDestroyed					 = void(__thiscall*)(void* _this, siegeEngine* engine);
using t_PostBattle										 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_BattleArmyRouted								 = void(__thiscall*)(void* _this, stackStruct* army);
using t_BattleGeneralKilled								 = void(__thiscall*)(void* _this, character* character);
using t_BattleGeneralRouted								 = void(__thiscall*)(void* _this, character* character);
using t_BattleReinforcementsArrive						 = void(__thiscall*)(void* _this, stackStruct* army);
using t_BattleSiegeEngineDestroyed						 = void(__thiscall*)(void* _this, siegeEngine* engine);
using t_BattleSiegeEngineDocksWall						 = void(__thiscall*)(void* _this, unit* unit);
using t_BattleGatesAttackedByEngine						 = void(__thiscall*)(void* _this, siegeEngine* engine, buildingBattle* building);
using t_BattleGatesAttackedByPlayerEngine				 = void(__thiscall*)(void* _this, siegeEngine* engine, buildingBattle* building);
using t_BattleGatesAttackedByEnemyEngine				 = void(__thiscall*)(void* _this, siegeEngine* engine, buildingBattle* building);
using t_BattleBattleGatesDestroyedByEngine				 = void(__thiscall*)(void* _this, siegeEngine* engine, buildingBattle* gates);
using t_BattleWallsBreachedByEngine						 = void(__thiscall*)(void* _this, siegeEngine* engine, buildingBattle* wall);
using t_BattleWallsCaptured								 = void(__thiscall*)(void* _this, buildingBattle* building, unit* unit);
using t_BattleFinished									 = void(__thiscall*)(void* _this, battleSide* side, int reason, int result, int rating);
using t_Birth											 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_CharacterComesOfAge								 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_CharacterMarries								 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_CharacterBecomesAFather							 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_CharacterTurnStart								 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_CharacterTurnEnd								 = void(__thiscall*)(void* _this, namedCharacter* nc, settlementStruct* settlement);
using t_CharacterTurnEndInSettlemen						 = void(__thiscall*)(void* _this, namedCharacter* nc, settlementStruct* settlement);
using t_GeneralDevastatesTile							 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_SpyMission										 = void(__thiscall*)(void* _this, namedCharacter* nc, factionStruct* faction, missionEnum m);
using t_ExecutesASpyOnAMission							 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_LeaderOrderedSpyingMission						 = void(__thiscall*)(void* _this, namedCharacter* nc, factionStruct* faction, missionEnum m);
using t_AssassinationMission							 = void(__thiscall*)(void* _this, namedCharacter* nc, missionEnum m);
using t_ExecutesAnAssassinOnAMission					 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_LeaderOrderedAssassination						 = void(__thiscall*)(void* _this, namedCharacter* leader, namedCharacter* target, missionEnum m);
using t_SufferAssassinationAttempt						 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_SabotageMission									 = void(__thiscall*)(void* _this, namedCharacter* nc, missionEnum m);
using t_LeaderOrderedSabotage							 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_BriberyMission									 = void(__thiscall*)(void* _this, namedCharacter* nc, factionStruct* target, missionEnum m);
using t_LeaderOrderedBribery							 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_AcceptBribe										 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_RefuseBribe										 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_Insurrection									 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_DiplomacyMission								 = void(__thiscall*)(void* _this, namedCharacter* nc, factionStruct* faction, missionEnum m);
using t_LeaderOrderedDiplomacy							 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_LeaderSenateMissionSuccess						 = void(__thiscall*)(void* _this, namedCharacter* nc);
using t_LeaderSenateMissionFailed						 = void(__thiscall*)(void* _this, namedCharacter* nc);


t_FactionTurnStart                                       o_FactionTurnStart                        = nullptr;
t_FactionWarDeclared                                     o_FactionWarDeclared                      = nullptr;
t_HordeFormed                                            o_HordeFormed                             = nullptr;
t_FactionTurnEnd                                         o_FactionTurnEnd                          = nullptr;
t_HireMercenaries                                        o_HireMercenaries                         = nullptr;
t_GeneralCaptureResidence                                o_GeneralCaptureResidence                 = nullptr;
t_GeneralCaptureWonder                                   o_GeneralCaptureWonder                    = nullptr;
t_GeneralCaptureSettlement                               o_GeneralCaptureSettlement                = nullptr;
t_LeaderDestroyedFaction                                 o_LeaderDestroyedFaction                  = nullptr;
t_Disaster                                               o_Disaster                                = nullptr;
t_CharacterDamagedByDisaster                             o_CharacterDamagedByDisaster              = nullptr;
t_GeneralAssaultsResidence                               o_GeneralAssaultsResidence                = nullptr;
t_OfferedForAdoption                                     o_OfferedForAdoption                      = nullptr;
t_LesserGeneralOfferedForAdoption                        o_LesserGeneralOfferedForAdoption         = nullptr;
t_OfferedForMarriage                                     o_OfferedForMarriage                      = nullptr;
t_BrotherAdopted                                         o_BrotherAdopted                          = nullptr;
t_BecomesFactionLeader                                   o_BecomesFactionLeader                    = nullptr;
t_BecomesFactionHeir                                     o_BecomesFactionHeir                      = nullptr;
t_BecomeQuaestor                                         o_BecomeQuaestor                          = nullptr;
t_BecomeAedile                                           o_BecomeAedile                            = nullptr;
t_BecomePraetor                                          o_BecomePraetor                           = nullptr;
t_BecomeConsul                                           o_BecomeConsul                            = nullptr;
t_BecomeCensor                                           o_BecomeCensor                            = nullptr;
t_BecomePontifexMaximus                                  o_BecomePontifexMaximus                   = nullptr;
t_CeasedFactionLeader                                    o_CeasedFactionLeader                     = nullptr;
t_CeasedFactionHeir                                      o_CeasedFactionHeir                       = nullptr;
t_CeasedQuaestor                                         o_CeasedQuaestor                          = nullptr;
t_CeasedAedile                                           o_CeasedAedile                            = nullptr;
t_CeasedPraetor                                          o_CeasedPraetor                           = nullptr;
t_CeasedConsul                                           o_CeasedConsul                            = nullptr;
t_CeasedCensor                                           o_CeasedCensor                            = nullptr;
t_CeasedPontifexMaximus                                  o_CeasedPontifexMaximus                   = nullptr;
t_UngarrisonedFort                                       o_UngarrisonedFort                        = nullptr;
t_LostLegionaryEagle                                     o_LostLegionaryEagle                      = nullptr;
t_CapturedLegionaryEagle                                 o_CapturedLegionaryEagle                  = nullptr;
//t_RecapturedLegionaryEagle                             o_RecapturedLegionaryEagle                = nullptr;
t_SenateExposure                                         o_SenateExposure                          = nullptr;
t_QuaestorInvestigationMinor                             o_QuaestorInvestigationMinor              = nullptr;
t_QuaestorInvestigation                                  o_QuaestorInvestigation                   = nullptr;
t_QuaestorInvestigationMajor                             o_QuaestorInvestigationMajor              = nullptr;
//t_PopularSupportForOverthrow                           o_PopularSupportForOverthrow              = nullptr;
//t_SenateReadyToOutlawFaction                           o_SenateReadyToOutlawFaction              = nullptr;
t_SenateOutlawsFaction                                   o_SenateOutlawsFaction                    = nullptr;
t_CharacterSelected                                      o_CharacterSelected                       = nullptr;
t_SettlementSelected                                     o_SettlementSelected                      = nullptr;
t_MultiTurnMove                                          o_MultiTurnMove                           = nullptr;
t_CharacterPanelOpen                                     o_CharacterPanelOpen                      = nullptr;
t_SettlementPanelOpen                                    o_SettlementPanelOpen                     = nullptr;
t_FinancesPanelOpen                                      o_FinancesPanelOpen                       = nullptr;
t_FactionSummaryPanelOpen                                o_FactionSummaryPanelOpen                 = nullptr;
t_FamilyTreePanelOpen                                    o_FamilyTreePanelOpen                     = nullptr;
//t_DiplomaticStandingPanelOpen                          o_DiplomaticStandingPanelOpen             = nullptr;
//t_SenateMissionsPanelOpen                              o_SenateMissionsPanelOpen                 = nullptr;
t_SenateOfficesPanelOpen                                 o_SenateOfficesPanelOpen                  = nullptr;
t_DiplomacyPanelOpen                                     o_DiplomacyPanelOpen                      = nullptr;
t_PreBattlePanelOpen                                     o_PreBattlePanelOpen                      = nullptr;
//t_RecruitmentPanelOpen                                 o_RecruitmentPanelOpen                    = nullptr;
//t_ConstructionPanelOpen                                o_ConstructionPanelOpen                   = nullptr;
t_TradePanelOpen                                         o_TradePanelOpen                          = nullptr;
//t_HireMercenariesPanelOpen                             o_HireMercenariesPanelOpen                = nullptr;
//t_NavalAutoResolvePanelOpen                            o_NavalAutoResolvePanelOpen               = nullptr;
t_IncomingMessage                                        o_IncomingMessage                         = nullptr;
t_MessageOpen                                            o_MessageOpen                             = nullptr;
t_RequestBuildingAdvice                                  o_RequestBuildingAdvice                   = nullptr;
t_RequestTrainingAdvice                                  o_RequestTrainingAdvice                   = nullptr;
//t_RequestMercenariesAdvice                             o_RequestMercenariesAdvice                = nullptr;
t_ButtonPressed                                          o_ButtonPressed                           = nullptr;
t_ShortcutTriggered                                      o_ShortcutTriggered                       = nullptr;
t_ScrollOpened                                           o_ScrollOpened                            = nullptr;
t_ScrollClosed                                           o_ScrollClosed                            = nullptr;
//t_AdviceSupressed                                      o_AdviceSupressed                         = nullptr;
t_ScrollAdviceRequested                                  o_ScrollAdviceRequested                   = nullptr;
//t_PreBattleScrollAdviceRequested                       o_PreBattleScrollAdviceRequested          = nullptr;
//t_NavalPreBattleScrollAdviceRequested                  o_NavalPreBattleScrollAdviceRequested     = nullptr;
t_SettlementScrollAdviceRequested                        o_SettlementScrollAdviceRequested         = nullptr;
//t_Idle                                                 o_Idle                                    = nullptr;
//t_AbandonShowMe                                        o_AbandonShowMe                           = nullptr;
//t_ScriptedAdvice                                       o_ScriptedAdvice                          = nullptr;
//t_DeclineAutomatedSettlementManagement                 o_DeclineAutomatedSettlementManagement    = nullptr;
//t_EscPressed                                           o_EscPressed                              = nullptr;
t_GameReloaded                                           o_GameReloaded                            = nullptr;
t_SettlementTurnStart                                    o_SettlementTurnStart                     = nullptr;
t_SettlementTurnEnd                                      o_SettlementTurnEnd                       = nullptr;
t_NewAdmiralCreated                                      o_NewAdmiralCreated                       = nullptr;
t_UnitTrained                                            o_UnitTrained                             = nullptr;
t_GovernorUnitTrained                                    o_GovernorUnitTrained                     = nullptr;
t_BuildingCompleted                                      o_BuildingCompleted                       = nullptr;
t_GovernorBuildingCompleted                              o_GovernorBuildingCompleted               = nullptr;
//t_PlugInCompleted                                      o_PlugInCompleted                         = nullptr;
//t_GovernorPlugInCompleted                              o_GovernorPlugInCompleted                 = nullptr;
t_AgentCreated                                           o_AgentCreated                            = nullptr;
t_GovernorAgentCreated                                   o_GovernorAgentCreated                    = nullptr;
t_BuildingDestroyed                                      o_BuildingDestroyed                       = nullptr;
t_GovernorBuildingDestroyed                              o_GovernorBuildingDestroyed               = nullptr;
t_CityRiots                                              o_CityRiots                               = nullptr;
t_GovernorCityRiots                                      o_GovernorCityRiots                       = nullptr;
t_CityRebels                                             o_CityRebels                              = nullptr;
t_GovernorCityRebels                                     o_GovernorCityRebels                      = nullptr;
t_GovernorThrowGames                                     o_GovernorThrowGames                      = nullptr;
t_GovernorThrowRaces                                     o_GovernorThrowRaces                      = nullptr;
t_UngarrisonedSettlement                                 o_UngarrisonedSettlement                  = nullptr;
t_EnslavePopulation                                      o_EnslavePopulation                       = nullptr;
t_ExterminatePopulation                                  o_ExterminatePopulation                   = nullptr;
t_CitySacked                                             o_CitySacked                              = nullptr;
t_PreBattle												 o_PreBattle                               = nullptr;
t_PreBattleWithdrawal									 o_PreBattleWithdrawal                     = nullptr;
t_BattleAiCommenced										 o_BattleAiCommenced                       = nullptr;
t_BattleDelayPhaseCommenced								 o_BattleDelayPhaseCommenced               = nullptr;
t_BattleDeploymentPhaseCommenced						 o_BattleDeploymentPhaseCommenced          = nullptr;
t_BattleConflictPhaseCommenced							 o_BattleConflictPhaseCommenced            = nullptr;
t_BattlePlayerUnitAttacksEnemyUnit						 o_BattlePlayerUnitAttacksEnemyUnit        = nullptr;
t_BattleEnemyUnitAttacksPlayerUnit						 o_BattleEnemyUnitAttacksPlayerUnit        = nullptr;
t_BattlePlayerAttacksSettlementBuilding					 o_BattlePlayerAttacksSettlementBuilding   = nullptr;
t_BattleEnemyAttacksSettlementBuilding					 o_BattleEnemyAttacksSettlementBuilding    = nullptr;
t_BattleUnitGoesBerserk									 o_BattleUnitGoesBerserk                   = nullptr;
t_BattlePlayerUnitGoesBerserk							 o_BattlePlayerUnitGoesBerserk             = nullptr;
t_BattleEnemyUnitGoesBerserk							 o_BattleEnemyUnitGoesBerserk              = nullptr;
t_BattleUnitRouts										 o_BattleUnitRouts                         = nullptr;
t_BattlePlayerUnitRouts									 o_BattlePlayerUnitRouts                   = nullptr;
t_BattleEnemyUnitRouts									 o_BattleEnemyUnitRouts                    = nullptr;
t_BattlePlayerSiegeEngineDestroyed						 o_BattlePlayerSiegeEngineDestroyed        = nullptr;
t_BattleEnemySiegeEngineDestroyed						 o_BattleEnemySiegeEngineDestroyed         = nullptr;
t_PostBattle											 o_PostBattle                              = nullptr;
t_BattleArmyRouted										 o_BattleArmyRouted                        = nullptr;
t_BattleGeneralKilled									 o_BattleGeneralKilled                     = nullptr;
t_BattleGeneralRouted									 o_BattleGeneralRouted                     = nullptr;
t_BattleReinforcementsArrive							 o_BattleReinforcementsArrive              = nullptr;
t_BattleSiegeEngineDestroyed							 o_BattleSiegeEngineDestroyed              = nullptr;
t_BattleSiegeEngineDocksWall							 o_BattleSiegeEngineDocksWall              = nullptr;
t_BattleGatesAttackedByEngine							 o_BattleGatesAttackedByEngine             = nullptr;
t_BattleGatesAttackedByPlayerEngine						 o_BattleGatesAttackedByPlayerEngine       = nullptr;
t_BattleGatesAttackedByEnemyEngine						 o_BattleGatesAttackedByEnemyEngine        = nullptr;
t_BattleBattleGatesDestroyedByEngine					 o_BattleBattleGatesDestroyedByEngine      = nullptr;
t_BattleWallsBreachedByEngine							 o_BattleWallsBreachedByEngine             = nullptr;
t_BattleWallsCaptured									 o_BattleWallsCaptured                     = nullptr;
t_BattleFinished										 o_BattleFinished                          = nullptr;
t_Birth													 o_Birth                                   = nullptr;
t_CharacterComesOfAge									 o_CharacterComesOfAge                     = nullptr;
t_CharacterMarries										 o_CharacterMarries                        = nullptr;
t_CharacterBecomesAFather								 o_CharacterBecomesAFather                 = nullptr;
t_CharacterTurnStart									 o_CharacterTurnStart                      = nullptr;
t_CharacterTurnEnd										 o_CharacterTurnEnd                        = nullptr;
t_CharacterTurnEndInSettlemen							 o_CharacterTurnEndInSettlement            = nullptr;
t_GeneralDevastatesTile									 o_GeneralDevastatesTile                   = nullptr;
t_SpyMission											 o_SpyMission                              = nullptr;
t_ExecutesASpyOnAMission								 o_ExecutesASpyOnAMission                  = nullptr;
t_LeaderOrderedSpyingMission							 o_LeaderOrderedSpyingMission              = nullptr;
t_AssassinationMission									 o_AssassinationMission                    = nullptr;
t_ExecutesAnAssassinOnAMission							 o_ExecutesAnAssassinOnAMission            = nullptr;
t_LeaderOrderedAssassination							 o_LeaderOrderedAssassination              = nullptr;
t_SufferAssassinationAttempt							 o_SufferAssassinationAttempt              = nullptr;
t_SabotageMission										 o_SabotageMission                         = nullptr;
t_LeaderOrderedSabotage									 o_LeaderOrderedSabotage                   = nullptr;
t_BriberyMission										 o_BriberyMission                          = nullptr;
t_LeaderOrderedBribery									 o_LeaderOrderedBribery                    = nullptr;
t_AcceptBribe											 o_AcceptBribe                             = nullptr;
t_RefuseBribe											 o_RefuseBribe                             = nullptr;
t_Insurrection											 o_Insurrection                            = nullptr;
t_DiplomacyMission										 o_DiplomacyMission                        = nullptr;
t_LeaderOrderedDiplomacy								 o_LeaderOrderedDiplomacy                  = nullptr;
t_LeaderSenateMissionSuccess							 o_LeaderSenateMissionSuccess              = nullptr;
t_LeaderSenateMissionFailed								 o_LeaderSenateMissionFailed               = nullptr;


void monitor_event::initGameEvents()
{
	LOG_ALWAYS(RELEASE, "monitor_event::initGameEvents()");

	o_FactionTurnStart                                              = (t_FactionTurnStart)offsets.onFactionTurnStart;
	o_FactionWarDeclared                                            = (t_FactionWarDeclared)offsets.onFactionWarDeclared;
	o_HordeFormed                                                   = (t_HordeFormed)offsets.onHordeFormed;
	o_FactionTurnEnd                                                = (t_FactionTurnEnd)offsets.onFactionTurnEnd;
	o_HireMercenaries                                               = (t_HireMercenaries)offsets.onHireMercenaries;
	o_GeneralCaptureResidence                                       = (t_GeneralCaptureResidence)offsets.onGeneralCaptureResidence;
	o_GeneralCaptureWonder                                          = (t_GeneralCaptureWonder)offsets.onGeneralCaptureWonder;
	o_GeneralCaptureSettlement                                      = (t_GeneralCaptureSettlement)offsets.onGeneralCaptureSettlement;
	o_LeaderDestroyedFaction                                        = (t_LeaderDestroyedFaction)offsets.onLeaderDestroyedFaction;
	o_Disaster                                                      = (t_Disaster)offsets.onDisaster;
	o_CharacterDamagedByDisaster                                    = (t_CharacterDamagedByDisaster)offsets.onCharacterDamagedByDisaster;
	o_GeneralAssaultsResidence                                      = (t_GeneralAssaultsResidence)offsets.onGeneralAssaultsResidence;
	o_OfferedForAdoption                                            = (t_OfferedForAdoption)offsets.onOfferedForAdoption;
	o_LesserGeneralOfferedForAdoption                               = (t_LesserGeneralOfferedForAdoption)offsets.onLesserGeneralOfferedForAdoption;
	o_OfferedForMarriage                                            = (t_OfferedForMarriage)offsets.onOfferedForMarriage;
	o_BrotherAdopted                                                = (t_BrotherAdopted)offsets.onBrotherAdopted;
	o_BecomesFactionLeader                                          = (t_BecomesFactionLeader)offsets.onBecomesFactionLeader;
	o_BecomesFactionHeir                                            = (t_BecomesFactionHeir)offsets.onBecomesFactionHeir;
	o_BecomeQuaestor                                                = (t_BecomeQuaestor)offsets.onBecomeQuaestor;
	o_BecomeAedile                                                  = (t_BecomeAedile)offsets.onBecomeAedile;
	o_BecomePraetor                                                 = (t_BecomePraetor)offsets.onBecomePraetor;
	o_BecomeConsul                                                  = (t_BecomeConsul)offsets.onBecomeConsul;
	o_BecomeCensor                                                  = (t_BecomeCensor)offsets.onBecomeCensor;
	o_BecomePontifexMaximus                                         = (t_BecomePontifexMaximus)offsets.onBecomePontifexMaximus;
	o_CeasedFactionLeader                                           = (t_CeasedFactionLeader)offsets.onCeasedFactionLeader;
	o_CeasedFactionHeir                                             = (t_CeasedFactionHeir)offsets.onCeasedFactionHeir;
	o_CeasedQuaestor                                                = (t_CeasedQuaestor)offsets.onCeasedQuaestor;
	o_CeasedAedile                                                  = (t_CeasedAedile)offsets.onCeasedAedile;
	o_CeasedPraetor                                                 = (t_CeasedPraetor)offsets.onCeasedPraetor;
	o_CeasedConsul                                                  = (t_CeasedConsul)offsets.onCeasedConsul;
	o_CeasedCensor                                                  = (t_CeasedCensor)offsets.onCeasedCensor;
	o_CeasedPontifexMaximus                                         = (t_CeasedPontifexMaximus)offsets.onCeasedPontifexMaximus;
	o_UngarrisonedFort                                              = (t_UngarrisonedFort)offsets.onUngarrisonedFort;
	o_LostLegionaryEagle                                            = (t_LostLegionaryEagle)offsets.onLostLegionaryEagle;
	o_CapturedLegionaryEagle                                        = (t_CapturedLegionaryEagle)offsets.onCapturedLegionaryEagle;
//	o_RecapturedLegionaryEagle                                      = (t_RecapturedLegionaryEagle)offsets.onRecapturedLegionaryEagle;
	o_SenateExposure                                                = (t_SenateExposure)offsets.onSenateExposure;
	o_QuaestorInvestigationMinor                                    = (t_QuaestorInvestigationMinor)offsets.onQuaestorInvestigationMinor;
	o_QuaestorInvestigation                                         = (t_QuaestorInvestigation)offsets.onQuaestorInvestigation;
	o_QuaestorInvestigationMajor                                    = (t_QuaestorInvestigationMajor)offsets.onQuaestorInvestigationMajor;
//	o_PopularSupportForOverthrow                                    = (t_PopularSupportForOverthrow)offsets.onPopularSupportForOverthrow;
//	o_SenateReadyToOutlawFaction                                    = (t_SenateReadyToOutlawFaction)offsets.onSenateReadyToOutlawFaction;
	o_SenateOutlawsFaction                                          = (t_SenateOutlawsFaction)offsets.onSenateOutlawsFaction;
	o_CharacterSelected                                             = (t_CharacterSelected)offsets.onCharacterSelected;
	o_SettlementSelected                                            = (t_SettlementSelected)offsets.onSettlementSelected;
	o_MultiTurnMove                                                 = (t_MultiTurnMove)offsets.onMultiTurnMove;
	o_CharacterPanelOpen                                            = (t_CharacterPanelOpen)offsets.onCharacterPanelOpen;
	o_SettlementPanelOpen                                           = (t_SettlementPanelOpen)offsets.onSettlementPanelOpen;
	o_FinancesPanelOpen                                             = (t_FinancesPanelOpen)offsets.onFinancesPanelOpen;
	o_FactionSummaryPanelOpen                                       = (t_FactionSummaryPanelOpen)offsets.onFactionSummaryPanelOpen;
	o_FamilyTreePanelOpen                                           = (t_FamilyTreePanelOpen)offsets.onFamilyTreePanelOpen;
//	o_DiplomaticStandingPanelOpen                                   = (t_DiplomaticStandingPanelOpen)offsets.onDiplomaticStandingPanelOpen;
//	o_SenateMissionsPanelOpen                                       = (t_SenateMissionsPanelOpen)offsets.onSenateMissionsPanelOpen;
	o_SenateOfficesPanelOpen                                        = (t_SenateOfficesPanelOpen)offsets.onSenateOfficesPanelOpen;
	o_DiplomacyPanelOpen                                            = (t_DiplomacyPanelOpen)offsets.onDiplomacyPanelOpen;
	o_PreBattlePanelOpen                                            = (t_PreBattlePanelOpen)offsets.onPreBattlePanelOpen;
//	o_RecruitmentPanelOpen                                          = (t_RecruitmentPanelOpen)offsets.onRecruitmentPanelOpen;
//	o_ConstructionPanelOpen                                         = (t_ConstructionPanelOpen)offsets.onConstructionPanelOpen;
	o_TradePanelOpen                                                = (t_TradePanelOpen)offsets.onTradePanelOpen;
//	o_HireMercenariesPanelOpen                                      = (t_HireMercenariesPanelOpen)offsets.onHireMercenariesPanelOpen;
//	o_NavalAutoResolvePanelOpen                                     = (t_NavalAutoResolvePanelOpen)offsets.onNavalAutoResolvePanelOpen;
	o_IncomingMessage                                               = (t_IncomingMessage)offsets.onIncomingMessage;
	o_MessageOpen                                                   = (t_MessageOpen)offsets.onMessageOpen;
	o_RequestBuildingAdvice                                         = (t_RequestBuildingAdvice)offsets.onRequestBuildingAdvice;
	o_RequestTrainingAdvice                                         = (t_RequestTrainingAdvice)offsets.onRequestTrainingAdvice;
//	o_RequestMercenariesAdvice                                      = (t_RequestMercenariesAdvice)offsets.onRequestMercenariesAdvice;
	o_ButtonPressed                                                 = (t_ButtonPressed)offsets.onButtonPressed;
	o_ShortcutTriggered                                             = (t_ShortcutTriggered)offsets.onShortcutTriggered;
	o_ScrollOpened                                                  = (t_ScrollOpened)offsets.onScrollOpened;
	o_ScrollClosed                                                  = (t_ScrollClosed)offsets.onScrollClosed;
//	o_AdviceSupressed                                               = (t_AdviceSupressed)offsets.onAdviceSupressed;
	o_ScrollAdviceRequested                                         = (t_ScrollAdviceRequested)offsets.onScrollAdviceRequested;
//	o_PreBattleScrollAdviceRequested                                = (t_PreBattleScrollAdviceRequested)offsets.onPreBattleScrollAdviceRequested;
//	o_NavalPreBattleScrollAdviceRequested                           = (t_NavalPreBattleScrollAdviceRequested)offsets.onNavalPreBattleScrollAdviceRequested;
	o_SettlementScrollAdviceRequested                               = (t_SettlementScrollAdviceRequested)offsets.onSettlementScrollAdviceRequested;
//	o_Idle                                                          = (t_Idle)offsets.onIdle;
//	o_AbandonShowMe                                                 = (t_AbandonShowMe)offsets.onAbandonShowMe;
//	o_ScriptedAdvice                                                = (t_ScriptedAdvice)offsets.onScriptedAdvice;
//	o_DeclineAutomatedSettlementManagement                          = (t_DeclineAutomatedSettlementManagement)offsets.onDeclineAutomatedSettlementManagement;
//	o_EscPressed                                                    = (t_EscPressed)offsets.onEscPressed;
	o_GameReloaded                                                  = (t_GameReloaded)offsets.onGameReloaded;
	o_SettlementTurnStart                                           = (t_SettlementTurnStart)offsets.onSettlementTurnStart;
	o_SettlementTurnEnd                                             = (t_SettlementTurnEnd)offsets.onSettlementTurnEnd;
	o_NewAdmiralCreated                                             = (t_NewAdmiralCreated)offsets.onNewAdmiralCreated;
	o_UnitTrained                                                   = (t_UnitTrained)offsets.onUnitTrained;
	o_GovernorUnitTrained                                           = (t_GovernorUnitTrained)offsets.onGovernorUnitTrained;
	o_BuildingCompleted                                             = (t_BuildingCompleted)offsets.onBuildingCompleted;
	o_GovernorBuildingCompleted                                     = (t_GovernorBuildingCompleted)offsets.onGovernorBuildingCompleted;
//	o_PlugInCompleted                                               = (t_PlugInCompleted)offsets.onPlugInCompleted;
//	o_GovernorPlugInCompleted                                       = (t_GovernorPlugInCompleted)offsets.onGovernorPlugInCompleted;
	o_AgentCreated                                                  = (t_AgentCreated)offsets.onAgentCreated;
	o_GovernorAgentCreated                                          = (t_GovernorAgentCreated)offsets.onGovernorAgentCreated;
	o_BuildingDestroyed                                             = (t_BuildingDestroyed)offsets.onBuildingDestroyed;
	o_GovernorBuildingDestroyed                                     = (t_GovernorBuildingDestroyed)offsets.onGovernorBuildingDestroyed;
	o_CityRiots                                                     = (t_CityRiots)offsets.onCityRiots;
	o_GovernorCityRiots                                             = (t_GovernorCityRiots)offsets.onGovernorCityRiots;
	o_CityRebels                                                    = (t_CityRebels)offsets.onCityRebels;
	o_GovernorCityRebels                                            = (t_GovernorCityRebels)offsets.onGovernorCityRebels;
	o_GovernorThrowGames                                            = (t_GovernorThrowGames)offsets.onGovernorThrowGames;
	o_GovernorThrowRaces                                            = (t_GovernorThrowRaces)offsets.onGovernorThrowRaces;
	o_UngarrisonedSettlement                                        = (t_UngarrisonedSettlement)offsets.onUngarrisonedSettlement;
	o_EnslavePopulation                                             = (t_EnslavePopulation)offsets.onEnslavePopulation;
	o_ExterminatePopulation                                         = (t_ExterminatePopulation)offsets.onExterminatePopulation;
	o_CitySacked                                                    = (t_CitySacked)offsets.onCitySacked;
	o_PreBattle														= (t_PreBattle)offsets.onPreBattle;
	o_PreBattleWithdrawal											= (t_PreBattleWithdrawal)offsets.onPreBattleWithdrawal;
	o_BattleAiCommenced												= (t_BattleAiCommenced)offsets.onBattleAiCommenced;
	o_BattleDelayPhaseCommenced										= (t_BattleDelayPhaseCommenced)offsets.onBattleDelayPhaseCommenced;
	o_BattleDeploymentPhaseCommenced								= (t_BattleDeploymentPhaseCommenced)offsets.onBattleDeploymentPhaseCommenced;
	o_BattleConflictPhaseCommenced									= (t_BattleConflictPhaseCommenced)offsets.onBattleConflictPhaseCommenced;
	o_BattlePlayerUnitAttacksEnemyUnit								= (t_BattlePlayerUnitAttacksEnemyUnit)offsets.onBattlePlayerUnitAttacksEnemyUnit;
	o_BattleEnemyUnitAttacksPlayerUnit								= (t_BattleEnemyUnitAttacksPlayerUnit)offsets.onBattleEnemyUnitAttacksPlayerUnit;
	o_BattlePlayerAttacksSettlementBuilding							= (t_BattlePlayerAttacksSettlementBuilding)offsets.onBattlePlayerAttacksSettlementBuilding;
	o_BattleEnemyAttacksSettlementBuilding							= (t_BattleEnemyAttacksSettlementBuilding)offsets.onBattleEnemyAttacksSettlementBuilding;
	o_BattleUnitGoesBerserk											= (t_BattleUnitGoesBerserk)offsets.onBattleUnitGoesBerserk;
	o_BattlePlayerUnitGoesBerserk									= (t_BattlePlayerUnitGoesBerserk)offsets.onBattlePlayerUnitGoesBerserk;
	o_BattleEnemyUnitGoesBerserk									= (t_BattleEnemyUnitGoesBerserk)offsets.onBattleEnemyUnitGoesBerserk;
	o_BattleUnitRouts												= (t_BattleUnitRouts)offsets.onBattleUnitRouts;
	o_BattlePlayerUnitRouts											= (t_BattlePlayerUnitRouts)offsets.onBattlePlayerUnitRouts;
	o_BattleEnemyUnitRouts											= (t_BattleEnemyUnitRouts)offsets.onBattleEnemyUnitRouts;
	o_BattlePlayerSiegeEngineDestroyed								= (t_BattlePlayerSiegeEngineDestroyed)offsets.onBattlePlayerSiegeEngineDestroyed;
	o_BattleEnemySiegeEngineDestroyed								= (t_BattleEnemySiegeEngineDestroyed)offsets.onBattleEnemySiegeEngineDestroyed;
	o_PostBattle													= (t_PostBattle)offsets.onPostBattle;
	o_BattleArmyRouted												= (t_BattleArmyRouted)offsets.onBattleArmyRouted;
	o_BattleGeneralKilled											= (t_BattleGeneralKilled)offsets.onBattleGeneralKilled;
	o_BattleGeneralRouted											= (t_BattleGeneralRouted)offsets.onBattleGeneralRouted;
	o_BattleReinforcementsArrive									= (t_BattleReinforcementsArrive)offsets.onBattleReinforcementsArrive;
	o_BattleSiegeEngineDestroyed									= (t_BattleSiegeEngineDestroyed)offsets.onBattleSiegeEngineDestroyed;
	o_BattleSiegeEngineDocksWall									= (t_BattleSiegeEngineDocksWall)offsets.onBattleSiegeEngineDocksWall;
	o_BattleGatesAttackedByEngine									= (t_BattleGatesAttackedByEngine)offsets.onBattleGatesAttackedByEngine;
	o_BattleGatesAttackedByPlayerEngine								= (t_BattleGatesAttackedByPlayerEngine)offsets.onBattleGatesAttackedByPlayerEngine;
	o_BattleGatesAttackedByEnemyEngine								= (t_BattleGatesAttackedByEnemyEngine)offsets.onBattleGatesAttackedByEnemyEngine;
	o_BattleBattleGatesDestroyedByEngine							= (t_BattleBattleGatesDestroyedByEngine)offsets.onBattleBattleGatesDestroyedByEngine;
	o_BattleWallsBreachedByEngine									= (t_BattleWallsBreachedByEngine)offsets.onBattleWallsBreachedByEngine;
	o_BattleWallsCaptured											= (t_BattleWallsCaptured)offsets.onBattleWallsCaptured;
	o_BattleFinished												= (t_BattleFinished)offsets.onBattleFinished;
	o_Birth															= (t_Birth)offsets.onBirth;
	o_CharacterComesOfAge											= (t_CharacterComesOfAge)offsets.onCharacterComesOfAge;
	o_CharacterMarries												= (t_CharacterMarries)offsets.onCharacterMarries;
	o_CharacterBecomesAFather										= (t_CharacterBecomesAFather)offsets.onCharacterBecomesAFather;
	o_CharacterTurnStart											= (t_CharacterTurnStart)offsets.onCharacterTurnStart;
	o_CharacterTurnEnd												= (t_CharacterTurnEnd)offsets.onCharacterTurnEnd;
	o_CharacterTurnEndInSettlement									= (t_CharacterTurnEndInSettlemen)offsets.onCharacterTurnEndInSettlement;
	o_GeneralDevastatesTile											= (t_GeneralDevastatesTile)offsets.onGeneralDevastatesTile;
	o_SpyMission													= (t_SpyMission)offsets.onSpyMission;
	o_ExecutesASpyOnAMission										= (t_ExecutesASpyOnAMission)offsets.onExecutesASpyOnAMission;
	o_LeaderOrderedSpyingMission									= (t_LeaderOrderedSpyingMission)offsets.onLeaderOrderedSpyingMission;
	o_AssassinationMission											= (t_AssassinationMission)offsets.onAssassinationMission;
	o_ExecutesAnAssassinOnAMission									= (t_ExecutesAnAssassinOnAMission)offsets.onExecutesAnAssassinOnAMission;
	o_LeaderOrderedAssassination									= (t_LeaderOrderedAssassination)offsets.onLeaderOrderedAssassination;
	o_SufferAssassinationAttempt									= (t_SufferAssassinationAttempt)offsets.onSufferAssassinationAttempt;
	o_SabotageMission												= (t_SabotageMission)offsets.onSabotageMission;
	o_LeaderOrderedSabotage											= (t_LeaderOrderedSabotage)offsets.onLeaderOrderedSabotage;
	o_BriberyMission												= (t_BriberyMission)offsets.onBriberyMission;
	o_LeaderOrderedBribery											= (t_LeaderOrderedBribery)offsets.onLeaderOrderedBribery;
	o_AcceptBribe													= (t_AcceptBribe)offsets.onAcceptBribe;
	o_RefuseBribe													= (t_RefuseBribe)offsets.onRefuseBribe;
	o_Insurrection													= (t_Insurrection)offsets.onInsurrection;
	o_DiplomacyMission												= (t_DiplomacyMission)offsets.onDiplomacyMission;
	o_LeaderOrderedDiplomacy										= (t_LeaderOrderedDiplomacy)offsets.onLeaderOrderedDiplomacy;
	o_LeaderSenateMissionSuccess									= (t_LeaderSenateMissionSuccess)offsets.onLeaderSenateMissionSuccess;
	o_LeaderSenateMissionFailed										= (t_LeaderSenateMissionFailed)offsets.onLeaderSenateMissionFailed;


	DETOUR_ATTACH(&(PVOID&)o_FactionTurnStart                       , onFactionTurnStart);
	DETOUR_ATTACH(&(PVOID&)o_FactionWarDeclared                     , onFactionWarDeclared);
	DETOUR_ATTACH(&(PVOID&)o_HordeFormed                            , onHordeFormed);
	DETOUR_ATTACH(&(PVOID&)o_FactionTurnEnd                         , onFactionTurnEnd);
	DETOUR_ATTACH(&(PVOID&)o_HireMercenaries                        , onHireMercenaries);
	DETOUR_ATTACH(&(PVOID&)o_GeneralCaptureResidence                , onGeneralCaptureResidence);
	DETOUR_ATTACH(&(PVOID&)o_GeneralCaptureWonder                   , onGeneralCaptureWonder);
	DETOUR_ATTACH(&(PVOID&)o_GeneralCaptureSettlement               , onGeneralCaptureSettlement);
	DETOUR_ATTACH(&(PVOID&)o_LeaderDestroyedFaction                 , onLeaderDestroyedFaction);
	DETOUR_ATTACH(&(PVOID&)o_Disaster                               , onDisaster);
	DETOUR_ATTACH(&(PVOID&)o_CharacterDamagedByDisaster             , onCharacterDamagedByDisaster);
	DETOUR_ATTACH(&(PVOID&)o_GeneralAssaultsResidence               , onGeneralAssaultsResidence);
	DETOUR_ATTACH(&(PVOID&)o_OfferedForAdoption                     , onOfferedForAdoption);
	DETOUR_ATTACH(&(PVOID&)o_LesserGeneralOfferedForAdoption        , onLesserGeneralOfferedForAdoption);
	DETOUR_ATTACH(&(PVOID&)o_OfferedForMarriage                     , onOfferedForMarriage);
	DETOUR_ATTACH(&(PVOID&)o_BrotherAdopted                         , onBrotherAdopted);
	DETOUR_ATTACH(&(PVOID&)o_BecomesFactionLeader                   , onBecomesFactionLeader);
	DETOUR_ATTACH(&(PVOID&)o_BecomesFactionHeir                     , onBecomesFactionHeir);
	DETOUR_ATTACH(&(PVOID&)o_BecomeQuaestor                         , onBecomeQuaestor);
	DETOUR_ATTACH(&(PVOID&)o_BecomeAedile                           , onBecomeAedile);
	DETOUR_ATTACH(&(PVOID&)o_BecomePraetor                          , onBecomePraetor);
	DETOUR_ATTACH(&(PVOID&)o_BecomeConsul                           , onBecomeConsul);
	DETOUR_ATTACH(&(PVOID&)o_BecomeCensor                           , onBecomeCensor);
	DETOUR_ATTACH(&(PVOID&)o_BecomePontifexMaximus                  , onBecomePontifexMaximus);
	DETOUR_ATTACH(&(PVOID&)o_CeasedFactionLeader                    , onCeasedFactionLeader);
	DETOUR_ATTACH(&(PVOID&)o_CeasedFactionHeir                      , onCeasedFactionHeir);
	DETOUR_ATTACH(&(PVOID&)o_CeasedQuaestor                         , onCeasedQuaestor);
	DETOUR_ATTACH(&(PVOID&)o_CeasedAedile                           , onCeasedAedile);
	DETOUR_ATTACH(&(PVOID&)o_CeasedPraetor                          , onCeasedPraetor);
	DETOUR_ATTACH(&(PVOID&)o_CeasedConsul                           , onCeasedConsul);
	DETOUR_ATTACH(&(PVOID&)o_CeasedCensor                           , onCeasedCensor);
	DETOUR_ATTACH(&(PVOID&)o_CeasedPontifexMaximus                  , onCeasedPontifexMaximus);
	DETOUR_ATTACH(&(PVOID&)o_UngarrisonedFort                       , onUngarrisonedFort);
	DETOUR_ATTACH(&(PVOID&)o_LostLegionaryEagle                     , onLostLegionaryEagle);
	DETOUR_ATTACH(&(PVOID&)o_CapturedLegionaryEagle                 , onCapturedLegionaryEagle);
//	DETOUR_ATTACH(&(PVOID&)o_RecapturedLegionaryEagle               , onRecapturedLegionaryEagle);
	DETOUR_ATTACH(&(PVOID&)o_SenateExposure                         , onSenateExposure);
	DETOUR_ATTACH(&(PVOID&)o_QuaestorInvestigationMinor             , onQuaestorInvestigationMinor);
	DETOUR_ATTACH(&(PVOID&)o_QuaestorInvestigation                  , onQuaestorInvestigation);
	DETOUR_ATTACH(&(PVOID&)o_QuaestorInvestigationMajor             , onQuaestorInvestigationMajor);
//	DETOUR_ATTACH(&(PVOID&)o_PopularSupportForOverthrow             , onPopularSupportForOverthrow);
//	DETOUR_ATTACH(&(PVOID&)o_SenateReadyToOutlawFaction             , onSenateReadyToOutlawFaction);
	DETOUR_ATTACH(&(PVOID&)o_SenateOutlawsFaction                   , onSenateOutlawsFaction);
	DETOUR_ATTACH(&(PVOID&)o_CharacterSelected                      , onCharacterSelected);
	DETOUR_ATTACH(&(PVOID&)o_SettlementSelected                     , onSettlementSelected);
	DETOUR_ATTACH(&(PVOID&)o_MultiTurnMove                          , onMultiTurnMove);
	DETOUR_ATTACH(&(PVOID&)o_CharacterPanelOpen                     , onCharacterPanelOpen);
	DETOUR_ATTACH(&(PVOID&)o_SettlementPanelOpen                    , onSettlementPanelOpen);
	DETOUR_ATTACH(&(PVOID&)o_FinancesPanelOpen                      , onFinancesPanelOpen);
	DETOUR_ATTACH(&(PVOID&)o_FactionSummaryPanelOpen                , onFactionSummaryPanelOpen);
	DETOUR_ATTACH(&(PVOID&)o_FamilyTreePanelOpen                    , onFamilyTreePanelOpen);
//	DETOUR_ATTACH(&(PVOID&)o_DiplomaticStandingPanelOpen            , onDiplomaticStandingPanelOpen);
//	DETOUR_ATTACH(&(PVOID&)o_SenateMissionsPanelOpen                , onSenateMissionsPanelOpen);
	DETOUR_ATTACH(&(PVOID&)o_SenateOfficesPanelOpen                 , onSenateOfficesPanelOpen);
	DETOUR_ATTACH(&(PVOID&)o_DiplomacyPanelOpen                     , onDiplomacyPanelOpen);
	DETOUR_ATTACH(&(PVOID&)o_PreBattlePanelOpen                     , onPreBattlePanelOpen);
//	DETOUR_ATTACH(&(PVOID&)o_RecruitmentPanelOpen                   , onRecruitmentPanelOpen);
//	DETOUR_ATTACH(&(PVOID&)o_ConstructionPanelOpen                  , onConstructionPanelOpen);
	DETOUR_ATTACH(&(PVOID&)o_TradePanelOpen                         , onTradePanelOpen);
//	DETOUR_ATTACH(&(PVOID&)o_HireMercenariesPanelOpen               , onHireMercenariesPanelOpen);
//	DETOUR_ATTACH(&(PVOID&)o_NavalAutoResolvePanelOpen              , onNavalAutoResolvePanelOpen);
	DETOUR_ATTACH(&(PVOID&)o_IncomingMessage                        , onIncomingMessage);
	DETOUR_ATTACH(&(PVOID&)o_MessageOpen                            , onMessageOpen);
	DETOUR_ATTACH(&(PVOID&)o_RequestBuildingAdvice                  , onRequestBuildingAdvice);
	DETOUR_ATTACH(&(PVOID&)o_RequestTrainingAdvice                  , onRequestTrainingAdvice);
//	DETOUR_ATTACH(&(PVOID&)o_RequestMercenariesAdvice               , onRequestMercenariesAdvice);
	DETOUR_ATTACH(&(PVOID&)o_ButtonPressed                          , onButtonPressed);
	DETOUR_ATTACH(&(PVOID&)o_ShortcutTriggered                      , onShortcutTriggered);
	DETOUR_ATTACH(&(PVOID&)o_ScrollOpened                           , onScrollOpened);
	DETOUR_ATTACH(&(PVOID&)o_ScrollClosed                           , onScrollClosed);
//	DETOUR_ATTACH(&(PVOID&)o_AdviceSupressed                        , onAdviceSupressed);
	DETOUR_ATTACH(&(PVOID&)o_ScrollAdviceRequested                  , onScrollAdviceRequested);
//	DETOUR_ATTACH(&(PVOID&)o_PreBattleScrollAdviceRequested         , onPreBattleScrollAdviceRequested);
//	DETOUR_ATTACH(&(PVOID&)o_NavalPreBattleScrollAdviceRequested    , onNavalPreBattleScrollAdviceRequested);
	DETOUR_ATTACH(&(PVOID&)o_SettlementScrollAdviceRequested        , onSettlementScrollAdviceRequested);
//	DETOUR_ATTACH(&(PVOID&)o_Idle                                   , onIdle);
//	DETOUR_ATTACH(&(PVOID&)o_AbandonShowMe                          , onAbandonShowMe);
//	DETOUR_ATTACH(&(PVOID&)o_ScriptedAdvice                         , onScriptedAdvice);
//	DETOUR_ATTACH(&(PVOID&)o_DeclineAutomatedSettlementManagement   , onDeclineAutomatedSettlementManagement);
//	DETOUR_ATTACH(&(PVOID&)o_EscPressed                             , onEscPressed);
	DETOUR_ATTACH(&(PVOID&)o_GameReloaded                           , onGameReloaded);
	DETOUR_ATTACH(&(PVOID&)o_SettlementTurnStart                    , onSettlementTurnStart);
	DETOUR_ATTACH(&(PVOID&)o_SettlementTurnEnd                      , onSettlementTurnEnd);
	DETOUR_ATTACH(&(PVOID&)o_NewAdmiralCreated                      , onNewAdmiralCreated);
	DETOUR_ATTACH(&(PVOID&)o_UnitTrained                            , onUnitTrained);
	DETOUR_ATTACH(&(PVOID&)o_GovernorUnitTrained                    , onGovernorUnitTrained);
	DETOUR_ATTACH(&(PVOID&)o_BuildingCompleted                      , onBuildingCompleted);
	DETOUR_ATTACH(&(PVOID&)o_GovernorBuildingCompleted              , onGovernorBuildingCompleted);
//	DETOUR_ATTACH(&(PVOID&)o_PlugInCompleted                        , onPlugInCompleted);
//	DETOUR_ATTACH(&(PVOID&)o_GovernorPlugInCompleted                , onGovernorPlugInCompleted);
	DETOUR_ATTACH(&(PVOID&)o_AgentCreated                           , onAgentCreated);
	DETOUR_ATTACH(&(PVOID&)o_GovernorAgentCreated                   , onGovernorAgentCreated);
	DETOUR_ATTACH(&(PVOID&)o_BuildingDestroyed                      , onBuildingDestroyed);
	DETOUR_ATTACH(&(PVOID&)o_GovernorBuildingDestroyed              , onGovernorBuildingDestroyed);
	DETOUR_ATTACH(&(PVOID&)o_CityRiots                              , onCityRiots);
	DETOUR_ATTACH(&(PVOID&)o_GovernorCityRiots                      , onGovernorCityRiots);
	DETOUR_ATTACH(&(PVOID&)o_CityRebels                             , onCityRebels);
	DETOUR_ATTACH(&(PVOID&)o_GovernorCityRebels                     , onGovernorCityRebels);
	DETOUR_ATTACH(&(PVOID&)o_GovernorThrowGames                     , onGovernorThrowGames);
	DETOUR_ATTACH(&(PVOID&)o_GovernorThrowRaces                     , onGovernorThrowRaces);
	DETOUR_ATTACH(&(PVOID&)o_UngarrisonedSettlement                 , onUngarrisonedSettlement);
	DETOUR_ATTACH(&(PVOID&)o_EnslavePopulation                      , onEnslavePopulation);
	DETOUR_ATTACH(&(PVOID&)o_ExterminatePopulation                  , onExterminatePopulation);
	DETOUR_ATTACH(&(PVOID&)o_CitySacked                             , onCitySacked);
	DETOUR_ATTACH(&(PVOID&)o_PreBattle								, onPreBattle);
	DETOUR_ATTACH(&(PVOID&)o_PreBattleWithdrawal					, onPreBattleWithdrawal);
	DETOUR_ATTACH(&(PVOID&)o_BattleAiCommenced						, onBattleAiCommenced);
	DETOUR_ATTACH(&(PVOID&)o_BattleDelayPhaseCommenced				, onBattleDelayPhaseCommenced);
	DETOUR_ATTACH(&(PVOID&)o_BattleDeploymentPhaseCommenced			, onBattleDeploymentPhaseCommenced);
	DETOUR_ATTACH(&(PVOID&)o_BattleConflictPhaseCommenced			, onBattleConflictPhaseCommenced);
	DETOUR_ATTACH(&(PVOID&)o_BattlePlayerUnitAttacksEnemyUnit		, onBattlePlayerUnitAttacksEnemyUnit);
	DETOUR_ATTACH(&(PVOID&)o_BattleEnemyUnitAttacksPlayerUnit		, onBattleEnemyUnitAttacksPlayerUnit);
	DETOUR_ATTACH(&(PVOID&)o_BattlePlayerAttacksSettlementBuilding	, onBattlePlayerAttacksSettlementBuilding);
	DETOUR_ATTACH(&(PVOID&)o_BattleEnemyAttacksSettlementBuilding	, onBattleEnemyAttacksSettlementBuilding);
	DETOUR_ATTACH(&(PVOID&)o_BattleUnitGoesBerserk					, onBattleUnitGoesBerserk);
	DETOUR_ATTACH(&(PVOID&)o_BattlePlayerUnitGoesBerserk			, onBattlePlayerUnitGoesBerserk);
	DETOUR_ATTACH(&(PVOID&)o_BattleEnemyUnitGoesBerserk				, onBattleEnemyUnitGoesBerserk);
	DETOUR_ATTACH(&(PVOID&)o_BattleUnitRouts						, onBattleUnitRouts);
	DETOUR_ATTACH(&(PVOID&)o_BattlePlayerUnitRouts					, onBattlePlayerUnitRouts);
	DETOUR_ATTACH(&(PVOID&)o_BattleEnemyUnitRouts					, onBattleEnemyUnitRouts);
	DETOUR_ATTACH(&(PVOID&)o_BattlePlayerSiegeEngineDestroyed		, onBattlePlayerSiegeEngineDestroyed);
	DETOUR_ATTACH(&(PVOID&)o_BattleEnemySiegeEngineDestroyed		, onBattleEnemySiegeEngineDestroyed);
	DETOUR_ATTACH(&(PVOID&)o_PostBattle								, onPostBattle);
	DETOUR_ATTACH(&(PVOID&)o_BattleArmyRouted						, onBattleArmyRouted);
	DETOUR_ATTACH(&(PVOID&)o_BattleGeneralKilled					, onBattleGeneralKilled);
	DETOUR_ATTACH(&(PVOID&)o_BattleGeneralRouted					, onBattleGeneralRouted);
	DETOUR_ATTACH(&(PVOID&)o_BattleReinforcementsArrive				, onBattleReinforcementsArrive);
	DETOUR_ATTACH(&(PVOID&)o_BattleSiegeEngineDestroyed				, onBattleSiegeEngineDestroyed);
	DETOUR_ATTACH(&(PVOID&)o_BattleSiegeEngineDocksWall				, onBattleSiegeEngineDocksWall);
	DETOUR_ATTACH(&(PVOID&)o_BattleGatesAttackedByEngine			, onBattleGatesAttackedByEngine);
	DETOUR_ATTACH(&(PVOID&)o_BattleGatesAttackedByPlayerEngine		, onBattleGatesAttackedByPlayerEngine);
	DETOUR_ATTACH(&(PVOID&)o_BattleGatesAttackedByEnemyEngine		, onBattleGatesAttackedByEnemyEngine);
	DETOUR_ATTACH(&(PVOID&)o_BattleBattleGatesDestroyedByEngine		, onBattleBattleGatesDestroyedByEngine);
	DETOUR_ATTACH(&(PVOID&)o_BattleWallsBreachedByEngine			, onBattleWallsBreachedByEngine);
	DETOUR_ATTACH(&(PVOID&)o_BattleWallsCaptured					, onBattleWallsCaptured);
	DETOUR_ATTACH(&(PVOID&)o_BattleFinished							, onBattleFinished);
	DETOUR_ATTACH(&(PVOID&)o_Birth									, onBirth);
	DETOUR_ATTACH(&(PVOID&)o_CharacterComesOfAge					, onCharacterComesOfAge);
	DETOUR_ATTACH(&(PVOID&)o_CharacterMarries						, onCharacterMarries);
	DETOUR_ATTACH(&(PVOID&)o_CharacterBecomesAFather				, onCharacterBecomesAFather);
	DETOUR_ATTACH(&(PVOID&)o_CharacterTurnStart						, onCharacterTurnStart);
	DETOUR_ATTACH(&(PVOID&)o_CharacterTurnEnd						, onCharacterTurnEnd);
	DETOUR_ATTACH(&(PVOID&)o_CharacterTurnEndInSettlement			, onCharacterTurnEndInSettlement);
	DETOUR_ATTACH(&(PVOID&)o_GeneralDevastatesTile					, onGeneralDevastatesTile);
	DETOUR_ATTACH(&(PVOID&)o_SpyMission								, onSpyMission);
	DETOUR_ATTACH(&(PVOID&)o_ExecutesASpyOnAMission					, onExecutesASpyOnAMission);
	DETOUR_ATTACH(&(PVOID&)o_LeaderOrderedSpyingMission				, onLeaderOrderedSpyingMission);
	DETOUR_ATTACH(&(PVOID&)o_AssassinationMission					, onAssassinationMission);
	DETOUR_ATTACH(&(PVOID&)o_ExecutesAnAssassinOnAMission			, onExecutesAnAssassinOnAMission);
	DETOUR_ATTACH(&(PVOID&)o_LeaderOrderedAssassination				, onLeaderOrderedAssassination);
	DETOUR_ATTACH(&(PVOID&)o_SufferAssassinationAttempt				, onSufferAssassinationAttempt);
	DETOUR_ATTACH(&(PVOID&)o_SabotageMission						, onSabotageMission);
	DETOUR_ATTACH(&(PVOID&)o_LeaderOrderedSabotage					, onLeaderOrderedSabotage);
	DETOUR_ATTACH(&(PVOID&)o_BriberyMission							, onBriberyMission);
	DETOUR_ATTACH(&(PVOID&)o_LeaderOrderedBribery					, onLeaderOrderedBribery);
	DETOUR_ATTACH(&(PVOID&)o_AcceptBribe							, onAcceptBribe);
	DETOUR_ATTACH(&(PVOID&)o_RefuseBribe							, onRefuseBribe);
	DETOUR_ATTACH(&(PVOID&)o_Insurrection							, onInsurrection);
	DETOUR_ATTACH(&(PVOID&)o_DiplomacyMission						, onDiplomacyMission);
	DETOUR_ATTACH(&(PVOID&)o_LeaderOrderedDiplomacy					, onLeaderOrderedDiplomacy);
	DETOUR_ATTACH(&(PVOID&)o_LeaderSenateMissionSuccess				, onLeaderSenateMissionSuccess);
	DETOUR_ATTACH(&(PVOID&)o_LeaderSenateMissionFailed				, onLeaderSenateMissionFailed);
}


void monitor_event::deInitGameEvents()
{
	LOG_ALWAYS(RELEASE, "monitor_event::deInitGameEvents()");

	DETOUR_DETACH(&(PVOID&)o_FactionTurnStart                       , onFactionTurnStart);
	DETOUR_DETACH(&(PVOID&)o_FactionWarDeclared                     , onFactionWarDeclared);
	DETOUR_DETACH(&(PVOID&)o_HordeFormed                            , onHordeFormed);
	DETOUR_DETACH(&(PVOID&)o_FactionTurnEnd                         , onFactionTurnEnd);
	DETOUR_DETACH(&(PVOID&)o_HireMercenaries                        , onHireMercenaries);
	DETOUR_DETACH(&(PVOID&)o_GeneralCaptureResidence                , onGeneralCaptureResidence);
	DETOUR_DETACH(&(PVOID&)o_GeneralCaptureWonder                   , onGeneralCaptureWonder);
	DETOUR_DETACH(&(PVOID&)o_GeneralCaptureSettlement               , onGeneralCaptureSettlement);
	DETOUR_DETACH(&(PVOID&)o_LeaderDestroyedFaction                 , onLeaderDestroyedFaction);
	DETOUR_DETACH(&(PVOID&)o_Disaster                               , onDisaster);
	DETOUR_DETACH(&(PVOID&)o_CharacterDamagedByDisaster             , onCharacterDamagedByDisaster);
	DETOUR_DETACH(&(PVOID&)o_GeneralAssaultsResidence               , onGeneralAssaultsResidence);
	DETOUR_DETACH(&(PVOID&)o_OfferedForAdoption                     , onOfferedForAdoption);
	DETOUR_DETACH(&(PVOID&)o_LesserGeneralOfferedForAdoption        , onLesserGeneralOfferedForAdoption);
	DETOUR_DETACH(&(PVOID&)o_OfferedForMarriage                     , onOfferedForMarriage);
	DETOUR_DETACH(&(PVOID&)o_BrotherAdopted                         , onBrotherAdopted);
	DETOUR_DETACH(&(PVOID&)o_BecomesFactionLeader                   , onBecomesFactionLeader);
	DETOUR_DETACH(&(PVOID&)o_BecomesFactionHeir                     , onBecomesFactionHeir);
	DETOUR_DETACH(&(PVOID&)o_BecomeQuaestor                         , onBecomeQuaestor);
	DETOUR_DETACH(&(PVOID&)o_BecomeAedile                           , onBecomeAedile);
	DETOUR_DETACH(&(PVOID&)o_BecomePraetor                          , onBecomePraetor);
	DETOUR_DETACH(&(PVOID&)o_BecomeConsul                           , onBecomeConsul);
	DETOUR_DETACH(&(PVOID&)o_BecomeCensor                           , onBecomeCensor);
	DETOUR_DETACH(&(PVOID&)o_BecomePontifexMaximus                  , onBecomePontifexMaximus);
	DETOUR_DETACH(&(PVOID&)o_CeasedFactionLeader                    , onCeasedFactionLeader);
	DETOUR_DETACH(&(PVOID&)o_CeasedFactionHeir                      , onCeasedFactionHeir);
	DETOUR_DETACH(&(PVOID&)o_CeasedQuaestor                         , onCeasedQuaestor);
	DETOUR_DETACH(&(PVOID&)o_CeasedAedile                           , onCeasedAedile);
	DETOUR_DETACH(&(PVOID&)o_CeasedPraetor                          , onCeasedPraetor);
	DETOUR_DETACH(&(PVOID&)o_CeasedConsul                           , onCeasedConsul);
	DETOUR_DETACH(&(PVOID&)o_CeasedCensor                           , onCeasedCensor);
	DETOUR_DETACH(&(PVOID&)o_CeasedPontifexMaximus                  , onCeasedPontifexMaximus);
	DETOUR_DETACH(&(PVOID&)o_UngarrisonedFort                       , onUngarrisonedFort);
	DETOUR_DETACH(&(PVOID&)o_LostLegionaryEagle                     , onLostLegionaryEagle);
	DETOUR_DETACH(&(PVOID&)o_CapturedLegionaryEagle                 , onCapturedLegionaryEagle);
//	DETOUR_DETACH(&(PVOID&)o_RecapturedLegionaryEagle               , onRecapturedLegionaryEagle);
	DETOUR_DETACH(&(PVOID&)o_SenateExposure                         , onSenateExposure);
	DETOUR_DETACH(&(PVOID&)o_QuaestorInvestigationMinor             , onQuaestorInvestigationMinor);
	DETOUR_DETACH(&(PVOID&)o_QuaestorInvestigation                  , onQuaestorInvestigation);
	DETOUR_DETACH(&(PVOID&)o_QuaestorInvestigationMajor             , onQuaestorInvestigationMajor);
//	DETOUR_DETACH(&(PVOID&)o_PopularSupportForOverthrow             , onPopularSupportForOverthrow);
//	DETOUR_DETACH(&(PVOID&)o_SenateReadyToOutlawFaction             , onSenateReadyToOutlawFaction);
	DETOUR_DETACH(&(PVOID&)o_SenateOutlawsFaction                   , onSenateOutlawsFaction);
	DETOUR_DETACH(&(PVOID&)o_CharacterSelected                      , onCharacterSelected);
	DETOUR_DETACH(&(PVOID&)o_SettlementSelected                     , onSettlementSelected);
	DETOUR_DETACH(&(PVOID&)o_MultiTurnMove                          , onMultiTurnMove);
	DETOUR_DETACH(&(PVOID&)o_CharacterPanelOpen                     , onCharacterPanelOpen);
	DETOUR_DETACH(&(PVOID&)o_SettlementPanelOpen                    , onSettlementPanelOpen);
	DETOUR_DETACH(&(PVOID&)o_FinancesPanelOpen                      , onFinancesPanelOpen);
	DETOUR_DETACH(&(PVOID&)o_FactionSummaryPanelOpen                , onFactionSummaryPanelOpen);
	DETOUR_DETACH(&(PVOID&)o_FamilyTreePanelOpen                    , onFamilyTreePanelOpen);
//	DETOUR_DETACH(&(PVOID&)o_DiplomaticStandingPanelOpen            , onDiplomaticStandingPanelOpen);
//	DETOUR_DETACH(&(PVOID&)o_SenateMissionsPanelOpen                , onSenateMissionsPanelOpen);
	DETOUR_DETACH(&(PVOID&)o_SenateOfficesPanelOpen                 , onSenateOfficesPanelOpen);
	DETOUR_DETACH(&(PVOID&)o_DiplomacyPanelOpen                     , onDiplomacyPanelOpen);
	DETOUR_DETACH(&(PVOID&)o_PreBattlePanelOpen                     , onPreBattlePanelOpen);
//	DETOUR_DETACH(&(PVOID&)o_RecruitmentPanelOpen                   , onRecruitmentPanelOpen);
//	DETOUR_DETACH(&(PVOID&)o_ConstructionPanelOpen                  , onConstructionPanelOpen);
	DETOUR_DETACH(&(PVOID&)o_TradePanelOpen                         , onTradePanelOpen);
//	DETOUR_DETACH(&(PVOID&)o_HireMercenariesPanelOpen               , onHireMercenariesPanelOpen);
//	DETOUR_DETACH(&(PVOID&)o_NavalAutoResolvePanelOpen              , onNavalAutoResolvePanelOpen);
	DETOUR_DETACH(&(PVOID&)o_IncomingMessage                        , onIncomingMessage);
	DETOUR_DETACH(&(PVOID&)o_MessageOpen                            , onMessageOpen);
	DETOUR_DETACH(&(PVOID&)o_RequestBuildingAdvice                  , onRequestBuildingAdvice);
	DETOUR_DETACH(&(PVOID&)o_RequestTrainingAdvice                  , onRequestTrainingAdvice);
//	DETOUR_DETACH(&(PVOID&)o_RequestMercenariesAdvice               , onRequestMercenariesAdvice);
	DETOUR_DETACH(&(PVOID&)o_ButtonPressed                          , onButtonPressed);
	DETOUR_DETACH(&(PVOID&)o_ShortcutTriggered                      , onShortcutTriggered);
	DETOUR_DETACH(&(PVOID&)o_ScrollOpened                           , onScrollOpened);
	DETOUR_DETACH(&(PVOID&)o_ScrollClosed                           , onScrollClosed);
//	DETOUR_DETACH(&(PVOID&)o_AdviceSupressed                        , onAdviceSupressed);
	DETOUR_DETACH(&(PVOID&)o_ScrollAdviceRequested                  , onScrollAdviceRequested);
//	DETOUR_DETACH(&(PVOID&)o_PreBattleScrollAdviceRequested         , onPreBattleScrollAdviceRequested);
//	DETOUR_DETACH(&(PVOID&)o_NavalPreBattleScrollAdviceRequested    , onNavalPreBattleScrollAdviceRequested);
	DETOUR_DETACH(&(PVOID&)o_SettlementScrollAdviceRequested        , onSettlementScrollAdviceRequested);
//	DETOUR_DETACH(&(PVOID&)o_Idle                                   , onIdle);
//	DETOUR_DETACH(&(PVOID&)o_AbandonShowMe                          , onAbandonShowMe);
//	DETOUR_DETACH(&(PVOID&)o_ScriptedAdvice                         , onScriptedAdvice);
//	DETOUR_DETACH(&(PVOID&)o_DeclineAutomatedSettlementManagement   , onDeclineAutomatedSettlementManagement);
//	DETOUR_DETACH(&(PVOID&)o_EscPressed                             , onEscPressed);
	DETOUR_DETACH(&(PVOID&)o_GameReloaded                           , onGameReloaded);
	DETOUR_DETACH(&(PVOID&)o_SettlementTurnStart                    , onSettlementTurnStart);
	DETOUR_DETACH(&(PVOID&)o_SettlementTurnEnd                      , onSettlementTurnEnd);
	DETOUR_DETACH(&(PVOID&)o_NewAdmiralCreated                      , onNewAdmiralCreated);
	DETOUR_DETACH(&(PVOID&)o_UnitTrained                            , onUnitTrained);
	DETOUR_DETACH(&(PVOID&)o_GovernorUnitTrained                    , onGovernorUnitTrained);
	DETOUR_DETACH(&(PVOID&)o_BuildingCompleted                      , onBuildingCompleted);
	DETOUR_DETACH(&(PVOID&)o_GovernorBuildingCompleted              , onGovernorBuildingCompleted);
//	DETOUR_DETACH(&(PVOID&)o_PlugInCompleted                        , onPlugInCompleted);
//	DETOUR_DETACH(&(PVOID&)o_GovernorPlugInCompleted                , onGovernorPlugInCompleted);
	DETOUR_DETACH(&(PVOID&)o_AgentCreated                           , onAgentCreated);
	DETOUR_DETACH(&(PVOID&)o_GovernorAgentCreated                   , onGovernorAgentCreated);
	DETOUR_DETACH(&(PVOID&)o_BuildingDestroyed                      , onBuildingDestroyed);
	DETOUR_DETACH(&(PVOID&)o_GovernorBuildingDestroyed              , onGovernorBuildingDestroyed);
	DETOUR_DETACH(&(PVOID&)o_CityRiots                              , onCityRiots);
	DETOUR_DETACH(&(PVOID&)o_GovernorCityRiots                      , onGovernorCityRiots);
	DETOUR_DETACH(&(PVOID&)o_CityRebels                             , onCityRebels);
	DETOUR_DETACH(&(PVOID&)o_GovernorCityRebels                     , onGovernorCityRebels);
	DETOUR_DETACH(&(PVOID&)o_GovernorThrowGames                     , onGovernorThrowGames);
	DETOUR_DETACH(&(PVOID&)o_GovernorThrowRaces                     , onGovernorThrowRaces);
	DETOUR_DETACH(&(PVOID&)o_UngarrisonedSettlement                 , onUngarrisonedSettlement);
	DETOUR_DETACH(&(PVOID&)o_EnslavePopulation                      , onEnslavePopulation);
	DETOUR_DETACH(&(PVOID&)o_ExterminatePopulation                  , onExterminatePopulation);
	DETOUR_DETACH(&(PVOID&)o_CitySacked                             , onCitySacked);
	DETOUR_DETACH(&(PVOID&)o_PreBattle								, onPreBattle);
	DETOUR_DETACH(&(PVOID&)o_PreBattleWithdrawal					, onPreBattleWithdrawal);
	DETOUR_DETACH(&(PVOID&)o_BattleAiCommenced						, onBattleAiCommenced);
	DETOUR_DETACH(&(PVOID&)o_BattleDelayPhaseCommenced				, onBattleDelayPhaseCommenced);
	DETOUR_DETACH(&(PVOID&)o_BattleDeploymentPhaseCommenced			, onBattleDeploymentPhaseCommenced);
	DETOUR_DETACH(&(PVOID&)o_BattleConflictPhaseCommenced			, onBattleConflictPhaseCommenced);
	DETOUR_DETACH(&(PVOID&)o_BattlePlayerUnitAttacksEnemyUnit		, onBattlePlayerUnitAttacksEnemyUnit);
	DETOUR_DETACH(&(PVOID&)o_BattleEnemyUnitAttacksPlayerUnit		, onBattleEnemyUnitAttacksPlayerUnit);
	DETOUR_DETACH(&(PVOID&)o_BattlePlayerAttacksSettlementBuilding	, onBattlePlayerAttacksSettlementBuilding);
	DETOUR_DETACH(&(PVOID&)o_BattleEnemyAttacksSettlementBuilding	, onBattleEnemyAttacksSettlementBuilding);
	DETOUR_DETACH(&(PVOID&)o_BattleUnitGoesBerserk					, onBattleUnitGoesBerserk);
	DETOUR_DETACH(&(PVOID&)o_BattlePlayerUnitGoesBerserk			, onBattlePlayerUnitGoesBerserk);
	DETOUR_DETACH(&(PVOID&)o_BattleEnemyUnitGoesBerserk				, onBattleEnemyUnitGoesBerserk);
	DETOUR_DETACH(&(PVOID&)o_BattleUnitRouts						, onBattleUnitRouts);
	DETOUR_DETACH(&(PVOID&)o_BattlePlayerUnitRouts					, onBattlePlayerUnitRouts);
	DETOUR_DETACH(&(PVOID&)o_BattleEnemyUnitRouts					, onBattleEnemyUnitRouts);
	DETOUR_DETACH(&(PVOID&)o_BattlePlayerSiegeEngineDestroyed		, onBattlePlayerSiegeEngineDestroyed);
	DETOUR_DETACH(&(PVOID&)o_BattleEnemySiegeEngineDestroyed		, onBattleEnemySiegeEngineDestroyed);
	DETOUR_DETACH(&(PVOID&)o_PostBattle								, onPostBattle);
	DETOUR_DETACH(&(PVOID&)o_BattleArmyRouted						, onBattleArmyRouted);
	DETOUR_DETACH(&(PVOID&)o_BattleGeneralKilled					, onBattleGeneralKilled);
	DETOUR_DETACH(&(PVOID&)o_BattleGeneralRouted					, onBattleGeneralRouted);
	DETOUR_DETACH(&(PVOID&)o_BattleReinforcementsArrive				, onBattleReinforcementsArrive);
	DETOUR_DETACH(&(PVOID&)o_BattleSiegeEngineDestroyed				, onBattleSiegeEngineDestroyed);
	DETOUR_DETACH(&(PVOID&)o_BattleSiegeEngineDocksWall				, onBattleSiegeEngineDocksWall);
	DETOUR_DETACH(&(PVOID&)o_BattleGatesAttackedByEngine			, onBattleGatesAttackedByEngine);
	DETOUR_DETACH(&(PVOID&)o_BattleGatesAttackedByPlayerEngine		, onBattleGatesAttackedByPlayerEngine);
	DETOUR_DETACH(&(PVOID&)o_BattleGatesAttackedByEnemyEngine		, onBattleGatesAttackedByEnemyEngine);
	DETOUR_DETACH(&(PVOID&)o_BattleBattleGatesDestroyedByEngine		, onBattleBattleGatesDestroyedByEngine);
	DETOUR_DETACH(&(PVOID&)o_BattleWallsBreachedByEngine			, onBattleWallsBreachedByEngine);
	DETOUR_DETACH(&(PVOID&)o_BattleWallsCaptured					, onBattleWallsCaptured);
	DETOUR_DETACH(&(PVOID&)o_BattleFinished							, onBattleFinished);
	DETOUR_DETACH(&(PVOID&)o_Birth									, onBirth);
	DETOUR_DETACH(&(PVOID&)o_CharacterComesOfAge					, onCharacterComesOfAge);
	DETOUR_DETACH(&(PVOID&)o_CharacterMarries						, onCharacterMarries);
	DETOUR_DETACH(&(PVOID&)o_CharacterBecomesAFather				, onCharacterBecomesAFather);
	DETOUR_DETACH(&(PVOID&)o_CharacterTurnStart						, onCharacterTurnStart);
	DETOUR_DETACH(&(PVOID&)o_CharacterTurnEnd						, onCharacterTurnEnd);
	DETOUR_DETACH(&(PVOID&)o_CharacterTurnEndInSettlement			, onCharacterTurnEndInSettlement);
	DETOUR_DETACH(&(PVOID&)o_GeneralDevastatesTile					, onGeneralDevastatesTile);
	DETOUR_DETACH(&(PVOID&)o_SpyMission								, onSpyMission);
	DETOUR_DETACH(&(PVOID&)o_ExecutesASpyOnAMission					, onExecutesASpyOnAMission);
	DETOUR_DETACH(&(PVOID&)o_LeaderOrderedSpyingMission				, onLeaderOrderedSpyingMission);
	DETOUR_DETACH(&(PVOID&)o_AssassinationMission					, onAssassinationMission);
	DETOUR_DETACH(&(PVOID&)o_ExecutesAnAssassinOnAMission			, onExecutesAnAssassinOnAMission);
	DETOUR_DETACH(&(PVOID&)o_LeaderOrderedAssassination				, onLeaderOrderedAssassination);
	DETOUR_DETACH(&(PVOID&)o_SufferAssassinationAttempt				, onSufferAssassinationAttempt);
	DETOUR_DETACH(&(PVOID&)o_SabotageMission						, onSabotageMission);
	DETOUR_DETACH(&(PVOID&)o_LeaderOrderedSabotage					, onLeaderOrderedSabotage);
	DETOUR_DETACH(&(PVOID&)o_BriberyMission							, onBriberyMission);
	DETOUR_DETACH(&(PVOID&)o_LeaderOrderedBribery					, onLeaderOrderedBribery);
	DETOUR_DETACH(&(PVOID&)o_AcceptBribe							, onAcceptBribe);
	DETOUR_DETACH(&(PVOID&)o_RefuseBribe							, onRefuseBribe);
	DETOUR_DETACH(&(PVOID&)o_Insurrection							, onInsurrection);
	DETOUR_DETACH(&(PVOID&)o_DiplomacyMission						, onDiplomacyMission);
	DETOUR_DETACH(&(PVOID&)o_LeaderOrderedDiplomacy					, onLeaderOrderedDiplomacy);
	DETOUR_DETACH(&(PVOID&)o_LeaderSenateMissionSuccess				, onLeaderSenateMissionSuccess);
	DETOUR_DETACH(&(PVOID&)o_LeaderSenateMissionFailed				, onLeaderSenateMissionFailed);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void __thiscall monitor_event::onFactionTurnStart(void* _this, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onFactionTurnStart(" + string(faction->factSmDescr->facName) + ")");
	o_FactionTurnStart(_this, faction);
}

void __thiscall monitor_event::onFactionWarDeclared(void* _this, factionStruct* faction, factionStruct* targetfac)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onFactionWarDeclared(fac: " + string(faction->factSmDescr->facName) + ", targetfac: " + string(targetfac->factSmDescr->facName) + ")");
	o_FactionWarDeclared(_this, faction, targetfac);
}

void __thiscall monitor_event::onHordeFormed(void* _this, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onHordeFormed(" + string(faction->factSmDescr->facName) + ")");
	o_HordeFormed(_this, faction);
}

void __thiscall monitor_event::onFactionTurnEnd(void* _this, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onFactionTurnEnd(" + string(faction->factSmDescr->facName) + ")");
	o_FactionTurnEnd(_this, faction);
}

void __thiscall monitor_event::onHireMercenaries(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onHireMercenaries(" + string(character->fullName) + ")");
	o_HireMercenaries(_this, character);
}

void __thiscall monitor_event::onGeneralCaptureResidence(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onGeneralCaptureResidence(" + string(character->fullName) + ")");
	o_GeneralCaptureResidence(_this, character);
}

void __thiscall monitor_event::onGeneralCaptureWonder(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onGeneralCaptureWonder(" + string(character->fullName) + ")");
	o_GeneralCaptureWonder(_this, character);
}

void __thiscall monitor_event::onGeneralCaptureSettlement(void* _this, namedCharacter* character, settlementStruct* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onGeneralCaptureSettlement(character: " + string(character->fullName) + ", settlement: " + string(settlement->name) + ")");
	o_GeneralCaptureSettlement(_this, character, settlement);
}

void __thiscall monitor_event::onLeaderDestroyedFaction(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onLeaderDestroyedFaction(" + string(character->fullName) + ")");
	o_LeaderDestroyedFaction(_this, character);
}

void __thiscall monitor_event::onDisaster(void* _this, int_32 disasterType)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onDisaster(" + to_string(disasterType) + ")");
	o_Disaster(_this, disasterType);
}

void __thiscall monitor_event::onCharacterDamagedByDisaster(void* _this, namedCharacter* character, int_32 disasterType)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onCharacterDamagedByDisaster(" + string(character->fullName) + ", disasterType: " + to_string(disasterType) + ")");
	o_CharacterDamagedByDisaster(_this, character, disasterType);
}

void __thiscall monitor_event::onGeneralAssaultsResidence(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onGeneralAssaultsResidence(" + string(character->fullName) + ")");
	o_GeneralAssaultsResidence(_this, character);
}

void __thiscall monitor_event::onOfferedForAdoption(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onOfferedForAdoption(" + string(character->fullName) + ")");
	o_OfferedForAdoption(_this, character);
}

void __thiscall monitor_event::onLesserGeneralOfferedForAdoption(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onLesserGeneralOfferedForAdoption(" + string(character->fullName) + ")");
	o_LesserGeneralOfferedForAdoption(_this, character);
}

void __thiscall monitor_event::onOfferedForMarriage(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onOfferedForMarriage(" + string(character->fullName) + ")");
	o_OfferedForMarriage(_this, character);
}

void __thiscall monitor_event::onBrotherAdopted(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBrotherAdopted(" + string(character->fullName) + ")");
	o_BrotherAdopted(_this, character);
}

void __thiscall monitor_event::onBecomesFactionLeader(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBecomesFactionLeader(" + string(character->fullName) + ")");
	o_BecomesFactionLeader(_this, character);
}

void __thiscall monitor_event::onBecomesFactionHeir(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBecomesFactionHeir(" + string(character->fullName) + ")");
	o_BecomesFactionHeir(_this, character);
}

void __thiscall monitor_event::onBecomeQuaestor(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBecomeQuaestor(" + string(character->fullName) + ")");
	o_BecomeQuaestor(_this, character);
}

void __thiscall monitor_event::onBecomeAedile(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBecomeAedile(" + string(character->fullName) + ")");
	o_BecomeAedile(_this, character);
}

void __thiscall monitor_event::onBecomePraetor(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBecomePraetor(" + string(character->fullName) + ")");
	o_BecomePraetor(_this, character);
}

void __thiscall monitor_event::onBecomeConsul(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBecomeConsul(" + string(character->fullName) + ")");
	o_BecomeConsul(_this, character);
}

void __thiscall monitor_event::onBecomeCensor(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBecomeCensor(" + string(character->fullName) + ")");
	o_BecomeCensor(_this, character);
}

void __thiscall monitor_event::onBecomePontifexMaximus(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBecomePontifexMaximus(" + string(character->fullName) + ")");
	o_BecomePontifexMaximus(_this, character);
}

void __thiscall monitor_event::onCeasedFactionLeader(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onCeasedFactionLeader(" + string(character->fullName) + ")");
	o_CeasedFactionLeader(_this, character);
}

void __thiscall monitor_event::onCeasedFactionHeir(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::oCeasedFactionHeir(" + string(character->fullName) + ")");
	o_CeasedFactionHeir(_this, character);
}

void __thiscall monitor_event::onCeasedQuaestor(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::oCeasedQuaestor(" + string(character->fullName) + ")");
	o_CeasedQuaestor(_this, character);
}

void __thiscall monitor_event::onCeasedAedile(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onCeasedAedile(" + string(character->fullName) + ")");
	o_CeasedAedile(_this, character);
}

void __thiscall monitor_event::onCeasedPraetor(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onCeasedPraetor(" + string(character->fullName) + ")");
	o_CeasedPraetor(_this, character);
}

void __thiscall monitor_event::onCeasedConsul(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onCeasedConsul(" + string(character->fullName) + ")");
	o_CeasedConsul(_this, character);
}

void __thiscall monitor_event::onCeasedCensor(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onCeasedCensor(" + string(character->fullName) + ")");
	o_CeasedCensor(_this, character);
}

void __thiscall monitor_event::onCeasedPontifexMaximus(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onCeasedPontifexMaximus(" + string(character->fullName) + ")");
	o_CeasedPontifexMaximus(_this, character);
}

void __thiscall monitor_event::onUngarrisonedFort(void* _this, fortStruct* fort)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onUngarrisonedFort(" + to_string(fort->xCoord) + ", " + to_string(fort->yCoord) + ")");
	o_UngarrisonedFort(_this, fort);
}

void __thiscall monitor_event::onLostLegionaryEagle(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onLostLegionaryEagle(" + string(character->fullName) + ")");
	o_LostLegionaryEagle(_this, character);
}

void __thiscall monitor_event::onCapturedLegionaryEagle(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onCapturedLegionaryEagle(" + string(character->fullName) + ")");
	o_CapturedLegionaryEagle(_this, character);
}

void __thiscall monitor_event::onSenateExposure(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onSenateExposure(" + string(character->fullName) + ")");
	o_SenateExposure(_this, character);
}

void __thiscall monitor_event::onQuaestorInvestigationMinor(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onQuaestorInvestigationMinor(" + string(character->fullName) + ")");
	o_QuaestorInvestigationMinor(_this, character);
}

void __thiscall monitor_event::onQuaestorInvestigation(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onQuaestorInvestigation(" + string(character->fullName) + ")");
	o_QuaestorInvestigation(_this, character);
}

void __thiscall monitor_event::onQuaestorInvestigationMajor(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onQuaestorInvestigationMajor(" + string(character->fullName) + ")");
	o_QuaestorInvestigationMajor(_this, character);
}

//void __thiscall monitor_event::onSenateReadyToOutlawFaction(void* _this, factionStruct* faction)
//{
//	LOG_ALWAYS(RELEASEFULL, "monitor_event::onSenateReadyToOutlawFaction(" + string(faction->factSmDescr->facName) + ")");
//	o_SenateReadyToOutlawFaction(_this, faction);
//}

void __thiscall monitor_event::onSenateOutlawsFaction(void* _this, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onSenateOutlawsFaction(" + string(faction->factSmDescr->facName) + ")");
	o_SenateOutlawsFaction(_this, faction);
}

void __thiscall monitor_event::onCharacterSelected(void* _this, namedCharacter* selectedChar, int_32 action, coords* coords, int_32 region_id)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onCharacterSelected(" + string(selectedChar->fullName) + ")");
	o_CharacterSelected(_this, selectedChar, action, coords, region_id);
}

static bool print_capabilities = true;
void __thiscall monitor_event::onSettlementSelected(void* _this, settlementStruct* settlement)
{
	if (LOG.m_current_level == BUGTEST)
	{
		int _gate_strength = settlement->capabilities.settlementCapabilities[gate_strength].value;
		int _gate_defences = settlement->capabilities.settlementCapabilities[gate_defences].value;
		int _wall_level    = settlement->capabilities.settlementCapabilities[wall_level].value;
		int _tower_level   = settlement->capabilities.settlementCapabilities[tower_level].value;
		LOG_ALWAYS(BUGTEST, "monitor_event::onSettlementSelected(" + string(settlement->name) +
			", gate_strength: " + to_string(_gate_strength) +
			", gate_defences: " + to_string(_gate_defences) +
			", wall_level: "    + to_string(_wall_level)    +
			", tower_level: "   + to_string(_tower_level)   +
		")");
	}
	else
	{
		LOG_ALWAYS(DEVELOPMENT, "monitor_event::onSettlementSelected(" + string(settlement->name) + ")");
	}
	o_SettlementSelected(_this, settlement);
}

void __thiscall monitor_event::onMultiTurnMove(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onMultiTurnMove(" + string(character->fullName) + ")");
	o_MultiTurnMove(_this, character);
}

void __thiscall monitor_event::onCharacterPanelOpen(void* _this, settlementStruct* settlement)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onCharacterPanelOpen(_this, settlement)");
	o_CharacterPanelOpen(_this, settlement);
}

void __thiscall monitor_event::onSettlementPanelOpen(void* _this, factionStruct* faction)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onSettlementPanelOpen(_this, factionStruct* faction)");
	o_SettlementPanelOpen(_this, faction);
}

void __thiscall monitor_event::onFinancesPanelOpen(void* _this, factionStruct* faction)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onFinancesPanelOpen(_this, factionStruct* faction)");
	o_FinancesPanelOpen(_this, faction);
}

void __thiscall monitor_event::onFactionSummaryPanelOpen(void* _this, factionStruct* faction)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onFactionSummaryPanelOpen(_this, factionStruct* faction)");
	o_FactionSummaryPanelOpen(_this, faction);
}

void __thiscall monitor_event::onFamilyTreePanelOpen(void* _this, factionStruct* faction)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onFamilyTreePanelOpen(_this, factionStruct* faction)");
	o_FamilyTreePanelOpen(_this, faction);
}

//void __thiscall monitor_event::onDiplomaticStandingPanelOpen(void* _this)
//{
//	LOG_ALWAYS(RELEASEFULL, "monitor_event::onDiplomaticStandingPanelOpen(_this)");
//	o_DiplomaticStandingPanelOpen(_this);
//}
//
//void __thiscall monitor_event::onSenateMissionsPanelOpen(void* _this, factionStruct* faction)
//{
//	LOG_ALWAYS(RELEASEFULL, "monitor_event::onSenateMissionsPanelOpen(_this, factionStruct* faction)");
//	o_SenateMissionsPanelOpen(_this, faction);
//}

void __thiscall monitor_event::onSenateOfficesPanelOpen(void* _this, int param_2)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onSenateOfficesPanelOpen(_this)");
	o_SenateOfficesPanelOpen(_this, param_2);
}

void __thiscall monitor_event::onDiplomacyPanelOpen(void* _this, factionStruct* faction)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onDiplomacyPanelOpen(_this, factionStruct* faction)");
	o_DiplomacyPanelOpen(_this, faction);
}

void __thiscall monitor_event::onPreBattlePanelOpen(void* _this, factionStruct* faction)
{
	LOG_ALWAYS(RELEASE, "monitor_event::onPreBattlePanelOpen(_this, factionStruct* faction)");
	o_PreBattlePanelOpen(_this, faction);
}

//void __thiscall monitor_event::onRecruitmentPanelOpen(void* _this, settlementStruct* settlement)
//{
//	LOG_ALWAYS(RELEASEFULL, "monitor_event::onRecruitmentPanelOpen(_this, settlement)");
//	o_RecruitmentPanelOpen(_this, settlement);
//}
//
//void __thiscall monitor_event::onConstructionPanelOpen(void* _this, settlementStruct* settlement)
//{
//	LOG_ALWAYS(RELEASEFULL, "monitor_event::onConstructionPanelOpen(_this, settlement)");
//	o_ConstructionPanelOpen(_this, settlement);
//}

void __thiscall monitor_event::onTradePanelOpen(void* _this, settlementStruct* settlement)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onTradePanelOpen(_this, settlement)");
	o_TradePanelOpen(_this, settlement);
}

//void __thiscall monitor_event::onHireMercenariesPanelOpen(void* _this)
//{
//	LOG_ALWAYS(RELEASEFULL, "monitor_event::onHireMercenariesPanelOpen(_this)");
//	o_HireMercenariesPanelOpen(_this);
//}
//
//void __thiscall monitor_event::onNavalAutoResolvePanelOpen(void* _this)
//{
//	LOG_ALWAYS(RELEASEFULL, "monitor_event::onNavalAutoResolvePanelOpen(_this)");
//	o_NavalAutoResolvePanelOpen(_this);
//}

void __thiscall monitor_event::onIncomingMessage(void* _this, int eventID)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onIncomingMessage(_this, eventID)");
	o_IncomingMessage(_this, eventID);
}

void __thiscall monitor_event::onMessageOpen(void* _this, int eventID)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onMessageOpen(_this, eventID)");
	o_MessageOpen(_this, eventID);
}

void __thiscall monitor_event::onRequestBuildingAdvice(void* _this, settlementStruct* settlement, char* resourceDescription)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onRequestBuildingAdvice(_this, settlement, resourceDescription)");
	o_RequestBuildingAdvice(_this, settlement, resourceDescription);
}

void __thiscall monitor_event::onRequestTrainingAdvice(void* _this, settlementStruct* settlement, char* resourceDescription)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onRequestTrainingAdvice(_this, settlement, resourceDescription)");
	o_RequestTrainingAdvice(_this, settlement, resourceDescription);
}

//void __thiscall monitor_event::onRequestMercenariesAdvice(void* _this, stackStruct* army)
//{
//	LOG_ALWAYS(RELEASEFULL, "monitor_event::onRequestMercenariesAdvice(_this, stackStruct* army)");
//	o_RequestMercenariesAdvice(_this, army);
//}

void __thiscall monitor_event::onButtonPressed(void* _this, char* resourceDescription)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onButtonPressed(" + string(resourceDescription) + ")");
	o_ButtonPressed(_this, resourceDescription);
}

void __thiscall monitor_event::onShortcutTriggered(void* _this, char* resourceDescription1, char* resourceDescription2)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onShortcutTriggered(" + string(resourceDescription1) + "::" + string(resourceDescription2) + ")");
	o_ShortcutTriggered(_this, resourceDescription1, resourceDescription2);
}

void __thiscall monitor_event::onScrollOpened(void* _this, char* resourceDescription)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onScrollOpened(" + string(resourceDescription) + ")");
	battle_result::onScrollOpened(resourceDescription);
	HOT_SEAT_CAMPAIGN.checkDiplomacyOverviewScroll(resourceDescription, true);
	o_ScrollOpened(_this, resourceDescription);
}

void __thiscall monitor_event::onScrollClosed(void* _this, char* resourceDescription)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onScrollClosed(" + string(resourceDescription) + ")");
	battle_result::onScrollClosed(resourceDescription);
	HOT_SEAT_CAMPAIGN.checkDiplomacyOverviewScroll(resourceDescription, false);
	o_ScrollClosed(_this, resourceDescription);
}

//void __thiscall monitor_event::onAdviceSupressed(void* _this, char* resourceDescription)
//{
//	LOG_ALWAYS(RELEASEFULL, "monitor_event::onAdviceSupressed(_this, resourceDescription)");
//	o_AdviceSupressed(_this, resourceDescription);
//}

void __thiscall monitor_event::onScrollAdviceRequested(void* _this, char* resourceDescription)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onScrollAdviceRequested(_this, resourceDescription)");
	o_ScrollAdviceRequested(_this, resourceDescription);
}

//void __thiscall monitor_event::onPreBattleScrollAdviceRequested(void* _this)
//{
//	LOG_ALWAYS(RELEASEFULL, "monitor_event::onPreBattleScrollAdviceRequested(_this)");
//	o_PreBattleScrollAdviceRequested(_this);
//}
//
//void __thiscall monitor_event::onNavalPreBattleScrollAdviceRequested(void* _this)
//{
//	LOG_ALWAYS(RELEASEFULL, "monitor_event::onNavalPreBattleScrollAdviceRequested(_this)");
//	o_NavalPreBattleScrollAdviceRequested(_this);
//}

void __thiscall monitor_event::onSettlementScrollAdviceRequested(void* _this, settlementStruct* settlement)
{
	LOG_ALWAYS(DEVELOPMENT, "monitor_event::onSettlementScrollAdviceRequested(_this, settlement, factionStruct* faction, int_32 region_id, resourceDescription)");
	o_SettlementScrollAdviceRequested(_this, settlement);
}

//void __thiscall monitor_event::onIdle(void* _this)
//{
//	LOG_ALWAYS(RELEASEFULL, "monitor_event::onIdle(_this)");
//	o_Idle(_this);
//}
//
//void __thiscall monitor_event::onAbandonShowMe(void* _this)
//{
//	LOG_ALWAYS(RELEASEFULL, "monitor_event::onAbandonShowMe(_this)");
//	o_AbandonShowMe(_this);
//}
//
//void __thiscall monitor_event::onScriptedAdvice(void* _this)
//{
//	LOG_ALWAYS(RELEASEFULL, "monitor_event::onScriptedAdvice(_this)");
//	o_ScriptedAdvice(_this);
//}
//
//void __thiscall monitor_event::onDeclineAutomatedSettlementManagement(void* _this, factionStruct* faction, settlementStruct* settlement)
//{
//	LOG_ALWAYS(RELEASEFULL, "monitor_event::onDeclineAutomatedSettlementManagement(_this, factionStruct* faction, settlement)");
//	o_DeclineAutomatedSettlementManagement(_this, faction, settlement);
//}
//
//void __thiscall monitor_event::onEscPressed(void* _this)
//{
//	LOG_ALWAYS(RELEASEFULL, "monitor_event::onEscPressed(_this)");
//	o_EscPressed(_this);
//}

void __thiscall monitor_event::onGameReloaded(void* _this)
{
	LOG_ALWAYS(RELEASE, "monitor_event::onGameReloaded(_this)");
	EOP_SETTLEMENTS.m_is_save_load = false;
	campaign* camp = helper_functions::getGameDataAll()->campaignData;
	o_GameReloaded(_this);
}

void __thiscall monitor_event::onSettlementTurnStart(void* _this, settlementStruct* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onSettlementTurnStart(" + string(settlement->name) + ")");
	o_SettlementTurnStart(_this, settlement);
}

void __thiscall monitor_event::onSettlementTurnEnd(void* _this, settlementStruct* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onSettlementTurnEnd(" + string(settlement->name) + ")");
	o_SettlementTurnEnd(_this, settlement);
}

void __thiscall monitor_event::onNewAdmiralCreated(void* _this, settlementStruct* settlement, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onNewAdmiralCreated(_this, settlement, character)");
	o_NewAdmiralCreated(_this, settlement, character);
}

void __thiscall monitor_event::onUnitTrained(void* _this, factionStruct* faction, settlementStruct* settlement, unit* trainedUnit)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onUnitTrained(faction: " + string(faction->factSmDescr->facName) + ", settlement: " + string(settlement->name) + ", unit: " + string(trainedUnit->eduEntry->Type) + ")");
	o_UnitTrained(_this, faction, settlement, trainedUnit);
}

void __thiscall monitor_event::onGovernorUnitTrained(void* _this, namedCharacter* character, settlementStruct* settlement, unit* trainedUnit)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onGovernorUnitTrained(character: " + string(character->fullName) + ", settlement: " + string(settlement->name) + ", unit: " + string(trainedUnit->eduEntry->Type) + ")");
	o_GovernorUnitTrained(_this, character, settlement, trainedUnit);
}

void __thiscall monitor_event::onBuildingCompleted(void* _this, settlementStruct* settlement, factionStruct* faction, eventBuild* evBuild)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBuildingCompleted(settlement: " + string(settlement->name) + ", faction: " + string(faction->factSmDescr->facName) + ", building: " + string(evBuild->edbEntry->type) + ", level: " + to_string(evBuild->newLevel) + ")");
	o_BuildingCompleted(_this, settlement, faction, evBuild);
}

void __thiscall monitor_event::onGovernorBuildingCompleted(void* _this, namedCharacter* character, settlementStruct* settlement, eventBuild* evBuild)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onGovernorBuildingCompleted(character: " + string(character->fullName) + ", settlement: " + string(settlement->name) + ", building: " + string(evBuild->edbEntry->type) + ", level: " + to_string(evBuild->newLevel) + ")");
	o_GovernorBuildingCompleted(_this, character, settlement, evBuild);
}

//void __thiscall monitor_event::onPlugInCompleted(void* _this, settlementStruct* settlement, eventBuild* evBuild)
//{
//	LOG_ALWAYS(RELEASEFULL, "monitor_event::onPlugInCompleted(_this, settlement, building)");
//	o_PlugInCompleted(_this, settlement, building);
//}
//
//void __thiscall monitor_event::onGovernorPlugInCompleted(void* _this, namedCharacter* character, eventBuild* evBuild)
//{
//	LOG_ALWAYS(RELEASEFULL, "monitor_event::onGovernorPlugInCompleted(_this, character, building)");
//	o_GovernorPlugInCompleted(_this, character, building);
//}

void __thiscall monitor_event::onAgentCreated(void* _this, namedCharacter* character, enum characterType type, settlementStruct* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onAgentCreated(_this, character, characterType, settlement)");
	o_AgentCreated(_this, character, type, settlement);
}

void __thiscall monitor_event::onGovernorAgentCreated(void* _this, namedCharacter* character, enum characterType type, settlementStruct* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onGovernorAgentCreated(_this, character, characterType, settlement)");
	o_GovernorAgentCreated(_this, character, type, settlement);
}

void __thiscall monitor_event::onBuildingDestroyed(void* _this, namedCharacter* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBuildingDestroyed(_this)");
	o_BuildingDestroyed(_this, settlement);
}

void __thiscall monitor_event::onGovernorBuildingDestroyed(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onGovernorBuildingDestroyed(_this, character)");
	o_GovernorBuildingDestroyed(_this, character);
}

void __thiscall monitor_event::onCityRiots(void* _this, settlementStruct* settlement, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onCityRiots(_this, settlement, faction)");
	o_CityRiots(_this, settlement, faction);
}

void __thiscall monitor_event::onGovernorCityRiots(void* _this, namedCharacter* character, settlementStruct* settlement, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onGovernorCityRiots(_this, character, settlement, faction)");
	o_GovernorCityRiots(_this, character, settlement, faction);
}

void __thiscall monitor_event::onCityRebels(void* _this, settlementStruct* settlement, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onCityRebels(_this, settlement, faction)");
	o_CityRebels(_this, settlement, faction);
}

void __thiscall monitor_event::onGovernorCityRebels(void* _this, namedCharacter* character, settlementStruct* settlement, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onGovernorCityRebels(_this, character, settlement, faction)");
	o_GovernorCityRebels(_this, character, settlement, faction);
}

void __thiscall monitor_event::onGovernorThrowGames(void* _this, namedCharacter* character, settlementStruct* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onGovernorThrowGames(_this, character, settlement)");
	o_GovernorThrowGames(_this, character, settlement);
}

void __thiscall monitor_event::onGovernorThrowRaces(void* _this, namedCharacter* character, settlementStruct* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onGovernorThrowRaces(_this, character, settlement)");
	o_GovernorThrowRaces(_this, character, settlement);
}

void __thiscall monitor_event::onUngarrisonedSettlement(void* _this, settlementStruct* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onUngarrisonedSettlement(_this, settlement)");
	o_UngarrisonedSettlement(_this, settlement);
}

void __thiscall monitor_event::onEnslavePopulation(void* _this, namedCharacter* character, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onEnslavePopulation(_this, character, faction)");
	o_EnslavePopulation(_this, character, faction);
}

void __thiscall monitor_event::onExterminatePopulation(void* _this, namedCharacter* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onExterminatePopulation(_this, character)");
	o_ExterminatePopulation(_this, character);
}

void __thiscall monitor_event::onCitySacked(void* _this, settlementStruct* settlement, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onCitySacked(_this, settlement, faction)");
	o_CitySacked(_this, settlement, faction);
}


void __thiscall monitor_event::onPreBattle(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onPreBattle()");
	o_PreBattle(_this, nc);
}

void __thiscall monitor_event::onPreBattleWithdrawal(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onPreBattleWithdrawal()");
	o_PreBattleWithdrawal(_this, nc);
}

void __thiscall monitor_event::onBattleAiCommenced(void* _this, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleAiCommenced()");
	o_BattleAiCommenced(_this, faction);
}

void __thiscall monitor_event::onBattleDelayPhaseCommenced(void* _this, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleDelayPhaseCommenced()");
	o_BattleDelayPhaseCommenced(_this, faction);
}

void __thiscall monitor_event::onBattleDeploymentPhaseCommenced(void* _this, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleDeploymentPhaseCommenced()");
	o_BattleDeploymentPhaseCommenced(_this, faction);
}

void __thiscall monitor_event::onBattleConflictPhaseCommenced(void* _this, factionStruct* faction)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleConflictPhaseCommenced()");
	o_BattleConflictPhaseCommenced(_this, faction);
}

void __thiscall monitor_event::onBattlePlayerUnitAttacksEnemyUnit(void* _this, unit* attacker, unit* defender)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattlePlayerUnitAttacksEnemyUnit()");
	o_BattlePlayerUnitAttacksEnemyUnit(_this, attacker, defender);
}

void __thiscall monitor_event::onBattleEnemyUnitAttacksPlayerUnit(void* _this, unit* attacker, unit* defender)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleEnemyUnitAttacksPlayerUnit()");
	o_BattleEnemyUnitAttacksPlayerUnit(_this, attacker, defender);
}

void __thiscall monitor_event::onBattlePlayerAttacksSettlementBuilding(void* _this, unit* unit, buildingBattle* building)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattlePlayerAttacksSettlementBuilding()");
	o_BattlePlayerAttacksSettlementBuilding(_this, unit, building);
}

void __thiscall monitor_event::onBattleEnemyAttacksSettlementBuilding(void* _this, unit* unit, buildingBattle* building)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleEnemyAttacksSettlementBuilding()");
	o_BattleEnemyAttacksSettlementBuilding(_this, unit, building);
}

void __thiscall monitor_event::onBattleUnitGoesBerserk(void* _this, unit* unit)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleUnitGoesBerserk()");
	o_BattleUnitGoesBerserk(_this, unit);
}

void __thiscall monitor_event::onBattlePlayerUnitGoesBerserk(void* _this, unit* unit)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattlePlayerUnitGoesBerserk()");
	o_BattlePlayerUnitGoesBerserk(_this, unit);
}

void __thiscall monitor_event::onBattleEnemyUnitGoesBerserk(void* _this, unit* unit)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleEnemyUnitGoesBerserk()");
	o_BattleEnemyUnitGoesBerserk(_this, unit);
}

void __thiscall monitor_event::onBattleUnitRouts(void* _this, unit* unit)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleUnitRouts()");
	o_BattleUnitRouts(_this, unit);
}

void __thiscall monitor_event::onBattlePlayerUnitRouts(void* _this, unit* unit)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattlePlayerUnitRouts()");
	o_BattlePlayerUnitRouts(_this, unit);
}

void __thiscall monitor_event::onBattleEnemyUnitRouts(void* _this, unit* unit)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleEnemyUnitRouts()");
	o_BattleEnemyUnitRouts(_this, unit);
}

void __thiscall monitor_event::onBattlePlayerSiegeEngineDestroyed(void* _this, siegeEngine* engine)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattlePlayerSiegeEngineDestroyed()");
	o_BattlePlayerSiegeEngineDestroyed(_this, engine);
}

void __thiscall monitor_event::onBattleEnemySiegeEngineDestroyed(void* _this, siegeEngine* engine)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleEnemySiegeEngineDestroyed()");
	o_BattleEnemySiegeEngineDestroyed(_this, engine);
}

void __thiscall monitor_event::onPostBattle(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onPostBattle()");
	o_PostBattle(_this, nc);
}

void __thiscall monitor_event::onBattleArmyRouted(void* _this, stackStruct* army)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleArmyRouted()");
	o_BattleArmyRouted(_this, army);
}

void __thiscall monitor_event::onBattleGeneralKilled(void* _this, character* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleGeneralKilled()");
	o_BattleGeneralKilled(_this, character);
}

void __thiscall monitor_event::onBattleGeneralRouted(void* _this, character* character)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleGeneralRouted()");
	o_BattleGeneralRouted(_this, character);
}

void __thiscall monitor_event::onBattleReinforcementsArrive(void* _this, stackStruct* army)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleReinforcementsArrive()");
	o_BattleReinforcementsArrive(_this, army);
}

void __thiscall monitor_event::onBattleSiegeEngineDestroyed(void* _this, siegeEngine* engine)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleSiegeEngineDestroyed()");
	o_BattleSiegeEngineDestroyed(_this, engine);
}

void __thiscall monitor_event::onBattleSiegeEngineDocksWall(void* _this, unit* unit)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleSiegeEngineDocksWall()");
	o_BattleSiegeEngineDocksWall(_this, unit);
}

void __thiscall monitor_event::onBattleGatesAttackedByEngine(void* _this, siegeEngine* engine, buildingBattle* building)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleGatesAttackedByEngine()");
	o_BattleGatesAttackedByEngine(_this, engine, building);
}

void __thiscall monitor_event::onBattleGatesAttackedByPlayerEngine(void* _this, siegeEngine* engine, buildingBattle* building)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleGatesAttackedByPlayerEngine()");
	o_BattleGatesAttackedByPlayerEngine(_this, engine, building);
}

void __thiscall monitor_event::onBattleGatesAttackedByEnemyEngine(void* _this, siegeEngine* engine, buildingBattle* building)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleGatesAttackedByEnemyEngine()");
	o_BattleGatesAttackedByEnemyEngine(_this, engine, building);
}

void __thiscall monitor_event::onBattleBattleGatesDestroyedByEngine(void* _this, siegeEngine* engine, buildingBattle* gates)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleBattleGatesDestroyedByEngine()");
	o_BattleBattleGatesDestroyedByEngine(_this, engine, gates);
}

void __thiscall monitor_event::onBattleWallsBreachedByEngine(void* _this, siegeEngine* engine, buildingBattle* wall)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleWallsBreachedByEngine()");
	o_BattleWallsBreachedByEngine(_this, engine, wall);
}

void __thiscall monitor_event::onBattleWallsCaptured(void* _this, buildingBattle* building, unit* unit)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleWallsCaptured()");
	o_BattleWallsCaptured(_this, building, unit);
}

void __thiscall monitor_event::onBattleFinished(void* _this, battleSide* side, int reason, int result, int rating)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBattleFinished()");
	o_BattleFinished(_this, side, reason, result, rating);
}

void __thiscall monitor_event::onBirth(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBirth()");
	o_Birth(_this, nc);
}

void __thiscall monitor_event::onCharacterComesOfAge(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onCharacterComesOfAge()");
	o_CharacterComesOfAge(_this, nc);
}

void __thiscall monitor_event::onCharacterMarries(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onCharacterMarries()");
	o_CharacterMarries(_this, nc);
}

void __thiscall monitor_event::onCharacterBecomesAFather(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onCharacterBecomesAFather()");
	o_CharacterBecomesAFather(_this, nc);
}

void __thiscall monitor_event::onCharacterTurnStart(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onCharacterTurnStart()");
	o_CharacterTurnStart(_this, nc);
}

void __thiscall monitor_event::onCharacterTurnEnd(void* _this, namedCharacter* nc, settlementStruct* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onCharacterTurnEnd()");
	o_CharacterTurnEnd(_this, nc, settlement);
}

void __thiscall monitor_event::onCharacterTurnEndInSettlement(void* _this, namedCharacter* nc, settlementStruct* settlement)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onCharacterTurnEndInSettlement()");
	o_CharacterTurnEndInSettlement(_this, nc, settlement);
}

void __thiscall monitor_event::onGeneralDevastatesTile(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onGeneralDevastatesTile()");
	o_GeneralDevastatesTile(_this, nc);
}

void __thiscall monitor_event::onSpyMission(void* _this, namedCharacter* nc, factionStruct* faction, missionEnum m)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onSpyMission()");
	o_SpyMission(_this, nc, faction, m);
}

void __thiscall monitor_event::onExecutesASpyOnAMission(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onExecutesASpyOnAMission()");
	o_ExecutesASpyOnAMission(_this, nc);
}

void __thiscall monitor_event::onLeaderOrderedSpyingMission(void* _this, namedCharacter* nc, factionStruct* faction, missionEnum m)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onLeaderOrderedSpyingMission()");
	o_LeaderOrderedSpyingMission(_this, nc, faction, m);
}

void __thiscall monitor_event::onAssassinationMission(void* _this, namedCharacter* nc, missionEnum m)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onAssassinationMission()");
	o_AssassinationMission(_this, nc, m);
}

void __thiscall monitor_event::onExecutesAnAssassinOnAMission(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onExecutesAnAssassinOnAMission()");
	o_ExecutesAnAssassinOnAMission(_this, nc);
}

void __thiscall monitor_event::onLeaderOrderedAssassination(void* _this, namedCharacter* leader, namedCharacter* target, missionEnum m)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onLeaderOrderedAssassination()");
	o_LeaderOrderedAssassination(_this, leader, target, m);
}

void __thiscall monitor_event::onSufferAssassinationAttempt(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onSufferAssassinationAttempt()");
	o_SufferAssassinationAttempt(_this, nc);
}

void __thiscall monitor_event::onSabotageMission(void* _this, namedCharacter* nc, missionEnum m)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onSabotageMission()");
	o_SabotageMission(_this, nc, m);
}

void __thiscall monitor_event::onLeaderOrderedSabotage(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onLeaderOrderedSabotage()");
	o_LeaderOrderedSabotage(_this, nc);
}

void __thiscall monitor_event::onBriberyMission(void* _this, namedCharacter* nc, factionStruct* target, missionEnum m)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onBriberyMission()");
	o_BriberyMission(_this, nc, target, m);
}

void __thiscall monitor_event::onLeaderOrderedBribery(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onLeaderOrderedBribery()");
	o_LeaderOrderedBribery(_this, nc);
}

void __thiscall monitor_event::onAcceptBribe(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onAcceptBribe()");
	o_AcceptBribe(_this, nc);
}

void __thiscall monitor_event::onRefuseBribe(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onRefuseBribe()");
	o_RefuseBribe(_this, nc);
}

void __thiscall monitor_event::onInsurrection(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onInsurrection()");
	o_Insurrection(_this, nc);
}

void __thiscall monitor_event::onDiplomacyMission(void* _this, namedCharacter* nc, factionStruct* faction, missionEnum m)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onDiplomacyMission()");
	o_DiplomacyMission(_this, nc, faction, m);
}

void __thiscall monitor_event::onLeaderOrderedDiplomacy(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onLeaderOrderedDiplomacy()");
	o_LeaderOrderedDiplomacy(_this, nc);
}

void __thiscall monitor_event::onLeaderSenateMissionSuccess(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onLeaderSenateMissionSuccess()");
	o_LeaderSenateMissionSuccess(_this, nc);
}

void __thiscall monitor_event::onLeaderSenateMissionFailed(void* _this, namedCharacter* nc)
{
	LOG_ALWAYS(RELEASEFULL, "monitor_event::onLeaderSenateMissionFailed()");
	o_LeaderSenateMissionFailed(_this, nc);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////





















