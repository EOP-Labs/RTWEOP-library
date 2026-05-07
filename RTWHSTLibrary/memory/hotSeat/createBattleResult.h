#pragma once


void createBattleResult(battleDataS* battle, bool isResult, std::string descrBattlePath);
void transferBattleResult(battleDataS* battle);
extern int goTransferBattleResult;
extern bool goCreateBattle;
void transferResultFromLanMpFile(std::string selFile, battleDataS* battle);


namespace battle_result
{
	void onScrollOpened(char* resourceDescription);
	void onScrollClosed(char* resourceDescription);
	void createMinorCharacters(character* general, std::string fileName, descrFile* df);
}




