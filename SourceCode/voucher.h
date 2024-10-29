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
	cout << "Nhap ma giam gia:  ";
	is >> voucher.id;
	do {
		cout << "\nNhap muc giam (%):  ";
		is >> voucher.reduceLevel;
		if( voucher.reduceLevel <= 0 || voucher.reduceLevel > 100 )
			cout << "\nMuc giam gia chi nam trong khoang ( 0 -> 100 ). Vui long nhap lai\n";
	}while( voucher.reduceLevel <= 0 || voucher.reduceLevel > 100 );
	cout << "\nNhap ngay voucher co hieu luc:  \n";
	is >> voucher.fromDate;
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
