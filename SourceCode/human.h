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
		humanInPlane operator = ( const humanInPlane &hip );
		void setId( string id );
		void setSalary( string position );
		string getPosition() const;
		double getSalary() const;
		string getId() const;
		bool operator < (const humanInPlane& other) const;
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
		friend void findWithTicketPrice( vector<pair<Flight, string>> flight, double minPrice, double maxPrice, string rank, string area );
		friend void findWithDestination( vector<pair<Flight, string>> flight, string destination, string area );
		friend void findWithTime( vector<pair<Flight, string>> flight, Time startTime, Time endTime, string area );
		friend void findWithDate( vector<pair<Flight, string>> flight, Date date, string area );
		friend void findWithPlaneName( vector<pair<Flight,string>> flight, string plName, string area, unordered_map<string, string> planeName );
		friend void sortIncreaseTicketPrice( vector<pair<Flight, string>> flight );
};


// Build class Human
Human::Human(){
	name = sex = "";
	age = 0;
}
Human::Human( string name, Date date, string sex ){
	this->name = name;
	this->date = date;
	this->sex = sex;
	this->age = 2024-this->date.getYear();
}
Human::Human( const Human &human ){
	this->name = human.name;
	this->date = human.date;
	this->sex = human.sex;
	this->age = 2024-this->date.getYear();
}
void standarName( string &name ){
	int n = name.size();
	for( int i = 0 ; i < n ; i++ ){
        name[i] = toupper(name[i]);
	}
}
istream& operator >> ( istream& is, Human &human ){
	cin.ignore();
	cout << "\nNhap ho va ten:  ";
	getline(is,human.name);
	standarName(human.name);
	cout << "\nNhap ngay sinh (year/month/day):  \n";
	is >> human.date;
	char choice;
	cout << "\nChon gioi tinh:\n1.Nam\n2.Nu\n3.Khac\n" << endl;
	do {
		cout << "Nhap lua chon cua ban:  ";
		is >> choice;
		if( choice != '1' && choice != '2' && choice != '3' )
			cout << "\nBan chi duoc chon so trong khoang 1 -> 3. Vui long nhap lai.\n\n";
	}while( choice != '1' && choice != '2' && choice != '3' );
	if( choice == '1' )
		human.sex = "Nam";
	else if( choice == '2' )
		human.sex = "Nu ";
	else
		human.sex = "Khac";
	human.age = 2024-human.date.getYear();
	return is;
}
ostream& operator << ( ostream& os, const Human &human ){
	os << human.name << "\t" << human.age << "\t" << human.sex << "\t" << human.date << "\t";
	return os;
}
Human Human::operator = ( const Human &human ){
	if( this != &human ){
		name = human.name;
		sex = human.sex;
		date = human.date;
		this->age = 2024-this->date.getYear();
	}
	return *this;
}
string Human::getName() const{
	return name;
}
Date Human::getDate() const{
	return date;
}
string Human::getSex() const{
	return sex;
}
int Human::getAge() const{
	return age;
}


