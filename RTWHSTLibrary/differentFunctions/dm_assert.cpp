#include "../memory/memoryWork.h"
#include "dm_assert.h"

using namespace std;

static char* ConvertUtf8ToWindows1251(string utf8_str) 
{
    // Преобразуем строку из UTF-8 в wide-char (UTF-16)  
    int wideCharSize = MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), -1, NULL, 0);
    wchar_t* wideCharStr = new wchar_t[wideCharSize];
    MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), -1, wideCharStr, wideCharSize);
    // Преобразуем wide-char строку в Windows-1251  
    int multiByteSize = WideCharToMultiByte(1251, 0, wideCharStr, -1, NULL, 0, NULL, NULL);
    char* multiByteStr = new char[multiByteSize];
    WideCharToMultiByte(1251, 0, wideCharStr, -1, multiByteStr, multiByteSize, NULL, NULL);

    return multiByteStr;
}

bool dm_assert(bool condition, string text)
{
	if (!condition)
	{
        char* text1251 = ConvertUtf8ToWindows1251(text);
        LOG_ALWAYS(RELEASE, "!!! assert | " + text);
		MessageBoxA(nullptr, text1251, "assert", MB_ICONWARNING);
		return false;
	}
	return true;
}

bool fileExists(const string& filename)
{
	struct stat buffer;
	return (stat(filename.c_str(), &buffer) == 0);
}

languageS language;
descriptionTab desTab;











