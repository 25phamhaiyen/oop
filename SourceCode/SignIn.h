#include<iostream>
#include<conio.h>
#include<fstream>
using namespace std;
class SignIn {
	private:
	    string userName, password;
	public:
	    SignIn();
	    friend bool checkPass(string password);
	    friend void inputPass(string &password);
	    void sign_in(int choice);
	    void sign_up();
	    string getUserName();
	    string getPassword();
};