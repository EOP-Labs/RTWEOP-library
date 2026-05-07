#pragma once
#include <WinUser.h>
#include <sys/stat.h>  
using namespace std;

bool dm_assert(bool condition, string text);
bool fileExists(const string& filename);

struct languageS
{
    bool RU = true;
    bool ENG = false;
};
extern languageS language;

struct descriptionTab 
{
    string cfg                = "Не удалось открыть RTWHST.cfg.dm!";
    string dll                = "Отсутствует файл RTWHSTLibrary.dll!";
    string game               = "Не удалось запустить игру!";
    string process            = "Не удалось открыть процесс!";
    string memory             = "Не удалось выделить память!";
    string rome_jpeg          = "Отсутствует файл dmData/images/rome.jpeg";
    string cursor_tga         = "Отсутствует файл dmData/cursor/cursor.tga";
    string with_dll           = "Запустить с RTWHSTLibrary.dll";
    string without_dll        = "Запустить без RTWHSTLibrary.dll";
    string close              = "Закрыть";
    string play_music         = "Включить музыку";
    string language           = "Язык";
    string hotSeat            = "Выбрать ХотСит";
    string RTWHST             = "RTWHotSeatTool запущен";
    string battle1            = "Битва создается: ";
    string battle2            = "Битва создана: ";
    string kConsole           = "Консоль ключника";
    string consVer            = "ver. 0.0.1";
    string stratCoords        = "Координаты страт карты: ";
    string selCoords          = "Выбраны координаты: ";
    string selChar            = "Выбраны персонаж: ";
    string PMOpercent         = "Отнять -10% за отступление";
    string currHotSeat        = "Текущий ХотСит: ";
    string battResult         = "Результат битвы создан: ";
    string failedRes          = "Не удалось создать результаты боя";
    string transferRes        = "Перенести результаты боя";
    string fileMissing        = "Не удалось загрузить файл: ";
    string resultsDone        = "Результаты перенесены";
    string createBattle       = "Создать битву";
    string errNumUnits        = "Количество юнитов в файле результатов и в бою не совпадают.";
    string errTypeUnits       = "Типы юнитов в файле результатов и в бою не совпадают.";
    string hideLauncher       = "Скрыть лаунчер";
    string hideLauncTooltip   = "Скрыть лаунчер при дальнейших запусках программы.\nИгра автоматически будет запускаться в режиме \"Запустить с RTWHSTLibrary.dll\" \nТакже настройки можно менять в \\dmData\\configs\\launchSettings.json";
    string ancillaryLimit     = "Лимит анчей";
    string ancLimitTooltip    = "Установить новый лимит анчей\nпо умолчанию - 8, максимум - 127";
    string logLevel           = "Уровень лога";
    string playersList        = "Игроки";
    string incomingMessage    = "Входящее сообщение";
    string writeMessage       = "Написать сообщение";
    string reply              = "Ответить";
    string deleteMessage      = "Удалить сообщение";
    string sendMessage        = "Отправить сообщение";
    string quitGame           = "Выйти из игры";
    string loadSave           = "Загрузить сохранение";
    string start              = "СТАРТ";
    string setNickname        = "установить никнейм";
    string setPlayer          = "Установить фракцию игрока";
    string deletePlayer       = "Удалить фракцию игрока";
    string nickname           = "никнейм";
    string password           = "пароль ";
    string isKeymaster        = "это фракция ключника";
    string husbands           = "Почаще предлагать мужей дочерям";
    string updateFiles        = "Обновите все файлы";
    string updKeyPass         = "Обновить пароль ключника";
    string setKeyPass         = "установить пароль ключника";
    string openHS             = "Открыть настройки ХотСит кампании";
    string neverWithdraw      = "Армии игроков никогда не отступают";
    string player             = "Игрок";
};
extern descriptionTab desTab;













