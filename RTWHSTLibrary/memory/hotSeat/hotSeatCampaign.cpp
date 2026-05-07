#include "hotSeatCampaign.h"
#include <regex>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../../differentFunctions/dm_assert.h"
#include "createBattle.h"
#include <imgui.h>
#include <imgui_stdlib.h>
#include "../../differentFunctions/screenshoter.h"
#include <ImFileDialog.h>
#include <imgui_notify.h>
#include <textures.h>

#define SAVE_FILE (0xbbfc)

using namespace std;
using json = nlohmann::json;

saveFilesS saveFiles;
HOT_SEAT HOT_SEAT_CAMPAIGN;

HOT_SEAT::HOT_SEAT() :
	m_hot_seat_name             ("hot seat"),
	m_is_hot_seat_campaign      (false),
	m_is_load_save              (false),
	m_keymaster_faction_id      (-1),
	m_keymaster_password        (""),
	m_keymaster_password_hash   (0),
	m_current_faction_id        (-1),
	m_faction_name              (),
	m_player_faction            (),
	m_password                  (),
	m_password_hash             (),
	m_player_nickname           (),
	m_faction_localized_name    (),
	m_pre_player_faction        (false),
	m_control_transferred       (false),
	m_block_game_console        (false),
	m_block_advisor_scripts     (false),
	m_candidate_marry           (false),
	m_log_for_save              (""),
	m_never_withdraw            (false),
	m_message                   (),
	m_open_menu                 (false),
	m_open_password             (false),
	m_is_strat_map_draw         (false),
	m_input_buffer_1            (""),
	m_input_buffer_2            (""),
	m_input_buffer_3            (""),
	m_show_keymaster_console    (true),
	m_diplomacy_overview_scroll (false),
	m_open_players_list         (false),
	m_open_write_message        (false),
	m_open_come_message         (false),
	m_file_requester_scroll     (false),
	m_file_requester_buffer     ("")
{
}

static struct helperStruct
{
	bool keymaster_faction[21];
	string password[21];
	bool read_message[21];
	int target_f                = -1;
	int red_color               = 0;
	bool change_color           = false;
	bool change_tooltip         = false;
	string tooltip_buffer       = "Это принадлежит другой фракции";

	helperStruct() :
		keymaster_faction       (),
		password                (),
		target_f                (-1),
		read_message            (),
		red_color               (0),
		change_color            (false),
		change_tooltip          (false),
		tooltip_buffer          ("Это принадлежит другой фракции")
	{
	}
}helper;

void HOT_SEAT::onPseudoPreFactionTurnStart(factionStruct* faction)
{
	if (!m_is_hot_seat_campaign) 
		return;

	m_open_menu                 = false;
	m_diplomacy_overview_scroll = false;
	m_open_players_list         = false;

	if (!m_player_faction[faction->dipNum])
		return;


	char* facName = faction->factSmDescr->facName;
	LOG_ALWAYS(RELEASE, "controlNextFaction(" + string(facName) + ")");

	helper_functions::callGameConsoleCommand("control", facName);

	m_current_faction_id = faction->dipNum;

	new_events::callScript(
		"call_object_shortcut strat_ui capital_zoom\n"
		"zoom_strat_camera 0.1"
	);

	createCandidateMarrying(faction);

	m_pre_player_faction = false;
	m_input_buffer_1 = "";
	m_input_buffer_2 = "";
	m_input_buffer_3 = "";

	clearMessage();
	checkMessage();
	helper = helperStruct();
	m_open_password = true;

	string saveFile = string(qa.modPatch) + "/saves/" + string(faction->factSmDescr->facName) + "_" + to_string(qa.campaignStruct->turnNumber + 1) + ".sav";
	new_events::callSaveCreate(saveFile.c_str());
	ImGui::InsertNotification({ ImGuiToastType_Success, 6700, ("save created: " + saveFile).c_str() });
}

void HOT_SEAT::onNewGameStart(campaign* camp)
{
	if (startSettings.gameVersion == 2)// если это Steam версия, то отбой - временно   
		return;

	brokenSave(SAVE_FILE);
	HOT_SEAT_CAMPAIGN = HOT_SEAT();
	helper = helperStruct();
//	m_faction_localized_name = camp->getLocalizedNames();
}

