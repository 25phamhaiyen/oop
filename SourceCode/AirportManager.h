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
		int getHour();
		int getMin();
};
class Human {
	private:
		string name;
		Date date;
		string sex; // giới tính
		int age;
	public:
		Human();
		Human( string name, Date date, string sex );
		Human( const Human &human );
		friend void standarName( string &name );
		friend istream& operator >> ( istream& is, Human &human );
		friend ostream& operator << ( ostream& os, const Human &human );
		Human operator = ( const Human &human );
		string getName();
		Date getDate();
		string getSex();
		int getAge();
		
};
class humanInPlane : public Human {
	private:
		string position;  // chức vụ trên máy bay( cơ trưởng, tiếp viên, cơ phó )
		double salary;
	public:
		humanInPlane();
		humanInPlane( const Human &human, string position, double salary );
		friend istream& operator >> ( istream& is, humanInPlane &hip );
		friend ostream& operator << ( ostream& os, const humanInPlane &hip );
		void setSalary( string position );
		string getPosition();
		double getSalary();
};
class Plane {
	private:
		string planeName; // tên hãng bay
		string aircraftNumber; // số hiệu máy bay
		string type;  // loại máy bay ( dân dung, chở hàng )
		string status;  // tình trạng ( bảo trì, hoạt động )
	public:
		Plane();
		Plane( string planeName, string aircraftNumber, string type, string status );
		friend istream& operator >> ( istream& is, Plane &plane );
		friend ostream& operator << ( ostream& os, const Plane &plane );
		Plane operator = ( const Plane &plane );
		string getPlaneName();
		string getStatus();
		string getType();
		string getAircraftNumber();
		void setAircraftNumber( string s );
};
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
class Passenger : public Human {
	private:
		string phoneNum; // số đt
		bool isInCountry; // biến check xem là bay trong nước hay bay ra nước ngoài
		string passportNum; // số hộ chiếu
		string cidNum; // số căn cước
		string rank; // hạng ghế ngồi
		int position; // vị trí ghế ngồi
		string status; // tinh trang( DAT or HUY )
	public:
		Passenger();
		Passenger( const Human &human, string sdt, string passport, string cccd, string rank, int pos, string status );
		friend istream& operator >> ( istream& is, Passenger &pas );
		friend ostream& operator << ( ostream& os, const Passenger &pas );
		void setInCountry( bool check );
		void setRank( string rank );
		void setPosition( int position );
		void setStatus( string s );
		bool isPassport( string passport );
		bool isPhoneNum( string phoneNum );
		bool isCidNum( string cidNum );
		string getRank();
		string getStatus();
		int getPos();
		string getPhoneNum();
		string getCidNum();
		string getPassportNum();
		friend void addFlight(vector<pair<Passenger,string>> &passenger );
		friend void findWithTicketPrice( vector<pair<Flight, string>> flight, double minPrice, double maxPrice, string rank );
		friend void findWithDestination( vector<pair<Flight, string>> flight, string destination );
		friend void findWithTime( vector<pair<Flight, string>> flight, Time startTime, Time endTime );
		friend void findWithDate( vector<pair<Flight, string>> flight, Date date );
		friend void findWithPlaneName( vector<pair<Flight, string>> flight, string planeName );
		friend void sortIncreaseTicketPrice( vector<pair<Flight, string>> flight );
};
class Voucher {
	private:
		string id;  // mã giảm giá
		double reduceLevel;  // mức giảm (%)
		Date fromDate; // ngày có hiệu lực
		Date reduceDeadline;  // ngày hết hạn giảm;
	public:
		Voucher();
		Voucher( string id, double reduceLevel, Date fromDate, Date reduceDeadline );
		friend istream& operator >> ( istream& is, Voucher &voucher );
		friend ostream& operator << ( ostream& os, const Voucher &voucher );
		string getID();
		double getReduceLevel();
		Date getFromDate();
		Date getReduceDeadline();
};
class Manager {
	public:
		friend void displayHistory( vector<pair<Passenger, string>> history );
		friend void displayFlight( vector<pair<Flight, string>> flight );
		friend void displayPlane( vector<Plane> plane );
		friend void displayPassenger( vector<pair<Passenger,string>> plane );
		friend void displayHumanInPlane( vector<vector<pair<humanInPlane,string>>> personal );
		friend void displayVoucher( vector<Voucher> voucher );
		friend void inputFlight( Flight &fly );
		friend void addFlight( vector<Plane> &plane, vector<pair<Flight,string>> &flight, vector<vector<pair<humanInPlane,string>>> &personal );
		friend void addVoucher( vector<Voucher> &voucher );
		friend void displayBill( int ticketNum, vector<pair<Flight, string>> passfly, vector<pair<Passenger, string>> passenger, int voucherLevel );
};
class setUpData {
	public:
		friend Date stringToDate( string s );
		friend Time stringToTime( string s );
		friend int stringToInt( string s );
		friend void readData( vector<Plane> &plane, vector<Flight> &flight, vector<pair<Passenger,string>> &passInfo, vector<Voucher> &voucher, vector<vector<humanInPlane>> &personal );
		friend void writeData( vector<Plane> &plane, vector<Flight> &flight, vector<pair<Passenger,string>> &passInfo, vector<Voucher> &voucher, vector<vector<humanInPlane>> &personal );
		friend void updateSitPos( vector<pair<Flight, string>> &flight, vector<pair<Passenger,string>> passInfo );
};