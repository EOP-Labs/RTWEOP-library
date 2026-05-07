#include "Drawing.h"
#include "Hook.h"
#include "memory/memoryWork.h"
#include <fstream>
#include <iostream>
#include <ImFileDialog.h>
#include "Impl.h"
#include "memory/hotSeat/hotSeatCampaign.h"
#include "memory/hotSeat/createBattle.h"

BOOL   Drawing::bInit       = FALSE;    // Status of the initialization of ImGui.
bool   Drawing::bDisplay    = true;     // Status of the menu display.
ImVec2 Drawing::vWindowPos  = { 0, 0 }; // Last ImGui window position.
ImVec2 Drawing::vWindowSize = { 0, 0 }; // Last ImGui window size.


HRESULT Drawing::hkBeginScene(const LPDIRECT3DDEVICE9 D3D9Device)
{
	return Hook::oBeginScene(D3D9Device);
}

HRESULT Drawing::hkEndScene(const LPDIRECT3DDEVICE9 D3D9Device)
{
	return Hook::oEndScene(D3D9Device);
}

HRESULT __fastcall Drawing::onDrawGameCursor(void* _this, int stub)
{
	return Hook::drawGameCursor(_this, stub);
}


//////////////////////////////////////////////////////////////////////
// render на страт карте и тактике   
HRESULT __fastcall Drawing::onGameDrawOnStratAndTacticMap(int param_1)
{
	HRESULT result = Hook::o_onGameDrawOnStratAndTacticMap(param_1);

	HOT_SEAT_CAMPAIGN.m_is_strat_map_draw = true;
	draw();

	return result;
}

//////////////////////////////////////////////////////////////////////
// render в главном меню   
HRESULT __fastcall Drawing::onGameDrawOnMainMenu(void* _this, int stub, char** name, undefined4 param_3, float* param_4)
{
	HRESULT result = Hook::o_onGameDrawOnMainMenu(_this, stub, name, param_3, param_4);

	HOT_SEAT_CAMPAIGN.m_is_strat_map_draw = false;
	draw();

	return result;
}

//////////////////////////////////////////////////////////////////////
// Загрузка рендер 2   
HRESULT __fastcall Drawing::onGameDrawOnLoadingScreen(void* _this, int* param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5)
{
	HRESULT result = Hook::o_onGameDrawOnLoadingScreen(_this, param_1, param_2, param_3, param_4, param_5);

	HOT_SEAT_CAMPAIGN.m_is_strat_map_draw = false;
	draw();

	return result;
}


void Drawing::draw()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (bDisplay)
	{
		if (startSettings.gameVersion == 2)// если это Steam версия, то только битвы - временно   
		{
			battle_create::drawBattle();
		}
		else
		{
			draw_main();
		}
	}

	// Render toasts on top of everything, at the end of your code!
	// You should push style vars here
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.9f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f));
	ImGui::RenderNotifications();
	ImGui::PopStyleVar(2); // Don't forget to Pop()
	ImGui::PopStyleColor(1);

	ImGuiIO& io = ImGui::GetIO();
	gameWindow.mouseAtImgui = io.WantCaptureMouse;
	gameWindow.mouseAtImgui |= io.WantCaptureKeyboard;

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	if (gameWindow.texturesForDeleting.size())
	{
		for (auto tex : gameWindow.texturesForDeleting)
		{
			tex->Release();
		}
		gameWindow.texturesForDeleting.clear();
	}
}