void HOT_SEAT::onCampaignMapLoaded(campaign* camp)
{
	helper = helperStruct();

	if (!m_is_hot_seat_campaign) return;

	m_input_buffer_1 = "";
	m_input_buffer_2 = "";
	m_input_buffer_3 = "";
	checkMessage();

	if (factionLocalizedName.getName(0) == "")
	{
		m_faction_localized_name = camp->getLocalizedNames();
	}
	else
	{
		m_faction_localized_name = factionLocalizedName;
	}

	m_open_password = true;
}

void HOT_SEAT::brokenSave(int val)
{
	if (startSettings.gameVersion == 2)// если это Steam версия, то отбой - временно   
		return;

	if (!val) val = SAVE_FILE + 3;

	unsigned short val_short = val;
	size_t size = sizeof(val_short);

	const DWORD load = 0x0040E703;
	memory::Write(&val, load, size);

	const DWORD save = 0x0040E9C6;
	memory::Write(&val_short, save, size);
}

void HOT_SEAT::brokenSaveOnPreSave()
{
	if (!m_is_hot_seat_campaign) return;

	m_current_faction_id = helper_functions::getGameDataAll()->campaignData->currentFactionTurn->dipNum;
	size_t previous_faction_hash = getPreviousFaction(m_current_faction_id);
	brokenSave(
		SAVE_FILE   						  ^ (m_current_faction_id + 1) + 
		m_keymaster_password_hash             ^ (m_current_faction_id + 1) +
		previous_faction_hash                 ^ (m_current_faction_id + 1) +
		m_password_hash[m_current_faction_id] ^ (m_current_faction_id + 1)
	);
}

bool HOT_SEAT::onLoad(string savePath)
{
	HOT_SEAT_CAMPAIGN = HOT_SEAT();
	string hsFile = "dmData\\temp\\temp_file3";
	if (!fileExists(hsFile))
	{
		brokenSave(SAVE_FILE);
		return false;
	}


	string newFile = "dmData\\temp\\hs.bin";
//	size_t key = stringToHash(newFile);
//	encryption::encryptionString(hsFile, newFile, key);
	encryption::encryptionBin(hsFile, newFile, to_string(sumFile.sumAll));
	if (MoveFileExA(newFile.c_str(), "dmData\\temp\\hs.json", MOVEFILE_REPLACE_EXISTING))
	{
		remove(newFile.c_str());
	}


	m_is_load_save = true;

	json result;
	ifstream f(filesystem::u8path("dmData\\temp\\hs.json"));
	result = json::parse(f);
	f.close();

	result.at("hot_seat_name"       ).get_to(m_hot_seat_name);
	result.at("is_hot_seat_campaign").get_to(m_is_hot_seat_campaign);
	result.at("keymaster_faction_id").get_to(m_keymaster_faction_id);
	result.at("keymaster_password"  ).get_to(m_keymaster_password_hash);
	result.at("current_faction_id"  ).get_to(m_current_faction_id);
	result.at("log_for_save"        ).get_to(m_log_for_save);
	result.at("never_withdraw"      ).get_to(m_never_withdraw);
	result.at("candidate_marry"     ).get_to(m_candidate_marry);

	json mesJ = NULL;
	result.at("messages").get_to(mesJ);
	for (int f = 0; f < 21; f++)
	{
		json facM = mesJ[f];
		for (auto& it : facM.items())
		{
			m_message[f][stoi(it.key())] = it.value();
		}
	}


	json factionsJ = NULL;
	result.at("factions").get_to(factionsJ);
	int i = 0;
	if (factionsJ.is_object() || factionsJ.is_array())
	{
		for (auto& it : factionsJ.items())
		{
			auto k = it.key();
			auto v = it.value().type_name();
			json fac = it.value();

			fac.at("faction_name").get_to(m_faction_name[i]);
			fac.at("player_faction").get_to(m_player_faction[i]);
			fac.at("password").get_to(m_password_hash[i]);
			fac.at("player_nickname").get_to(m_player_nickname[i]);

			i++;
		}
	}
	checkKeymasterConsole();

/*
	newFile = "dmData\\temp\\temp_file.bin";
	size_t keyS[4] = {
		getPreviousFaction(m_current_faction_id),
		stringToHash(m_faction_name[m_current_faction_id]),
		m_password_hash[m_current_faction_id],
		m_keymaster_password_hash
	};
	encryption::encryptionBin("dmData\\temp\\temp_file", newFile, keyS, 3);
*/

	size_t previous_faction_hash = getPreviousFaction(m_current_faction_id);
	newFile = "dmData\\temp\\temp_file.bin";
	string keyS = to_string(
		previous_faction_hash +
		stringToHash(m_faction_name[m_current_faction_id]) +
		m_password_hash[m_current_faction_id] +
		m_keymaster_password_hash
	);
	encryption::encryptionBin("dmData\\temp\\temp_file", newFile, keyS);
//	encryption::encryptionBin("dmData\\temp\\temp_file", newFile, keyS, 500);

	brokenSave(
		SAVE_FILE   						  ^ (m_current_faction_id + 1) + 
		m_keymaster_password_hash             ^ (m_current_faction_id + 1) +
		previous_faction_hash                 ^ (m_current_faction_id + 1) +
		m_password_hash[m_current_faction_id] ^ (m_current_faction_id + 1)
	);

	if (MoveFileExA(newFile.c_str(), "dmData\\temp\\temp_file", MOVEFILE_REPLACE_EXISTING))
	{
		remove(newFile.c_str());
		remove("dmData\\temp\\hs.json");
	}

	return true;
}

