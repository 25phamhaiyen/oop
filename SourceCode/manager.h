#pragma once
#include "human.h"

class Manager {
	public:
		friend void displayHistory( vector<pair<Passenger, string>> history );
		friend void displayFlight( vector<pair<Flight, string>> flight );
		friend void displayFlightUser( vector<pair<Flight,string>> flight, string area );
		friend void displayPlane( vector<Plane> plane );
		friend void displayPassenger( vector<pair<Passenger,string>> plane );
		friend void displayHumanInPlane( vector<vector<pair<humanInPlane,string>>> personal );
		friend void displayHumanInPlaneWithPosition( unordered_map<string, set<pair<humanInPlane, string>>> employ, string pos );
		friend void displayVoucher( vector<Voucher> voucher );
		friend void inputFlight( Flight &fly );
		friend void addFlight( vector<Plane> &plane, vector<pair<Flight,string>> &flight, vector<vector<pair<humanInPlane,string>>> &personal );
		friend void addVoucher( vector<Voucher> &voucher );
		friend void displayBill( int ticketNum, vector<pair<Flight, string>> passfly, vector<pair<Passenger, string>> passenger, int voucherLevel );
		friend void displayMenuManager();
		friend void displayMenuUser();
		friend void displayMenuDatve();
		friend void displayChinhsuaChuyenbay();
		friend void displayChinhsuaMaybay();
		friend void displayChinhsuaVoucher();
};

