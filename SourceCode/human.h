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
