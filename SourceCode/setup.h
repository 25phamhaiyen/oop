#pragma once
#include "human.h"
#include "voucher.h"
class setUpData {
	public:
		friend Date stringToDate( string s );
		friend Time stringToTime( string s );
		friend int stringToInt( string s );
		friend void readDataUser( vector<pair<Passenger, string>> &demopass, vector<pair<Flight, string>> &passfly, vector<pair<Passenger, string>> &hispass, string namefile );
		friend void readData( vector<Plane> &plane, vector<Flight> &flight, vector<pair<Passenger,string>> &passInfo, vector<Voucher> &voucher, vector<vector<humanInPlane>> &personal );
		friend void writeData( vector<Plane> &plane, vector<Flight> &flight, vector<pair<Passenger,string>> &passInfo, vector<Voucher> &voucher, vector<vector<humanInPlane>> &personal );
		friend void writeDataUser( vector<pair<Passenger, string>> demopass, vector<pair<Flight, string>> passfly, vector<pair<Passenger, string>> hispass, string namefile );
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
void readDataUser( vector<pair<Passenger, string>> &demopass, vector<pair<Flight, string>> &passfly, vector<pair<Passenger, string>> &hispass, string namefile ){
    ifstream file;
	file.open(namefile);
	string line;
	while( getline(file, line) ) {
        streamsize fileSize = file.tellg();
        if( fileSize == 0 )
            break;
        stringstream ss(line);
        string type, name, date, sex, sdt, passport, cccd, rank, pos, status, id;;
        getline(ss, type, ',');
        if( type == "pas" || type == "his" ){
            getline(ss, name, ',');
            getline(ss, date, ',');
            getline(ss, sex, ',');
            getline(ss, sdt, ',');
            getline(ss, passport, ',');
            getline(ss, cccd, ',');
            getline(ss, rank, ',');
            getline(ss, pos, ',');
            getline(ss, status, ',');
            getline(ss, id, ',');
            if( type == "pas" )
                demopass.push_back(make_pair(Passenger(Human(name, stringToDate(date), sex ), sdt, passport, cccd, rank, stringToInt(pos), status ),id));
            else
                hispass.push_back(make_pair(Passenger(Human(name, stringToDate(date), sex ), sdt, passport, cccd, rank, stringToInt(pos), status ),id));
        }
        else {
            string id2, date2, firstLocal, secondLocal, firstTime, secondTime, popPrice, vipPrice, area, planeName;
            getline(ss, id2, ',');
            getline(ss, date2, ',');
            getline(ss, firstLocal, ',');
            getline(ss, secondLocal, ',');
            getline(ss, firstTime, ',');
            getline(ss, secondTime, ',');
            getline(ss, popPrice, ',');
            getline(ss, vipPrice, ',');
            getline(ss, area, ',');
            getline(ss, planeName, ',');
            passfly.push_back(make_pair(Flight(id2, stringToDate(date2), firstLocal, secondLocal, stringToTime(firstTime), stringToTime(secondTime), stringToInt(popPrice), stringToInt(vipPrice), area), planeName));
        }
    }
    file.close();
    cout << "\nDoc file thanh cong\n\n";
}
void readData( vector<pair<Plane, string>> &plane, vector<pair<Flight, string>> &flight, vector<pair<Passenger,string>> &passInfo,
    vector<Voucher> &voucher, vector<vector<pair<humanInPlane, string>>> &personal, vector<pair<Passenger,string>> &history,
    unordered_map<string, set<pair<humanInPlane, string>>> &employ ){

	ifstream file;
	string line;
	file.open("../Database/PlaneData.txt");
    while( getline(file, line) ) {
        stringstream ss(line);
        string name, num, type, status, id;
        getline(ss, name, ',');
        getline(ss, num, ',');
        getline(ss, type, ',');
        getline(ss, status, ',');
        getline(ss, id, ',');
        plane.push_back(make_pair(Plane(name, num, type, status),id));
    }
    file.close();

    file.open("../Database/FlightData.txt");
    while( getline(file, line) ) {
        stringstream ss(line);
        string id, date, firstLocal, secondLocal, firstTime, secondTime, popPrice, vipPrice, area, planeName;
        getline(ss, id, ',');
        getline(ss, date, ',');
        getline(ss, firstLocal, ',');
        getline(ss, secondLocal, ',');
        getline(ss, firstTime, ',');
        getline(ss, secondTime, ',');
        getline(ss, popPrice, ',');
        getline(ss, vipPrice, ',');
        getline(ss, area, ',');
        getline(ss, planeName, ',');
        flight.push_back(make_pair(Flight(id, stringToDate(date), firstLocal, secondLocal, stringToTime(firstTime), stringToTime(secondTime), stringToInt(popPrice), stringToInt(vipPrice), area), planeName));
    }
    file.close();

    file.open("../Database/VoucherData.txt");
    while( getline(file, line) ) {
        stringstream ss(line);
        string id, level, firstDate, lastDate;
        getline(ss, id, ',');
        getline(ss, level, ',');
        getline(ss, firstDate, ',');
        getline(ss, lastDate, ',');
        voucher.push_back(Voucher(id, stod(level), stringToDate(firstDate), stringToDate(lastDate)));
    }
    file.close();

    file.open("../Database/PassengerData.txt");
    while( getline(file, line) ) {
        stringstream ss(line);
        string name, date, sex, age, sdt, passport, cccd, rank, pos, status, id;
        getline(ss, name, ',');
        getline(ss, date, ',');
        getline(ss, sex, ',');
        getline(ss, sdt, ',');
        getline(ss, passport, ',');
        getline(ss, cccd, ',');
        getline(ss, rank, ',');
        getline(ss, pos, ',');
        getline(ss, status, ',');
        getline(ss, id, ',');
        passInfo.push_back(make_pair(Passenger(Human(name, stringToDate(date), sex ), sdt, passport, cccd, rank, stringToInt(pos), status ),id));
    }
    file.close();

    file.open("../Database/HistoryData.txt");
    while( getline(file, line) ) {
        stringstream ss(line);
        string name, date, sex, age, sdt, passport, cccd, rank, pos, status, id;
        getline(ss, name, ',');
        getline(ss, date, ',');
        getline(ss, sex, ',');
        getline(ss, sdt, ',');
        getline(ss, passport, ',');
        getline(ss, cccd, ',');
        getline(ss, rank, ',');
        getline(ss, pos, ',');
        getline(ss, status, ',');
        getline(ss, id, ',');
        history.push_back(make_pair(Passenger(Human(name, stringToDate(date), sex ), sdt, passport, cccd, rank, stringToInt(pos), status ),id));
    }
    file.close();

    file.open("../Database/HumanInPlaneData.txt");
    int count = 0;
    vector<pair<humanInPlane,string>> tmp;
    while( getline(file, line) ) {
        stringstream ss(line);
        string id, name, date, sex, age, job, salary, aircraftNum;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, date, ',');
        getline(ss, sex, ',');
        getline(ss, job, ',');
        getline(ss, salary, ',');
        getline(ss, aircraftNum, ',');
        count++;
        if( count == 3 && job != "Tiep vien" ){
        	personal.push_back(tmp);
        	tmp.clear();
        	tmp.push_back(make_pair(humanInPlane(Human(name, stringToDate(date), sex ), id, job, stringToInt(salary) ), aircraftNum));
        	count = 0;
		}
        else if( count != 4 )
        	tmp.push_back(make_pair(humanInPlane(Human(name, stringToDate(date), sex ), id, job, stringToInt(salary) ), aircraftNum));
        else {
        	tmp.push_back(make_pair(humanInPlane(Human(name, stringToDate(date), sex ), id, job, stringToInt(salary) ), aircraftNum));
        	personal.push_back(tmp);
        	tmp.clear();
        	count = 0;
		}
    }
    if( !tmp.empty() )
    	personal.push_back(tmp);
    file.close();

