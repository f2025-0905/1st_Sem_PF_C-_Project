#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Global Variables
int rowsFirstClass, rowsBusiness, rowsEconomy;

// Structure to hold Passenger info
struct passengerData {
    string name;
    string gender;
    long long cnic;
    int ticketPrice;
};

// Structure to hold Flight info
struct flightData {
    string flightName;
    string flightType; // Local or International
    string from;
    string to;

    int rowsFirstClass;
    int rowsBusiness;
    int rowsEconomy;
    int colsFirstClass;
    int colsBusiness;
    int colsEconomy;

    vector<vector<char>> seats; // 'F' = free, 'R' = reserved
    vector<vector<passengerData>> passengerInfo;

    string departureTime;
    string landingTime;

    int revenue;
};

// Container for all flights
vector<flightData> flights;

// Function to add a new flight
void addFlight() {
    flightData newFlight;

    cout << "\nEnter Flight Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newFlight.flightName);

    cout << "Enter Flight Type (Local/International): ";
    getline(cin, newFlight.flightType);

    cout << "From (Origin): ";
    getline(cin, newFlight.from);
    cout << "To (Destination): ";
    getline(cin, newFlight.to);

    cout << "Enter number of rows for First Class: ";
    cin >> newFlight.rowsFirstClass;
    cout << "Enter number of seats per row for First Class: ";
    cin >> newFlight.colsFirstClass;

    cout << "Enter number of rows for Business Class: ";
    cin >> newFlight.rowsBusiness;
    cout << "Enter number of seats per row for Business Class: ";
    cin >> newFlight.colsBusiness;

    cout << "Enter number of rows for Economy Class: ";
    cin >> newFlight.rowsEconomy;
    cout << "Enter number of seats per row for Economy Class: ";
    cin >> newFlight.colsEconomy;

    cin.ignore(); // Clear input buffer
    cout << "Enter Departure Time (HH:MM): ";
    getline(cin, newFlight.departureTime);
    cout << "Enter Landing Time (HH:MM): ";
    getline(cin, newFlight.landingTime);

    int totalRows = newFlight.rowsFirstClass + newFlight.rowsBusiness + newFlight.rowsEconomy;
    int maxCols = max(newFlight.colsFirstClass, max(newFlight.colsBusiness, newFlight.colsEconomy));

    // Initialize seats and passenger info
    newFlight.seats = vector<vector<char>>(totalRows, vector<char>(maxCols, 'F'));
    newFlight.passengerInfo = vector<vector<passengerData>>(totalRows, vector<passengerData>(maxCols));
    newFlight.revenue = 0;

    flights.push_back(newFlight);
    cout << "\nFlight added successfully!\n";
}

// Function to display seats of a flight with class labels
void displayFlightSeats(flightData &flight) {
    cout << "\nSeat Layout for Flight: " << flight.flightName
         << " | Type: " << flight.flightType
         << " | From: " << flight.from
         << " | To: " << flight.to << endl;

    int rowIndex = 0;

    // First Class
    for (int i = 0; i < flight.rowsFirstClass; i++, rowIndex++) {
        cout << "First Class Row " << i << ": ";
        for (int j = 0; j < flight.colsFirstClass; j++)
            cout << "(" << rowIndex << "-" << j << " " << flight.seats[rowIndex][j] << ") ";
        cout << endl;
    }

    // Business Class
    for (int i = 0; i < flight.rowsBusiness; i++, rowIndex++) {
        cout << "Business Class Row " << i << ": ";
        for (int j = 0; j < flight.colsBusiness; j++)
            cout << "(" << rowIndex << "-" << j << " " << flight.seats[rowIndex][j] << ") ";
        cout << endl;
    }

    // Economy Class
    for (int i = 0; i < flight.rowsEconomy; i++, rowIndex++) {
        cout << "Economy Class Row " << i << ": ";
        for (int j = 0; j < flight.colsEconomy; j++)
            cout << "(" << rowIndex << "-" << j << " " << flight.seats[rowIndex][j] << ") ";
        cout << endl;
    }
}

