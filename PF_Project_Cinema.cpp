#include <iostream>
#include <vector>
#include <cstdlib>
#include <limits>

using namespace std;

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

int seatPrice(int rowIn){
    if(rowIn <= 1) return 1000;
    else if(rowIn <= 4) return 600;
    else return 350;
}

struct bookData{
    string userName;
    string gender;
    long long cnic = 0;
    int ticketPrice = 0;
};

void reserveFunction(
    int r, int c,
    vector<vector<char>>& reserveSeats,
    vector<vector<bookData>>& seatData,
    vector<vector<vector<bookData>>>& allSeatData
){

    cout << "Enter row and column: ";
    cin >> rowIn >> columnIn;

    long long inputCnic;
    cout << "Enter CNIC: ";
    cin >> inputCnic;

    bool found = false;
    string foundName, foundGender;

    // Search CNIC in all movies
    for(int m=0; m<allSeatData.size(); m++){
        for(int i=0;i<allSeatData[m].size();i++){
            for(int j=0;j<allSeatData[m][i].size();j++){
                if(allSeatData[m][i][j].cnic == inputCnic){
                    foundName = allSeatData[m][i][j].userName;
                    foundGender = allSeatData[m][i][j].gender;
                    found = true;
                }
            }
        }
    }


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
        break;
    }

    seatData[rowIn][columnIn].cnic = inputCnic;

    if(found){
        seatData[rowIn][columnIn].userName = foundName;
        seatData[rowIn][columnIn].gender = foundGender;
        cout << "Existing user found. Data auto-filled.\n";
    } else {
        cout << "Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, seatData[rowIn][columnIn].userName);

        cout << "Gender: ";
        cin >> seatData[rowIn][columnIn].gender;
    }

    seatData[rowIn][columnIn].ticketPrice = seatPrice(rowIn);
    reserveSeats[rowIn][columnIn] = 'R';
}

