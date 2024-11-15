#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "flight.h"

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

    // Hàm tìm kiếm chuyến bay theo địa điểm xuất phát và điểm đến
    vector<Flight> searchFlights(const string &departure, const string &destination);

    // Thống kê tổng số chuyến bay
    int getTotalFlights() const;

    // Tìm chuyến bay theo ngày
    vector<Flight> findFlightsByDate(const Date &date) const;

    // Hiển thị tất cả các chuyến bay trong khoảng thời gian cụ thể
    void displayFlightsByDateRange(const Date &startDate, const Date &endDate) const;

    // Kiểm tra xem mã chuyến bay có tồn tại hay không
    bool flightExists(const string &id) const;

    // Tính tổng doanh thu từ tất cả các chuyến bay
    double calculateTotalRevenue() const;
};

// Tìm kiếm chuyến bay theo địa điểm xuất phát và điểm đến
vector<Flight> FlightManager::searchFlights(const string &departure, const string &destination) {
    vector<Flight> results;
    for (const auto &flight : flights) {
        if (flight.getDepartureLocation() == departure && flight.getDestination() == destination) {
            results.push_back(flight);
        }
    }
    return results;
}

// Tìm chuyến bay theo ngày
vector<Flight> FlightManager::findFlightsByDate(const Date &date) const {
    vector<Flight> results;
    for (const auto &flight : flights) {
        if (flight.getFlightDate() == date) {
            results.push_back(flight);
        }
    }
    return results;
}

// Hiển thị tất cả các chuyến bay trong khoảng thời gian cụ thể
void FlightManager::displayFlightsByDateRange(const Date &startDate, const Date &endDate) const {
    for (const auto &flight : flights) {
        if (flight.getFlightDate() >= startDate && flight.getFlightDate() <= endDate) {
            cout << flight << endl;
        }
    }
}

// Kiểm tra xem mã chuyến bay có tồn tại hay không
bool FlightManager::flightExists(const string &id) const {
    for (const auto &flight : flights) {
        if (flight.getId() == id) {
            return true;
        }
    }
    return false;
}

// Tính tổng doanh thu từ tất cả các chuyến bay
double FlightManager::calculateTotalRevenue() const {
    double totalRevenue = 0;
    for (const auto &flight : flights) {
        totalRevenue += flight.getSitNum() * flight.getPopTicketPrice(); // Vé hạng thường
        totalRevenue += flight.getSitNum() * flight.getVipTicketPrice(); // Vé hạng thương gia
    }
    return totalRevenue;
}
