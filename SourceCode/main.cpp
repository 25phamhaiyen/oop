#include "signIn.h"
#include "date_time.h"
#include "airport.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	// set up du lieu

	vector<pair<Plane, string>> plane;
	vector<pair<Flight,string>> flight;
	vector<vector<pair<humanInPlane, string>>> personal;
	vector<pair<Passenger,string>> passInfo;
	vector<Voucher> voucher;
	vector<pair<Passenger,string>> history;
	unordered_map<string, int> checkid;
	readData(plane, flight, passInfo, voucher, personal, history);
	updateSitPos(flight, passInfo);
	for( auto it : plane ){
		checkid[it.second]++;
		checkid[it.first.getAircraftNumber()]++;
	}
	for( auto it : voucher ){
		checkid[it.getID()] = it.getReduceLevel();
	}
	
	// chay ct
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
	
	// dang nhap giao dien quan ly
	
	if( choice == '1' ){ 
		cout << "\n-----------------Sign In---------------------\n";
		si.sign_in('1');
		cout << "\n---------------------------------------------\n";
		system("cls");
		char choice;
		while( choice != 't' && choice != 'T' ){
			displayMenuManager();
			do {
				cout << "\nNhap lua chon cua ban:  ";
				cin >> choice;
				if ((choice < '1' || choice > '8') && choice != 't' && choice != 'T') {
					cout << "\nBan chi duoc nhap gia tri trong khoang tu 1 -> 8 hoac {t, T} de thoat. Vui long nhap lai.\n";
				}
			}while ((choice < '1' || choice > '8') && choice != 't' && choice != 'T');
			system("cls");
			switch(choice){
				case '1':
					cout << endl;
					displayPlane(plane);
					cout << endl;
					break;
				case '2':
					cout << endl;
					displayFlight(flight);
					cout << endl;
					break;
				case '3':
					cout << endl;
					displayPassenger(passInfo);
					cout << endl;
					break;
				case '4':
					cout << endl;
					displayHistory(history);
					cout << endl;
					break;
				case '5':
					cout << endl;
					displayHumanInPlane(personal);
					cout << endl;
					break;
				case '6':
					cout << endl;
					displayVoucher(voucher);
					cout << endl;
					break;
				case '7':
					cout << endl;
					addFlight(plane, flight, personal, checkid);
					cout << endl;
					break;
				case '8':
					cout << endl;
					addVoucher(voucher);
					cout << endl;
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
	
	// dang nhap/ dang ky giao dien nguoi dung
	
	else {
		char signChoice;
		cout << "\nBan da co tai khoan chua?" << endl;
		cout << "1.Da co tai khoan \n2.Chua co tai khoan" << endl << endl;
		do {
			cout << "Enter your choice:  ";
			cin >> signChoice;
			if( signChoice != '1' && signChoice != '2' )
				cout << "\nMust enter 1 or 2. Please re-enter\n\n";
		}while( signChoice != '1' && signChoice != '2' );
		system("cls");
		cin.ignore();
		if( signChoice == '1' ){
			cout << "\n-----------------Sign In---------------------\n";
			si.sign_in('2');
			cout << "\n---------------------------------------------\n";
		}
		else {
			cout << "\n-----------------Sign Up---------------------\n";
			si.sign_up();
			cout << "\n---------------------------------------------\n";
			system("cls");
			cout << "\n-----------------Sign In---------------------\n";
			si.sign_in('2');
			cout << "\n---------------------------------------------\n";
		}
		system("cls");
		char choice;
		vector<pair<Flight, string>> passfly; // vector luu chuyen bay nguoi dung đã đặt
		vector<pair<Passenger, string>> demoPass; // vector lưu thông tin người dùng
		vector<pair<Passenger, string>> hisPass; // vector lưu lịch sử đặt vé, hủy vé
		unordered_map<int, int> mp;  // map dùng để lưu vị trí người dùng đặt
		unordered_map<string,int> idmap; // map dùng để lưu mã chuyến bay
		while( choice != '8' ){
			int ticketNum;
			displayMenuUser();
			do {
				cout << "Nhap lua chon cua ban:  ";
				cin >> choice;
				if( choice < '1' || choice > '8' )
					cout << "\nBan chi duoc nhap trong khoang tu 1 -> 8. Vui long nhap lai\n\n";
			}while( choice < '1' || choice > '8' );
			system("cls");
			switch( choice ){
				case '1':
					{
						do {
							cout << "Nhap so luong ve muon dat:  ";
							cin >> ticketNum;
							if( ticketNum <= 0 )
								cout << "\nSo luong ve phai > 0. Vui long nhap lai.\n\n";
						}while( ticketNum <= 0 );
						
						int k = ticketNum;
						Passenger pas;
						char yourChoice;
						string idVoucher;
						
						while( k-- ){
							char n;
							cout << "Ban muon bay trong nuoc hay nuoc ngoai?\n";
							cout << "1. Trong nuoc.\n";
							cout << "2. Nuoc ngoai.\n";
							do {
								cout << "\nNhap lua chon cua ban:  ";
								cin >> n;
								if( n != '1' && n != '2' )
									cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai.\n";
							}while( n != '1' && n != '2' );
							if( n == '1' )
								pas.setInCountry(true); // dùng để kiểm tra trong nước hay ngoài nước để nhập passport
							else
								pas.setInCountry(false);
							system("cls");
							cin >> pas;
							yourChoice = '0';
							while( yourChoice != '8'){  // hiển thị menu đặt vé khi nhập thông tin xong thì sẽ hiện ra để người dùng dễ dàng chọn chuyến bay
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
										cout << endl;
										break;
									case '2':
										{
											cout << endl;
											Date date;
											cout << "Nhap ngay bay ban muon tim:\n";
											cin >> date;
											findWithFlightDate(flight, date);
											cout << endl;
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
											cout << endl;
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
											cout << endl;
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
											cout << endl;
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
											cout << endl;
											break;
										}
									case '7':
										{
											cout << endl;
											sortIncreaseTicketPrice(flight);
											displayFlight(flight);
											cout << endl;
											break;
										}
									case '8':
										cout << endl << "KET THUC\n";
										break;
								}	
								// hỏi người dùng đã tìm được chuyến bay mong muốn chưa
								char ch;
								cout << "\n Ban da tim duoc chuyen bay mong muon chua?\n";
								cout << "1. Da tim duoc.\n";
								cout << "2. Chua tim duoc.\n";
								do {
									cout << "\nNhap lua chon cua ban:  ";
									cin >> ch;
									if( ch != '1' && ch != '2' )
										cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai\n";
								}while( ch != '1' && ch != '2' );
								cout << "-------------------------------\n";
								// nếu đã tìm được thì sẽ cho người dùng nhập mã chuyến bay và chỗ ngồi
								if( ch == '1' ){ 
									string id, plane;
									cin.ignore();
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
									// list các chỗ ngồi còn trống
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
									// cập nhật vị trí ghế và mã chuyến bay;
									mp[pos]++;
									idmap[id]++;
									pas.setPosition(pos);
									// thêm vào các vector
									demoPass.push_back(make_pair(pas,id));
									hisPass.push_back(make_pair(pas,id));
									bool check = true;
									// đoạn này để kiểm tra xem trong vector đã tồn tại chuyến bay chưa nếu chưa thì dẩy vào
									for( auto &it : passfly ){
										if( it.first.getId() == id ){
											check = false;
											break;
										}			
									}
									if( check ){
										passfly.push_back(make_pair(f,plane));
									}
									// cập nhật vị trí ngồi mới của chuyến bay
									for( auto &it : flight ){
										if( it.first.getId() == id ){
											it.first.setSitPos(pos);
										}
									}
										
									yourChoice = '8';	
									system("cls");
								}
							}
						}	
						// hỏi khách hàng về voucher
						char a;
						do {
							cout << "Quy khach co ma Voucher giam gia khong?( neu co thi nhap ma Voucher, neu khong thi go phim 'e' ):  ";
							cin >> idVoucher;
							if( checkid[idVoucher] == 0 ){
								cout << "\nQuy khach da nhap sai ma khuyen mai. Quy khach co muon tiep tuc khong?\n";
								cout << "1. Co.\n";
								cout << "2. Khong.\n";
								do {
									cout << "\nNhap lua chon cua ban:  ";
									cin >> a;
									if( a != '1' && a != '2' )
										cout << "\nBan chi duoc chon 1 hoac 2. Vui long nhap lai.\n";
								}while( a != '1' && a != '2' );
								if( a == '2' )
									break;
							}
						}while( checkid[idVoucher] == 0 || a == '1' );
						system("cls");
						// xác nhận thanh toán
						char acept;
						cout << "Moi quy khach xac nhan:\n";
						cout << "1. Xac nhan thanh toan.\n";
						cout << "2. Huy ve.\n";
						do {
							cout << "\nNhap lua chon cua ban:  ";
							cin >> acept;
							if( acept != '1' && acept != '2' )
								cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai.\n";
						}while( acept != '1' && acept != '2' );
						if( acept == '1' ){
							cout << endl; 
							displayBill(ticketNum, passfly, demoPass, checkid[idVoucher], idmap);
							cout << endl;
						}
						else { // nếu không xác nhận thanh toán thì clear toàn bộ thao tác trên
							demoPass.clear();
							passfly.clear();
							hisPass.clear();
							idmap.clear();
							mp.clear();
							cout << endl;
						}
						break;
					}
				case '2':
					{
						cout << endl;
						displayFlight(flight);
						cout << endl;
						break;
					}
				case '3':
					{
						if( demoPass.empty() ){
							cout << "Khong the huy chuyen bay vi quy khach chua dat chuyen bay nao.\n";
							break;
						}
						// list các chuyến bay đã đặt
						cout << PINK << "|   Ho va ten\t  " << " |    Hang ghe    " << "| Vi tri ghe " <<  "| Ma chuyen bay |" << RESET << "\n\n"; 
						for( auto it : demoPass ){
							cout << "|   " << it.first.getName() << "   |   " << it.first.getRank() << "   |     ";
							if( it.first.getPos() < 10 )
								cout << it.first.getPos() << "      |     ";
							else
								cout << it.first.getPos() << "     |     ";
							cout << it.second << "     |" << endl;
						}
						// cho người dùng nhập id và vị trí ngồi
						string id;
						int position;
						do {
							cout << "\nNhap id chuyen bay muon huy:  ";
							cin >> id;
							if( idmap[id] == 0 )
								cout << "\nID khong dung. Vui long nhap lai.\n";
						}while( idmap[id] == 0 );
						do {
							cout << "Nhap vi tri ghe muon huy:  ";
							cin >> position;
							if( mp[position] == 0 )
								cout << "\nVi tri khong hop le. Vui long nhap lai\n\n";
						}while( mp[position] == 0 );
						// xóa thông tin người dùng trong vector demoPass và thêm vào lịch sử với trạng thái hủy vé và giảm đi id chuyến bay đã hủy
						for( auto it = demoPass.begin(); it != demoPass.end(); it++) {
						    if( it->first.getPos() == position && it->second == id ) {
						    	it->first.setStatus("HUY");
						    	hisPass.push_back(make_pair(it->first, it->second));
						        demoPass.erase(it);
						        idmap[it->second]--;
						        break;
						    }
						}
						// cập nhật lại vị trí đã hủy
						for( auto &it : flight ){
							if( it.first.getId() == id ){
								it.first.setSitPosHuy(position);
								break;
							}
						}
						
						break;
					}	
				case '4':
					{
						cout << endl;
						displayHistory(hisPass);
						cout << endl;
						break;
					}
				case '5':
					{
						cout << endl;
						if( demoPass.empty() )
							cout << "Khong co Bill dat ve vi quy khach chua dat ve nao.\n";
						else
							displayBill(ticketNum, passfly, demoPass, 0, idmap);
						cout << endl;
						break;
					}
				case '6':
					break;
			}
		}
		for( auto it : hisPass ){
			history.push_back(it);
		}
		for( auto it : demoPass ){
			passInfo.push_back(it);
		}
		
	}
	writeFile(plane, flight, passInfo, voucher, personal, history);
	// sau khi chạy xong thì ghi thông tin người dùng, lịch sử đặt vé vào các file gốc để khi đăng nhập với tư cách quản lý thì sẽ thấy các thông tin vừa đặt
	return 0;
}