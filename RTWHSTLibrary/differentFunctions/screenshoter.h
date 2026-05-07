#pragma once
#include <d3d9.h>
#include <vector>

struct rectW
{
	WNDPROC m_pWindowProc;
	IDirect3DDevice9* pDevice;
	HWND hwnd;
	RECT rect;
	std::vector<IDirect3DTexture9*>texturesForDeleting;
	uint32_t RomeTW_ALX_exe;

	bool bShowWindow      = false;
	bool mouseAtImgui     = false;
	bool isLeftAlt        = false;
	bool controlsDisabled = false;
	bool isDraw           = false;
	bool isKeymaster      = false;
	bool mapView          = false;
};
extern rectW gameWindow;

rectW getWindowRect();
void createScreenshots();





