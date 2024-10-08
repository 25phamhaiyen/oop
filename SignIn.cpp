#include<iostream>
#include<string.h>
#include<conio.h>
#include<fstream>
using namespace std;
class SignIn {
	private:
		string userName, password;
	public:
		SignIn();
		friend bool checkPass( string password );
		friend void inputPass( string &password );
		void sign_in( int choice );
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
void SignIn::sign_up(){
	ofstream file("passengerSignUpAccount.txt");
	string userName, password = "", repeatPass = "";
	
	fflush(stdin);
	cout << "\nUserName:  ";  getline(cin, userName);
	
	// Nhap pass;
	do {
		cout << "Password:  ";  inputPass(password);
		if( password.size() < 8 ){
			cout << "\n\nWeak password ( password must more than 8 character ) please re-enter\n\n";
			continue;
		}
		if( checkPass(password) == false )
			cout << "\n\nPassword is incorrect ( phai co chu HOA, chu THUONG, chu SO ), please re-enter\n\n";
	}while( checkPass(password) == false || password.size() < 8 );
	
	// Nhap lai pass;
	do {
		fflush(stdin);
		cout << "\nRe-enter password:  ";
		inputPass(repeatPass);
		if( repeatPass != password )
			cout << "\n\nPassword is incorrect, please re-enter\n";
	}while( repeatPass != password );
	cout << "\nSign Up Success\n\n";
	
	// ghi file
	file << userName << endl;
	file << password;
	file.close();
}
void SignIn::sign_in( int choice ){
	ifstream file;
	if( choice == 1 )
		file.open("managerAccount.txt");
	else if( choice == 2 )
		file.open("passengerSignInAccount.txt");
	else 
		file.open("passengerSignUpAccount.txt");
	string userName, password;
	string userTemp, passTemp;
	int count = 0;
	
	// doc file
	file >> userTemp;
	cout << endl;
	file >> passTemp;
	
	// Nhap userName;
	do {
		count++;
		if( count > 3 ){
			cout << "\n\nEntered more than 3 times. Please wait a few minutes and try again\n";
			return;
		}		
		cout << "UserName:  ";  
		getline(cin, this->userName);
		if( this->userName != userTemp )
			cout << "\nUserName is incorrect, please re-enter\n\n";
	}while( this->userName != userTemp );
	count = 0;
	// nhap password;
	do {
		count++;
		cout << "Password:  ";  
		this->password = "";
		inputPass(this->password);
		if( !checkPass(this->password) && count == 3 ){
			cout << "\n\nEntered more than 3 times. Please try again\n";
			return;
		}
		if( !checkPass(this->password) )
			cout << "\n\nPassword is incorrect, please re-enter\n\n";
	}while( !checkPass(this->password) || this->password.size() < 8 );
	cout << "\nLogged in successfully\n";	
}
string SignIn::getPassword(){
	return this->password;
}
string SignIn::getUserName(){
	return this->userName;
}
int main(){
	SignIn si;
	cout << "Ban dang nhap voi tu cach nao?" << endl;
	cout << "1.Quan ly \n2.Khach hang" << endl << endl;
	int choice;
	do {
		cout << "Enter your choice:  ";
		cin >> choice;
		if( choice != 1 && choice != 2 )
			cout << "\nMust enter 1 or 2. Please re-enter\n\n";
	}while( choice != 1 && choice != 2 );
	cin.ignore();
	if( choice == 1 ){
		cout << "\n-----------------Sign In---------------------\n";
		si.sign_in(1);
		cout << "\n---------------------------------------------\n";
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
			si.sign_in(1);
			cout << "\n---------------------------------------------\n";
		}
		else {
			cout << "\n-----------------Sign Up---------------------\n";
			si.sign_up();
			cout << "\n---------------------------------------------\n";
			
			cout << "\n-----------------Sign In---------------------\n";
			si.sign_in(3);
			cout << "\n---------------------------------------------\n";
		}
	}
	return 0;
}