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


