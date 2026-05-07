#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
#include "screenshoter.h"
#include "stringThings.h"
#include <imgui.h>
#include <imgui_notify.h>
#include "../memory/memoryWork.h"
#include "dm_assert.h"
#include <textures.h>
using namespace std;
//using namespace Gdiplus;

rectW gameWindow;

static struct screenshoter
{
	HWND m_hwnd                 = gameWindow.hwnd;
	RECT m_rect                 = gameWindow.rect;

	int m_scr_width             = 0;
	int m_scr_height            = 0;

	ImVec2 m_start_pos          = ImVec2(0, 0);
	ImVec2 m_end_pos            = ImVec2(0, 0);
	bool m_isAreaScreenshot     = false;
	bool m_testArea             = false;
	PDIRECT3DTEXTURE9 m_texture = NULL;
	int m_image_width           = 0;
	int m_image_height          = 0;
	string m_temp               = "dmData\\temp\\temp_screenshot.png";

    void createScreenshots();
}screenshot;

rectW getWindowRect()
{
    if (!gameWindow.hwnd)
    {
        LOG_ALWAYS(RELEASE, "get gameWindow.hwnd");
        gameWindow.hwnd = FindWindowA(NULL, "Rome: Total War - Alexander");
    }
    GetWindowRect(gameWindow.hwnd, &gameWindow.rect);
    screenshot.m_scr_width  = gameWindow.rect.right  - gameWindow.rect.left;
    screenshot.m_scr_height = gameWindow.rect.bottom - gameWindow.rect.top;
    screenshot.m_hwnd = gameWindow.hwnd;
    screenshot.m_rect = gameWindow.rect;
    LOG_ALWAYS(RELEASE, "rect: " + to_string(gameWindow.rect.right) + " x " + to_string(gameWindow.rect.bottom));
    return gameWindow;
}

static void captureScreenshot(int scr_width, int scr_height, int scr_X, int scr_Y, const wchar_t* screenshotName, HWND hwnd)
{
	scr_width -= scr_X;
	scr_height -= scr_Y;
//	HDC hdc = GetDC(NULL); //Все мониторы, основной - GetDC(GetDesktopWindow()) 
	HDC hdc = GetDC(hwnd);
	HDC hdcMem = CreateCompatibleDC(hdc); //Создание памяти контекста устройства 

	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, scr_width, scr_height);
	SelectObject(hdcMem, hBitmap);
	BitBlt(hdcMem, 0, 0, scr_width, scr_height, hdc, scr_X, scr_Y, SRCCOPY);

	//Для PNG требуется подключить <gdiplus.h> и -lgdiplus -lole32 в аргументах линковщика 
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL); //-lgdiplus 
	Gdiplus::Bitmap image(hBitmap, NULL);
	Gdiplus::Bitmap* newImage = new Gdiplus::Bitmap(image.GetWidth(), image.GetHeight()); //можно менять размер 
	Gdiplus::Graphics graphics(newImage);
	graphics.DrawImage(&image, 0, 0, newImage->GetWidth(), newImage->GetHeight());
	CLSID pngClsid;
	CLSIDFromString(L"{557CF406-1A04-11D3-9A73-0000F81EF32E}", &pngClsid); //-lole32 
	//557CF400-bmp, 557CF401-jpg 557CF402-gif 557CF405-tif 557CF406-png 
	image.Save(screenshotName, &pngClsid, NULL);
	delete newImage;
//	Gdiplus::GdiplusShutdown(gdiplusToken);


