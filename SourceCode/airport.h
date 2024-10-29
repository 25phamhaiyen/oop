#include "date_time.h"

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
		string getName();
		Date getDate();
		string getSex();
		int getAge();
		
};
class humanInPlane : public Human {
	private:
		string position;  // chức vụ trên máy bay( cơ trưởng, tiếp viên, cơ phó )
		double salary;
	public:
		humanInPlane();
		humanInPlane( const Human &human, string position, double salary );
		friend istream& operator >> ( istream& is, humanInPlane &hip );
		friend ostream& operator << ( ostream& os, const humanInPlane &hip );
		void setSalary( string position );
		string getPosition();
		double getSalary();
};
class Plane {
	private:
		string planeName; // tên hãng bay
		string aircraftNumber; // số hiệu máy bay
		string type;  // loại máy bay ( dân dung, chở hàng )
		string status;  // tình trạng ( bảo trì, hoạt động )
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
		void setAircraftNumber( string s );
};
class Flight {
	private:
		string id; //  mã chuyến bay
		string departureLocation;  // nơi xuất phát
		string destination; // nơi đến
		Time departureTime; // giờ khởi hành
		Time landingTime; // giờ hạ cánh
		Date flightDate; // ngày bay
		double popTicketPrice; // giá vé hạng thường
		double vipTicketPrice; // giá vé hạng thương gia
		unordered_map<int,int> sitPos; // vi tri ngoi
	public:
		Flight();
		Flight( string id, Date flightDate, string departureLocation, string destination, Time departureTime, Time landingTime, double popTicketPrice, double vipTicketPrice );
		friend istream& operator >> ( istream& is, Flight &fly );
		friend ostream& operator << ( ostream& os, const Flight &fly );
		Flight operator = ( const Flight &fly2 );
		string getId();
		string getDepartureLocation();
		string getDestination();
		Time getDepartureTime();
		Time getLandingTime();
		Date getFlightDate();
		double getPopTicketPrice();
		double getVipTicketPrice();
		void setSitPos( int pos );
		void setSitPosHuy( int pos );
		int getSitNum();
		void listVip();
		void listPopular();
		int countVip();
		int countPopular();
		
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
		friend void addFlight(vector<pair<Passenger,string>> &passenger );
		friend void findWithTicketPrice( vector<pair<Flight, string>> flight, double minPrice, double maxPrice, string rank );
		friend void findWithDestination( vector<pair<Flight, string>> flight, string destination );
		friend void findWithTime( vector<pair<Flight, string>> flight, Time startTime, Time endTime );
		friend void findWithDate( vector<pair<Flight, string>> flight, Date date );
		friend void findWithPlaneName( vector<pair<Flight, string>> flight, string planeName );
		friend void sortIncreaseTicketPrice( vector<pair<Flight, string>> flight );
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
		friend void displayHistory( vector<pair<Passenger, string>> history );
		friend void displayFlight( vector<pair<Flight, string>> flight );
		friend void displayPlane( vector<Plane> plane );
		friend void displayPassenger( vector<pair<Passenger,string>> plane );
		friend void displayHumanInPlane( vector<vector<pair<humanInPlane,string>>> personal );
		friend void displayVoucher( vector<Voucher> voucher );
		friend void inputFlight( Flight &fly );
		friend void addFlight( vector<Plane> &plane, vector<pair<Flight,string>> &flight, vector<vector<pair<humanInPlane,string>>> &personal );
		friend void addVoucher( vector<Voucher> &voucher );
		friend void displayBill( int ticketNum, vector<pair<Flight, string>> passfly, vector<pair<Passenger, string>> passenger, int voucherLevel );
};
class setUpData {
	public:
		friend Date stringToDate( string s );
		friend Time stringToTime( string s );
		friend int stringToInt( string s );
		friend void readData( vector<Plane> &plane, vector<Flight> &flight, vector<pair<Passenger,string>> &passInfo, vector<Voucher> &voucher, vector<vector<humanInPlane>> &personal );
		friend void writeData( vector<Plane> &plane, vector<Flight> &flight, vector<pair<Passenger,string>> &passInfo, vector<Voucher> &voucher, vector<vector<humanInPlane>> &personal );
		friend void updateSitPos( vector<pair<Flight, string>> &flight, vector<pair<Passenger,string>> passInfo );
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
		if( name[i] != ' ' && i == 0 || name[i] != ' ' && name[i-1] == ' ' && i-1 >= 0 )
			name[i] = toupper(name[i]);
		else
			name[i] = tolower(name[i]);
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
	cout << "\nChon gioi tinh cua ban:\n1.Nam\n2.Nu\n3.Khac\n" << endl;
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
string Human::getName(){
	return name;
}
Date Human::getDate(){
	return date;
}
string Human::getSex(){
	return sex;
}
int Human::getAge(){
	return age;
}


// Build class humanInPlane
humanInPlane::humanInPlane(){
	position = "";
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
humanInPlane::humanInPlane( const Human &human, string position, double salary ) : Human(human){
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
	os << static_cast<const Human&>(hip) << hip.position << "\t" << hip.salary << endl;
	return os;
}
string humanInPlane::getPosition(){
	return position;
}
double humanInPlane::getSalary(){
	return salary;
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
			cout << "\nSo dien thoai phai du 10 chu so. Vui long nhap lai.\n";
			continue;
		}
		if( pas.phoneNum[0] != '0' ){
			cout << "\nSo dien thoai phai bat dau bang 0. Vui long nhap lai.\n";
			continue;
		}
		if( !pas.isPhoneNum(pas.phoneNum) ){
			cout << "\nSo dien thoai chi chua cac chu so. Vui long nhap lai.\n";
		}	
	}while( pas.phoneNum.size() != 10 || pas.phoneNum[0] != '0' || !pas.isPhoneNum(pas.phoneNum) );
	
