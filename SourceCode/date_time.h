#pragma once
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
using namespace std;
#define PINK "\033[38;5;206m"
#define RESET "\033[0m"
class Date
{
private:
	int day, month, year; // ngày tháng năm
	// mảng lưu các ngày trong tháng
	int dayOfMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

public:
	// hàm khởi tạo
	Date();
	Date(int day, int month, int year);
	Date(const Date &date);
	// hàm nhập ngày
	friend void inputDay(int &day, int maxDay);
	// hàm nhập ngày, xuat
	void inputDate();
	friend istream &operator>>(istream &is, Date &date);
	friend ostream &operator<<(ostream &os, const Date &date);
	// nạp chồng toán tử gán
	Date operator=(const Date &date);
	// nạp chồng toán tử so sánh
	friend bool operator<(const Date &date1, const Date &date2);
	friend bool operator>(const Date &date1, const Date &date2);
	friend bool operator>=(const Date &date1, const Date &date2);
	friend bool operator<=(const Date &date1, const Date &date2);
	friend bool operator==(const Date &date1, const Date &date2);
	friend int age(const Date &date);
	// hàm lấy giá trị ngay, tháng , năm
	int getDay();
	int getMonth();
	int getYear();
};

class Time
{
private:
	int minute, hour; // giờ, phút
public:
	// hàm khởi tạo
	Time();
	Time(int hour, int minute);
	Time(const Time &time);
	// hàm nhập xuất thời gian
	friend istream &operator>>(istream &is, Time &time);
	friend ostream &operator<<(ostream &os, const Time &time);
	// toán tử gán
	Time operator=(const Time &time);
	// toán tử so sánh
	friend bool operator<(const Time &time1, const Time &time2);
	friend bool operator>(const Time &time1, const Time &time2);
	friend bool operator>=(const Time &time1, const Time &time2);
	friend bool operator<=(const Time &time1, const Time &time2);
	friend int operator-(const Time &time1, const Time &time2);
	int getHour();
	int getMin();
};

