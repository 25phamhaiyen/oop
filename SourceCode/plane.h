#pragma once
#include "date_time.h"
class Plane
{
private:
	string planeName;	   // tên hãng bay
	string aircraftNumber; // số hiệu máy bay
	string type;		   // loại máy bay ( dân dung, chở hàng )
	string status;		   // tình trạng ( bảo trì, hoạt động )
public:
	// hàm khởi tạo
	Plane();
	Plane(string planeName, string aircraftNumber, string type, string status);
	// hàm nhập xuất
	friend istream &operator>>(istream &is, Plane &plane);
	friend ostream &operator<<(ostream &os, const Plane &plane);
	// toán tử gán
	Plane operator=(const Plane &plane);
	// các hàm lấy và gán giá trị
	string getPlaneName();
	string getStatus();
	string getType();
	string getAircraftNumber();
	void setAircraftNumber(string s);
	void setPlaneName(string s);
	void setType(string s);
	void setStatus(string s);
};

// Build class Plane
Plane::Plane()
{
	planeName = aircraftNumber = type = status = "";
}
Plane::Plane(string planeName, string aircraftNumber, string type, string status)
{
	this->planeName = planeName;
	this->aircraftNumber = aircraftNumber;
	this->type = type;
	this->status = status;
}
istream &operator>>(istream &is, Plane &plane)
{
	cout << "Chon 1 trong cac hang bay duoi: \n1.VietNam Airlines \n2.VietJet Air \n3.Bamboo Airways \n4.Jetstar Pacific\n"
		 << endl;
	char choice;
	do
	{
		cout << "Nhap lua chon cua ban:  ";
		is >> choice;
		if (choice > '4' || choice < '1')
			cout << "\nBan chi duoc chon so trong khoang 1 -> 4. Vui long nhap lai.\n\n";
	} while (choice > '4' || choice < '1');
	switch (choice)
	{
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
	cout << "\nChon loai may bay: \n1.May bay dan dung \n2.May bay cho hang" << endl;
	do
	{
		cout << "\nNhap lua chon cua ban:  ";
		is >> choice;
		if (choice != '2' && choice != '1')
			cout << "\nBan chi duoc chon 1 hoac 2. Vui long nhap lai.\n\n";
	} while (choice != '2' && choice != '1');
	plane.type = (choice == '1') ? "Dan dung" : "Cho hang";
	cout << "\nTinh trang: \n1.Hoat dong \n2.Bao tri" << endl;
	do
	{
		cout << "\nNhap lua chon cua ban:  ";
		is >> choice;
		if (choice != '2' && choice != '1')
			cout << "\nBan chi duoc chon 1 hoac 2. Vui long nhap lai.\n\n";
	} while (choice != '2' && choice != '1');
	plane.status = (choice == '1') ? "Hoat dong" : "Bao tri  ";
	return is;
}
ostream &operator<<(ostream &os, const Plane &plane)
{
	os << plane.planeName << "\t" << plane.aircraftNumber << "\t" << plane.type << "\t" << plane.status << endl;
	return os;
}
string Plane::getPlaneName()
{
	return planeName;
}
string Plane::getType()
{
	return type;
}
string Plane::getStatus()
{
	return status;
}
string Plane::getAircraftNumber()
{
	return aircraftNumber;
}
Plane Plane::operator=(const Plane &plane)
{
	Plane::operator=(plane);
	return *this;
}
void Plane::setAircraftNumber(string s)
{
	this->aircraftNumber = s;
}
void Plane::setPlaneName(string s)
{
	this->planeName = s;
}
void Plane::setType(string s)
{
	this->type = s;
}
void Plane::setStatus(string s)
{
	this->status = s;
}
