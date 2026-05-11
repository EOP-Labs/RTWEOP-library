///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <imgui.h>
#include "backends/imgui_impl_dx9.h"
#include "backends/imgui_impl_win32.h"
#include <d3d9.h>
#include <tchar.h>
#include <imgui_internal.h>
#include "mainMenu.h"
#include <memoryWork.h>
#include <windows.h>
#include <mmsystem.h>//sndPlaySound
#include <textures.h>
#include <dm_assert.h>

#if defined(_MSC_VER)
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "shlwapi.lib")
#endif 

#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include <dwmapi.h>
#include <regex>
using json = nlohmann::json;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int                             STARTER::m_game_version;
uint32_t                        STARTER::m_sum;

BOOL                            STARTER::m_success;
bool                            STARTER::m_is_start;
bool                            STARTER::m_is_game_ranger;
wchar_t*                        STARTER::m_cmd;
bool                            STARTER::m_debug_exe;
bool                            STARTER::m_debug_dll;
int                             STARTER::m_input_ancillary;
std::string                     STARTER::m_hot_seat_tool_exe;

std::string                     STARTER::m_full_path;
const char*                     STARTER::m_target_exe;
const char*                     STARTER::m_target_steam_exe;
wchar_t*                        STARTER::m_w_target_exe;
DWORD                           STARTER::m_process_ID;
const char*                     STARTER::m_dll_path;

launchSettings                  startSettings;

static LPDIRECT3D9              g_pD3D = nullptr;
static LPDIRECT3DDEVICE9        g_pd3dDevice = nullptr;
static bool                     g_DeviceLost = false;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

static PDIRECT3DTEXTURE9        myCursor = NULL;
static int                      myCursor_width = 0;
static int                      myCursor_height = 0;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
string STARTER::getFullPath()
{
    WCHAR path[MAX_PATH];
    GetModuleFileNameW(NULL, path, MAX_PATH);
//  wstring ws(path);
//  string fullPath(ws.begin(), ws.end());   //C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.40.33807\include\xutility(4672,18): warning C4244: =: преобразование "wchar_t" в "char", возможна потеря данных   
    string fullPath = wcharToString(path);
    fullPath = regex_replace(fullPath, regex(STARTER::m_hot_seat_tool_exe), "");
    return fullPath;
}

void STARTER::callDllFunction()
{
    string fullPath = getFullPath();

    const char* dllPath = "RTWHSTLibrary.dll";
    HMODULE hmtw = LoadLibraryA((fullPath + dllPath).c_str());
    if (hmtw != 0)
    {
        DWORD callDllAdd = (DWORD)GetProcAddress(hmtw, "callDll");

        typedef bool __cdecl func(string, launchSettings, LOG_LEVEL, descriptionTab);
        func* callDll = (func*)callDllAdd;
        bool result = callDll(fullPath, startSettings, LOG.m_current_level, desTab);
        LOG_ASSERT(result, "callDllFunction()");
    }

}

static bool playOurSound()
{
    if (!startSettings.playMusic) return false;

    LOG_ALWAYS(RELEASE, "playOurSound");
    char puth[] = "dmData\\sounds\\CampaignBattle1-Time_2_Kill.wav";
    PlaySoundA(puth, NULL, SND_FILENAME | SND_ASYNC);
    mciSendStringA(puth, NULL, 0, NULL);

    return true;
}

static bool stopPlayOurSound()
{
    PlaySoundA(nullptr, nullptr, 0);
    return true;
}