bool HOT_SEAT::onSave(string savePath)
{
	if (!m_is_hot_seat_campaign) 
		return false;


	m_current_faction_id = helper_functions::getGameDataAll()->campaignData->currentFactionTurn->dipNum;
	m_hot_seat_name      = startSettings.mainHotSeat;

	json data;

	data["hot_seat_name"]        = m_hot_seat_name;
	data["is_hot_seat_campaign"] = m_is_hot_seat_campaign;
	data["keymaster_faction_id"] = m_keymaster_faction_id;
	data["keymaster_password"]   = m_keymaster_password_hash;
	data["current_faction_id"]   = m_current_faction_id;
	data["log_for_save"]         = m_log_for_save;
	data["never_withdraw"]       = m_never_withdraw;
	data["candidate_marry"]      = m_candidate_marry;

	json dataA = json::array();
	for (int f = 0; f < 21; f++)
	{
		json unitM;

		unitM["faction_name"]    = m_faction_name[f];
		unitM["player_faction"]  = m_player_faction[f];
		unitM["password"]        = m_password_hash[f];
		unitM["player_nickname"] = m_player_nickname[f];

		dataA.push_back(unitM);
	}
	data["factions"] = dataA;

	data["messages"] = m_message;

	string jsonFile = "dmData\\temp\\hs.json";
	ofstream f1(jsonFile);
	f1 << setw(4) << data;
	f1.close();


	string newFile = "dmData\\temp\\hs.bin";
//	size_t key = stringToHash(newFile);
//	encryption::encryptionString(jsonFile, newFile, key);
	encryption::encryptionBin(jsonFile, newFile, to_string(sumFile.sumAll));
	if (MoveFileExA(newFile.c_str(), "dmData\\temp\\temp_file3", MOVEFILE_REPLACE_EXISTING))
	{
		remove(newFile.c_str());
		remove(jsonFile.c_str());
	}
	saveFiles.files.push_back("dmData\\temp\\temp_file3");

/*
	newFile = "dmData\\temp\\temp_file.bin";
	size_t keyS[4] = { 
		getPreviousFaction(m_current_faction_id),
		stringToHash(m_faction_name[m_current_faction_id]), 
		m_password_hash[m_current_faction_id], 
		m_keymaster_password_hash 
	};
	encryption::encryptionBin("dmData\\temp\\temp_file", newFile, keyS, 3);
*/

	newFile = "dmData\\temp\\temp_file.bin";
	string keyS = to_string(
		getPreviousFaction(m_current_faction_id) +
		stringToHash(m_faction_name[m_current_faction_id]) +
		m_password_hash[m_current_faction_id] +
		m_keymaster_password_hash
	);
	encryption::encryptionBin("dmData\\temp\\temp_file", newFile, keyS);
//	encryption::encryptionBin("dmData\\temp\\temp_file", newFile, keyS, 500);


	if (MoveFileExA(newFile.c_str(), "dmData\\temp\\temp_file", MOVEFILE_REPLACE_EXISTING))
	{
		remove(newFile.c_str());
	}

	return true;
}

