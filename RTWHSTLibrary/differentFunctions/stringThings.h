#pragma once
#include <Windows.h>
#include <string>
#include "../memory/gameStructures.h"

wchar_t* StrToWstr(const std::string& aString);
const wchar_t* GetWC(const char* c);
std::string getTime_2();
std::string boolStr(bool result);
char* ConvertUtf8ToWindows1251(std::string utf8_str);
std::string cp1251_to_utf8(const char* str);
std::string uniStringToStr(UNICODE_STRING**& uniString);
std::string uniToAnsi(UNICODE_STRING**& uniStr);
std::string uniToAnsi_2(UNICODE_STRING**& uniStr);
std::string uniToAcp(UNICODE_STRING**& uniStr);
void createUniString(UNICODE_STRING**& newUniStringPointer, const char* nonUniStr);
bool checNonStandardChar(std::string text);
bool checNonStandardChar2(std::string text);
bool checNonStandardCharCyrillic(std::string text);
bool checNonStandardCharAll(std::string text);
size_t stringToHash(std::string strToHash);
char* validChar(char* v);
extern std::string wcharToString(const wchar_t* wstr);

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args);