static void setLanguage()
{
    json data = NULL;
    if (startSettings.language == "RU")
    {
        ifstream f("dmData/configs/languageRU.json");
        data = json::parse(f);
        f.close();
    }
    else
    {
        ifstream f("dmData/configs/languageENG.json");
        data = json::parse(f);
        f.close();
    }

    LOG_ASSERT(data!=NULL, "Failed to install language.");

    data.at("cfg"              ).get_to(desTab.cfg);
    data.at("dll"              ).get_to(desTab.dll);
    data.at("game"             ).get_to(desTab.game);
    data.at("process"          ).get_to(desTab.process);
    data.at("memory"           ).get_to(desTab.memory);
    data.at("rome_jpeg"        ).get_to(desTab.rome_jpeg);
    data.at("cursor_tga"       ).get_to(desTab.cursor_tga);
    data.at("with_dll"         ).get_to(desTab.with_dll);
    data.at("without_dll"      ).get_to(desTab.without_dll);
    data.at("close"            ).get_to(desTab.close);
    data.at("play_music"       ).get_to(desTab.play_music);
    data.at("language"         ).get_to(desTab.language);
    data.at("hotSeat"          ).get_to(desTab.hotSeat);
    data.at("hideLauncher"     ).get_to(desTab.hideLauncher);
    data.at("hideLauncTooltip" ).get_to(desTab.hideLauncTooltip);
    data.at("ancillaryLimit"   ).get_to(desTab.ancillaryLimit);
    data.at("ancLimitTooltip"  ).get_to(desTab.ancLimitTooltip);
    data.at("logLevel"         ).get_to(desTab.logLevel);

    LOG_ALWAYS(RELEASE, "setLanguage()");
}

static wchar_t* StrToWstr2(const std::string& aString)
{
    // чтобы не делать каждый раз new создадим некоторый буфер заранее
    const int maxSize = 1024 * 1024; // 1Мб символов
    static wchar_t buff[maxSize];

    int nSize = ::MultiByteToWideChar(CP_UTF8, 0, aString.c_str(), static_cast<int>(aString.length() + 1), NULL, NULL);

    wchar_t* tBuff = buff;
    if (nSize > maxSize)
    {
        // пытаемся выделить память только если не хватило
        tBuff = new wchar_t[nSize];
    }
    if (nSize <= 0 && tBuff == NULL)
        return L"";

    ::MultiByteToWideChar(CP_UTF8, 0, aString.c_str(), static_cast<int>(aString.length() + 1), buff, nSize);

    wchar_t* result(tBuff);

    if (tBuff != buff)
        delete[] tBuff;

    return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace ImGui {

    bool BufferingBar(const char* label, float value, const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col) {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);

        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size = size_arg;
        size.x -= style.FramePadding.x * 2;

        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        ItemSize(bb, style.FramePadding.y);
        if (!ItemAdd(bb, id))
            return false;

        // Render
        const float circleStart = size.x * 0.7f;
        const float circleEnd = size.x;
        const float circleWidth = circleEnd - circleStart;

        window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart, bb.Max.y), bg_col);
        window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart * value, bb.Max.y), fg_col);

        const float t = (float)g.Time;
        const float r = size.y / 2;
        const float speed = 1.5f;

        const float a = speed * 0;
        const float b = speed * 0.333f;
        const float c = speed * 0.666f;

        const float o1 = (circleWidth + r) * (t + a - speed * (int)((t + a) / speed)) / speed;
        const float o2 = (circleWidth + r) * (t + b - speed * (int)((t + b) / speed)) / speed;
        const float o3 = (circleWidth + r) * (t + c - speed * (int)((t + c) / speed)) / speed;

        window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o1, bb.Min.y + r), r, bg_col);
        window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o2, bb.Min.y + r), r, bg_col);
        window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o3, bb.Min.y + r), r, bg_col);

        return true;
    }

    bool Spinner(const char* label, float radius, int thickness, const ImU32& color) {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);

        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size((radius) * 2, (radius + style.FramePadding.y) * 2);

        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        ItemSize(bb, style.FramePadding.y);
        if (!ItemAdd(bb, id))
            return false;

        // Render
        window->DrawList->PathClear();

        auto num_segments = 30.0;
        auto start = abs(static_cast<double>(ImSin(float(g.Time * 1.8))) * (num_segments - 5.0));

        auto a_min = IM_PI * 2.0 * start / num_segments;
        auto a_max = IM_PI * 2.0 * (num_segments - 3) / num_segments;

        const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius + style.FramePadding.y);

        for (float i = 0.0f; i < num_segments; i++) {
            auto a = a_min + (i / num_segments) * (a_max - a_min);
            window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(float(a + g.Time * 8)) * radius,
                centre.y + ImSin(float(a + g.Time * 8.0)) * radius));
        }

        window->DrawList->PathStroke(color, false, (float)thickness);

        return true;
    }

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

