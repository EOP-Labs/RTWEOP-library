#ifndef DRAWING_H
#define DRAWING_H
#define TEST_STEAM_DRAW

#include "pch.h"

typedef int undefined4;

class Drawing
{
public:
	static bool bDisplay;
	static BOOL bInit;

	static void hook();
	static void unHook();

	static HRESULT APIENTRY hkBeginScene(LPDIRECT3DDEVICE9 D3D9Device);
	static HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 D3D9Device);
	static HRESULT APIENTRY hkPresent(IDirect3DDevice9* m_pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);

	static HRESULT __fastcall onDrawGameCursor(void* _this, int stub);

	using t_onDrawGameCursorOnStratAndTacticMap = void(__fastcall*)(int param_1);
	using t_onGameDrawOnMainMenu = HRESULT(__fastcall*)(void* _this, int stub, char** name, undefined4 param_3, float* param_4);
	using t_onGameDrawOnLoadingScreen = HRESULT(__fastcall*)(void* _this, int* param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5);
	using t_onGameDrawOnMainMenuNew = void(__fastcall*)(int param_1);
	using t_onGameDrawOnStratAndTacticMap = void(__cdecl*)(int param_1);

	static t_onDrawGameCursorOnStratAndTacticMap o_onDrawGameCursorOnStratAndTacticMap;
	static t_onGameDrawOnMainMenu o_onGameDrawOnMainMenu;
	static t_onGameDrawOnLoadingScreen o_onGameDrawOnLoadingScreen;
	static t_onGameDrawOnStratAndTacticMap o_onGameDrawOnStratAndTacticMap;
	static t_onGameDrawOnMainMenuNew o_onGameDrawOnMainMenuNew;

	static void __fastcall onDrawGameCursorOnStratAndTacticMap(int param_1);
	static int __fastcall onGameDrawOnMainMenu(void* _this, int stub, char** name, undefined4 param_3, float* param_4);
	static void __fastcall onGameDrawOnLoadingScreen(void* _this, int* param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5);
	static void __cdecl onGameDrawOnStratAndTacticMap(int param_1);
	static void __fastcall onGameDrawOnMainMenuNew(int param_1);

	static void draw();

private:
	static ImVec2 vWindowPos;
	static ImVec2 vWindowSize;
	static bool isStartDraw;

	static void InitImGui(LPDIRECT3DDEVICE9 pDevice);
};

#endif







