#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include "airline.h"

using namespace std;

struct passengerData {
    string name;
    string gender;
    long long cnic = 0;
    int ticketPrice = 0;
};

struct flightData {
    string flightName;
    string flightType;
    string from;
    string to;

    int rowsFirstClass;
    int rowsBusiness;
    int rowsEconomy;
    int colsFirstClass;
    int colsBusiness;
    int colsEconomy;

    vector<vector<char>> seats;
    vector<vector<passengerData>> passengerInfo;

    string departureTime;
    string landingTime;

    int revenue = 0;
};

vector<flightData> flights;

void saveToFile() {
    ofstream file("./airline_data.txt");

    file << flights.size() << endl;

    for (auto &f : flights) {
        file << f.flightName << endl;
        file << f.flightType << endl;
        file << f.from << endl;
        file << f.to << endl;

        file << f.rowsFirstClass << " "
             << f.rowsBusiness << " "
             << f.rowsEconomy << " "
             << f.colsFirstClass << " "
             << f.colsBusiness << " "
             << f.colsEconomy << endl;

        file << f.departureTime << endl;
        file << f.landingTime << endl;
        file << f.revenue << endl;

        int totalRows = f.seats.size();
        int totalCols = f.seats[0].size();

        file << totalRows << " " << totalCols << endl;

        for (int i = 0; i < totalRows; i++) {
            for (int j = 0; j < totalCols; j++) {
                file << f.seats[i][j] << endl;
                file << f.passengerInfo[i][j].name << endl;
                file << f.passengerInfo[i][j].gender << endl;
                file << f.passengerInfo[i][j].cnic << endl;
                file << f.passengerInfo[i][j].ticketPrice << endl;
            }
        }
    }
    file.close();
}

void loadFromFile() {
    ifstream file("./airline_data.txt");
    if (!file) return;

    flights.clear();

    int flightCount;
    file >> flightCount;
    file.ignore();

    for (int k = 0; k < flightCount; k++) {
        flightData f;

        getline(file, f.flightName);
        getline(file, f.flightType);
        getline(file, f.from);
        getline(file, f.to);

        file >> f.rowsFirstClass
             >> f.rowsBusiness
             >> f.rowsEconomy
             >> f.colsFirstClass
             >> f.colsBusiness
             >> f.colsEconomy;
        file.ignore();

        getline(file, f.departureTime);
        getline(file, f.landingTime);
        file >> f.revenue;

        int totalRows, totalCols;
        file >> totalRows >> totalCols;
        file.ignore();

        f.seats = vector<vector<char>>(totalRows, vector<char>(totalCols));
        f.passengerInfo = vector<vector<passengerData>>(totalRows, vector<passengerData>(totalCols));

        for (int i = 0; i < totalRows; i++) {
            for (int j = 0; j < totalCols; j++) {
                file >> f.seats[i][j];
                file.ignore();

                getline(file, f.passengerInfo[i][j].name);
                getline(file, f.passengerInfo[i][j].gender);
                file >> f.passengerInfo[i][j].cnic;
                file >> f.passengerInfo[i][j].ticketPrice;
                file.ignore();
            }
        }
        flights.push_back(f);
    }
    file.close();
}


void addFlight() {
    system("cls");
    flightData f;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Flight Name: ";
    getline(cin, f.flightName);

    cout << "Enter Flight Type (Local/International): ";
    getline(cin, f.flightType);

    cout << "From: ";
    getline(cin, f.from);

    cout << "To: ";
    getline(cin, f.to);

    cout << "Rows First Class: ";
    cin >> f.rowsFirstClass;
    cout << "Seats per row First Class: ";
    cin >> f.colsFirstClass;

    cout << "Rows Business Class: ";
    cin >> f.rowsBusiness;
    cout << "Seats per row Business Class: ";
    cin >> f.colsBusiness;

    cout << "Rows Economy Class: ";
    cin >> f.rowsEconomy;
    cout << "Seats per row Economy Class: ";
    cin >> f.colsEconomy;

    cin.ignore();
    cout << "Departure Time: ";
    getline(cin, f.departureTime);

    cout << "Landing Time: ";
    getline(cin, f.landingTime);

    int totalRows = f.rowsFirstClass + f.rowsBusiness + f.rowsEconomy;
    int maxCols = max(f.colsFirstClass, max(f.colsBusiness, f.colsEconomy));

    f.seats = vector<vector<char>>(totalRows, vector<char>(maxCols, 'F'));
    f.passengerInfo = vector<vector<passengerData>>(totalRows, vector<passengerData>(maxCols));

    flights.push_back(f);

    cout << "____________________________________\n";
    cout << "Flight added successfully\n";
    cout << "____________________________________\n";

    // Reading data from file
    saveToFile();

    system("pause");
}

