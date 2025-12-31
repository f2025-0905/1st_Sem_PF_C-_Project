#include <iostream>
#include <vector>
#include <cstdlib>
#include <limits>

using namespace std;

// GLOBAL VARIABLES
int rows, columns, rowIn, columnIn, totalAmount = 0;

void cinemaSize(int& rows, int& columns){
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> columns;
}

void emptySeats(int r, int c, vector<vector<char>>& reserveSeats){
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            reserveSeats[i][j] = 'F';
}

void displaySeats(int r, int c, vector<vector<char>>& reserveSeats){
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cout << "(" << i << "-" << j << " " << reserveSeats[i][j] << ")  ";
        }
        cout << endl;
    }
}

void priceList(){
    cout << "Front 2 rows = 1000\n";
    cout << "Middle 3 rows = 600\n";
    cout << "Last rows = 350\n";
}

int seatPrice(int rowIn){
    if(rowIn <= 1) return 1000;
    else if(rowIn <= 4) return 600;
    else return 350;
}

struct bookData{
    string userName;
    string gender;
    long long cnic;
    int ticketPrice;
};

void reserveFunction(int r,int c,vector<vector<char>>& reserveSeats,vector<vector<bookData>>& seatData){
    cout << "Enter row and column: ";
    cin >> rowIn >> columnIn;

    while(true){
        if(rowIn >= r || columnIn >= c){
            cout << "Invalid seat. Enter again: ";
            cin >> rowIn >> columnIn;
            continue;
        }
        if(reserveSeats[rowIn][columnIn] == 'R'){
            cout << "Already reserved. Enter again: ";
            cin >> rowIn >> columnIn;
            continue;
        }

        cout << "Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, seatData[rowIn][columnIn].userName);

        cout << "Gender: ";
        cin >> seatData[rowIn][columnIn].gender;

        cout << "CNIC: ";
        cin >> seatData[rowIn][columnIn].cnic;

        seatData[rowIn][columnIn].ticketPrice = seatPrice(rowIn);
        reserveSeats[rowIn][columnIn] = 'R';
        break;
    }
}

void freeFunction(int r,int c,vector<vector<char>>& reserveSeats){
    cout << "Enter row and column: ";
    cin >> rowIn >> columnIn;

    while(true){
        if(rowIn >= r || columnIn >= c){
            cout << "Invalid seat. Enter again: ";
            cin >> rowIn >> columnIn;
            continue;
        }
        if(reserveSeats[rowIn][columnIn] == 'F'){
            cout << "Seat already free. Enter again: ";
            cin >> rowIn >> columnIn;
            continue;
        }
        break;
    }
    reserveSeats[rowIn][columnIn] = 'F';
}

void showSeatInfo(vector<vector<bookData>>& seatData, vector<vector<char>>& reserveSeats){
    cout << "Enter row and column: ";
    cin >> rowIn >> columnIn;

    if(reserveSeats[rowIn][columnIn] == 'F'){
        cout << "Seat is free\n";
    } else {
        cout << "Name: " << seatData[rowIn][columnIn].userName << endl;
        cout << "Gender: " << seatData[rowIn][columnIn].gender << endl;
        cout << "CNIC: " << seatData[rowIn][columnIn].cnic << endl;
        cout << "Price: " << seatData[rowIn][columnIn].ticketPrice << endl;
    }
}

