#pragma once
#include "..\helper_functions.h"
#include "../../differentFunctions/stringThings.h"
#include "../../differentFunctions/encryption.h"
using namespace std;

struct HS_FACTION
{

};

typedef string MESSAGE_MATRIX[21][21];

struct HOT_SEAT
{
	HOT_SEAT();

	string           m_hot_seat_name;
	bool             m_is_hot_seat_campaign;
	bool             m_is_load_save;
	int              m_keymaster_faction_id;
	string           m_keymaster_password;
	size_t           m_keymaster_password_hash;
	int              m_current_faction_id;

	string           m_faction_name[21];
	bool             m_player_faction[21];
	string           m_password[21];
	size_t           m_password_hash[21];
	string           m_player_nickname[21];
	factionLocName   m_faction_localized_name;

	bool             m_pre_player_faction;
	bool             m_control_transferred;
	bool             m_block_game_console;
	bool             m_block_advisor_scripts;
	bool             m_candidate_marry;
	string           m_log_for_save;
	bool             m_never_withdraw;

	MESSAGE_MATRIX   m_message;


	// functions: 
	bool             onSave(string savePath);
	bool             onLoad(string savePath);
	void             onPseudoPreFactionTurnStart(factionStruct* faction);
	void             onNewGameStart(campaign* camp);
	void             onCampaignMapLoaded(campaign* camp);
	void             onCreateScriptFromFile(string fileName);
	void             createCandidateMarrying(factionStruct* faction);


	// draw:   
	bool             m_open_menu;
	bool             m_open_password;
	bool             m_is_strat_map_draw;
	string           m_input_buffer_1;
	string           m_input_buffer_2;
	string           m_input_buffer_3;
	bool             m_show_keymaster_console;

	bool             m_diplomacy_overview_scroll;
	bool             m_open_players_list;
	bool             m_open_write_message;
	bool             m_open_come_message;
	bool             m_file_requester_scroll;
	string           m_file_requester_buffer;


	bool             drawSettings();
	void             drawMenu();
	void             drawPassword();

	void             drawPlayersButton();
	void             drawPlayersList();
	void             drawWriteMessage(int sender, int recipient);

	void             brokenSave(int val);
	void             brokenSaveOnPreSave();
	void             setOwnerTooltip();


	// methods: 
	void             setHotSeatCampaign(bool click)              { m_is_hot_seat_campaign = click; }
	void             setKeymasterPassword(string password)       { m_keymaster_password = password; m_keymaster_password_hash = stringToHash(password); }
	void             log(string text)                            { m_log_for_save += LOG.getTime(false) + " " + text + " \n"; }
	void             clearLog()                                  { m_log_for_save = ""; }

	void setPlayerFaction(factionStruct* fac, string password, string nickname, bool keymaster, bool click)
	{ 
		int facDipNum                = fac->dipNum;
		m_faction_name[facDipNum]    = fac->factSmDescr->facName;
		m_player_faction[facDipNum]  = click;
		m_password[facDipNum]        = password; 
		m_password_hash[facDipNum]   = stringToHash(password);
		m_player_nickname[facDipNum] = nickname;
		if (keymaster)
		{
			m_keymaster_faction_id = facDipNum;
		}
	}

	void setPlayerFaction(factionStruct* fac, string password, string nickname, bool keymaster)
	{
		int facDipNum                = fac->dipNum;
		m_faction_name[facDipNum]    = fac->factSmDescr->facName;
		m_player_faction[facDipNum]  = true;
		m_password[facDipNum]        = password;
		m_password_hash[facDipNum]   = stringToHash(password);
		m_player_nickname[facDipNum] = nickname;
		if (keymaster)
		{
			m_keymaster_faction_id = facDipNum;
		}
	}

	size_t getPreviousFaction(int currentID) const
	{
		int stop = 0;
		int f = currentID - 1;
		for (; true; )
		{
			if (f == -1)
				f = 20;

			if (m_player_faction[f])
			{
				return m_password_hash[f];
			}

			f--;

			stop++;
			if (stop > 21)
			{
				return 0;
			}
		}
		return 0;
	}

	void checkKeymasterConsole()
	{
	//	m_show_keymaster_console = !m_is_load_save || m_current_faction_id == m_keymaster_faction_id;
		m_block_game_console     = m_is_hot_seat_campaign;
		m_show_keymaster_console = !m_is_load_save && !m_block_game_console;
	}

	void checkDiplomacyOverviewScroll(char* resourceDescription, bool open)
	{
		if (m_is_hot_seat_campaign && strcmp(resourceDescription, "diplomacy_overview_scroll") == 0)
		{
			m_diplomacy_overview_scroll = open;
		}
		else if (open && strcmp(resourceDescription, "file_requester_scroll") == 0)
		{
			m_file_requester_scroll = open;
		}
		else if (!open && strcmp(resourceDescription, "file_io_result_scroll") == 0)
		{
			m_file_requester_scroll = open;
		}
	}

	void checkMessage()
	{
		m_open_come_message = false;
		for (int f = 0; f < 21; f++)
		{
			if (m_player_faction[f] && m_message[f][m_current_faction_id] != "")
			{
				m_open_come_message = true;
				m_open_players_list = true;
				return;
			}
		}
	}

	void clearMessage()
	{
		for (int f = 0; f < 21; f++)
		{
			m_message[m_current_faction_id][f] = "";
		}
	}



};
extern HOT_SEAT HOT_SEAT_CAMPAIGN;


struct saveFilesS
{
	std::vector<std::string>files;
	int everything_deleted;

	void deleteFiles();
	void deleteAgain();
	void deleteAll();

	saveFilesS() :
		files(),
		everything_deleted(0)
	{
	}
};
extern saveFilesS saveFiles;