    // GHI FILE ALLHUMANINPLANE
    file.open("../Database/AllHumanInPlaneData.txt");
    while( getline(file, line) ) {
        stringstream ss(line);
        string id, name, date, sex, age, job, salary, aircraftNum;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, date, ',');
        getline(ss, sex, ',');
        getline(ss, job, ',');
        getline(ss, salary, ',');
        getline(ss, aircraftNum, ',');
        employ[job].insert(make_pair(humanInPlane(Human(name, stringToDate(date), sex), id, job, stringToInt(salary)), aircraftNum));
    }
    file.close();
}
void writeData( vector<pair<Plane, string>> plane, vector<pair<Flight, string>> flight, vector<pair<Passenger,string>> passInfo, vector<Voucher> voucher,
    vector<vector<pair<humanInPlane, string>>> personal, vector<pair<Passenger,string>> history, unordered_map<string, set<pair<humanInPlane, string>>> employ ){
	// ghi file du lieu cua Plane
	ofstream file;
	file.open("../Database/PlaneData.txt",ios::trunc);
	string str = "";
    if( file.is_open() ) {
        for( auto &it : plane ){
        	str = it.first.getPlaneName() + "," + it.first.getAircraftNumber() + "," + it.first.getType() + "," + it.first.getStatus()+ "," + it.second;
	        file << str << endl;
	        str = "";
	    }
    }
    file.close();

    // ghi file du lieu cua Flight
    file.open("../Database/FlightData.txt",ios::trunc);
    if( file.is_open() ) {
        for( auto &it : flight ){
	        file << it.first.getId() << "," << it.first.getFlightDate() << "," << it.first.getDepartureLocation() << "," << it.first.getDestination() << "," << it.first.getDepartureTime() << ","
				<< it.first.getLandingTime() << ","<< it.first.getPopTicketPrice() << "," << it.first.getVipTicketPrice() << "," << it.first.getArea() << ",";
            file << it.second << endl;
	    }
    }
    file.close();

    // ghi file du lieu cua Passenger
    file.open("../Database/PassengerData.txt",ios::trunc);
    if( file.is_open() ) {
        for( auto &it : passInfo ){
	        file << it.first.getName() << "," << it.first.getDate() << "," << it.first.getSex() << "," << it.first.getPhoneNum() << "," << it.first.getPassportNum() << ","
				<< it.first.getCidNum() << ","<< it.first.getRank() << "," << it.first.getPos() << "," << it.first.getStatus() << ",";
            file << it.second << endl;
	    }
    }
    file.close();

     // ghi file du lieu cua personal
    file.open("../Database/HumanInPlaneData.txt",ios::trunc);
    if( file.is_open() ) {
        for( auto &it : personal ){
        	for( auto i : it ){
		        file << i.first.getId() << "," << i.first.getName() << "," << i.first.getDate() << "," << i.first.getSex() << "," << i.first.getPosition() << "," << i.first.getSalary() << ",";
                file << i.second << endl;
        	}
	    }
    }
    file.close();

    // ghi file allhumaninplane
    file.open("../Database/AllHumanInPlaneData.txt",ios::trunc);
    if( file.is_open() ) {
        for( auto &it : employ ){
        	for( auto i : it.second ){
		        file << i.first.getId() << "," << i.first.getName() << "," << i.first.getDate() << "," << i.first.getSex() << "," << i.first.getPosition() << "," << i.first.getSalary() << ",";
                file << i.second << endl;
        	}
	    }
    }
    file.close();

    // ghi file du lieu cua personal
    file.open("../Database/HistoryData.txt",ios::trunc);
    if( file.is_open() ) {
        for( auto &it : history ){
	        file << it.first.getName() << "," << it.first.getDate() << "," << it.first.getSex() << "," << it.first.getPhoneNum() << "," << it.first.getPassportNum() << ","
				<< it.first.getCidNum() << ","<< it.first.getRank() << "," << it.first.getPos() << "," << it.first.getStatus() << ",";
            file << it.second << endl;
	    }
    }
    file.close();

    // GHI FILE voucher
    file.open("../Database/VoucherData.txt",ios::trunc);
    if( file.is_open() ) {
        for( auto &it : voucher ){
		        file << it.getID() << "," << it.getReduceLevel() << "," << it.getFromDate() << "," << it.getReduceDeadline() << endl;
	    }
    }
    file.close();

}
void writeDataUser( vector<pair<Passenger, string>> demopass, vector<pair<Flight, string>> passfly, vector<pair<Passenger, string>> hispass, string namefile ){
    ofstream file;
	file.open(namefile, ios::trunc);
	if( file.is_open() ){
        for( auto it : demopass ){
            file << "pas," << it.first.getName() << "," << it.first.getDate() << "," << it.first.getSex() << "," << it.first.getPhoneNum() << "," << it.first.getPassportNum() << ","
				<< it.first.getCidNum() << ","<< it.first.getRank() << "," << it.first.getPos() << "," << it.first.getStatus() << "," << it.second << endl;
        }
        for( auto it : hispass ){
            file << "his," << it.first.getName() << "," << it.first.getDate() << "," << it.first.getSex() << "," << it.first.getPhoneNum() << "," << it.first.getPassportNum() << ","
				<< it.first.getCidNum() << ","<< it.first.getRank() << "," << it.first.getPos() << "," << it.first.getStatus() << "," << it.second << endl;
        }
        for( auto &it : passfly ){
	        file << "fly," << it.first.getId() << "," << it.first.getFlightDate() << "," << it.first.getDepartureLocation() << "," << it.first.getDestination() << "," << it.first.getDepartureTime() << ","
				<< it.first.getLandingTime() << ","<< it.first.getPopTicketPrice() << "," << it.first.getVipTicketPrice() << "," << it.first.getArea() << "," << it.second << endl;
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

