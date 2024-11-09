#pragma once
#include "date_time.h"
#include "flight.h"
#include "plane.h"
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
		string getName() const;
		Date getDate() const;
		string getSex() const;
		int getAge() const;
};
class humanInPlane : public Human {
	private:
		string id;
		string position;  // chức vụ trên máy bay( cơ trưởng, tiếp viên, cơ phó )
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
		humanInPlane();
		humanInPlane( const Human &human, string id, string position, double salary );
		friend istream& operator >> ( istream& is, humanInPlane &hip );
		friend ostream& operator << ( ostream& os, const humanInPlane &hip );
};
