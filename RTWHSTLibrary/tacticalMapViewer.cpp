#include "tacticalMapViewer.h"
#include "differentFunctions/dm_assert.h"
#include "differentFunctions/screenshoter.h"
#include "memory/hotSeat/createBattle.h"

tacticalMapViewer mapView;

void tacticalMapViewer::onTransitionToBattleFromStratMap()
{
	if (!is_mapView)
		return;

	LOG_ALWAYS(DEVELOPMENT, "tacticalMapViewer::onTransitionToBattleFromStratMap()");

	is_mapView = false;
	is_mapView_open = false;
	pos = { 0, 0 };

	battleDataS* battle = helper_functions::getGameDataAll()->battleHandler;
	battle->xCoord = xy.xCoord;
	battle->yCoord = xy.yCoord;

	gameWindow.mapView = true;
}

void tacticalMapViewer::tacticalMapViewerDraw()
{
	if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Middle) && helper_functions::getGameDataAll()->battleHandler && qa.gDataAll->battleHandler->battleState == NOTHING)
	{
		if (!texture)
		{
			LOAD_TEXTURE("dmData/images/loupe.tga", &texture, &image_width, &image_height);
		}
		if (!sett)
		{
			sett = helper_functions::getGameDataAll()->campaignData->settlementList.settlements[0];
		}
		xy = coords(qa.stratPosition->x, qa.stratPosition->y);
		is_mapView_open = true;
		imgSize = getOurSize(66, 66);
		pos = ImGui::GetMousePos();
	}

	if (is_mapView_open)
	{
		if (
			(xy.xCoord != qa.stratPosition->x             || xy.yCoord != qa.stratPosition->y) &&
			(ImGui::IsMouseClicked(ImGuiMouseButton_Left) || ImGui::IsMouseClicked(ImGuiMouseButton_Right) || ImGui::IsMouseClicked(ImGuiMouseButton_Middle))
		   )
		{
			is_mapView_open = false;
		}

		ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(imgSize.x * 1.5f, imgSize.y * 1.5f));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::Begin("TacticalMapViewer", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::PopStyleColor(2);

//		ImGui::SetCursorPos(pos);
		ImGui::Image(texture, imgSize);
		ImGui::SetCursorPos(pos);
		if (beginOurTooltip(ImVec2(pos.x + 5, pos.y - 5), imgSize, string("TacticalMapViewer\nCoords: " + to_string(xy.xCoord) + ", " + to_string(xy.yCoord)).c_str()) && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
		{
			is_mapView = true;
			GAME_FUNC(void*(__thiscall*)(DWORD _this, unsigned int x, unsigned int y), offsets.transitionToMapView)(offsets.transitionToMapView2, sett->xCoord, sett->yCoord); 
		}

	//	int xyCoords[2] = { xy.xCoord, xy.yCoord };
	//	ImGui::InputInt2("Coords", xyCoords);
	//	if (ImGui::Button("Go"))
	//	{
	//		is_mapView = true;
	//		GAME_FUNC(void*(__thiscall*)(DWORD _this, unsigned int x, unsigned int y), 0x00b39fbc)(0x00188610, sett->xCoord, sett->yCoord); // 0x00b39fbc - transitionToMapView 
	//	}

		ImGui::Dummy({ 0, 0 });
		ImGui::End();
	}
}