static void setNewCursor()
{
    ImVec2 p = ImGui::GetMousePos();
    ImGui::GetWindowDrawList()->AddImage((ImTextureID)(intptr_t)myCursor, ImVec2(p.x - 5.0f, p.y), ImVec2(p.x + myCursor_width - 5.0f, p.y + myCursor_height));
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
    return STARTER::WinMain();
}

int STARTER::WinMain()
{
    LOG.init(DEBUG);
    init();


    ifstream file_read("dmData/configs/launchSettings.json");
    json launch_data = json::parse(file_read);
    launch_data.at("playMusic"     ).get_to(startSettings.playMusic);
    launch_data.at("language"      ).get_to(startSettings.language);
    launch_data.at("mainHotSeat"   ).get_to(startSettings.mainHotSeat);
    launch_data.at("hideLauncher"  ).get_to(startSettings.hideLauncher);
    launch_data.at("ancillaryLimit").get_to(startSettings.ancLimit);
    launch_data.at("logLevel"      ).get_to(startSettings.logLevel);
    launch_data.at("debugExe"      ).get_to(m_debug_exe);
    launch_data.at("debugDll"      ).get_to(m_debug_dll);
//  launch_data.at("gameVersion"   ).get_to(m_game_version);
    file_read.close();

    if (startSettings.ancLimit > 127)
    {
        startSettings.ancLimit = 127;
    }
    else if (startSettings.ancLimit < 1)
    {
        startSettings.ancLimit = 1;
    }

    launch_data["ancillaryLimit"] = startSettings.ancLimit;
    launch_data["gameVersion"]    = m_game_version;
    ofstream file_write("dmData/configs/launchSettings.json");
    file_write << setw(4) << launch_data;
    file_write.close();


    while (m_debug_exe && !IsDebuggerPresent())
    {
        Sleep(100);
    }


    m_input_ancillary = startSettings.ancLimit;

    ifstream config("dmData/configs/RTWHST.cfg.dm.json");
    json dataCfg = json::parse(config);
    m_cmd = StrToWstr2(dataCfg[startSettings.mainHotSeat]);
    int numOfElements = dataCfg.size();
    string* hotSeats = new string[numOfElements];
    int m = 0;
    config.close();

    if (dataCfg.is_object() || dataCfg.is_array())
    {
        for (auto& it : dataCfg.items())
        {
            auto k = it.key();
            auto v = it.value().type_name();
            LOG_ALWAYS(RELEASE, "key: " + k + ", " + v);
            hotSeats[m] = k;
            m++;
        }
    }

    setLanguage();
    LOG.setLogLevel(LOG_LEVEL(startSettings.logLevel));


    if (startSettings.hideLauncher)
    {
        injectDLL();
        return 0;
    }

    // Make process DPI aware and obtain main monitor scale
    ImGui_ImplWin32_EnableDpiAwareness();
    float main_scale = ImGui_ImplWin32_GetDpiScaleForMonitor(::MonitorFromPoint(POINT{ 0, 0 }, MONITOR_DEFAULTTOPRIMARY));

    // Create application window
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"RTWHotSeatTool", nullptr };
    ::RegisterClassExW(&wc);

    int xSize = (int)(700 * main_scale);
    int ySize = (int)(725 * main_scale);

 	int xPos = (GetSystemMetrics(SM_CXSCREEN) - xSize) / 2;
 	int yPos = (GetSystemMetrics(SM_CYSCREEN) - ySize) / 2;

    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"RTWHotSeatTool", WS_POPUPWINDOW, xPos, yPos, xSize, ySize, nullptr, nullptr, wc.hInstance, nullptr);
