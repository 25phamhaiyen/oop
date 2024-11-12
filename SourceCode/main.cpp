#include "signin.h"
#include "setup.h"
#include "manager.h"
#include "voucher.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char **argv)
{
    // set up du lieu
    vector<pair<Plane, string>> plane;                                // may bay
    vector<pair<Flight, string>> flight;                              // chuyen bay
    unordered_map<string, vector<pair<Passenger, string>>> passInFly; // danh sach khach hang tren tuwng chuyen bay
    vector<vector<pair<humanInPlane, string>>> personal;              // nhan su
    vector<pair<Passenger, string>> passInfo;                         // khach hang
    vector<Voucher> voucher;                                          // voucher
    vector<pair<Passenger, string>> history;                          // lich su dat ve
    vector<pair<Plane, string>> emptyId;                              // vector chua thong tin may bay da bi xoa chuyen bay
    unordered_map<string, string> planeName;                          // get plane name tu id chuyen bay
    unordered_map<string, int> checkid;                               // luu thong tin id chuyen bay, shmb, ma khuyen mai, ma nhan su
    unordered_map<string, set<pair<humanInPlane, string>>> employ;    // luu vi tri cua nhan su
    readData(plane, flight, passInfo, voucher, personal, history);
    updateSitPos(flight, passInfo);
    for (auto it : plane)
    {
        checkid[it.second]++;
        checkid[it.first.getAircraftNumber()]++;
        planeName[it.second] = it.first.getPlaneName();
    }
    for (auto it : voucher)
    {
        checkid[it.getID()] = it.getReduceLevel();
    }
    for (auto it : personal)
    {
        for (auto i : it)
        {
            employ[i.first.getPosition()].insert(i);
            checkid[i.first.getId()]++;
        }
    }
    for (auto it : passInfo)
    {
        passInFly[it.second].push_back(it);
    }

    // chayj ct
    SignIn si;
    cout << "Ban dang nhap voi tu cach nao?" << endl;
    cout << "1.Quan ly \n2.Khach hang" << endl
         << endl;
    char choice;
    do
    {
        cout << "Nhap lua chon cua ban:  ";
        cin >> choice;
        // Kiểm tra nếu nhập liệu không hợp lệ (ví dụ: nhập ký tự không phải số)
        if (cin.fail() || (choice != '1' && choice != '2'))
        {
            cin.clear();                                         // Xóa trạng thái lỗi của cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bỏ qua các ký tự còn lại trong bộ đệm
            cout << RED;	
            cout << "\nBan chi co the chon 1 hoac 2. Vui long chon lai\n\n";
            cout << RESET;	
        }
        else
        {
            break; // Thoát khỏi vòng lặp nếu nhập đúng
        }
    } while (true);
    cin.ignore();

    // dang nhap giao dien quan ly

    if (choice == '1')
    {
        system("cls");
        cout << BLUE;	
        cout << "-----------------Sign In---------------------\n";
        cout << RESET;	
        si.sign_in('1');
        cout << "\n---------------------------------------------\n";
        system("cls");
        string mchoice;
        while (mchoice != "t" && mchoice != "T")
        {
            displayMenuManager();
            do
            {
                cout << "\nNhap lua chon cua ban:  ";
                cin >> mchoice;
                if ((stoi(mchoice) < 1 || stoi(mchoice) > 18) && (mchoice != "t" && mchoice != "T")){
                    cout << RED;	
                    cout << "\nBan chi duoc nhap gia tri trong khoang tu 1 -> 18 hoac {t,T}. Vui long nhap lai.\n";
                    cout << RESET;	    
                }
            } while ((stoi(mchoice) < 1 || stoi(mchoice) > 18) && (mchoice != "t" && mchoice != "T"));
            system("cls");
            if (mchoice == "1")
            {
                cout << endl;
                displayPlane(plane);
                cout << endl;
            }
            else if (mchoice == "2")
            {
                cout << endl;
                displayFlight(flight, planeName);
                cout << endl;
            }
            else if (mchoice == "3")
            {
                char a;
                do
                {
                    displayFlight(flight, planeName);
                    string id;
                    do
                    {
                        cout << "\nNhap id chuyen bay ban muon xem danh sach khach hang:  ";
                        cin >> id;
                        if (!checkid[id]){
                            cout << RED;	
                            cout << "\nId khong dung. Vui long nhap lai.\n";
                            cout << RESET;	    
                        }
                    } while (!checkid[id]);
                    system("cls");
                    if (passInFly[id].empty())
                    {
                        cout << YELLOW;	
                        cout << "Chuyen bay " << id << " hien chua co khach hang nao dat ve.\n";
                        cout << RESET;	
                    }
                    else
                    {
                        displayPassenger(passInFly[id]);
                        cout << endl;
                    }
                    cout << "\nBan co muon tiep tuc cho cac chuyen bay khac?\n";
                    cout << GREEN;	
                    cout <<"1. Co \n";
                    cout << RED;	
                    cout << "2. Khong\n";
                    cout << RESET;	
                    do
                    {
                        cout << "\nNhap lua chon cua ban:  ";
                        cin >> a;
                        if (a != '1' && a != '2'){
                            cout << RED;	
                            cout << "\nBa chi duoc chon 1 hoac 2. Vui long nhap lai.\n";
                            cout << RESET;	    
                        }
                    } while (a != '1' && a != '2');
                    system("cls");
                } while (a == '1');
            }
            else if (mchoice == "4")
            {
                cout << endl;
                displayPassenger(passInfo);
                cout << endl;
            }
            else if (mchoice == "5")
            {
                cout << endl;
                displayHistory(history);
                cout << endl;
            }
            else if (mchoice == "6")
            {
                cout << endl;
                displayHumanInPlane(personal);
                cout << endl;
            }
            else if (mchoice == "7")
            {
                cout << "Danh sach cac Co truong:  \n\n";
                displayHumanInPlaneWithPosition(employ, "Co truong");
                cout << "\nDanh sach cac Co pho:  \n\n";
                displayHumanInPlaneWithPosition(employ, "Co pho   ");
                cout << "\nDanh sach cac Tiep vien:  \n\n";
                displayHumanInPlaneWithPosition(employ, "Tiep vien");
                cout << endl;
            }
            else if (mchoice == "8")
            {
                cout << endl;
                displayVoucher(voucher);
                cout << endl;
            }
            else if (mchoice == "9")
            {
                // check xem mảng chưa máy bay đã bị xóa chuyến bay có phần tử nào không
                if (emptyId.empty())
                    addFlight(plane, flight, personal, checkid, employ, planeName);
                else
                {
                    char ch;
                    cout << "Hien tai may bay " << emptyId[0].first.getAircraftNumber() << " chua co chuyen bay nao. Ban co muon them thong tin chuyen bay cho may bay " << emptyId[0].first.getAircraftNumber();
                    cout << GREEN;	
                    cout <<"\n1. Co \n";
                    cout << RED;	
                    cout << "2. Khong\n";
                    cout << RESET;	
                    do
                    {
                        cout << "\nNhap lua chon cua ban:  ";
                        cin >> ch;
                        if (ch != '1' && ch != '2'){
                            cout << RED;
                            cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai\n";
                            cout << RESET;    
                        }
                    } while (ch != '1' && ch != '2');
                    system("cls");
                    if (ch == '2')
                    {
                        addFlight(plane, flight, personal, checkid, employ, planeName);
                    }
                    else
                    {
                        cout << "Nhap thong tin chuyen bay:  \n\n";
                        cout << "-------------------------------------\n\n";
                        Flight fly;
                        inputFlight(fly, checkid, flight);
                        emptyId[0].second = fly.getId();
                        checkid[fly.getId()]++;
                        flight.push_back(make_pair(fly, emptyId[0].first.getAircraftNumber()));
                        emptyId.erase(emptyId.begin());
                        planeName[fly.getId()] = emptyId[0].first.getPlaneName();
                        system("cls");
                    }
                }
                cout << endl;
            }
            else if (mchoice == "10")
            {
                cout << endl;
                addVoucher(voucher, checkid);
                cout << endl;
            }
            else if (mchoice == "11")
            {
                cout << endl;
                int n;
                do
                {
                    cout << "\nNhap so luong nhap su muon them:  ";
                    cin >> n;
                    if (n <= 0)
                        cout << "\nSo luong nhan su muon them phai > 0. Vui long nhap lai.\n";
                } while (n <= 0);
                humanInPlane hip;
                system("cls");
                while (n--)
                {
                    cin >> hip;
                    string first = "AP0";
                    int size = employ["Co truong"].size() + employ["Co pho   "].size() + employ["Tiep vien"].size();
                    if (size >= 100)
                        first.pop_back();
                    string realId = first + to_string(size);
                    while (checkid[first])
                    {
                        size++;
                        realId = first + to_string(size);
                    }
                    hip.setId(realId);
                    checkid[realId]++;
                    employ[hip.getPosition()].insert(make_pair(hip, "     "));
                    system("cls");
                }
            }
            else if (mchoice == "12")
            {
                char a = '1';
                while (a != '2')
                {
                    displayFlight(flight, planeName);
                    cout << endl;
                    string idToDelete;
                    do
                    {
                        cout << "\nNhap id chuyen bay can xoa:  ";
                        cin >> idToDelete;
                        if (!checkid[idToDelete])
                        {
                            cout << RED;
                            cout << "\nID chuyen bay khong hop le. Vui long nhap lai.\n";
                            cout << RESET;
                        }
                    } while (!checkid[idToDelete]);
                    // cap nhat may bay
                    planeName.erase(idToDelete);
                    for (auto &it : plane)
                    {
                        if (it.second == idToDelete)
                        {
                            it.second = "     ";
                            emptyId.push_back(it);
                            break;
                        }
                    }
                    // xoa chuyen bay
                    for (auto it = flight.begin(); it != flight.end(); ++it)
                    {
                        if (it->first.getId() == idToDelete)
                        {
                            flight.erase(it);
                            checkid[idToDelete]--;
                            break;
                        }
                    }
                    // cập nhật history
                    for (auto it = passInfo.begin(); it != passInfo.end();)
                    {
                        if (it->second == idToDelete)
                        {
                            it->first.setStatus("HUY");
                            history.push_back(make_pair(it->first, idToDelete));
                            it = passInfo.erase(it);
                        }
                        else
                            ++it;
                    }
                    cout << GREEN;
                    cout << "\nXoa chuyen bay thanh cong!\n\n";
                    cout << RESET;
                    cout << "Ban co muon tiep tuc xoa? ";
                    cout << GREEN;	
                    cout <<"\n1. Co \n";
                    cout << RED;	
                    cout << "2. Khong\n";
                    cout << RESET;	
                    do
                    {
                        cout << "\nNhap lua chon cua ban:  ";
                        cin >> a;
                        if (a != '1' && a != '2')
                            cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai\n";
                    } while (a != '1' && a != '2');
                    system("cls");
                }
            }
            else if (mchoice == "13")
            {
                char a = '1';
                while (a != '2')
                {
                    displayPlane(plane);
                    cout << endl;
                    string aircraft;
                    do
                    {
                        cout << "\nNhap so hieu may bay can xoa:  ";
                        cin >> aircraft;
                        if (!checkid[aircraft])
                        {
                            cout << RED;	
                            cout << "\nSo hieu may bay khong hop le. Vui long nhap lai.\n";
                            cout << RESET;	
                        }
                    } while (!checkid[aircraft]);

                    // xoa may bay
                    string idchuyenbay;
                    for (auto it = plane.begin(); it != plane.end(); ++it)
                    {
                        if (it->first.getAircraftNumber() == aircraft)
                        {
                            idchuyenbay = it->second;
                            plane.erase(it);
                            checkid[aircraft]--;
                            break;
                        }
                    }
                    system("cls");
                    cout << GREEN;	
                    cout << "\nXoa may bay thanh cong!\n\n";
                    cout << BLUE;	
                    cout << "Vi may bay " << aircraft << " tuong ung voi chuyen bay " << idchuyenbay << " da bi xoa. Nen he thong se tu dong xoa chuyen bay " << idchuyenbay << ".\n";
                    cout << RESET;	
                    cout << "\nBan co muon them may bay moi cho chuyen bay " << idchuyenbay << " ?\n";
                    cout << GREEN;	
                    cout <<"1. Co \n";
                    cout << RED;	
                    cout << "2. Khong\n";
                    cout << RESET;	
                    char ch;
                    do
                    {
                        cout << "\nNhap lua chon cua ban:  ";
                        cin >> ch;
                        if (ch != '1' && ch != '2')
                            cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai\n";
                    } while (ch != '1' && ch != '2');
                    if (ch == '2')
                    {
                        for (auto it = flight.begin(); it != flight.end(); it++)
                        {
                            if (it->first.getId() == idchuyenbay)
                            {
                                flight.erase(it);
                                checkid[idchuyenbay]--;
                                break;
                            }
                        }
                        // cập nhật history
                        for (auto it = passInfo.begin(); it != passInfo.end();)
                        {
                            if (it->second == idchuyenbay)
                            {
                                it->first.setStatus("HUY");
                                history.push_back(make_pair(it->first, idchuyenbay));
                                it = passInfo.erase(it);
                            }
                            else
                                ++it;
                        }

                        // cập nhật nhân sự
                        for (auto &it : personal)
                        {
                            bool check = false;
                            for (auto &i : it)
                            {
                                if (i.second == aircraft)
                                {
                                    i.second = "     ";
                                    check = true;
                                }
                            }
                            if (check)
                                break;
                        }
                    }
                    else
                    {
                        Plane p;
                        cout << "Nhap thong tin may bay:\n\n";
                        cin >> p;
                        string first;
                        if (p.getPlaneName() == "VietNam Airlines")
                            first = "VA0";
                        else if (p.getPlaneName() == "VietJet Air     ")
                            first = "VJ0";
                        else if (p.getPlaneName() == "Bamboo Airways  ")
                            first = "BA0";
                        else
                            first = "JP0";
                        int size = plane.size() + 1;
                        string aircraft = first + to_string(size);
                        while (checkid[aircraft])
                        {
                            size++;
                            aircraft = first + to_string(size);
                        }
                        checkid[aircraft]++;
                        p.setAircraftNumber(aircraft);
                        plane.push_back(make_pair(p, idchuyenbay));
                    }
                    system("cls");
                    cout << "Ban co muon tiep tuc xoa? ";
                    cout << GREEN;	
                    cout <<"\n1. Co \n";
                    cout << RED;	
                    cout << "2. Khong\n";
                    cout << RESET;
                    do
                    {
                        cout << "\nNhap lua chon cua ban:  ";
                        cin >> a;
                        if (a != '1' && a != '2')
                            cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai\n";
                    } while (a != '1' && a != '2');
                    system("cls");
                }
            }
            else if (mchoice == "14")
            {
                char a = '1';
                while (a != '2')
                {
                    char t;
                    cout << "Ban muon xoa nhan su o vi tri nao? \n1. Co truong \n2. Co pho \n3. Tiep vien \n";
                    do
                    {
                        cout << "\nNhap lua chon cua ban:  ";
                        cin >> t;
                        if (t < '1' || t > '3')
                            cout << "\nBan chi dươc nhap 1 hoac 2 hoac 3. Vui long nhap lai.\n";
                    } while (t < '1' || t > '3');
                    string pos = (t == '1') ? "Co truong" : ((t == '2') ? "Co pho   " : "Tiep vien");
                    system("cls");
                    displayHumanInPlaneWithPosition(employ, pos);
                    string id;
                    bool isValidId = false;
                    do
                    {
                        cout << "\nNhap id nhan su muon xoa:  ";
                        cin >> id;
                        for (auto it = employ[pos].begin(); it != employ[pos].end(); it++)
                        {
                            if (it->first.getId() == id)
                            {
                                isValidId = true;
                                employ[pos].erase(it);
                                checkid[id]--;
                                break;
                            }
                        }
                        for (auto &it : personal)
                        {
                            for (auto &i : it)
                            {
                                if (i.first.getId() == id)
                                { // thay the nhan su vua xoa bang 1 nhan su khac
                                    system("cls");
                                    displayHumanInPlaneWithPosition(employ, i.first.getPosition());
                                    cout << "Chon 1 " << i.first.getPosition() << " de thay the " << i.first.getPosition() << " vua xoa\n";
                                    bool isValidId = false;
                                    string idToReplace;
                                    humanInPlane hip;
                                    do
                                    {
                                        cout << "\nNhap id nhan su muon them:  ";
                                        cin >> idToReplace;
                                        for (auto itor : employ[pos])
                                        {
                                            if (itor.first.getId() == idToReplace)
                                            {
                                                isValidId = true;
                                                hip = itor.first;
                                                break;
                                            }
                                        }
                                        if (!isValidId)
                                            cout << "\nId khong dung. Vui long nhap lai.\n";
                                    } while (!isValidId);
                                    i.first = hip;
                                }
                            }
                        }
                        if (!isValidId)
                            cout << "\nId khong dung. Vui long nhap lai.\n";
                    } while (!isValidId);
                    cout << "\nXoa nhan su " << id << " thanh cong!\n\n";
                    cout << "Ban co muon tiep tuc xoa? \n1. Co \n2. Khong\n";
                    do
                    {
                        cout << "\nNhap lua chon cua ban:  ";
                        cin >> a;
                        if (a != '1' && a != '2')
                            cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai\n";
                    } while (a != '1' && a != '2');
                    system("cls");
                }
            }
            else if (mchoice == "15")
            {
                char a = '1';
                while (a != '2')
                {
                    displayVoucher(voucher);
                    cout << endl;
                    string id;
                    do
                    {
                        cout << "\nNhap ma khuyen mai can xoa:  ";
                        cin >> id;
                        if (!checkid[id])
                        {
                            cout << RED;
                            cout << "\nMa khuyen mai khong hop le. Vui long nhap lai.\n";
                            cout << RESET;
                        }
                    } while (!checkid[id]);

                    // xoa may bay
                    for (auto it = voucher.begin(); it != voucher.end(); ++it)
                    {
                        if (it->getID() == id)
                        {
                            voucher.erase(it);
                            checkid[id]--;
                            break;
                        }
                    }
                    cout << "\nXoa Voucher thanh cong!\n\n";
                    cout << "Ban co muon tiep tuc xoa? \n1. Co \n2. Khong\n";
                    do
                    {
                        cout << "\nNhap lua chon cua ban:  ";
                        cin >> a;
                        if (a != '1' && a != '2')
                            cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai\n";
                    } while (a != '1' && a != '2');
                    system("cls");
                }
            }
            else if (mchoice == "16")
            {
                char a = '1';
                while (a != '2')
                {
                    displayFlight(flight, planeName);
                    cout << endl;
                    string idToDelete;
                    do
                    {
                        cout << "\nNhap id chuyen bay can sua:  ";
                        cin >> idToDelete;
                        if (!checkid[idToDelete])
                        {
                            cout << RED;
                            cout << "\nID chuyen bay khong hop le. Vui long nhap lai.\n";
                            cout << RESET;
                        }
                    } while (!checkid[idToDelete]);
                    char ychoice = '7';
                    while (ychoice != '6')
                    {
                        system("cls");
                        displayChinhsuaChuyenbay();
                        cout << endl;
                        do
                        {
                            cout << "Nhap lua chon cua ban:  ";
                            cin >> ychoice;
                            if (ychoice < '1' || ychoice > '6')
                                cout << "\bBan chi duoc chon gia tri trong khoang 1 -> 6. Vui long nhap lai.\n\n";
                        } while (ychoice < '1' || ychoice > '6');
                        system("cls");
                        switch (ychoice)
                        {
                        case '1':
                        {
                            string idToReplace;
                            do
                            {
                                cout << "Nhap ID ban muon chinh sua:  ";
                                cin >> idToReplace;
                                if (checkid[idToReplace])
                                    cout << "\nID ban nhap da ton tai. Vui long nhap lai.\n\n";
                            } while (checkid[idToReplace]);
                            for (auto it = flight.begin(); it != flight.end(); ++it)
                            {
                                if (it->first.getId() == idToDelete)
                                {
                                    it->first.setId(idToReplace);
                                    break;
                                }
                            }
                            cout << GREEN;
                            cout << "\nChinh sua ID thanh cong!\n\n";
                            cout << RESET;
                            break;
                        }
                        case '2':
                        {
                            string desToReplace;
                            cout << "Nhap noi den ban muon chinh sua:  ";
                            cin >> desToReplace;
                            for (int i = 0; i < 9 - desToReplace.size(); i++)
                                desToReplace += ' ';
                            for (auto it = flight.begin(); it != flight.end(); ++it)
                            {
                                if (it->first.getId() == idToDelete)
                                {
                                    it->first.setDestination(desToReplace);
                                    break;
                                }
                            }
                            cout << GREEN;
                            cout << "\nChinh sua noi den thanh cong!\n\n";
                            cout << RESET;
                            break;
                        }
                        case '3':
                        {
                            time_t t = time(nullptr); // LAY THOI GIAN TAI
                            tm *now = localtime(&t);
                            Date nowDate(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
                            Date d;
                            do
                            {
                                cout << "Nhap ngay ban muon chinh sua:  \n\n";
                                cin >> d;
                                if (d < nowDate)
                                    cout << "\nNgay bay phai lon hon ngay hom nay. Vui long nhap lai.\n";
                            } while (d < nowDate);
                            for (auto it = flight.begin(); it != flight.end(); ++it)
                            {
                                if (it->first.getId() == idToDelete)
                                {
                                    it->first.setFlyDate(d);
                                    break;
                                }
                            }
                            cout << GREEN;
                            cout << "\nChinh sua ngay bay thanh cong!\n\n";
                            cout << RESET;
                            break;
                        }
                        case '4':
                        {
                            cout << endl;
                            Time sTime, eTime;
                            cout << "Nhap khoang thoi gian can sua: \n\n";
                            cout << "Thoi gian khoi hanh:  \n";
                            cin >> sTime;
                            do
                            {
                                cout << "\nThoi gian ha canh:  \n";
                                cin >> eTime;
                                if (eTime <= sTime)
                                    cout << "\nThoi gian sau phai lon hon thoi gian truoc. Vui long nhap lai\n";
                            } while (eTime <= sTime);
                            for (auto it = flight.begin(); it != flight.end(); ++it)
                            {
                                if (it->first.getId() == idToDelete)
                                {
                                    it->first.setTime(sTime, eTime);
                                    break;
                                }
                            }
                            cout << GREEN;
                            cout << "\nChinh sua gio bay thanh cong!\n\n";
                            cout << RESET;
                            break;
                        }
                        case '5':
                        {
                            cout << endl;
                            double minTic, maxTic;
                            cout << "Nhap khoang gia ve muon chinh sua: \n\n";
                            do
                            {
                                cout << "Tu:  ";
                                cin >> minTic;
                                if (minTic <= 0)
                                    cout << "\nGia ve phai > 0. Vui long nhap lai.\n\n";
                            } while (minTic <= 0);
                            do
                            {
                                cout << "Den:  ";
                                cin >> maxTic;
                                if (maxTic < minTic)
                                    cout << "\nGia ve sau phai lon hon gia ve truoc. Vui long nhap lai.\n\n";
                            } while (maxTic < minTic);
                            for (auto it = flight.begin(); it != flight.end(); ++it)
                            {
                                if (it->first.getId() == idToDelete)
                                {
                                    it->first.setPrice(minTic, maxTic);
                                    break;
                                }
                            }
                            cout << GREEN;
                            cout << "\nChinh sua gia ve thanh cong!\n\n";
                            cout << RESET;
                            break;
                        }
                        case '6':
                            break;
                        }
                    }
                    system("cls");
                    cout << "Ban co muon tiep tuc chinh sua cac chuyen bay khac?\n1. Co \n2. Khong\n";
                    do
                    {
                        cout << "\nNhap lua chon cua ban:  ";
                        cin >> a;
                        if (a != '1' && a != '2')
                            cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai.\n";
                    } while (a != '1' && a != '2');
                    system("cls");
                }
            }
            else if (mchoice == "17")
            {
                char a = '1';
                while (a != '2')
                {
                    displayPlane(plane);
                    cout << endl;
                    string idToDelete;
                    do
                    {
                        cout << "\nNhap so hieu may bay can sua:  ";
                        cin >> idToDelete;
                        if (!checkid[idToDelete])
                        {
                            cout << RED;
                            cout << "\nSo hieu may bay khong hop le. Vui long nhap lai.\n";
                            cout << RESET;
                        }
                    } while (!checkid[idToDelete]);
                    char ychoice = '7';
                    while (ychoice != '5')
                    {
                        system("cls");
                        displayChinhsuaMaybay();
                        cout << endl;
                        do
                        {
                            cout << "Nhap lua chon cua ban:  ";
                            cin >> ychoice;
                            if (ychoice < '1' || ychoice > '5')
                                cout << "\bBan chi duoc chon gia tri trong khoang 1 -> 5. Vui long nhap lai.\n\n";
                        } while (ychoice < '1' || ychoice > '5');
                        system("cls");
                        switch (ychoice)
                        {
                        case '1':
                        {
                            cout << endl;
                            char c;
                            string planeName;
                            cout << "Chon 1 trong cac hang bay:\n\n";
                            
                            cout << "1. VietNam Airlines\n";
                            cout << RED;
                            cout << "2. VietJet Air\n";
                            cout << BLUE;
                            cout << "3. Bamboo Airways\n";
                            cout << YELLOW;
                            cout << "4. Jetstar Pacific\n\n";
                            cout << RESET;
                            do
                            {
                                cout << "Nhap lua chon cua ban:  ";
                                cin >> c;
                                if (c < '1' || c > '4')
                                    cout << "\nBan chi duoc nhap gia tri trong khaong 1 -> 4. Vui long nhap lai\n";
                            } while (c < '1' || c > '4');
                            switch (c)
                            {
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
                            for (auto it = plane.begin(); it != plane.end(); ++it)
                            {
                                if (it->first.getAircraftNumber() == idToDelete)
                                {
                                    it->first.setPlaneName(planeName);
                                    break;
                                }
                            }
                            cout << GREEN;
                            cout << "\nChinh sua ten hang bay thanh cong!\n\n";
                            cout << RESET;
                            break;
                        }
                        case '2':
                        {
                            string idToReplace;
                            do
                            {
                                cout << "Nhap so hieu may bay ban muon thay the:  ";
                                cin >> idToReplace;
                                if (checkid[idToReplace])
                                    cout << "\nSo hieu may bay ban nhap da ton tai. Vui long nhap lai.\n\n";
                            } while (checkid[idToReplace]);
                            for (auto it = plane.begin(); it != plane.end(); ++it)
                            {
                                if (it->first.getAircraftNumber() == idToDelete)
                                {
                                    it->first.setAircraftNumber(idToReplace);
                                    break;
                                }
                            }
                            cout << GREEN;
                            cout << "\nChinh sua so hieu may bay thanh cong!\n\n";
                            cout << RESET;
                            break;
                        }
                        case '3':
                        {
                            char b;
                            cout << "Chon loai may bay de thay the:\n1. Dan dung \n2. Cho hang\n";
                            do
                            {
                                cout << "\nNhap lua chon cua ban:  ";
                                cin >> b;
                                if (b != '1' && b != '2')
                                    cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai.\n";
                            } while (b != '1' && b != '2');
                            string type = (b == '1') ? "Dan dung" : "Cho hang";
                            for (auto it = plane.begin(); it != plane.end(); ++it)
                            {
                                if (it->first.getAircraftNumber() == idToDelete)
                                {
                                    it->first.setType(type);
                                    break;
                                }
                            }
                            cout << GREEN;
                            cout << "\nChinh sua loai may bay thanh cong!\n\n";
                            cout << RESET;
                            break;
                        }
                        case '4':
                        {
                            char b;
                            cout << "Chon trang thai de thay the:\n1. Hoat dong \n2. Bao tri\n";
                            do
                            {
                                cout << "\nNhap lua chon cua ban:  ";
                                cin >> b;
                                if (b != '1' && b != '2')
                                    cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai.\n";
                            } while (b != '1' && b != '2');
                            string status = (b == '1') ? "Hoat dong" : "Bao tri  ";
                            for (auto it = plane.begin(); it != plane.end(); ++it)
                            {
                                if (it->first.getAircraftNumber() == idToDelete)
                                {
                                    it->first.setStatus(status);
                                    break;
                                }
                            }
                            cout << GREEN;
                            cout << "\nChinh sua loai may bay thanh cong!\n\n";
                            cout << RESET;
                            break;
                        }
                        case '5':
                            break;
                        }
                    }
                    system("cls");
                    cout << "Ban co muon tiep tuc chinh sua cac may bay khac?\n1. Co \n2. Khong\n";
                    do
                    {
                        cout << "\nNhap lua chon cua ban:  ";
                        cin >> a;
                        if (a != '1' && a != '2')
                            cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai.\n";
                    } while (a != '1' && a != '2');
                    system("cls");
                }
            }
            else if (mchoice == "18")
            {
                char a = '1';
                while (a != '2')
                {
                    displayVoucher(voucher);
                    cout << endl;
                    string idToDelete;
                    do
                    {
                        cout << "\nNhap ma khuyen mai can sua:  ";
                        cin >> idToDelete;
                        if (!checkid[idToDelete])
                        {
                            cout << RED;
                            cout << "\nMa khuyen mai khong hop le. Vui long nhap lai.\n";
                            cout << RESET;
                        }
                    } while (!checkid[idToDelete]);
                    char ychoice = '7';
                    while (ychoice != '5')
                    {
                        system("cls");
                        displayChinhsuaVoucher();
                        cout << endl;
                        do
                        {
                            cout << "Nhap lua chon cua ban:  ";
                            cin >> ychoice;
                            if (ychoice < '1' || ychoice > '5')
                                cout << "\bBan chi duoc chon gia tri trong khoang 1 -> 5. Vui long nhap lai.\n\n";
                        } while (ychoice < '1' || ychoice > '5');
                        system("cls");
                        switch (ychoice)
                        {
                        case '1':
                        {
                            string idToReplace;
                            do
                            {
                                cout << "Nhap ma khuyen mai ban muon thay the:  ";
                                cin >> idToReplace;
                                if (checkid[idToReplace])
                                    cout << "\nMa khuyen mai ban nhap da ton tai. Vui long nhap lai.\n\n";
                            } while (checkid[idToReplace]);
                            for (auto it = voucher.begin(); it != voucher.end(); ++it)
                            {
                                if (it->getID() == idToDelete)
                                {
                                    checkid[idToDelete]--;
                                    idToDelete = idToReplace;
                                    it->setID(idToReplace);
                                    checkid[idToDelete]++;
                                    break;
                                }
                            }
                            cout << GRREN;
                            cout << "\nChinh sua ma khuyen mai thanh cong!\n\n";
                            cout << RESET;
                            break;
                        }
                        case '2':
                        {
                            double level;
                            do
                            {
                                cout << "Nhap muc giam ban muon thay the:  ";
                                cin >> level;
                                if (level <= 0)
                                    cout << "\nMuc giam phai > 0. Vui long nhap lai.\n\n";
                            } while (level <= 0);
                            for (auto it = voucher.begin(); it != voucher.end(); ++it)
                            {
                                if (it->getID() == idToDelete)
                                {
                                    it->setReduceLevel(level);
                                    break;
                                }
                            }
                            cout << GREEN;
                            cout << "\nChinh sua muc giam thanh cong!\n\n";
                            cout << RESET;
                            break;
                        }
                        case '3':
                        {
                            Date t;
                            for (auto it = voucher.begin(); it != voucher.end(); ++it)
                            {
                                if (it->getID() == idToDelete)
                                {
                                    t = it->getReduceDeadline();
                                    break;
                                }
                            }
                            Date d;
                            do
                            {
                                cout << "Nhap ngay bat dau khuyen mai:  \n\n";
                                cin >> d;
                                if (d > t)
                                {
                                    cout << RED;
                                    cout << "\nNgay bat dau khuyen mai phai nho hon ngay ket thuc khuyen mai.\n";
                                    cout << RESET;
                                    cout << "Vui long nhap ngay bat dau khuyen mai nho hon ngay:  " << t << "\n\n";
                                }
                            } while (d > t);
                            for (auto it = voucher.begin(); it != voucher.end(); ++it)
                            {
                                if (it->getID() == idToDelete)
                                {
                                    it->setFromDate(d);
                                    break;
                                }
                            }
                            cout << GREEN;
                            cout << "\nChinh sua ngay bat dau khuyen mai thanh cong!\n\n";
                            cout << RESET;
                            break;
                        }
                        case '4':
                        {
                            Date t;
                            for (auto it = voucher.begin(); it != voucher.end(); ++it)
                            {
                                if (it->getID() == idToDelete)
                                {
                                    t = it->getFromDate();
                                    break;
                                }
                            }
                            Date d;
                            do
                            {
                                cout << "Nhap ngay bat dau khuyen mai:  \n\n";
                                cin >> d;
                                if (d < t)
                                {
                                    cout << RED;
                                    cout << "\nNgay ket thuc khuyen mai phai lon hon ngay bat dau khuyen mai.\n";
                                    cout << RESET;
                                    cout << "Vui long nhap ngay ket thuc khuyen mai lon hon ngay:  " << t << "\n\n";
                                }
                            } while (d < t);
                            for (auto it = voucher.begin(); it != voucher.end(); ++it)
                            {
                                if (it->getID() == idToDelete)
                                {
                                    it->setReduceDeadline(d);
                                    break;
                                }
                            }
                            cout << GREEN;
                            cout << "\nChinh sua ngay ket thuc khuyen mai thanh cong!\n\n";
                            cout << RESET;
                            break;
                        }
                        case '5':
                            break;
                        }
                    }
                    system("cls");
                    cout << "Ban co muon tiep tuc chinh sua cac Voucher khac?\n1. Co \n2. Khong\n";
                    do
                    {
                        cout << "\nNhap lua chon cua ban:  ";
                        cin >> a;
                        if (a != '1' && a != '2')
                            cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai.\n";
                    } while (a != '1' && a != '2');
                    system("cls");
                }
            }
            else if (mchoice == "t" || mchoice == "T")
            {
                cout << endl
                     << "KET THUC\n";
            }
        }
    }

    // dang nhap/ dang ky giao dien nguoi dung

    else
    {
        system("cls");
        char signChoice;
        cout << "Ban da co tai khoan chua?" << endl;
        cout << "1.Da co tai khoan \n2.Chua co tai khoan" << endl
             << endl;
        do
        {
            cout << "Nhap lua chon cua ban:  ";
            cin >> signChoice;
            if (signChoice != '1' && signChoice != '2')
                cout << "\nBan chi co the chon 1 hoac 2. Vui long chon lai\n\n";
        } while (signChoice != '1' && signChoice != '2');
        system("cls");
        if (signChoice == '1')
        {
            cin.ignore();
            cout << PINK;
            cout << "-----------------Sign In---------------------\n";
            cout << RESET;
            si.sign_in('2');
            cout << "\n---------------------------------------------\n";
        }
        else
        {
            cout << PINK;
            cout << "-----------------Sign Up---------------------\n";
            cout << RESET;
            si.sign_up();
            cout << "\n---------------------------------------------\n";
            system("cls");
            cout << PINK;
            cout << "-----------------Sign In---------------------\n";
            cout << RESET;
            si.sign_in('2');
            cout << "\n---------------------------------------------\n";
        }
        system("cls");
        char choice;
        vector<pair<Flight, string>> passfly;     // vector luu chuyen bay nguoi dung đã đặt
        vector<pair<Passenger, string>> demoPass; // vector lưu thông tin người dùng
        vector<pair<Passenger, string>> hisPass;  // vector lưu lịch sử đặt vé, hủy vé
        unordered_map<int, int> mp;               // map dùng để lưu vị trí người dùng đặt
        unordered_map<string, int> idmap;         // map dùng để lưu mã chuyến bay
        string namefile = si.getUserName() + ".txt";
        readDataUser(demoPass, passfly, hisPass, namefile);
        if (!demoPass.empty())
        {
            for (auto it : demoPass)
            {
                mp[it.first.getPos()]++;
                idmap[it.second]++;
            }
        }
        while (choice != '6')
        {
            int ticketNum;
            displayMenuUser();
            cout << endl;
            do
            {
                cout << "Nhap lua chon cua ban:  ";
                cin >> choice;
                if (choice < '1' || choice > '6')
                    cout << "\nBan chi duoc nhap trong khoang tu 1 -> 6. Vui long nhap lai\n\n";
            } while (choice < '1' || choice > '6');
            system("cls");
            switch (choice)
            {
            case '1':
            {
                do
                {
                    cout << "Nhap so luong ve muon dat:  ";
                    cin >> ticketNum;
                    if (ticketNum <= 0){
                        cout << RED;
                        cout << "\nSo luong ve phai > 0. Vui long nhap lai.\n\n";
                        cout << RESET;
                    }
                } while (ticketNum <= 0);

                Passenger pas;
                char yourChoice = '0';
                string idVoucher, area;

                for (int i = 0; i < ticketNum; i++)
                {
                    char n;
                    cout << "Ban muon bay trong nuoc hay nuoc ngoai?\n";
                    cout << "1. Trong nuoc.\n";
                    cout << "2. Nuoc ngoai.\n";
                    do
                    {
                        cout << "\nNhap lua chon cua ban:  ";
                        cin >> n;
                        if (n != '1' && n != '2')
                            cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai.\n";
                    } while (n != '1' && n != '2');
                    if (n == '1')
                    {
                        pas.setInCountry(true); // dùng để kiểm tra trong nước hay ngoài nước để nhập passport
                        area = "in ";
                    }
                    else
                    {
                        pas.setInCountry(false);
                        area = "out";
                    }
                    system("cls");
                    cout << BLUE;
                    cout << "Ban hay su dung cac tinh nang ben duoi de tim chuyen bay mong muon\n";
                    cout << RESET;
                    do
                    { // hiển thị menu đặt vé khi nhập thông tin xong thì sẽ hiện ra để người dùng dễ dàng chọn chuyến bay
                        displayMenuDatve();
                        cin.ignore();
                        do
                        {
                            cout << "\nNhap lua chon cua ban:  ";
                            cin >> yourChoice;
                            if (yourChoice < '1' || yourChoice > '8')
                                cout << "\nBan chi duoc nhap trong khoang tu 1 -> 8. Vui long nhap lai\n";
                        } while (yourChoice < '1' || yourChoice > '8');
                        system("cls");
                        switch (yourChoice)
                        {
                        case '1':
                            cout << endl;
                            displayFlightUser(flight, area, planeName);
                            cout << endl;
                            break;
                        case '2':
                        {
                            cout << endl;
                            Date date;
                            cout << "Nhap ngay bay ban muon tim:\n";
                            date.inputDate();
                            findWithFlightDate(flight, date, area);
                            cout << endl;
                            break;
                        }
                        case '3':
                        {
                            cout << endl;
                            double minTic, maxTic;
                            cout << "Nhap khoang gia ve muon tim: \n\n";
                            do
                            {
                                cout << "Tu:  ";
                                cin >> minTic;
                                if (minTic <= 0)
                                    cout << "\nGia ve phai > 0. Vui long nhap lai.\n\n";
                            } while (minTic <= 0);
                            do
                            {
                                cout << "Den:  ";
                                cin >> maxTic;
                                if (maxTic < minTic)
                                    cout << "\nGia ve sau phai lon hon gia ve truoc. Vui long nhap lai.\n\n";
                            } while (maxTic < minTic);

                            findWithTicketPrice(flight, minTic, maxTic, pas.getRank(), area);
                            cout << endl;
                            break;
                        }
                        case '4':
                        {
                            cout << endl;
                            char c;
                            string plName;
                            cout << "Chon 1 trong cac hang bay:\n\n";

                            cout << "1. VietNam Airlines\n";
                            cout << RED;
                            cout << "2. VietJet Air\n";
                            cout << BLUE;
                            cout << "3. Bamboo Airways\n";
                            cout << YELLOW;
                            cout << "4. Jetstar Pacific\n\n";
                            cout << RESET;
                            do
                            {
                                cout << "Nhap lua chon cua ban:  ";
                                cin >> c;
                                if (c < '1' || c > '4')
                                    cout << "\nBan chi duoc nhap gia tri trong khaong 1 -> 4. Vui long nhap lai\n";
                            } while (c < '1' || c > '4');
                            switch (c)
                            {
                            case '1':
                                plName = "VietNam Airlines";
                                break;
                            case '2':
                                plName = "VietJet Air     ";
                                break;
                            case '3':
                                plName = "Bamboo Airways  ";
                                break;
                            case '4':
                                plName = "Jetstar Pacific ";
                                break;
                            }
                            findWithPlaneName(flight, plName, area, planeName);
                            cout << endl;
                            break;
                        }
                        case '5':
                        {
                            cout << endl;
                            cin.ignore();
                            string destination;
                            cout << "Nhap noi den muon tim:  ";
                            getline(cin, destination);
                            string space = "";
                            for (int i = 0; i < 9 - destination.size(); i++)
                            {
                                space += " ";
                            }
                            destination += space;
                            findWithDestination(flight, destination, area);
                            break;
                        }
                        case '6':
                        {
                            cout << endl;
                            Time sTime, eTime;
                            cout << "Nhap khoang thoi gian muon tim: \n\n";
                            cout << "Tu:  \n";
                            cin >> sTime;
                            do
                            {
                                cout << "\nDen:  \n";
                                cin >> eTime;
                                if (eTime <= sTime){
                                    cout << RED;
                                    cout << "\nThoi gian sau phai lon hon thoi gian truoc. Vui long nhap lai\n";
                                    cout << RESET;    
                                 }
                            } while (eTime <= sTime);
                            findWithTime(flight, sTime, eTime, area);
                            break;
                        }
                        case '7':
                        {
                            cout << endl;
                            sortIncreaseTicketPrice(flight);
                            displayFlightUser(flight, area, planeName);
                            break;
                        }
                        case '8':
                            cout << endl
                                 << "KET THUC\n";
                            break;
                        }
                        // hỏi người dùng đã tìm được chuyến bay mong muốn chưa
                        char ch;
                        cout << "\nBan da tim duoc chuyen bay mong muon chua?\n";
                        cout << GREEN;
                        cout << "1. Da tim duoc.\n";
                        cout << RED;
                        cout << "2. Chua tim duoc.\n";
                        cout << RESET;
                        do
                        {
                            cout << "\nNhap lua chon cua ban:  ";
                            cin >> ch;
                            if (ch != '1' && ch != '2')
                                cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai\n";
                        } while (ch != '1' && ch != '2');
                        cout << "------------------------------------\n";
                        // nếu đã tìm được thì sẽ cho người dùng nhập mã chuyến bay và chỗ ngồi
                        if (ch == '1')
                        {
                            string id, plane;
                            cin.ignore();
                            do
                            {
                                cout << "\nNhap id chuyen bay muon dat:  ";
                                cin >> id;
                                if (!checkid[id]){
                                    cout << RED;
                                    cout << "\nID chuyen bay khong co trong danh sach. Vui long nhap lai.\n";
                                    cout << RESET;
                                }
                                    
                            } while (!checkid[id]);
                            Flight f;
                            for (auto it : flight)
                            {
                                if (it.first.getId() == id)
                                {
                                    f = it.first;
                                    plane = it.second;
                                    break;
                                }
                            }
                            system("cls");
                            cout << "Moi nhap thong tin ca nhan cua ban: \n\n---------------------------------------\n";
                            cin >> pas;
                            system("cls");
                            // cout << "Danh sach cho ngoi hang " << pas.getRank() << ":  \n\n";
                            if (pas.getRank() == "Thuong gia")
                                displayChoNgoi(flight, id, 1, 15);
                            else
                                displayChoNgoi(flight, id, 16, 50);
                            cout << "\n\nLuu y: Nhung vi tri mau";
                            cout << RED;
                            cout << " DO ";
                            cout << RESET;
                            cout << "la da co nguoi dat cho. Nhung vi tri mau";
                            cout << GREEN;
                            cout << " XANH ";
                            cout << RESET;
                            cout << "la con trong";

                            int pos;
                            do
                            {
                                cout << "\nNhap vi tri ghe ban muon ngoi:  ";
                                cin >> pos;
                                if (f.findSitPos(pos))
                                {
                                    cout << RED;
                                    cout << "\nGhe ngoi ban chon da duoc dat truoc do. Vui long chon so ghe khac.\n";
                                    cout << RESET;
                                    continue;
                                }
                                if (pas.getRank() == "Thuong gia" && (pos < 1 || pos > 15))
                                {
                                    cout << "\nBan chi duoc chon cac vi tri ghe " << YELLOW << "( 1->15 ). " << RED << "Vui long chon lai.\n";
                                }
                                if (pas.getRank() == "Pho thong " && (pos < 16 || pos > 50))
                                {
                                    cout << "\nBan chi duoc chon cac vi tri ghe " << YELLOW << "( 16->50 ). " << RED << "Vui long chon lai.\n";
                                }
                            } while (f.findSitPos(pos) || (pas.getRank() == "Thuong gia" && (pos < 1 || pos > 15)) || (pas.getRank() == "Pho thong " && (pos < 16 || pos > 50)));
                            // cập nhật vị trí ghế và mã chuyến bay;
                            mp[pos]++;
                            idmap[id]++;
                            pas.setPosition(pos);
                            // thêm vào các vector
                            demoPass.push_back(make_pair(pas, id));
                            hisPass.push_back(make_pair(pas, id));
                            bool check = true;
                            // đoạn này để kiểm tra xem trong vector đã tồn tại chuyến bay chưa nếu chưa thì dẩy vào
                            for (auto &it : passfly)
                            {
                                if (it.first.getId() == id)
                                {
                                    check = false;
                                    break;
                                }
                            }
                            if (check)
                            {
                                passfly.push_back(make_pair(f, plane));
                            }
                            // cập nhật vị trí ngồi mới của chuyến bay
                            for (auto &it : flight)
                            {
                                if (it.first.getId() == id)
                                {
                                    it.first.setSitPos(pos);
                                }
                            }

                            yourChoice = '8';
                            system("cls");
                        }
                        else
                            system("cls");
                    } while (yourChoice != '8');
                }
                // hỏi khách hàng về voucher
                do
                {
                    cout << "Quy khach co ma Voucher giam gia khong?( neu co thi nhap ma Voucher, neu khong thi go phim 'e' ):  ";
                    cin >> idVoucher;
                    if (idVoucher == "e" || idVoucher == "E")
                        break;
                    if (!checkid[idVoucher])
                    {
                        cout << RED;
                        cout << "\nQuy khach da nhap sai ma khuyen mai.\n\n";
                        cout << RESET;
                    }
                } while (!checkid[idVoucher] && idVoucher != "e" && idVoucher != "E");
                system("cls");
                // xác nhận thanh toán
                char acept;
                cout << "Moi quy khach xac nhan:\n";
                cout << GREEN;
                cout << "1. Xac nhan thanh toan.\n";
                cout << RED;
                cout << "2. Huy ve.\n";
                cout << RESET;
                do
                {
                    cout << "\nNhap lua chon cua ban:  ";
                    cin >> acept;
                    if (acept != '1' && acept != '2')
                        cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai.\n";
                } while (acept != '1' && acept != '2');
                system("cls");
                if (acept == '1')
                {
                    cout << endl;
                    displayBill(ticketNum, passfly, demoPass, checkid[idVoucher], idmap);
                    cout << endl;
                }
                else
                { // nếu không xác nhận thanh toán thì clear toàn bộ thao tác trên
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
                displayFlight(flight, planeName);
                cout << endl;
                break;
            }
            case '3':
            {
                if (demoPass.empty())
                {
                    cout << RED;
                    cout << "\nKhong the huy chuyen bay vi quy khach chua dat chuyen bay nao.\n\n";
                    cout << RESET;
                    break;
                }
                char b;
                cout << "Ban co chac chan muon huy? \n1. Co \n2. Khong\n";
                do
                {
                    cout << "\nNhap lua chon cua ban:  ";
                    cin >> b;
                    if (b != '1' && b != '2')
                        cout << "\nBan chi duoc chon 1 hoac 2. Vui long chon lai.\n";
                } while (b != '1' && b != '2');
                if (b == '2')
                    break;
                // list các chuyến bay đã đặt
                cout << PINK << "\n+----------------------------------------------------------------+" << endl;
                cout << "|   Ho va ten\t  " << " |    Hang ghe    " << "| Vi tri ghe " << "| Ma chuyen bay |" << endl;
                cout << "+----------------------------------------------------------------+" << RESET << endl;
                for (auto it : demoPass)
                {
                    cout << "|   " << it.first.getName() << "   |   " << it.first.getRank() << "   |     ";
                    if (it.first.getPos() < 10)
                        cout << it.first.getPos() << "      |     ";
                    else
                        cout << it.first.getPos() << "     |     ";
                    cout << it.second << "     |" << endl;
                }
                cout << "+----------------------------------------------------------------+\n";
                // cho người dùng nhập id và vị trí ngồi
                string id;
                int position;
                do
                {
                    cout << "\nNhap id chuyen bay muon huy:  ";
                    cin >> id;
                    if (idmap[id] == 0)
                        cout << "\nID khong dung. Vui long nhap lai.\n";
                } while (idmap[id] == 0);
                do
                {
                    cout << "Nhap vi tri ghe muon huy:  ";
                    cin >> position;
                    if (!mp[position])
                        cout << "\nVi tri khong hop le. Vui long nhap lai\n\n";
                } while (!mp[position]);
                // xóa thông tin người dùng trong vector demoPass và thêm vào lịch sử với trạng thái hủy vé và giảm đi id chuyến bay đã hủy
                for (auto it = demoPass.begin(); it != demoPass.end(); /* không tăng it ở đây */)
                {
                    if (it->first.getPos() == position && it->second == id)
                    {
                        it->first.setStatus("HUY");
                        hisPass.push_back(*it);
                        idmap[it->second]--;
                        it = demoPass.erase(it); // cập nhật it sau khi xóa
                        break;
                    }
                    else
                    {
                        ++it; // tăng it khi không xóa
                    }
                }

                // cập nhật lại vị trí đã hủy
                for (auto &it : flight)
                {
                    if (it.first.getId() == id)
                    {
                        it.first.setSitPosHuy(position);
                        break;
                    }
                }

                // xóa các chuyến bay có ID phù hợp trong passfly
                for (auto it = passfly.begin(); it != passfly.end(); /* không tăng it ở đây */)
                {
                    if (it->first.getId() == id)
                    {
                        it = passfly.erase(it); // cập nhật it sau khi xóa
                    }
                    else
                    {
                        ++it; // tăng it khi không xóa
                    }
                }
                cout << GREEN;
                cout << "\nDa huy ve thanh cong\n\n";
                cout << RESET;
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
                ticketNum = demoPass.size();
                cout << endl;
                if (demoPass.empty())
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
        for (auto it : hisPass)
        {
            history.push_back(it);
        }
        for (auto it : demoPass)
        {
            passInfo.push_back(it);
        }
        writeDataUser(demoPass, passfly, hisPass, namefile);
    }
    // writeFile(plane, flight, passInfo, voucher, personal, history);
    //  sau khi chạy xong thì ghi thông tin người dùng, lịch sử đặt vé vào các file gốc để khi đăng nhập với tư cách quản lý thì sẽ thấy các thông tin vừa đặt
    return 0;
}