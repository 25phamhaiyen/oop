#pragma once
#include "date_time.h"

class Voucher {
	private:
		string id;  // mã giảm giá
		double reduceLevel;  // mức giảm (%)
		Date fromDate; // ngày có hiệu lực
		Date reduceDeadline;  // ngày hết hạn giảm;
	public:
		Voucher();
		Voucher( string id, double reduceLevel, Date fromDate, Date reduceDeadline );
		friend ostream& operator << ( ostream& os, const Voucher &voucher );
		string getID();
		double getReduceLevel();
		Date getFromDate();
		Date getReduceDeadline();
		void setID( string newId );
		void setReduceLevel( double level );
		void setFromDate( Date fDate );
		void setReduceDeadline( Date rDate );
};

// Build class Voucher
Voucher::Voucher(){
	id = "";
	reduceLevel = 0;
}
Voucher::Voucher( string id, double reduceLevel, Date fromDate, Date reduceDeadline ){
	this->id = id;
	this->reduceLevel = reduceLevel;
	this->fromDate = fromDate;
	this->reduceDeadline = reduceDeadline;
}
ostream& operator << ( ostream& os, const Voucher &voucher ){
	os << "|  " << voucher.id;
	if( voucher.reduceLevel - round(voucher.reduceLevel) != 0 )
		os << "  |     " << voucher.reduceLevel << "     |  ";
	else if( voucher.reduceLevel < 10 )
		os << "  |     " << voucher.reduceLevel << "       |  ";
	else if( voucher.reduceLevel < 100 )
		os << "  |     " << voucher.reduceLevel << "      |  ";
    else
        os << "  |     " << voucher.reduceLevel << "     |  ";
	os << voucher.fromDate << "  |  " << voucher.reduceDeadline << "   |" << endl;
	return os;
}
string Voucher::getID(){
	return id;
}
double Voucher::getReduceLevel(){
	return reduceLevel;
}
Date Voucher::getFromDate(){
	return fromDate;
}
Date Voucher::getReduceDeadline(){
	return reduceDeadline;
}
void Voucher::setID( string newId ){
	this->id = newId;
}
void Voucher::setReduceLevel( double level ){
    this->reduceLevel = level;
}
void Voucher::setFromDate( Date fDate ){
    this->fromDate = fDate;
}
void Voucher::setReduceDeadline( Date rDate ){
    this->reduceDeadline = rDate;
}
