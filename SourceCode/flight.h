#include "date_time.h"

class Flight {
	private:
		string id; //  mã chuyến bay
		string departureLocation;  // nơi xuất phát
		string destination; // nơi đến
		Time departureTime; // giờ khởi hành
		Time landingTime; // giờ hạ cánh
		Date flightDate; // ngày bay
		double popTicketPrice; // giá vé hạng thường
		double vipTicketPrice; // giá vé hạng thương gia
		unordered_map<int,int> sitPos; // vi tri ngoi
	public:
		Flight();
		Flight( string id, Date flightDate, string departureLocation, string destination, Time departureTime, Time landingTime, double popTicketPrice, double vipTicketPrice );
		friend istream& operator >> ( istream& is, Flight &fly );
		friend ostream& operator << ( ostream& os, const Flight &fly );
		Flight operator = ( const Flight &fly2 );
		string getId();
		string getDepartureLocation();
		string getDestination();
		Time getDepartureTime();
		Time getLandingTime();
		Date getFlightDate();
		double getPopTicketPrice();
		double getVipTicketPrice();
		void setSitPos( int pos );
		void setSitPosHuy( int pos );
		int getSitNum();
		void listVip();
		void listPopular();
		int countVip();
		int countPopular();
		
};

// Build class Flight 
Flight::Flight(){
	id = departureLocation = destination = "";
	vipTicketPrice = popTicketPrice = 0;
	departureTime = Time(); 
    landingTime = Time(); 
    flightDate = Date();
}
Flight::Flight( string id, Date flightDate, string departureLocation, string destination, Time departureTime, Time landingTime, double popTicketPrice, double vipTicketPrice ){
	this->id = id;
	this->departureLocation = departureLocation;
	this->destination = destination;
	this->departureTime = departureTime;
	this->landingTime = landingTime;
	this->flightDate = flightDate;
	this->popTicketPrice = popTicketPrice;
	this->vipTicketPrice = vipTicketPrice;
}
istream& operator >> ( istream& is, Flight &fly ){
	fly.departureLocation = "Sai Gon";
	cin.ignore();
	cout << "\nNhap ID chuyen bay: ";
	is >> fly.id;
	cin.ignore();
	cout << "\nNhap noi den ( Tinh hoac TP ):  ";
	getline(is, fly.destination);
	cout << "\nNhap ngay bay ( year/month/day ):  \n";
	is >> fly.flightDate;
	cout << "\nNhap thoi gian khoi hanh ( hour:minute ):  \n";
	is >> fly.departureTime;
	do {
		cout << "\nNhap thoi gian ha canh ( hour:minute ):  \n";
		is >> fly.landingTime;
		if( fly.landingTime < fly.departureTime )
			cout << "\nThoi gian ha canh phai lon hon thoi gian khoi hanh. Vui long nhap lai\n";
	}while( fly.landingTime < fly.departureTime );
	do {
		cout << "\nNhap gia ve hang thuong (.000 VND):  ";
		is >> fly.popTicketPrice;
		if( fly.popTicketPrice <= 0 )
			cout << "\nGia ve phai lon hon 0. Vui long nhap lai\n";
	}while( fly.popTicketPrice <= 0 );
	do {
		cout << "\nNhap gia ve hang thuong gia (.000 VND):  ";
		is >> fly.vipTicketPrice;
		if( fly.vipTicketPrice <= 0 ){
			cout << "\nGia ve phai lon hon 0. Vui long nhap lai\n";
			continue;
		}
		if( fly.vipTicketPrice <= fly.popTicketPrice )
			cout << "\nGia ve hang thuong gia phai lon hon gia ve hang thuong. Vui long nhap lai\n";
	}while( fly.vipTicketPrice <= 0 || fly.vipTicketPrice <= fly.popTicketPrice );
	return is;
}
ostream& operator << ( ostream& os, const Flight &fly ){
	os << fly.id << "   |   " << fly.flightDate << "   |   from " << fly.departureLocation << " to " << fly.destination << "   |    " << fly.departureTime << "    |    " << fly.landingTime << "    |     " << fly.popTicketPrice  << "      |    ";
	if( fly.vipTicketPrice >= 10000 )
		cout << fly.vipTicketPrice << "   |";
	else
		cout << fly.vipTicketPrice << "    |";
	return os;
}
Flight Flight::operator = ( const Flight &fly2 ){
	this->id = fly2.id;
	this->flightDate = fly2.flightDate;
	this->departureLocation = fly2.departureLocation;
	this->destination = fly2.destination;
	this->departureTime = fly2.departureTime;
	this->landingTime = fly2.landingTime;
	this->popTicketPrice = fly2.popTicketPrice;
	this->vipTicketPrice = fly2.vipTicketPrice;
	return *this;
	
}
string Flight::getDepartureLocation(){
	return this->departureLocation;
}
string Flight::getDestination(){
	return this->destination;
}
Time Flight::getDepartureTime(){
	return this->departureTime;
}
Time Flight::getLandingTime(){
	return this->landingTime;
}
Date Flight::getFlightDate(){
	return this->flightDate;
}
double Flight::getPopTicketPrice(){
	return this->popTicketPrice;
}
double Flight::getVipTicketPrice(){
	return this->vipTicketPrice;
}
void Flight::setSitPos( int pos ){
	sitPos[pos] = 1;
}
void Flight::setSitPosHuy( int pos ){
	sitPos[pos] = 0;
}
string Flight::getId(){
	return id;
}
int Flight::getSitNum(){
	int count = 0;
	for( int i = 0 ; i < 51 ; i++ ){
		if( sitPos[i] == 1 )
			count++;
	}
	return count;
}
void Flight::listVip(){
	cout << endl << "Nhung vi tri ghe ngoi hang THUONG GIA con trong: \n{ ";
	for( int i = 1 ; i <= 15 ; i++ ){
		if( sitPos[i] != 0 )
			continue;
		cout << i << ", ";
	}
	cout << "}";
}
void Flight::listPopular(){
	cout << endl << "Nhung vi tri ghe ngoi hang PHO THONG con trong: \n{ ";
	for( int i = 16 ; i <= 50 ; i++ ){
		if( sitPos[i] != 0 )
			continue;
		cout << i << ", ";
	}
	cout << "}";
}
int Flight::countVip(){
	int cnt = 0;
	for( int i = 1 ; i < 16 ; i++ ){
		if( sitPos[i] == 0 )
			cnt++;
	}
	return cnt;
}
int Flight::countPopular(){
	int cnt = 0;
	for( int i = 16 ; i < 51 ; i++ ){
		if( sitPos[i] == 0 )
			cnt++;
	}
	return cnt;
}