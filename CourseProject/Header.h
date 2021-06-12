#ifndef HEADER_H
#define HEADER_H

#include <Windows.h>
#include <string>
#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <ostream>

using namespace std;

struct Education;
struct AutoData;
struct auto;
extern struct UserData
{
    char login[255];
    char password[255];
    int level;
};

extern bool availabilityauto;
extern int varSort;
/*
============================================
            объявление функций
============================================
*/
// проверка на наличие файла данных
bool SearchDataFile();
// проеверка файла админа
bool CreateOrDeleteAdminFile();
// запись данных в файла профиля
string WorkUserDataFD(UserData user, bool rePass, bool del);
// смена пароля имеющемуся пользователю
UserData setNewPass();
// сбор данных для пользователя
UserData GetNewUserDataData();
// Функции выбора в меню
void GetChoiceMenuAdmin();
void GetChoiceAutoDataFileData();
void GetChoiceAutoDataRecords();
void GetChoiceAutoDataUserData();
void GetChoiceMenuManager();
void GetChoiceMenuUser();
// функции принта меню
void PrintMenuAdmin();
void DisplayAutoDataFileData();
void DisplayAutoDataRecords();
void DisplayAutoDataUserData();
void PrintMenuManager();
void PrintMenuUser();
// функции получения значения с клавиатуры
// получения значения int
int getValueInt(string mess);
// получения значения string
string getValueStr(string mess);
// проверка пароля и логина
void GetLogiAndPass();
// проверка на наличие файла данных
bool SearchDataFile();
// создание и затирание файла данных
bool CreateOrDeleteFD(bool createOrDelete);
// сбор сведений по работнику
auto aggregationautoData();
// запись данных нового работника в файл данных (перезапись файла)
bool creatRecordInFD(bool atMemory);
// принт таблицы файла данных
void printTable();
// принт таблицы файла данных сокращенно
void printTableAbbr();
// поиск работника и принт таблицы
void searchAndPrintTable(int change);
// функция поиска в строке
bool search(string query, string fundStr);
// получение данных работников в память
void getAllautoFD();
// удаление данных работника в памяти и перезапись в файл
bool deleteWirkerInMemory();
// изменение данных работника в памяти и перезапись в файл
bool changeWirkerInMemory();
//сортировка
// компаратор last name
bool compararereceipt_date(const auto lhs, const auto rhs);
// компаратор first name
bool compararemodel(const auto lhs, const auto rhs);
// компаратор departure_date
bool compararecolor(const auto lhs, const auto rhs);
// функция сортировки
void sortLN();
void sortFN();
void sortDep();
#endif