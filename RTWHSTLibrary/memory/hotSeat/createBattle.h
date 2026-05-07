#pragma once

namespace battle_create
{
    void onBattleStateChange(battleDataS* battle);
    void onBattleEnd(battleDataS* battle);
    void onCampaignMapLoaded(campaign* camp);
    void drawBattle();
    void zoomAndSpeed();
    void createBattle();
}

struct quickAccess
{
    battleCamera* camera;
    battleDataS* battle;
    stratCursorPosition* stratPosition;
    campaign* campaignStruct;
    factionStruct* currentFaction;
    gameDataAllStruct* gDataAll;
    namedCharacter* selectGeneral;
    int xLocCoord = 0;
    int yLocCoord = 0;
    bool isUnitLimitTest = false;
    const char* modPatch;
    std::string fullPatch;
    int toggle_fow = 0;
    int toggle_fow_pref = 0;
};

extern quickAccess qa;




