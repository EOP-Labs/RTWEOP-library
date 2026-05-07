#include "stringThings.h"
#include <chrono>
#include <fstream>
#include <filesystem>  
#include "log.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// סעאנאÿ סטסעולא כמדמג   
void log_always(string text)
{
//  string file = "dmData/RTWHST.log.dm";
//  ofstream out;
//  out.open(file, ios::app);
//  // out.open(file, ios::out);
//  if (out.is_open())
//  {
//      out << getTime(false) + " [.dll] " + text << endl;
//  }
//  out.close();
    LOG_ALWAYS(RELEASE, "createUniString(" + text + ")");
}

void log_always(bool print, string text)
{
    if (!print)
        return;

//  string file = "dmData/RTWHST.log.dm";
//  ofstream out;
//  out.open(file, ios::app);
//  // out.open(file, ios::out);
//  if (out.is_open())
//  {
//      out << getTime(false) + " [.dll] " + text << endl;
//  }
//  out.close();
    LOG_ALWAYS(RELEASE, "createUniString(" + text + ")");
}

void log_reminder(string text)
{
//  string file = "dmData/reminder.log.dm";
//  ofstream out;
//  out.open(file, ios::app);
//  if (out.is_open())
//  {
//      out << "[.dll] " + text << endl;
//  }
//  out.close();
    LOG_REMINDER(text);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void createUniString(UNICODE_STRING**& newUniStringPointer, const char* nonUniStr)
{
    LOG_ALWAYS(DEBUG, "createUniString(" + string(nonUniStr) + ")");

    char* nonUniStrC = const_cast<char*>(nonUniStr);
    
    typedef void __fastcall func2(UNICODE_STRING**& param_1, int stub, char* param_3);
    func2* f2 = (func2*)offsets.onCreateUniString;
    f2(newUniStringPointer, 0, nonUniStrC);

//  newUniStringPointer = reinterpret_cast<UNICODE_STRING**>(*uniStr);
    int wCharsNum = MultiByteToWideChar(CP_UTF8, 0, nonUniStr, -1, nullptr, 0);
    auto wStr = new wchar_t[wCharsNum];
    MultiByteToWideChar(CP_UTF8, 0, nonUniStr, -1, wStr, wCharsNum);
    wstring utf16Line = wStr;
    delete[] wStr;
    (*newUniStringPointer)->Length = static_cast<USHORT>(utf16Line.size());
    (*newUniStringPointer)->something2 = static_cast<USHORT>(utf16Line.size());
    auto ptr = reinterpret_cast<unsigned short*>(&(*newUniStringPointer)->Buffer);
    for (UINT32 i = 0; i < utf16Line.size(); i++)
        *(ptr + i) = utf16Line[i];
    *(ptr + utf16Line.size()) = static_cast<unsigned short>(0);
}

string uniStringToStr(UNICODE_STRING**& uniString)
{
    if (uniString == nullptr || *uniString == nullptr)
    {
        return "";
    }

    string strTo;
    UNICODE_STRING* uniS = *uniString;
    wchar_t* wstr = (wchar_t*)&uniS->Buffer;

    int wchars_num = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    if (wchars_num <= 0)
    {
        return strTo;
    }
    char* szTo = new char[wchars_num];
    szTo[wchars_num - 1] = '\0';
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, szTo, wchars_num, NULL, NULL);

    strTo = szTo;
    delete[] szTo;

    return strTo;
}

string uniToAcp(UNICODE_STRING**& uniStr)
{
    if (uniStr == nullptr || *uniStr == nullptr)
        return "";
    UNICODE_STRING* uniS = *uniStr;
    const auto wstr = reinterpret_cast<wchar_t*>(&uniS->Buffer);
    const int sizeNeeded = WideCharToMultiByte(CP_ACP, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    const auto szTo = new char[sizeNeeded];
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, szTo, sizeNeeded, nullptr, nullptr);
    szTo[uniS->Length] = '\0';
    std::string strTo = szTo;
    delete[] szTo;
    return strTo;
}

bool checNonStandardChar(string text)
{
    if (text.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_/.,") != string::npos)
    {
        return true;
    }
    return false;
}

bool checNonStandardChar2(string text)
{
    if (text.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_/.,-=!@#$%^&()+'~") != string::npos)
    {
        return true;
    }
    return false;
}

bool checNonStandardCharCyrillic(string text)
{
    if (text.find_first_not_of("ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞ‗אבגדהו¸זחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ_/.,") != string::npos)
    {
        return true;
    }
    return false;
}

bool checNonStandardCharAll(string text)
{
//  if (text.find_first_not_of("ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞ‗אבגדהו¸זחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_/.,-=!@#$%^&()+'""`~") != string::npos)
    if (text.find_first_not_of("ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞ‗אבגדהו¸זחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_/.,") != string::npos)
    {
        return true;
    }
    return false;
}

bool is_russian_letter(wchar_t c) {
    static const std::wstring alphabet = L"ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞ‗אבגדהו¸זחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ";
    return alphabet.find(c) != std::wstring::npos;
}

string uniToAnsi(UNICODE_STRING**& uniStr)
{
    if (uniStr == nullptr || *uniStr == nullptr)
    {
        return "";
    }
    UNICODE_STRING* uniS = *uniStr;
    const auto wstr = reinterpret_cast<wchar_t*>(&uniS->Buffer);
    const int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    const auto szTo = new char[sizeNeeded];
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, szTo, sizeNeeded, nullptr, nullptr);
    szTo[uniS->Length] = '\0';
    std::string strTo = szTo;
    delete[] szTo;


    if (checNonStandardChar(strTo))
    {
        strTo = uniToAcp(uniStr);
    }


    return strTo;
}

string uniToAnsi_2(UNICODE_STRING**& uniStr)
{
    if (uniStr == nullptr || *uniStr == nullptr)
    {
        return "";
    }
    UNICODE_STRING* uniS = *uniStr;
    const auto wstr = reinterpret_cast<wchar_t*>(&uniS->Buffer);
    const int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    const auto szTo = new char[sizeNeeded];
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, szTo, sizeNeeded, nullptr, nullptr);
    szTo[uniS->Length] = '\0';
    std::string strTo = szTo;
    delete[] szTo;

    return strTo;
}

