#include "Hook.h"
#include "Drawing.h"
#include "Impl.h"
#include "memory/events/monitor_event.h"
#include <textures.h>

LPDIRECT3DDEVICE9 Hook::pDevice = nullptr; // Direct3D9 Device Object
tEndScene Hook::oBeginScene = nullptr; // Pointer of the original EndScene function
tEndScene Hook::oEndScene = nullptr; // Pointer of the original EndScene function
tPresent Hook::oPresent = nullptr;

tdrawGameCursor Hook::drawGameCursor = nullptr;
t_onGameDrawOnStratAndTacticMap Hook::o_onGameDrawOnStratAndTacticMap = nullptr;
t_onGameDrawOnMainMenu Hook::o_onGameDrawOnMainMenu = nullptr;
t_onGameDrawOnLoadingScreen Hook::o_onGameDrawOnLoadingScreen = nullptr;

tReset Hook::oReset = nullptr; // Pointer of the original Reset function
HWND Hook::window = nullptr; // Window of the current process
HMODULE Hook::hDDLModule = nullptr; // HMODULE of the DLL
bool Hook::noDouble = false;

int Hook::windowHeight = 0; // Height of the window
int Hook::windowWidth = 0; // Width of the window
void* Hook::d3d9Device[119]; // Array of pointer of the DirectX functions.
WNDPROC Hook::OWndProc = nullptr; // Pointer of the original window message handler.

////////////////////////////////////////////////////////

typedef BOOL(APIENTRY* oSetCursorPos)(int, int);
oSetCursorPos pSetCursorPos = NULL;

// Пока вот так вот...   
BOOL APIENTRY hkSetCursorPos(int X, int Y)
{
	if (!gameCursor)
	{
		return pSetCursorPos(X, Y);
	}


	double o = 15.0;

	if (gameWindow.rect.right == 1024 && gameWindow.rect.bottom == 768)
	{
		return pSetCursorPos(X, Y);
	}
	else if (gameWindow.rect.right == 800 && gameWindow.rect.bottom == 600)
	{
		double _y = ((Y + gameCursor->previousPosition.yCoord) * 0.5) - Y / 7.5;
		return pSetCursorPos(X, static_cast<int>(round(_y)));
	}
	else if (gameWindow.rect.right == 1152 && gameWindow.rect.bottom == 864)
	{
		o = Y / 10.0;
	}
	else if (gameWindow.rect.right == 1280 && gameWindow.rect.bottom == 768)
	{
		double _y = ((Y + gameCursor->previousPosition.yCoord) * 0.5) - Y / 10.0;
		return pSetCursorPos(X, static_cast<int>(round(_y)));
	}
	else if (gameWindow.rect.right == 1280 && gameWindow.rect.bottom == 800)
	{
		double _y = ((Y + gameCursor->previousPosition.yCoord) * 0.5) - Y / 15.0;
		return pSetCursorPos(X, static_cast<int>(round(_y)));
	}
	else if (gameWindow.rect.right == 1280 && gameWindow.rect.bottom == 960)
	{
		o = Y / 5;
	}
	else if (gameWindow.rect.right == 1360 && gameWindow.rect.bottom == 768)
	{
		double _y = ((Y + gameCursor->previousPosition.yCoord) * 0.5) - Y / 8.0;
		return pSetCursorPos(X, static_cast<int>(round(_y)));
	}
	else if (gameWindow.rect.right == 1366 && gameWindow.rect.bottom == 768)
	{
		double _y = ((Y + gameCursor->previousPosition.yCoord) * 0.5) - Y / 8.0;
		return pSetCursorPos(X, static_cast<int>(round(_y)));
	}
	else if (gameWindow.rect.right == 1440 && gameWindow.rect.bottom == 1080)
	{
		o = Y / 3.5;
	}
	else if (gameWindow.rect.right == 1600 && gameWindow.rect.bottom == 900)
	{
		double _y = ((Y + gameCursor->previousPosition.yCoord) * 0.5) - Y / 15.0;
		return pSetCursorPos(X, static_cast<int>(round(_y)));
	}
	else if (gameWindow.rect.right == 1600 && gameWindow.rect.bottom == 1024)
	{
		o = Y / 15.0;
	}
	else if (gameWindow.rect.right == 1600 && gameWindow.rect.bottom == 1200)
	{
		o = Y / 2.75;
	}
	else if (gameWindow.rect.right == 1680 && gameWindow.rect.bottom == 1050)
	{
		o = Y / 15.0;
	}
//	кажется его нет в риме1   
//	else if (gameWindow.rect.right == 1768 && gameWindow.rect.bottom == 992)
//	{
//		o = Y / 10.0;
//	}
	else if (gameWindow.rect.right == 1920 && gameWindow.rect.bottom == 1080)
	{
		double _y = ((Y + gameCursor->previousPosition.yCoord) * 0.5) - 5.0;
		return pSetCursorPos(X, static_cast<int>(round(_y)));
	}
	else if (gameWindow.rect.right == 1920 && gameWindow.rect.bottom == 1200)
	{
		o = Y / 7.0;
	}
	else if (gameWindow.rect.right == 1920 && gameWindow.rect.bottom == 1440)
	{
		return pSetCursorPos(X, gameCursor->previousPosition.yCoord * 2 - gameCursor->previousPosition.yCoord / 10);
	}
	else if (gameWindow.rect.right == 1280 && gameWindow.rect.bottom == 1440)
	{
		return pSetCursorPos(X, gameCursor->previousPosition.yCoord * 2 - gameCursor->previousPosition.yCoord / 10);
	}
	else if (gameWindow.rect.right == 1440 && gameWindow.rect.bottom == 900)
	{
		o = -5.0;
	}
	else if (gameWindow.rect.right == 1280 && gameWindow.rect.bottom == 1024)
	{
		o = Y / 3.0;
	}
	else if (gameWindow.rect.right == 2560 && gameWindow.rect.bottom == 1440)
	{
		o = Y / 10.0;
	}

	double relativelyY = (Y + gameCursor->previousPosition.yCoord + o) * 0.5;
	return pSetCursorPos(X, static_cast<int>(round(relativelyY)));
}