void HOT_SEAT::onCreateScriptFromFile(string fileName)
{
	if (fileName == "dmData\\temp\\temp_file2" || fileName == "luaCommand") // if callScript or callScriptFromFile   
		return;

	ifstream file(fileName);
	uint32_t sum = encryption::checksum(file);
	sumFile.show_me_sum.push_back(sum);
	sumFile.show_me.push_back(fileName);
	sumFile.sumAll += sum;

#if _DEBUG
	LOG_ALWAYS(RELEASE, "getFilesSum(show_me: size: " + to_string(sumFile.show_me_sum.size()) + ", sum: " + to_string(sum) + ", fileName: " + fileName + ", sumFile.sumAll: " + to_string(sumFile.sumAll) + ")");
#endif
}

void HOT_SEAT::createCandidateMarrying(factionStruct* faction)
{
	if (!m_candidate_marry)
		return;

	for (int c = 0; c < faction->numOfCharacters; c++)
	{
		character* cha = faction->characters[c];
		if (cha->genType->type == NAMED_CHARACTER && cha->genChar->isFamily > 0 && cha->genChar->isAlive > 0 && cha->genChar->numberOfChildren > 0)
		{
			for (int ch = 0; ch < cha->genChar->numberOfChildren; ch++)
			{
				namedCharacter* daughter = cha->genChar->childs[ch];
				if (daughter && !daughter->spouse && daughter->isMale == 0 && daughter->isAlive > 0 && daughter->age >= 14 /*&& helper_functions::randomPercent(100)*/)
				{
					namedCharacter* new_husband = new_events::createCandidateMarrying(daughter);
					if (new_husband)
					{
						log("MARRY(faction: " + string(faction->factSmDescr->facName) +
							", daughter: " + string(daughter->fullName) +
							", new_husband: " + string(new_husband->fullName) +
							", coords: " + to_string(cha->xCoord) + "," + to_string(cha->yCoord) + ")"
						);
					}
					else
					{
						log("ERROR_MARRY(the husband was not created for: faction: " + string(faction->factSmDescr->facName) +
							", daughter: " + string(daughter->fullName) +
							", coords: " + to_string(cha->xCoord) + "," + to_string(cha->yCoord) + ")"
						);
					}
					return;
				}
			}
		}
	}
}



bool HOT_SEAT::drawSettings()
{
	ImGui::Checkbox(u8"hotSeatMode", &m_is_hot_seat_campaign);
	if (m_is_hot_seat_campaign && ImGui::Button(desTab.openHS.c_str()))
	{
		if (m_open_menu)
		{
			m_open_menu = false;
		}
		else
		{
			m_open_menu = true;

			if (factionLocalizedName.getName(0) == "")
			{
				m_faction_localized_name = helper_functions::getGameDataAll()->campaignData->getLocalizedNames();
			}
			else
			{
				m_faction_localized_name = factionLocalizedName;
			}

			return false;
		}
	}
	return gameWindow.bShowWindow;
}

