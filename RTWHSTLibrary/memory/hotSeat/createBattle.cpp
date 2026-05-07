///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <fstream>
#include <filesystem>  
#include <imgui.h>
#include <imgui_notify.h>
#include "../differentFunctions/screenshoter.h"
#include "../differentFunctions/dm_assert.h"
#include "../differentFunctions/stringThings.h"
#include "createBattleResult.h"
#include "../helper_functions.h"
#include "createBattle.h"
#include "../events/new_event.h"

using namespace std;
typedef unsigned char undefined;
typedef unsigned char uchar;

uint32_t cameraAddress;
uint32_t battleAddress;
uint32_t gDataAllAddress;

quickAccess qa;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// Create Battle ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
static string getTraits(namedCharacter* namChar)
{
    string traits = "";
    if (namChar->traits != nullptr)
    {
        traits = "\ntraits ";
        traitContainer* traitCont = namChar->traits;
        while (traitCont != nullptr)
        {
            traits = traits + " " + traitCont->trait->traitEntry->name + " " + to_string(traitCont->trait->level->level) + " ,";
            traitCont = traitCont->next;
        }
    }
    return traits;
}
static string getAncillaries(namedCharacter* namChar)
{
    string ancillaries = "";
    if (namChar->ancNum != 0)
    {
        ancillaries = "\nancillaries ";
        UINT32 ancNum = namChar->ancNum;
        for (UINT32 i = 0; i < ancNum; i++)
        {
            ancillaries = ancillaries + " " + namChar->ancillaries[i]->dataAnc->ancName + " ,";
        }
    }
    return ancillaries;
}

static string getFortificationLevel(int wallLevel)
{
    if (wallLevel < 0)
    {
        return "none";
    }
    return to_string(wallLevel);
}

static string findBattleSettlement(factionStruct* fac)
{
    string settStr = "";
    settlementStruct* settlement = helper_functions::getSettlementByCoords(qa.battle->xCoord, qa.battle->yCoord);

    if (!settlement || settlement->faction != fac)
        return settStr;

    int _gate_strength = settlement->capabilities.settlementCapabilities[gate_strength].value;
    int _gate_defences = settlement->capabilities.settlementCapabilities[gate_defences].value;
    int _wall_level    = settlement->capabilities.settlementCapabilities[wall_level].value;
    int _tower_level   = settlement->capabilities.settlementCapabilities[tower_level].value;

    settStr = settStr + 
        "settlement\n"
        "{\n"
        "	level " + ds.settlementLevel[settlement->level] + "\n"
        "	tile " + to_string(settlement->xCoord) + " " + to_string(settlement->yCoord) + "\n"
        "	year_founded " + to_string(qa.campaignStruct->currentDate) + "\n"
        "	fortification " + getFortificationLevel(_wall_level) + " greek, walls " + to_string(_wall_level) + " towers " + to_string(_tower_level) + " gates " + to_string(_gate_strength) + " gate_defences " + to_string(_gate_defences) + "\n"
        "	population " + to_string(settlement->populationSiegeStart) + "\n"
        ";	battle_pos 32.000 91.973 - 32.000	rotation_0	0\n"
        "	plan_set default_set\n"
        "	faction_creator " + qa.gDataAll->campaignData->getFactionById(settlement->faction_creator)->factSmDescr->facName + "\n";

    for (int b = 0; b < settlement->buildingsNum; b++)
    {
        building* build = settlement->buildings[b];
        string buildType = build->edbEntry->type;
        int8_t k = build->level;
        buildingLevel level = build->edbEntry->buildingLevel[k];
        string buildName = level.name;
        settStr = settStr + 
        "	building\n"
        "	{\n"
        "		type " + buildType + " " + buildName + "\n"
        "		creator " + qa.gDataAll->campaignData->getFactionById(build->factionID)->factSmDescr->facName + "\n"
        "	}\n";
    }
    settStr = settStr + "}\n";

    return settStr;
}

static int captureSettlementSideID = -1;
static string getBattleAlliance(bool isDefender)
{
    string alliance = "";
    for (int s = 0; s < qa.battle->sidesNum; s++)
    {
    	battleSide& side = qa.battle->sides[s];
        //  is attacker                        or  is Defender   
        if ( (!isDefender && !side.isDefender) || (isDefender && side.isDefender) )
        {
            for (int f = 0; f < side.factionCount; f++)
            {
                alliance = alliance + side.factions[f]->factSmDescr->facName + ", ";
            }

            if (qa.battle->battleType == SIEGE && !side.isDefender || qa.battle->battleType == SALLY && side.isDefender)
            {
                captureSettlementSideID = s;  // временное решение   
            }

        }
    }
    return alliance;
}