// Build class humanInPlane
humanInPlane::humanInPlane(){
	id = position = "";
	salary = 0;
}
void humanInPlane::setSalary( string position ){
	if( position == "Co truong" )
		this->salary = 100000;
	else if( position == "Co pho   " )
		this->salary = 50000;
	else
		this->salary = 25000;
}
humanInPlane::humanInPlane( const Human &human, string id, string position, double salary ) : Human(human){
    this->id = id;
	this->position = position;
	this->salary = salary;
}
istream& operator >> ( istream& is, humanInPlane &hip ){
	char choice;
	cin.ignore();
	cout << "\nChon chuc vu: \n1.Co truong \n2.Co pho \n3.Tiep vien\n\n";
	do {
		cout << "Nhap lua chon cua ban:  ";
		is >> choice;
		if( choice != '1' && choice != '2' && choice != '3' )
			cout << "\nBan chi duoc nhap trong khoang 1 -> 3. Vui long nhap lai\n\n";
	}while( choice != '1' && choice != '2' && choice != '3' );
	if( choice == '1' )
		hip.position = "Co truong";
	else if( choice == '2' )
		hip.position = "Co pho   ";
	else
		hip.position = "Tiep vien";
	hip.setSalary(hip.position);
	is >> (Human&)hip;
	return is;
}
ostream& operator << ( ostream& os, const humanInPlane &hip ){
	os << hip.id << "\t" << static_cast<const Human&>(hip) << hip.position << "\t" << hip.salary << endl;
	return os;
}
string humanInPlane::getPosition() const{
	return position;
}
string humanInPlane::getId() const{
    return id;
}
double humanInPlane::getSalary() const{
	return salary;
}
void humanInPlane::setId( string id ){
    this->id = id;
}
bool humanInPlane::operator < (const humanInPlane& other) const {
    return this->id < other.id;
}
humanInPlane humanInPlane::operator = ( const humanInPlane &hip ){
    if( this != &hip ) {
        Human::operator=(hip);
        id = hip.id;
        position = hip.position;
        salary = hip.salary;
    }
    return *this;
}


// Build class Passeger
Passenger::Passenger(){
	phoneNum = passportNum = cidNum = rank = status = "";
	position = 0;
}
Passenger::Passenger( const Human &human, string sdt, string passport, string cccd, string rank, int pos, string status ) : Human(human){
	this->phoneNum = sdt;
	this->passportNum = passport;
	this->cidNum = cccd;
	this->rank = rank;
	this->position = pos;
	this->status = status;
}
bool Passenger::isPassport( string passport ){
	if( passport[0] != toupper(passport[0]) )
		return false;
	for( int i = 1 ; i < 8 ; i++ ){
		if( passport[i] < '0' || passport[i] > '9' )
			return false;
	}
	return true;
}
bool Passenger::isPhoneNum( string phoneNum ){
	for( int i = 1 ; i < 10 ; i++ ){
		if( phoneNum[i] < '0' || phoneNum[i] > '9' ){
			return false;
		}
	}
	return true;
}
bool Passenger::isCidNum( string cidNum ){
	for( int i = 1 ; i < 12 ; i++ ){
		if( cidNum[i] < '0' || cidNum[i] > '9' ){
			return false;
		}
	}
	return true;
}
void Passenger::setInCountry( bool check ){
	this->isInCountry = check;
}
istream& operator >> ( istream& is, Passenger &pas ){
	is >> (Human&)pas;
	do {
		cout << "\nNhap so dien thoai ( 0********* ):  ";
		is >> pas.phoneNum;
		if( pas.phoneNum.size() != 10 ){
			cout << RED;
			cout << "\nSo dien thoai phai du 10 chu so. Vui long nhap lai.\n";
			cout << RESET;
			continue;
		}
		if( pas.phoneNum[0] != '0' ){
			cout << RED;
			cout << "\nSo dien thoai phai bat dau bang 0. Vui long nhap lai.\n";
			cout << RESET;
			continue;
		}
		if( !pas.isPhoneNum(pas.phoneNum) ){
			cout << RED;
			cout << "\nSo dien thoai chi chua cac chu so. Vui long nhap lai.\n";
			cout << RESET;
		}
	}while( pas.phoneNum.size() != 10 || pas.phoneNum[0] != '0' || !pas.isPhoneNum(pas.phoneNum) );

	if( !pas.isInCountry ){
		do {
			cout << "\nNhap so ho chieu ( 1 chu IN HOA + 7 chu SO ):  ";
			is >> pas.passportNum;
			if( pas.passportNum.size() != 8 ){
				cout << RED;
				cout << "\nHo chieu phai du 8 ky tu. Vui long nhap lai\n";
				cout << RESET;
				continue;
			}
			if( !pas.isPassport( pas.passportNum ) ){
				cout << RED;
				cout << "\nBan da nhap sai format ho chieu. Vui long nhap lai\n";
				cout << RESET;
			}
		}while( !pas.isPassport( pas.passportNum ) || pas.passportNum.size() != 8 );
	}
	else
		pas.passportNum = "Khong co";
	do {
		cout << "\nNhap so CCCD :  ";
		is >> pas.cidNum;
		if( pas.cidNum.size() != 12 ){
			cout << RED;
			cout << "\nSo CCCD phai du 12 chu so. Vui long nhap lai\n";
			cout << RESET;
			continue;
		}
		if( pas.cidNum[0] != '0' ){
			cout << RED;
			cout << "\nSo CCCD phai bat dau bang 0. Vui long nhap lai\n";
			cout << RESET;
			continue;
		}
		if( !pas.isCidNum(pas.cidNum) ){
			cout << RED;
			cout << "\nSo CCCD chi chua cac chu so. Vui long nhap lai.\n";
			cout << RESET;
		}
	}while( pas.cidNum.size() != 12 || pas.cidNum[0] != '0' || !pas.isCidNum(pas.cidNum) );
	char choice;
	cout << "\nQuy khach muon chon loai ghe nao: \n1.Thuong gia \n2.Pho thong\n";
	do {
		cout << "\nNhap lua chon cua ban:  ";
		is >> choice;
		if( choice != '1' && choice != '2' )
			cout << RED;
			cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai\n";
			cout << RESET;
	}while( choice != '1' && choice != '2' );
	if( choice == '1' )
		pas.rank = "Thuong gia";
	else
		pas.rank = "Pho thong ";
	pas.status = "DAT";
	return is;
}
ostream& operator << ( ostream& os, const Passenger &pas ){
	os << static_cast<const Human&>(pas);
	os << pas.phoneNum << "\t";
	if( !pas.isInCountry )
		os << pas.passportNum << "\t";
	os << pas.cidNum << "\t" << pas.rank << "\t" << pas.position << endl;
	return os;
}
void Passenger::setRank( string rank ){
	this->rank = rank;
}
void Passenger::setPosition( int position ){
	this->position = position;
}
void Passenger::setStatus( string s ){
	this->status = s;
}
string Passenger::getRank(){
	return rank;
}
int Passenger::getPos(){
	return position;
}
string Passenger::getStatus(){
	return status;
}
string Passenger::getPhoneNum(){
	return phoneNum;
}
string Passenger::getPassportNum(){
	return passportNum;
}
string Passenger::getCidNum(){
	return cidNum;
}

