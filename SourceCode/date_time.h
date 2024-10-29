#pragma once
#include<iostream>
#include<math.h>
#include<string>
#include<vector>
#include<map>
#include<unordered_map>
#include<conio.h>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<ctime>
using namespace std;

#define PINK "\033[38;5;206m"
#define RESET "\033[0m"

class Date {
	private:
		int day, month, year;
		int dayOfMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	public:
		Date();
		Date( int day, int month, int year );
		Date( const Date &date );
		friend void inputDay( int &day, int maxDay );
		friend istream& operator >> ( istream& is, Date &date );
		friend ostream& operator << ( ostream& os, const Date &date );
		Date operator = ( const Date &date );
		friend bool operator < ( const Date &date1, const Date &date2 );
		friend bool operator > ( const Date &date1, const Date &date2 );
		friend bool operator >= ( const Date &date1, const Date &date2 );
		friend bool operator <= ( const Date &date1, const Date &date2 );
		friend bool operator == ( const Date &date1, const Date &date2 );
		int getDay();
		int getMonth();
		int getYear();
};
class Time {
	private:
		int minute, hour;
	public:
		Time();
		Time( int hour, int minute );
		Time( const Time &time );
		friend istream& operator >> ( istream& is, Time &time );
		friend ostream& operator << ( ostream& os, const Time &time );
		Time operator = ( const Time &time );
		friend bool operator < ( const Time &time1, const Time &time2 );
		friend bool operator > ( const Time &time1, const Time &time2 );
		friend bool operator >= ( const Time &time1, const Time &time2 );
		friend bool operator <= ( const Time &time1, const Time &time2 );
		friend bool operator == ( const Time &time1, const Time &time2 );
		int getHour();
		int getMin();
};


// Build class Date
Date::Date(){
	day = month = 1;
	year = 1990;
}
Date::Date( int day, int month, int year ){
	this->day = day;
	this->month = month;
	this->year = year;
}
Date::Date( const Date &date ){
	this->day = date.day;
	this->month = date.month;
	this->year = date.year;
}
void inputDay( int &day, int maxDay ){ // Ham check input day
	do {
		cout << "Nhap ngay:  ";
		cin >> day;
		if( day < 1 || day > maxDay )
			cout << "\nNgay phai >= 1 va <= " << maxDay << ". Vui long nhap lai\n\n";
	}while( day < 1 || day > maxDay );
}
istream& operator >> ( istream& is, Date &date ){
	do {
		cout << "Nhap nam:  ";
		is >> date.year;
		if( date.year < 1990 )
			cout << "\nNam phai >= 1990. Vui long nhap lai\n\n";
	}while( date.year < 1990 );
	do {
		cout << "Nhap thang:  ";
		is >> date.month;
		if( date.month < 1 || date.month > 12 )
			cout << "\nThang phai >= 1 va <= 12. Vui long nhap lai\n\n";
	}while( date.month < 1 || date.month > 12 );
	if( date.month == 1 || date.month == 3 || date.month == 5 || date.month == 7 || date.month == 8 || date.month == 10 || date.month == 12 )
		inputDay(date.day,31);
	else if( date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11 )
		inputDay(date.day,30);
	else {
		if( date.year % 400 == 0 || ( date.year % 4 == 0 && date.year % 100 != 0 ) ){
			inputDay(date.day,29);
			date.dayOfMonth[1] = 29;
		}	
		else 
			inputDay(date.day,28);
	}
	return is;
}
ostream& operator << ( ostream& os, const Date &date ){
	if( date.day > 9 )
		os << date.day << "/";
	else 
		os << "0" << date.day << "/";
	if( date.month > 9 )
		os << date.month << "/";
	else 
		os << "0" << date.month << "/";
	os << date.year;
	return os;
}
Date Date::operator = ( const Date &date ){
	if( this != &date ) { 
        day = date.day;
        month = date.month;
        year = date.year;
    }
    return *this;
}
bool operator < ( const Date &date1, const Date &date2 ){
	if( date1.year < date2.year )
		return true;
	else if( date1.year == date2.year ){
		if( date1.month < date2.month )
			return true;
		else if( date1.month == date2.month ){
			if( date1.day < date2.day)
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
bool operator > ( const Date &date1, const Date &date2 ){
	if( date1.year > date2.year )
		return true;
	else if( date1.year == date2.year ){
		if( date1.month > date2.month )
			return true;
		else if( date1.month == date2.month ){
			if( date1.day > date2.day)
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
bool operator >= ( const Date &date1, const Date &date2 ){
	return !( date1 < date2 );
}
bool operator <= ( const Date &date1, const Date &date2 ){
	return !( date1 > date2 );
}
bool operator == ( const Date &date1, const Date &date2 ){
	return ( date1.day == date2.day && date1.month == date2.month && date1.year == date2.year );
}
int Date::getDay(){
	return day;
}
int Date::getMonth(){
	return month;
}
int Date::getYear(){
	return year;
}


// Build class Time
Time::Time(){
	hour = minute = 0;
}
Time::Time( int hour, int minute ){
	this->hour = hour;
	this->minute = minute;
}
Time::Time( const Time &time ){
	this->hour = time.hour;
	this->minute = time.minute;
}
istream& operator >> ( istream& is, Time &time ){
	do {
		cout << "Nhap gio:  ";
		is >> time.hour;
		if( time.hour < 0 || time.hour > 23 )
			cout << "\nGio phai >= 0 va <= 23. Vui long nhap lai\n\n";
	}while( time.hour < 0 || time.hour > 23 );
	do {
		cout << "Nhap phut:  ";
		is >> time.minute;
		if( time.minute < 0 || time.minute > 59 )
			cout << "\nPhut phai >= 0 va <= 59. Vui long nhap lai\n\n";
	}while( time.minute < 0 || time.minute > 59 );
	return is;
}
ostream& operator << ( ostream& os, const Time &time ){
	if( time.hour > 9 )
		os << time.hour << ":";
	else 
		os << "0" << time.hour << ":";
	if( time.minute > 9 )
		os << time.minute;
	else 
		os << "0" << time.minute;
	return os;
}
Time Time::operator = ( const Time &time ){
	if( this != &time ) { 
        hour = time.hour;
        minute = time.minute;
    }
    return *this;
} 
bool operator < ( const Time &time1, const Time &time2 ){
	if( time1.hour < time2.hour )
		return true;
	else if( time1.hour == time2.hour ){
		if( time1.minute < time2.minute )
			return true;
		else
			return false;
	}
	else
		return false;
}
bool operator > ( const Time &time1, const Time &time2 ){
	if( time1.hour > time2.hour )
		return true;
	else if( time1.hour == time2.hour ){
		if( time1.minute > time2.minute )
			return true;
		else
			return false;
	}
	else
		return false;
}
bool operator >= ( const Time &time1, const Time &time2 ){
	return !( time1 < time2 );
}
bool operator <= ( const Time &time1, const Time &time2 ){
	return !( time1 > time2 );
}
bool operator == ( const Time &time1, const Time &time2 ){
	return (time1.hour == time2.hour && time1.minute == time2.minute);
}
int Time::getHour(){
	return hour;
}
int Time::getMin(){
	return minute;
}