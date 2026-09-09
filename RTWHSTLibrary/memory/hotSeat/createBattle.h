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
    const char* modPatch;
    std::string fullPatch;
    bool toggle_fow      = false;
    bool toggle_fow_pref = false;
};

extern quickAccess qa;




