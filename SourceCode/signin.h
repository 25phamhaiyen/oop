#pragma once
#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include "date_time.h"
using namespace std;
class SignIn
{
private:
	string userName, password; // tên tài khoản và mật khẩu
public:
	SignIn(); // hàm khởi tạo
	// hàm kiểm tra thông tin đăng nhập có hợp lệ
	friend int isValidAccount(string username, string password, char choice);
	// hàm kiểm tra tên tài khoản có bị trùng không
	friend bool isValidUserName(string username);
	// hàm kiểm tra mật khẩu
	friend bool checkPass(string password);
	// hàm nhập mật khẩu
	friend void inputPass(string &password);
	// hàm đăng nhập
	bool sign_in(char choice);
	// hàm đăng ký
	void sign_up();
	// hàm lấy giá trị username và pass
	string getUserName();
	string getPassword();
	bool forgotPassword();
};

SignIn::SignIn()
{
	this->userName = this->password = "";
}
bool checkPass(string password)
{
	bool isUp = false;
	bool isLow = false;
	bool isNum = false;
	for (char c : password)
	{
		// check chu hoa
		if (isupper(c))
			isUp = true;
		// check chu thuong
		if (islower(c))
			isLow = true;
		// check chu so
		if (isdigit(c))
			isNum = true;
		if (isUp && isLow && isNum)
			return true;
	}
	return false;
}
void inputPass(string &password)
{
	char c;
	bool isMasked = true; // Biến trạng thái để theo dõi việc ẩn/hiện mật khẩu
	while (true)
	{
		c = _getch();
		// enter
		if (c == 13)
			break;
		// tab
		else if (c == 9)
		{
			isMasked = !isMasked;
			// Xóa toàn bộ dòng trước khi in lại
			cout << "\rNhap mat khau: "; // Quay về đầu dòng
			for (size_t i = 0; i < password.size(); i++)
			{
				// In lại mật khẩu với dấu * hoặc ký tự thực tế tùy theo trạng thái
				if (isMasked)
					cout << '*';
				else
					cout << password[i];
			}
		}
		// Khi nhấn Backspace (phím ASCII 8)
		else if (c == 8)
		{
			if (!password.empty())
			{
				password.pop_back();
				cout << "\b \b"; // Xóa ký tự cuối cùng
			}
		}
		// Các ký tự khác
		else
		{
			password += c;
			if (isMasked)
				cout << '*';
			else
				cout << c;
		}
	}
}
int isValidAccount(string username, string password, char choice) {
    ifstream file;
    if (choice == '1')
        file.open("../Database/managerAccount.txt");
    else
        file.open("../Database/passengerSignInAccount.txt");

    string line;
    bool userExists = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string user, pass;
        getline(ss, user, ',');
        getline(ss, pass, ',');

        // Kiểm tra tài khoản có tồn tại không
        if (user == username) {
            userExists = true;
            // Kiểm tra nếu mật khẩu trùng khớp
            if (pass == password) {
                file.close();
                return 1; // Đăng nhập thành công
            }
        }
    }

    file.close();
    return userExists ? -1 : 0; // -1: Sai mật khẩu, 0: Tài khoản không tồn tại
}

