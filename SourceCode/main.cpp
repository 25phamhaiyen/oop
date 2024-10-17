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
	displayPlane(plane);
	displayVoucher(voucher);
	return 0;
}