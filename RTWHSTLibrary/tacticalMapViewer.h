#pragma once

#include "memory/helper_functions.h"
#include <textures.h>

struct tacticalMapViewer
{
	bool is_mapView = false;
	bool is_mapView_open = false;
	coords xy;
	settlementStruct* sett = nullptr;
	ImVec2 imgSize = { 0, 0 };
	PDIRECT3DTEXTURE9 texture = NULL;
	int image_width = 0;
	int image_height = 0;
	ImVec2 pos = { 0, 0 };
	void tacticalMapViewerDraw();
	void onTransitionToBattleFromStratMap();
};
extern tacticalMapViewer mapView;




















