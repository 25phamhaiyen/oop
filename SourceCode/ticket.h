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
