#pragma once
#include <string>

class STARTER
{
public:
    static int            m_game_version;
    static uint32_t       m_sum;

    static BOOL           m_success;
    static bool           m_is_start;
    static bool           m_is_game_ranger;
    static wchar_t*       m_cmd;
    static bool           m_debug_exe;
    static bool           m_debug_dll;
    static int            m_input_ancillary;
    static std::string    m_hot_seat_tool_exe;

    static std::string    m_full_path;
    static const char*    m_target_exe;
    static const char*    m_target_steam_exe;
    static wchar_t*       m_w_target_exe;
    static DWORD          m_process_ID;
    static const char*    m_dll_path;

    static void           init();
    static int            injectDLL();
    static BOOL           startGame();
    static bool           checkProcessID();
    static int            WinMain();
    static std::string    getFullPath();
    static void           callDllFunction();
};

std::string wcharToString(const wchar_t* wstr);