void findWithTicketPrice( vector<pair<Flight,string>> flight, double minPrice, double maxPrice, string rank, string area, unordered_map<string, string> planeName ){
	int count = 0;
	cout << PINK << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|    ID     |    Ngay bay    |   Lich trinh bay              | TG cat canh | TG ha canh  | Gia ve thuong | Gia ve vip | Luot dat |   Ten hang bay      |" << endl;
    cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << RESET << "\n";
	for( auto &it : flight ){
		double veThuong = it.first.getPopTicketPrice();
		double veVip = it.first.getVipTicketPrice();
		if( rank == "Pho thong" && veThuong >= minPrice && veThuong <= maxPrice ||  rank == "Thuong gia" && veVip >= minPrice && veVip <= maxPrice && it.first.getArea() == area ){
			cout << "|   " << it.first << "    " << it.first.getSitNum() << "     |   " << planeName[it.first.getId()] << "  |" << endl;
			count++;
		}
	}
	cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------+\n\n";
	if( !count ){
		system("cls");
		cout << RED;
		cout << "Khong tim thay khoang gia ve ban muon tim.\n";
		cout << RESET;
	}
}
void findWithDestination( vector<pair<Flight,string>> flight, string destination, string area, unordered_map<string, string> planeName ){
	int count = 0;
	cout << PINK << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|    ID     |    Ngay bay    |   Lich trinh bay              | TG cat canh | TG ha canh  | Gia ve thuong | Gia ve vip | Luot dat |   Ten hang bay      |" << endl;
    cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << RESET << "\n";
	for( auto &it : flight ){
		if( it.first.getDestination() == destination && it.first.getPopTicketPrice() != 0 && it.first.getArea() == area ){
			cout << "|   " << it.first << "    " << it.first.getSitNum() << "     |   " << planeName[it.first.getId()] << "  |" << endl;
			count++;
		}
	}
	cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------+\n\n";
	if( !count ){
		system("cls");
		cout << RED;
		cout << "Khong tim thay noi den ban muon tim.\n";
		cout << RESET;
	}
}
void findWithTime( vector<pair<Flight,string>> flight, Time startTime, Time endTime, string area, unordered_map<string, string> planeName ){
	int count = 0;
	cout << PINK << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|    ID     |    Ngay bay    |   Lich trinh bay              | TG cat canh | TG ha canh  | Gia ve thuong | Gia ve vip | Luot dat |   Ten hang bay      |" << endl;
    cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << RESET << "\n";
	for( auto &it : flight ){
		if( it.first.getDepartureTime() >= startTime && it.first.getLandingTime() <= endTime && it.first.getPopTicketPrice() != 0 && it.first.getArea() == area ){
			cout << "|   " << it.first << "    " << it.first.getSitNum() << "     |   " << planeName[it.first.getId()] << "  |" << endl;
			count++;
		}
	}
	cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------+\n\n";
	if( !count ){
		system("cls");
		cout << RED;
		cout << "Khong tim thay khoang thoi gian bay ban muon tim.\n";
		cout << RESET;
	}
}