void deleteFlight() {
    system("cls");

    if (flights.empty()) {
        cout << "No flights available to delete\n";
        system("pause");
        return;
    }

    cout << "_______________________________________________\n";
    cout << left << setw(5) << "No"
         << setw(20) << "Flight"
         << setw(12) << "From"
         << setw(12) << "To" << endl;
    cout << "_______________________________________________\n";

    for (int i = 0; i < flights.size(); i++) {
        cout << left << setw(5) << i + 1
             << setw(20) << flights[i].flightName
             << setw(12) << flights[i].from
             << setw(12) << flights[i].to << endl;
    }

    cout << "_______________________________________________\n";
    cout << "Select flight to delete: ";

    int choice;
    cin >> choice;
    choice--;

    if (choice < 0 || choice >= flights.size()) {
        cout << "Invalid selection\n";
        system("pause");
        return;
    }

    flights.erase(flights.begin() + choice);

    saveToFile();   // THIS LINE UPDATES THE FILE

    cout << "_______________________________________________\n";
    cout << "Flight deleted successfully\n";
    cout << "_______________________________________________\n";
    system("pause");
}


void displayFlightSeats(flightData &f) {
    system("cls");

    cout << "____________________________________________________\n";
    cout << "Flight: " << f.flightName << " | " << f.from << " -> " << f.to << endl;
    cout << "____________________________________________________\n";

    int r = 0;

    cout << "\nFirst Class Seats\n";
    cout << "____________________________________________________\n";
    for (int i = 0; i < f.rowsFirstClass; i++, r++) {
        for (int j = 0; j < f.colsFirstClass; j++)
            cout << "(" << r << "-" << j << " " << f.seats[r][j] << ") ";
        cout << endl;
    }

    cout << "\nBusiness Class Seats\n";
    cout << "____________________________________________________\n";
    for (int i = 0; i < f.rowsBusiness; i++, r++) {
        for (int j = 0; j < f.colsBusiness; j++)
            cout << "(" << r << "-" << j << " " << f.seats[r][j] << ") ";
        cout << endl;
    }

    cout << "\nEconomy Class Seats\n";
    cout << "____________________________________________________\n";
    for (int i = 0; i < f.rowsEconomy; i++, r++) {
        for (int j = 0; j < f.colsEconomy; j++)
            cout << "(" << r << "-" << j << " " << f.seats[r][j] << ") ";
        cout << endl;
    }
}

int getTicketPrice(flightData &f, int row) {
    int first = 25000, business = 20000, economy = 15000;
    if (f.flightType == "International") {
        first *= 3; business *= 3; economy *= 3;
    }
    if (row < f.rowsFirstClass) return first;
    if (row < f.rowsFirstClass + f.rowsBusiness) return business;
    return economy;
}

void reserveSeat(flightData &f) {
    displayFlightSeats(f);

    int row, col;
    cout << "Enter row and column: ";
    cin >> row >> col;

    while (row < 0 || col < 0 || row >= f.seats.size() ||
           col >= f.seats[0].size() || f.seats[row][col] == 'R') {
        cout << "Invalid or reserved. Enter again: ";
        cin >> row >> col;
    }

    cin.ignore();
    cout << "Passenger Name: ";
    getline(cin, f.passengerInfo[row][col].name);
    cout << "Gender: ";
    getline(cin, f.passengerInfo[row][col].gender);
    cout << "CNIC: ";
    cin >> f.passengerInfo[row][col].cnic;

    int price = getTicketPrice(f, row);
    f.passengerInfo[row][col].ticketPrice = price;
    f.seats[row][col] = 'R';
    f.revenue += price;

    cout << "______________________________________\n";
    cout << "Ticket Reserved Successfully\n";
    cout << "______________________________________\n";
    cout << "Name  : " << f.passengerInfo[row][col].name << endl;
    cout << "CNIC  : " << f.passengerInfo[row][col].cnic << endl;
    cout << "Seat  : Row " << row << " , Column " << col << endl;
    cout << "Price : " << price << endl;
    cout << "_______________________________________\n";

    saveToFile();

    system("pause");
}


