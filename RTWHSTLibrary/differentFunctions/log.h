#pragma once
#include <string>
#include <fstream>
#include <cassert>

enum LOG_LEVEL
{
	RELEASE,
	RELEASEFULL,
	DEVELOPMENT,
	BUGTEST,
	DEBUG
};

struct LOG_STRUCT
{
	std::string     m_file = "dmData/RTWHST.log.dm";
	std::string     m_file_reminder = "dmData/reminder.log.dm";
	std::ofstream   m_out_file;
	int             m_status = 0;
	std::string     m_last_source_file = "";
	std::string     m_status_str[2]{ " [.exe] ", " [.dll] " };
	LOG_LEVEL       m_current_level;
	std::string     m_log_level_str[5]{
		"RELEASE",
		"RELEASEFULL",
		"DEVELOPMENT",
		"BUGTEST",
		"DEBUG"
	};

	void            init(LOG_LEVEL level);
	void            openLogFile(int status);
	void            always(LOG_LEVEL level, std::string text);
	void            always(std::string text);
	void            always(bool print, std::string text);
	void            reminder(std::string text);
	void            reminder(std::string text, const wchar_t* file, unsigned line);
	bool            dm_assert(bool condition, std::string text);
	bool            dm_assert(bool condition, std::string text, const wchar_t* file, unsigned line);
	void            dm_assert_r(bool condition, std::string text, const wchar_t* file, unsigned line);
	std::string     getTime(bool isScreen);
	void            setLogLevel(LOG_LEVEL level) { m_current_level = level; };
	void            close();
};
extern LOG_STRUCT LOG;

#define LOG_ALWAYS(level, text)   LOG.always(level, text)

#define LOG_REMINDER(text)        LOG.reminder(text, _CRT_WIDE(__FILE__), (unsigned)(__LINE__))


#if NDEBUG
	#define LOG_ASSERT(condition, text)   LOG.dm_assert_r(condition, text, _CRT_WIDE(__FILE__), (unsigned)(__LINE__))
#else
	#define LOG_ASSERT(condition, text)   assert(LOG.dm_assert(condition, text, _CRT_WIDE(__FILE__), (unsigned)(__LINE__)))
#endif



/////////////////////
//	
//	#define LOG_ALWAYS(level, text)			LOG.always(level, text)
//	
//	#define LOG_REMINDER_EXTENDED(text)		LOG.reminder(text, _CRT_WIDE(__FILE__), (unsigned)(__LINE__))
//	#define LOG_REMINDER(text)				LOG_REMINDER_EXTENDED(text)
//	
//	
//	#if NDEBUG
//	#define LOG_ASSERT_EXTENDED(condition, text)	LOG.dm_assert_r(condition, text, _CRT_WIDE(__FILE__), (unsigned)(__LINE__))
//	#else
//	#define LOG_ASSERT_EXTENDED(condition, text)	assert(LOG.dm_assert(condition, text, _CRT_WIDE(__FILE__), (unsigned)(__LINE__)))
//	#endif
//	
//	#define LOG_ASSERT(condition, text)					LOG_ASSERT_EXTENDED(condition, text)
//	
/////////////////////

































