#include "log.h"
#include <ctime>
#include "stringThings.h"
#include "screenshoter.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
LOG_STRUCT LOG;

string LOG_STRUCT::getTime(bool isScreen)
{
    time_t now = time(0);
#pragma warning(suppress : 4996)
    tm* ltm = localtime(&now);
    string data = "";
    if (isScreen)
    {
        data =
            to_string(ltm->tm_mday) + "_" +
            to_string(1 + ltm->tm_mon) + "_" +
            to_string(1900 + ltm->tm_year) + "_" +
            to_string(ltm->tm_hour) + "_" + to_string(ltm->tm_min) + "_" + to_string(ltm->tm_sec);
    }
    else
    {
        data =
            "[" +
            to_string(ltm->tm_mday) + "." +
            to_string(1 + ltm->tm_mon) + "." +
            to_string(1900 + ltm->tm_year) + " - " +
            to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec) +
            "]";
    }
    return data;
}

void LOG_STRUCT::init(LOG_LEVEL level)
{
    setLogLevel(level);
    openLogFile(0);
}

void LOG_STRUCT::openLogFile(int status)
{
    m_status = status;

    if (m_status == 0)
    {
    //  фокус, чтоб часть текста не затиралась при переходе с .exe на .dll   
        m_out_file.open(m_file, ios::out);
        m_out_file.close();

        m_out_file.open(m_file, ios::app);
        if (m_out_file.is_open())
        {
            m_out_file << getTime(false) + " [.exe] " + "openLogFile(" + to_string(status) + ")" << endl;
        }
    }
    else
    {
        m_out_file.open(m_file, ios::app);
        if (m_out_file.is_open())
        {
            m_out_file << getTime(false) + " [.dll] " + "openLogFile(" + to_string(status) + ")" << endl;
        }
        return;
    }

    if (m_out_file.is_open())
    {
        m_out_file << getTime(false) + " [.exe] " + "RTWHotSeatTool.exe - running" << endl;
    }
}

void LOG_STRUCT::close()
{
    if (m_out_file.is_open())
    {
        m_out_file << getTime(false) + m_status_str[m_status] + "closeLogFile(" + to_string(m_status) + ")" << endl;
    }
    m_out_file.close();
}

void LOG_STRUCT::always(LOG_LEVEL level, string text)
{
#if _DEBUG
#else
    if (level == DEBUG) // Эти логи только для меня, только для меня ;)   
        return;
#endif

    if (m_current_level >= level && level >= RELEASE && level <= DEBUG && m_out_file.is_open())
    {
        m_out_file << getTime(false) + m_status_str[m_status] + "[" + m_log_level_str[level] + "] " + text + "\n" << flush;
    }
}

void LOG_STRUCT::always(string text)
{
    if (m_out_file.is_open())
    {
        m_out_file << getTime(false) + m_status_str[m_status] + text << endl;
    }
}

void LOG_STRUCT::always(bool print, string text)
{
    if (!print)
        return;

    if (m_out_file.is_open())
    {
        m_out_file << getTime(false) + m_status_str[m_status] + text << endl;
    }
}

void LOG_STRUCT::reminder(string text)
{
    ofstream out;
    out.open(m_file_reminder, ios::app);
    if (out.is_open())
    {
        out << getTime(false) + m_status_str[m_status] + text << endl;
    }
    out.close();
}

void LOG_STRUCT::reminder(string text, const wchar_t* sourceFile, unsigned line)
{
    ofstream out;
    out.open(m_file_reminder, ios::app);
    if (out.is_open())
    {
    //  wstring ws(sourceFile);
    //  string str(ws.begin(), ws.end());   //C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.40.33807\include\xutility(4672,18): warning C4244: =: преобразование "wchar_t" в "char", возможна потеря данных   

        string str = wcharToString(sourceFile);

        m_last_source_file = "source file: " + str + ", line : " + to_string(line);
        out << getTime(false) + m_status_str[m_status] + text + " | " + m_last_source_file << endl;

    //  out << getTime(false) + m_status_str[m_status] + text << endl;
    }
    out.close();
}

bool LOG_STRUCT::dm_assert(bool condition, string text)
{
    if (condition) return true;

    always(RELEASE, "dm_assert(" + text + ")");
    reminder("dm_assert(" + text + ")");

    return false;
}

bool LOG_STRUCT::dm_assert(bool condition, string text, const wchar_t* file, unsigned line)
{
    if (condition) return true;

    reminder("dm_assert(" + text + ")", file, line);
    always(RELEASE, "dm_assert(" + text + ") | " + m_last_source_file + ")");

    return false;
}

void LOG_STRUCT::dm_assert_r(bool condition, string text, const wchar_t* file, unsigned line)
{
    if (condition) return;

    reminder("dm_assert(" + text + ")", file, line);
    always(RELEASE, "dm_assert(" + text + ") | " + m_last_source_file + ")");

    HWND hwnd = gameWindow.hwnd;
    char* text1251 = ConvertUtf8ToWindows1251("ASSERT: \n" + text + "\n" + m_last_source_file);

    int result = MessageBoxA(hwnd, text1251, "ASSERT!", MB_ABORTRETRYIGNORE | MB_ICONEXCLAMATION);
	switch (result) 
    {
		case IDABORT:
			// «Прервать»
			exit(0);
			break;
		case IDRETRY:
			// «Повторить»
			break;
		case IDIGNORE:
			// «Пропустить»
            return;
		default:
			exit(0);
			break;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////




















