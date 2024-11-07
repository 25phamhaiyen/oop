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
		friend istream& operator >> ( istream& is, Voucher &voucher );
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
istream& operator >> ( istream& is, Voucher &voucher ){
	time_t t = time(nullptr); // Lấy thời gian hiện tại
    tm* now = localtime(&t);
    Date nowDate(now->tm_mday, now->tm_mon+1, now->tm_year+1900);
	cout << "Nhap ma giam gia:  ";
	is >> voucher.id;
	do {
		cout << "\nNhap muc giam (%):  ";
		is >> voucher.reduceLevel;
		if( voucher.reduceLevel <= 0 || voucher.reduceLevel > 100 )
			cout << "\nMuc giam gia chi nam trong khoang ( 0 -> 100 ). Vui long nhap lai\n";
	}while( voucher.reduceLevel <= 0 || voucher.reduceLevel > 100 );
	do {
		cout << "\nNhap ngay voucher co hieu luc:  \n";
		is >> voucher.fromDate;
		if( voucher.fromDate < nowDate )
			cout << "\nNgay bat dau khuyen mai phai >= ngay hom nay. Vui long nhap lai.\n";
	}while( voucher.fromDate < nowDate );
	do {
		cout << "\nNhap ngay voucher het hieu luc:  \n";
		is >> voucher.reduceDeadline;
		if( voucher.reduceDeadline < voucher.fromDate )
			cout << "\nNgay voucher het hieu luc phai lon hon ngay bat dau co hieu luc. Vui long nhap lai\n";
	}while( voucher.reduceDeadline < voucher.fromDate );
	return is;
}
ostream& operator << ( ostream& os, const Voucher &voucher ){
	os << "|  " << voucher.id;
	if( voucher.reduceLevel - round(voucher.reduceLevel) != 0 )
		os << "  |     " << voucher.reduceLevel << "     |  ";
	else if( voucher.reduceLevel < 10 )
		os << "  |     " << voucher.reduceLevel << "       |  ";
	else
		os << "  |     " << voucher.reduceLevel << "      |  ";
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
