// Build class Date
Date::Date(){
	day = month = year = 0;
}
Date::Date( int day, int month, int year ){
	this->day = day;
	this->month = month;
	this->year = year;
}
void inputDay( int &day, int maxDay ){ // Ham check input day
	do {
		cout << "Nhap ngay:  ";
		cin >> day;
		if( day < 0 || day > maxDay )
			cout << "\nNgay phai >= 1 va <= " << maxDay << ". Vui long nhap lai\n\n";
	}while( day < 1 || day > maxDay );
}
istream& operator >> ( istream& is, Date &date ){
	do {
		cout << "Nhap nam:  ";
		is >> date.year;
		if( date.year < 1900 )
			cout << "\nNam phai >= 1900. Vui long nhap lai\n\n";
	}while( date.year < 1900 );
	do {
		cout << "Nhap thang:  ";
		is >> date.month;
		if( date.month < 1 || date.month > 12 )
			cout << "\nThang phai >= 1 va <= 12. Vui long nhap lai\n\n";
	}while( date.month < 1 || date.month > 12 );
	if( date.month == 1 || date.month == 3 || date.month == 5 || date.month == 7 || date.month == 8 || date.month == 10 || date.month == 12 )
		inputDay(date.day,31);
	else if( date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11 )
		inputDay(date.day,30);
	else {
		if( date.year % 400 == 0 || ( date.year % 4 == 0 && date.year % 100 != 0 ) ){
			inputDay(date.day,29);
			date.dayOfMonth[1] = 29;
		}	
		else 
			inputDay(date.day,28);
	}
	return is;
}
ostream& operator << ( ostream& os, Date date ){
	if( date.day > 9 )
		os << date.day << "/";
	else 
		os << "0" << date.day << "/";
	if( date.month > 9 )
		os << date.month << "-";
	else 
		os << "0" << date.month << "/";
	os << date.year;
	return os;
}
Date Date::operator = ( const Date &date ){
	Date::operator=(date);
	return *this;
}

// Build class Time
Time::Time(){
	hour = minute = 0;
}
Time::Time( int hour, int minute ){
	this->hour = hour;
	this->minute = minute;
}
istream& operator >> ( istream& is, Time &time ){
	do {
		cout << "Nhap gio:  ";
		is >> time.hour;
		if( time.hour < 0 || time.hour > 23 )
			cout << "\nGio phai >= 0 va <= 23. Vui long nhap lai\n\n";
	}while( time.hour < 0 || time.hour > 23 );
	do {
		cout << "Nhap phut:  ";
		is >> time.minute;
		if( time.minute < 0 || time.minute > 59 )
			cout << "\nPhut phai >= 0 va <= 59. Vui long nhap lai\n\n";
	}while( time.minute < 0 || time.minute > 59 );
	return is;
}
ostream& operator << ( ostream& os, Time time ){
	if( time.hour > 9 )
		os << time.hour << ":";
	else 
		os << "0" << time.hour << ":";
	if( time.minute > 9 )
		os << time.minute;
	else 
		os << "0" << time.minute;
	return os;
}
Time Time::operator = ( const Time &time ){
	Time::operator=(time); 
	return *this;
} 

// Build class Human
Human::Human(){
	name = sex = address = "";
	age = 0;
}
Human::Human( string name, Date date, string sex, int age, string address ){
	this->name = name;
	this->date = date;
	this->sex = sex;
	this->age = age;
	this->address = address;
}
Human::Human( const Human &human ){
	this->name = human.name;
	this->date = human.date;
	this->sex = human.sex;
	this->age = human.age;
	this->address = human.address;
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
	cout << "Nhap ho va ten cua ban:  "; 
	getline(is,human.name);
	do {
		cout << "Nhap tuoi:  "; 
		is >> human.age;
		if( human.age <= 0 ){
			cout << "\nSo tuoi phai > 0. Vui long nhap lai.\n\n";
			continue;
		}
		if( human.age < 13 )
			cout << "\nHang bay chi chap nhan tre tren 11 tuoi. Vui long nhap lai.\n\n";
	}while( human.age < 13 );
	char choice;
	cout << "\nChon gioi tinh cua ban:\n1.Nam\n2.Nu\n3.Tuy chinh" << endl;
	do {
		cout << "Nhap lua chon cua ban:  ";
		is >> choice;
		if( choice != '1' && choice != '2' && choice != '3' ) 
			cout << "\nBan chi duoc chon so trong khoang 1 -> 3. Vui long nhap lai.\n\n";
	}while( choice != '1' && choice != '2' && choice != '3' );
	if( choice == '1' )
		human.sex = "Nam";
	else if( choice == '2' )
		human.sex = "Nu";
	else
		human.sex = "Tuy chinh";
	cout << "Nhap ngay sinh (year/month/day):  \n";
	is >> human.date;
	cin.ignore();
	cout << "Nhap dia chi ( So nha, xa/phuong, huyen/quan, tinh/thanh pho ):  ";
	getline(is, human.address);
	return is;
}
ostream& operator << ( ostream& os, Human human ){
	os << human.name << "\t" << human.age << "\t" << human.sex << "\t" << (Date)human.date << "\t" << human.address << "\t";
	return os;
}
Human Human::operator = ( const Human &human ){
	Human::operator=(human); 
	return *this;
}

