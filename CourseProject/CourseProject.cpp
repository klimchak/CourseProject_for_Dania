#include "Header.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ostream>
#include <cstdlib>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include "tabulate/table.hpp"

using namespace std;
using std::string;
using namespace tabulate;
#if __cplusplus >= 201703L
#include <variant>
using std::variant;
#else
#include "tabulate/variant_lite.hpp"
using nonstd::variant;
#endif
using Row_t = std::vector<variant<std::string, const char*, Table>>;

                                                                /*
                                                                глобальные переменные
                                                                */

bool choiceCreateFD = false;
bool fileCreate;
bool fileAdminCreate;
bool availabilityAuto;
vector<Auto> allAuto;
bool availabilityAuto;
int varSort = 1;
/*
структуры программы
*/
struct Profile
{
    char login[255];
    char password[255];
    int level;
};

// данные о самой машине
struct AutoData
{
    string body;
    string color;
    string equipment;
};

// общие сведения о машине
struct Auto
{
    string model;
    string receipt_date;
    string departure_date;
    string cost;
    AutoData Autoequipment;
};
                                                                /*
                                                                объявление всех функций
                                                                */
                                                                // проверка на наличие файла данных
bool SearchDataFile();
// проеверка файла админа
bool CreateOrDeleteAdminFile();
// запись данных в файла профиля
string WorkProfileFD(Profile user, bool rePass, bool del);
// сбор данных для пользователя
Profile GetNewProfile();
// Функции выбора в меню
void GetChoiceMenuAdmin();
void GetChoiceAutoDataFileData();
void GetChoiceAutoDataRecords();
void GetChoiceAutoDataProfile();
void GetChoiceMenuManager();
void GetChoiceMenuUser();
// функции принта меню
void PrintMenuAdmin();
void DisplayAutoDataFileData();
void DisplayAutoDataRecords();
void DisplayAutoDataProfile();
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
Auto aggregationAutoData();
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
void getAllAutoFD();
// удаление данных работника в памяти и перезапись в файл
bool deleteWirkerInMemory();
// изменение данных работника в памяти и перезапись в файл
bool changeWirkerInMemory();
//сортировка
// компаратор last name
bool compararereceipt_date(const Auto lhs, const Auto rhs);
// компаратор first name
bool compararemodel(const Auto lhs, const Auto rhs);
// компаратор departure_date
bool compararecolor(const Auto lhs, const Auto rhs);
// функция сортировки
void sortLN();
void sortFN();
void sortDep();

                                                                /*
                                                                функции вывода меню
                                                                */
void PrintMenuMain()
{
    cout << "          Меню входа\n";
    cout << "\n";
    cout << "Пожалуйста укажите пункт\n";
    cout << "1 - Вход администора\n";
    cout << "2 - Вход менеджера\n";
    cout << "3 - Вход пользователя\n";
    cout << "5 - Выход\n";
    cout << "Ваш выбор: ";
}

void PrintMenuAdmin()
{
    cout << "          Меню администратора\n";
    cout << "\n";
    cout << "Пожалуйста укажите пункт\n";
    cout << "1 - Работа с файлом данных\n";
    cout << "2 - Работа с записями в файле данных\n";
    cout << "3 - Просмотр всех записей в таблице\n";
    cout << "4 - Работа с учетными записями\n";
    cout << "5 - Выход\n";
    cout << "Ваш выбор: ";
}

void DisplayAutoDataFileData()
{
    cout << "          Меню работы с файлами данных\n";
    cout << "\n";
    cout << "Пожалуйста укажите пункт\n";
    cout << "1 - Создать файл данных сотрудников\n";
    cout << "2 - Удалить файл данных сотрудников\n";
    cout << "3 - Назад\n";
    cout << "4 - Выход\n";
    cout << "Ваш выбор: ";
}

void DisplayAutoDataRecords()
{
    cout << "          Меню работы с записями\n";
    cout << "\n";
    cout << "Пожалуйста укажите пункт\n";
    cout << "1 - Добавление записи\n";
    cout << "2 - Редактирование записи\n";
    cout << "3 - Удаление записи\n";
    cout << "4 - Просмотр всех записей в таблице\n";
    cout << "5 - Поиск записей\n";
    cout << "6 - Назад\n";
    cout << "7 - Выход\n";
    cout << "Ваш выбор: ";
}

void DisplayAutoDataProfile()
{
    cout << "          Меню работы с учетными записями\n";
    cout << "\n";
    cout << "Пожалуйста укажите пункт\n";
    cout << "1 - Добавление учетной записи\n";
    cout << "2 - Редактирование учетной записи\n";
    cout << "3 - Удаление учетной записи\n";
    cout << "4 - Смена пароля учетной записи\n";
    cout << "5 - Назад\n";
    cout << "6 - Выход\n";
    cout << "Ваш выбор: ";
}

void PrintMenuManager()
{
    cout << "          Меню менеджера\n";
    cout << "\n";
    cout << "Пожалуйста укажите пункт\n";
    cout << "1 - Добавление записи\n";
    cout << "2 - Редактирование записи\n";
    cout << "3 - Удаление записи\n";
    cout << "4 - Просмотр всех записей в таблице\n";
    cout << "5 - Поиск записей\n";
    cout << "6 - Выход\n";
    cout << "Ваш выбор: ";
}

void PrintMenuUser()
{
    cout << "          Меню пользователя\n";
    cout << "\n";
    cout << "Пожалуйста укажите пункт\n";
    cout << "1 - Просмотр всех записей в таблице\n";
    cout << "2 - Поиск записей\n";
    cout << "3 - Выход\n";
    cout << "Ваш выбор: ";
}

                                                                /*
                                                                функции работы c пользователями
                                                                */