void showSeatInfo(flightData &f) {
    displayFlightSeats(f);

    int row, col;
    cout << "Enter row and column: ";
    cin >> row >> col;

    if (f.seats[row][col] == 'F') {
        cout << "Seat is free\n";
        system("pause");
        return;
    }

    cout << "_____________________________________\n";
    cout << "Seat Information\n";
    cout << "_____________________________________\n";
    cout << "Name   : " << f.passengerInfo[row][col].name << endl;
    cout << "Gender : " << f.passengerInfo[row][col].gender << endl;
    cout << "CNIC   : " << f.passengerInfo[row][col].cnic << endl;
    cout << "Price  : " << f.passengerInfo[row][col].ticketPrice << endl;
    cout << "______________________________________\n";
    system("pause");
}

void freeSeatByCNIC() {
    system("cls");
    long long c;
    cout << "Enter CNIC: ";
    cin >> c;

    for (auto &f : flights)
        for (int i = 0; i < f.seats.size(); i++)
            for (int j = 0; j < f.seats[i].size(); j++)
                if (f.seats[i][j] == 'R' && f.passengerInfo[i][j].cnic == c) {
                    f.revenue -= f.passengerInfo[i][j].ticketPrice;
                    f.seats[i][j] = 'F';
                    f.passengerInfo[i][j] = passengerData();

                    cout << "_____________________________________\n";
                    cout << "Seat freed successfully\n";
                    cout << "______________________________________\n";
                    system("pause");
                    return;
                }

    cout << "No booking found\n";

    saveToFile();

    system("pause");
}

void manageFlight() {
    system("cls");

    if (flights.empty()) {
        cout << "No flights available\n";
        system("pause");
        return;
    }

    cout << "___________________________________________________________________\n";
    cout << left << setw(5) << "No"
         << setw(15) << "Flight"
         << setw(12) << "From"
         << setw(12) << "To"
         << setw(15) << "Type"
         << setw(10) << "Revenue" << endl;
    cout << "___________________________________________________________________\n";

    for (int i = 0; i < flights.size(); i++){
        cout << left << setw(5) << i + 1
             << setw(15) << flights[i].flightName
             << setw(12) << flights[i].from
             << setw(12) << flights[i].to
             << setw(16) << flights[i].flightType
             << setw(10) << flights[i].revenue << endl;
    }

    cout << "___________________________________________________________________\n";

    int ch;
    cout << "Select flight: ";
    cin >> ch;
    ch--;

    while (true) {
        system("cls");
        cout << "1. Reserve Seat\n";
        cout << "2. Free Seat by CNIC\n";
        cout << "3. Delete a flight\n";
        cout << "4. Show Seat Info\n";
        cout << "0. Back\n";
        cout << "Enter: ";
        int op;
        cin >> op;

        if (op == 0) break;
        if (op == 1){
            reserveSeat(flights[ch]);
        } else if (op == 2){
            freeSeatByCNIC();
        } else if (op == 3){
            deleteFlight();
        } else if (op == 4) {
            showSeatInfo(flights[ch]);
        }
    }
}

void airlineSystem() {
    loadFromFile();

    system("cls");
    string user, pass;

    cout << "Admin Login\n";
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    if (user != "admin" || pass != "123") {
        cout << "Invalid login\n";
        system("pause");
        return;
    }

    while (true) {
        system("cls");
        cout << "\n_________________________________\n";
        cout << "AIRLINE ADMIN MENU\n";
        cout << "_________________________________\n";
        cout << "1. Add Flight\n";
        cout << "2. Manage Flight\n";
        cout << "0. Exit\n";
        cout << "_________________________________\n";
        cout << "Enter choice: ";

        int op;
        cin >> op;

        if (op == 0) break;
        if (op == 1) addFlight();
        else if (op == 2) manageFlight();
    }

    cout << "Air line Program Ended\n";
}