static string getSubFaction(factionStruct* fac, namedCharacter* namChar)
{
    if (strcmp(fac->factSmDescr->facName, "slave") != 0)
        return "";

    return "sub_faction " + string(qa.gDataAll->campaignData->getFactionById(namChar->subFaction)->factSmDescr->facName) + ", ";
}

static string writeFactionsSection(factionStruct* fac, battleSide& side, int sideID)
{
    string factionsSection = findBattleSettlement(fac);
    for (int a = 0; a < side.armiesNum; a++)
    {
        stackStruct* army = side.armies[a].stack;

        if (fac != army->faction)
            continue;

        namedCharacter* namChar = army->gen->genChar;
        string charType = ", general";
        char* charName = namChar->shortName;
        if (army->gen->genType->type == NAMED_CHARACTER)
        {
            charType = ", named character";
            charName = namChar->fullName;
        }
        factionsSection = factionsSection + "\ncharacter	" + getSubFaction(fac, namChar) + charName + charType + ", command 0, influence 0, management 0, subterfuge 0, age " + to_string(namChar->age) + ", , x " + to_string(army->gen->xCoord) + ", y " + to_string(army->gen->yCoord) +
                                            getTraits(namChar) +
                                            getAncillaries(namChar);

        factionsSection = factionsSection + "\narmy\n";
        for (int u = 0; u < army->numOfUnits; u++)
        {
            unit* un = army->units[u];
            factionsSection = factionsSection +
                "unit		" + string(un->eduEntry->Type) +
                "				soldiers " + to_string(un->SoldierCountStrat) +
                " exp " + to_string(un->expScreen) +
                " armour " + to_string(un->avgArmourUpg) +
                " weapon_lvl " + to_string(un->avgWeaponUpg) + "\n";
        }

        if(qa.battle->battleType == SIEGE || qa.battle->battleType == SALLY)
        {
            if (army->sapPoints > 0)
            {
                factionsSection = factionsSection + "sieging\n\n";
            }
            else
            {
                factionsSection = factionsSection + ";sieging\n\n";
            }

            if (army->rams > 0)      factionsSection = factionsSection + "siege_equipment 	ram "       + to_string(army->rams)      + "\n";
            if (army->ladders > 0)   factionsSection = factionsSection + "siege_equipment 	ladder "    + to_string(army->ladders)   + "\n";
            if (army->towers > 0)    factionsSection = factionsSection + "siege_equipment 	tower "     + to_string(army->towers)    + "\n";
            if (army->sapPoints > 0) factionsSection = factionsSection + "siege_equipment 	sap_point " + to_string(army->sapPoints) + "\n";
        }
    }
    return factionsSection;
}

static bool checkBattleArea()
{
    for (int s = 0; s < qa.battle->sidesNum; s++)
    {
        battleSide& side = qa.battle->sides[s];
        for (int a = 0; a < side.armiesNum; a++)
        {
            stackStruct* army = side.armies[a].stack;
            for (int u = 0; u < army->numOfUnits; u++)
            {
                unit* un = army->units[u];
                if (un->soldiersBattleArr == nullptr)
                {
                    LOG_ALWAYS(RELEASE, "checkBattleArea(false)");
                    return false;
                }
                if (un->soldiersBattleArr[0]->xCoord == 0 && un->soldiersBattleArr[0]->yCoord == 0)
                {
                    LOG_ALWAYS(RELEASE, "checkBattleArea(false)");
                    return false;
                }
            }
        }
    }
    LOG_ALWAYS(RELEASE, "checkBattleArea(true)");
    return true;
}

