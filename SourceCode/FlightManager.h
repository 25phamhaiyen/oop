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