void HOT_SEAT::setOwnerTooltip()
{
	if (!gameCursor || !gameCursor->action || !gameCursor->action->tooltip)
		return;

	if (!helper.change_tooltip && ImGui::IsKeyDown(ImGuiKey_LeftCtrl) && ImGui::IsMouseDown(ImGuiMouseButton_Left))
	{
		qa.xLocCoord = qa.stratPosition->x;
		qa.yLocCoord = qa.stratPosition->y;
		oneTile* tile = helper_functions::getTile(qa.xLocCoord, qa.yLocCoord);

		if (tile && tile->object)
		{
			factionStruct* faction = nullptr;

			if (character* object = helper_functions::getCharacterByCoords(qa.xLocCoord, qa.yLocCoord); object)
				faction = object->genChar->faction;
			else if (settlementStruct* object = helper_functions::getSettlementByCoords(qa.xLocCoord, qa.yLocCoord); object)
				faction = object->faction;
			else if (fortStruct* object = helper_functions::getFortByCoords(qa.xLocCoord, qa.yLocCoord); object)
				faction = object->faction;
			else if (portBuildingStruct* object = helper_functions::getPortByCoords(qa.xLocCoord, qa.yLocCoord); object)
				faction = object->settlement->faction;

			if (faction && m_player_faction[faction->dipNum] && m_player_nickname[faction->dipNum].size() > 0)
			{
				UNICODE_STRING**& uni = *gameCursor->action->tooltip;
				helper.tooltip_buffer = uniStringToStr(uni);
				helper.change_tooltip = true;

				string new_tooltip = desTab.player + ": " + m_player_nickname[faction->dipNum];
				createUniString(*gameCursor->action->tooltip, new_tooltip.c_str());
			}
		}
	}
	else if (helper.change_tooltip && !ImGui::IsMouseDown(ImGuiMouseButton_Left))
	{
		helper.change_tooltip = false;
		createUniString(*gameCursor->action->tooltip, helper.tooltip_buffer.c_str());
	}
}

void HOT_SEAT::drawMenu()
{
	if (!m_is_hot_seat_campaign) return;


	saveFiles.deleteAgain();
	drawPassword();
	drawPlayersButton();
	drawPlayersList();
	setOwnerTooltip();


	if (!m_open_menu)
		return;


	RECT rect = gameWindow.rect;
	ImGui::SetNextWindowPos({ 0, 0 }, ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2((float)rect.right, (float)rect.bottom));

	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.9f);
	ImGui::Begin(m_hot_seat_name.c_str(), &m_open_menu, ImGuiWindowFlags_None | ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImGui::PopStyleVar(1);

	helper_functions::disableShortcutsIsWindowFocused();

	ImGui::PushItemWidth(300.F);

	ImGui::Separator();
	ImGui::Separator();
	ImGui::NewLine();
	ImGui::InputText("##0", &m_keymaster_password);
	ImGui::SameLine();
	if (m_keymaster_password_hash == 0 && ImGui::Button(desTab.setKeyPass.c_str()))
	{
		setKeymasterPassword(m_keymaster_password);
	}
	else if (m_keymaster_password_hash > 0 && ImGui::Button(desTab.updKeyPass.c_str()))
	{
		setKeymasterPassword(m_keymaster_password);
		m_show_keymaster_console = false;
		m_block_game_console     = true;
	}
	ImGui::NewLine();
	if (ImGui::Button(desTab.updateFiles.c_str()))
	{
		encryption::updateAllSum();
	}
	ImGui::NewLine();
	ImGui::Checkbox(desTab.husbands.c_str(), &m_candidate_marry);
	ImGui::Checkbox(desTab.neverWithdraw.c_str(), &m_never_withdraw);
#ifdef _DEBUG
	ImGui::NewLine();
	if (ImGui::Button("clearLog()"))
	{
		clearLog();
	}
#endif
	ImGui::NewLine();
	ImGui::Separator();
	ImGui::Separator();


	if (m_keymaster_password_hash > 0)
	{
		campaign* camp = qa.gDataAll->campaignData;
		for (int f = 0; f < 21; f++)
		{
			factionStruct* faction = camp->getFactionById(f);
			if (!faction)
				continue;

			char* facName = faction->factSmDescr->facName;
			if (strcmp(facName, "slave") == 0 || /*strcmp(facName, "romans_senate") == 0 ||*/ faction->numOfCharacters == 0)
				continue;


			ImGui::PushID(f);

			ImGui::TextColored(ImColor(208, 206, 92, 255), m_faction_localized_name.getName(f).c_str());
			ImGui::SameLine(0.0f, 0.1f);
			ImGui::Text("(" + string(facName) + ")");

			helper.keymaster_faction[f] = m_keymaster_faction_id == f;
			if (m_keymaster_faction_id == -1 || m_keymaster_faction_id == f)
			{
				ImGui::SameLine();
				if (ImGui::Checkbox(desTab.isKeymaster.c_str(), &helper.keymaster_faction[f]))
				{
					if (helper.keymaster_faction[f])
						m_keymaster_faction_id = f;
					else
						m_keymaster_faction_id = -1;
				}
			}

			ImGui::TextColored(ImColor(44, 234, 86), desTab.nickname.c_str());
			ImGui::SameLine();
			ImGui::SetCursorPosX(100.f);
			ImGui::InputText("##1", &m_player_nickname[f]);

			ImGui::TextColored(ImColor(44, 234, 86), desTab.password.c_str());
			ImGui::SameLine();
			ImGui::SetCursorPosX(100.f);
			ImGui::InputText("##2", &helper.password[f]);

			const char* text = desTab.setPlayer.c_str();
			if (m_player_faction[f])
			{
				text = desTab.deletePlayer.c_str();
			}

			if (ImGui::Button(text))
			{
				if (!m_player_faction[f])
				{
					setPlayerFaction(faction, helper.password[f], m_player_nickname[f], helper.keymaster_faction[f]); // Set player faction   
				}
				else //if (!m_is_load_save || m_current_faction_id == f)
				{
					setPlayerFaction(faction, "", "", false, false);                                                  // Delete player faction   
					helper.password[f] = "";
					helper.keymaster_faction[f] = false;
				}
			}

			ImGui::NewLine();
			ImGui::NewLine();

			ImGui::PopID();

			ImGui::Separator();
		}
	}


	ImGui::Separator();
	if (ImGui::Button(desTab.close.c_str()))
	{
		m_open_menu = false;
	}
	ImGui::Separator();
	ImGui::Separator();

	ImGui::PopItemWidth();

	ImGui::End();
}

