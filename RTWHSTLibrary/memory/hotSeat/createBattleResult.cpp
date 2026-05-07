///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <imgui.h>
#include <imgui_notify.h>
#include "../gameStructures.h"
#include "../memoryWork.h"
#include <filesystem>  
#include "../../differentFunctions/stringThings.h"
#include "../../differentFunctions/dm_assert.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include "../../differentFunctions/screenshoter.h"
#include <textures.h>
#include <ImFileDialog.h>
#include "createBattleResult.h"
#include "../helper_functions.h"
#include <regex>
#include "hotSeatCampaign.h"

using namespace std;
using json = nlohmann::json;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// Create Battle Result /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
static json getTraits(namedCharacter* namChar)
{
    if (!namChar->traits)
        return NULL;

    json traits = json::array();
    traitContainer* traitCont = namChar->traits;
    while (traitCont != nullptr)
    {
        json traitArray = json::array({ traitCont->trait->traitEntry->name, traitCont->trait->level->level });
        traits.push_back(traitArray);

        traitCont = traitCont->next;
    }

    return traits;
}

static json getAncillaries(namedCharacter* namChar)
{
    if (namChar->ancNum == 0)
        return NULL;

    json data = json::array();
    UINT32 ancNum = namChar->ancNum;
    for (UINT32 i = 0; i < ancNum; i++)
    {
        data.push_back(namChar->ancillaries[i]->dataAnc->ancName);
    }

    return data;
}

static json getUnitGeneral(unit* un)
{
    if (!un->general)
        return NULL;

    json data;

    data["subFaction"]  = (int)un->general->genChar->subFaction;
    data["isAlive"]     = (int)un->general->genChar->isAlive;
    data["age"]         = (int)un->general->genChar->age;
    data["shortName"]   = validChar(un->general->genChar->shortName);
    data["lastName"]    = validChar(un->general->genChar->lastName);
    data["portrait"]    = validChar(un->general->genChar->portrait);
    data["traits"]      = getTraits(un->general->genChar);
    data["ancillaries"] = getAncillaries(un->general->genChar);

    return data;
}

static json getUnits(battleArmy bArmy)
{
    json data = json::array();
    json unitJ;
    for (int u = 0; u < bArmy.unitCount; u++)
    {
        unit* un                = bArmy.units[u].unit;
        unitJ["number in army"] = u;
        unitJ["type"]           = un->eduEntry->Type;
        unitJ["soldiers"]       = un->SoldierCountStrat;
    //  unitJ["soldBattle"]     = un->SoldierCountBattlemap;
    //  unitJ["soldiers_new"]   = bArmy.units[u].soldiersStart - bArmy.units[u].soldiersLost + bArmy.units[u].soldiersHealed;
        unitJ["exp"]            = un->expScreen;
    //  unitJ["exp_new"]        = bArmy.units[u].expStart + bArmy.units[u].expGained;
        unitJ["general"]        = getUnitGeneral(un);

        data.push_back(unitJ);
    }
    return data;
}

static json getArmy(battleArmy bArmy)
{
    json armyJ;
//  armyJ["isAlive"]    = (int)bArmy.army->gen->genChar->isAlive;
    armyJ["age"]        = (int)bArmy.army->gen->genChar->age;
    armyJ["numOfUnits"] = bArmy.army->numOfUnits;
    armyJ["units"]      = getUnits(bArmy);

    return armyJ;
}

static json getCharacter(factionStruct* fac, battleSide& side)
{
    json character;

    for (int a = 0; a < side.armiesNum; a++)
    {
        battleArmy bArmy = side.forces[a];
        if (fac == bArmy.army->faction)
        {
            character[bArmy.army->gen->genChar->fullName] = getArmy(bArmy);
        }
    }
    return character;
}