// Function to determine ticket price by row
int getTicketPrice(flightData &flight, int rowIn) {
    int localFirst = 25000;
    int localBusiness = 20000;
    int localEconomy = 15000;

    if (flight.flightType == "International") {
        localFirst *= 3;
        localBusiness *= 3;
        localEconomy *= 3;
    }

    if (rowIn < flight.rowsFirstClass)
        return localFirst;
    else if (rowIn < flight.rowsFirstClass + flight.rowsBusiness)
        return localBusiness;
    else
        return localEconomy;
}

// Function to reserve a seat
void reserveSeat(flightData &flight) {
    cout << "\nSeat Prices:\n";
    int priceFirst = (flight.flightType == "Local" || flight.flightType == "local") ? 25000 : 75000;
    int priceBusiness = (flight.flightType == "Local" || flight.flightType == "local") ? 20000 : 60000;
    int priceEconomy = (flight.flightType == "Local" || flight.flightType == "local") ? 15000 : 45000;

    cout << "First Class: " << priceFirst << " | Business: " << priceBusiness << " | Economy: " << priceEconomy << endl;

    int row, col;
    cout << "Enter row and column to reserve: ";
    cin >> row >> col;

    while (row < 0 || col < 0 || row >= flight.seats.size() || col >= flight.seats[0].size() || flight.seats[row][col] == 'R') {
        cout << "Invalid or already reserved! Enter again: ";
        cin >> row >> col;
    }

    flight.seats[row][col] = 'R';
    int price = getTicketPrice(flight, row);
    flight.passengerInfo[row][col].ticketPrice = price;
    flight.revenue += price;

    cout << "Seat reserved! Ticket Price: " << price << endl;
}

// Function to free a seat
void freeSeat(flightData &flight) {
    int row, col;
    cout << "Enter row and column to free: ";
    cin >> row >> col;

    while (row < 0 || col < 0 || row >= flight.seats.size() || col >= flight.seats[0].size() || flight.seats[row][col] == 'F') {
        cout << "Invalid or already free! Enter again: ";
        cin >> row >> col;
    }

    flight.seats[row][col] = 'F';
    int price = flight.passengerInfo[row][col].ticketPrice;
    flight.passengerInfo[row][col] = passengerData{}; // Remove passenger info
    flight.revenue -= price;

    cout << "Seat freed successfully!\n";
}

// Function to manage a flight
void manageFlight() {
    if (flights.empty()) {
        cout << "\nNo flights available. Add flights first!\n";
        return;
    }

    cout << "\nAvailable Flights:\n";
    for (int i = 0; i < flights.size(); i++)
        cout << i + 1 << ". " << flights[i].flightName << " | Type: " << flights[i].flightType
             << " | From: " << flights[i].from << " | To: " << flights[i].to
             << " | Revenue: " << flights[i].revenue << endl;

    int choice;
    cout << "Select Flight to manage: ";
    cin >> choice;
    choice--;

    if (choice < 0 || choice >= flights.size()) {
        cout << "Invalid choice!\n";
        return;
    }

    bool flightMenu = true;
    while (flightMenu) {
        displayFlightSeats(flights[choice]);
        cout << "\n1. Reserve Seat\n2. Free Seat\n0. Back\nEnter: ";
        int op;
        cin >> op;

        switch (op) {
            case 1: reserveSeat(flights[choice]); break;
            case 2: freeSeat(flights[choice]); break;
            case 0: flightMenu = false; break;
            default: cout << "Invalid option!\n";
        }
    }
}

// Main Function
int main() {
    bool runProgram = true;
    string adminUsername = "admin";
    string adminPassword = "123";

    // Login
    string username, password;
    cout << "AirlineAdmin Login\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username != adminUsername || password != adminPassword) {
        cout << "Invalid credentials! Exiting...\n";
        return 0;
    }

    while (runProgram) {
        cout << "\n--- AirlineAdmin Menu ---\n";
        cout << "1. Add Flight\n";
        cout << "2. Manage Flight\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: addFlight(); break;
            case 2: manageFlight(); break;
            case 0: runProgram = false; break;
            default: cout << "Invalid option!\n";
        }
    }

    cout << "Exiting Airline Management System. Goodbye!\n";
    return 0;
}
