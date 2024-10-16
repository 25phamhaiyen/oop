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
		displayMenuManager();
		char choice;
		while( choice != 't' && choice != 'T' ){
			do {
				cout << "\nNhap lua chon cua ban:  ";
				cin >> choice;
				if( choice < '1' || choice > '8' )
					cout << "\nBan chi duoc nhap gia tri trong khoang tu 1 -> 9 hoac {t,T}. Vui long nhap lai.\n";
			}while( choice < '1' || choice > '8' );
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
				case 't':
					cout << endl << "KET THUC\n";
					break;
				case 'T':
					cout << endl << "KET THUC\n";
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
		char choice;
		vector<pair<Flight, string>> passfly;
		vector<pair<Passenger, string>> demoPass;
		vector<pair<Passenger, string>> hisPass;
		while( choice != '7' ){
			system("cls");
			displayMenuUser();
			do {
				cout << "Nhap lua chon cua ban:  ";
				cin >> choice;
				if( choice < '1' || choice > '7' )
					cout << "\nBan chi duoc nhap trong khoang tu 1 -> 7. Vui long nhap lai\n\n";
			}while( choice < '1' || choice > '7' );
			system("cls");
			switch( choice ){
				case '1':
					{
						Passenger pas;
						cin >> pas;
						char yourChoice;
						while( yourChoice != '8'){
							cout << "\n---------------------MENU---------------------\n\n";
							cout << "1. Hien thi danh sach chuyen bay.\n";
							cout << "2. Tim kiem theo ngay bay.\n";
							cout << "3. Tim kiem theo gia ve.\n";
							cout << "4. Tim kiem theo hang bay.\n";
							cout << "5. Tim kiem theo noi den.\n";
							cout << "6. Tim kiem theo thoi gian.\n";
							cout << "7. Sap xep tang dan gia ve.\n";
							cout << "8. Thoat.\n";
							cout << "\n----------------------------------------------\n\n";
							cin.ignore();
							do {
								cout << "Nhap lua chon cua ban:  ";
								cin >> yourChoice;
								if( yourChoice < '1' || yourChoice > '8' )
									cout << "\nBan chi duoc nhap trong khoang tu 1 -> 8. Vui long nhap lai\n\n";
							}while( yourChoice < '1' || yourChoice > '8' );
							system("cls");
							switch( yourChoice ){
								case '1':
									cout << endl;
									displayFlight(flight);
									break;
								case '2':
									{
										cout << endl;
										Date date;
										cout << "Nhap ngay bay ban muon tim:\n";
										cin >> date;
										findWithFlightDate(flight, date);
										break;
									}
								case '3':
									{
										cout << endl;
										double minTic, maxTic;
										cout << "Nhap khoang gia ve muon tim: \n\n";
										cout << "Tu:  "; cin >> minTic;
										cout << "Den:  "; cin >> maxTic;
										findWithTicketPrice(flight, minTic, maxTic, pas.getRank());
										break;
									}
								case '4':
									{
										cout << endl;
										char c;
										string planeName;
										cout << "Chon 1 trong cac hang bay:\n\n";
										cout << "1. VietNam Airlines\n";
										cout << "2. VietJet Air\n";
										cout << "3. Bamboo Airways\n";
										cout << "4. Jetstar Pacific\n\n";
										do {
											cout << "Nhap lua chon cua ban:  "; cin >> c;
											if( c < '1' || c > '4' )
												cout << "\nBan chi duoc nhap gia tri trong khaong 1 -> 4. Vui long nhap lai\n";
										}while( c < '1' || c > '4' );
										switch( c ){
											case '1':
												planeName = "VietNam Airlines";
												break;
											case '2':
												planeName = "VietJet Air     ";
												break;
											case '3':
												planeName = "Bamboo Airways  ";
												break;
											case '4':
												planeName = "Jetstar Pacific ";
												break;	
										}
										findWithPlaneName(flight, planeName);
										break;
									}
								case '5':
									{
										cout << endl;
										cin.ignore();
										string destination;
										cout << "Nhap noi den muon tim:  "; getline(cin, destination);
										string space = "";
										for( int i = 0 ; i < 9-destination.size() ; i++ ){
											space += " ";
										}
										destination += space;
										findWithDestination(flight, destination);
										break;
									}
								case '6':
									{
										cout << endl;
										Time sTime, eTime;
										cout << "Nhap khoang thoi gian muon tim: \n\n";
										cout << "Tu:  \n"; cin >> sTime;
										do {
											cout << "\nDen:  \n"; cin >> eTime;
											if( eTime <= sTime )
												cout << "\nThoi gian sau phai lon hon thoi gian truoc. Vui long nhap lai\n";
										}while( eTime <= sTime );
										findWithTime(flight, sTime, eTime);
										break;
									}
								case '7':
									{
										cout << endl;
										sortIncreaseTicketPrice(flight);
										displayFlight(flight);
										break;
									}
								case '8':
									cout << endl << "KET THUC\n";
									break;
							}	
							char ch;
							cout << "\n Ban da tim duoc chuyen bay mong muon chua?\n";
							cout << "1. Da tim duoc.\n";
							cout << "2. Chua tim duoc.\n";
							do {
								cout << "\nNhap lua chon cua ban:  ";
								cin >> ch;
								if( ch != '1' && ch != '2' )
									cout << "\nBan chi duoc chon 1 hoac 2. Vui logn chon lai\n";
							}while( ch != '1' && ch != '2' );
							cout << "------------------\n";
							if( ch == '1' ){
								string id, plane;
								cout << "\nNhap id chuyen bay muon dat:  ";
								cin >> id;
								Flight f;
								for( auto it : flight ){
									if( it.first.getId() == id ){
										f = it.first;
										plane = it.second;
										break;
									}
								}
								if( pas.getRank() == "Thuong gia" ){
									if( f.countVip() )
										f.listVip();
								}
								else if( pas.getRank() == "Pho thong " ){
									if( f.countPopular() )
										f.listPopular();
								}
								cout << endl;
								int pos;
								do {
									cout << "\nNhap vi tri ghe ban muon ngoi:  ";
									cin >> pos;
									if( pas.getRank() == "Thuong gia" && ( pos < 1 || pos > 15 ) ){
										cout << "\nBan chi duoc chon cac vi tri ghe da liet ke o tren. Vui long chon lai.\n";
									}
									if( pas.getRank() == "Pho thong " && ( pos < 16 || pos > 50 ) ){
										cout << "\nBan chi duoc chon cac vi tri ghe da liet ke o tren. Vui long chon lai.\n";
									}
								}while( ( pas.getRank() == "Thuong gia" && ( pos < 1 || pos > 15 ) ) || ( pas.getRank() == "Pho thong " && ( pos < 16 || pos > 50 ) ) );
								pas.setPosition(pos);
								demoPass.push_back(make_pair(pas,id));
								hisPass.push_back(make_pair(pas,id));
								bool check = true;
								for( auto it : passfly ){
									if( it.first.getId() == id ){
										check = false;
										break;
									}			
								}
								if( check )
									passfly.push_back(make_pair(f,plane));
								yourChoice = '8';	
							}
							
						}	
					}
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
					cout << endl << "KET THUC\n";
					break;
			}
		}
		
	}
	return 0;
}
