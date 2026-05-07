///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <conio.h>
#include <Psapi.h>
#include <process.h>
#include <fstream>
#include "mainMenu.h"
#include <RTWHotSeatTool/RTWHSTLibrary/differentFunctions/dm_assert.h>
#include <RTWHotSeatTool/RTWHSTLibrary/differentFunctions/log.h>
using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_ATTEMPTS (9999)

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

char* ConvertUtf8ToWindows1251(string utf8_str)
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

static DWORD FindProcessId(string processName)
{
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);
    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE) return 0;
    Process32First(processesSnapshot, &processInfo);
//  std::wstring ws(processInfo.szExeFile);
//  std::string strP(ws.begin(), ws.end());   //C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.40.33807\include\xutility(4672,18): warning C4244: =: преобразование "wchar_t" в "char", возможна потеря данных   
    string strP = wcharToString(processInfo.szExeFile);
    if (!processName.compare(strP)) {
        CloseHandle(processesSnapshot);
        return processInfo.th32ProcessID;
    }
    while (Process32Next(processesSnapshot, &processInfo)) {
    //  std::wstring ws(processInfo.szExeFile);
    //  std::string strP(ws.begin(), ws.end());
        string strP2 = wcharToString(processInfo.szExeFile);
        if (!processName.compare(strP2)) {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }
    }
    CloseHandle(processesSnapshot);
    return 0;
}

static uint32_t checksum(std::ifstream& file)
{
    uint32_t sum = 0;

    uint32_t word = 0;
    while (file.read(reinterpret_cast<char*>(&word), sizeof(word))) {
        sum += word;
        word = 0;
    }

    sum += word;

    return sum;
}

static string boolStr(bool result)
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

const wchar_t* GetWC(const char* c)
{
    const size_t cSize = strlen(c) + 1;
    wchar_t* wc = new wchar_t[cSize];
//	mbstowcs(wc, c, cSize);

    size_t outSize;
    mbstowcs_s(&outSize, wc, cSize, c, cSize - 1);

    return wc;
}

/*
static HMODULE getAndLogModule(HANDLE hProcess, string moduleName)
{
    HMODULE target = NULL;
    HMODULE hModules[1024];
    DWORD cbNeeded;

    if (EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded)) {
        for (DWORD i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
            TCHAR szModName[MAX_PATH];
            if (GetModuleFileNameEx(hProcess, hModules[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
            {
                string str = wcharToString(szModName);
                LOG_ALWAYS(RELEASE, str);

                if (str.find(moduleName) != string::npos)
                {
                    target = hModules[i];
                }
            }
        }
    }

//  CloseHandle(hProcess);
    return target;
}
*/