//	//Получение массива пикселей и сохранение как BMP 
//	BITMAPINFOHEADER bmi;
//	bmi.biSize = sizeof(BITMAPINFOHEADER);
//	bmi.biWidth = scr_width;
//	bmi.biHeight = -scr_height; //сверху вниз 
//	bmi.biPlanes = 1;
//	bmi.biBitCount = 24;
//	bmi.biCompression = BI_RGB;
//	bmi.biSizeImage = scr_width * scr_height;
//	bmi.biXPelsPerMeter = 0;
//	bmi.biYPelsPerMeter = 0;
//	bmi.biClrUsed = 0;
//	bmi.biClrImportant = 0;
//	BYTE* ScreenData = new BYTE[3 * scr_width * scr_height];
//	GetDIBits(hdc, hBitmap, 0, scr_height, ScreenData, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);
//	//Пиксели можно выдернуть: ScreenData[3 * ((y * scr_width) + x)] + 0 B + 1G + 2 R 
//	HANDLE hFile = CreateFileA("ScreenShotBMP.bmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//	DWORD dwSizeofDIB = bmi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
//	BITMAPFILEHEADER bmfHeader;
//	bmfHeader.bfType = 0x4D42;
//	bmfHeader.bfSize = dwSizeofDIB;
//	bmfHeader.bfReserved1 = 0;
//	bmfHeader.bfReserved2 = 0;
//	bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);
//	DWORD dwBytesWritten = 0;
//	WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
//	WriteFile(hFile, (LPSTR)&bmi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
//	WriteFile(hFile, (LPSTR)ScreenData, bmi.biSizeImage, &dwBytesWritten, NULL);
//	CloseHandle(hFile);
//	delete ScreenData;

	//Освобождение ресурсов 
	DeleteObject(hBitmap);
	DeleteDC(hdcMem);
	ReleaseDC(NULL, hdc);
}

static void createScreenshot(const char* screenName)
{
	const wchar_t* screenshotName = GetWC(screenName);
	int scr_X = 0; //сдвиг по X 
	int scr_Y = 0; //сдвиг по Y 
//	int scr_width  = GetSystemMetrics(SM_CXSCREEN); //ширина экрана 
//	int scr_height = GetSystemMetrics(SM_CYSCREEN); //высота экрана 

	captureScreenshot(screenshot.m_scr_width, screenshot.m_scr_height, scr_X, scr_Y, screenshotName, screenshot.m_hwnd);
}

static void createScreenshotArea(const char* screenName, int scr_width, int scr_height, int scr_X, int scr_Y)
{
	const wchar_t* screenshotName = GetWC(screenName);
	captureScreenshot(scr_width, scr_height, scr_X, scr_Y, screenshotName, gameWindow.hwnd);
}

