#pragma once
#include "date_time.h"

class Flight
{
private:
	string id;						//  mã chuyến bay
	string departureLocation;		// nơi xuất phát
	string destination;				// nơi đến
	Time departureTime;				// giờ khởi hành
	Time landingTime;				// giờ hạ cánh
	Date flightDate;				// ngày bay
	double popTicketPrice;			// giá vé hạng thường
	double vipTicketPrice;			// giá vé hạng thương gia
	unordered_map<int, int> sitPos; // vi tri ngoi
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
	bool checkSitPos(int pos);
	// hàm lấy tổng các vị trí ngồi đã đặt
	int getSitNum();
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
Flight::Flight(string id, Date flightDate, string departureLocation, string destination, Time departureTime, Time landingTime, double popTicketPrice, double vipTicketPrice, string area)
{
	this->id = id;
	this->departureLocation = departureLocation;
	this->destination = destination;
	this->departureTime = departureTime;
	this->landingTime = landingTime;
	this->flightDate = flightDate;
	this->popTicketPrice = popTicketPrice;
	this->vipTicketPrice = vipTicketPrice;
	this->area = area;
}
ostream &operator<<(ostream &os, const Flight &fly)
{
	os << fly.id << "   |   " << fly.flightDate << "   |   from " << fly.departureLocation << " to " << fly.destination << "   |    " << fly.departureTime << "    |    " << fly.landingTime << "    |     " << fly.popTicketPrice << "      |    ";
	if (fly.vipTicketPrice >= 10000)
		cout << fly.vipTicketPrice << "   |";
	else
		cout << fly.vipTicketPrice << "    |";
	return os;
}
Flight Flight::operator=(const Flight &fly2)
{
	this->id = fly2.id;
	this->flightDate = fly2.flightDate;
	this->departureLocation = fly2.departureLocation;
	this->destination = fly2.destination;
	this->departureTime = fly2.departureTime;
	this->landingTime = fly2.landingTime;
	this->popTicketPrice = fly2.popTicketPrice;
	this->vipTicketPrice = fly2.vipTicketPrice;
	this->area = fly2.area;
	return *this;
}
string Flight::getDepartureLocation()
{
	return this->departureLocation;
}
string Flight::getDestination()
{
	return this->destination;
}
Time Flight::getDepartureTime()
{
	return this->departureTime;
}
Time Flight::getLandingTime()
{
	return this->landingTime;
}
Date Flight::getFlightDate()
{
	return this->flightDate;
}
double Flight::getPopTicketPrice()
{
	return this->popTicketPrice;
}
double Flight::getVipTicketPrice()
{
	return this->vipTicketPrice;
}
string Flight::getArea()
{
	return this->area;
}
void Flight::setSitPos(int pos)
{
	sitPos[pos] = 1;
}
void Flight::setSitPosHuy(int pos)
{
	sitPos[pos] = 0;
}
string Flight::getId()
{
	return id;
}
int Flight::getSitNum()
{
	int count = 0;
	for (int i = 0; i < 51; i++)
	{
		if (sitPos[i] == 1)
			count++;
	}
	return count;
}
bool Flight::checkSitPos(int pos)
{
	if (this->sitPos[pos] == 1)
		return false;
	return true;
}
void Flight::setId(string id)
{
	this->id = id;
}
void Flight::setFlyDate(Date flyDate)
{
	this->flightDate = flyDate;
}
void Flight::setDestination(string destination)
{
	this->destination = destination;
}
void Flight::setTime(Time firstTime, Time secondTime)
{
	this->departureTime = firstTime;
	this->landingTime = secondTime;
}
void Flight::setPrice(double pop, double vip)
{
	this->popTicketPrice = pop;
	this->vipTicketPrice = vip;
}