static string writeBattleSection(factionStruct* fac, battleSide& side)
{
    int facArmy = 0;
    string battleSection = "\n";
    for (int a = 0; a < side.armiesNum; a++)
    {
        stackStruct* army = side.armies[a].stack;
        if (fac == army->faction)
        {
            battleSection = battleSection + "\narmy	" + fac->factSmDescr->facName + ", " + to_string(facArmy) + ", supporting_armies 0\n\n";
            facArmy++;

            int coordsPairsNum = side.armies[a].deploymentArea->coordsNum;
            float* coords = side.armies[a].deploymentArea->coordsPairs;
            for (int k = 0; k < coordsPairsNum; k++)
            {
                battleSection = battleSection + "deployment_area_point	" + to_string(coords[k * 2]) + ", " + to_string(coords[k * 2 + 1]) + "\n";
            }

            for (int u = 0; u < army->numOfUnits; u++)
            {
                unit* un = army->units[u];
                while (1)
                {
                    if (un->soldiersBattleArr == nullptr)
                    {
                        continue;
                    }

                    bool test = un->soldiersBattleArr[0]->xCoord == 0;
                    if (un->soldiersBattleArr[0]->xCoord == 0 && un->soldiersBattleArr[0]->yCoord == 0)
                    {
                        continue;
                    }

                    battleSection = battleSection + 
                        "unit			" + to_string(u) +
                        ", " + to_string(un->soldiersBattleArr[0]->xCoord) + 
                        ", " + to_string(un->soldiersBattleArr[0]->yCoord) + 
                        ", 0, formation_type " + eduFormation.type[un->eduEntry->Index] + ", formation_width 50";

                    string attach_engine = "";
                    if (un->eduEntry->Category == INFANTRY)
                    {
                        battleStatus status = un->checkUnitBattleStatus();
                        if (status.hasRam)
                        {
                            attach_engine = attach_engine + ", attach_engine ram";
                        }
                        else if (status.hasLadders)
                        {
                            attach_engine = attach_engine + ", attach_engine ladder";
                        }
                        else if (status.hasSiegeTower)
                        {
                            attach_engine = attach_engine + ", attach_engine tower";
                        }
                    }
 
                    battleSection = battleSection + attach_engine + "\n";
                    break;
                }
            }
        }
    }

    return battleSection;
}

static string check_capture_major_settlement(int sideID)
{
    if (captureSettlementSideID == sideID)
    {
        return "condition capture_major_settlement";
    }
    return "";
}