void GetLogiAndPass(int choice)
{
    bool ok = false;
    char fileLogin[127];
    char filePass[127];
    int Profile = 0;
    int i = 1;
    Profile searchProfile;
    while (ok == false)
    {
        if (i == 1)
        {
            system("cls");
            char choiceLogin[127];
            cout << "Введите логин:\n";
            cin >> choiceLogin;
            std::ifstream openFile(choiceLogin, std::ios::in | std::ios::binary);
            if (!openFile.is_open()) // если файл не открыт
            {
                cout << "Пользователь с таким логином не найден!\n";
                int continueAnsw;
                bool okContin = false;
                while (okContin == false)
                {
                    continueAnsw = getValueInt("Продолжаем?\n1 - Да\n2 - нет\n");
                    if (continueAnsw == 1 || continueAnsw == 2)
                    {
                        okContin = true;
                    }
                    else
                    {
                        cout << "Введите одно из указанных чисел.\n" << endl;
                    }
                }
                if (continueAnsw == 2)
                {
                    cout << "Операция прервана\n" << endl;
                    system("pause");
                    exit(0);
                }
            }
            else
            {
                openFile.read((char*)&searchProfile, sizeof(Profile));
                openFile.close();
                i = 2;
            }
        }
        if (i == 2)
        {
            system("cls");
            char choicePass[127];
            cout << "Введите пароль:\n";
            cin >> choicePass;;
            if (strcmp(choicePass, searchProfile.password) == 0)
            {
                ok = true;
            }
            else
            {
                cout << "Ошибка пароля. Повторите ввод.\n"; // сообщить об этом
                int continueAnsw;
                bool okContin = false;
                while (okContin == false)
                {
                    continueAnsw = getValueInt("Продолжаем?\n1 - Да\n2 - нет\n");
                    if (continueAnsw == 1 || continueAnsw == 2)
                    {
                        okContin = true;
                    }
                    else
                    {
                        cout << "Введите одно из указанных чисел.\n" << endl;
                    }
                }
                if (continueAnsw == 2)
                {
                    cout << "Операция прервана\n" << endl;
                    system("pause");
                    exit(0);
                }
            }
        }
    }
    if (searchProfile.level == 1) { GetChoiceMenuAdmin(); }
    if (searchProfile.level == 2) { GetChoiceMenuManager(); }
    if (searchProfile.level == 3) { GetChoiceMenuUser(); }
}

// запись данных в файла профиля
string WorkProfileFD(Profile user, bool rePass, bool del)
{
    string out;
    string interString = (1, user.login);
    ofstream fs;
    if (del)
    {
        if (remove(user.login) != 0)
        {
            out = "Ошибка удаления. Попробуйте вручную.\n";
        }
        else
        {
            if (user.level == 1)
            {
                out = "Удален администратор " + interString + "\n";
            }
            if (user.level == 2)
            {
                out = "Удален менеджер " + interString + "\n";
            }
            if (user.level == 3)
            {
                out = "Удален пользователь " + interString + "\n";
            }
        }
        return out;
    }
    else
    {
        if (rePass)
        {
            fs.open(user.login, std::ios::out | std::ios::binary | ios_base::trunc);
        }
        else
        {
            fs.open(user.login, std::ios::out | std::ios::binary | ios_base::app);
        }
        fs.write((char*)&user, sizeof(Profile));
        fs.close();
        if (rePass)
        {
            if (user.level == 2)
            {
                out = "Изменен пароль администратора " + interString + "\n";
            }
            if (user.level == 2)
            {
                out = "Изменен пароль менеджера " + interString + "\n";
            }
            if (user.level == 3)
            {
                out = "Изменен пароль пользователя " + interString + "\n";
            }
        }
        else
        {
            if (user.level == 2)
            {
                out = "Создан администратор " + interString + "\n";
            }
            if (user.level == 2)
            {
                out = "Создан менеджер " + interString + "\n";
            }
            if (user.level == 3)
            {
                out = "Создан пользователь " + interString + "\n";
            }
        }
        return out;
    }

}



// сбор данных для пользователя
Profile GetNewProfile()
{
    bool ok = false;
    Profile fileUser;
    cout << "Введите имя объекта:\n";
    cin >> fileUser.login;
    cout << "Введите пароль:\n";
    cin >> fileUser.password;
    int i = 1;
    while (true)
    {
        if (i > 1)
        {
            cout << "Ошибка. Повторите ввод. Варианты для выбора:\n1 - Администратор\n2 - Менеджер\n3 - Пользователь\nВаш выбор:\n";
        }
        else
        {
            cout << "Введите уровень доступа:\n1 - Администратор\n2 - Менеджер\n3 - Пользователь\nВаш выбор:\n";
        }

        cin >> fileUser.level;
        if (fileUser.level == 1 || fileUser.level == 2 || fileUser.level == 3)
        {
            break;
        }
    }
    return fileUser;
}

                                                                /*
                                                                    функции получения значения с клавиатуры
                                                                */

int getValueInt(string mess)
{
    while (true)
    {
        cout << mess + "\n";
        int a;
        std::cin >> a;

        if (std::cin.fail())
        {
            std::cin.clear(); 
            std::cin.ignore(32767, '\n');
        }
        else 
            return a;
    }
}

string getValueStr(string mess)
{
    while (true) 
    {
        cout << mess << endl;
        std::string userStr;
        std::getline(std::cin >> std::ws, userStr);
        return userStr;
    }
}

                                                                /*
                                                                    функции работы с файлом базы данных
                                                                */


// -------------------------------------------------====
//         сортировка
// -------------------------------------------------====
// компараторы
bool compararereceipt_date(const Auto lhs, const Auto rhs) {
    if (varSort == 1)
    {
        return lhs.receipt_date > rhs.receipt_date;
    }
    else
    {
        return lhs.receipt_date < rhs.receipt_date;
    }

}
bool compararemodel(const Auto lhs, const Auto rhs) {
    if (varSort == 1)
    {
        return lhs.model > rhs.model;
    }
    else
    {
        return lhs.model < rhs.model;
    }
}
bool compararecolor(const Auto lhs, const Auto rhs) {
    if (varSort == 1)
    {
        return lhs.Autoequipment.color > rhs.Autoequipment.color;
    }
    else
    {
        return lhs.Autoequipment.color < rhs.Autoequipment.color;
    }

}
// сортировка по фамилии
void sortLN() {
    sort( allAuto.begin(),  allAuto.end(), compararereceipt_date);
    if (varSort == 1)
    {
        varSort = 2;
    }
    else
    {
        varSort = 1;
    }
}
// сортировка по имени
void sortFN() {
    sort( allAuto.begin(),  allAuto.end(), compararemodel);
    if (varSort == 1)
    {
        varSort = 2;
    }
    else
    {
        varSort = 1;
    }
}
// сортировка по отделу
void sortDep() {
    sort( allAuto.begin(),  allAuto.end(), compararecolor);
    if (varSort == 1)
    {
        varSort = 2;
    }
    else
    {
        varSort = 1;
    }
}

// делитель строки
vector<string> split(const string& s, char delim) {
    vector<string> result;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
}

