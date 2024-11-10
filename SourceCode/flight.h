#pragma once
#include "date_time.h"

class Flight
{
private:
	string id;				  //  mã chuyến bay
	string departureLocation; // nơi xuất phát
	string destination;		  // nơi đến
	Time departureTime;		  // giờ khởi hành
	Time landingTime;		  // giờ hạ cánh
	Date flightDate;		  // ngày bay
	double popTicketPrice;	  // giá vé hạng thường
	double vipTicketPrice;	  // giá vé hạng thương gia
	set<int> sitPos;		  // vi tri ngoi
	string area;

public:
	// hàm khởi tạo
	Flight();
	Flight(string id, Date flightDate, string departureLocation, string destination,
		   Time departureTime, Time landingTime, double popTicketPrice, double vipTicketPrice, string area);
	// hàm xuất
	friend ostream &operator<<(ostream &os, const Flight &fly);
	// toán tử gán
	Flight operator=(const Flight &fly2);
	// các hàm lấy giá trị
	string getId();
	string getDepartureLocation();
	string getDestination();
	Time getDepartureTime();
	Time getLandingTime();
	Date getFlightDate();
	double getPopTicketPrice();
	double getVipTicketPrice();
	string getArea();
	// các hàm thiết lập gái trị
	void setSitPos(int pos);
	void setSitPosHuy(int pos);
	void setId(string id);
	void setFlyDate(Date flyDate);
	void setDestination(string destination);
	void setTime(Time firstTime, Time secondTime);
	void setPrice(double pop, double vip);
	// hàm kiểm tra vị trí ngồi
	bool findSitPos(int pos);
	// hàm lấy tổng các vị trí ngồi đã đặt
	int getSitNum();
	friend void displayChoNgoiThuonggia(vector<pair<Flight, string>> flight, string id);
};

// Build class Flight
Flight::Flight()
{
	id = departureLocation = destination = "";
	vipTicketPrice = popTicketPrice = 0;
	departureTime = Time();
	landingTime = Time();
	flightDate = Date();
}
