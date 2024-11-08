#pragma once
#include "human.h"
#include "voucher.h"
class setUpData {
	public:
		friend Date stringToDate( string s );
		friend Time stringToTime( string s );
		friend int stringToInt( string s );
		friend void readData( vector<Plane> &plane, vector<Flight> &flight, vector<pair<Passenger,string>> &passInfo, vector<Voucher> &voucher, vector<vector<humanInPlane>> &personal );
		friend void writeData( vector<Plane> &plane, vector<Flight> &flight, vector<pair<Passenger,string>> &passInfo, vector<Voucher> &voucher, vector<vector<humanInPlane>> &personal );
		friend void updateSitPos( vector<pair<Flight, string>> &flight, vector<pair<Passenger,string>> passInfo );
};

// build class setUpData
Date stringToDate( string s ){
	int date[3];
	int count = 0;
	string tmp = "";
	for( int i = 0 ; i < s.size() ; i++ ){
		if( s[i] != '/' )
			tmp += s[i];
		else {
			date[count] = stoi(tmp);
			count++;
			tmp = "";
		}
	}
	date[count] = stoi(tmp);
	return Date(date[0],date[1],date[2]);
}
Time stringToTime( string s ){
	return Time(stoi(s.substr(0,2)),stoi(s.substr(3,2)));
}
int stringToInt( string s ){
	int ans = 0;
	for( int i = 0 ; i < s.size() ; i++ ){
		if( s[i] >= '0' && s[i] <= '9'){
			int x = s[i]-'0';
			ans = ans*10 + x;
		}
	}
	return ans;
}
void readData( vector<pair<Plane, string>> &plane, vector<pair<Flight, string>> &flight, vector<pair<Passenger,string>> &passInfo, vector<Voucher> &voucher, vector<vector<pair<humanInPlane, string>>> &personal, vector<pair<Passenger,string>> &history ){
	ifstream file;
	file.open("Database\\PlaneData.txt");
	file.open("./Database/PlaneData.txt");
	string line;
    while( getline(file, line) ) {
        stringstream ss(line);
@@ -57,7 +57,7 @@
    }
    file.close();

    file.open("Database\\FlightData.txt");
    file.open("./Database/FlightData.txt");
    while( getline(file, line) ) {
        stringstream ss(line);
        string id, date, firstLocal, secondLocal, firstTime, secondTime, popPrice, vipPrice, area, planeName;
@@ -75,7 +75,7 @@
    }
    file.close();

    file.open("Database\\VoucherData.txt");
    file.open("./Database/VoucherData.txt");
    while( getline(file, line) ) {
        stringstream ss(line);
        string id, level, firstDate, lastDate;
@@ -87,7 +87,7 @@
    }
    file.close();

    file.open("Database\\PassengerData.txt");
    file.open("./Database/PassengerData.txt");
    while( getline(file, line) ) {
        stringstream ss(line);
        string name, date, sex, age, sdt, passport, cccd, rank, pos, status, id;
@@ -105,7 +105,7 @@
    }
    file.close();

    file.open("Database\\HistoryData.txt");
    file.open("./Database/HistoryData.txt");
    while( getline(file, line) ) {
        stringstream ss(line);
        string name, date, sex, age, sdt, passport, cccd, rank, pos, status, id;
@@ -123,7 +123,7 @@
    }
    file.close();

    file.open("Database\\HumanInPlaneData.txt");
    file.open("./Database/HumanInPlaneData.txt");
    int count = 0;
    vector<pair<humanInPlane,string>> tmp;
    while( getline(file, line) ) {
@@ -159,7 +159,7 @@
void writeFile( vector<pair<Plane, string>> &plane, vector<pair<Flight, string>> &flight, vector<pair<Passenger,string>> &passInfo, vector<Voucher> &voucher, vector<vector<pair<humanInPlane, string>>> &personal, vector<pair<Passenger,string>> &history ){
	// ghi file du lieu cua Plane
	ofstream file;
	file.open("Database\\PlaneData.txt",ios::trunc);
	file.open("./Database/PlaneData.txt",ios::trunc);
	string str = "";
    if( file.is_open() ) {
        for( auto &it : plane ){
@@ -171,7 +171,7 @@
    file.close();

    // ghi file du lieu cua Flight
    file.open("Database\\FlightData.txt",ios::trunc);
    file.open("./Database/FlightData.txt",ios::trunc);
    if( file.is_open() ) {
        for( auto &it : flight ){
	        file << it.first.getId() << "," << it.first.getFlightDate() << "," << it.first.getDepartureLocation() << "," << it.first.getDestination() << "," << it.first.getDepartureTime() << ","
@@ -181,7 +181,7 @@
    file.close();

    // ghi file du lieu cua Passenger
    file.open("Database\\PassengerData.txt",ios::trunc);
    file.open("./Database/PassengerData.txt",ios::trunc);
    if( file.is_open() ) {
        for( auto &it : passInfo ){
	        file << it.first.getName() << "," << it.first.getDate() << "," << it.first.getSex() << "," << it.first.getPhoneNum() << "," << it.first.getPassportNum() << ","
@@ -191,7 +191,7 @@
    file.close();

     // ghi file du lieu cua personal
    file.open("Database\\HumanInPlane.txt",ios::trunc);
    file.open("./Database/HumanInPlane.txt",ios::trunc);
    if( file.is_open() ) {
        for( auto &it : personal ){
        	for( auto i : it )
@@ -201,23 +201,23 @@
    file.close();

    // ghi file du lieu cua personal
    file.open("Database\\HistoryData.txt",ios::trunc);
    file.open("./Database/HistoryData.txt",ios::trunc);
    if( file.is_open() ) {
        for( auto &it : personal ){
        	for( auto i : it )
		        file << i.first.getName() << "," << i.first.getDate() << "," << i.first.getSex() << "," << i.first.getPosition() << "," << i.first.getSalary() << "," << i.second << endl;
	    }
    }
    file.close();

}
void updateSitPos( vector<pair<Flight, string>> &flight, vector<pair<Passenger,string>> passInfo ){
	for( auto &it : passInfo ){
		for( auto &fly : flight ){
			if( fly.first.getId() == it.second ){
				fly.first.setSitPos( it.first.getPos() );
			}
		}
	}
}