static void writeLogModule(HANDLE hProcess)
{
    HMODULE hModules[1024];
    DWORD cbNeeded;
    if (EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded)) {
        for (DWORD i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
            TCHAR szModName[MAX_PATH];
            if (GetModuleFileNameEx(hProcess, hModules[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
            {
                string str = wcharToString(szModName);
                LOG_ALWAYS(RELEASE, str);
            }
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void STARTER::init()
{
    m_target_exe = "RomeTW-ALX.exe";
    m_full_path = getFullPath();

    LOG_ASSERT(fileExists(m_target_exe), string(m_target_exe) + " not found in '" + m_full_path + "'");

    ifstream file(m_target_exe);
    m_sum = checksum(file);
    LOG_ALWAYS(DEVELOPMENT, "STARTER::init(m_sum: " + to_string(m_sum) + ")");

    if (m_sum == 271658014)
    {
        m_game_version = 1; //disk
    }
    else
    {
        m_game_version = 2; //steam
    }

    m_success           = FALSE;
    m_is_start          = false;
    m_is_game_ranger    = false;
    m_cmd               = NULL;
    m_debug_exe         = false;
    m_debug_dll         = false;
    m_input_ancillary   = 8;
    m_w_target_exe      = L"RomeTW-ALX.exe";
    m_target_steam_exe  = "testappa.exe";
    m_dll_path          = "RTWHSTLibrary.dll";
    m_hot_seat_tool_exe = "RTWHotSeatTool.exe";
    m_process_ID        = NULL;
}

/*
BOOL STARTER::startGame()
{
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    // Запускаем процесс  
    m_success = CreateProcess(m_w_target_exe, m_cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    LOG_ALWAYS(RELEASE, "startGame(" + boolStr(m_success) + ")");
    return m_success;
}
*/

BOOL STARTER::startGame()
{
    m_success = ShellExecute
    (
        NULL,              // родительское окно
        L"open",           // операция (запуск)
        m_w_target_exe,    // путь к исполняемому файлу
        m_cmd,             // командная строка (параметры)
        NULL,              // рабочая директория
        SW_SHOW            // показ окна
    ) != NULL;

    LOG_ALWAYS(RELEASE, "startGame(" + boolStr(m_success) + ")");
    return m_success;
}

bool STARTER::checkProcessID()
{
    m_process_ID = FindProcessId(m_target_exe);
    return m_process_ID != NULL;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int STARTER::injectDLL()
{
    LOG_ALWAYS(RELEASE, "injectDLL() - start");


    // Если это не через GameRanger, то запускаем игру сразу   
    if (!m_is_game_ranger)
    {
        LOG_ASSERT(startGame() == TRUE, desTab.game);
    }

    // Если это стим версия игры, то нам нужен другой ехе   
    if (m_game_version == 2)
    {
        m_target_exe = m_target_steam_exe;
    }

    // Ждем...   
    int count = 0;
    while (!m_process_ID)
    {
        m_process_ID = FindProcessId(m_target_exe);

    #ifdef _DEBUG
        LOG_ALWAYS(RELEASE, "while (!m_process_ID): " + to_string(m_process_ID));
    #endif // _DEBUG

        if (count >= MAX_ATTEMPTS) // На всякий случай...   
        {
            LOG_ALWAYS(RELEASE, " !!! ХВАТИТ !!! " + to_string(m_process_ID));
            break;
        }
        count++;
    }
    LOG_ALWAYS(RELEASE, "FindProcessId: " + to_string(m_process_ID));

    // Открываем процесс  
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_process_ID);
    if (!hProcess) 
    {
        LOG_ASSERT(false, desTab.process);
        return -1;
    }

    // Выделяем память в процессе  
    LPVOID remoteMem = VirtualAllocEx(hProcess, NULL, strlen(m_dll_path) + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!remoteMem) 
    {
        LOG_ASSERT(false, desTab.memory);
        CloseHandle(hProcess);
        return -1;
    }

    // Записываем путь к DLL в выделенную память  
    bool tr = WriteProcessMemory(hProcess, remoteMem, m_dll_path, strlen(m_dll_path) + 1, NULL);
    LOG_ALWAYS(RELEASE, "WriteProcessMemory: " + to_string(tr));

    // Получаем адрес LoadLibraryA  
    DWORD adr = NULL;
    HMODULE module = GetModuleHandleA("Kernel32.dll");
    if (module)
    {
        adr = (DWORD)GetProcAddress(module, "LoadLibraryA");
    }
    else if(!module || !adr)
    {
        LOG_ASSERT(false, "else if(!module || !adr)");
        CloseHandle(hProcess);
        return -1;
    }

    // Вызываем LoadLibraryA с аргументом .dll и возвращаем адрес потока  
    HANDLE hThread = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)adr, remoteMem, 0, 0);
    if (!hThread)
    {
        LOG_ASSERT(false, "CreateRemoteThread");
        CloseHandle(hProcess);
        return -1;
    }

    // Ожидаем завершение потока  
    DWORD wait = WaitForSingleObject(hThread, INFINITE);
    string waitStr = "";
    switch (wait)
    {
        case WAIT_OBJECT_0:    // объект перешёл в сигнальное состояние.
        {
            waitStr = "WAIT_OBJECT_0";
            break;
        }
        case WAIT_TIMEOUT:     // интервал ожидания истёк, а состояние объекта — несигнальное.
        {
            waitStr = "WAIT_TIMEOUT";
            break;
        }
        case WAIT_FAILED:      // ошибка функции(например, неверный дескриптор).Для получения дополнительной информации можно вызвать GetLastError.
        {
            waitStr = "WAIT_FAILED";
            break;
        }
        case WAIT_ABANDONED:   // указанный объект — мьютекс, который не был
        {
            waitStr = "WAIT_ABANDONED";
            break;
        }
    }
    LOG_ALWAYS(RELEASE, "WaitForSingleObject: " + waitStr);

//  HMODULE hmtw = getAndLogModule(hProcess, dllPath);
    writeLogModule(hProcess);
//  callDllFunction();

    // Закрываем дескрипторы  
    CloseHandle(hThread);
    CloseHandle(hProcess);


    LOG_ALWAYS(RELEASE, "injectDLL() - end");
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


