void createBattleResult(battleDataS* battle, bool isResult, string descrBattlePath)
{
    LOG_ALWAYS(RELEASE, "---createBattleResult(start)---");

    json facs;
    for (int i = 0; i < battle->sidesNum; i++)
    {
        battleSide& side = battle->sides[i];
        string notDouble = "";
        for (int j = 0; j < side.armiesNum; j++)
        {
            string facName = side.armies[j].stack->faction->factSmDescr->facName;
            if (notDouble.find("_" + facName + "_") == string::npos)
            {
                facs[facName.c_str()] = getCharacter(side.armies[j].stack->faction, side);    
            }
            notDouble = notDouble + "_" + facName + "_";
        }
    }

    if (facs == NULL)
    {
        LOG_ALWAYS(RELEASE, desTab.failedRes);
        ImGui::InsertNotification({ ImGuiToastType_Error, 9000, desTab.failedRes.c_str() });
        return;
    }   

    string path = "";
    string jsonFile = "";
    if (isResult)
    {
        string battleName = string(battle->sides[0].armies[0].stack->faction->factSmDescr->facName) + "_" + string(battle->sides[1].armies[0].stack->faction->factSmDescr->facName) + "_" + LOG.getTime(true);
        filesystem::create_directory("dmData/battleResults/");
        path = "dmData/battleResults/" + battleName;
        filesystem::create_directory(path);
        jsonFile = path + "/battleResult.json";
    }
    else
    {
        jsonFile = descrBattlePath + "/characters.json";

    }

    ofstream f1(jsonFile);
    f1 << setw(4) << facs;
    f1.close();

    LOG_ALWAYS(RELEASE, "---createBattleResult(end)---");
    if (isResult)
    {
        ImGui::InsertNotification({ ImGuiToastType_Success, 9000, (desTab.battResult + path).c_str() });
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// Transfer Battle Result ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool checkJsonKey(json jsonArray, string key)
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

static void getBattleCharacterJ(factionStruct* fac, battleSide& side, json characterJ)
{
    for (int a = 0; a < side.armiesNum; a++)
    {
        stackStruct* army = side.armies[a].stack;
        if (fac == army->faction)
        {
            char* fullName = army->gen->genChar->fullName;
            json unitsArray = json::array();
            int numOfUnits = 0;
            int age = 0;
            json armyJ = NULL;

            if (!dm_assert(checkJsonKey(characterJ, string(fullName)), "general not found: " + string(fullName)))
                continue;

            characterJ.at(fullName).get_to(armyJ);
            armyJ.at("age").get_to(age);
            armyJ.at("numOfUnits").get_to(numOfUnits);
            armyJ.at("units").get_to(unitsArray);
            LOG_ALWAYS(RELEASE, "character: " + string(fullName) + ", numOfUnits: " + to_string(numOfUnits));

            if (numOfUnits == army->numOfUnits && age == (int)army->gen->genChar->age)
            {
            //  for (int u = 0; u < army->numOfUnits; u++)
                for (int u = army->numOfUnits; u >= 0; u--)
                {
                    unit* un = army->units[u];
                    if (unitsArray.is_object() || unitsArray.is_array())
                    {
                        for (auto& it : unitsArray.items())
                        {
                            auto k = it.key();
                            auto v = it.value().type_name();
                            json unit = it.value();
                            int numberInArmy = 0;
                            string unitType = "type";
                            unit.at("number in army").get_to(numberInArmy);
                            unit.at("type").get_to(unitType);

                            if (numberInArmy == u && unitType == un->eduEntry->Type)
                            {
                                numOfUnits--;
                                unit.at("soldiers").get_to(un->SoldierCountStrat);

                                if (un->general)
                                {
                                    int isAlive = 1;
                                    json generalJ = NULL;
                                    unit.at("general").get_to(generalJ);
                                    generalJ.at("isAlive").get_to(isAlive);

                                    if (isAlive == 0)
                                    {
                                        un->general->genChar->deathType = BATTLE;
                                        new_events::o_onKillCharacter(un->general);
                                    }
                                    else if (un->SoldierCountStrat > 0)
                                    {
                                        int r_exp;
                                        unit.at("exp").get_to(r_exp);
                                        army->units[u]->setExperience(r_exp);
                                    }
                                }
                                else if (un->SoldierCountStrat > 0)
                                {
                                    int r_exp;
                                    unit.at("exp").get_to(r_exp);
                                    army->units[u]->setExperience(r_exp);
                                }

                                LOG_ALWAYS(RELEASE, "unitsArray(key: " + k + ", " + v + " | " + unitType + " | exp: " + to_string(un->expScreen) + ", SoldierCountStrat: " + to_string(un->SoldierCountStrat) + ")");
                            }
                        //  else
                        //  {
                        //      string err = desTab.errTypeUnits + " | " + unitType;
                        //      ImGui::InsertNotification({ ImGuiToastType_Error, 9000, err.c_str() });
                        //  }
                        }
                    }
                }

                if (numOfUnits > 0)
                {
                    ImGui::InsertNotification({ ImGuiToastType_Error, 9000, desTab.errTypeUnits.c_str() });
                }
            }
            else
            {
                string err = desTab.errNumUnits + " | " + fullName;
                ImGui::InsertNotification({ ImGuiToastType_Error, 9000, err.c_str() });
            }

            ImGui::InsertNotification({ ImGuiToastType_Success, 3000, fullName });
        }
    }
}

static void transferResultFromFile(string selFile, battleDataS* battle)
{
    if (selFile.find("lan_mp_") != std::string::npos || selFile.find(".txt") != std::string::npos)
    {
        transferResultFromLanMpFile(selFile, battle);
        return;
    }


    json result;
    ifstream f(filesystem::u8path(selFile));
    result = json::parse(f);
    f.close();

    for (int i = 0; i < battle->sidesNum; i++)
    {
        battleSide& side = battle->sides[i];
        string notDouble = "";
        for (int j = 0; j < side.armiesNum; j++)
        {
            string facName = side.armies[j].stack->faction->factSmDescr->facName;
            if (notDouble.find("_" + facName + "_") == string::npos)
            {
                json characterJ = NULL;
                result.at(facName.c_str()).get_to(characterJ);
                ImGui::InsertNotification({ ImGuiToastType_Success, 3000, facName.c_str() });
                LOG_ALWAYS(RELEASE, "faction: " + facName);
                getBattleCharacterJ(side.armies[j].stack->faction, side, characterJ);
            }
            notDouble = notDouble + "_" + facName + "_";
        }
    }

    ImGui::InsertNotification({ ImGuiToastType_Success, 9000, desTab.resultsDone.c_str() });
    LOG_ALWAYS(RELEASE, desTab.transferRes + " 8");
}

bool isWIN = false;
static void setWinner()
{
    if (isWIN)
    {
        LOG_ALWAYS(RELEASE, "WIN true");
        helper_functions::callGameConsoleCommand("auto_win", "attacker");
    }
    else
    {
        LOG_ALWAYS(RELEASE, "WIN false");
        helper_functions::callGameConsoleCommand("auto_win", "defender");
    }
}

static bool isDialogOpen = false;
static bool alpB = false;
static float alp = 0.2f;
bool goCreateBattle = false;
static int my_image_width = 0;
static int my_image_height = 0;
static PDIRECT3DTEXTURE9 my_texture = NULL;
static RECT rect = gameWindow.rect;
static int scr_width = 0;
static int scr_height = 0;
int goTransferBattleResult = 0;
static string selectedFile;
battleDataS* battleRes = NULL;
static bool isCheckBox = false;
bool isPMO = false;
void transferBattleResult(battleDataS* battle)
{
    if (HOT_SEAT_CAMPAIGN.m_open_password)
        return;


    if (goTransferBattleResult == 2 && isPMO)
    {
        LOG_ALWAYS(RELEASE, desTab.transferRes + " 6");
        callGameButton("prebattle_withdraw_button");
    }
    else if (goTransferBattleResult == 2 && !isPMO)
    {
        LOG_ALWAYS(RELEASE, desTab.transferRes + " 4");
        callGameButton("prebattle_auto_resolve_button");
    }


    if (goTransferBattleResult != 1 || gameWindow.mapView) return;
    bool openPreBattleMenu = true;

    if (!my_texture)
    {
        LOAD_TEXTURE("dmData/images/battleOptions.tga", &my_texture, &my_image_width, &my_image_height);
    }

    rect = gameWindow.rect;
    ImGui::SetNextWindowPos( {0, 0}, ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2((float)rect.right, (float)rect.bottom));

    if (alp <= 0.05f)
    {
        alpB = true;
    }
    else if (alp >= 0.5f)
    {
        alpB = false;
    }

    if (alpB)
    {
        alp = alp + 0.0050f;
    }
    else
    {
        alp = alp - 0.0050f;
    }

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, alp));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::Begin(desTab.transferRes.c_str(), &openPreBattleMenu, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus);
    ImGui::PopStyleColor(2);

    ImVec2 imgSize = getOurSize(200, 66);
    ImVec2 coords = ImageCentered(my_texture, imgSize);

    float imgSizePartX = getOurSizeX(64);
    ImGui::SetCursorPos(coords);
    if (!isDialogOpen && beginOurTooltip(ImVec2(imgSizePartX, imgSize.y), desTab.createBattle.c_str()) && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        LOG_ALWAYS(RELEASE, desTab.createBattle);
        goCreateBattle = true;
        goTransferBattleResult = -1;
    }


    float xTool = coords.x + imgSizePartX + 2.0f;
    if (isCheckBox)
    {
        ImGui::BeginGroup();

        ImGui::SetCursorPos(ImVec2(xTool, coords.y - 20.0f));
        ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(ImColor(208, 206, 92)));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 0, 51)));
        if (ImGui::Checkbox(u8"PMO", &isPMO))
        {
            if (isPMO)
            {
                LOG_ALWAYS(RELEASE, "PMO true");
            }
            else
            {
                LOG_ALWAYS(RELEASE, "PMO false");
            }
        }


        ImGui::SameLine();
        if (ImGui::Checkbox(u8"WIN", &isWIN))
        {
            setWinner();
        }
        ImGui::PopStyleColor(2);

        ImGui::EndGroup();
    }


    ImGui::SetCursorPos(ImVec2(xTool, coords.y));
    if (!isCheckBox && !isDialogOpen && beginOurTooltip(ImVec2(imgSizePartX, imgSize.y), desTab.transferRes.c_str()) && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        LOG_ALWAYS(RELEASE, desTab.transferRes + " 1");
        isCheckBox = true;
    }
    else if (isCheckBox && !isDialogOpen && beginOurTooltip(ImVec2(imgSizePartX, imgSize.y), desTab.transferRes.c_str()) && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        LOG_ALWAYS(RELEASE, desTab.transferRes + " 2");
        setWinner();
        isDialogOpen = ifd::FileDialog::Instance().Open(desTab.transferRes, desTab.transferRes, "file (*.json;){.json},.*");
    }
    if (ifd::FileDialog::Instance().IsDone(desTab.transferRes)) {
        if (ifd::FileDialog::Instance().HasResult()) {
            LOG_ALWAYS(RELEASE, desTab.transferRes + " 3");
            selectedFile = ifd::FileDialog::Instance().GetResult().u8string();
            goTransferBattleResult = 2;
            openPreBattleMenu = false;
            battleRes = battle;

            if (isPMO)
            {
                transferResultFromFile(selectedFile, battle);
            }
        }
        ifd::FileDialog::Instance().Close();
        isDialogOpen = false;
    }


    float xTool2 = xTool + imgSizePartX + 2.0f;
    ImGui::SetCursorPos(ImVec2(xTool2, coords.y));
    if (!isDialogOpen && beginOurTooltip(ImVec2(imgSizePartX, imgSize.y), desTab.close.c_str()) && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        LOG_ALWAYS(RELEASE, desTab.close);
        goTransferBattleResult = -1;
    }