int main(){

    vector<string> movieNames;
    vector<int> movieRows, movieCols;
    vector<int> movieRevenue;
    vector<vector<vector<char>>> movieSeats;
    vector<vector<vector<bookData>>> movieSeatData;

    bool runProgram = true;

    while(runProgram){
        system("cls");

        int role;
        cout << "1. Owner\n2. User\n0. Exit\nEnter: ";
        cin >> role;

        if(role == 0) break;

        /* ================= OWNER ================= */
        if(role == 1){
            string user, pass;
            cout << "Username(default: shafqat): ";
            cin >> user;
            cout << "Password(default: 123): ";
            cin >> pass;

            if(user != "shafqat" || pass != "123"){
                cout << "Invalid login\n";
                system("pause");
                continue;
            }

            bool ownerMenu = true;
            while(ownerMenu){
                system("cls");
                cout << "\nOWNER MENU\n";
                cout << "1. Add Movie\n";
                cout << "2. Manage Movie\n";
                cout << "3. Show Total Revenue\n";
                cout << "0. Back to Main Menu\n";
                cout << "Enter: ";
                int op;
                cin >> op;

                if(op == 0) break;

                if(op == 1){
                    string name;
                    cout << "Enter movie name: ";
                    cin.ignore();
                    getline(cin, name);

                    cinemaSize(rows, columns);

                    movieNames.push_back(name);
                    movieRows.push_back(rows);
                    movieCols.push_back(columns);
                    movieRevenue.push_back(0);

                    movieSeats.push_back(vector<vector<char>>(rows, vector<char>(columns)));
                    movieSeatData.push_back(vector<vector<bookData>>(rows, vector<bookData>(columns)));
                    emptySeats(rows, columns, movieSeats.back());

                    cout << "Movie added successfully\n";
                    system("pause");
                }

                else if(op == 2){
                    if(movieNames.size() == 0){
                        cout << "There is no movie currently available\n";
                        system("pause");
                        continue;
                    }

                    cout << "Movies:\n";
                    for(int i=0;i<movieNames.size();i++)
                        cout << i+1 << ". " << movieNames[i] << endl;

                    int choice;
                    cout << "Select movie: ";
                    cin >> choice;
                    choice--;

                    rows = movieRows[choice];
                    columns = movieCols[choice];

                    displaySeats(rows, columns, movieSeats[choice]);

                    cout << "1. Reserve Seat\n";
                    cout << "2. Free Seat\n";
                    cout << "3. Show Seat Info\n";
                    cout << "4. Show Movie Revenue\n";
                    cout << "0. Back\n";
                    cout << "Enter: ";

                    int ch;
                    cin >> ch;

                    if(ch == 1){
                        reserveFunction(rows, columns, movieSeats[choice], movieSeatData[choice]);
                        int price = seatPrice(rowIn);
                        totalAmount += price;
                        movieRevenue[choice] += price;
                    }
                    else if(ch == 2){
                        freeFunction(rows, columns, movieSeats[choice]);
                        int price = seatPrice(rowIn);
                        totalAmount -= price;
                        movieRevenue[choice] -= price;
                    }
                    else if(ch == 3){
                        showSeatInfo(movieSeatData[choice], movieSeats[choice]);
                    }
                    else if(ch == 4){
                        cout << "Revenue of this movie = " << movieRevenue[choice] << endl;
                    }
                    system("pause");
                }

                else if(op == 3){
                    cout << "Total Revenue from all movies = " << totalAmount << endl;
                    system("pause");
                }
            }
        }

        /* ================= USER ================= */
        else if(role == 2){
            if(movieNames.size() == 0){
                cout << "There is no movie currently available\n";
                system("pause");
                continue;
            }

            bool userMenu = true;
            while(userMenu){
                system("cls");
                cout << "\nMovies:\n";
                for(int i=0;i<movieNames.size();i++)
                    cout << i+1 << ". " << movieNames[i] << endl;
                cout << "0. Back to Main Menu\n";

                int choice;
                cout << "Select movie: ";
                cin >> choice;

                if(choice == 0) break;
                choice--;

                rows = movieRows[choice];
                columns = movieCols[choice];

                displaySeats(rows, columns, movieSeats[choice]);

                cout << "1. Reserve Seat\n2. Free Seat\n0. Back\nEnter: ";
                int op;
                cin >> op;

                if(op == 1){
                    reserveFunction(rows, columns, movieSeats[choice], movieSeatData[choice]);
                    cout << "Your bill = " << seatPrice(rowIn) << endl;
                    totalAmount += seatPrice(rowIn);
                    movieRevenue[choice] += seatPrice(rowIn);
                }
                else if(op == 2){
                    freeFunction(rows, columns, movieSeats[choice]);
                    totalAmount -= seatPrice(rowIn);
                    movieRevenue[choice] -= seatPrice(rowIn);
                }
                system("pause");
            }
        }
    }
    return 0;
}
