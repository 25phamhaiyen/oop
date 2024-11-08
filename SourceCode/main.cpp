#include "signin.h"
#include "setup.h"
#include "manager.h"
#include "voucher.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char **argv)
{
    // set up du lieu
    vector<pair<Plane, string>> plane;
    vector<pair<Flight, string>> flight;
    vector<vector<pair<humanInPlane, string>>> personal;
    vector<pair<Passenger, string>> passInfo;
    vector<Voucher> voucher;
    vector<pair<Passenger, string>> history;
    unordered_map<string, int> checkid;
    unordered_map<string, set<pair<humanInPlane, string>>> employ;
    readData(plane, flight, passInfo, voucher, personal, history);
    updateSitPos(flight, passInfo);
    for (auto it : plane)
    {
        checkid[it.second]++;
        checkid[it.first.getAircraftNumber()]++;
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
        }
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
        if (cin.fail() || (choice != '1' && choice != '2')){
            cin.clear(); // Xóa trạng thái lỗi của cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bỏ qua các ký tự còn lại trong bộ đệm
            cout << "\nBan chi co the chon 1 hoac 2. Vui long chon lai\n\n";
        }
        else {
        break; // Thoát khỏi vòng lặp nếu nhập đúng
        }
    } while (true);
    cin.ignore();

    // dang nhap giao dien quan ly

    if (choice == '1')
    {
        system("cls");
        cout << "-----------------Sign In---------------------\n";
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
                if ((stoi(mchoice) < 1 || stoi(mchoice) > 16) && (mchoice != "t" && mchoice != "T"))
                    cout << "\nBan chi duoc nhap gia tri trong khoang tu 1 -> 16 hoac {t,T}. Vui long nhap lai.\n";
            } while ((stoi(mchoice) < 1 || stoi(mchoice) > 16) && (mchoice != "t" && mchoice != "T"));
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
                displayFlight(flight);
                cout << endl;
            }
            else if (mchoice == "3")
            {
                cout << endl;
                displayPassenger(passInfo);
                cout << endl;
            }
            else if (mchoice == "4")
            {
                cout << endl;
                displayHistory(history);
                cout << endl;
            }
            else if (mchoice == "5")
            {
                cout << endl;
                displayHumanInPlane(personal);
                cout << endl;
            }
            else if (mchoice == "6")
            {
                cout << endl;
                displayVoucher(voucher);
                cout << endl;
            }
            else if (mchoice == "7")
            {
                addFlight(plane, flight, personal, checkid, employ);
                cout << endl;
            }
            else if (mchoice == "8")
            {
                cout << endl;
                addVoucher(voucher, checkid);
                cout << endl;
            }
            else if (mchoice == "9")
            {
                cout << endl;
                vector<pair<humanInPlane, string>> v;
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
                    v.push_back(make_pair(hip, "     "));
                    system("cls");
                }
                personal.push_back(v);
            }
            else if (mchoice == "10")
            {
                char a = '1';
                while (a != '2')
                {
                    displayFlight(flight);
                    cout << endl;
                    string idToDelete;
                    do
                    {
                        cout << "\nNhap id chuyen bay can xoa:  ";
                        cin >> idToDelete;
                        if (!checkid[idToDelete])
                        {
                            cout << "\nID chuyen bay khong hop le. Vui long nhap lai.\n";
                        }
                    } while (!checkid[idToDelete]);

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
                    cout << "\nXoa chuyen bay thanh cong!\n\n";
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
            else if (mchoice == "11")
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
                            cout << "\nSo hieu may bay khong hop le. Vui long nhap lai.\n";
                        }
                    } while (!checkid[aircraft]);

                    // xoa may bay
                    for (auto it = plane.begin(); it != plane.end(); ++it)
                    {
                        if (it->first.getAircraftNumber() == aircraft)
                        {
                            plane.erase(it);
                            checkid[aircraft]--;
                            break;
                        }
                    }
                    cout << "\nXoa may bay thanh cong!\n\n";
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
            else if (mchoice == "12")
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
                                break;
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
            else if (mchoice == "13")
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
                            cout << "\nMa khuyen mai khong hop le. Vui long nhap lai.\n";
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
            else if (mchoice == "14")
            {
                char a = '1';
                while (a != '2')
                {
                    displayFlight(flight);
                    cout << endl;
                    string idToDelete;
                    do
                    {
                        cout << "\nNhap id chuyen bay can sua:  ";
                        cin >> idToDelete;
                        if (!checkid[idToDelete])
                        {
                            cout << "\nID chuyen bay khong hop le. Vui long nhap lai.\n";
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
                            cout << "\nChinh sua ID thanh cong!\n\n";
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
                            cout << "\nChinh sua noi den thanh cong!\n\n";
                            break;
                        }
                        case '3':
                        {
                            time_t t = time(nullptr); // L?y th?i gian hi?n t?i
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
                            cout << "\nChinh sua ngay bay thanh cong!\n\n";
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
                            cout << "\nChinh sua gio bay thanh cong!\n\n";
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
                            cout << "\nChinh sua gia ve thanh cong!\n\n";
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
            else if (mchoice == "15")
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
                            cout << "\nSo hieu may bay khong hop le. Vui long nhap lai.\n";
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
                            cout << "2. VietJet Air\n";
                            cout << "3. Bamboo Airways\n";
                            cout << "4. Jetstar Pacific\n\n";
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
                            cout << "\nChinh sua ten hang bay thanh cong!\n\n";
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
                            cout << "\nChinh sua so hieu may bay thanh cong!\n\n";
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
                            cout << "\nChinh sua loai may bay thanh cong!\n\n";
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
                            cout << "\nChinh sua loai may bay thanh cong!\n\n";
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
            else if (mchoice == "16")
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
                            cout << "\nMa khuyen mai khong hop le. Vui long nhap lai.\n";
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
                            cout << "\nChinh sua ma khuyen mai thanh cong!\n\n";
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
                            cout << "\nChinh sua muc giam thanh cong!\n\n";
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
                                    cout << "\nNgay bat dau khuyen mai phai nho hon ngay ket thuc khuyen mai.\n";
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
                            cout << "\nChinh sua ngay bat dau khuyen mai thanh cong!\n\n";
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
                                    cout << "\nNgay ket thuc khuyen mai phai lon hon ngay bat dau khuyen mai.\n";
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
                            cout << "\nChinh sua ngay ket thuc khuyen mai thanh cong!\n\n";
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
            cout << "-----------------Sign In---------------------\n";
            si.sign_in('2');
            cout << "\n---------------------------------------------\n";
        }
        else
        {
            cout << "-----------------Sign Up---------------------\n";
            si.sign_up();
            cout << "\n---------------------------------------------\n";
            system("cls");
            cout << "-----------------Sign In---------------------\n";
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
                    if (ticketNum <= 0)
                        cout << "\nSo luong ve phai > 0. Vui long nhap lai.\n\n";
                } while (ticketNum <= 0);

                int k = ticketNum;
                Passenger pas;
                char yourChoice = '0';
                string idVoucher, area;

                while (k--)
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
                    cout << "Ban hay su dung cac tinh nang ben duoi de tim chuyen bay mong muon\n";
                    while (yourChoice != '8')
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
                            displayFlightUser(flight, area);
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
                            string planeName;
                            cout << "Chon 1 trong cac hang bay:\n\n";
                            cout << "1. VietNam Airlines\n";
                            cout << "2. VietJet Air\n";
                            cout << "3. Bamboo Airways\n";
                            cout << "4. Jetstar Pacific\n\n";
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
                            findWithPlaneName(flight, planeName, area);
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
                                if (eTime <= sTime)
                                    cout << "\nThoi gian sau phai lon hon thoi gian truoc. Vui long nhap lai\n";
                            } while (eTime <= sTime);
                            findWithTime(flight, sTime, eTime, area);
                            break;
                        }
                        case '7':
                        {
                            cout << endl;
                            sortIncreaseTicketPrice(flight);
                            displayFlightUser(flight, area);
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
                        cout << "1. Da tim duoc.\n";
                        cout << "2. Chua tim duoc.\n";
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
                                if (!checkid[id])
                                    cout << "\nID chuyen bay khong co trong danh sach. Vui long nhap lai.\n";
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
                            cout << "Danh sach cho ngoi hang " << pas.getRank() << ":  \n\n";
                            if (pas.getRank() == "Thuong gia")
                                displayChoNgoiThuonggia(flight, id, 1, 15);
                            else
                                displayChoNgoiThuonggia(flight, id, 16, 50);
                            cout << "\n\nLuu y: Nhung vi tri mau hong la da co nguoi dat cho.\n";

                            // khúc này bị lỗi tưc là vẫn chọn được vị trí ng khác đã chọn rồi

                            int pos;
                            do
                            {
                                cout << "\nNhap vi tri ghe ban muon ngoi:  ";
                                cin >> pos;
                                if (f.findSitPos(pos))
                                {
                                    cout << "\nGhe ngoi ban chon da duoc dat truoc do. Vui long chon so ghe khac.\n";
                                    continue;
                                }
                                if (pas.getRank() == "Thuong gia" && (pos < 1 || pos > 15))
                                {
                                    cout << "\nBan chi duoc chon cac vi tri ghe ( 1->15 ). Vui long chon lai.\n";
                                }
                                if (pas.getRank() == "Pho thong " && (pos < 16 || pos > 50))
                                {
                                    cout << "\nBan chi duoc chon cac vi tri ghe ( 16->50 ). Vui long chon lai.\n";
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
                    }
                }
                // hỏi khách hàng về voucher
                char a;
                do
                {
                    cout << "Quy khach co ma Voucher giam gia khong?( neu co thi nhap ma Voucher, neu khong thi go phim 'e' ):  ";
                    cin >> idVoucher;
                    if (idVoucher == "e" || idVoucher == "E")
                        break;
                    else if (checkid[idVoucher] == 0)
                    {
                        cout << "\nQuy khach da nhap sai ma khuyen mai. Quy khach co muon tiep tuc khong?\n";
                        cout << "1. Co.\n";
                        cout << "2. Khong.\n";
                        do
                        {
                            cout << "\nNhap lua chon cua ban:  ";
                            cin >> a;
                            if (a != '1' && a != '2')
                                cout << "\nBan chi duoc chon 1 hoac 2. Vui long nhap lai.\n";
                        } while (a != '1' && a != '2');
                        if (a == '2')
                            break;
                    }
                } while (checkid[idVoucher] == 0 && idVoucher != "e" && idVoucher != "E" || a == '1');
                system("cls");
                // xác nhận thanh toán
                char acept;
                cout << "Moi quy khach xac nhan:\n";
                cout << "1. Xac nhan thanh toan.\n";
                cout << "2. Huy ve.\n";
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
                displayFlight(flight);
                cout << endl;
                break;
            }
            case '3':
            {
                if (demoPass.empty())
                {
                    cout << "\nKhong the huy chuyen bay vi quy khach chua dat chuyen bay nao.\n\n";
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
                cout << PINK << "+----------------------------------------------------------------+" << endl;
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
                    if (mp[position] == 0)
                        cout << "\nVi tri khong hop le. Vui long nhap lai\n\n";
                } while (mp[position] == 0);
                // xóa thông tin người dùng trong vector demoPass và thêm vào lịch sử với trạng thái hủy vé và giảm đi id chuyến bay đã hủy
                for (auto it = demoPass.begin(); it != demoPass.end(); it++)
                {
                    if (it->first.getPos() == position && it->second == id)
                    {
                        it->first.setStatus("HUY");
                        hisPass.push_back(make_pair(it->first, it->second));
                        demoPass.erase(it);
                        idmap[it->second]--;
                        break;
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
                cout << "\nDa huy ve thanh cong\n\n";
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
    }
    // writeFile(plane, flight, passInfo, voucher, personal, history);
    //  sau khi chạy xong thì ghi thông tin người dùng, lịch sử đặt vé vào các file gốc để khi đăng nhập với tư cách quản lý thì sẽ thấy các thông tin vừa đặt
    return 0;
}