bool isValidUserName(string username)
{
	ifstream file("../Database/passengerSignInAccount.txt");
	string line;
	while (getline(file, line))
	{
		stringstream ss(line);
		string user, pass;
		getline(ss, user, ',');
		getline(ss, pass, ',');
		if (user == username)
		{
			file.close();
			return true;
		}
	}
	file.close();
	return false;
}
void SignIn::sign_up()
{
	string userName, password = "", repeatPass = "",  securityQuestion, securityAnswer;


	cin.ignore();
	do
	{
		cout << "\nNhap tai khoan:  ";
		getline(cin, userName);
		if (userName.size() < 8 || userName.size() > 20)
		{
			cout << RED << "\nTen tai khoan phai co do dai tu 8 den 20 ky tu. Vui long nhap lai.\n"
				 << RESET;
			continue;
		}
		if (isValidUserName(userName))
			cout << RED << "\nTen tai khoan da ton tai. Vui long nhap lai.\n"
				 << RESET;
	} while (isValidUserName(userName) || userName.size() < 8 || userName.size() > 20);

	// Nhap pass;
	do
	{
		cout << "Nhap mat khau:  ";
		inputPass(password);
		if (password.size() < 8 || password.size() > 20)
		{
			cout << RED << "\n\nMat khau phai co do dai tu 8 den 20 ky tu. Vui long nhap lai.\n\n"
				 << RESET;
			password = "";
			continue;
		}
		if (checkPass(password) == false)
		{
			cout << RED << "\n\nMat khau phai bao gom chu HOA, chu THUONG, chu SO. Vui long nhap lai\n\n"
				 << RESET;
			password = "";
		}
	} while (checkPass(password) == false || password.size() < 8 || password.size() > 20);

	// Nhap lai pass;
	do
	{
		cout << "\nNhap lai mat khau:  ";
		inputPass(repeatPass);
		if (repeatPass != password)
		{
			cout << RED << "\n\nMat khau khong chinh xac. Vui long nhap lai\n"
				 << RESET;
			repeatPass = "";
		}
	} while (repeatPass != password);

	// Chọn câu hỏi bảo mật
    cout << "\n\nChon cau hoi bao mat:\n";
    cout << "1. Ten thu cung cua ban?\n";
    cout << "2. Ten truong tieu hoc cua ban?\n";
    cout << "3. Mon an yeu thich cua ban?\n";
    int questionChoice;
    do {
        cout << "\nNhap lua chon (1-3): ";
        cin >> questionChoice;
        if (questionChoice < 1 || questionChoice > 3)
            cout << RED << "Lua chon khong hop le. Vui long chon lai.\n" << RESET;
    } while (questionChoice < 1 || questionChoice > 3);

    switch (questionChoice) {
        case 1: securityQuestion = "Ten thu cung cua ban?"; break;
        case 2: securityQuestion = "Ten truong tieu hoc cua ban?"; break;
        case 3: securityQuestion = "Mon an yeu thich cua ban?"; break;
    }
    cout << "Nhap cau tra loi cho cau hoi bao mat: ";
    cin.ignore();
    getline(cin, securityAnswer);

    // Lưu tài khoản vào file
    ofstream fileSignIn("../Database/passengerSignInAccount.txt", ios::app);
    fileSignIn << userName << ',' << password << ',' << securityQuestion << ',' << securityAnswer << '\n';
    fileSignIn.close();

    cout << GREEN << "\nDang ky thanh cong!\n" << RESET;
}

// bo sung tinh nang khoi phuc mat khau khi bi quen
bool SignIn::sign_in(char choice) {
    int count = 0;
    bool isAuthenticated = false;

    do {
        count++;
        if (count == 4) {
            cout << RED << "\nDa nhap sai qua 3 lan. Vui long thoat ra dang nhap lai.\n" << RESET;
            return false;
        }

        //if (count > 1) cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
        cout << "\nNhap tai khoan:  ";
        getline(cin, this->userName);
        cout << "Nhap mat khau:  ";
        this->password = "";
        inputPass(this->password);

        int result = isValidAccount(this->userName, this->password, choice);
        if (result == 1) {
            isAuthenticated = true;
        } else if (result == -1) {
            cout << RED << "\nSai mat khau. Vui long nhap lai.\n" << RESET;
            if(choice=='2')
			{// Hỏi người dùng có muốn khôi phục mật khẩu không
				char recoveryChoice;
				do {
                    cout << "\nBan co muon khoi phuc mat khau? (y/n): ";
                    cin >> recoveryChoice;
                    if( recoveryChoice != 'y' && recoveryChoice != 'n' )
                        cout << "\n\nBan chi co the chon y hoac n. Vui long nhap lai.\n";
				}while( recoveryChoice != 'y' && recoveryChoice != 'n' );
				if (recoveryChoice == 'y' || recoveryChoice == 'Y') {
					// Gọi hàm khôi phục mật khẩu
					if(forgotPassword()==true){
						cout << GREEN << "\nMat khau da duoc thay doi thanh cong!\n" << RESET;
						return true;
					}

				}
			}
        } else if (result == 0) {
            cout << RED << "\n\nTai khoan khong ton tai. Vui long nhap lai.\n" << RESET;
        }

    } while (!isAuthenticated);

    cout << GREEN << "\nDang nhap thanh cong!\n" << RESET;
	return true;
}