/**
    @brief : Function that hook the Reset and EndScene function.
**/
void Hook::HookDirectX()
{
	if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
	{
		oBeginScene = (tBeginScene)d3d9Device[41];
		oEndScene = (tEndScene)d3d9Device[42];
		oReset = (tReset)d3d9Device[16];
		oPresent = (tPresent)d3d9Device[17];


		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());


		DETOUR_ATTACH(&(PVOID&)oBeginScene, Drawing::hkBeginScene);
		DETOUR_ATTACH(&(PVOID&)oEndScene, Drawing::hkEndScene);
		DETOUR_ATTACH(&(PVOID&)oReset, hkReset);
		DETOUR_ATTACH(&(PVOID&)oPresent, Drawing::hkPresent);


		o_onGameDrawOnStratAndTacticMap = (t_onGameDrawOnStratAndTacticMap)offsets.onGameDrawOnStratAndTacticMap;
		DETOUR_ATTACH(&(PVOID&)o_onGameDrawOnStratAndTacticMap, Drawing::onGameDrawOnStratAndTacticMap);

		o_onGameDrawOnMainMenu = (t_onGameDrawOnMainMenu)offsets.onGameDrawOnMainMenu;
		DETOUR_ATTACH(&(PVOID&)o_onGameDrawOnMainMenu, Drawing::onGameDrawOnMainMenu);

		o_onGameDrawOnLoadingScreen = (t_onGameDrawOnLoadingScreen)offsets.onGameDrawOnLoadingScreen;
		DETOUR_ATTACH(&(PVOID&)o_onGameDrawOnLoadingScreen, Drawing::onGameDrawOnLoadingScreen);


		HMODULE USER32 = GetModuleHandleA("USER32.dll");
		pSetCursorPos = (oSetCursorPos)GetProcAddress(USER32, "SetCursorPos");
		DETOUR_ATTACH(&(LPVOID&)pSetCursorPos, hkSetCursorPos);

	//	drawGameCursor = (tdrawGameCursor)0x00CD76C8; // draw cursor on strat map!!! 
	//	DETOUR_ATTACH(&(PVOID&)drawGameCursor, Drawing::onDrawGameCursor);

		new_events::initNewEvents();
		monitor_event::initGameEvents();
		new_events::testGameEvents();


		DetourTransactionCommit();
	}
}

