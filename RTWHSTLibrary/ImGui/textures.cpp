#include <textures.h>
#include "../memory/memoryWork.h"
#include "../differentFunctions/screenshoter.h"
#include "../differentFunctions/dm_assert.h"

bool LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)
{
	LOG_ALWAYS(RELEASE, "LoadTextureFromFile(" + std::string(filename) + ")");

	LPDIRECT3DDEVICE9 g_pd3dDevice = gameWindow.pDevice;

	// Load texture from disk
	PDIRECT3DTEXTURE9 texture;
	HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice, filename, &texture);
	if (hr != S_OK)
		return false;

	// Retrieve description of the texture surface so we can access its size
	D3DSURFACE_DESC my_image_desc;
	texture->GetLevelDesc(0, &my_image_desc);
	*out_texture = texture;
	*out_width = (int)my_image_desc.Width;
	*out_height = (int)my_image_desc.Height;

	return true;
}

bool LoadTextureFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)
{
	LOG_ALWAYS(RELEASE, "LoadTextureFromFile(" + std::string(filename) + ")");

	// Load texture from disk
	PDIRECT3DTEXTURE9 texture;
	HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice, filename, &texture);
	if (hr != S_OK)
		return false;

	// Retrieve description of the texture surface so we can access its size
	D3DSURFACE_DESC my_image_desc;
	texture->GetLevelDesc(0, &my_image_desc);
	*out_texture = texture;
	*out_width = (int)my_image_desc.Width;
	*out_height = (int)my_image_desc.Height;

	return true;
}

void unloadTexture(LPDIRECT3DTEXTURE9 texture)
{
	if (texture == nullptr)
	{
		return;
	}
	gameWindow.texturesForDeleting.push_back(texture);
}

void unloadTexture(LPDIRECT3DTEXTURE9 texture, string file)
{
	if (texture == nullptr)
	{
		return;
	}
	LOG_ALWAYS(RELEASE, "unloadTexture(" + file + ")");
	gameWindow.texturesForDeleting.push_back(texture);
}

ImVec2 getOurSize(int a, int b)
{
//	ImVec2 rect = ImGui::GetMainViewport()->WorkSize;
	RECT rect = gameWindow.rect;
	return { (float)rect.right / (1280.f / (float)a), (float)rect.bottom / (1024.f / (float)b) };
}

float getOurSizeX(int a)
{
//	ImVec2 rect = ImGui::GetMainViewport()->WorkSize;
	RECT rect = gameWindow.rect;
	return rect.right / (static_cast<float>(1280) / a);
}

float getOurSizeY(int b)
{
//	ImVec2 rect = ImGui::GetMainViewport()->WorkSize;
	RECT rect = gameWindow.rect;
	return rect.bottom / (static_cast<float>(1024) / b);
}

bool beginOurTooltip(ImVec2 logoSize, const char* text)
{
	ImVec2 min = ImGui::GetCursorScreenPos();
	ImVec2 max = ImVec2(min.x + logoSize.x, min.y + logoSize.y);
	if (ImGui::IsMouseHoveringRect(min, max, false) == true)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.75f);
		ImGui::BeginTooltip();
		ImGui::PopStyleVar();
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(208, 206, 92)));
		ImGui::Text(text);
		ImGui::PopStyleColor();
		ImGui::EndTooltip();
		return true;
	}
	return false;
}

bool beginOurTooltip(ImVec2 min, ImVec2 logoSize, const char* text)
{
	ImVec2 max = ImVec2(min.x + logoSize.x, min.y + logoSize.y);
	if (ImGui::IsMouseHoveringRect(min, max, false) == true)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.75f);
		ImGui::BeginTooltip();
		ImGui::PopStyleVar();
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(208, 206, 92)));
		ImGui::Text(text);
		ImGui::PopStyleColor();
		ImGui::EndTooltip();
		return true;
	}
	return false;
}

void TextCentered(std::string text)
{
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::Text(text.c_str());
}

ImVec2 ImageCentered(PDIRECT3DTEXTURE9 texture, ImVec2 size)
{
	ImVec2 window = ImGui::GetWindowSize();
	ImVec2 coords = ImVec2((window.x - size.x) * 0.5f, (window.y - size.y) * 0.5f);
	ImGui::SetCursorPos(coords);
	ImGui::Image(texture, size);
	return coords;
}

/*
static IDirect3DDevice9* get_pDevice()
{
	if (!gameWindow.pDevice)
	{
		gameWindow.pDevice = getWindowRect().pDevice;
	}
	return gameWindow.pDevice;
}
*/

static PDIRECT3DTEXTURE9 myCursor = NULL;
static int myCursor_width = 0;
static int myCursor_height = 0;
void setNewCursor()
{
	if (!myCursor)
	{
		LOAD_TEXTURE("dmData/cursor/cursor.tga", &myCursor, &myCursor_width, &myCursor_height);
	}
	ImVec2 p = ImGui::GetMousePos();
	ImGui::GetWindowDrawList()->AddImage((ImTextureID)(intptr_t)myCursor, ImVec2(p.x - 5.0f, p.y), ImVec2(p.x + myCursor_width - 5.0f, p.y + myCursor_height));
}

void setGameCursorPos(int x, int y)
{
//	ImVec2 pos = getOurSize(617, 535);

	coords* pos1 = reinterpret_cast<coords*>(0x02928D24);
	pos1->xCoord = x;
	pos1->yCoord = y;

	coords* pos2 = reinterpret_cast<coords*>(0x02742128);
	pos2->xCoord = x;
	pos2->yCoord = y;
}

void callGameButton(string button)
{
	int x = 0;
	int y = 0;
	if (strcmp(button.c_str(), "prebattle_withdraw_button") == 0)
	{
		x = 617;
		y = 535;
	}
	else if (strcmp(button.c_str(), "prebattle_auto_resolve_button") == 0)
	{
		x = 617;
		y = 485;
	}
	else if (strcmp(button.c_str(), "prebattle_fight_button") == 0)
	{
		x = 617;
		y = 435;
	}
	else
	{
		LOG_ALWAYS(DEVELOPMENT, "callGameButton(" + button + ") return");
		return;
	}
	LOG_ALWAYS(DEVELOPMENT, "callGameButton(" + button + ")");
	setGameCursorPos(x, y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
}
















