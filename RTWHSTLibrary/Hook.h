// https://github.com/adamhlt/D3D9-Hook-ImGui 

#ifndef HOOK_H
#define HOOK_H

#include "pch.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
using tBeginScene = HRESULT(APIENTRY*)(LPDIRECT3DDEVICE9 pDevice);
using tEndScene = HRESULT(APIENTRY*)(LPDIRECT3DDEVICE9 pDevice);
using tReset = HRESULT(APIENTRY*)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
using tPresent = HRESULT(APIENTRY*)(IDirect3DDevice9*, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);

typedef int undefined4;
using t_onGameDrawOnStratAndTacticMap = HRESULT(__fastcall*)(int param_1);
using t_onGameDrawOnMainMenu = HRESULT(__fastcall*)(void* _this, int stub, char** name, undefined4 param_3, float* param_4);
using t_onGameDrawOnLoadingScreen = HRESULT(__fastcall*)(void* _this, int* param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5);

using tdrawGameCursor = HRESULT(__fastcall*)(void* _this, int stub);


class Hook
{
public:
	static bool isReset;

	static tdrawGameCursor drawGameCursor;

	static t_onGameDrawOnStratAndTacticMap o_onGameDrawOnStratAndTacticMap;
	static t_onGameDrawOnMainMenu o_onGameDrawOnMainMenu;
	static t_onGameDrawOnLoadingScreen o_onGameDrawOnLoadingScreen;

	static IDirect3DDevice9* pDevice;
	static tBeginScene oBeginScene;
	static tEndScene oEndScene;
	static tPresent oPresent;
	static HWND window;
	static HMODULE hDDLModule;
	static bool noDouble;

	static void HookDirectX();
	static void UnHookDirectX();
	static void HookWindow();
	static void UnHookWindow();

private:
	static int windowHeight, windowWidth;
	static void* d3d9Device[119];
	static WNDPROC OWndProc;
	static tReset oReset;


	static BOOL CALLBACK enumWind(HWND handle, LPARAM lp);
	static HWND GetProcessWindow();
	static BOOL GetD3D9Device(void** pTable, size_t size);
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static HRESULT APIENTRY hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
};

#endif