int _createBattleState = 0;
int _createBattleResultState = 0;
string battleText = "";
string battleName = "";
string path = "";
static void createBattleFile(int state)
{
    auto battle = qa.battle;

    if (state == 1)
    {
        LOG_ALWAYS(RELEASE, "---createBattleFile(start)---");
        
        battleName = string(battle->sides[0].armies[0].stack->faction->factSmDescr->facName) + "_" + string(battle->sides[1].armies[0].stack->faction->factSmDescr->facName) + "_" + to_string(qa.campaignStruct->turnNumber) + "_" + to_string(battle->xCoord) + to_string(battle->yCoord);
        filesystem::create_directory("dmData/createdBattles/");
        path = "dmData/createdBattles/" + battleName;        //  path = "E:/Games_Hot_seats/Rome.Total War.Gold Edition/alexander/createdBattles/" + battleName;
        filesystem::create_directory(path);

        const char* mod = helper_functions::getModPatchName();
        string save = string(mod) + "/saves/" + battleName + ".sav";
        new_events::callSaveCreate(save.c_str());

        CopyFileA(save.c_str(), string(path + "/" + battleName + ".sav").c_str(), FALSE);
    //  std::filesystem::copy(save, path + "/" + battleName + ".sav");


        battleText = ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"
            ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Custom battle script generated by RTW Hot Seat Tool. ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"
            ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"
            ";;;coords(" + to_string(battle->xCoord) + ", " + to_string(battle->yCoord) + ")\n"
            "\n\n\nbattle		" + battleName + "		multiplayer\n" + "playable\n";

        for (int i = 0; i < battle->sidesNum; i++)
        {
            battleSide& side = battle->sides[i];

            string notDouble = "";
            for (int j = 0; j < side.armiesNum; j++)
            {
                string facName = side.armies[j].stack->faction->factSmDescr->facName;
                if (notDouble.find("_" + facName + "_") == string::npos)
                {
                    battleText = battleText + "	" + facName + "\n";
                }
                notDouble = notDouble + "_" + facName + "_";
            }
        }

        string date = to_string(qa.campaignStruct->currentDate) + " " + string(ds.season[qa.campaignStruct->season]);
        battleText = battleText + "end\nnonplayable\nend\n\n\n"
            + "start_date	" + date
            + "\nend_date	" + date + "\n\n\n;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n; >>>> start of factions section <<<<\n";



        for (int i = 0; i < battle->sidesNum; i++)
        {
            battleSide& side = battle->sides[i];
            string notDouble = "";
            for (int j = 0; j < side.armiesNum; j++)
            {
                string facName = side.armies[j].stack->faction->factSmDescr->facName;
                if (notDouble.find("_" + facName + "_") == string::npos)
                {
                    battleText = battleText + "\n\nfaction	" + facName + "\n";
                    battleText = battleText + writeFactionsSection(side.armies[j].stack->faction, side, i);
                }
                notDouble = notDouble + "_" + facName + "_";

            }
        }
        string bName1 = desTab.battle1 + path;
        const char* c = bName1.c_str();
        ImGui::InsertNotification({ ImGuiToastType_Success, 9000, c });
    }



    if (state < 2) return;
    LOG_ALWAYS(RELEASE, "---createBattleFile(battle)---");



    battleText = battleText + "\n\n\n;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"
        "; >>>> start of battle section <<<<\n"
        "battle	" + to_string(battle->xCoord) + ", " + to_string(battle->yCoord) + "\n\n"

        ";constant_weather_and_time ( day_time 9.00, year_day 90, mediterranean_summer,	hazy )			;;; the weather and time do not change / погода и время не меняются\n"
        "variable_weather_and_time ( day_time 12.00, year_day 0, duration	00.00, weather_seed	0 )		;;; the weather and time are changing / погода и время меняются\n"
        "playable_area_dimensions 1850 1850																;;; maximum: 2000 2000\n\n"

        "home_faction	" + battle->sides[0].armies[0].stack->faction->factSmDescr->facName + "\n";

    string attacking = getBattleAlliance(false);
    string defending = getBattleAlliance(true);


    battleText = battleText + "alliance	can_deploy	can_view    can_delay	" + attacking + "attacking\n"
        "alliance	can_deploy	can_view 	can_delay	" + defending + "defending\n\n";



    for (int i = 0; i < battle->sidesNum; i++)
    {
        battleSide& side = battle->sides[i];

        string notDouble = "";
        for (int a = 0; a < side.armiesNum; a++)
        {
            string facName = side.armies[a].stack->faction->factSmDescr->facName;
            if (notDouble.find("_" + facName + "_") == string::npos)
            {
                battleText = battleText + writeBattleSection(side.armies[a].stack->faction, side);
            }
            notDouble = notDouble + "_" + facName + "_";
        }
    }

    battleText = battleText + "\n\n\n;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"
        "; >>>> start of objectives scripting section <<<<\n\n"
        "objectives\n\n";

    for (int i = 0; i < battle->sidesNum; i++)
    {
        battleSide& side = battle->sides[i];

        battleText = battleText + 
            "alliance " + to_string(i) + "\n"
            "condition destroy_or_rout_enemy\n"
         // "condition capture_major_settlement\n"
            + check_capture_major_settlement(i) +
            "\n\n";
    }

    battleText = battleText + "\n\n\n;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"
                              ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; End. ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"
                              ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";

    string file = path + "/descr_battle.txt";
    ofstream out;
    out.open(file, ios::out);
    if (out.is_open())
    {
        out << battleText << endl;
    }
    out.close();

    createBattleResult(battle, false, path); // "characters.json"   

    LOG_ALWAYS(RELEASE, "---createBattleFile(end)---");
    ImGui::InsertNotification({ ImGuiToastType_Success, 9000, (desTab.battle2 + path).c_str() });
}


