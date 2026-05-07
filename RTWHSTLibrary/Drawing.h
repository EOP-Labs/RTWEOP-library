#ifndef DRAWING_H
#define DRAWING_H

#include "pch.h"

typedef int undefined4;

class Drawing
{
public:
	static bool bDisplay;
	static BOOL bInit;

	static HRESULT APIENTRY hkBeginScene(LPDIRECT3DDEVICE9 D3D9Device);
	static HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 D3D9Device);
	static HRESULT APIENTRY hkPresent(IDirect3DDevice9* m_pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion);

	static HRESULT __fastcall onDrawGameCursor(void* _this, int stub);

	static HRESULT __fastcall onGameDrawOnStratAndTacticMap(int param_1);
	static HRESULT __fastcall onGameDrawOnMainMenu(void* _this, int stub, char** name, undefined4 param_3, float* param_4);
	static HRESULT __fastcall onGameDrawOnLoadingScreen(void* _this, int* param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5);

	static void draw();

private:
	static ImVec2 vWindowPos;
	static ImVec2 vWindowSize;

	static void InitImGui(LPDIRECT3DDEVICE9 pDevice);
};

#endif