void screenshoter::createScreenshots()
{
    if (!m_isAreaScreenshot && (GetKeyState(VK_F12) & 0x8000) && (GetKeyState(VK_LSHIFT) & 0x8000) && (GetKeyState(VK_LCONTROL) & 0x8000) && (GetKeyState(VK_LMENU) & 0x8000))     // ctrl shift alt F12  
    {
        m_isAreaScreenshot = true;
        m_testArea         = true;
        m_texture          = NULL;

        createScreenshot(m_temp.c_str());
        if (fileExists(m_temp))
        {
            LOG_ALWAYS(RELEASE, "createScreenshots(load: " + m_temp + ")");
            LOAD_TEXTURE(m_temp.c_str(), &m_texture, &m_image_width, &m_image_height);
            m_image_width  = m_rect.right  - 100;
            m_image_height = m_rect.bottom - 100;
        }
        remove(m_temp.c_str());
    }
    else if (!m_isAreaScreenshot && (GetKeyState(VK_F12) & 0x8000) && (GetKeyState(VK_LSHIFT) & 0x8000) && (GetKeyState(VK_LCONTROL) & 0x8000))     // ctrl shift F12  
    {
        m_isAreaScreenshot = true;
        m_texture          = NULL;
    }
    else if (!m_isAreaScreenshot && (GetKeyState(VK_F12) & 0x8000) && (GetKeyState(VK_LCONTROL) & 0x8000))                                     // ctrl F12  
    {
        string screenName = "dmData\\screenshots\\screenshot" + LOG.getTime(true) + ".png";// ".jpg";
        const char* cstr = screenName.c_str();
        ImGui::InsertNotification({ ImGuiToastType_Success, 9000, cstr });
        createScreenshot(cstr);
    }

    if (m_isAreaScreenshot)
    {
        ImGui::SetNextWindowPos({ 0, 0 }, ImGuiCond_None);
        ImGui::SetNextWindowSize(ImVec2((float)m_rect.right, (float)m_rect.bottom));
    //  ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.2f);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        ImGui::Begin("area", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus);
        ImGui::PopStyleColor(2);

        if (m_testArea && m_texture)
        {
            if (m_image_width < m_rect.right)
            {
                m_image_width += 1;
            }
            else
            {
                m_image_width = m_rect.right;
            }
            if (m_image_height < m_rect.bottom)
            {
                m_image_height += 1;
            }
            else
            {
                m_image_height = m_rect.bottom;
            }

            ImGui::SetCursorPos(ImVec2(0.F, 0.F));
        //  ImGui::GetWindowDrawList()->AddImage(texture, ImGui::GetCursorScreenPos(), ImVec2(image_width, image_height), ImVec2(0, 0), ImVec2(1, 1));
            ImGui::GetWindowDrawList()->AddImage(m_texture, ImGui::GetCursorScreenPos(), ImVec2((float)m_rect.right, (float)m_rect.bottom), ImVec2(0, 0), ImVec2(1, 1));
        }

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            m_start_pos = ImGui::GetMousePos();
        }

        ImDrawList* draw_list = ImGui::GetForegroundDrawList(); //ImGui::GetWindowDrawList();
        if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
        {
            m_end_pos = ImGui::GetMousePos();
            draw_list->AddRect(m_start_pos, m_end_pos, ImGui::GetColorU32(IM_COL32(0, 130, 216, 255)));             // Border
        //  draw_list->AddRectFilled(start_pos, end_pos, ImGui::GetColorU32(IM_COL32(0, 130, 216, 0)));         // Background
        }

        float scr_X      = m_start_pos.x;
        float scr_Y      = m_start_pos.y;
        float scr_width  = m_end_pos.x;
        float scr_height = m_end_pos.y;

        if (m_end_pos.x - m_start_pos.x < 0)
        {
            scr_X     = m_end_pos.x;
            scr_width = m_start_pos.x;
        }
        if (m_end_pos.y - m_start_pos.y < 0)
        {
            scr_Y      = m_end_pos.y;
            scr_height = m_start_pos.y;
        }

        // Background 
        draw_list->AddRectFilled(ImVec2(0, 0), ImVec2(scr_X, (float)m_rect.bottom), ImGui::GetColorU32(IM_COL32(0, 0, 0, 155)));                          // left of area 
        draw_list->AddRectFilled(ImVec2(scr_width, 0), ImVec2((float)m_rect.right, (float)m_rect.bottom), ImGui::GetColorU32(IM_COL32(0, 0, 0, 155)));      // right of area 
        draw_list->AddRectFilled(ImVec2(scr_X, 0), ImVec2(scr_width, scr_Y), ImGui::GetColorU32(IM_COL32(0, 0, 0, 155)));                               // top of area 
        draw_list->AddRectFilled(ImVec2(scr_X, scr_height), ImVec2(scr_width, (float)m_rect.bottom), ImGui::GetColorU32(IM_COL32(0, 0, 0, 155)));         // bottom of area 

        if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
        {
            string screenName = "dmData\\screenshots\\screenshot" + LOG.getTime(true) + ".png";// ".jpg";
            const char* cstr = screenName.c_str();
            ImGui::InsertNotification({ ImGuiToastType_Success, 9000, cstr });
            createScreenshotArea(cstr, static_cast<int>(round(scr_width)), static_cast<int>(round(scr_height)), static_cast<int>(round(scr_X)), static_cast<int>(round(scr_Y)));
            m_start_pos = ImVec2(0, 0);
            m_end_pos = ImVec2(0, 0);
            m_isAreaScreenshot = false;
            if (m_texture)
            {
                unloadTexture(m_texture, m_temp);
            }
        }

        ImGui::End();
    //  ImGui::PopStyleVar(1);
    }
}

void createScreenshots()
{
    screenshot.createScreenshots();
}












