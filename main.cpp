#include <iostream>
#include "cinema.h"
#include "airline.h"

using namespace std;

int main() {
    int option;

    do {
        cout << "\n===== MAIN MENU =====\n";
        cout << "1. Cinema Reservation\n";
        cout << "2. Airline Reservation\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> option;

        switch (option) {
            case 1:
                mainCinema();
                break;
            case 2:
                airlineSystem();
                break;
            case 0:
                cout << "Exiting Program...\n";
                break;
            default:
                cout << "Invalid Option\n";
        }

    } while (option != 0);

    return 0;
}
