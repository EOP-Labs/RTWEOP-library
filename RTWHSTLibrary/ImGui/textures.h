#pragma once
#include <D3dx9tex.h>
#pragma comment(lib, "D3dx9")
#include <imgui.h>
#include <string>
#include "../differentFunctions/log.h"

bool LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height);
bool LoadTextureFromFile(LPDIRECT3DDEVICE9 g_pd3dDevice, const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height);
void unloadTexture(LPDIRECT3DTEXTURE9 texture);
void unloadTexture(LPDIRECT3DTEXTURE9 texture, std::string file);
ImVec2 getOurSize(int a, int b);
float getOurSizeX(int a);
float getOurSizeY(int b);
bool beginOurTooltip(ImVec2 logoSize, const char* text);
bool beginOurTooltip(ImVec2 min, ImVec2 logoSize, const char* text);
//void setNewCursor();
void TextCentered(std::string text);
ImVec2 ImageCentered(PDIRECT3DTEXTURE9 texture, ImVec2 size);
void setGameCursorPos(int x, int y);
void callGameButton(std::string button);



#define LOAD_TEXTURE(filename, out_texture, out_width, out_height)   LOG_ASSERT(LoadTextureFromFile(filename, out_texture, out_width, out_height), desTab.fileMissing + filename)