/**
    @brief : Function that unhook Reset and EnScene functions, and also disable the window message handler.
**/
void Hook::UnHookDirectX()
{
	if (Drawing::bInit)
	{
		UnHookWindow();
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	Drawing::bInit = FALSE;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());


	DETOUR_DETACH(&(PVOID&)oBeginScene, Drawing::hkBeginScene);
	DETOUR_DETACH(&(PVOID&)oEndScene, Drawing::hkEndScene);
	DETOUR_DETACH(&(PVOID&)oReset, hkReset);
	DETOUR_DETACH(&(PVOID&)oPresent, Drawing::hkPresent);

	DETOUR_DETACH(&(PVOID&)o_onGameDrawOnStratAndTacticMap, Drawing::onGameDrawOnStratAndTacticMap);
	DETOUR_DETACH(&(PVOID&)o_onGameDrawOnMainMenu, Drawing::onGameDrawOnMainMenu);
	DETOUR_DETACH(&(PVOID&)o_onGameDrawOnLoadingScreen, Drawing::onGameDrawOnLoadingScreen);

	DETOUR_DETACH(&(PVOID&)pSetCursorPos, hkSetCursorPos);
//	DETOUR_DETACH(&(PVOID&)drawGameCursor, Drawing::onDrawGameCursor);

	new_events::deInitNewEvents();
	monitor_event::deInitGameEvents();


	DetourTransactionCommit();
}

/**
    @brief : Function that enumerate windows.
**/
BOOL CALLBACK Hook::enumWind(const HWND handle, LPARAM lp)
{
	DWORD procID;
	GetWindowThreadProcessId(handle, &procID);
	if (GetCurrentProcessId() != procID)
		return TRUE;

	window = handle;
	return FALSE;
}

/**
    @brief : Function that retrieve the window of the current process.
    @retval : window of the current process.
**/
HWND Hook::GetProcessWindow()
{
	window = nullptr;

	EnumWindows(enumWind, NULL);

	RECT size;
	if (window == nullptr)
		return nullptr;

	GetWindowRect(window, &size);

	windowWidth = size.right - size.left;
	windowHeight = size.bottom - size.top;

	windowHeight -= 29;
	windowWidth -= 5;

	return window;
}

/**
    @brief : Function that get a Direct3D9 Device Object. (https://guidedhacking.com/threads/get-direct3d9-and-direct3d11-devices-dummy-device-method.11867/)
    @param  pTable : Array of functions pointer.
    @param  size   : Size of the array of pointers.
    @retval : True if the function succeed else False.
**/
bool testInit = false;
BOOL Hook::GetD3D9Device(void** pTable, const size_t size)
{
	while (testInit && IsDebuggerPresent() == false)
	{
		Sleep(100);
	}



	if (!pTable)
		return FALSE;

	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pD3D)
		return FALSE;

/*
	HMODULE hD3d9 = GetModuleHandleA("d3d9.dll");
	if (!hD3d9)
		return FALSE;

	using oDirect3DCreate9 = IDirect3D9*(WINAPI*)(UINT);
	oDirect3DCreate9 pDirect3DCreate9 = (oDirect3DCreate9)GetProcAddress(hD3d9, "Direct3DCreate9");

	IDirect3D9* pD3D = pDirect3DCreate9(D3D9b_SDK_VERSION);
	if (!pD3D)
		return FALSE;
*/


