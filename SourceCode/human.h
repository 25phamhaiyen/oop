#pragma once
#include "date_time.h"
#include "flight.h"
#include "plane.h"
class Human {
	private:
		string name;
		Date date;
		string sex; // giá»›i tĂ­nh
		int age;
	public:
		Human();
		Human( string name, Date date, string sex );
		Human( const Human &human );
		friend void standarName( string &name );
		friend istream& operator >> ( istream& is, Human &human );
		friend ostream& operator << ( ostream& os, const Human &human );
		Human operator = ( const Human &human );
		string getName() const;
		Date getDate() const;
		string getSex() const;
		int getAge() const;

};
class humanInPlane : public Human {
	private:
	    string id;
		string position;  // chá»©c vá»¥ trĂªn mĂ¡y bay( cÆ¡ trÆ°á»Ÿng, tiáº¿p viĂªn, cÆ¡ phĂ³ )
		double salary;
	public:
		humanInPlane();
		humanInPlane( const Human &human, string id, string position, double salary );
		friend istream& operator >> ( istream& is, humanInPlane &hip );
		friend ostream& operator << ( ostream& os, const humanInPlane &hip );
		void setId( string id );
		void setSalary( string position );
		string getPosition() const;
		double getSalary() const;
		string getId() const;
		bool operator<(const humanInPlane& other) const;
};
class Passenger : public Human {
	private:
		string phoneNum; // sá»‘ Ä‘t
		bool isInCountry; // biáº¿n check xem lĂ  bay trong nÆ°á»›c hay bay ra nÆ°á»›c ngoĂ i
		string passportNum; // sá»‘ há»™ chiáº¿u
		string cidNum; // sá»‘ cÄƒn cÆ°á»›c
		string rank; // háº¡ng gháº¿ ngá»“i
		int position; // vá»‹ trĂ­ gháº¿ ngá»“i
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
		friend void findWithTicketPrice( vector<pair<Flight, string>> flight, double minPrice, double maxPrice, string rank );
		friend void findWithDestination( vector<pair<Flight, string>> flight, string destination );
		friend void findWithTime( vector<pair<Flight, string>> flight, Time startTime, Time endTime );
		friend void findWithDate( vector<pair<Flight, string>> flight, Date date );
		friend void findWithPlaneName( vector<pair<Flight, string>> flight, string planeName );
		friend void sortIncreaseTicketPrice( vector<pair<Flight, string>> flight );
};