// запись данных нового работника в файл данных (перезапись файла)
bool creatRecordInFD(bool atMemory)
{
    if (atMemory)
    {
        vector<string> allString;

        for (Auto wk :  allAuto)
        {
            string outStrInterim = "";
            outStrInterim = outStrInterim + "#" + wk.receipt_date
                + "#" + wk.model
                + "#" + wk.departure_date
                + "#" + wk.cost
                + "#" + wk.educationAuto.nameEdComp
                + "#" + wk.educationAuto.spacialization
                + "#" + to_string(wk.educationAuto.yearEndEducation)
                + "#" + wk.martStatus
                + "#" + wk.homeTelNumber
                + "#" + wk.Autoequipment.body
                + "#" + wk.Autoequipment.color
                + "#" + wk.Autoequipment.equipment
                + "#" + wk.Autoequipment.workTelNumber
                + "#" + wk.Autoequipment.dateStopWork;
            allString.push_back(outStrInterim);
        }
        std::ofstream out("dataFile.txt", std::ios::trunc);
        if (out.is_open())
        {
            for (string strInFile : allString)
            {
                out << strInFile << std::endl;
            }

        }
        out.close();
        return true;
    }
    else
    {
        Auto newAuto = aggregationAutoData();
        string outStr = "";
        outStr = outStr + "#" + newAuto.receipt_date
            + "#" + newAuto.model
            + "#" + newAuto.departure_date
            + "#" + newAuto.cost
            + "#" + newAuto.educationAuto.nameEdComp
            + "#" + newAuto.educationAuto.spacialization
            + "#" + to_string(newAuto.educationAuto.yearEndEducation)
            + "#" + newAuto.martStatus
            + "#" + newAuto.homeTelNumber
            + "#" + newAuto.Autoequipment.body
            + "#" + newAuto.Autoequipment.color
            + "#" + newAuto.Autoequipment.equipment
            + "#" + newAuto.Autoequipment.workTelNumber
            + "#" + newAuto.Autoequipment.dateStopWork;
        std::ofstream out("dataFile.txt", std::ios::app);
        if (out.is_open())
        {
            out << outStr << std::endl;
        }
        out.close();
        return true;
    }

}

// принт таблицы файла данных
void printTable()
{
    if ( allAuto.size() > 0)
    {
        Table Autos;
        Autos.add_row(Row_t{ "Фамилия", "Имя", "Отчество", "Дата рождения", "Сем. положение \n" "Дом. телефон",
                                "Образование:\n- оконченное УО;\n- специализация\n- год окончания", "Дата приёма",
                                "Сведения о найме:\n- отдел,\n- должность,\n- рабочий телефон", "Дата увольнения" });
        for (size_t i = 0; i <  allAuto.size(); i++)
        {
            Autos.add_row(Row_t{  allAuto[i].receipt_date,  allAuto[i].model,  allAuto[i].departure_date,  allAuto[i].cost,
                                     allAuto[i].martStatus + "\n" +  allAuto[i].homeTelNumber,  allAuto[i].educationAuto.nameEdComp + "\n" +  allAuto[i].educationAuto.spacialization + "\n" +
                                    to_string( allAuto[i].educationAuto.yearEndEducation) ,  allAuto[i].Autoequipment.body,  allAuto[i].Autoequipment.color + "\n" +
                                     allAuto[i].Autoequipment.equipment + "\n" +  allAuto[i].Autoequipment.workTelNumber,  allAuto[i].Autoequipment.dateStopWork });
        }
        Autos.add_row(Row_t{ "Итого сотрудников: ", to_string( allAuto.size()), "", "", "", "", "", "", "" });
        Autos.column(0).format().font_align(FontAlign::center);
        Autos.column(1).format().font_align(FontAlign::center);
        Autos.column(2).format().font_align(FontAlign::center);
        Autos.column(3).format().font_align(FontAlign::center);
        Autos.column(6).format().font_align(FontAlign::center);
        Autos.column(8).format().font_align(FontAlign::center);
        int a =  allAuto.size() + 1;
        for (size_t i = 0; i < 9; ++i) {
            Autos[0][i].format().font_color(Color::yellow).font_style({ FontStyle::bold });
            Autos[a][i].format().font_color(Color::green).font_style({ FontStyle::bold });
        }
        std::cout << Autos << "\n\n";
    }
    else
    {
        cout << "                                               " << endl;
        cout << "          Записей не обнаружено.               " << endl;
        cout << "                                               " << endl;
    }
}

// принт таблицы файла данных сокращенно
void printTableAbbr()
{
    if ( allAuto.size() > 0)
    {
        Table Autos;
        Autos.add_row(Row_t{ "Фамилия", "Имя", "Отчество", "Дата рождения", "Сем. положение \n" "Дом. телефон",
                                "Сведения о найме:\n- отдел,\n- должность,\n- рабочий телефон" });
        for (size_t i = 0; i <  allAuto.size(); i++)
        {
            Autos.add_row(Row_t{  allAuto[i].receipt_date,  allAuto[i].model,  allAuto[i].departure_date,  allAuto[i].cost,
                                     allAuto[i].martStatus + "\n" +  allAuto[i].homeTelNumber,   allAuto[i].Autoequipment.color + "\n" +
                                     allAuto[i].Autoequipment.equipment + "\n" +  allAuto[i].Autoequipment.workTelNumber });
        }
        Autos.add_row(Row_t{ "Итого сотрудников: ", to_string( allAuto.size()), "", "", "",  "" });
        Autos.column(0).format().font_align(FontAlign::center);
        Autos.column(1).format().font_align(FontAlign::center);
        Autos.column(2).format().font_align(FontAlign::center);
        Autos.column(3).format().font_align(FontAlign::center);
        int a =  allAuto.size() + 1;
        for (size_t i = 0; i < 6; ++i) {
            Autos[0][i].format().font_color(Color::yellow).font_style({ FontStyle::bold });
            Autos[a][i].format().font_color(Color::green).font_style({ FontStyle::bold });
        }
        std::cout << Autos << "\n\n";
    }
    else
    {
        cout << "                                               " << endl;
        cout << "          Записей не обнаружено.               " << endl;
        cout << "                                               " << endl;
    }
}

// функция поиска в строке
bool search(string query, string fundStr) {
    string queryDest;
    queryDest.resize(query.size());
    string fundStrDest;
    fundStrDest.resize(fundStr.size());
    transform(query.begin(), query.end(), queryDest.begin(), ::tolower);
    transform(fundStr.begin(), fundStr.end(), fundStrDest.begin(), ::tolower);
    size_t pos = fundStrDest.find(queryDest);
    if (pos != string::npos)
        return true;
    else
        return false;
}

