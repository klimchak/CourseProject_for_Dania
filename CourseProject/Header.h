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
            ���������� �������
============================================
*/
// �������� �� ������� ����� ������
bool SearchDataFile();
// ��������� ����� ������
bool CreateOrDeleteAdminFile();
// ������ ������ � ����� �������
string WorkUserDataFD(UserData user, bool rePass, bool del);
// ����� ������ ���������� ������������
UserData setNewPass();
// ���� ������ ��� ������������
UserData GetNewUserDataData();
// ������� ������ � ����
void GetChoiceMenuAdmin();
void GetChoiceAutoDataFileData();
void GetChoiceAutoDataRecords();
void GetChoiceAutoDataUserData();
void GetChoiceMenuManager();
void GetChoiceMenuUser();
// ������� ������ ����
void PrintMenuAdmin();
void DisplayAutoDataFileData();
void DisplayAutoDataRecords();
void DisplayAutoDataUserData();
void PrintMenuManager();
void PrintMenuUser();
// ������� ��������� �������� � ����������
// ��������� �������� int
int getValueInt(string mess);
// ��������� �������� string
string getValueStr(string mess);
// �������� ������ � ������
void GetLogiAndPass();
// �������� �� ������� ����� ������
bool SearchDataFile();
// �������� � ��������� ����� ������
bool CreateOrDeleteFD(bool createOrDelete);
// ���� �������� �� ���������
auto aggregationautoData();
// ������ ������ ������ ��������� � ���� ������ (���������� �����)
bool creatRecordInFD(bool atMemory);
// ����� ������� ����� ������
void printTable();
// ����� ������� ����� ������ ����������
void printTableAbbr();
// ����� ��������� � ����� �������
void searchAndPrintTable(int change);
// ������� ������ � ������
bool search(string query, string fundStr);
// ��������� ������ ���������� � ������
void getAllautoFD();
// �������� ������ ��������� � ������ � ���������� � ����
bool deleteWirkerInMemory();
// ��������� ������ ��������� � ������ � ���������� � ����
bool changeWirkerInMemory();
//����������
// ���������� last name
bool compararereceipt_date(const auto lhs, const auto rhs);
// ���������� first name
bool compararemodel(const auto lhs, const auto rhs);
// ���������� departure_date
bool compararecolor(const auto lhs, const auto rhs);
// ������� ����������
void sortLN();
void sortFN();
void sortDep();
#endif