//  setNewCursor();
    ImGui::End();
}

namespace battle_result
{
    void onScrollOpened(char* resourceDescription)
    {
        if (goTransferBattleResult == 2 && battleRes && !isPMO && strcmp(resourceDescription, "post_battle_scroll") == 0)
        {
            LOG_ALWAYS(RELEASE, desTab.transferRes + " 5");
            transferResultFromFile(selectedFile, battleRes);
            goTransferBattleResult = -1;
            selectedFile.clear();
            battleRes = NULL;
            isCheckBox = false;
            isPMO = false;
        }
    }

    void onScrollClosed(char* resourceDescription)
    {
        if (goTransferBattleResult == 2 && battleRes && isPMO && strcmp(resourceDescription, "prebattle_scroll") == 0)
        {
            LOG_ALWAYS(RELEASE, desTab.transferRes + " 7");
            goTransferBattleResult = -1;
            selectedFile.clear();
            battleRes = NULL;
            isCheckBox = false;
            isPMO = false;
        }
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void createMinorCharacters(character* general, string fileName, descrFile* df)
    {
        factionStruct* faction = general->genChar->faction;
        string fileNameR = regex_replace(fileName, regex("descr_battle.txt"), "");
    //  int _index = 33;

        if (!fileExists(fileNameR + "/characters.json"))
        {
            return;
        }

        json result;
        ifstream f(filesystem::u8path(fileNameR + "/characters.json"));
        result = json::parse(f);
        f.close();

        char* facName = faction->factSmDescr->facName;
        json characterJ = NULL;
        result.at(facName).get_to(characterJ);

        char* fullName = general->genChar->fullName;
        json armyJ = NULL;

        if (!dm_assert(checkJsonKey(characterJ, string(fullName)), "general not found: " + string(fullName)))
            return;

        characterJ.at(fullName).get_to(armyJ);

        json unitsArray = json::array();
        int numOfUnits = 0;
        int age = 0;
        armyJ.at("age").get_to(age);
        armyJ.at("numOfUnits").get_to(numOfUnits);
        armyJ.at("units").get_to(unitsArray);

        stackStruct* army = general->armyLeaded;
        if (numOfUnits == army->numOfUnits && age == (int)general->genChar->age)
        {
            if (unitsArray.is_object() || unitsArray.is_array())
            {
                for (auto& it : unitsArray.items())
                {
                    auto k = it.key();
                    auto v = it.value().type_name();

                    json unitJ = it.value();
                    int numberInArmy = 0;
                    string unitType = "type";
                    unitJ.at("number in army").get_to(numberInArmy);
                    unitJ.at("type").get_to(unitType);

                    json generalJ = it.value();
                    unitJ.at("general").get_to(generalJ);

                    for (int u = 0; u < army->numOfUnits; u++)
                //  for (int u = army->numOfUnits; u >= 0; u--)
                    {
                        unit* un = army->units[u];

                        if (u > 0 && !un->general && !generalJ.is_number() && numberInArmy == u && unitType == un->eduEntry->Type)
                        {
                            string shortName = "";
                            string lastName  = "";
                            string portrait  = "";
                            int _age         = 17;
                            int subFaction   = faction->dipNum;

                            generalJ.at("shortName").get_to(shortName);
                            generalJ.at("lastName").get_to(lastName);
                            generalJ.at("portrait").get_to(portrait);
                            generalJ.at("age").get_to(_age);
                            if (checkJsonKey(generalJ, "subFaction")) // чтоб старые файлы работали, до "subFaction"   
                            {
                                LOG_REMINDER("if (checkJsonKey(generalJ, 'subFaction')) - убрать это в следующих версиях");
                                generalJ.at("subFaction").get_to(subFaction);
                            }
                        //  generalJ.at("traits").get_to(portrait);
                        //  generalJ.at("ancillaries").get_to(portrait);

                            /*
                            typedef character* __cdecl func(descrFile* bFile, factionStruct* faction, int age, const char* name, const char* surname, int subFaction, const char* portrait, int x, int y);
                            func* f = (func*)0x0089061c;
                            character* new_character = f(df, faction, _age, shortName.c_str(), lastName.c_str(), faction->dipNum, general->genChar->portrait, 0, 0);
                            */
                            
                            character* new_character = new_events::onCharacterCreated(NAMED_CHARACTER, faction, _age, shortName.c_str(), lastName.c_str(), subFaction, "", general->xCoord, general->yCoord);

                            un->general = new_character;
                            new_character->bodyguards = un;

                            char* cstr = new char[portrait.size()];

#pragma warning(suppress : 4996)
                            strcpy(cstr, portrait.c_str());

                            new_character->genChar->portrait  = cstr;
                            new_character->genChar->portrait2 = cstr;

                            new_character->genChar->portraitIndex = 1;
                        }
                    }
                }
            }
        }
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct lanMpUnit
{
    string Type;
    string Deployed;
    string Initial_exp;
    string Exp_gained;
    string Armour;
    string Weapon;
    string Remaining;

    lanMpUnit() :
        Type        (""),
        Deployed    (""),
        Initial_exp (""),
        Exp_gained  (""),
        Armour      (""),
        Weapon      (""),
        Remaining   ("")
    {
    }
};

struct lanMpFile
{
    map<int, lanMpUnit> unit;
    string startBlockArmy   = "Units:";
    string stopBlockUnit[2] = { "Kills: ", "Cost: " };
    string stopBlockArmy[7] = { "Men: ", "Killed: ", "Result: ", "TotalCost: ", "Player_", "PlayerSetup: ", "Team: " };
    bool isUnitBlock        = false;
    bool isStartUnitBlock   = false;

    lanMpFile(string selFile)
    {
        int units  = -1;

        string line;
        ifstream file(selFile);
 
        while (getline(file, line))
        {
            if (line.find(startBlockArmy) != string::npos)
            {
                isStartUnitBlock = true;
                continue;
            }
            else if (isStartUnitBlock && line.find(stopBlockUnit[0]) == string::npos && line.find(stopBlockUnit[1]) == string::npos && 
                line.find(stopBlockArmy[0]) == string::npos && line.find(stopBlockArmy[1]) == string::npos && line.find(stopBlockArmy[2]) == string::npos && 
                line.find(stopBlockArmy[3]) == string::npos && line.find(stopBlockArmy[4]) == string::npos && line.find(stopBlockArmy[5]) == string::npos && line.find(stopBlockArmy[6]) == string::npos)
            {
                units++;
                unit[units]      = lanMpUnit();
                unit[units].Type = line;
                isStartUnitBlock = false;
                isUnitBlock      = true;
            }
            else if (isUnitBlock)
            {
                if (line.find("Deployed:") != string::npos)
                {
                    unit[units].Deployed = regex_replace(line, regex("Deployed:"), "");
                }
                else if (line.find("Initial_exp:") != string::npos)
                {
                    unit[units].Initial_exp = regex_replace(line, regex("Initial_exp:"), "");
                }
                else if (line.find("Exp_gained ") != string::npos)
                {
                    unit[units].Exp_gained = regex_replace(line, regex("Exp_gained "), "");
                }
                else if (line.find("Armour: ") != string::npos)
                {
                    unit[units].Armour = regex_replace(line, regex("Armour: "), "");
                }
                else if (line.find("Weapon: ") != string::npos)
                {
                    unit[units].Weapon = regex_replace(line, regex("Weapon: "), "");
                }
                else if (line.find("Remaining: ") != string::npos)
                {
                    unit[units].Remaining = regex_replace(line, regex("Remaining: "), "");
                }
                else if (line.find(stopBlockUnit[0]) != string::npos || line.find(stopBlockUnit[1]) != string::npos)
                {
                    isUnitBlock      = false;
                    isStartUnitBlock = true;
                }
            }
        }
        file.close();
    }
};

void transferResultFromLanMpFile(string selFile, battleDataS* battle)
{
    lanMpFile lanData = lanMpFile(selFile);
    int lan_u = 0;

    for (int i = 0; i < battle->sidesNum; i++)
    {
        battleSide& side = battle->sides[i];
        for (int a = 0; a < side.armiesNum; a++)
        {
            stackStruct* army = side.armies[a].stack;
            string fullName = army->gen->genChar->fullName;
            for (int u = 0; u < army->numOfUnits; u++)
            {
                unit* un = army->units[u];
                lanMpUnit lanUnit = lanData.unit[lan_u];
                lan_u++;
                if (lanUnit.Type == un->eduEntry->Type)
                {
                    int sold = stoi(lanUnit.Remaining);
                    if (sold == 0)
                    {
                        if (un->general)
                        {
                            un->general->genChar->deathType = BATTLE;
                            new_events::onKillCharacter(un->general);
                        }
                        else
                        {
                        //  new_events::onKillUnit(un); // вылет при вызове во время авторасчёта???   
                            un->SoldierCountStrat = sold;
                        }
                    }
                    else if (sold > 0)
                    {
                        un->SoldierCountStrat = sold;
                        int exp = stoi(lanUnit.Initial_exp) + stoi(lanUnit.Exp_gained);
                        army->units[u]->setExperience(exp);
                    }
                    LOG_ALWAYS(RELEASE, "transferResultFromLanMpFile(unit: " + lanUnit.Type + " | exp: " + to_string(un->expScreen) + ", SoldierCountStrat: " + to_string(un->SoldierCountStrat) + ", general: " + fullName + ")");
                }
                else
                {
                    ImGui::InsertNotification({ ImGuiToastType_Error, 9000, desTab.errTypeUnits.c_str() });
                }
            }

            ImGui::InsertNotification({ ImGuiToastType_Success, 3000, army->gen->genChar->fullName });
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
