//	D3DDISPLAYMODE stDisplay;
//	if (FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &stDisplay))) 
//		return FALSE;


	IDirect3DDevice9* pDummyDevice = nullptr;

	D3DPRESENT_PARAMETERS d3dpp = {};
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GetProcessWindow();
	d3dpp.Windowed = (GetWindowLongPtr(d3dpp.hDeviceWindow, GWL_STYLE) & WS_POPUP) != 0 ? FALSE : TRUE;

//	d3dpp.BackBufferWidth = 1024;
//	d3dpp.BackBufferHeight = 768;

//	d3dpp.BackBufferFormat = stDisplay.Format;

	if (HRESULT dummyDevCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice); dummyDevCreated != S_OK)
	{
		d3dpp.Windowed = !d3dpp.Windowed;
		dummyDevCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);

		if (dummyDevCreated != S_OK)
		{
			pD3D->Release();
			return FALSE;
		}
	}

	memcpy(pTable, *(void***)(pDummyDevice), size);
	pDummyDevice->Release();
	pD3D->Release();

	gameWindow.pDevice = pDummyDevice;

	return TRUE;
}

/**
	@brief : Function that setup the WndProc callback function.
**/
void Hook::HookWindow()
{
	OWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
}

/**
    @brief : Function that disable the WndProc callback function.
**/
void Hook::UnHookWindow()
{
	SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)OWndProc);
}


POINTS m_Pos;
LRESULT WINAPI Hook::WndProc(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam) && !gameWindow.mouseAtImgui)
	{
		return CallWindowProc(gameWindow.m_pWindowProc, hWnd, msg, wParam, lParam);
	}
	// TO-DO: Stop this code from crashing
	// switch (uMsg)
	// {
	// case WM_SETFOCUS:
	// 	RECT rect;
	// 	if (!GetWindowRect(hWnd, &rect)) {
	// 		break;
	// 	}
	// 	ClipCursor(&rect);
	// 	break;
	// case WM_KILLFOCUS:
	// 	ClipCursor(NULL);
	// 	break;
	// }