bool goGetWindowRect = false;
bool _test = false;
void battle_create::createBattle()
{
    if (qa.battle == NULL) 
        return;



    if (
        (goCreateBattle || goTransferBattleResult != 0 || goGetWindowRect || _createBattleResultState != 0) 
        && qa.battle->battleState == NOTHING
       )
    {
        LOG_ALWAYS(RELEASE, "---createBattle(0)---");
        _createBattleState = 0;
        _createBattleResultState = 0;
        battleText = "";
        battleName = "";
        path = "";
        goTransferBattleResult = 0;
        goCreateBattle = false;
        goGetWindowRect = false;
        gameWindow.mapView = false;
    }


    if (goCreateBattle)
    {
        if (_createBattleState != 1 && qa.battle->battleState == PRE_BATTLE && qa.battle->battleType != NAVAL)
        {
        //  Sleep(100);
            _createBattleState = 1;
            LOG_ALWAYS(RELEASE, "---createBattle(1)---");
            createBattleFile(1);
        }
        else if (_createBattleState != 2 && qa.battle->battleState == CONFLICT && checkBattleArea())
        {
            Sleep(100);
            _createBattleState = 2;
            LOG_ALWAYS(RELEASE, "---createBattle(2)---");
            createBattleFile(2);
            goCreateBattle = false;
        }
    }


    if (goTransferBattleResult == 0 && qa.battle->battleState == PRE_BATTLE && qa.battle->battleType != NAVAL && qa.stratPosition && qa.stratPosition->x >= 0 && qa.stratPosition->y >= 0)
    {
        LOG_ALWAYS(RELEASE, "---createBattle(3)---");
        goTransferBattleResult = 1;
    }


    if (!goGetWindowRect && qa.battle->battleState > PRE_BATTLE)
    {
        LOG_ALWAYS(RELEASE, "---createBattle(5)---");
        goGetWindowRect = true;
        getWindowRect();
    }


    transferBattleResult(qa.battle);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace battle_create
{
    void onBattleStateChange(battleDataS* battle)
    {

    }

    void onBattleEnd(battleDataS* battle)
    {
        if (_createBattleResultState == 0 /*&& battle->battleState == FINISHED_2*/)
        {
            LOG_ALWAYS(RELEASE, "---createBattle(4)---");
            _createBattleResultState = 1;
            createBattleResult(battle, true, "");
        }
    }

    void onCampaignMapLoaded(campaign* camp)
    {
        qa.selectGeneral = NULL;


        if (startSettings.gameVersion == 2)// если это Steam версия - временно   
        {
            qa.battle = reinterpret_cast<battleDataS*>(memory::Read(gameWindow.RomeTW_ALX_exe + 0x014E3E20));
        //  helper_functions::getGameDataAll();
            qa.gDataAll = new gameDataAllStruct;
            qa.gDataAll->battleHandler = qa.battle;
            qa.gDataAll->campaignData = camp;
        }
        else
        {
            qa.battle = helper_functions::getGameDataAll()->battleHandler;
        }


        qa.campaignStruct = camp;
        qa.modPatch = helper_functions::getModPatchName();
    //  qa.modPatch = "alexander";

        uint32_t stratPositionAddress = memory::Read(gameWindow.RomeTW_ALX_exe + offsets.stratPosition);
        qa.stratPosition = reinterpret_cast<stratCursorPosition*>(stratPositionAddress);

    //  uint32_t currentFactionAddress = memory::Read(gameWindow.RomeTW_ALX_exe + 0x00C444B8);
    //  qa.currentFaction = reinterpret_cast<factionStruct*>(currentFactionAddress);
        qa.currentFaction = camp->currentFactionTurn;

        if (offsets.toggle_fow)
        {
            qa.toggle_fow      = *reinterpret_cast<int*>(offsets.toggle_fow);
            qa.toggle_fow_pref = *reinterpret_cast<int*>(offsets.toggle_fow_pref);
        }

        LOG_ALWAYS(RELEASE, "modPatch: " + string(qa.modPatch) +
            ", battle: "                 + boolStr(qa.battle) +
            ", campaignStruct: "         + boolStr(qa.campaignStruct) +
            ", stratPosition: "          + boolStr(qa.stratPosition) +
            ", currentFaction: "         + boolStr(qa.currentFaction) +
            ", toggle_fow: "             + boolStr(qa.toggle_fow) +
            ", toggle_fow_pref: "        + boolStr(qa.toggle_fow_pref)
        );
    //  stratPosition->x = -1;
    //  stratPosition->y = -1;
    //  new_events::onCampaignMapLoaded(campaignStruct);
    //  getWindowRect();
    }
}

void onCampaignMapUnloaded()
{
    if (!qa.campaignStruct) return;
    if (!qa.campaignStruct->factionsSortedByDescrStrat[0])
    {
        qa.campaignStruct = NULL;
        qa.currentFaction = NULL;
        qa.stratPosition = NULL;
        qa.selectGeneral = NULL;
        new_events::onCampaignMapUnloaded();
    }
}

string getClickCharacterName()
{
    if (!(qa.stratPosition && qa.stratPosition->x && qa.stratPosition->y)) 
        return "null";

    qa.xLocCoord = qa.stratPosition->x;
    qa.yLocCoord = qa.stratPosition->y;
 
    if (!qa.campaignStruct) 
        return "null";

    string text = "";
    for (int f = 0; f < 21; f++)
    {
        factionStruct* faction = qa.campaignStruct->factionsSortedByID[f];
        if (!faction) 
            continue;

        for (int c = 0; c < faction->numOfCharacters; c++)
        {
            character* currentChar = faction->characters[c];
            if (qa.xLocCoord == currentChar->xCoord && qa.yLocCoord == currentChar->yCoord)
            {
                qa.selectGeneral = currentChar->genChar;
                text = text + qa.selectGeneral->fullName + "(" + faction->factSmDescr->facName + ")";
                return text;
            }
        }
    }

    return "null";
}

string getAndPrintStratPosition()
{
    if (qa.stratPosition && qa.stratPosition->x >= 0 && qa.stratPosition->y >= 0)
    {
        string coords = to_string(qa.stratPosition->x) + ", " + to_string(qa.stratPosition->y);
        return coords;
    }
    return "null, null";
}

void killPMOpercent(float percent)
{
    if (!qa.selectGeneral) return;

    struct stackStruct* army = qa.selectGeneral->gen->armyLeaded;
    if (!army) return;

    for (int u = 0; u < army->numOfUnits; u++)
    {
        unit* un = army->units[u];

        float minusSoldierCount_f = (float)un->SoldierCountStrat / 100.0f * percent;
        int   minusSoldierCount_i = static_cast<int>(round(minusSoldierCount_f));

        if (un->SoldierCountStrat - minusSoldierCount_i > 3)
        {
            un->SoldierCountStrat = un->SoldierCountStrat - minusSoldierCount_i;
        }
    }
}

void battle_create::zoomAndSpeed()
{
    if ((qa.camera && qa.battle && qa.battle->battleState > PRE_BATTLE) || gameWindow.mapView)
    {
        // zoom 
        if (GetKeyState(VK_ADD) & 0x8000 && GetKeyState(VK_LCONTROL) & 0x8000)               // CTRL + 
        {
            qa.camera->z = 0.0f;
            memory::Write(&qa.camera->z, cameraAddress, sizeof(qa.camera->z));
            return;
        }
        else if (GetKeyState(VK_SUBTRACT) & 0x8000 && GetKeyState(VK_LCONTROL) & 0x8000)     // CTRL - 
        {
            qa.camera->z += 0.5f;
            memory::Write(&qa.camera->z, cameraAddress, sizeof(qa.camera->z));
            return;
        }

        // speed 
        else if (GetKeyState(VK_ADD) & 0x8000 && GetKeyState(VK_LSHIFT) & 0x8000)     // SHIFT + 
        {
            qa.battle->speed = qa.battle->speed + 0.025f;
            if (qa.battle->speed > 10.0f) qa.battle->speed = 10.0f;
            return;
        }
        else if (GetKeyState(VK_SUBTRACT) & 0x8000 && GetKeyState(VK_LSHIFT) & 0x8000)     // SHIFT - 
        {
            qa.battle->speed -= 0.025f;
            if (qa.battle->speed < 0.0f) qa.battle->speed = 0.025f;
            return;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool debuggAddresses = false;
void getAddresses()
{
    while (debuggAddresses && !IsDebuggerPresent())
    {
        Sleep(100);
    }

    LOG_ALWAYS(RELEASE, "getAddresses()");
    gameWindow.RomeTW_ALX_exe = (uint32_t)GetModuleHandle(nullptr);

    if (offsets.gDataAll)
    {
        gDataAllAddress = memory::Read(gameWindow.RomeTW_ALX_exe + offsets.gDataAll);
        qa.gDataAll = reinterpret_cast<gameDataAllStruct*>(gDataAllAddress);
    }

    if (offsets.camera)
    {
        cameraAddress = memory::Read(gameWindow.RomeTW_ALX_exe + offsets.camera);
        qa.camera = reinterpret_cast<battleCamera*>(cameraAddress);
    }

    LOG_ALWAYS(RELEASE, "RomeTW_ALX_exe: " + to_string(gameWindow.RomeTW_ALX_exe) +
        ", gDataAllAddress: " + to_string(gDataAllAddress) +
        ", cameraAddress: " + to_string(cameraAddress) + 
        ", gDataAll: " + boolStr(qa.gDataAll) +
        ", camera: " + boolStr(qa.camera)
    );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// draw /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool gameStart = true;
void battle_create::drawBattle()
{
    if (gameStart)
    {
        gameStart = false;
        ImGui::InsertNotification({ ImGuiToastType_Success, 9000, desTab.RTWHST.c_str() });
    }

    createScreenshots();
    onCampaignMapUnloaded();
    zoomAndSpeed();
    createBattle();

    if (gameWindow.rect.left == 0 && gameWindow.rect.right == 0 && gameWindow.rect.top == 0 && gameWindow.rect.bottom == 0)
    {
        getWindowRect();
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////












