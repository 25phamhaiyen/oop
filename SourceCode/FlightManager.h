class FlightManager {
private:
    vector<Flight> flights;

public:
    // Thêm chuyến bay mới
    void addFlight(const Flight& flight) {
        flights.push_back(flight);
        cout << "Flight added successfully!" << endl;
    }

    // Xóa chuyến bay theo ID
    void removeFlight(const string& flightID) {
        for (auto it = flights.begin(); it != flights.end(); ++it) {
            if (it->getFlightID() == flightID) {
                flights.erase(it);
                cout << "Flight removed successfully!" << endl;
                return;
            }
        }
        cout << "Flight not found!" << endl;
    }

    // Cập nhậtt thông tin chuyn bay
    void updateFlight(const string& flightID, const string& newDeparture, const string& newDestination,
                      const string& newDepartureTime, const string& newArrivalTime) {
        for (auto& flight : flights) {
            if (flight.getFlightID() == flightID) {
                flight.setDeparture(newDeparture);
                flight.setDestination(newDestination);
                flight.setDepartureTime(newDepartureTime);
                flight.setArrivalTime(newArrivalTime);
                cout << "Flight updated successfully!" << endl;
                return;
            }
        }
        cout << "Flight not found!" << endl;
    }

    // Tìm kiếm chuyến bay theo ID
    Flight* findFlightByID(const string& flightID) {
        for (auto& flight : flights) {
            if (flight.getFlightID() == flightID) {
                return &flight;
            }
        }
        cout << "Flight not found!" << endl;
        return nullptr;
    }
// Hiển thị menu
    void printMenu() {
        cout << "====== Flight Manager Menu ======" << endl;
        cout << "1. Add Flight" << endl;
        cout << "2. Remove Flight" << endl;
        cout << "3. Update Flight" << endl;
        cout << "4. Find Flight by ID" << endl;
        cout << "5. Display All Flights" << endl;
        cout << "6. Exit" << endl;
        cout << "Select an option: ";
    }

    // Hiển thị tất cả các chuyến bay
    void displayAllFlights() const {
        if (flights.empty()) {
            cout << "No flights available." << endl;
        } else {
            cout << "List of Flights:" << endl;
            for (const auto& flight : flights) {
                flight.displayInfo();
            }
        }
    }
};