//	static bool isLastAtImgui = false;
//	static HCURSOR lastGameCursor = NULL;
//	//	if (ImGui::GetIO().WantCaptureMouse)
//	if (mouseAtImgui)
//	{
//	//	HCURSOR retCur = LoadCursorFromFile(TEXT("data\\cursors\\arrow.cur"));
//	//	SetSystemCursor(retCur, 32512);
//	//	HCURSOR retCur = LoadCursorFromFile(L"dmData\\cursor\\arrow.cur");
//	//	SetCursor(retCur);
//
//		isLastAtImgui = true;
//		HCURSOR retCur = SetCursor(NULL);
//		if (retCur != NULL)
//		{
//			lastGameCursor = retCur;
//		}
//		ImGuiIO& io = ImGui::GetIO();
//		io.MouseDrawCursor = true;
//	}
//	else
//	{
//		if (lastGameCursor != NULL)
//		{
//			SetCursor(lastGameCursor);
//			lastGameCursor = NULL;
//		}
//		ImGuiIO& io = ImGui::GetIO();
//		io.MouseDrawCursor = false;
//	}
	if (gameWindow.mouseAtImgui)
	{
		switch (msg)
		{
		case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
		case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_XBUTTONUP:
		case WM_MOUSEHWHEEL:
		case WM_MOUSEWHEEL:
		case WM_CHAR:
		case WM_SETCURSOR:
	//	case WM_MOUSEMOVE:
	//	case WM_MOUSEMOVE:
	//	{
	//		SetCursorPos(gameCursor->previousPosition.xCoord, gameCursor->previousPosition.yCoord);
	//	}
		case WM_INPUTLANGCHANGE:
		case WM_KEYDOWN:
		case WM_KEYUP:

			//	case WM_SETCURSOR:
			//		// Turn off window cursor. 
			//		SetCursor(NULL);
			//		gpDevice->ShowCursor(TRUE);
			//		return TRUE; // Prevent Windows from setting cursor to window class cursor.
			//		break;

			return true;
		}

	}


	if (gameWindow.isLeftAlt)
	{
		switch (msg)
		{
	//	case WM_MOUSEWHEEL:
	//	{
	//		RECT rect;
	//		GetWindowRect(hWnd, &rect);
	//
	//		short wheel = GET_WHEEL_DELTA_WPARAM(wParam);
	//		if (wheel < 0)
	//		{
	//			rect.right -= 10;
	//			rect.bottom -= 10;
	//		}
	//		else
	//		{
	//			rect.right += 10;
	//			rect.bottom += 10;
	//		}
	//
	//		if (rect.right < 500) rect.right = 500;
	//		if (rect.bottom < 500) rect.bottom = 500;
	//		MoveWindow(hWnd, gameWindow.rect.left, gameWindow.rect.top, rect.right, rect.bottom, false);
	//
	//
	//		break;
	//	}


		case WM_LBUTTONDOWN:
		{
			m_Pos = MAKEPOINTS(lParam);
			break;
		}
		case WM_MOUSEMOVE:
		{
			if (wParam == MK_LBUTTON)
			{
				POINTS p = MAKEPOINTS(lParam);

				RECT rect;
				GetWindowRect(hWnd, &rect);

				rect.left += p.x - m_Pos.x;
				rect.top += p.y - m_Pos.y;
//				if (m_Pos.x >= 0 && m_Pos.x <= gameWindow.rect.right && m_Pos.y >= 0 && m_Pos.y <= gameWindow.rect.bottom)
//				{
					SetWindowPos(hWnd, NULL, rect.left, rect.top, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER);
				//	MoveWindow(hWnd, rect.left, rect.top, gameWindow.rect.right, gameWindow.rect.bottom, false);

					rect.right += p.x - m_Pos.x;
					rect.bottom += p.y - m_Pos.y;

					int min = 250;
					if (rect.right < min) rect.right = min;
					if (rect.bottom < min) rect.bottom = min;

					int xSize = GetSystemMetrics(SM_CXSCREEN);
					int ySize = GetSystemMetrics(SM_CYSCREEN);
					if (rect.right > xSize) rect.right = xSize;
					if (rect.bottom > ySize) rect.bottom = ySize;

					MoveWindow(hWnd, gameWindow.rect.left, gameWindow.rect.top, rect.right, rect.bottom, false);



				//	pSetCursorPos(rect.left + p.x, rect.top + p.y);

					//	SetCursorPos(m_Pos.x, m_Pos.y);

					//	gameWindow.pDevice->SetCursorPosition(m_Pos.x, m_Pos.y, 0);

					//	COORD pos = { m_Pos.x, m_Pos.y };
					//	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
					//	SetConsoleCursorPosition(output, pos);
//				}
			}
			break;
		}

		case WM_MBUTTONDOWN:
			break;
		case WM_MBUTTONUP:
			break;
		}
	}
	else
	{
		switch (msg)
		{
		case WM_MOUSEMOVE:
			break;

		case WM_MBUTTONDOWN:
			break;
		case WM_MBUTTONUP:
			break;
		}
	}


	return CallWindowProc(OWndProc, hWnd, msg, wParam, lParam);
}


bool Hook::isReset = false;
/**
    @brief : Hook of the function IDirect3DDevice9::Reset, to handle resize, etc...
	@param pDevice : Direct3D9 Device Object
    @param pPresentationParameters : parameters passed to the original function. 
    @retval : return value of the original function.
**/
HRESULT Hook::hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT tmpReset = oReset(pDevice, pPresentationParameters);
	ImGui_ImplDX9_CreateDeviceObjects();
	isReset = true;
	return tmpReset;
}
























