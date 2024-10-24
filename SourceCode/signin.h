#pragma once
#include<iostream>
#include<conio.h>
#include<fstream>
#include<sstream>
using namespace std;
class SignIn {
	private:
	    string userName, password;
	public:
	    SignIn();
	    friend bool isValidAccount( string username, string password, char choice ); 
	    friend bool isValidUserName( string username); 
	    friend bool checkPass(string password);
	    friend void inputPass(string &password);
	    void sign_in(char choice);
	    void sign_up();
	    string getUserName();
	    string getPassword();
};


SignIn::SignIn(){
	this->userName = this->password = "";
}
bool checkPass( string password ){
	bool isUp = false;
    bool isLow = false;
    bool isNum = false;
    for( char c : password ) {
    	// check chu hoa
        if( isupper(c) )
            isUp = true;
        // check chu thuong
        if( islower(c) )
            isLow = true;
        // check chu so
        if( isdigit(c) )
            isNum = true;
        if( isUp && isLow && isNum )
            return true;
    }
    return false;
}
void inputPass( string &password ){
	char c;
	while(1){
		c = _getch(); 
		// check enter
        if( c == 13 ) 
            break; 
    	// check backspace;
		else if( c == 8 ) { 
            if( !password.empty() ) {
                password.pop_back(); 
                cout << "\b \b"; 
            }
        } 
		else {
            password += c;
            cout << '*'; 
        }
    }
}
bool isValidAccount( string username, string password, char choice ){
	ifstream file;
	if( choice == '1')
		file.open("C:\\Users\\Nguyen\\OneDrive\\Lap trinh\\C++\\OOP\\BTL\\Database\\managerAccount.txt");
	else
		file.open("C:\\Users\\Nguyen\\OneDrive\\Lap trinh\\C++\\OOP\\BTL\\Database\\passengerSignInAccount.txt");
    string line;
    while( getline(file, line) ) {
        stringstream ss(line);
        string user, pass;
        getline(ss, user, ',');
		getline(ss, pass, ',');
		if( user == username && pass == password )
			return true;
    }
    return false;
}
bool isValidUserName( string username ){
	ifstream file("C:\\Users\\Nguyen\\OneDrive\\Lap trinh\\C++\\OOP\\BTL\\Database\\passengerSignInAccount.txt");
    string line;
    while( getline(file, line) ) {
        stringstream ss(line);
        string user, pass;
        getline(ss, user, ',');
		getline(ss, pass, ',');
		if( user == username ){
			file.close();
			return true;
		}
    }
    file.close();
    return false;
}
void SignIn::sign_up(){
	string userName, password = "", repeatPass = "";
	
	fflush(stdin);
	do{
		cout << "\nNhap tai khoan:  ";  getline(cin, userName);
		if( isValidUserName( userName) )
			cout << "\nTen tai khoan da ton tai. Vui long nhap lai.\n";
	}while( isValidUserName( userName) );
	
	// Nhap pass;
	do {
		cout << "Nhap mat khau:  ";  inputPass(password);
		if( password.size() < 8 ){
			cout << "\n\nMat khau phai co hon 8 ki tu. Vui long nhap lai.\n\n";
			password = "";
			continue;
		}
		if( checkPass(password) == false ){
			cout << "\n\nMat khau phai co chu HOA, chu THUONG, chu SO ). Vui long nhap lai\n\n";
			password = "";
		}
	}while( checkPass(password) == false || password.size() < 8 );
	
	// Nhap lai pass;
	do {
		fflush(stdin);
		cout << "\nNhap lai mat khau:  ";
		inputPass(repeatPass);
		if( repeatPass != password ){
			cout << "\n\nMat khau khong chinh xac. Vui long nhap lai\n";
			repeatPass = "";
		}
	}while( repeatPass != password );
	cout << "\nDang ky thanh cong!\n\n";
	
	// ghi file
	ofstream fileSignIn("C:\\Users\\Nguyen\\OneDrive\\Lap trinh\\C++\\OOP\\BTL\\Database\\passengerSignInAccount.txt", ios::app);
	fileSignIn << userName << ',' << password << endl;
	fileSignIn.close();
}
void SignIn::sign_in( char choice ){
	int count = 0;
	do {
		// nhap username
		count++;
		if( count == 4 ){
			cout << "\nDa nhap sai qua 3 lan. Vui long thoat ra dang nhap lai.\n";
			return;
		}	
		cout << "\nNhap tai khoan:  ";  
		getline(cin, this->userName);
		cout << "\nNhap mat khau:  ";
		this->password = "";
		inputPass(this->password);
		if( !isValidAccount(this->userName, this->password, choice) )
			cout << "\nTai khoan hoac mat khau sai. Vui long nhap lai.\n";
	}while( !isValidAccount(this->userName, this->password, choice) );
	cout << "\nDang nhap thanh cong!\n";	
}
string SignIn::getPassword(){
	return this->password;
}
string SignIn::getUserName(){
	return this->userName;
}