#include<iostream>
#include<math.h>
#include<string.h>
#include<vector>
#include<map>
#include<unordered_map>
#include<conio.h>
#include<fstream>
using namespace std;
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
};
class Human {
	private:
		string name;
		Date date;
		string sex; // giới tính
		int age;
		string address;
	public:
		Human();
		Human( string name, Date date, string sex, int age, string address );
		Human( const Human &human );
		friend void standarName( string &name );
		friend istream& operator >> ( istream& is, Human &human );
		friend ostream& operator << ( ostream& os, const Human &human );
		Human operator = ( const Human &human );
		
};
class humanInPlane : public Human {
	private:
		string position;  // chức vụ trên máy bay( cơ trưởng, tiếp viên, cơ phó )
		double salary;
	public:
		humanInPlane();
		humanInPlane( const Human &human, string position );
		friend istream& operator >> ( istream& is, humanInPlane &hip );
		friend ostream& operator << ( ostream& os, const humanInPlane &hip );
		void setSalary( string position );
};
class Plane {
	private:
		string planeName; // tên hãng bay
		string aircraftNumber; // số hiệu máy bay
		string type;  // loại máy bay ( dân dung, chở hàng )
		string status;  // tình trạng ( bảo trì, hoạt động )
		//vector<int> sitPos(50,0);  // vị trí ghế ngồi( 0 -> 14: hạng thương gia, 15 -> 49: hạng thường )
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
};
class Flight {
	private:
		string id; //  mã chuyến bay
		string departureLocation;  // nơi xuất phát
		string destination; // nơi đến
		Time departureTime; // giờ khởi hành
		Time landingTime; // giờ hạ cánh
		Date flightDate; // ngày bay
		double ticketPrice; // giá vé
	public:
		Flight();
		Flight( string id, Date flightDate, string departureLocation, string destination, Time departureTime, Time landingTime, double ticketPrice );
		friend istream& operator >> ( istream& is, Flight &fly );
		friend ostream& operator << ( ostream& os, const Flight &fly );
		string getDepartureLocation();
		string getDestination();
		Time getDepartureTime();
		Time getLandingTime();
		Date getFlightDate();
		double getTicketPrice();
		
};
class Passenger : public Human {
	private:
		string phoneNum; // số đt
		bool isInCountry; // biến check xem là bay trong nước hay bay ra nước ngoài
		string passportNum; // số hộ chiếu
		string cidNum; // số căn cước
		string rank; // hạng ghế ngồi
		int position; // vị trí ghế ngồi
	public:
		friend istream& operator >> ( istream& is, Passenger &pas );
		friend ostream& operator << ( ostream& os, const Passenger &pas );
		void setInCountry( bool check );
		void setRank( string rank );
		void setPosition( int position );
		bool isPassport( string passport );
		string getRank();
		void deleteFlight();
		void addFlight();
		double allTicketPrice();
		void findWithTicketPrice();
		void findWithDestination();
		void findWithDepartureTime();
		void findWithLandingTime();
		void findWithFlightDate();
		void findWithPlaneName();
		void sortIncreaseTicketPrice();
		void sortDecreaseTicketPrice();		
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
		Plane plane;
		humanInPlane hip;
		Flight fly;
		Voucher vou;
		friend istream& operator >> ( istream& is, Manager &manager );
		friend ostream& operator << ( ostream& os, const Manager &manager );
		friend void displayHistory();
		friend void displayFlight();
};