void freeFunction(
    int r,int c,
    vector<vector<char>>& reserveSeats,
    vector<vector<bookData>>& seatData,
    int& movieRevenueSingle
){
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

    int price = seatData[rowIn][columnIn].ticketPrice;

    reserveSeats[rowIn][columnIn] = 'F';
    seatData[rowIn][columnIn] = bookData(); // DELETE USER DATA

    movieRevenueSingle -= price;
    totalAmount -= price;

    cout << "Seat freed successfully.\n";
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


bool freeSeatByCNIC(
    vector<vector<vector<char>>>& movieSeats,
    vector<vector<vector<bookData>>>& movieSeatData,
    vector<int>& movieRevenue,
    vector<string>& movieNames
    ){
    long long inputCnic;
    cout << "Enter CNIC: ";
    cin >> inputCnic;

    // Store found seats
    vector<int> foundMovie, foundRow, foundCol;

    for(int m = 0; m < movieSeatData.size(); m++){
        for(int i = 0; i < movieSeatData[m].size(); i++){
            for(int j = 0; j < movieSeatData[m][i].size(); j++){
                if(movieSeatData[m][i][j].cnic == inputCnic &&
                   movieSeats[m][i][j] == 'R'){
                    foundMovie.push_back(m);
                    foundRow.push_back(i);
                    foundCol.push_back(j);
                }
            }
        }
    }

    if(foundMovie.size() == 0){
        cout << "CNIC not found. Seat not freed.\n";
        return false;
    }

    int select = 0;
    if(foundMovie.size() > 1){
        cout << "\nMultiple seats found:\n";
        for(int k = 0; k < foundMovie.size(); k++){
            cout << k+1 << ". Movie: " << movieNames[foundMovie[k]]
                 << " Seat (" << foundRow[k]
                 << "," << foundCol[k] << ")\n";
        }
        cout << "Select seat to free: ";
        cin >> select;
        select--;
    }

    int m = foundMovie[select];
    int r = foundRow[select];
    int c = foundCol[select];

    int price = movieSeatData[m][r][c].ticketPrice;

    movieSeats[m][r][c] = 'F';
    movieSeatData[m][r][c] = bookData(); // CLEAR DATA

    movieRevenue[m] -= price;
    totalAmount -= price;

    cout << "Seat freed successfully.\n";
    return true;
}



int main(){

    vector<string> movieNames;
    vector<int> movieRows, movieCols;
    vector<int> movieRevenue;
    vector<vector<vector<char>>> movieSeats;
    vector<vector<vector<bookData>>> movieSeatData;

    while(true){
        system("cls");
        int role;
        cout << "1. Owner\n2. User\n0. Exit\nEnter: ";
        cin >> role;

        if(role == 0) break;

        // OWNER
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

            while(true){
                system("cls");
                cout << "\nOWNER MENU\n";
                cout << "1. Add Movie\n";
                cout << "2. Manage Movie\n";
                cout << "3. Show Total Revenue\n";
                cout << "4. Search Person by CNIC\n";
                cout << "0. Back\n";
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
                    if(movieNames.empty()){
                        cout << "There is no movie currently available\n";
                        system("pause");
                        continue;
                    }

                    for(int i=0;i<movieNames.size();i++)
                        cout << i+1 << ". " << movieNames[i] << endl;

                    int choice;
                    cout << "Select movie: ";
                    cin >> choice;
                    choice--;

                    rows = movieRows[choice];
                    columns = movieCols[choice];

                    displaySeats(rows, columns, movieSeats[choice]);

                    cout << "1. Reserve Seat\n2. Free Seat\n3. Show Seat Info\n4. Show Movie Revenue\n0. Back\nEnter: ";
                    int ch;
                    cin >> ch;

                    if(ch == 1){
                        reserveFunction(rows, columns, movieSeats[choice], movieSeatData[choice], movieSeatData);
                        int p = seatPrice(rowIn);
                        totalAmount += p;
                        movieRevenue[choice] += p;
                    }
                    else if(ch == 2){
                        freeFunction(
                        rows,
                        columns,
                        movieSeats[choice],
                        movieSeatData[choice],
                        movieRevenue[choice]
                        );
                    }
                    else if(ch == 3){
                        showSeatInfo(movieSeatData[choice], movieSeats[choice]);
                    }
                    else if(ch == 4){
                        cout << "Movie Revenue = " << movieRevenue[choice] << endl;
                    }
                    system("pause");
                }

                else if(op == 3){
                    cout << "Total Revenue = " << totalAmount << endl;
                    system("pause");
                }

                else if(op == 4){
                    long long c;
                    cout << "Enter CNIC: ";
                    cin >> c;
                    bool found = false;

                    for(int m=0;m<movieSeatData.size();m++){
                        for(int i=0;i<movieSeatData[m].size();i++){
                            for(int j=0;j<movieSeatData[m][i].size();j++){
                                if(movieSeatData[m][i][j].cnic == c){
                                    cout << "\nMovie: " << movieNames[m];
                                    cout << "\nSeat: (" << i << "," << j << ")";
                                    cout << "\nName: " << movieSeatData[m][i][j].userName;
                                    cout << "\nGender: " << movieSeatData[m][i][j].gender;
                                    cout << "\nPrice: " << movieSeatData[m][i][j].ticketPrice << endl;
                                    found = true;
                                }
                            }
                        }
                    }
                    if(!found) cout << "No record found\n";
                    system("pause");
                }
            }
        }

        // USER
        else if(role == 2){
            if(movieNames.empty()){
                cout << "There is no movie currently available\n";
                system("pause");
                continue;
            }

            while(true){
                system("cls");
                for(int i=0;i<movieNames.size();i++)
                    cout << i+1 << ". " << movieNames[i] << endl;
                cout << "0. Back\nEnter: ";

                int choice;
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
                    reserveFunction(rows, columns, movieSeats[choice], movieSeatData[choice], movieSeatData);
                    int p = seatPrice(rowIn);
                    cout << "Your bill = " << p << endl;
                    totalAmount += p;
                    movieRevenue[choice] += p;
                }
                else if(op == 2){
                    freeSeatByCNIC(movieSeats, movieSeatData, movieRevenue, movieNames);
                system("pause");
                }
            }
        }
    }
    return 0;
}