HRESULT Drawing::hkPresent(IDirect3DDevice9* D3D9Device, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
	if (!Hook::pDevice)
	{
		Hook::pDevice = D3D9Device;
	}


	if (!bInit)
	{
		gameWindow.pDevice = D3D9Device;

		InitImGui(D3D9Device);

		ifd::FileDialog::Instance().CreateTexture = [](uint8_t* data, int w, int h, char fmt) -> void* {
			IDirect3DTexture9* texture = NULL;

			// Create empty IDirect3DTexture9*
			if (fmt)
			{
				gameWindow.pDevice->CreateTexture(w, h, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture, 0);
			}
			else
			{
				gameWindow.pDevice->CreateTexture(w, h, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture, 0);

			}
			if (!texture)
			{
				throw std::runtime_error("CreateTexture failed");
			}

			D3DLOCKED_RECT rect;
			texture->LockRect(0, &rect, 0, D3DLOCK_DISCARD);
			unsigned char* dest = static_cast<unsigned char*>(rect.pBits);
			memcpy(dest, &data[0], sizeof(unsigned char) * w * h * 4);
			texture->UnlockRect(0);

			return (void*)texture;
			};

		ifd::FileDialog::Instance().DeleteTexture = [](void* tex)
			{
				gameWindow.texturesForDeleting.push_back((IDirect3DTexture9*)tex);
			};
	}
	else if (bInit && startSettings.gameVersion == 2)// если это Steam версия - временно   
	{
		draw();
	}




	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		bDisplay = !bDisplay;
	}

	if (GetAsyncKeyState(VK_END) & 1)
	{
		Hook::UnHookDirectX();
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, Hook::hDDLModule, 0, nullptr);
		return Hook::oPresent(D3D9Device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	}

//	if (isTest)
//	{
//		return Hook::oPresent(D3D9Device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
//	}
//	draw();

	return Hook::oPresent(D3D9Device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}


static void SetStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImVec4* colors = style.Colors;

	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(ImColor(47, 47, 47));
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(ImColor(208, 206, 92));
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(ImColor(89, 40, 40));
	colors[ImGuiCol_TitleBgActive] = ImVec4(ImColor(144, 7, 7));
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.56f, 0.03f, 0.03f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(ImColor(144, 7, 7));
	colors[ImGuiCol_ButtonActive] = ImVec4(ImColor(255, 7, 7));
	colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab] = ImLerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.80f);
	colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
	colors[ImGuiCol_TabActive] = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
	colors[ImGuiCol_TabUnfocused] = ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
	colors[ImGuiCol_TabUnfocusedActive] = ImLerp(colors[ImGuiCol_TabActive], colors[ImGuiCol_TitleBg], 0.40f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);   // Prefer using Alpha=1.0 here
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);   // Prefer using Alpha=1.0 here
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

/**
    @brief : function that init ImGui for rendering.
    @param pDevice : Current Direct3D9 Device Object given by the hooked function.
**/
void Drawing::InitImGui(const LPDIRECT3DDEVICE9 pDevice)
{
	D3DDEVICE_CREATION_PARAMETERS CP;
	pDevice->GetCreationParameters(&CP);
	Hook::window = CP.hFocusWindow;
	Hook::HookWindow();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.IniFilename = nullptr;
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	io.ConfigFlags &= ~ImGuiConfigFlags_NavEnableKeyboard;
	io.MouseDrawCursor = false;
//	io.DisplaySize = ImVec2((float)(gameWindow.rect.right - gameWindow.rect.left), (float)(gameWindow.rect.bottom - gameWindow.rect.top));
//	io.DisplaySize = ImVec2(1024.0f, 768.0f);
	

	ImFontConfig font_config;
	font_config.OversampleH = 1;
	font_config.OversampleV = 1;
	font_config.SizePixels = 12.f;
	font_config.PixelSnapH = 1;
	font_config.FontDataOwnedByAtlas = false;

	//	ImFont* newFont = io.Fonts->AddFontFromFileTTF(u8"C:\\Windows\\Fonts\\Tahoma.ttf", 16.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
	ImFont* newFont = io.Fonts->AddFontFromFileTTF(u8"dmData\\fonts\\mainFont.ttf", 16.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
	if (newFont == nullptr)
	{
		io.Fonts->AddFontDefault(&font_config);
	}
	ImGui::MergeIconsWithLatestFont(16.f, false);

//	ImGui::StyleColorsDark();
	SetStyle();
	ImGui_ImplWin32_Init(Hook::window);
	ImGui_ImplDX9_Init(pDevice);

	bInit = TRUE;
	new_events::onInit(bInit);
}