	if( !pas.isInCountry ){
		do {
			cout << "\nNhap so ho chieu ( 1 chu IN HOA + 7 chu SO ):  ";
			is >> pas.passportNum;
			if( pas.passportNum.size() != 8 ){
				cout << "\nHo chieu phai du 8 ky tu. Vui long nhap lai\n";
				continue;
			}
			if( !pas.isPassport( pas.passportNum ) )
				cout << "\nBan da nhap sai format ho chieu. Vui long nhap lai\n";
		}while( !pas.isPassport( pas.passportNum ) || pas.passportNum.size() != 8 );
	}
	else
		pas.passportNum = "Khong co";
	do {
		cout << "\nNhap so CCCD :  ";
		is >> pas.cidNum;
		if( pas.cidNum.size() != 12 ){
			cout << "\nSo CCCD phai du 12 chu so. Vui long nhap lai\n";
			continue;
		}
		if( pas.cidNum[0] != '0' ){
			cout << "\nSo CCCD phai bat dau bang 0. Vui long nhap lai\n";
			continue;
		}
		if( !pas.isCidNum(pas.cidNum) ){
			cout << "\nSo CCCD chi chua cac chu so. Vui long nhap lai.\n";
		}
	}while( pas.cidNum.size() != 12 || pas.cidNum[0] != '0' || !pas.isCidNum(pas.cidNum) );
	char choice;
	cout << "\nQuy khach muon chon loai ghe nao: \n1.Thuong gia \n2.Pho thong\n";
	do {
		cout << "\nNhap lua chon cua ban:  ";
		is >> choice;
		if( choice != '1' && choice != '2' )
			cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai\n";
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

void findWithTicketPrice( vector<pair<Flight,string>> flight, double minPrice, double maxPrice, string rank ){
	int count = 0;
	cout << endl << PINK << "|   ID" << "\t    |    Ngay bay    " << "|   Lich trinh bay\t\t     " << "| TG cat canh " << "| TG ha canh  " << "| Gia ve thuong " << "| Gia ve vip " << "| Luot dat |   " << "Ten hang bay      |\n\n" << RESET;
	for( auto &it : flight ){
		double veThuong = it.first.getPopTicketPrice();
		double veVip = it.first.getVipTicketPrice();
		if( rank == "Pho thong" && veThuong >= minPrice && veThuong <= maxPrice ||  rank == "Thuong gia" && veVip >= minPrice && veVip <= maxPrice ){
			cout << "|   " << it.first << "    " << it.first.getSitNum() << "     |   " << it.second << "  |" << endl;
			count++;
		}
	}
	if( !count )
		cout << "Khong tim thay khoang gia ve ban muon tim.\n";
}
void findWithDestination( vector<pair<Flight,string>> flight, string destination ){
	int count = 0;
	cout << endl << PINK << "|   ID" << "\t    |    Ngay bay    " << "|   Lich trinh bay\t\t     " << "| TG cat canh " << "| TG ha canh  " << "| Gia ve thuong " << "| Gia ve vip " << "| Luot dat |   " << "Ten hang bay      |\n\n" << RESET;
	for( auto &it : flight ){
		if( it.first.getDestination() == destination && it.first.getPopTicketPrice() != 0 ){
			cout << "|   " << it.first << "    " << it.first.getSitNum() << "     |   " << it.second << "  |" << endl;
			count++;
		}
	}
	if( !count )
		cout << "Khong tim thay noi den ban muon tim.\n";
}
void findWithTime( vector<pair<Flight,string>> flight, Time startTime, Time endTime ){
	int count = 0;
	cout << endl << PINK << "|   ID" << "\t    |    Ngay bay    " << "|   Lich trinh bay\t\t     " << "| TG cat canh " << "| TG ha canh  " << "| Gia ve thuong " << "| Gia ve vip " << "| Luot dat |   " << "Ten hang bay      |\n\n" << RESET;
	for( auto &it : flight ){
		if( it.first.getDepartureTime() >= startTime && it.first.getLandingTime() <= endTime && it.first.getPopTicketPrice() != 0 ){
			cout << "|   " << it.first << "    " << it.first.getSitNum() << "     |   " << it.second << "  |" << endl;
			count++;
		}
	}
	if( !count )
		cout << "Khong tim thay khoang thoi gian bay ban muon tim.\n";
}

void findWithFlightDate( vector<pair<Flight, string>> flight, Date date ){
	int count = 0;
	cout << endl << PINK << "|   ID" << "\t    |    Ngay bay    " << "|   Lich trinh bay\t\t     " << "| TG cat canh " << "| TG ha canh  " << "| Gia ve thuong " << "| Gia ve vip " << "| Luot dat |   " << "Ten hang bay      |\n\n" << RESET;
	for( auto &it : flight ){
		if( it.first.getFlightDate() == date ){
			cout << "|   " << it.first << "    " << it.first.getSitNum() << "     |   " << it.second << "  |" << endl;
			count++;
		}
	}
	if( !count )
		cout << "Khong tim thay ngay bay ban muon tim.\n";
}
void findWithPlaneName( vector<pair<Flight,string>> flight, string planeName ){
	int count = 0;
	cout << endl << PINK << "|   ID" << "\t    |    Ngay bay    " << "|   Lich trinh bay\t\t     " << "| TG cat canh " << "| TG ha canh  " << "| Gia ve thuong " << "| Gia ve vip " << "| Luot dat |   " << "Ten hang bay      |\n\n" << RESET;
	for( auto &it : flight ){
		if( it.second == planeName && it.first.getPopTicketPrice() != 0 ){
			cout << "|   " << it.first << "    " << it.first.getSitNum() << "     |   " << it.second << "  |" << endl;
			count++;
		}
	}
	if( !count )
		cout << "Khong tim thay ten hang bay ban muon tim.\n";
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
void addFlight( vector<pair<Passenger,string>> &passInfo, vector<pair<Passenger,string>> &history ){
	Passenger p;
	cin >> p;
	history.push_back(make_pair(p,""));
	for( auto &it : passInfo ){
		if( it.first.getPhoneNum() == p.getPhoneNum() && it.first.getCidNum() == p.getCidNum() )
			return;
	}
	passInfo.push_back(make_pair(p,""));
}


// Build class Plane
Plane::Plane(){
	planeName = aircraftNumber = type = status = "";
}
Plane::Plane( string planeName, string aircraftNumber, string type, string status ){
	this->planeName = planeName;
	this->aircraftNumber = aircraftNumber;
	this->type = type;
	this->status = status;
}
istream& operator >> ( istream& is, Plane &plane ){
	cout << "Chon 1 trong cac hang bay duoi: \n1.VietNam Airlines \n2.VietJet Air \n3.Bamboo Airways \n4.Jetstar Pacific\n" << endl;
	char choice;
	do {
		cout << "Nhap lua chon cua ban:  ";
		is >> choice;
		if( choice > '4' || choice < '1' )
			cout << "\nBan chi duoc chon so trong khoang 1 -> 4. Vui long nhap lai.\n\n";
	}while( choice > '4' || choice < '1' );
	switch( choice ){
		case '1':
			plane.planeName = "VietNam Airlines";
			break;
		case '2':
			plane.planeName = "VietJet Air     ";
			break;
		case '3':
			plane.planeName = "Bamboo Airways  ";
			break;
		case '4':
			plane.planeName = "Jetstar Pacific ";
			break;
	}
	cout << "\nNhap so hieu may bay:  ";
	is >> plane.aircraftNumber;
	cout << "\nChon loai may bay: \n1.May bay dan dung \n2.May bay cho hang" << endl;
	do {
		cout << "\nNhap lua chon cua ban:  ";
		is >> choice;
		if( choice != '2' && choice != '1' )
			cout << "\nBan chi duoc chon 1 hoac 2. Vui long nhap lai.\n\n";
	}while( choice != '2' && choice != '1' );
	plane.type = ( choice == '1' )?"Dan dung":"Cho hang";
	cout << "\nTinh trang: \n1.Dang hoat dong \n2.Dang bao tri" << endl;
	do {
		cout << "\nNhap lua chon cua ban:  ";
		is >> choice;
		if( choice != '2' && choice != '1' )
			cout << "\nBan chi duoc chon 1 hoac 2. Vui long nhap lai.\n\n";
	}while( choice != '2' && choice != '1' );
	plane.status = ( choice == '1' )?"Hoat dong":"Bao tri  ";
	return is;
}
ostream& operator << ( ostream& os, const Plane &plane ){
	os << plane.planeName << "\t" << plane.aircraftNumber << "\t" << plane.type << "\t" << plane.status << endl;
	return os;
}
string Plane::getPlaneName(){
	return planeName;
}
string Plane::getType(){
	return type;
}
string Plane::getStatus(){
	return status;
}
string Plane::getAircraftNumber(){
	return aircraftNumber;
}
Plane Plane::operator = ( const Plane &plane ){
	Plane::operator=(plane); 
	return *this;
}
void Plane::setAircraftNumber( string s ){
	this->aircraftNumber = s;
}


// Build class Flight 
Flight::Flight(){
	id = departureLocation = destination = "";
	vipTicketPrice = popTicketPrice = 0;
	departureTime = Time(); 
    landingTime = Time(); 
    flightDate = Date();
}
Flight::Flight( string id, Date flightDate, string departureLocation, string destination, Time departureTime, Time landingTime, double popTicketPrice, double vipTicketPrice ){
	this->id = id;
	this->departureLocation = departureLocation;
	this->destination = destination;
	this->departureTime = departureTime;
	this->landingTime = landingTime;
	this->flightDate = flightDate;
	this->popTicketPrice = popTicketPrice;
	this->vipTicketPrice = vipTicketPrice;
}
istream& operator >> ( istream& is, Flight &fly ){
	fly.departureLocation = "Sai Gon";
	cin.ignore();
	cout << "\nNhap ID chuyen bay: ";
	is >> fly.id;
	cin.ignore();
	cout << "\nNhap noi den ( Tinh hoac TP ):  ";
	getline(is, fly.destination);
	cout << "\nNhap ngay bay ( year/month/day ):  \n";
	is >> fly.flightDate;
	cout << "\nNhap thoi gian khoi hanh ( hour:minute ):  \n";
	is >> fly.departureTime;
	do {
		cout << "\nNhap thoi gian ha canh ( hour:minute ):  \n";
		is >> fly.landingTime;
		if( fly.landingTime < fly.departureTime )
			cout << "\nThoi gian ha canh phai lon hon thoi gian khoi hanh. Vui long nhap lai\n";
	}while( fly.landingTime < fly.departureTime );
	do {
		cout << "\nNhap gia ve hang thuong (.000 VND):  ";
		is >> fly.popTicketPrice;
		if( fly.popTicketPrice <= 0 )
			cout << "\nGia ve phai lon hon 0. Vui long nhap lai\n";
	}while( fly.popTicketPrice <= 0 );
	do {
		cout << "\nNhap gia ve hang thuong gia (.000 VND):  ";
		is >> fly.vipTicketPrice;
		if( fly.vipTicketPrice <= 0 ){
			cout << "\nGia ve phai lon hon 0. Vui long nhap lai\n";
			continue;
		}
		if( fly.vipTicketPrice <= fly.popTicketPrice )
			cout << "\nGia ve hang thuong gia phai lon hon gia ve hang thuong. Vui long nhap lai\n";
	}while( fly.vipTicketPrice <= 0 || fly.vipTicketPrice <= fly.popTicketPrice );
	return is;
}
ostream& operator << ( ostream& os, const Flight &fly ){
	os << fly.id << "   |   " << fly.flightDate << "   |   from " << fly.departureLocation << " to " << fly.destination << "   |    " << fly.departureTime << "    |    " << fly.landingTime << "    |     " << fly.popTicketPrice  << "      |    ";
	if( fly.vipTicketPrice >= 10000 )
		cout << fly.vipTicketPrice << "   |";
	else
		cout << fly.vipTicketPrice << "    |";
	return os;
}
Flight Flight::operator = ( const Flight &fly2 ){
	this->id = fly2.id;
	this->flightDate = fly2.flightDate;
	this->departureLocation = fly2.departureLocation;
	this->destination = fly2.destination;
	this->departureTime = fly2.departureTime;
	this->landingTime = fly2.landingTime;
	this->popTicketPrice = fly2.popTicketPrice;
	this->vipTicketPrice = fly2.vipTicketPrice;
	return *this;
	
}
string Flight::getDepartureLocation(){
	return this->departureLocation;
}
string Flight::getDestination(){
	return this->destination;
}
Time Flight::getDepartureTime(){
	return this->departureTime;
}
Time Flight::getLandingTime(){
	return this->landingTime;
}
Date Flight::getFlightDate(){
	return this->flightDate;
}
double Flight::getPopTicketPrice(){
	return this->popTicketPrice;
}
double Flight::getVipTicketPrice(){
	return this->vipTicketPrice;
}
void Flight::setSitPos( int pos ){
	sitPos[pos] = 1;
}
void Flight::setSitPosHuy( int pos ){
	sitPos[pos] = 0;
}
string Flight::getId(){
	return id;
}
int Flight::getSitNum(){
	int count = 0;
	for( int i = 0 ; i < 51 ; i++ ){
		if( sitPos[i] == 1 )
			count++;
	}
	return count;
}
void Flight::listVip(){
	cout << endl << "Nhung vi tri ghe ngoi hang THUONG GIA con trong: \n{ ";
	for( int i = 1 ; i <= 15 ; i++ ){
		if( sitPos[i] != 0 )
			continue;
		cout << i << ", ";
	}
	cout << "}";
}
void Flight::listPopular(){
	cout << endl << "Nhung vi tri ghe ngoi hang PHO THONG con trong: \n{ ";
	for( int i = 16 ; i <= 50 ; i++ ){
		if( sitPos[i] != 0 )
			continue;
		cout << i << ", ";
	}
	cout << "}";
}
int Flight::countVip(){
	int cnt = 0;
	for( int i = 1 ; i < 16 ; i++ ){
		if( sitPos[i] == 0 )
			cnt++;
	}
	return cnt;
}
int Flight::countPopular(){
	int cnt = 0;
	for( int i = 16 ; i < 51 ; i++ ){
		if( sitPos[i] == 0 )
			cnt++;
	}
	return cnt;
}

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


// build class setUpData
Date stringToDate( string s ){
	int date[3];
	int count = 0;
	string tmp = "";
	for( int i = 0 ; i < s.size() ; i++ ){
		if( s[i] != '/' )
			tmp += s[i];
		else {
			date[count] = stoi(tmp);
			count++;
			tmp = "";
		}
	}
	date[count] = stoi(tmp);
	return Date(date[0],date[1],date[2]);
}
Time stringToTime( string s ){
	return Time(stoi(s.substr(0,2)),stoi(s.substr(3,2)));
}
int stringToInt( string s ){
	int ans = 0;
	for( int i = 0 ; i < s.size() ; i++ ){
		if( s[i] >= '0' && s[i] <= '9'){
			int x = s[i]-'0';
			ans = ans*10 + x;
		}
	}
	return ans;
}
void readData( vector<pair<Plane, string>> &plane, vector<pair<Flight, string>> &flight, vector<pair<Passenger,string>> &passInfo, vector<Voucher> &voucher, vector<vector<pair<humanInPlane, string>>> &personal, vector<pair<Passenger,string>> &history ){
	ifstream file;
	file.open("../Database/PlaneData.txt");
	string line;
	while( getline(file, line) ) {
		stringstream ss(line);
	        string name, num, type, status, id;
	        getline(ss, name, ',');
	        getline(ss, num, ',');
	        getline(ss, type, ',');
	        getline(ss, status, ',');
	        getline(ss, id, ',');
	        plane.push_back(make_pair(Plane(name, num, type, status),id));
	    }
	file.close();
	    
	file.open("../Database/FlightData.txt");
	while( getline(file, line) ) {
	        stringstream ss(line);
	        string id, date, firstLocal, secondLocal, firstTime, secondTime, popPrice, vipPrice, planeName;
	        getline(ss, id, ',');
	        getline(ss, date, ',');
	        getline(ss, firstLocal, ',');
	        getline(ss, secondLocal, ',');
	        getline(ss, firstTime, ',');
	        getline(ss, secondTime, ',');
	        getline(ss, popPrice, ',');
	        getline(ss, vipPrice, ',');
	        getline(ss, planeName, ',');
	        flight.push_back(make_pair(Flight(id, stringToDate(date), firstLocal, secondLocal, stringToTime(firstTime), stringToTime(secondTime), stringToInt(popPrice), stringToInt(vipPrice)), planeName));
	    }
	file.close();
	    
	file.open("../Database/VoucherData.txt");
	while( getline(file, line) ) {
	        stringstream ss(line);
	        string id, level, firstDate, lastDate;
	        getline(ss, id, ',');
	        getline(ss, level, ',');
	        getline(ss, firstDate, ',');
	        getline(ss, lastDate, ',');
	        voucher.push_back(Voucher(id, stod(level), stringToDate(firstDate), stringToDate(lastDate)));
	    }
	    file.close();
	    
	file.open("../Database/PassengerData.txt");
	while( getline(file, line) ) {
	        stringstream ss(line);
	        string name, date, sex, age, sdt, passport, cccd, rank, pos, status, id;
	        getline(ss, name, ',');
	        getline(ss, date, ',');
	        getline(ss, sex, ',');
	        getline(ss, sdt, ',');
	        getline(ss, passport, ',');
	        getline(ss, cccd, ',');
	        getline(ss, rank, ',');
	        getline(ss, pos, ',');
	        getline(ss, status, ',');
	        getline(ss, id, ',');
	        passInfo.push_back(make_pair(Passenger(Human(name, stringToDate(date), sex ), sdt, passport, cccd, rank, stringToInt(pos), status ),id));
	    }
	file.close();
	    
	file.open("../Database/HistoryData.txt");
	while( getline(file, line) ) {
	        stringstream ss(line);
	        string name, date, sex, age, sdt, passport, cccd, rank, pos, status, id;
	        getline(ss, name, ',');
	        getline(ss, date, ',');
	        getline(ss, sex, ',');
	        getline(ss, sdt, ',');
	        getline(ss, passport, ',');
	        getline(ss, cccd, ',');
	        getline(ss, rank, ',');
	        getline(ss, pos, ',');
	        getline(ss, status, ',');
	        getline(ss, id, ',');
	        history.push_back(make_pair(Passenger(Human(name, stringToDate(date), sex ), sdt, passport, cccd, rank, stringToInt(pos), status ),id));
	    }
	file.close();
	    
	file.open("../Database/HumanInPlaneData.txt");
	int count = 0;
	vector<pair<humanInPlane,string>> tmp;
	    while( getline(file, line) ) {
	        stringstream ss(line);
	        string name, date, sex, age, job, salary, aircraftNum;
	        getline(ss, name, ',');
	        getline(ss, date, ',');
	        getline(ss, sex, ',');
	        getline(ss, job, ',');
	        getline(ss, salary, ',');
	        getline(ss, aircraftNum, ',');
	        count++;
	        if( count == 3 && job != "Tiep vien" ){
	        	personal.push_back(tmp);
	        	tmp.clear();
	        	tmp.push_back(make_pair(humanInPlane(Human(name, stringToDate(date), sex ), job, stringToInt(salary) ), aircraftNum));
	        	count = 0;
		}
	        else if( count != 4 )
	        	tmp.push_back(make_pair(humanInPlane(Human(name, stringToDate(date), sex ), job, stringToInt(salary) ), aircraftNum));
	        else {
	        	tmp.push_back(make_pair(humanInPlane(Human(name, stringToDate(date), sex ), job, stringToInt(salary) ), aircraftNum));
	        	personal.push_back(tmp);
	        	tmp.clear();
	        	count = 0;
		}
	    }
	if( !tmp.empty() ) 
	    personal.push_back(tmp);
	file.close();
}
void writeFile( vector<pair<Plane, string>> &plane, vector<pair<Flight, string>> &flight, vector<pair<Passenger,string>> &passInfo, vector<Voucher> &voucher, vector<vector<pair<humanInPlane, string>>> &personal, vector<pair<Passenger,string>> &history ){
	// ghi file du lieu cua Plane
	ofstream file;
	file.open("../Database/PlaneData.txt",ios::trunc);
	string str = "";
    if( file.is_open() ) {
        for( auto &it : plane ){
        	str = it.first.getPlaneName() + "," + it.first.getAircraftNumber() + "," + it.first.getType() + "," + it.first.getStatus()+ "," + it.second;
	        file << str << endl;
	        str = "";
	    }  
    } 
    file.close();
    
    // ghi file du lieu cua Flight
    file.open("../Database/FlightData.txt",ios::trunc);
    if( file.is_open() ) {
        for( auto &it : flight ){
	        file << it.first.getId() << "," << it.first.getFlightDate() << "," << it.first.getDepartureLocation() << "," << it.first.getDestination() << "," << it.first.getDepartureTime() << "," 
				<< it.first.getLandingTime() << ","<< it.first.getPopTicketPrice() << "," << it.first.getVipTicketPrice() << "," << it.second << endl;
	    }  
    } 
    file.close();
    
    // ghi file dư lieu cua Passenger
    file.open("../Database/PassengerData.txt",ios::trunc);
    if( file.is_open() ) {
        for( auto &it : passInfo ){
	        file << it.first.getName() << "," << it.first.getDate() << "," << it.first.getSex() << "," << it.first.getPhoneNum() << "," << it.first.getPassportNum() << "," 
				<< it.first.getCidNum() << ","<< it.first.getRank() << "," << it.first.getPos() << "," << it.second << endl;
	    }  
    } 
    file.close();
    
     // ghi file dư lieu cua personal
    file.open("../Database/PersonalData.txt",ios::trunc);
    if( file.is_open() ) {
        for( auto &it : personal ){
        	for( auto i : it )
		        file << i.first.getName() << "," << i.first.getDate() << "," << i.first.getSex() << "," << i.first.getPosition() << "," << i.first.getSalary() << "," << i.second << endl;
	    }  
    } 
    file.close();
    
    // ghi file dư lieu cua personal
    file.open("../Database/HistoryData.txt",ios::trunc);
    if( file.is_open() ) {
        for( auto &it : personal ){
        	for( auto i : it )
		        file << i.first.getName() << "," << i.first.getDate() << "," << i.first.getSex() << "," << i.first.getPosition() << "," << i.first.getSalary() << "," << i.second << endl;
	    }  
    } 
    file.close();
    
}
void updateSitPos( vector<pair<Flight, string>> &flight, vector<pair<Passenger,string>> passInfo ){
	for( auto &it : passInfo ){
		for( auto &fly : flight ){
			if( fly.first.getId() == it.second ){
				fly.first.setSitPos( it.first.getPos() );
			}
		}
	}
}

// build class Manager
void displayFlight( vector<pair<Flight,string>> flight ){
	cout << endl << PINK << "|   ID" << "\t    |    Ngay bay    " << "|   Lich trinh bay\t\t     " << "| TG cat canh " << "| TG ha canh  " << "| Gia ve thuong " << "| Gia ve vip " << "| Luot dat |   " << "Ten hang bay      |\n\n" << RESET;
	if( flight.empty() )
		cout << "Khong co chuyen bay nao de hien thi.\n";
	for( auto &it : flight ){
		if( it.first.getPopTicketPrice() != 0 )
			cout << "|   " << it.first << "    " << it.first.getSitNum() << "     |   " << it.second << "  |" << endl;
	}
}
void displayPassenger( vector<pair<Passenger,string>> passInfo ){
	cout << PINK << "|   Ho va ten\t  " << "|   Ngay sinh\t   " << "| Gioi tinh " << "|  Tuoi  " << "| So dien thoai  " << "| So ho chieu  " << "|   So CCCD\t   |"  << RESET << "\n\n"; 
	if( passInfo.empty() )
		cout << "Khong co hanh khach nao de hien thi.\n";
	for( auto it : passInfo ){
		cout << "|   " << it.first.getName() << "  |   " << it.first.getDate() << "   |    " << it.first.getSex() << "    |   " << it.first.getAge() << "   |   "
		<< it.first.getPhoneNum() << "   |   " <<  it.first.getPassportNum() << "   |   " << it.first.getCidNum() << "   |   " << endl; 
	}
}
void displayHistory( vector<pair<Passenger,string>> history ){
	cout << PINK << "|   Ho va ten\t  " << "|   Ngay sinh\t   " << "| Gioi tinh " << "|  Tuoi  " << "|    Hang ghe    " << "| Vi tri ghe " << "| Trang thai " <<  "| Ma chuyen bay |" << RESET << "\n\n"; 
	if( history.empty() )
		cout << "Khong co lich su dat ve nao de hien thi.\n";
	for( auto it : history ){
		cout << "|   " << it.first.getName() << "  |   " << it.first.getDate() << "   |    " << it.first.getSex() << "    |   " << it.first.getAge() << "   |   " << it.first.getRank() << "   |     ";
		if( it.first.getPos() < 10 )
			cout << it.first.getPos() << "      |     ";
		else
			cout << it.first.getPos() << "     |     ";
		cout << it.first.getStatus() << "    |     " << it.second << "     |" << endl;
	}
}
void displayPlane( vector<pair<Plane, string>> plane ){
	cout << PINK << "|   Ten hang bay  " << "    | So hieu may bay " << "|  Loai may bay  " << "|   Tinh trang  |" << RESET << "\n\n"; 
	if( plane.empty() )
		cout << "Khong co may bay nao de hien thi.\n";
	for( auto &it : plane ){
		cout << "|   " << it.first.getPlaneName() << "  |      " << it.first.getAircraftNumber() << "      |    " << it.first.getType() << "    |   " << it.first.getStatus() << "   |" << endl;
	}
}
void displayHumanInPlane( vector<vector<pair<humanInPlane, string>>> personal ){
	cout << PINK << "|   Ho va ten \t  " << "|   Ngay sinh    " << "| Gioi tinh " << "|  Tuoi  " << "|    Vi tri\t" << "| Luong(.000 VND) " << "| SHMB phu trach |"<< RESET << "\n\n\n"; 
	if( personal.empty() )
		cout << "Khong co Nhan su nao de hien thi.\n";
	for( auto &it : personal ){
		for( auto &i : it ){
			cout << "|   " << i.first.getName() << "  |   " << i.first.getDate() << "   |    " << i.first.getSex() << "    |   " << i.first.getAge() << "   |   " << i.first.getPosition() << "   |      ";
			if( i.first.getSalary() == 100000 )
				cout << i.first.getSalary() << "     |     " << i.second << "      |\n";
			else
				cout << i.first.getSalary() << "      |     " << i.second << "      |\n";	
		}
		cout << endl;
	}
}
void displayVoucher( vector<Voucher> voucher ){
	cout << PINK << "|   ID   " << "| Muc giam(%) " << "| Ngay bat dau " << "| Ngay ket thuc |\n\n" << RESET;
	if( voucher.empty() )
		cout << "Khong co Voucher nao de hien thi.\n";
	for( auto &it : voucher ){
		cout << it;
	}
}
void inputFlight( Flight &fly, unordered_map<string,int> &checkid ){
	time_t t = time(nullptr); // Lấy thời gian hiện tại
    tm* now = localtime(&t); 
    string id, destination;
    Time dpTime, ldTime;
    double pop, vip;
    Date date;
    Date nowDate(now->tm_mday, now->tm_mon+1, now->tm_year+1900);
    do {
    	cout << "\nNhap ID chuyen bay: ";
		cin >> id;
		if( checkid[id] != 0 )
			cout << "\nID da ton tai. Vui long nhap lai.\n";
	}while( checkid[id] != 0 );
	checkid[id]++;
	cin.ignore();
	cout << "\nNhap noi den ( Tinh hoac TP ):  ";
	getline(cin, destination);
	do {
		cout << "\nNhap ngay bay ( year/month/day ):  \n";
		cin >> date;
		if( date < nowDate )
			cout << "\nNgay bay phai lon hon ngay hom nay. Vui long nhap lai.\n";
	}while( date < nowDate );
	cout << "\nNhap thoi gian khoi hanh ( hour:minute ):  \n";
	cin >> dpTime;
	do {
		cout << "\nNhap thoi gian ha canh ( hour:minute ):  \n";
		cin >> ldTime;
		if( ldTime < dpTime )
			cout << "\nThoi gian ha canh phai lon hon thoi gian khoi hanh. Vui long nhap lai\n";
	}while( ldTime < dpTime );
	do {
		cout << "\nNhap gia ve hang thuong (.000 VND):  ";
		cin >> pop;
		if( pop <= 0 )
			cout << "\nGia ve phai lon hon 0. Vui long nhap lai\n";
	}while( pop <= 0 );
	do {
		cout << "\nNhap gia ve hang thuong gia (.000 VND):  ";
		cin >> vip;
		if( vip <= 0 ){
			cout << "\nGia ve phai lon hon 0. Vui long nhap lai\n";
			continue;
		}
		if( vip <= pop )
			cout << "\nGia ve hang thuong gia phai lon hon gia ve hang thuong. Vui long nhap lai\n";
	}while( vip <= 0 || vip <= pop );
	Flight flight(id,date,"Sai gon",destination, dpTime, ldTime, pop, vip);
	fly = flight;
}
void addFlight( vector<pair<Plane, string>> &plane, vector<pair<Flight,string>> &flight, vector<vector<pair<humanInPlane,string>>> &personal, unordered_map<string, int> &checkid ){
	cout << endl;
	Plane p;
	Flight fly;
	vector<pair<humanInPlane,string>> human;
	humanInPlane hip;
	cout << "Nhap thong tin may bay:\n\n";
	cin >> p;
	string num = p.getAircraftNumber();
	while( checkid[num] != 0 ){
		cout << "\nSo hieu may bay vua nhap da ton tai. Vui long nhap lai\n";
		cout << "\nNhap so hieu may bay:  ";
		cin >> num;
	}
	checkid[num]++;
	p.setAircraftNumber(num);
	system("cls");
	cout << "Nhap thong tin chuyen bay:\n";
	inputFlight(fly, checkid);
	system("cls");
	cout << "Nhap thong tin nhan su ( 1 Co truong, 1 Co pho, 2 Tiep vien ):\n";
	for( int i = 0 ; i < 4 ; i++ ){
		cin >> hip;
		cout << endl;
		human.push_back(make_pair(hip,p.getAircraftNumber()));
	}
	personal.push_back(human);
	flight.push_back(make_pair(fly,p.getPlaneName()));
	plane.push_back(make_pair(p,fly.getId()));
}
void addVoucher( vector<Voucher> &voucher ){
	Voucher vou;
	cin >> vou;
	voucher.push_back(vou);
}
void displayBill( int ticketNum, vector<pair<Flight, string>> passfly, vector<pair<Passenger, string>> passenger, int voucherLevel, unordered_map<string,int> idmap ){
	double total = 0;
	for( auto &it : passenger ){
		for( auto &i : passfly ){
			if( it.first.getRank() == "Thuong gia" && i.first.getId() == it.second )
				total += i.first.getVipTicketPrice();
			else if( it.first.getRank() == "Pho thong " && i.first.getId() == it.second )
				total += i.first.getPopTicketPrice();
		}
	}
	double real = total - total*voucherLevel/100;
	time_t t = time(nullptr); // Lấy thời gian hiện tại
    tm* now = localtime(&t); 
	cout << PINK << "---------------------------------------BILL THANH TOAN-----------------------------------------\n" << RESET;
	cout << " So luong ve da dat:  " << ticketNum << endl;
	cout << "-----------------------------------------------------------------------------------------------\n";
	cout << " Thong tin dat cho:\n\n";
	cout << " Trang thai dat cho:  Da xac nhan  \t\t\t\tNguoi dat:  " << passenger[0].first.getName() << endl;
	cout << " Ngay dat:  " << now->tm_mday << "/" << (now->tm_mon + 1) << "/" << (now->tm_year + 1900) << "\t\t\t\t\t\tLien lac:  " << passenger[0].first.getPhoneNum() << endl;
	cout << "-----------------------------------------------------------------------------------------------\n";
	cout << " Thong tin hanh khach:\n\n";
	cout << PINK << "|   Ho va ten\t  " << " |    Hang ghe    " << "| Vi tri ghe " <<  "| Ma chuyen bay |" << RESET << "\n\n"; 
	for( auto it : passenger ){
		cout << "|   " << it.first.getName() << "   |   " << it.first.getRank() << "   |     ";
		if( it.first.getPos() < 10 )
			cout << it.first.getPos() << "      |     ";
		else
			cout << it.first.getPos() << "     |     ";
		cout << it.second << "     |" << endl;
	}
	cout << "\n------------------------------------------------------------------------------------------------\n";
	cout << " Thong tin chuyen bay:\n";
	cout << endl << PINK << "|   ID" << "\t    |    Ngay bay    " << "|   Lich trinh bay\t\t     " << "| TG cat canh " << "| TG ha canh  |\n\n" << RESET;
	for( auto &it : passfly ){
		if( idmap[it.first.getId()] != 0 )
			cout << "|   " << it.first.getId() << "   |   " << it.first.getFlightDate() << "   |   from " << it.first.getDepartureLocation() << " to " << it.first.getDestination() << "   |    " 
				<< it.first.getDepartureTime() << "    |    " << it.first.getLandingTime() << "    |\n";
	}
	cout << "\n------------------------------------------------------------------------------------------------\n";
	cout << " Tong tien ve:  " << total << " (Nghin VND)" << endl;
	cout << " Khuyen mai:  " << total*voucherLevel/100 << " (Nghin VND)" << endl;
	cout << " So tien phai thanh toan:  " << real << " (Nghin VND)" << endl;
	cout << "------------------------------------------------------------------------------------------------\n";
}
void displayMenuManager(){
	cout << "---------------------MENU-----------------------\n\n";
	cout << "1. Hien thi danh sach may bay.\n";
	cout << "2. Hien thi danh sach chuyen bay.\n";
	cout << "3. Hien thi danh sach thong tin nguoi dung.\n";
	cout << "4. Hien thi danh sach luot dat ve.\n";
	cout << "5. Hien thi danh sach nhan su.\n";
	cout << "6. Hien thi danh sach Voucher.\n";
	cout << "7. Them thong tin chuyen bay.\n";
	cout << "8. Them Voucher.\n";
	cout << "T. Thoat.\n\n";
	cout << "------------------------------------------------\n";
}
void displayMenuUser(){
	cout << "-----------------------MENU------------------------\n\n";
	cout << "1. Dat ve." << endl;
	cout << "2. Hien thi danh sach chuyen bay." << endl;
    cout << "3. Huy chuyen bay." << endl;
    cout << "4. Xem lich su dat ve." << endl;
    cout << "5. Xuat Bill dat ve." << endl;
    cout << "6. Thoat." << endl << endl;
    cout << "---------------------------------------------------\n";
}