//  HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"RTWHotSeatTool", WS_OVERLAPPEDWINDOW | WS_VISIBLE, xPos, yPos, xSize, ySize, nullptr, nullptr, wc.hInstance, nullptr);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    SetStyle();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale;        // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

	ImFontConfig font_config;
	font_config.OversampleH = 1;
	font_config.OversampleV = 1;
	font_config.SizePixels = 12.f;
	font_config.PixelSnapH = 1;
	font_config.FontDataOwnedByAtlas = false;

	ImFont* newFont = io.Fonts->AddFontFromFileTTF(u8"dmData\\fonts\\mainFont.ttf", 16.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
	if (newFont == nullptr)
	{
		io.Fonts->AddFontDefault(&font_config);
	}


    bool isMainMenu = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ShowCursor(false);
    int my_image_width = 0;
    int my_image_height = 0;
    PDIRECT3DTEXTURE9 my_texture = NULL;
    LOG_ASSERT(LoadTextureFromFile(g_pd3dDevice, "dmData/images/rome.jpeg", &my_texture, &my_image_width, &my_image_height), desTab.rome_jpeg);
    LOG_ASSERT(LoadTextureFromFile(g_pd3dDevice, "dmData/cursor/cursor.tga", &myCursor, &myCursor_width, &myCursor_height), desTab.cursor_tga);
    playOurSound();


    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Handle lost D3D9 device
        if (g_DeviceLost)
        {
            HRESULT hr = g_pd3dDevice->TestCooperativeLevel();
            if (hr == D3DERR_DEVICELOST)
            {
                ::Sleep(10);
                continue;
            }
            if (hr == D3DERR_DEVICENOTRESET)
                ResetDevice();
            g_DeviceLost = false;
        }

        // Handle window resize (we don't resize directly in the WM_SIZE handler)
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            g_d3dpp.BackBufferWidth = g_ResizeWidth;
            g_d3dpp.BackBufferHeight = g_ResizeHeight;
            g_ResizeWidth = g_ResizeHeight = 0;
            ResetDevice();
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();



        /*=============================================================================*/
    //  ImGui::SetNextWindowPos(ImVec2(-0.5f, -0.5f), ImGuiCond_Always);
        ImGui::SetNextWindowPos(ImVec2(-1.0f, -1.0f), ImGuiCond_None);
        ImGui::SetNextWindowSize(ImVec2((float)xSize, (float)ySize));
        ImGui::Begin("RTWHotSeatTool",&isMainMenu, ImGuiWindowFlags_NoDecoration);

        ImGui::Image((ImTextureID)(intptr_t)my_texture, ImVec2(685, 500));

        ImGui::NewLine();
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(208, 206, 92)));
        TextCentered("RTWHotSeatTool");
        ImGui::PopStyleColor(1);
        ImGui::NewLine();


        std::string text = desTab.with_dll;
        const ImVec2 label_size = ImGui::CalcTextSize(text.c_str(), NULL, true);
        if (!m_is_start && ImGui::Button(text.c_str(), ImVec2(-1.0f, (label_size.y + style.FramePadding.y * 2.0f) * 2)))
        {
            stopPlayOurSound();
            if (!m_is_game_ranger)
            {
                ::DestroyWindow(hwnd);
                injectDLL();
            }
            else
            {
                m_is_start = true;
                if (m_game_version == 2)               // Если это стим версия игры, то нам нужен другой ехе   
                {
                    m_target_exe = m_target_steam_exe; // Ну а че? А вдруг кто-то будет играть стим версию через GameRanger?!   
                }
            }
        }
        

        text = desTab.without_dll;
        const ImVec2 label_size2 = ImGui::CalcTextSize(text.c_str(), NULL, true);
        if (!m_is_start && ImGui::Button(text.c_str(), ImVec2(-1.0f, (label_size2.y + style.FramePadding.y * 2.0f) * 2)))
        {
            ::DestroyWindow(hwnd);
            LOG_ASSERT(startGame() == TRUE, desTab.game);
        }


        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(107, 107, 107)));
        text = u8"" + desTab.close + "   ";
        const ImVec2 label_size3 = ImGui::CalcTextSize(text.c_str(), NULL, true);
        ImGui::SetCursorPosY(667.0f);
        if (ImGui::Button(text.c_str(), ImVec2(-1.0f, (label_size3.y + style.FramePadding.y * 2.0f) * 2)))
        {
            ::DestroyWindow(hwnd);
        }
        ImGui::PopStyleColor(1);


        if(!m_is_start)
        {
            ImGui::SetCursorPos(ImVec2(10, 10));
            ImGui::BeginGroup();
            const char* preview = startSettings.mainHotSeat.c_str();
            string label = desTab.hotSeat + "(" + startSettings.mainHotSeat + ")";
            if (ImGui::BeginCombo(label.c_str(), preview, ImGuiComboFlags_NoPreview))
            {
                for (int i = 0; i < numOfElements; i++)
                {
                    if (ImGui::Selectable(hotSeats[i].c_str(), i == 2))
                    {
                        LOG_ALWAYS(RELEASE, "Selectable: " + to_string(i) + ", " + hotSeats[i]);

                        ifstream f("dmData/configs/launchSettings.json");
                        json data = json::parse(f);
                        data.at("mainHotSeat").get_to(startSettings.mainHotSeat);
                        preview = hotSeats[i].c_str();
                        startSettings.mainHotSeat = hotSeats[i];
                        data["mainHotSeat"] = startSettings.mainHotSeat;
                        f.close();

                        ofstream f1("dmData/configs/launchSettings.json");
                        f1 << setw(4) << data;
                        f1.close();

                        ifstream cf("dmData/configs/RTWHST.cfg.dm.json");
                        json dCfg = json::parse(cf);
                        m_cmd = StrToWstr2(dCfg[startSettings.mainHotSeat]);
                        cf.close();
                    }
                }
                ImGui::EndCombo();
            }

            if (ImGui::Checkbox(u8"GameRanger", &m_is_game_ranger))
            {
                if (m_is_game_ranger)
                {
                    LOG_ALWAYS(RELEASE, "isGameRanger true");
                }
                else
                {
                    LOG_ALWAYS(RELEASE, "isGameRanger false");
                }
            }
            ImGui::PushItemWidth(110.F);
            ImGui::InputInt("##0", &m_input_ancillary, 1);
            if (m_input_ancillary > 127)
            {
                m_input_ancillary = 127;
            }
            else if (m_input_ancillary < 1)
            {
                m_input_ancillary = 1;
            }
            ImGui::PopItemWidth();
            ImGui::SameLine();

            ImVec2 loolSixe = ImGui::CalcTextSize((desTab.ancLimitTooltip.c_str()));
            beginOurTooltip(loolSixe, desTab.ancLimitTooltip.c_str());
            if (ImGui::Button(desTab.ancillaryLimit.c_str()))
            {
                startSettings.ancLimit = static_cast<uint8_t>(m_input_ancillary);

                LOG_ALWAYS(DEBUG, "ancLimit: " + to_string(startSettings.ancLimit) + " = " + to_string(m_input_ancillary));

                ifstream f("dmData/configs/launchSettings.json");
                json data = json::parse(f);
                f.close();

                data["ancillaryLimit"] = m_input_ancillary;

                ofstream f1("dmData/configs/launchSettings.json");
                f1 << setw(4) << data;
                f1.close();
            }

            preview = LOG.m_log_level_str[startSettings.logLevel].c_str();
            label = desTab.logLevel + "(" + LOG.m_log_level_str[startSettings.logLevel] + ")";
            if (ImGui::BeginCombo(label.c_str(), preview, ImGuiComboFlags_NoPreview))
            {
                for (int i = 0; i < 5; i++)
                {
                    if (ImGui::Selectable(LOG.m_log_level_str[i].c_str(), i == 5))
                    {
                        LOG_ALWAYS(RELEASE, "Selectable: " + to_string(i) + ", " + LOG.m_log_level_str[i]);

                        LOG.setLogLevel(LOG_LEVEL(i));

                        ifstream f("dmData/configs/launchSettings.json");
                        json data = json::parse(f);
                        data.at("logLevel").get_to(startSettings.logLevel);
                        preview = LOG.m_log_level_str[i].c_str();
                        startSettings.logLevel = i;
                        data["logLevel"] = startSettings.logLevel;
                        f.close();

                        ofstream f1("dmData/configs/launchSettings.json");
                        f1 << setw(4) << data;
                        f1.close();
                    }
                }
                ImGui::EndCombo();
            }
            ImGui::EndGroup();



            ImGui::SetCursorPos(ImVec2(500, 10));
            ImGui::BeginGroup();
            preview = startSettings.language.c_str();
            label = desTab.language + "(" + startSettings.language + ")";
            if (ImGui::BeginCombo(label.c_str(), preview, ImGuiComboFlags_NoPreview))
            {
                const char* l[2] = { "RU", "ENG" };
                for (int i = 0; i < 2; i++)
                {
                    if (ImGui::Selectable(l[i], i == 2))
                    {
                        LOG_ALWAYS(RELEASE, "Selectable: " + to_string(i) + ", " + l[i]);

                        ifstream f("dmData/configs/launchSettings.json");
                        json data = json::parse(f);
                        //  data.at("playMusic").get_to(startSettings.playMusic);
                        data.at("language").get_to(startSettings.language);
                        preview = l[i];
                        startSettings.language = preview;
                        data["language"] = startSettings.language;
                        f.close();

                        ofstream f1("dmData/configs/launchSettings.json");
                        f1 << setw(4) << data;
                        f1.close();

                        setLanguage();
                    }
                }
                ImGui::EndCombo();
            }

            if (ImGui::Checkbox(desTab.play_music.c_str(), &startSettings.playMusic))
            {
                ifstream f("dmData/configs/launchSettings.json");
                json data = json::parse(f);
                data.at("playMusic").get_to(startSettings.playMusic);
                f.close();

                if (startSettings.playMusic)
                {
                    LOG_ALWAYS(RELEASE, "Checkbox Play music false");
                    startSettings.playMusic = false;
                    data["playMusic"] = false;
                    stopPlayOurSound();
                }
                else
                {
                    LOG_ALWAYS(RELEASE, "Checkbox Play music true");
                    startSettings.playMusic = true;
                    data["playMusic"] = true;
                    playOurSound();
                }

                ofstream f1("dmData/configs/launchSettings.json");
                f1 << setw(4) << data;
                f1.close();
            }

            beginOurTooltip(ImVec2(150.F, 25.F), desTab.hideLauncTooltip.c_str());
            if (ImGui::Checkbox(desTab.hideLauncher.c_str(), &startSettings.hideLauncher))
            {
                ifstream f("dmData/configs/launchSettings.json");
                json data = json::parse(f);
                f.close();

                data["hideLauncher"] = startSettings.hideLauncher;

                ofstream f1("dmData/configs/launchSettings.json");
                f1 << setw(4) << data;
                f1.close();
            }

        #ifdef _DEBUG
            if (ImGui::Button("TEST"))
            {
            //  testModule();
                callDllFunction();
            }
            if (ImGui::Button("ASSERT"))
            {
                ImU32 ptr = NULL;
                LOG_ASSERT(ptr != NULL, "TEST");
            }
        #endif // _DEBUG

            ImGui::EndGroup();


        }
        else
        {
            const ImU32 col = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
            const ImU32 bg = ImGui::GetColorU32(ImGuiCol_Border);

            ImGui::SetCursorPos({ 135, 20 });
            ImGui::Spinner("##spinner", 220, 11, bg);
            ImGui::SetCursorPos({ 135, 20 });
            ImGui::Spinner("##spinner2", 220, 7, col);
        //  ImGui::BufferingBar("##buffer_bar", 0.7f, ImVec2(400, 6), bg, col);

            if (checkProcessID())
            {
                ::DestroyWindow(hwnd);
                injectDLL();
            }
        }


        setNewCursor();
        ImGui::End();
        /*=============================================================================*/



        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x*clear_color.w*255.0f), (int)(clear_color.y*clear_color.w*255.0f), (int)(clear_color.z*clear_color.w*255.0f), (int)(clear_color.w*255.0f));
        g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
        if (result == D3DERR_DEVICELOST)
            g_DeviceLost = true;
    }

    my_texture->Release();
    myCursor->Release();

    // Cleanup
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);


    LOG_ALWAYS(RELEASE, "RTWHotSeatTool.exe - completed");
    LOG.close();

    return 0;
}

// Helper functions
bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;                      // Need to use an explicit format with alpha if needing per-pixel alpha composition.
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;         // Present with vsync
//  g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = nullptr; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//  перетаскивание сверху окна 
POINTS m_Pos;
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_LBUTTONDOWN:
    {
        m_Pos = MAKEPOINTS(lParam);
        return 0;
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
            if (m_Pos.x >= 0 && m_Pos.x <= 700 &&           // 700 - ширина окна 
                m_Pos.y >= 0 && m_Pos.y <= 725              /* или ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 4.0f*/) // насколько высокой будет рамка за которую можно потянуть окно
                SetWindowPos(hWnd, NULL, rect.left, rect.top, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER);
        }
        return 0;
    }
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }

    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////










