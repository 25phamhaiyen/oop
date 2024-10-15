#include "AirportManager.h"
#include "SignIn.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	vector<Plane> plane;
	vector<pair<Flight,string>> flight;
	vector<vector<pair<humanInPlane, string>>> personal;
	vector<pair<Passenger,string>> passInfo;
	vector<Voucher> voucher;
	vector<pair<Passenger,string>> history;
	readData(plane, flight, passInfo, voucher, personal, history);
	updateSitPos(flight, passInfo);
	SignIn si;
	cout << "Ban dang nhap voi tu cach nao?" << endl;
	cout << "1.Quan ly \n2.Khach hang" << endl << endl;
	char choice;
	do {
		cout << "Enter your choice:  ";
		cin >> choice;
		if( choice != '1' && choice != '2' )
			cout << "\nMust enter 1 or 2. Please re-enter\n\n";
	}while( choice != '1' && choice != '2' );
	cin.ignore();
	if( choice == '1' ){
		cout << "\n-----------------Sign In---------------------\n";
		si.sign_in(1);
		cout << "\n---------------------------------------------\n";
		system("cls");
		cout << "---------------------MENU-----------------------\n\n";
		cout << "1.Hien thi danh sach may bay.\n";
		cout << "2.Hien thi danh sach chuyen bay.\n";
		cout << "3.Hien thi danh sach thong tin nguoi dung.\n";
		cout << "4.Hien thi danh sach luot dat ve.\n";
		cout << "5.Hien thi danh sach nhan su.\n";
		cout << "6.Hien thi danh sach Voucher.\n"
		cout << "7.Them thong tin chuyen bay.\n";
		cout << "8.Them Voucher.\n";
		cout << "9.Hien thi tong doanh thu dat ve.\n";
		cout << "T.Thoat.\n";
		char choice;
		while( choice != 't' && choice != 'T' ){
			do {
				cout << "\nNhap lua chon cua ban:  ";
				cin >> choice;
				if( choice < '1' || choice > '9' )
					cout << "\nBan chi duoc nhap gia tri trong khoang tu 1 -> 9 hoac {t,T}. Vui long nhap lai.\n";
			}while( choice < '1' || choice > '9' );
			switch(choice){
				case '1':
					cout << endl;
					displayPlane(plane);
					break;
				case '2':
					cout << endl;
					displayFlight(flight);
					break;
				case '3':
					cout << endl;
					displayPassenger(passInfo);
					break;
				case '4':
					cout << endl;
					displayHistory(history);
					break;
				case '5':
					cout << endl;
					displayHumanInPlane(personal);
					break;
				case '6':
					cout << endl;
					displayVoucher(voucher);
					break;
				case '7':
					cout << endl;
					addFlight(plane, flight, personal);
					break;
				case '8':
					cout << endl;
					addVoucher(voucher);
					break;
				case '9':
					cout << endl;
					displayRevenue(history);
					break;
				case 't','T':
					cout << endl << "KET THUC" << endl;
					break;
			}
		}	
	}
	else {
		int signChoice;
		cout << "\nBan da co tai khoan chua?" << endl;
		cout << "1.Da co tai khoan \n2.Chua co tai khoan" << endl << endl;
		do {
			cout << "Enter your choice:  ";
			cin >> signChoice;
			if( signChoice != 1 && signChoice != 2 )
				cout << "\nMust enter 1 or 2. Please re-enter\n\n";
		}while( signChoice != 1 && signChoice != 2 );
		cin.ignore();
		if( signChoice == 1 ){
			cout << "\n-----------------Sign In---------------------\n";
			si.sign_in(2);
			cout << "\n---------------------------------------------\n";
		}
		else {
			cout << "\n-----------------Sign Up---------------------\n";
			si.sign_up();
			cout << "\n---------------------------------------------\n";
			
			cout << "\n-----------------Sign In---------------------\n";
			si.sign_in(2);
			cout << "\n---------------------------------------------\n";
		}
	}
	return 0;
}