// поиск работника и принт таблицы
void searchAndPrintTable(int change)
{
    if ( allAuto.size() > 0)
    {
        bool ok = false;
        string query;
        vector<Auto> searchAutos;
        int continueAnsw;
        switch (change)
        {
        case 1:
            query = getValueStr("Введите фамилию работника");
            break;
        case 2:
            query = getValueStr("Введите имя работника");
            break;
        case 3:
            query = getValueStr("Введите отчетсво работника");
            break;
        case 4:
            query = getValueStr("Введите отдел");
            break;
        }
        for (size_t i = 0; i <  allAuto.size(); i++)
        {
            if (change == 1 && search(query,  allAuto[i].receipt_date))
            {
                searchAutos.push_back( allAuto[i]);
            }
            if (change == 2 && search(query,  allAuto[i].model))
            {
                searchAutos.push_back( allAuto[i]);
            }
            if (change == 3 && search(query,  allAuto[i].departure_date))
            {
                searchAutos.push_back( allAuto[i]);
            }
            if (change == 4 && search(query,  allAuto[i].Autoequipment.color))
            {
                searchAutos.push_back( allAuto[i]);
            }
        }
        if (searchAutos.size() > 0)
        {
            Table Autos;
            Autos.add_row(Row_t{ "Фамилия", "Имя", "Отчество", "Дата рождения", "Сем. положение \n" "Дом. телефон",
                                    "Образование:\n- оконченное УО;\n- специализация\n- год окончания", "Дата приёма",
                                    "Сведения о найме:\n- отдел,\n- должность,\n- рабочий телефон", "Дата увольнения" });
            for (size_t i = 0; i < searchAutos.size(); i++)
            {
                Autos.add_row(Row_t{ searchAutos[i].receipt_date, searchAutos[i].model, searchAutos[i].departure_date, searchAutos[i].cost, 
                                        searchAutos[i].Autoequipment.body, searchAutos[i].Autoequipment.color + "\n" +
                                        searchAutos[i].Autoequipment.equipment });
            }
            Autos.add_row(Row_t{ "Найдено сотрудников: ", to_string(searchAutos.size()), "", "", "", "", "", "", "" });
            Autos.column(0).format().font_align(FontAlign::center);
            Autos.column(1).format().font_align(FontAlign::center);
            Autos.column(2).format().font_align(FontAlign::center);
            Autos.column(3).format().font_align(FontAlign::center);
            Autos.column(6).format().font_align(FontAlign::center);
            Autos.column(8).format().font_align(FontAlign::center);
            int a = searchAutos.size() + 1;
            for (size_t i = 0; i < 9; ++i) {
                Autos[0][i].format().font_color(Color::yellow).font_style({ FontStyle::bold });
                Autos[a][i].format().font_color(Color::green).font_style({ FontStyle::bold });
            }
            std::cout << Autos << "\n\n";
            searchAutos.clear();
        }
        else
        {
            cout << "                                               " << endl;
            cout << "          Записей не обнаружено.               " << endl;
            cout << "                                               " << endl;
        }
    }
    else
    {
        cout << "                                               " << endl;
        cout << "          Записей не обнаружено.               " << endl;
        cout << "                                               " << endl;
    }
}

// получение данных работников в память
void getAllAutoFD()
{
    int amountOfAuto = 0;
    ifstream fin("dataFile.txt", ios_base::in);
    string line;
    vector<string> strs;
    if (!fin.is_open())
    {
        cout << "not" << endl;
        availabilityAuto = false;
    }
    else
    {
         allAuto.clear();
        while (getline(fin, line))
        {
            amountOfAuto++;
            strs.push_back(line);
        }
        for (string u : strs)
        {
            vector<string> AutoVect = split(u, '#');
            Auto interimAuto;
            for (size_t i = 0; i < AutoVect.size(); i++)
            {
                switch (i)
                {
                case 1:
                    interimAuto.receipt_date = AutoVect[i];
                    break;
                case 2:
                    interimAuto.model = AutoVect[i];
                    break;
                case 3:
                    interimAuto.departure_date = AutoVect[i];
                    break;
                case 4:
                    interimAuto.cost = AutoVect[i];
                    break;
                case 5:
                    interimAuto.Autoequipment.body = AutoVect[i];
                    break;
                case 6:
                    interimAuto.Autoequipment.color = AutoVect[i];
                    break;
                case 7:
                    interimAuto.Autoequipment.equipment = AutoVect[i];
                    break;
                }
            }
             allAuto.push_back(interimAuto);
            if ( allAuto.size() > 0)
            {
                availabilityAuto = true;
            }
            else
            {
                availabilityAuto = false;
            }
        }
    }
}