ImVec2 getCenteredPos(ImVec2 size)
{
	ImVec2 window = ImGui::GetWindowSize();
	return ImVec2((window.x - size.x) * 0.5f, (window.y - size.y) * 0.5f);
}

void HOT_SEAT::drawPassword()
{
	if (!m_open_password || !m_is_strat_map_draw)
		return;



	while (qa.toggle_fow == 0)
	{
#ifdef _DEBUG
		LOG_ALWAYS(RELEASE, "while (qa.toggle_fow == 0)");
#endif // _DEBUG

		helper_functions::callGameConsoleCommand("toggle_fow");

		qa.toggle_fow      = *reinterpret_cast<int*>(offsets.toggle_fow);
        qa.toggle_fow_pref = *reinterpret_cast<int*>(offsets.toggle_fow_pref);

//		if (qa.toggle_fow_pref == 0)
//		{
//#ifdef _DEBUG
//			LOG_ALWAYS(RELEASE, "if (qa.toggle_fow_pref == 0)");
//#endif // _DEBUG
//			int state = 1;
//			memory::Write(&state, offsets.toggle_fow_pref, 1);
//		}
	}



	RECT rect = gameWindow.rect;
	ImGui::SetNextWindowPos({ 0, 0 }, ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2((float)rect.right, (float)rect.bottom));
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::Begin("m_open_password", &m_open_password, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImGui::PopStyleColor(1);
	ImGui::PushID("m_open_password_ID");
	ImGui::PushItemWidth(200.F);

	helper_functions::disableShortcutsIsWindowFocused();

	factionStruct* currentFaction = helper_functions::getGameDataAll()->campaignData->currentFactionTurn;
	int facID = currentFaction->dipNum;

	ImGui::Separator();
	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::SetCursorPosX(getCenteredPos(ImGui::CalcTextSize(m_hot_seat_name.c_str())).x);
	ImGui::TextColored(ImColor(255, 0, 0, 255), m_hot_seat_name.c_str());
	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::Separator();

	ImGui::NewLine();
	if (m_player_nickname[facID] == "")
	{
		ImGui::SetCursorPosX(getCenteredPos(ImGui::CalcTextSize((m_faction_localized_name.getName(facID) + "(" + m_faction_name[facID] + ")" + "---" + m_input_buffer_3 + "--------- " + desTab.setNickname).c_str())).x);
	}
	else
	{
		ImGui::SetCursorPosX(getCenteredPos(ImGui::CalcTextSize((m_faction_localized_name.getName(facID) + "(" + m_faction_name[facID] + ")" + "---" + m_player_nickname[facID]).c_str())).x);
	}

	ImGui::TextColored(ImColor(44, 234, 86), m_faction_localized_name.getName(facID).c_str());
	ImGui::SameLine(0.0f, 0.1f);
	ImGui::Text("(" + m_faction_name[facID] + ")");
	ImGui::SameLine();
	ImGui::Text(" - ");
	ImGui::SameLine();
	if (m_player_nickname[facID] == "")
	{
		ImGui::InputText("##11", &m_input_buffer_3);
		ImGui::SameLine();
		if (ImGui::Button(desTab.setNickname.c_str()))
		{
			m_player_nickname[facID] = m_input_buffer_3;
			m_input_buffer_3 = "";
		}
	}
	else
	{
		ImGui::TextColored(ImColor(208, 206, 92, 255), m_player_nickname[facID].c_str());
	}
	ImGui::NewLine();
	ImGui::Separator();


	ImGui::SetCursorPos(getCenteredPos(ImVec2(200.F, 50.F)));
	ImGui::BeginGroup();
	ImGui::InputText("##9", &m_input_buffer_1);

	if (m_password_hash[facID] == 0)
	{
		ImGui::InputText("##10", &m_input_buffer_2);

		ImGui::SetCursorPosX(getCenteredPos(ImGui::CalcTextSize(desTab.start.c_str())).x);
		if (ImGui::Button(desTab.start.c_str()) && m_input_buffer_1 == m_input_buffer_2)
		{
			m_password[facID]      = m_input_buffer_1;
			m_password_hash[facID] = stringToHash(m_input_buffer_1);
			m_open_password        = false;
		}
	}
	else 
	{
		ImGui::SetCursorPosX(getCenteredPos(ImGui::CalcTextSize(desTab.start.c_str())).x);
		if (ImGui::Button(desTab.start.c_str()) && (stringToHash(m_input_buffer_1) == m_password_hash[facID] || stringToHash(m_input_buffer_1) == m_keymaster_password_hash))
		{
			m_open_password = false;
		}
	}
	ImGui::EndGroup();

	ImGui::SetCursorPosY(float(rect.bottom - 100));
	ImGui::Separator();
	ImGui::NewLine();
	if (ImGui::Button(desTab.loadSave.c_str()))
	{
		ifd::FileDialog::Instance().Open("Load Save", desTab.loadSave.c_str(), "file (*.sav;){.sav},.*");
	}
	if (ifd::FileDialog::Instance().IsDone("Load Save"))
	{
		if (ifd::FileDialog::Instance().HasResult()) 
		{
			m_open_password = false;
			string selectedFile = ifd::FileDialog::Instance().GetResult().u8string();
			new_events::callSaveLoad(selectedFile.c_str());
		}
		ifd::FileDialog::Instance().Close();
	}
	ImGui::SameLine();

	ImGui::SetCursorPosX(float(rect.right - ImGui::CalcTextSize(desTab.quitGame.c_str()).x - 15));
	if (ImGui::Button(desTab.quitGame.c_str()))
	{
		new_events::quitGame();
	}
	ImGui::NewLine();
	ImGui::Separator();

	ImGui::PopItemWidth();
	ImGui::PopID();

	ImGui::End();
}

void HOT_SEAT::drawPlayersButton()
{
	if (!m_diplomacy_overview_scroll || m_open_password)
		return;


	RECT rect = gameWindow.rect;
	ImVec2 buttName = ImGui::CalcTextSize(desTab.playersList.c_str());

	ImGui::SetNextWindowPos(ImVec2((float)rect.right - buttName.x * 3, (float)rect.top + buttName.y * 2.5f), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(buttName.x * 1.5f, buttName.y));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::Begin("m_diplomacy_overview_scroll", &m_diplomacy_overview_scroll, ImGuiWindowFlags_NoDecoration);
	ImGui::PopStyleColor(2);

	if (ImGui::Button(desTab.playersList.c_str()))
	{
		if (!m_open_players_list) m_open_players_list = true;
		else                      m_open_players_list = false;
	}

	ImGui::End();
}

void HOT_SEAT::drawPlayersList()
{
	if (!m_open_players_list || m_open_password)
		return;


	RECT rect = gameWindow.rect;
	ImVec2 imgSize = getOurSize(3, 3);
	ImVec2 scrollSize = getOurSize(635, 785);

	ImGui::SetNextWindowPos(imgSize, ImGuiCond_Always);
	ImGui::SetNextWindowSize(scrollSize);
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.9f);
	ImGui::Begin("m_open_players_list", &m_open_players_list, ImGuiWindowFlags_NoDecoration);
	ImGui::PopStyleVar(1);

	campaign* camp = qa.gDataAll->campaignData;
	for (int f = 0; f < 21; f++)
	{
		if (m_current_faction_id == f || !m_player_faction[f])
			continue;


		ImGui::PushID(f);
		ImGui::NewLine();

		ImGui::TextColored(ImColor(208, 206, 92, 255), (m_faction_localized_name.getName(f)).c_str());
		ImGui::SameLine(0.0f, 0.1f);
		ImGui::Text("(" + m_faction_name[f] + ")");
		ImGui::SameLine();
		ImGui::Text(" - ");
		ImGui::SameLine();
		ImGui::TextColored(ImColor(44, 234, 86, 255), m_player_nickname[f].c_str());


		if (m_open_come_message && m_message[f][m_current_faction_id] != "")
		{
			if (!helper.change_color && helper.red_color < 255)
			{
				helper.red_color += 3;
				if (helper.red_color >= 255)
					helper.change_color = true;
			}
			else if (helper.change_color && helper.red_color > 0)
			{
				helper.red_color -= 3;
				if (helper.red_color <= 0)
					helper.change_color = false;
			}
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, helper.red_color, helper.red_color)));
			if (ImGui::Button(desTab.incomingMessage.c_str()))
			{
				if (!helper.read_message[f]) helper.read_message[f] = true;
				else                         helper.read_message[f] = false;
			}
			ImGui::PopStyleColor(2);
			if (helper.read_message[f])
			{
				const char* text = m_message[f][m_current_faction_id].c_str();
				float textY = ImGui::CalcTextSize(text).y;
				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.26f, 0.59f, 0.98f, 0.35f));
				ImGui::BeginChild(desTab.incomingMessage.c_str(), ImVec2(-FLT_MIN, textY * 1.5f));
				ImGui::PopStyleColor(1);
				ImGui::Text(text);
				ImGui::EndChild();
				if (ImGui::Button(desTab.reply.c_str()))
				{
					m_open_write_message = true;
					helper.target_f = f;
				}
			}
		}
		else if (ImGui::Button(desTab.writeMessage.c_str()))
		{
			m_open_write_message = true;
			helper.target_f = f;
		}
		drawWriteMessage(m_current_faction_id, f);


		ImGui::NewLine();
		ImGui::Separator();
		ImGui::PopID();
	}


	if (ImGui::Button(desTab.close.c_str()))
	{
		m_open_players_list = false;
	}

	ImGui::End();
}

void HOT_SEAT::drawWriteMessage(int sender, int recipient)
{
	if (!m_open_write_message || helper.target_f != recipient)
		return;

	float textY = ImGui::CalcTextSize(m_message[sender][recipient].c_str()).y;
	ImGui::BeginChild("drawWriteMessage", ImVec2(-FLT_MIN, textY * 4));

	helper_functions::disableShortcutsIsWindowFocused();

	ImGui::InputTextMultiline("##drawWriteMessage", &m_message[sender][recipient], ImVec2(-FLT_MIN, textY * 2), ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_EnterReturnsTrue);

	if (ImGui::Button(desTab.sendMessage.c_str()))
	{
		m_open_write_message = false;
		helper.target_f = -1;
	}
	ImGui::SameLine();
	if (ImGui::Button(desTab.deleteMessage.c_str()))
	{
		m_message[sender][recipient] = "";
	}
	ImGui::SameLine();
	if (ImGui::Button(desTab.close.c_str()))
	{
		m_message[sender][recipient] = "";
		m_open_write_message = false;
		helper.target_f = -1;
	}

	ImGui::EndChild();
}




