// build class Manager
void displayFlight( vector<pair<Flight,string>> flight ){
	if( flight.empty() ){
		cout << "Khong co chuyen bay nao de hien thi.\n";
		return;
	}
	cout << PINK << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|    ID     |    Ngay bay    |   Lich trinh bay              | TG cat canh | TG ha canh  | Gia ve thuong | Gia ve vip | Luot dat |   Ten hang bay      |" << endl;
    cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << RESET << "\n";
	for( auto &it : flight ){
		if( it.first.getPopTicketPrice() != 0 )
			cout << "|   " << it.first << "    " << it.first.getSitNum() << "     |   " << it.second << "  |" << endl;
	}
	cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------+\n\n";
}
void displayFlightUser( vector<pair<Flight,string>> flight, string area ){
	if( flight.empty() ){
		cout << "Khong co chuyen bay nao de hien thi.\n";
		return;
	}
	cout << PINK << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|    ID     |    Ngay bay    |   Lich trinh bay              | TG cat canh | TG ha canh  | Gia ve thuong | Gia ve vip | Luot dat |   Ten hang bay      |" << endl;
    cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------+" << RESET << "\n";
	for( auto &it : flight ){
		if( it.first.getPopTicketPrice() != 0 && it.first.getArea() == area )
			cout << "|   " << it.first << "    " << it.first.getSitNum() << "     |   " << it.second << "  |" << endl;
	}
	cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------+\n\n";
}
void displayPassenger( vector<pair<Passenger,string>> passInfo ){
	if( passInfo.empty() ){
		cout << "Khong co hanh khach nao de hien thi.\n";
		return;
	}
	cout << PINK << "+----------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|   Ho va ten     |   Ngay sinh    | Gioi tinh |  Tuoi  | So dien thoai  | So ho chieu  |   So CCCD        |" << endl;
    cout << "+----------------------------------------------------------------------------------------------------------+" << RESET << "\n";
	for( auto it : passInfo ){
		cout << "|   " << it.first.getName() << "  |   " << it.first.getDate() << "   |    " << it.first.getSex() << "    |   " << it.first.getAge() << "   |   "
		<< it.first.getPhoneNum() << "   |   " <<  it.first.getPassportNum() << "   |   " << it.first.getCidNum() << "   |   " << endl;
	}
	cout << "+----------------------------------------------------------------------------------------------------------+\n\n";
}
void displayHistory( vector<pair<Passenger,string>> history ){
	if( history.empty() ){
		cout << "Khong co lich su dat ve nao de hien thi.\n";
		return;
	}
	cout << PINK << "+------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|   Ho va ten     |   Ngay sinh    | Gioi tinh |  Tuoi  |    Hang ghe    | Vi tri ghe | Trang thai | Ma chuyen bay |" << endl;
    cout << "+------------------------------------------------------------------------------------------------------------------+" << RESET << "\n";
	for( auto it : history ){
		cout << "|   " << it.first.getName() << "  |   " << it.first.getDate() << "   |    " << it.first.getSex() << "    |   " << it.first.getAge() << "   |   " << it.first.getRank() << "   |     ";
		if( it.first.getPos() < 10 )
			cout << it.first.getPos() << "      |     ";
		else
			cout << it.first.getPos() << "     |     ";
		cout << it.first.getStatus() << "    |     " << it.second << "     |" << endl;
	}
	cout << "+------------------------------------------------------------------------------------------------------------------+\n\n";
}
void displayPlane( vector<pair<Plane, string>> plane ){
	if( plane.empty() ){
		cout << "Khong co may bay nao de hien thi.\n";
		return;
	}
	cout << PINK << "+------------------------------------------------------------------------+" << endl;
    cout << "|   Ten hang bay      | So hieu may bay |  Loai may bay  |   Tinh trang  |" << endl;
    cout << "+------------------------------------------------------------------------+" << RESET << "\n";
	for( auto &it : plane ){
		cout << "|   " << it.first.getPlaneName() << "  |      " << it.first.getAircraftNumber() << "      |    " << it.first.getType() << "    |   " << it.first.getStatus() << "   |" << endl;
	}
	cout << "+------------------------------------------------------------------------+\n\n";
}
void displayHumanInPlane( vector<vector<pair<humanInPlane, string>>> personal ){
	if( personal.empty() ){
		cout << "Khong co Nhan su nao de hien thi.\n";
		return;
	}
	cout << PINK << "+--------------------------------------------------------------------------------------------------------------------+\n";
    cout << "|   ID    |   Ho va ten     " << "|   Ngay sinh    " << "| Gioi tinh " << "|  Tuoi  " << "|    Vi tri\t  " << "| Luong(.000 VND) " << "| SHMB phu trach |\n";
    cout << "+--------------------------------------------------------------------------------------------------------------------+" << RESET << "\n";
	for( auto &it : personal ){
		for( auto &i : it ){
			cout << "|  " << i.first.getId() << "  " << "|   " << i.first.getName() << "  |   " << i.first.getDate() << "   |    " << i.first.getSex() << "    |   " << i.first.getAge() << "   |   " << i.first.getPosition() << "   |      ";
			if( i.first.getSalary() == 100000 )
				cout << i.first.getSalary() << "     |     " << i.second << "      |\n";
			else
				cout << i.first.getSalary() << "      |     " << i.second << "      |\n";
		}
		cout << "+--------------------------------------------------------------------------------------------------------------------+\n";
	}
	cout << endl;
}
void displayHumanInPlaneWithPosition( unordered_map<string, set<pair<humanInPlane, string>>> employ, string pos ){
    if( employ.empty() ){
		cout << "Khong co Nhan su nao de hien thi.\n";
		return;
	}
	cout << PINK << "+--------------------------------------------------------------------------------------------------------------------+\n";
    cout << "|   ID    |   Ho va ten     " << "|   Ngay sinh    " << "| Gioi tinh " << "|  Tuoi  " << "|    Vi tri\t  " << "| Luong(.000 VND) " << "| SHMB phu trach |\n";
    cout << "+--------------------------------------------------------------------------------------------------------------------+" << RESET << "\n";
    for( const auto i : employ[pos] ){
        cout << "|  " << i.first.getId() << "  " << "|   " << i.first.getName() << "  |   " << i.first.getDate() << "   |    " << i.first.getSex() << "    |   " << i.first.getAge() << "   |   " << i.first.getPosition() << "   |      ";
        if( i.first.getSalary() == 100000 )
            cout << i.first.getSalary() << "     |     " << i.second << "      |\n";
        else
            cout << i.first.getSalary() << "      |     " << i.second << "      |\n";
    }
    cout << "+--------------------------------------------------------------------------------------------------------------------+\n\n";
}
void displayVoucher( vector<Voucher> voucher ){
	if( voucher.empty() ){
		cout << "Khong co Voucher nao de hien thi.\n";
		return;
	}
	cout << PINK << "+-----------------------------------------------------+\n" << RESET;
	cout << PINK << "|   ID   " << "| Muc giam(%) " << "| Ngay bat dau " << "| Ngay ket thuc |\n" << RESET;
	cout << PINK << "+-----------------------------------------------------+\n" << RESET;
	for( auto &it : voucher ){
		cout << it;
	}
	cout << "+-----------------------------------------------------+\n\n";
}
void inputFlight( Flight &fly, unordered_map<string,int> &checkid, vector<pair<Flight, string>> flight ){
	time_t t = time(nullptr); // L?y th?i gian hi?n t?i
    tm* now = localtime(&t);
    string id, destination, area;
    Time dpTime, ldTime;
    double pop, vip;
    Date date;
    Date nowDate(now->tm_mday, now->tm_mon+1, now->tm_year+1900);
    int size = flight.size()+1;
    id = "VN0" + to_string(size);
    while( checkid[id] ){
        size++;
        id = "VN0" + to_string(size);
    }
	checkid[id]++;
	cin.ignore();
	cout << "\nNhap noi den ( Tinh hoac TP ):  ";
	getline(cin, destination);
	for( int i = 0 ; i < 9-destination.size() ; i++ ){
		destination += ' ';
	}
	date.inputDate();
	cout << "\nNhap thoi gian khoi hanh ( hour:minute ):  \n";
	cin >> dpTime;
	do {
		cout << "\nNhap thoi gian ha canh ( hour:minute ):  \n";
		cin >> ldTime;
		if( ldTime - dpTime <= 20 )
			cout << "\nThoi gian ha canh phai lon hon thoi gian khoi hanh 20 phut tro len. Vui long nhap lai\n";
	}while( ldTime - dpTime <= 20 );
	do {
		cout << "\nNhap gia ve hang thuong (.000 VND):  ";
		cin >> pop;
		if( pop <= 900  )
			cout << "\nGia ve pho thong phai lon hon 900 nghin VND. Vui long nhap lai\n";
	}while( pop <= 900 );
	do {
		cout << "\nNhap gia ve hang thuong gia (.000 VND):  ";
		cin >> vip;
		if( vip-pop < 500 ){
			cout << "\nGia ve vip phai lon hon gia ve pho thong it nhat 500 nghin VND. Vui long nhap lai\n";
			continue;
		}
	}while( vip-pop < 500 );
	char c;
	cout << "\nChon pham vi chuyen bay: \n1. Trong nuoc \n2. Nuoc ngoai\n";
	do {
		cout << "\nNhap lua chon cua ban:  ";
		cin >> c;
		if( c != '1' && c != '2' )
			cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai.\n";
	}while( c != '1' && c != '2' );
	area = ( c == '1' )?"in ":"out";
	fly = Flight(id,date,"Sai gon",destination, dpTime, ldTime, pop, vip, area);
}
void addFlight( vector<pair<Plane, string>> &plane, vector<pair<Flight,string>> &flight, vector<vector<pair<humanInPlane,string>>> &personal, unordered_map<string, int> &checkid, unordered_map<string, set<pair<humanInPlane, string>>> employ ){
	Plane p;
	Flight fly;
	vector<pair<humanInPlane,string>> human;
	humanInPlane hip;
	cout << "Nhap thong tin may bay:\n\n";
	cin >> p;
	string first;
	if( p.getPlaneName() == "VietNam Airlines" )
        first = "VA0";
    else if( p.getPlaneName() == "VietJet Air     " )
        first = "VJ0";
    else if( p.getPlaneName() == "Bamboo Airways  " )
        first = "BA0";
    else
        first = "JP0";
    int size = plane.size()+1;
	string aircraft = first + to_string(size);
	while( checkid[aircraft] ){
        size++;
        aircraft = first + to_string(size);
	}
	checkid[aircraft]++;
	p.setAircraftNumber(aircraft);
	system("cls");
	cout << "Nhap thong tin chuyen bay:\n";
	inputFlight(fly, checkid, flight);
	system("cls");
	string pos;
	for( int i = 0 ; i < 4 ; i++ ){
        if( i == 0 )
            pos = "Co truong";
        else if( i == 1 )
            pos = "Co pho   ";
        else
            pos = "Tiep vien";
        displayHumanInPlaneWithPosition(employ, pos);
        cout << "Chon 1 " << pos << ".\n";
        bool isValidId = false;
		string id;
		humanInPlane hip;
		do {
            cout << "\nNhap id nhan su muon them:  ";
            cin >> id;
            for( auto it : employ[pos] ){
                if( it.first.getId() == id ){
                    isValidId = true;
                    hip = it.first;
                    break;
                }
            }
            cout << "\nId khong dung hoac nhan su da duoc chon cho vi tri khac. Vui long nhap lai.\n";
		}while( !isValidId );
		cout << endl;
		human.push_back(make_pair(hip,p.getAircraftNumber()));
		system("cls");
	}
	personal.push_back(human);
	flight.push_back(make_pair(fly,p.getPlaneName()));
	plane.push_back(make_pair(p,fly.getId()));
}
void addVoucher( vector<Voucher> &voucher, unordered_map<string,int> &checkid ){
	Voucher vou;
	cin >> vou;
	string newId = vou.getID();
	while( checkid[newId] ){
		cout << "\nMa khuyen mai da ton tai. Vui long nhap ma khac\n";
		cin >> newId;
	}
	checkid[newId]++;
	vou.setID(newId);
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
	time_t t = time(nullptr); // L?y th?i gian hi?n t?i
    tm* now = localtime(&t);
	cout << "+--------------------------------------BILL THANH TOAN----------------------------------------+\n";
	cout << "| So luong ve da dat:  " << ticketNum << setw(72) << "|\n";
	cout << "+---------------------------------------------------------------------------------------------+\n";
	cout << "| Thong tin dat cho:                                                                          |\n";
	cout << "|                                                                                             |\n";
	cout << "| Trang thai dat cho:  Da xac nhan  \t\t\t\tNguoi dat:  " << passenger[0].first.getName() << setw(8) << "|\n";
	cout << "| Ngay dat:  " << now->tm_mday << "/" << (now->tm_mon + 1) << "/" << (now->tm_year + 1900) << "\t\t\t\t\t\tLien lac:  " << passenger[0].first.getPhoneNum() << setw(11) << "|\n";
	cout << "|                                                                                             |\n";
	cout << "+---------------------------------------------------------------------------------------------+\n";
	cout << "| Thong tin hanh khach:                                                                       |\n";
	cout << "| " << PINK << "+-----------------------------------------------------------------------------+" << RESET << setw(15) << "|\n";
	cout << "| " << PINK << "|    Ho va ten     " << "|    Hang ghe    " << "| Vi tri ghe " <<  "| Ma chuyen bay |   Gia ve   |" << RESET <<  setw(15) << "|\n";
	cout << "| " << PINK << "+-----------------------------------------------------------------------------+" << RESET << setw(15) << "|\n";
	for( auto it : passenger ){
		cout << "| |   " << it.first.getName() << "   |   " << it.first.getRank() << "   |     ";
		if( it.first.getPos() < 10 )
			cout << it.first.getPos() << "      |     ";
		else
			cout << it.first.getPos() << "     |     ";
		cout << it.second << "     |    ";
		for( auto i : passfly ){
            if( i.first.getId() == it.second ){
                if( it.first.getRank() == "Thuong gia" ){
                    if( i.first.getVipTicketPrice() >= 10000 )
                        cout << i.first.getVipTicketPrice() << "   |";
                    else
                        cout << i.first.getVipTicketPrice() << "    |";
                }
                else
                    cout << i.first.getPopTicketPrice() << "    |";
            }
		}
		cout << setw(15) << "|\n";
	}
	cout << "| +-----------------------------------------------------------------------------+             |\n";
	cout << "|                                                                                             |\n";
	cout << "+---------------------------------------------------------------------------------------------+\n";
	cout << "| Thong tin chuyen bay:                                                                       |\n";
	cout << "| " << PINK << "+----------------------------------------------------------------------------------------+" << RESET << "  |\n";
	cout << "| " << PINK << "|    ID" << "     |    Ngay bay    " << "|   Lich trinh bay\t       " << "| TG cat canh " << "| TG ha canh  |" << RESET << "  |\n";
	cout << "| " << PINK << "+----------------------------------------------------------------------------------------+" << RESET << "  |\n";
	for( auto &it : passfly ){
		if( idmap[it.first.getId()] != 0 )
			cout << "| |   " << it.first.getId() << "   |   " << it.first.getFlightDate() << "   |   from " << it.first.getDepartureLocation() << " to " << it.first.getDestination() << "   |    "
				<< it.first.getDepartureTime() << "    |    " << it.first.getLandingTime() << "    |  |\n";
	}
	cout << "| +----------------------------------------------------------------------------------------+  |\n";
	cout << "|                                                                                             |\n";
	cout << "+---------------------------------------------------------------------------------------------+\n";
	cout << "| Tong tien ve:  " << total << " (Nghin VND)" << endl;
	cout << "| Khuyen mai:  " << total*voucherLevel/100 << " (Nghin VND)" << endl;
	cout << "| So tien phai thanh toan:  " << real << " (Nghin VND)" << endl;
	cout << "+------------------------------------------------+\n";
}
void displayMenuManager(){
	cout << "+--------------------MENU-----------------------+\n";
	cout << "|                                               |\n";
	cout << "| 1. Hien thi danh sach may bay.                |\n";
	cout << "| 2. Hien thi danh sach chuyen bay.             |\n";
	cout << "| 3. Hien thi danh sach thong tin nguoi dung.   |\n";
	cout << "| 4. Hien thi danh sach luot dat ve.            |\n";
	cout << "| 5. Hien thi danh sach nhan su.                |\n";
	cout << "| 6. Hien thi danh sach Voucher.                |\n";
	cout << "| 7. Them thong tin chuyen bay.                 |\n";
	cout << "| 8. Them Voucher.                              |\n";
	cout << "| 9. Them nhan su.                              |\n";
	cout << "| 10. Xoa chuyen bay.                           |\n";
	cout << "| 11. Xoa may bay.                              |\n";
	cout << "| 12. Xoa nhan su.                              |\n";
	cout << "| 13. Xoa voucher.                              |\n";
	cout << "| 14. Chinh sua thong tin chuyen bay.           |\n";
	cout << "| 15. Chinh sua thong tin may bay               |\n";
	cout << "| 16. Chinh sua thong tin Voucher               |\n";
	cout << "| T. Thoat.                                     |\n";
	cout << "|                                               |\n";
	cout << "+-----------------------------------------------+\n";
}
void displayMenuUser(){
	cout << "+----------------------MENU--------------------------+\n";
	cout << "|                                                    |\n";
	cout << "| 1. Dat ve.                                         |\n";
	cout << "| 2. Hien thi danh sach chuyen bay.                  |\n";
    cout << "| 3. Huy chuyen bay.                                 |\n";
    cout << "| 4. Xem lich su dat ve.                             |\n";
    cout << "| 5. Xuat Bill dat ve.                               |\n";
    cout << "| 6. Thoat.                                          |\n";
    cout << "|                                                    |\n";
    cout << "+----------------------------------------------------+\n";
}
void displayMenuDatve(){
	cout << "\n+--------------------MENU--------------------+\n";
    cout << "|                                            |\n";
    cout << "| 1. Hien thi danh sach chuyen bay.          |\n";
    cout << "| 2. Tim kiem theo ngay bay.                 |\n";
    cout << "| 3. Tim kiem theo gia ve.                   |\n";
    cout << "| 4. Tim kiem theo hang bay.                 |\n";
    cout << "| 5. Tim kiem theo noi den.                  |\n";
    cout << "| 6. Tim kiem theo thoi gian.                |\n";
    cout << "| 7. Sap xep tang dan gia ve.                |\n";
    cout << "| 8. Thoat.                                  |\n";
    cout << "|                                            |\n";
    cout << "+--------------------------------------------+\n\n";
}
void displayChinhsuaChuyenbay(){
    cout << "+--------------BAN MUON SUA THUOC TINH NAO-----------+\n";
	cout << "|                                                    |\n";
	cout << "| 1. ID                                              |\n";
	cout << "| 2. Diem den                                        |\n";
    cout << "| 3. Ngay bay                                        |\n";
    cout << "| 4. Gio bay                                         |\n";
    cout << "| 5. Gia ve                                          |\n";
    cout << "| 6. Thoat                                           |\n";
    cout << "|                                                    |\n";
    cout << "+----------------------------------------------------+\n";
}
void displayChinhsuaMaybay(){
    cout << "+--------------BAN MUON SUA THUOC TINH NAO-----------+\n";
	cout << "|                                                    |\n";
	cout << "| 1. Ten hang bay                                    |\n";
	cout << "| 2. So hieu may bay                                 |\n";
    cout << "| 3. Loai may bay                                    |\n";
    cout << "| 4. Tinh trang                                      |\n";
    cout << "| 5. Thoat                                           |\n";
    cout << "|                                                    |\n";
    cout << "+----------------------------------------------------+\n";
}
void displayChinhsuaVoucher(){
    cout << "+--------------BAN MUON SUA THUOC TINH NAO-----------+\n";
	cout << "|                                                    |\n";
	cout << "| 1. Ma khuyen mai                                   |\n";
	cout << "| 2. Muc giam                                        |\n";
    cout << "| 3. Ngay bat dau khuyen mai                         |\n";
    cout << "| 4. Ngay ket thuc khuyen mai                        |\n";
    cout << "| 5. Thoat                                           |\n";
    cout << "|                                                    |\n";
    cout << "+----------------------------------------------------+\n";
}