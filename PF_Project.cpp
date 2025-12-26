#include <iostream>
#include <vector>
#include <cstdlib>
#include <limits>

using namespace std;

int rows, columns, rowIn, columnIn, totalAmount = 0;
void cinemaSize(int& rows, int& columns){
    cout << "Enter the number of rows: ";
    cin >> rows;
    
    cout << "Enter the number of columns: ";
    cin >> columns;
}

void emptySeats(int r, int c, vector<vector<char>>& reserveSeats){
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            reserveSeats [i][j] = 'F';
        }
    }
}
void displaySeats(int r, int c, int freeSeat, int reservedSeat, vector<vector<char>>& reserveSeats){
    
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            cout << "(" << i << "-" << j << " " << reserveSeats [i][j] <<")  ";
        }
    cout << "\n";
    }
    cout << "\n";
    cout << "Total free seats= " << freeSeat << endl;
    cout << "Total Reserved Seats= " << reservedSeat << endl;
    
}

// Price of different seats
void priceList(){
    cout << "Front 2 row = 1000\n";
    cout << "Middle 3 rows = 600\n";
    cout << "Last  rows = 350\n";
}

int seatPrice(int rowIn){
    int price = 0;
    if (rowIn <= 1){
        price = 1000;
    } else if (rowIn <= 4){
        price = 600;
    }else {
        price = 350;
    }
    return price;
}

struct bookData{
    string userName;
    string gender;
    long long cnic;
    int ticketPrice;
};

void reserveFunction(int r, int c, vector<vector<char>>& reserveSeats, vector<vector<bookData>>& seatData){
    
        cout << "Enter row and column to reserve seat: ";
        cin >> rowIn >> columnIn;

        while (true) {
            if (rowIn >= r || columnIn >= c) {
                cout << rowIn << columnIn << " is an invalid seat number\n";
                cout << "Enter row and column: ";
                cin >> rowIn >> columnIn;
                continue;
            }

            if (reserveSeats[rowIn][columnIn] == 'R') {
                cout << rowIn << columnIn << " is already reserved\n";
                cout << "Enter row and column: ";
                cin >> rowIn >> columnIn;
                continue;
            }
        cout << "Enter Your Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, seatData[rowIn][columnIn].userName);

        cout << "Gender: ";
        cin >> seatData [rowIn][columnIn].gender;
        cout << "Enter CNIC Number: ";
        cin >> seatData [rowIn][columnIn].cnic;
        seatData [rowIn][columnIn].ticketPrice = seatPrice(rowIn);
        reserveSeats[rowIn][columnIn] = 'R';
        
        break;
    }
}   
    
void freeFunction(int r, int c, vector<vector<char>>& reserveSeats){
        
        cout << "Enter row and column to free seat: ";
        cin >> rowIn >> columnIn;
        
        while (true) {
            if (rowIn >= r || columnIn >= c) {
                cout << rowIn << columnIn << " is an invalid seat number\n";
                cout << "Enter row and column: ";
                cin >> rowIn >> columnIn;
                continue;
            }

            if (reserveSeats[rowIn][columnIn] == 'F') {
                cout << rowIn << columnIn << " is already free\n";
                cout << "Enter row and column: ";
                cin >> rowIn >> columnIn;
                continue;
            }
        break;
    }
    reserveSeats[rowIn][columnIn] = 'F';
}

void showSeatInfo (vector<vector<bookData>>& seatData,vector<vector<char>>& reserveSeats){
    cout << "Enter row and column to show seat info: ";
    cin >> rowIn >> columnIn;
        
        if (rowIn >= rows || columnIn >= columns) {
            cout << rowIn << columnIn << " is an invalid seat number\n";
        }else if (reserveSeats[rowIn][columnIn] == 'F') {
            cout << rowIn << columnIn << " is a free seat\n";
        }else {
            cout << "Seat holder name: " << seatData [rowIn][columnIn].userName << endl;
            cout << "Seat holder Gender: " << seatData [rowIn][columnIn].gender << endl;
            cout << "Seat holder CNIC: " << seatData [rowIn][columnIn].cnic << endl;
            cout << "Ticket Price: " << seatData [rowIn][columnIn].ticketPrice << endl;
    }
}


void cinemaMenu(){
    cinemaSize(rows, columns);
    int freeSeats = (rows*columns), reservedSeats = 0;
    
    cout << "\n";
    vector<vector<char>> reserveSeats (rows, vector<char>(columns));
    vector<vector<bookData>> seatData(rows, vector<bookData>(columns));
    
    emptySeats(rows, columns, reserveSeats);

    int userAmount = 0;
    
    
    bool runLoop = true;
    do{
        system("cls");
        displaySeats(rows, columns, freeSeats, reservedSeats, reserveSeats);
        cout << "\n";
       int option;
      
       cout << "\n";
       cout << "What do you want?\n";
       cout << "1. Reserve a seat\n";
       cout << "2. Free a seat\n";
       cout << "3. Show Total Amount of sold out tickets\n";
       cout << "4. Show seat holder details\n";
       cout << "0. to exit\n";
       cout << "Enter: ";
       cin >> option;
       cout << "\n";
       
        switch (option){
            case 1: priceList();
                    userAmount = 0;
                    reserveFunction(rows, columns, reserveSeats, seatData);
                    reservedSeats++;
                    freeSeats--;
                    userAmount += seatPrice(rowIn);
                    totalAmount += seatPrice(rowIn);
                    cout << "\n";
                    cout <<"Your Total bill = " << userAmount << endl;
            break;
            case 2: if (reservedSeats == 0){
                       cout << "All seats are already free";
                    } else {
                       freeFunction(rows, columns, reserveSeats);
                       reservedSeats--;
                       freeSeats++;
                       totalAmount -= seatPrice(rowIn);
                       seatData[rowIn][columnIn] = bookData{};
                    }
            break;
            case 3: cout << "Total sold out amount= " << totalAmount << endl;
            break;
            case 4: if (reservedSeats == 0){
                       cout << "No reserved seat. All seats are free!";
                    } else {
                    showSeatInfo(seatData, reserveSeats);
                    }
            break;
            case 0: runLoop = false;
            break;
            default: cout << "Invalid Option\n";
            break;
        }
        system("pause"); 
    }while (runLoop);
}
    
int main() {
    cinemaMenu();
    
    return 0;
}