// Build class humanInPlane
humanInPlane::humanInPlane(){
	position = "";
	salary = 0;
}
void humanInPlane::setSalary( string position ){
	if( position == "Co truong" )
		this->salary = 100000;
	else if( position == "Co pho" )
		this->salary = 50000;
	else
		this->salary = 25000;
}
humanInPlane::humanInPlane( const Human &human, string position ){
	this->position = position;
	setSalary(position);
}
istream& operator >> ( istream& is, humanInPlane &hip ){
	is >> (Human&)hip;
	char choice;
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
		hip.position = "Co pho";
	else 
		hip.position = "Tiep vien";	
	hip.setSalary(hip.position);
	return is;
}
ostream& operator << ( ostream& os, humanInPlane hip ){
	os << (Human)hip << hip.position << "\t" << hip.salary << endl;
	return os;
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
			plane.planeName = "VietJet Air";
			break;
		case '3':
			plane.planeName = "Bamboo Airways";
			break;
		case '4':
			plane.planeName = "Jetstar Pacific";
			break;
	}
	cout << "\nNhap so hieu may bay:  ";
	is >> plane.aircraftNumber;
	cout << "Chon loai may bay: \n1.May bay dan dung \n2.May bay cho hang" << endl;
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
	plane.status = ( choice == '1' )?"Hoat dong":"Bao tri";
	return is;
}
ostream& operator << ( ostream& os, Plane plane ){
	os << plane.planeName << "\t" << plane.aircraftNumber << "\t" << plane.type << "\t" << plane.status << endl;
	return os;
}
string Plane::getPlaneName(){
	return this->planeName;
}
string Plane::getType(){
	return this->type;
}
string Plane::getStatus(){
	return this->status;
}
Plane Plane::operator = ( const Plane &plane ){
	Plane::operator=(plane); 
	return *this;
}

// Build class Flight 
Flight::Flight(){
	//id = mp[plane.getPlaneName()] + to_string(i++);
	departureLocation = destination = "";
	ticketPrice = 0;
}
Flight::Flight( string departureLocation, string destination, Time departureTime, Time landingTime, Date flightDate, Plane plane, double ticketPrice ){
	//id = mp[plane.getPlaneName()] + to_string(i++);
	this->departureLocation = departureLocation;
	this->destination = destination;
	this->departureTime = departureTime;
	this->landingTime = landingTime;
	this->flightDate = flightDate;
	this->plane = plane;
	this->ticketPrice = ticketPrice;
}
istream& operator >> ( istream& is, Flight &fly ){
	cout << "Nhap noi xuat phat ( Tinh hoac TP ):  ";
	getline(is, fly.departureLocation);
	cout << "Nhap noi den ( Tinh hoac TP ):  ";
	getline(is, fly.destination);
	cout << "Nhap ngay bay ( year/month/day ):  \n";
	is >> fly.flightDate;
	cout << "Nhap thoi gian khoi hanh ( hour:minute ):  \n";
	is >> fly.departureTime;
	cout << "Nhap thoi gian ha canh ( hour:minute ):  \n";
	is >> fly.landingTime;
	cout << "Nhap gia ve (.000 VND):  ";
	is >> fly.ticketPrice;
	return is;
}
ostream& operator << ( ostream& os, Flight fly ){
	os << fly.id << "\t" << fly.departureLocation << "\t" << fly.destination << "\t" << fly.flightDate << "\t" << fly.departureTime << "\t" << fly.landingTime << "\t" << fly.ticketPrice << endl;
	return os;
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
double Flight::getTicketPrice(){
	return this->ticketPrice;
}

// Build class Passeger
bool Passenger::isPassport( string passport ){
	if( passport[0] != toupper(passport[0]) )
		return false;
	for( int i = 1 ; i < 8 ; i++ ){
		if( passport[i] < '0' || passport[i] > '9' )
			return false;
	}
	return true;
}
void Passenger::setInCountry( bool check ){
	this->isInCountry = check;
}
istream& operator >> ( istream& is, Passenger &pas ){
	is >> (Human&)pas;
	do {
		cout << "Nhap so dien thoai ( 0********* ):  ";
		is >> pas.phoneNum;
		if( pas.phoneNum.size() != 10 ){
			cout << "\nSo dien thoai phai du 10 chu so. Vui long nhap lai\n\n";
			continue;
		}
		if( pas.phoneNum[0] != '0' )
			cout << "\nSo dien thoai phai bat dau bang 0. Vui long nhap lai\n\n";
	}while( pas.phoneNum.size() != 10 || pas.phoneNum[0] != '0' );
	
	if( !pas.isInCountry ){
		do {
			cout << "Nhap so ho chieu ( 1 chu IN HOA + 7 chu SO ):  ";
			is >> pas.passportNum;
			if( pas.passportNum.size() != 8 ){
				cout << "\nHo chieu phai du 8 ky tu. Vui long nhap lai\n\n";
				continue;
			}
			if( !pas.isPassport( pas.passportNum ) )
				cout << "\nBan da nhap sai format ho chieu. Vui long nhap lai\n\n";
		}while( !pas.isPassport( pas.passportNum ) || pas.passportNum.size() != 8 );
	}
	do {
		cout << "Nhap so CCCD :  ";
		is >> pas.cidNum;
		if( pas.cidNum.size() != 12 ){
			cout << "\nSo CCCD phai du 12 chu so. Vui long nhap lai\n\n";
			continue;
		}
		if( pas.cidNum[0] != '0' )
			cout << "\nSo CCCD phai bat dau bang 0. Vui long nhap lai\n\n";
	}while( pas.cidNum.size() != 12 || pas.cidNum[0] != '0' );
	return is;	
}
ostream& operator << ( ostream& os, Passenger pas ){
	os << (Human)pas;
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