string SignIn::getPassword()
{
	return this->password;
}
string SignIn::getUserName()
{
	return this->userName;
}

// phuong thuc quen mat khau
bool SignIn::forgotPassword() {
    string username, securityQuestion, securityAnswer, storedAnswer;

    cout << "\nNhap tai khoan de khoi phuc mat khau: ";
    cin.ignore(); // Đảm bảo không có ký tự thừa từ lần nhập trước
    getline(cin, username);

    ifstream file("../Database/passengerSignInAccount.txt");
    string line, user, pass, question, answer;

    bool found = false;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, user, ',');
        getline(ss, pass, ',');
        getline(ss, question, ',');
        getline(ss, answer, ',');

        if (user == username) {
            securityQuestion = question;
            storedAnswer = answer;
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << RED << "\nTai khoan khong ton tai. Thu lai sau.\n" << RESET;
        return false;
    }

    cout << "\nCau hoi bao mat: " << securityQuestion << '\n';
    cout << "Nhap cau tra loi: ";
    getline(cin, securityAnswer);

    if (securityAnswer != storedAnswer) {
        cout << RED << "\nCau tra loi khong chinh xac. Thu lai sau.\n" << RESET;
        return false;
    }
    cout << GREEN << "\nCau tra loi dung. Hay tao mat khau moi.\n" << RESET;


    // dat lai mat khau
    string newPassword, repeatPassword;
    do
	{
		cout << "Nhap mat khau moi:  ";
		inputPass(newPassword);
		if (newPassword.size() < 8 || newPassword.size() > 20)
		{
			cout << RED << "\n\nMat khau phai co do dai tu 8 den 20 ky tu. Vui long nhap lai.\n\n" << RESET;
			newPassword = "";
			continue;
		}
		if (checkPass(newPassword) == false)
		{
			cout << RED << "\n\nMat khau phai bao gom chu HOA, chu THUONG, chu SO. Vui long nhap lai\n\n" << RESET;
			newPassword = "";
		}
	} while (checkPass(newPassword) == false || newPassword.size() < 8 || newPassword.size() > 20);

	// Nhap lai pass;
	do
	{
		cout << "\nNhap lai mat khau:  ";
		inputPass(repeatPassword);
		if (repeatPassword != newPassword)
		{
			cout << RED << "\n\nMat khau khong chinh xac. Vui long nhap lai\n" << RESET;
			repeatPassword = "";
		}
	} while (repeatPassword != newPassword);


    // Cập nhật mật khẩu
    ifstream fileIn("../Database/passengerSignInAccount.txt");
    ofstream fileOut("../Database/temp.txt");

    while (getline(fileIn, line)) {
        stringstream ss(line);
        getline(ss, user, ',');
        getline(ss, pass, ',');
        getline(ss, question, ',');
        getline(ss, answer, ',');

        if (user == username) {
            fileOut << user << ',' << newPassword << ',' << question << ',' << answer << '\n';
        } else {
            fileOut << line << '\n';
        }
    }

    fileIn.close();
    fileOut.close();
    remove("../Database/passengerSignInAccount.txt");
    rename("../Database/temp.txt", "../Database/passengerSignInAccount.txt");


	return true;
}