// изменение данных работника в памяти и перезапись в файл
bool changeWirkerInMemory()
{
    string searchAutoLN = getValueStr("Введите фамилию работника");
    string searchAutoFN = getValueStr("Введите имя работника");
    int indexAuto = -1;
    for (size_t i = 0; i <  allAuto.size(); i++)
    {
        if ( allAuto[i].model == searchAutoFN)
        {
            if ( allAuto[i].receipt_date == searchAutoLN)
            {
                indexAuto = i;
            }
        }

    }
    if (indexAuto < 0)
    {
        return false;
    }
    Auto newAuto = aggregationAutoData();
     allAuto[indexAuto] = newAuto;
    if (creatRecordInFD(true))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// удаление данных работника в памяти и перезапись в файл
bool deleteWirkerInMemory()
{
    string searchAutoLN = getValueStr("Введите фамилию работника");
    string searchAutoFN = getValueStr("Введите имя работника");
    int indexAuto = -1;
    Auto iter =  allAuto.cbegin();
    for (size_t i = 0; i <  allAuto.size(); i++)
    {
        if ( allAuto[i].model == searchAutoFN)
        {
            if ( allAuto[i].receipt_date == searchAutoLN)
            {
                indexAuto = i;
            }
        }

    }
    if (indexAuto < 0)
    {
        return false;
    }
     allAuto.erase(iter + indexAuto);
    if (creatRecordInFD(true))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// сбор сведений по авто
Auto aggregationAutoData() {
    Auto newAuto;
    newAuto.model = getValueStr("Введите имя");
    newAuto.receipt_date = getValueStr("Введите фамилию");
    newAuto.departure_date = getValueStr("Введите отчество");
    newAuto.cost = getValueStr("Введите дату рождения в формате мм-дд-гггг : ");
    char* intStr;
    string intStrLine = getValueStr("Введите номер в формате 121234567");
    intStr = &intStrLine[0];
    string intStrEnd = "";
    intStrEnd = intStrEnd + "+375(" + intStr[0] + intStr[1] + ")" + intStr[2] + intStr[3] + intStr[4] + "-" + intStr[5] + intStr[6] + "-" + intStr[7] + intStr[8];
    newAuto.Autoequipment.body = getValueStr("Введите дату прриема на работу в формате мм-дд-гггг : ");
    newAuto.Autoequipment.color = getValueStr("Введите название отдела : ");
    newAuto.Autoequipment.equipment = getValueStr("Введите должность : ");
    char* intStr2;
    string intStrLine2 = getValueStr("Введите номер в формате 121234567");
    intStr2 = &intStrLine2[0];
    string intStrEnd2 = "";
    intStrEnd2 = intStrEnd2 + "+375(" + intStr2[0] + intStr2[1] + ")" + intStr2[2] + intStr2[3] + intStr2[4] + "-" + intStr2[5] + intStr2[6] + "-" + intStr2[7] + intStr2[8];
    return newAuto;
}

// проверка на наличие файла данных
bool SearchDataFile()
{
    ifstream fin("dataFile.txt", ios_base::in);
    if (!fin.is_open())
    {
        return false;
    }
    else
    {
        fin.close();
        if (!availabilityAuto)
        {
            getAllAutoFD();
        }
        return true;
    }
}

// создание и удаление файла данных
bool CreateOrDeleteFD(bool createOrDelete)
{
    if (createOrDelete)
    {
        ofstream fout("dataFile.txt", ios_base::app);
        fout.close();
        return true;
    }
    else
    {
        if (remove("dataFile.txt") != 0)
        {
            return false;
        }
        else
        {
             allAuto.clear();
            return true;
        }
    }
}

// проеверка файла админа
bool CreateOrDeleteAdminFile()
{
    ifstream fin("admin", ios_base::in);
    if (!fin.is_open())
    {
        return false;
    }
    else
    {
        fin.close();
        return true;
    }
}

/*
функции работы меню
*/

void GetChoiceMenuAdmin()
{
    system("cls");
    bool file = SearchDataFile();
    bool ok = false;
    int continueAnsw;
    if (!SearchDataFile() && !choiceCreateFD)
    {
        cout << "Базы автомобилей не существует" << endl;
        bool ok = false;
        while (ok == false)
        {
            int continueAnsw = getValueInt("Создать файл данных? \n1 - Да\n2 - нет\n");
            if (continueAnsw == 1 || continueAnsw == 2)
            {
                if (continueAnsw == 1)
                {
                    if (CreateOrDeleteFD(true))
                    {
                        cout << "Файл данных успешно создан" << endl;
                        fileCreate = true;
                        system("pause");
                        GetChoiceMenuAdmin();
                    }
                    else
                    {
                        cout << "Ошибка при создании. Повторите попытку позже." << endl;
                        fileCreate = false;
                        system("pause");
                        GetChoiceMenuAdmin();
                    }
                    ok = true;
                }
                if (continueAnsw == 2)
                {
                    cout << "Файл не будет создан." << endl;
                    choiceCreateFD = true;
                    fileCreate = false;
                    system("pause");
                    GetChoiceMenuAdmin();
                }
            }
            else
            {
                cout << "Введите одно из указанных чисел.\n << endl";
            }
        }
    }
    else
    {
        if (!fileCreate)
        {
            cout << "Базы автомобилей не существует" << endl;
            PrintMenuAdmin();
            int choice = getValueInt("Ваш выбор:");
            switch (choice)
            {
            case 1:
                GetChoiceAutoDataFileData();
                break;
            case 2:
                GetChoiceAutoDataProfile();
                break;
            case 3:
                cout << "Выход!";
                exit(0);
            default:
                GetChoiceMenuAdmin();
                break;
            }
        
        }
        else
        {
            PrintMenuAdmin();
            int choice = getValueInt("Ваш выбор:");
            switch (choice)
            {
            case 1:
                GetChoiceAutoDataFileData();
                break;
            case 2:
                GetChoiceAutoDataRecords();
                break;
            case 3:
                system("cls");
                cout << "Просмотр всех записей в таблице" << endl;
                printTable();
                if (availabilityAuto) {
                    while (ok == false)
                    {
                        continueAnsw = getValueInt("Ваш действия?\n1 - Сортировка по имени\n2 - Сортировка по фамиии\n3 - Сортировка по отделу\n4 - Назад\n");
                        if (continueAnsw == 1 || continueAnsw == 2 || continueAnsw == 3 || continueAnsw == 4)
                        {
                            switch (continueAnsw)
                            {
                            case 1:
                                system("cls");
                                cout << "Сортировка по имени\n" << endl;
                                sortFN();
                                printTable();
                                continue;
                            case 2:
                                system("cls");
                                cout << "Сортировка по фамиии\n" << endl;
                                sortLN();
                                printTable();
                                continue;
                            case 3:
                                system("cls");
                                cout << "Сортировка по отделу\n" << endl;
                                sortDep();
                                printTable();
                                continue;
                            case 4:
                                GetChoiceMenuAdmin();
                                break;
                            default:
                                GetChoiceMenuAdmin();
                                break;
                            }
                        }
                        else
                        {
                            cout << "Введите одно из указанных чисел.\n" << endl;
                        }
                    }
                }
                else
                {
                    system("pause");
                    GetChoiceMenuAdmin();
                }
                break;
            case 4:
                GetChoiceAutoDataProfile();
                break;
            case 5:
                cout << "Выход!";
                exit(0);
            default:
                GetChoiceMenuAdmin();
                break;
            }
        }
        
    }
   
}

void GetChoiceAutoDataFileData()
{
    system("cls");
    if (!fileCreate)
    {
        cout << "Базы автомобилей не существует" << endl;
    }
    DisplayAutoDataFileData();
    int choice = getValueInt("Ваш выбор:");
    switch (choice)
    {
    case 1:
        system("cls");
        cout << "Создать базу автомобилей?" << endl;
        if (fileCreate)
        {
            cout << "База данных существует" << endl;
            system("pause");
            GetChoiceAutoDataFileData();
        }
        if (CreateOrDeleteFD(true))
        {
            cout << "База данных успешно создана" << endl;
            fileCreate = true;
            system("pause");
            GetChoiceAutoDataFileData();
        }
        else
        {
            cout << "Ошибка при создании. Повторите попытку позже." << endl;
            fileCreate = false;
            system("pause");
            GetChoiceAutoDataFileData();
        }
        break;
    case 2:
        system("cls");
        cout << "Удалить базу данных автомобилей" << endl;
        if (CreateOrDeleteFD(false))
        {
            cout << "База данных успешно удален" << endl;
            choiceCreateFD = true;
            fileCreate = false;
            system("pause");
            GetChoiceAutoDataFileData();
        }
        else
        {
            cout << "Ошибка при удалении. Повторите попытку позже." << endl;
            fileCreate = true;
            system("pause");
            GetChoiceAutoDataFileData();
        }
        break;
    case 3:
        GetChoiceMenuAdmin();
        break;
    case 4:
        cout << "Выход!";
        exit(0);
    default:
        GetChoiceAutoDataFileData();
        break;
    }
}

void GetChoiceAutoDataRecords()
{
    system("cls");
    DisplayAutoDataRecords();
    int choice = getValueInt("Ваш выбор:");
    bool ok = false;
    int continueAnsw;
    switch (choice)
    {
    case 1:
        system("cls");
        cout << "Добавление записи" << endl;
        if (creatRecordInFD(false))
        {
            getAllAutoFD();
            cout << "Запись успешно добавлена" << endl;
            getAllAutoFD();
            system("pause");
            GetChoiceAutoDataRecords();
        }
        else
        {
            cout << "Запись успешно добавлена" << endl;
            system("pause");
            GetChoiceAutoDataRecords();
        }
        break;
    case 2:
        system("cls");
        cout << "Редактирование записи" << endl;
        if (changeWirkerInMemory())
        {
            cout << "Данные работника изменены" << endl;
            system("pause");
            GetChoiceAutoDataRecords();
        }
        else
        {
            cout << "Ошибка. Данные не изменены." << endl;
            system("pause");
            GetChoiceAutoDataRecords();
        }
        break;
    case 3:
        system("cls");
        cout << "Удаление записи" << endl;
        if (deleteWirkerInMemory())
        {
            cout << "Работник удалён." << endl;
            system("pause");
            GetChoiceAutoDataRecords();
        }
        else
        {
            cout << "Ошибка. Данные не изменены." << endl;
            system("pause");
            GetChoiceAutoDataRecords();
        }
        break;
    case 4:
        system("cls");
        cout << "Просмотр всех записей в таблице" << endl;
        printTable();
        if (availabilityAuto) {
            while (ok == false)
            {
                continueAnsw = getValueInt("Ваш действия?\n1 - Сортировка по имени\n2 - Сортировка по фамиии\n3 - Сортировка по отделу\n4 - Назад\n");
                if (continueAnsw == 1 || continueAnsw == 2 || continueAnsw == 3 || continueAnsw == 4)
                {
                    switch (continueAnsw)
                    {
                    case 1:
                        system("cls");
                        cout << "Сортировка по имени\n" << endl;
                        sortFN();
                        printTable();
                        continue;
                    case 2:
                        system("cls");
                        cout << "Сортировка по фамиии\n" << endl;
                        sortLN();
                        printTable();
                        continue;
                    case 3:
                        system("cls");
                        cout << "Сортировка по отделу\n" << endl;
                        sortDep();
                        printTable();
                        continue;
                    case 4:
                        GetChoiceAutoDataRecords();
                        break;
                    default:
                        GetChoiceAutoDataRecords();
                        break;
                    }
                }
                else
                {
                    cout << "Введите одно из указанных чисел.\n" << endl;
                }
            }
        }
        else
        {
            system("pause");
            GetChoiceAutoDataRecords();
        }
        break;
    case 5:
        system("cls");
        cout << "  Поиск записей" << endl;
        cout << "и вывод в таблицу" << endl;
        while (ok == false)
        {
            continueAnsw = getValueInt("\nВарианты поиска?\n1 - по фамилии\n2 - по имени\n3 - по отчетсву\n4 - по отделу\n5 - Назад\n6 - Выход\n");
            if (continueAnsw == 1 || continueAnsw == 2 || continueAnsw == 3 || continueAnsw == 4 || continueAnsw == 5)
            {
                ok = true;
            }
            else
            {
                cout << "Введите одно из указанных чисел.\n";
            }
        }
        if (continueAnsw == 5)
        {
            GetChoiceMenuAdmin();
        }
        if (continueAnsw == 6)
        {
            cout << "Выход!";
            exit(0);
        }
        searchAndPrintTable(continueAnsw);
        system("pause");
        GetChoiceAutoDataRecords();
        break;
    case 7:
        GetChoiceMenuAdmin();
        break;
    case 8:
        cout << "Выход!";
        exit(0);
    default:
        GetChoiceAutoDataRecords();
        break;
    }
}

void GetChoiceAutoDataProfile()
{
    system("cls");
    if (!fileCreate)
    {
        cout << "Базы автомобилей не существует" << endl;
    }
    DisplayAutoDataProfile();
    int choice = getValueInt("Ваш выбор:");
    Profile newUser;
    Profile interimProfile;
    Profile fileUser;
    string out;
    char oldUserName[127];
    int continueAnsw;
    bool ok = false;
    ifstream fin;
    switch (choice)   
    {
    case 1:
        system("cls");
        cout << "Добавление новой учетной записи" << endl;
        newUser = GetNewProfileData();
        fin.open(newUser.login, ios_base::in | std::ios::binary);
        if (!fin.is_open()) // если файл не открыт
        {
            while (ok == false)
            {
                continueAnsw = getValueInt("Продолжаем?\n1 - Да\n2 - нет\n");
                if (continueAnsw == 1 || continueAnsw == 2)
                {
                    ok = true;
                }
                else
                {
                    cout << "Введите одно из указанных чисел.\n" << endl;
                }
            }
            if (continueAnsw == 1)
            {
                out = WorkProfileFD(newUser, false, false);
                cout << out;
                system("pause");
                GetChoiceAutoDataProfile();
            }
            if (continueAnsw == 2)
            {
                cout << "Операция прервана\n" << endl;
                GetChoiceAutoDataProfile();
            }
            ok = false;
            break;
        }
        else
        {
            fin.close();
            cout << "Пользователь с таким логином существует.\n";
            system("pause");
            GetChoiceAutoDataProfile();
            ok = false;
            break;
        }
        
    case 2:
        system("cls");
        cout << "Редактирование учетной записи" << endl;
        cout << "\n";
        cout << "Введите имя учетной записи, которую желаете изменить:\n";
        cin >> newUser.login;
        fin.open(newUser.login, ios_base::in);
        if (!fin.is_open())
        {
            cout << "Пользователь с таким логином не найден.\n";
            system("pause");
            GetChoiceAutoDataProfile();
            ok = false;
            break;
        }
        else
        {
            fin.close();
            ok = false;
            while (ok == false)
            {
                continueAnsw = getValueInt("Продолжаем?\n1 - Да\n2 - нет\n");
                if (continueAnsw == 1 || continueAnsw == 2)
                {
                    ok = true;
                }
                else
                {
                    cout << "Введите одно из указанных чисел.\n";
                }
            }
            if (continueAnsw == 1)
            {
                cout << "Введите новые данные учетной записи\n";
                interimProfile = GetNewProfileData();
                out = WorkProfileFD(interimProfile, true, false);
                cout << "Учетная запись изменена\n";
                if (strcmp(newUser.login, interimProfile.login) != 0)
                {
                    WorkProfileFD(newUser, false, true);
                }
                system("pause");
                GetChoiceAutoDataProfile();
            }
            if (continueAnsw == 2)
            {
                cout << "Операция прервана\n";
                GetChoiceAutoDataProfile();
            }
            ok = false;
            break;
        }
    case 3:
        system("cls");
        cout << "Удаление учетной записи" << endl;
        ok = false;
        while (ok == false)
        {
            
            cout << "Введите логин удаляемого объекта\n" << endl;
            cin >> newUser.login;
            ifstream finn(newUser.login, ios_base::in);
            if (!finn.is_open())
            {
                cout << "Пользователь с таким логином не найден!\n";
                system("pause");
                GetChoiceAutoDataProfile();
                break;
            }
            else
            {
                finn.close();
                ok = true;
            }
        }
        ok = false;
        while (ok == false)
        {
            continueAnsw = getValueInt("\nПродолжаем?\n1 - Да\n2 - нет\n");
            if (continueAnsw == 1 || continueAnsw == 2)
            {
                ok = true;
            }
            else
            {
                cout << "Введите одно из указанных чисел.\n";
            }
        }
        if (continueAnsw == 1)
        {
            out = WorkProfileFD(newUser, false, true);
            cout << out;
            system("pause");
            GetChoiceAutoDataProfile();
        }
        if (continueAnsw == 2)
        {
            cout << "Операция прервана\n";
            GetChoiceAutoDataProfile();
        }

        break;
    case 4:
        system("cls");
        cout << "Смена пароля учетной записи" << endl;
        while (ok == false)
        {
            system("cls");
            char choiceLogin[127];
            cout << "Введите логин изменяемого объекта:\n";
            cin >> choiceLogin;
            ifstream openFile(choiceLogin, std::ios::in | std::ios::binary | std::ios::app);
            if (!openFile.is_open())
            {
                cout << "Пользователь с таким логином не найден!\n";
            }
            else
            {
                openFile.read((char*)&fileUser, sizeof(Profile));
                openFile.close();
                ok = true;
            }
        }
        cout << "Введите новый пароль:\n";
        cin >> fileUser.password;
        out = WorkProfileFD(fileUser, true, false);
        cout << "пароль изменен \n";
        system("pause");
        GetChoiceAutoDataProfile();
        break;
    case 5:
        GetChoiceMenuAdmin();
        break;
    case 6:
        cout << "Выход!\n";
        exit(0);
    default:
        GetChoiceAutoDataProfile();
        break;
    }
}

void GetChoiceMenuManager()
{
    system("cls");
    if (!fileCreate)
    {
        cout << "Базы автомобилей не существует" << endl;
        system("pause");
        cout << "Выход!\n";
        exit(0);
    }
    PrintMenuManager();
    int choice = getValueInt("Ваш выбор:");
    bool ok = false;
    int continueAnsw;
    switch (choice)
    {
    case 1:
        system("cls");
        cout << "Добавление записи" << endl;
        if (creatRecordInFD(false))
        {
            getAllAutoFD();
            cout << "Запись успешно добавлена" << endl;
            getAllAutoFD();
            system("pause");
            GetChoiceMenuManager();
        }
        else
        {
            cout << "Запись успешно добавлена" << endl;
            system("pause");
            GetChoiceMenuManager();
        }
        break;
    case 2:
        system("cls");
        cout << "Редактирование записи" << endl;
        if (changeWirkerInMemory())
        {
            cout << "Данные работника изменены" << endl;
            system("pause");
            GetChoiceMenuManager();
        }
        else
        {
            cout << "Ошибка. Данные не изменены." << endl;
            system("pause");
            GetChoiceMenuManager();
        }
        break;
    case 3:
        system("cls");
        cout << "Удаление записи" << endl;
        if (deleteWirkerInMemory())
        {
            cout << "Работник удалён." << endl;
            system("pause");
            GetChoiceMenuManager();
        }
        else
        {
            cout << "Ошибка. Данные не изменены." << endl;
            system("pause");
            GetChoiceMenuManager();
        }
        break;
    case 4:
        system("cls");
        cout << "Просмотр всех записей в таблице" << endl;
        printTable();
        if (availabilityAuto) {
            while (ok == false)
            {
                continueAnsw = getValueInt("Ваш действия?\n1 - Сортировка по имени\n2 - Сортировка по фамиии\n3 - Сортировка по отделу\n4 - Назад\n");
                if (continueAnsw == 1 || continueAnsw == 2 || continueAnsw == 3 || continueAnsw == 4)
                {
                    switch (continueAnsw)
                    {
                    case 1:
                        system("cls");
                        cout << "Сортировка по имени\n" << endl;
                        sortFN();
                        printTable();
                        continue;
                    case 2:
                        system("cls");
                        cout << "Сортировка по фамиии\n" << endl;
                        sortLN();
                        printTable();
                        continue;
                    case 3:
                        system("cls");
                        cout << "Сортировка по отделу\n" << endl;
                        sortDep();
                        printTable();
                        continue;
                    case 4:
                        GetChoiceMenuManager();
                        break;
                    default:
                        GetChoiceMenuManager();
                        break;
                    }
                }
                else
                {
                    cout << "Введите одно из указанных чисел.\n" << endl;
                }
            }
        }
        else
        {
            system("pause");
            GetChoiceMenuManager();
        }
        break;
    case 5:
        system("cls");
        cout << "  Поиск записей" << endl;
        cout << "и вывод в таблицу" << endl;
        while (ok == false)
        {
            continueAnsw = getValueInt("\nВарианты поиска?\n1 - по фамилии\n2 - по имени\n3 - по отчетсву\n4 - по отделу\n5 - Назад\n6 - Выход\n");
            if (continueAnsw == 1 || continueAnsw == 2 || continueAnsw == 3 || continueAnsw == 4 || continueAnsw == 5)
            {
                ok = true;
            }
            else
            {
                cout << "Введите одно из указанных чисел.\n";
            }
        }
        if (continueAnsw == 5)
        {
            GetChoiceMenuManager();
        }
        if (continueAnsw == 6)
        {
            cout << "Выход!";
            exit(0);
        }
        searchAndPrintTable(continueAnsw);
        system("pause");
        GetChoiceMenuManager();
        break;
    case 7:
        cout << "Выход!";
        exit(0);
    default:
        GetChoiceMenuManager();
        break;
    }
}

void GetChoiceMenuUser()
{
    system("cls");
    if (!fileCreate || !availabilityAuto)
    {
        cout << "Базы автомобилей не существует" << endl;
        cout << "      или записей не обнаружено" << endl;
        system("pause");
        cout << "Выход!\n";
        exit(0);
    }
    PrintMenuUser();
    int choice = getValueInt("Ваш выбор:");
    bool ok = false;
    int continueAnsw;
    switch (choice)
    {
    case 1:
        system("cls");
        cout << "Просмотр всех записей в таблице" << endl;
        printTable();
        if (availabilityAuto) {
            while (ok == false)
            {
                continueAnsw = getValueInt("Ваш действия?\n1 - Сортировка по имени\n2 - Сортировка по фамиии\n3 - Сортировка по отделу\n4 - Назад\n");
                if (continueAnsw == 1 || continueAnsw == 2 || continueAnsw == 3 || continueAnsw == 4)
                {
                    switch (continueAnsw)
                    {
                    case 1:
                        system("cls");
                        cout << "Сортировка по имени\n" << endl;
                        sortFN();
                        printTable();
                        continue;
                    case 2:
                        system("cls");
                        cout << "Сортировка по фамиии\n" << endl;
                        sortLN();
                        printTable();
                        continue;
                    case 3:
                        system("cls");
                        cout << "Сортировка по отделу\n" << endl;
                        sortDep();
                        printTable();
                        continue;
                    case 4:
                        GetChoiceMenuUser();
                        break;
                    default:
                        GetChoiceMenuUser();
                        break;
                    }
                }
                else
                {
                    cout << "Введите одно из указанных чисел.\n" << endl;
                }
            }
        }
        else
        {
            system("pause");
            GetChoiceMenuUser();
        }
        break;
    case 2:
        system("cls");
        cout << "   Поиск записей" << endl;
        cout << "и вывод в таблицу" << endl;
        while (ok == false)
        {
            continueAnsw = getValueInt("\nВарианты поиска?\n1 - по фамилии\n2 - по имени\n3 - по отчетсву\n4 - по отделу\n5 - Назад\n6 - Выход\n");
            if (continueAnsw == 1 || continueAnsw == 2 || continueAnsw == 3 || continueAnsw == 4 || continueAnsw == 5)
            {
                ok = true;
            }
            else
            {
                cout << "Введите одно из указанных чисел.\n";
            }
        }
        if (continueAnsw == 5)
        {
            GetChoiceMenuUser();
        }
        if (continueAnsw == 6)
        {
            cout << "Выход!";
            exit(0);
        }
        searchAndPrintTable(continueAnsw);
        system("pause");
        GetChoiceMenuUser();
        break;
    case 4:
        cout << "Выход!";
        exit(0);
    default:
        GetChoiceMenuUser();
        break;
    }

}

int main(int argc, char* argv[])
{
    // установка локали
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // отображение меню выбора пользователя
    PrintMenuMain();
    // нужные переменные
    int continueAnsw;
    bool ok = false;
    string out;
    Profile searchUD;
    bool okTwo = false;
    char fileLogin[127];
    char filePass[127];
    int Profile = 0;
    int i = 1;
    while (ok == false)
    {
        system("cls");
        continueAnsw = getValueInt("Ваш выбор:\n");
        if (continueAnsw == 1 || continueAnsw == 2 || continueAnsw == 3)
        { 
            while (okTwo == false)
            {
                if (i == 1)
                {
                    system("cls");
                    char choiceLogin[127];
                    cout << "Введите логин:\n";
                    cin >> choiceLogin;
                    std::ifstream openFile(choiceLogin, std::ios::in | std::ios::binary);
                    if (!openFile.is_open())
                    {
                        cout << "Пользователь с таким логином не найден!\n";
                        int continueAnsw;
                        bool okContin = false;
                        while (okContin == false)
                        {
                            continueAnsw = getValueInt("Продолжаем?\n1 - Да\n2 - нет\n");
                            if (continueAnsw == 1 || continueAnsw == 2)
                            {
                                okContin = true;
                            }
                            else
                            {
                                cout << "Введите одно из указанных чисел.\n" << endl;
                            }
                        }
                        if (continueAnsw == 2)
                        {
                            cout << "Операция прервана\n" << endl;
                            system("pause");
                            exit(0);
                        }
                    }
                    else
                    {
                        openFile.read((char*)&searchUD, sizeof(Profile));
                        openFile.close();
                        i = 2;
                    }
                }
                if (i == 2)
                {
                    system("cls");
                    char choicePass[127];
                    cout << "Введите пароль:\n";
                    cin >> choicePass;;
                    if (strcmp(choicePass, searchUD.password) == 0)
                    {
                        ok = true;
                    }
                    else
                    {
                        cout << "Ошибка пароля. Повторите ввод.\n";
                        int continueAnsw;
                        bool okContin = false;
                        while (okContin == false)
                        {
                            continueAnsw = getValueInt("Продолжаем?\n1 - Да\n2 - нет\n");
                            if (continueAnsw == 1 || continueAnsw == 2)
                            {
                                okContin = true;
                            }
                            else
                            {
                                cout << "Введите одно из указанных чисел.\n" << endl;
                            }
                        }
                        if (continueAnsw == 2)
                        {
                            cout << "Операция прервана\n" << endl;
                            system("pause");
                            exit(0);
                        }
                    }
                }
            }
            if (searchUD.level == 1) { GetChoiceMenuAdmin(); }
            if (searchUD.level == 2) { GetChoiceMenuManager(); }
            if (searchUD.level == 3) { GetChoiceMenuUser(); }
        }
        else if (continueAnsw == 4)
        {
            cout << "Выход!\n";
            system("pause");
            exit(0);
        }
        else
        {
            cout << "Введите одно из указанных чисел.\n" << endl;
        }
    }
}