// Build class Date
Date::Date()
{
	day = month = 1;
	year = 1900;
}
Date::Date(int day, int month, int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
}
Date::Date(const Date &date)
{
	this->day = date.day;
	this->month = date.month;
	this->year = date.year;
}
int age(const Date &date)
{
	time_t t = time(0);
	struct tm *now = localtime(&t);
	// lấy ngày tháng năm hiện tại
	int current_year = now->tm_year + 1900;
	int current_month = now->tm_mon + 1;
	int current_day = now->tm_mday;
	int age = current_year - date.year;
	// kiểm tra xem tới ngày hiện tại chưa
	if (current_month < date.month || (current_month == date.month && current_day < date.day))
	{
		age--;
	}
	return age;
}
void inputDay(int &day, int maxDay)
{ // Ham check input day
	do
	{
		cout << "Nhap ngay:  ";
		cin >> day;
		if (day < 0 || day > maxDay)
			cout << "\nNgay phai >= 1 va <= " << maxDay << ". Vui long nhap lai\n\n";
	} while (day < 1 || day > maxDay);
}
void Date::inputDate()
{
	time_t t = time(nullptr); // L?y th?i gian hi?n t?i
	tm *now = localtime(&t);
	year = 2024;
	do
	{
		cout << "Nhap thang:  ";
		cin >> month;
		if (month < 1 || month > 12)
		{
			cout << "\nThang phai >= 1 va <= 12. Vui long nhap lai\n\n";
			continue;
		}
		if (month < now->tm_mon + 1)
			cout << "\nThang phai lon hon hoac bang thang hien tai. Vui long nhap lai\n\n";
	} while (month < 1 || month > 12 || month < now->tm_mon + 1);
	do
	{
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
			inputDay(day, 31);
		else if (month == 4 || month == 6 || month == 9 || month == 11)
			inputDay(day, 30);
		else
		{
			if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
			{
				inputDay(day, 29);
				dayOfMonth[1] = 29;
			}
			else
				inputDay(day, 28);
		}
		if (day < now->tm_mday)
			cout << "\nNgay phai lon hon hoac bang ngay hien tai\n\n";
	} while (day < now->tm_mday);
}
istream &operator>>(istream &is, Date &date)
{
	time_t t = time(nullptr);
	tm *now = localtime(&t);
	do
	{
		do
		{
			cout << "Nhap nam:  ";
			is >> date.year;
			if (date.year < 1900)
			{
				cout << "\nNam phai >= 1900. Vui long nhap lai\n\n";
				continue;
			}
			if (date.year > now->tm_year + 1900)
			{
				cout << "\nNam khong hop le. Vui long nhap lai.\n\n";
				continue;
			}
			if (date.year > 2012)
				cout << "\nNguoi tu 12 tuoi tro len moi duoc di may bay mot minh. Vui long nhap lai.\n";
		} while (date.year < 1900 || date.year > now->tm_year + 1900 || date.year > 2012);
		do
		{
			cout << "Nhap thang:  ";
			is >> date.month;
			if (date.month < 1 || date.month > 12)
				cout << "\nThang phai >= 1 va <= 12. Vui long nhap lai\n\n";
		} while (date.month < 1 || date.month > 12);
		if (date.month == 1 || date.month == 3 || date.month == 5 || date.month == 7 || date.month == 8 || date.month == 10 || date.month == 12)
			inputDay(date.day, 31);
		else if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11)
			inputDay(date.day, 30);
		else
		{
			if (date.year % 400 == 0 || (date.year % 4 == 0 && date.year % 100 != 0))
			{
				inputDay(date.day, 29);
				date.dayOfMonth[1] = 29;
			}
			else
				inputDay(date.day, 28);
		}
	} while (age(date) < 12);
	return is;
}
ostream &operator<<(ostream &os, const Date &date)
{
	if (date.day > 9)
		os << date.day << "/";
	else
		os << "0" << date.day << "/";
	if (date.month > 9)
		os << date.month << "/";
	else
		os << "0" << date.month << "/";
	os << date.year;
	return os;
}
Date Date::operator=(const Date &date)
{
	if (this != &date)
	{
		day = date.day;
		month = date.month;
		year = date.year;
	}
	return *this;
}
bool operator<(const Date &date1, const Date &date2)
{
	if (date1.year < date2.year)
		return true;
	else if (date1.year == date2.year)
	{
		if (date1.month < date2.month)
			return true;
		else if (date1.month == date2.month)
		{
			if (date1.day < date2.day)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}
bool operator>(const Date &date1, const Date &date2)
{
	if (date1.year > date2.year)
		return true;
	else if (date1.year == date2.year)
	{
		if (date1.month > date2.month)
			return true;
		else if (date1.month == date2.month)
		{
			if (date1.day > date2.day)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}
bool operator>=(const Date &date1, const Date &date2)
{
	return !(date1 < date2);
}
bool operator<=(const Date &date1, const Date &date2)
{
	return !(date1 > date2);
}
bool operator==(const Date &date1, const Date &date2)
{
	return (date1.day == date2.day && date1.month == date2.month && date1.year == date2.year);
}
int Date::getDay()
{
	return day;
}
int Date::getMonth()
{
	return month;
}
int Date::getYear()
{
	return year;
}

// Build class Time
Time::Time()
{
	hour = minute = 0;
}
Time::Time(int hour, int minute)
{
	this->hour = hour;
	this->minute = minute;
}
Time::Time(const Time &time)
{
	this->hour = time.hour;
	this->minute = time.minute;
}
istream &operator>>(istream &is, Time &time)
{
	do
	{
		cout << "Nhap gio:  ";
		is >> time.hour;
		if (time.hour < 0 || time.hour > 23)
			cout << "\nGio phai >= 0 va <= 23. Vui long nhap lai\n\n";
	} while (time.hour < 0 || time.hour > 23);
	do
	{
		cout << "Nhap phut:  ";
		is >> time.minute;
		if (time.minute < 0 || time.minute > 59)
			cout << "\nPhut phai >= 0 va <= 59. Vui long nhap lai\n\n";
	} while (time.minute < 0 || time.minute > 59);
	return is;
}
ostream &operator<<(ostream &os, const Time &time)
{
	if (time.hour > 9)
		os << time.hour << ":";
	else
		os << "0" << time.hour << ":";
	if (time.minute > 9)
		os << time.minute;
	else
		os << "0" << time.minute;
	return os;
}
Time Time::operator=(const Time &time)
{
	if (this != &time)
	{
		hour = time.hour;
		minute = time.minute;
	}
	return *this;
}
bool operator<(const Time &time1, const Time &time2)
{
	if (time1.hour < time2.hour)
		return true;
	else if (time1.hour == time2.hour)
	{
		if (time1.minute < time2.minute)
			return true;
		else
			return false;
	}
	else
		return false;
}
bool operator>(const Time &time1, const Time &time2)
{
	if (time1.hour > time2.hour)
		return true;
	else if (time1.hour == time2.hour)
	{
		if (time1.minute > time2.minute)
			return true;
		else
			return false;
	}
	else
		return false;
}
bool operator>=(const Time &time1, const Time &time2)
{
	return !(time1 < time2);
}
bool operator<=(const Time &time1, const Time &time2)
{
	return !(time1 > time2);
}
int Time::getHour()
{
	return hour;
}
int Time::getMin()
{
	return minute;
}
int operator-(const Time &time1, const Time &time2)
{
	int h = time1.hour - time2.hour;
	int m = time1.minute - time2.minute;
	return h * 60 + m;
}
