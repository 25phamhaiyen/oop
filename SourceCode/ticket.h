class Ticket {
private:
    string ticketID;
    string flightNumber;
    string passengerPassport;
    string seatNumber;
    string seatClass;
    double price;

public:
    Ticket(string ticketID, string flightNumber, string passengerPassport, 
           string seatNumber, string seatClass);

    double calculatePrice();
    double getPrice() const;
    void displayTicketInfo() const;
};
Ticket::Ticket(string ticketID, string flightNumber, string passengerPassport, 
               string seatNumber, string seatClass)
    : ticketID(ticketID), flightNumber(flightNumber), passengerPassport(passengerPassport), 
      seatNumber(seatNumber), seatClass(seatClass) {
    price = calculatePrice();
}
double Ticket::calculatePrice() {
    double basePrice = 100.0;

    if (seatClass == "First Class") {
        basePrice *= 3.0;
    } else if (seatClass == "Business") {
        basePrice *= 2.0;
    } else if (seatClass == "Economy") {
        basePrice *= 1.0;
    }
    return basePrice;
}

double Ticket::getPrice() const {
    return price;
}
void Ticket::displayTicketInfo() const {
    cout << "Ticket ID: " << ticketID << endl;
    cout << "Flight Number: " << flightNumber << endl;
    cout << "Passenger Passport: " << passengerPassport << endl;
    cout << "Seat Number: " << seatNumber << endl;
    cout << "Seat Class: " << seatClass << endl;
    cout << "Price: $" << price << endl;
}