void findWithFlightDate( vector<pair<Flight, string>> flight, Date date, string area, unordered_map<string, string> planeName ){
	int count = 0;
	cout << PINK << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|    ID     |    Ngay bay    |   Lich trinh bay              | TG cat canh | TG ha canh  | Gia ve thuong | Gia ve vip | Luot dat |   Ten hang bay      |" << endl;
    cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << RESET << "\n";
	for( auto &it : flight ){
		if( it.first.getFlightDate() == date && it.first.getArea() == area ){
			cout << "|   " << it.first << "    " << it.first.getSitNum() << "     |   " << planeName[it.first.getId()] << "  |" << endl;
			count++;
		}
	}
	cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------+\n\n";
	if( !count ){
		system("cls");
		cout << RED;
		cout << "Khong tim thay ngay bay ban muon tim.\n";
		cout << RESET;
	}
}
void findWithPlaneName( vector<pair<Flight,string>> flight, string plName, string area, unordered_map<string, string> planeName ){
	int count = 0;
	cout << PINK << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|    ID     |    Ngay bay    |   Lich trinh bay              | TG cat canh | TG ha canh  | Gia ve thuong | Gia ve vip | Luot dat |   Ten hang bay      |" << endl;
    cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << RESET << "\n";
	for( auto &it : flight ){
		if( planeName[it.first.getId()] == plName && it.first.getPopTicketPrice() != 0 && it.first.getArea() == area ){
			cout << "|   " << it.first << "    " << it.first.getSitNum() << "     |   " << planeName[it.first.getId()] << "  |" << endl;
			count++;
		}
	}
	cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------+\n\n";
	if( !count ){
		system("cls");
		cout << RED;
		cout << "Khong tim thay ten hang bay ban muon tim.\n";
		cout << RESET;
	}
}
void sortIncreaseTicketPrice( vector<pair<Flight, string>> &flight ){
	int n = flight.size();
    for( int i = 1 ; i < n ; i++) {
    	auto key = flight[i];
        int j = i - 1;
        while( j >= 0 && flight[j].first.getPopTicketPrice() > key.first.getPopTicketPrice() ) {
            flight[j + 1] = flight[j];
            j = j - 1;
        }
        flight[j + 1] = key;
    }
}