string wcharToString(const wchar_t* wstr)
{
    string strTo = "[ERROR wcharToString]";

    int wchars_num = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    if (wchars_num <= 0)
    {
        return strTo;
    }
    char* szTo = new char[wchars_num];
    szTo[wchars_num - 1] = '\0';
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, szTo, wchars_num, NULL, NULL);

    strTo = szTo;
    delete[] szTo;

    return strTo;
}

wchar_t* StrToWstr(const std::string& aString)
{
	// קעמבû םו הוכאעü ךאזהûי נאח new סמחהאהטל םוךמעמנûי בףפונ חאנאםוו
	const int maxSize = 1024 * 1024; // 1Ìב סטלגמכמג
	static wchar_t buff[maxSize];

	int nSize = ::MultiByteToWideChar(CP_UTF8, 0, aString.c_str(), static_cast<int>(aString.length() + 1), NULL, NULL);

	wchar_t* tBuff = buff;
	if (nSize > maxSize)
	{
		// ןûעאולסÿ גûהוכטעü ןאלÿעü עמכüךמ וסכט םו ץגאעטכמ
		tBuff = new wchar_t[nSize];
	}
	if (nSize <= 0 && tBuff == NULL)
//		return L"";
		return tBuff;

	::MultiByteToWideChar(CP_UTF8, 0, aString.c_str(), static_cast<int>(aString.length() + 1), buff, nSize);

	wchar_t* result(tBuff);

	if (tBuff != buff)
		delete[] tBuff;

	return result;
}

const wchar_t* GetWC(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	//	mbstowcs(wc, c, cSize);

	size_t outSize;
	mbstowcs_s(&outSize, wc, cSize, c, cSize - 1);

	return wc;
}

string cp1251_to_utf8(const char* str) 
{
    string res;
    int result_u, result_c;
    result_u = MultiByteToWideChar(1251, 0, str, -1, 0, 0);
    if (!result_u) { return 0; }
    wchar_t* ures = new wchar_t[result_u];
    if (!MultiByteToWideChar(1251, 0, str, -1, ures, result_u)) {
        delete[] ures;
        return 0;
    }
    result_c = WideCharToMultiByte(65001, 0, ures, -1, 0, 0, 0, 0);
    if (!result_c) {
        delete[] ures;
        return 0;
    }
    char* cres = new char[result_c];
    if (!WideCharToMultiByte(65001, 0, ures, -1, cres, result_c, 0, 0)) {
        delete[] cres;
        return 0;
    }
    delete[] ures;
    res.append(cres);
    delete[] cres;
    return res;
}

char* ConvertUtf8ToWindows1251(string utf8_str) 
{
    // Ïנומבנאחףול סענמךף טח UTF-8 ג wide-char (UTF-16)  
    int wideCharSize = MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), -1, NULL, 0);
    wchar_t* wideCharStr = new wchar_t[wideCharSize];
    MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), -1, wideCharStr, wideCharSize);
    // Ïנומבנאחףול wide-char סענמךף ג Windows-1251  
    int multiByteSize = WideCharToMultiByte(1251, 0, wideCharStr, -1, NULL, 0, NULL, NULL);
    char* multiByteStr = new char[multiByteSize];
    WideCharToMultiByte(1251, 0, wideCharStr, -1, multiByteStr, multiByteSize, NULL, NULL);

    return multiByteStr;
}

size_t stringToHash(string strToHash)
{
    if (strToHash.size() == 0)
        return 0;

    return hash<string>()(strToHash);
}

string replace_all(
    const string& str,    // where to work
    const string& find,   // substitute 'find'
    const string& replace //      by 'replace'
) {
    string result;
    size_t find_len = find.size();
    size_t pos, from = 0;
    while (string::npos != (pos = str.find(find, from))) {
        result.append(str, from, pos - from);
        result.append(replace);
        from = pos + find_len;
    }
    result.append(str, from, string::npos);
    return result;
}

static string deleteAllBefore(string& text, string target)
{
    string::size_type pos{};
    pos = text.find_first_of(target, pos);
    text.erase(0, pos + target.length());
    return text;
}

static string deleteAllBefore2(string& text, string target)
{
//	string target = string(qa.modPatch) + "\\saves\\";
    int pos = text.find(target);
#pragma warning(suppress : 4834)
    text.substr(pos + target.length());

    return text;
}

char* validChar(char* v)
{
    if (v)
        return v;
    else
        return (char*)"";
}

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
    auto size = static_cast<size_t>(size_s);
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

string boolStr(bool result)
{
    if (result)
    {
        return "true";
    }
    else if (!result)
    {
        return "false";
    }
    return "error";
}

string getTime_2()
{
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
//  log_always("finished computation at " + string(std::ctime(&end_time)) + "elapsed time: " + to_string(elapsed_seconds.count()) + "s");
#pragma warning(suppress : 4996)
    return string(std::ctime(&end_time));
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////














