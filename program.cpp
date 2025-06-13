#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>
#include <windows.h>
using namespace std;

HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
bool enter = false;

struct userAcc
{
    string username;
    string password;
};

struct flight
{
    int id;
    string destination;
    string time;
};

struct reserved
{
    string username;
    int id;
    string destination;
    string time;
    string seat;
    int price;
};

void bookTicket(string username);
void bookHistory();
void editTicket();
void showFlight();
void showUser();
void flightDetails();
void addFlight();
void removeFlight();
void adminLogin();
void login();
void signUp();
void updateFlightTxt();
void report();
int seat(string username, string destination);
bool payment(string username, int price);
void display();
void byebye();

int main()
{
    // Get a handle to the console window
    HWND consoleWindow = GetConsoleWindow();

    // Set the console window to maximized state
    ShowWindow(consoleWindow, SW_MAXIMIZE);

    system("cls");
    int choice;
    bool fail = false;

    while (!enter)
    {
        cout << endl;

        display();

        string temp;
        cout << endl << "\t\t\t\t\t\t\t\t\t\t   press ENTER to enter" << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
        getline(cin, temp);
        enter = true;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }

    //display main menu
    do
    {   
        system("cls");
        cout << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << "\t\t\tMAIN MENU" << endl << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << "\t\t\t\tUSER:" << endl;
        cout << "\t\t\t\t\t[1] View ALl Flights" << endl;
        cout << "\t\t\t\t\t[2] Book A Flight" << endl;
        cout << "\t\t\t\t\t[3] Booking History" << endl;
        cout << endl << "\t\t\t\tADMIN:" << endl;
        cout << "\t\t\t\t\t[4] User Account Management" << endl;
        cout << "\t\t\t\t\t[5] Flight Details Management" << endl;
        cout << "\t\t\t\t\t[6] Report" << endl;
        cout << endl << endl << "\t\t\t\t\t[0] Exit Program" << endl;
        cout << endl << "\t\t\t\t\tEnter here: ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | FOREGROUND_GREEN);
        cin >> choice;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //output error message when input is invalid
        if (cin.fail())
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\t\tInvalid input" << endl;
            cout << "\t\t\t\t\tEnter value between 1-6" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cin.clear();
            cin.ignore(10000, '\n');
            Sleep(1500);
        }
        //exit program
        else if (choice == 0)
        {
            system("cls");
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << endl << "\t\t\tExiting program..." << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
            byebye();
            exit(0);
        }
        else if (choice < 0 || choice > 6)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\t\tInvalid input" << endl;
            cout << "\t\t\t\t\tEnter value between 1-6" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
        }
        //book flight
        else if (choice == 2)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            login();
        }
        //booking history
        else if (choice == 3)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            bookHistory();
        }
        //view all flights
        else if (choice == 1)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            showFlight();
        }
        //user account management
        else if (choice == 4)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            adminLogin();
            showUser();
        }
        //flight details management
        else if (choice == 5)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            adminLogin();
            flightDetails();
        }
        //generate report
        else if (choice == 6)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            adminLogin();
            system("cls");
            cout << endl << "\t\t\tGenerating report..." << endl;
            Sleep(1500);
            report();
        }
    } while (!fail);

    return 0;
}


void bookTicket(string username)
{
    ifstream infile("flight.txt");
    ofstream outfile("reserved.txt", ios::app);
    int flightNo;
    string flightDestination, time1;
    int destination;
    string destination1;
    string line;
    int choice, choice1, found = 0;
    flight plane[1000];
    int m = 0, k = 0, id[100];
    bool fail = false, fail1 = false;
    int price;
    string type;
    bool paid = false, search = false;

    //show all available flight destinations
    do
    {
        system("cls");
        cout << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << "\t\t\tFLIGHT BOOKING" << endl << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        cout << "\t\t\t\t[1] Melaka" << endl;
        cout << "\t\t\t\t[2] Selangor" << endl;
        cout << "\t\t\t\t[3] Kuala Lumpur" << endl;
        cout << "\t\t\t\t[4] Penang" << endl;
        cout << "\t\t\t\t[5] Johor" << endl;
        cout << "\t\t\t\t[6] Kedah" << endl;
        cout << endl << "\t\t\t\t[0] Main Menu" << endl;
        cout << "\t\t\t\tSelect your destination: ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> destination;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //error due to invalid input
        if (cin.fail())
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input. Enter value between 1-6" << endl << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cin.clear();
            cin.ignore(10000, '\n');
            Sleep(1500);
        }
        else if (destination < 0 || destination > 6)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input. Enter value between 1-6" << endl << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
        }
        //convert user input to actual word of destination
        else if (destination == 1)
        {
            destination1 = "melaka";
            fail = true;
        }
        else if (destination == 2)
        {
            destination1 = "selangor";
            fail = true;
        }
        else if (destination == 3)
        {
            destination1 = "kl";
            fail = true;
        }
        else if (destination == 4)
        {
            destination1 = "penang";
            fail = true;
        }
        else if (destination == 5)
        {
            destination1 = "johor";
            fail = true;
        }
        else if (destination == 6)
        {
            destination1 = "kedah";
            fail = true;
        }
        //back to main menu
        else if (destination == 0)
        {
            system("cls");
            cout << endl << "\t\t\tHeading to Main Menu..." << endl;
            Sleep(1500);
            main();
        }
    } while (!fail);
    

    system("cls");
    cout << endl << "\t\t\tSearching..." << endl;
    Sleep(1500);

    system("cls");
    cout << endl << "\t\t\tDestination: " << destination1 << endl;

    //display out all available flights with departure time
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
    cout << endl << "\t\t\t\tAvailable Departure Time:" << endl;
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    Sleep(1500);

    if (infile.is_open())
    {
        cout << "\t\t\t\t";
        for (int i = 0; i < 50; i++)
        {
            cout << "-";
        }
        cout << endl;

        cout << "\t\t\t\tFlight ID\t| Departure Time" << endl;
        
        cout << "\t\t\t\t";
        for (int i = 0; i < 50; i++)
        {
            cout << "-";
        }
        cout << endl;

        while (getline(infile, line))
        {
            //get available flights data from text file
            infile >> plane[m].id >> plane[m].destination >> plane[m].time;

            if (destination1 == plane[m].destination)
            {
                //add flight with selected destination into an array
                id[k] = plane[m].id;
                k++;
            }
            m++;
        }
        //sort the data
        for (int j = 0; j < m - 1; j++)
        {
            for (int l = 0; l < m - j - 1; l++)
            {
                if (plane[l].destination > plane[l + 1].destination || ((plane[l].destination == plane[l + 1].destination) && plane[l].time > plane[l + 1].time))
                {
                    swap(plane[l], plane[l + 1]);
                }
            }
        }

        //display out the flight with selected destination
        for (int j = 0; j < m; j++)
        {
            for (int l = 0; l < k; l++)
            {
                if (id[l] == plane[j].id && destination1 == plane[j].destination)
                {
                    cout << "\t\t\t\t" << plane[j].id << "\t\t| " << plane[j].time << endl;
                    Sleep(250);
                }
            }
        }

        cout << "\t\t\t\t";
        for (int i = 0; i < 50; i++)
        {
            cout << "-";
        }
        cout << endl;
        infile.close();
    }
    else
    {
        cout << "\t\t\t\t";
        for (int i = 0; i < 50; i++)
        {
            cout << "-";
        }
        cout << endl;

        cout << "\t\t\t\tFlight ID\t| Departure Time" << endl;

        cout << "\t\t\t\t";
        for (int i = 0; i < 50; i++)
        {
            cout << "-";
        }
        cout << endl;

        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
        cout << "\t\t\t\t\tflight.txt is missing" << endl;
        Sleep(1500);
        cout << endl << "\t\t\t\t\tCreating flight.txt...Please try again." << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        cout << "\t\t\t\t";
        for (int i = 0; i < 50; i++)
        {
            cout << "-";
        }
        cout << endl;

        ofstream outfile("flight.txt", ios::app);
        outfile << "flight details";
        outfile.close();
        Sleep(1500);
        bookTicket(username);
    }

    cout << endl << "\t\t\t\t\t[0] Back" << endl;

    fail = false;
    do
    {
        //ask user to choose a flight
        cout << endl << "\t\t\t\t\tEnter Flight ID: ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> choice1;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //error due to invalid input
        if (cin.fail())
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\t\tInvalid input" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cin.clear();
            cin.ignore(10000, '\n');
        }
        //back to previous page
        else if (choice1 == 0)
        {
            system("cls");
            cout << endl << "\t\t\tHeading back..." << endl;
            Sleep(1500);
            bookTicket(username);
        }
        else
        {
            fail = true;
        }
    } while (!fail);

    //check whether then input flight id is valid
    for (int j = 0; j < k; j++)
    {
        //valid flight id
        if (choice1 == id[j])
        {
            cout << endl << "\t\t\t\t\tLoading..." << endl;
            Sleep(1500);

            //let user to choose type of seat
            price = seat(username, destination1);

            if (destination1 == "melaka")
            {
                if (price == 52)
                {
                    type = "premium";
                }
                else if (price == 52 / 2)
                {
                    type = "standard";
                }
            }
            else if (destination1 == "selangor")
            {
                if (price == 46)
                {
                    type = "premium";
                }
                else if (price == 46 / 2)
                {
                    type = "standard";
                }
            }
            else if (destination1 == "kl")
            {
                if (price == 50)
                {
                    type = "premium";
                }
                else if (price == 50 / 2)
                {
                    type = "standard";
                }
            }
            else if (destination1 == "penang")
            {
                if (price == 68)
                {
                    type = "premium";
                }
                else if (price == 68 / 2)
                {
                    type = "standard";
                }
            }
            else if (destination1 == "johor")
            {
                if (price == 88)
                {
                    type = "premium";
                }
                else if (price == 88 / 2)
                {
                    type = "standard";
                }
            }
            else if (destination1 == "kedah")
            {
                if (price == 58)
                {
                    type = "premium";
                }
                else if (price == 58 / 2)
                {
                    type = "standard";
                }
            }
            
            cout << endl << "\t\t\t\tProceed to payment..." << endl;
            Sleep(1500);

            //let user to complete their payment
            paid = payment(username, price);

            
            if (paid)
            {
                system("cls");
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
                cout << endl << "\t\t\tPayment done" << endl;
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                //update data into text file
                infile.open("flight.txt");
                while (getline(infile, line))
                {
                    infile >> flightNo >> flightDestination >> time1;

                    if (choice1 == flightNo && destination1 == flightDestination)
                    {
                        outfile << endl << username << " " << flightNo << " " << flightDestination << " " << time1 << " " << type << " " << price;
                    }
                }
                cout << endl << "\t\t\tBooking..." << endl;
                Sleep(1500);
                found++;
            }
            //payment failed
            else
            {
                system("cls");
                cout << "\t\t\t\tPayment unsuccessful. Please try again." << endl;
                Sleep(1500);
                bookTicket(username);
            }
        }
    }
    //invalid flight id
    if (found == 0)
    {
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
        cout << "\t\t\t\t\tInvalid Flight ID. Please try again." << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        Sleep(1500);
        bookTicket(username);
    }
    
    outfile.close();
    infile.close();


    do
    {
        system("cls");
        cout << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
        cout << "\t\t\tBooked successfully" << endl << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << "\t\t\t\t[1] Book Again" << endl;
        cout << "\t\t\t\t[2] Show Booking History" << endl;
        cout << "\t\t\t\t[0] Back" << endl;
        cout << endl << "\t\t\t\tEnter here: ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> choice;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //error due to invalid input
        if (cin.fail())
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cin.clear();
            cin.ignore(10000, '\n');
            Sleep(1500);
        }
        else if (choice < 0 || choice > 2)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
        }
        //back to main menu
        else if (choice == 0)
        {
            system("cls");
            cout << endl << "\t\t\tHeading to Main Menu..." << endl;
            Sleep(1500);
            main();
        }
        //book again
        else if (choice == 1)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            bookTicket(username);
        }
        //booking history
        else if (choice == 2)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            bookHistory();
        }
    } while (!fail1);
}

void bookHistory()
{
    system("cls");
    cout << endl;

    string input, line;
    int i = 0;
    int choice;
    bool found = false, fail = false;
    reserved ticket[1000];
    ifstream infile("reserved.txt");

    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
    cout << "\t\t\tBOOKING HISTORY" << endl << endl;
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    if (infile.is_open())
    {   
        //ask user to input their username
        cout << "\t\t\t\t[0] Back" << endl;
        cout << endl << "\t\t\t\tEnter Username: ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        getline(cin, input);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        
        //back to main menu
        if (input == "0")
        {
            system("cls");
            cout << endl << "\t\t\tHeading to Main Menu..." << endl;
            Sleep(1500);
            main();
        }

        cout << endl << "\t\t\t\tSearching..." << endl;
        Sleep(1500);

        //display all booked flight ticket by that user
        system("cls");
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << endl << "\t\t\tBOOKING HISTORY" << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << endl << "\t\t\t\tUsername: " << input << endl;
        cout << endl;

        cout << "\t\t\t\t";
        for (int i = 0; i < 100; i++)
        {
            cout << "-";
        }
        cout << endl;
        cout << "\t\t\t\t    \t| Flight ID \t| Destination\t\t| Departure Time\t| Seat Type\t| Price" << endl;

        cout << "\t\t\t\t";
        for (int i = 0; i < 100; i++)
        {
            cout << "-";
        }
        cout << endl;

        //get data from the text file
        while (getline(infile, line))
        {
            infile >> ticket[i].username  >> ticket[i].id >> ticket[i].destination >> ticket[i].time >> ticket[i].seat >> ticket[i].price;

            //find the data with input username
            if (input == ticket[i].username)
            {
                if (ticket[i].destination == "kl")
                {
                    ticket[i].destination = "kuala lumpur";
                }
                else if (ticket[i].destination == "kedah")
                {
                    ticket[i].destination = "kedah\t";
                }
                else if (ticket[i].destination == "johor")
                {
                    ticket[i].destination = "johor\t";
                }
                i++;
            }
        }

        //sort the data
        for (int j = 0; j < i - 1; j++)
        {
            for (int k = 0; k < i - j - 1; k++)
            {
                if (input == ticket[k].username)
                {
                    if (ticket[k].destination > ticket[k + 1].destination || ((ticket[k].destination == ticket[k + 1].destination) && ticket[k].time > ticket[k + 1].time))
                    {
                        swap(ticket[k], ticket[k + 1]);
                    }
                }

            }
        }

        //display out all the data
        for (int l = 0; l < i; l++)
        {
            cout << "\t\t\t\t" << l + 1 << " \t| " << ticket[l].id << " \t\t| " << ticket[l].destination << "\t\t| " << ticket[l].time << "\t\t\t| " << ticket[l].seat << "\t| " << ticket[l].price << endl;
            Sleep(250);
        }

        //no booked flight ticket found in the text file
        if (i == 0)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << endl << "\t\t\t\t\tNO FLIGHT BOOKED" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        cout << "\t\t\t\t";
        for (int i = 0; i < 100; i++)
        {
            cout << "-";
        }
        cout << endl;
    }
    else
    {
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
        cout << "\t\t\t\t\treserved.txt is missing...Please try again." << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        ofstream outfile("reserved.txt", ios::app);
        outfile << "reservation";
        outfile.close();
        Sleep(1500);
        bookHistory();
    }

    cout << endl;
    cout << "\t\t\t\t\t[1] Search Again" << endl;
    cout << "\t\t\t\t\t[2] Edit Details" << endl;
    cout << "\t\t\t\t\t[0] Back" << endl;

    do
    {
        cout << endl << "\t\t\t\t\tEnter here: ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> choice;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //error due to invalid input
        if (cin.fail())
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\t\tInvalid input" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cin.clear();
            cin.ignore(10000, '\n');
            Sleep(1500);
        }
        else if (choice < 0 || choice > 2)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\t\tInvalid input" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
        }
        //back to main menu
        else if (choice == 0)
        {
            system("cls");
            cout << endl << "\t\t\tHeading to Main Menu..." << endl;
            Sleep(1500);
            main();
        }
        //search again
        else if (choice == 1)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            bookHistory();
        }
        //edit flight ticket
        else if (choice == 2)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            editTicket();
        }
    } while (!fail);
}

void editTicket()
{
    int choice;
    bool fail = false;

    do
    {
        system("cls");
        cout << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << "\t\t\tEDIT TICKET" << endl << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        cout << "\t\t\t\t[1] Customer Service" << endl;
        cout << "\t\t\t\t[0] Back" << endl;
        cout << endl << "\t\t\t\tEnter here: ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> choice;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //error due to invalid input
        if (cin.fail())
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cin.clear();
            cin.ignore(10000, '\n');
            Sleep(1500);
        }
        else if (choice < 0 || choice > 1)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
        }
        //back to previous page
        else if (choice == 0)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            bookHistory();
        }
        //contact customer service
        else if (choice == 1)
        {
            cout << "\t\t\t\tLoading..." << endl;
            Sleep(1500);
            system("cls");
            cout << endl << "\t\t\tContacting our customer service..." << endl;
            Sleep(1500);
            cout << endl << "\t\t\tRinging..." << endl;
            Sleep(1500);
            exit(0);
        }
    } while (!fail);
}

void showFlight()
{
    system("cls");
    cout << endl;

    ifstream infile("flight.txt");
    string line;
    int choice;
    int i = 0;
    bool fail = false;
    flight plane[100];

    //display out all available flights of Kampar Mini Airport
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
    cout << "\t\t\tFLIGHTS" << endl;
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    if (infile.is_open())
    {
        cout << endl;
        cout << "\t\t\t\t";
        for (int i = 0; i < 70; i++)
        {
            cout << "-";
        }
        cout << endl;

        cout << "\t\t\t\t    \t| Flight ID\t| Destination\t\t| Departure Time" << endl;

        cout << "\t\t\t\t";
        for (int i = 0; i < 70; i++)
        {
            cout << "-";
        }
        cout << endl;

        //get data from text file
        while (getline(infile, line))
        {
            infile >> plane[i].id >> plane[i].destination >> plane[i].time;

            if (plane[i].destination == "kl")
            {
                plane[i].destination = "kuala lumpur";
            }
            else if (plane[i].destination == "kedah")
            {
                plane[i].destination = "kedah\t";
            }
            else if (plane[i].destination == "johor")
            {
                plane[i].destination = "johor\t";
            }
            i++;
        }

        //sort the data
        for (int j = 0; j < i - 1; j++)
        {
            for (int k = 0; k < i - j - 1; k++)
            {
                if (plane[k].destination > plane[k + 1].destination || ((plane[k].destination == plane[k + 1].destination) && plane[k].time > plane[k + 1].time))
                {
                    swap(plane[k], plane[k + 1]);
                }
            }
        }

        //display out all the data
        for (int l = 0; l < i; l++)
        {
            cout << "\t\t\t\t" << l + 1 << "\t| " << plane[l].id << "\t\t| " << plane[l].destination << "\t\t| " << plane[l].time << endl;
            Sleep(250);
        }

        if (i == 0)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\t\tNo flights available..." << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }

        cout << "\t\t\t\t";
        for (int i = 0; i < 70; i++)
        {
            cout << "-";
        }
        cout << endl;
        infile.close();
    }
    else
    {
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
        cout << "\t\t\t\t\tflight.txt is missing...Please try again." << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        ofstream outfile("flight.txt", ios::app);
        outfile << "flight details";
        outfile.close();
        Sleep(1500);
        showFlight();
    }

    Sleep(1500);
    cout << endl;
    cout << "\t\t\t\t\t[1] Book Flight" << endl;
    cout << "\t\t\t\t\t[2] Edit Flight" << endl;
    cout << "\t\t\t\t\t[0] Back" << endl;

    do
    {
        cout << endl << "\t\t\t\t\tEnter here: ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> choice;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //error due to invalid input
        if (cin.fail())
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\t\tInvalid input" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cin.clear();
            cin.ignore(10000, '\n');
            Sleep(1500);
        }
        else if (choice < 0 || choice > 2)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\t\tInvalid input" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
        }
        //back to main menu
        else if (choice == 0)
        {
            system("cls");
            cout << endl << "\t\t\tHeading to Main Menu..." << endl;
            Sleep(1500);
            main();
        }
        //book ticket
        else if (choice == 1)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            login();
        }
        //enter flight management menu
        else if (choice == 2)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            adminLogin();
            flightDetails();
        }
        else
        {
            fail = true;
        }
    } while (!fail);
}

void showUser()
{
    system("cls");
    cout << endl;

    int choice;
    ifstream infile("user.txt");
    userAcc user[100];
    string line;
    int i = 0;
    bool fail = false;

    //display out all registered users
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
    cout << "\t\t\tUSER ACCOUNT DETAILS" << endl << endl;
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    if (infile.is_open())
    {
        //get data from text file
        while (getline(infile, line))
        {
            infile >> user[i].username >> user[i].password;
            i++;
        }

        cout << "\t\t\t\t";
        for (int j = 0; j < 40; j++)
        {
            cout << "-";
        }
        cout << endl;
        cout << "\t\t\t\t  \t| Username\t| Password" << endl;

        cout << "\t\t\t\t";
        for (int j = 0; j < 40; j++)
        {
            cout << "-";
        }
        cout << endl;

        for (int k = 0; k < i; k++)
        {
            //display out the data
            cout << "\t\t\t\t" << k + 1 << "\t| " << user[k].username << "\t\t| " << user[k].password << endl;
            Sleep(250);
        }

        cout << "\t\t\t\t";
        for (int j = 0; j < 40; j++)
        {
            cout << "-";
        }
        cout << endl;
    }
    else
    {
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
        cout << "user.txt file is not found." << endl;
        cout << "Please try again later." << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        Sleep(1500);
        exit(0);
    }

    cout << endl;
    cout << "\t\t\t\t\t[0] Back" << endl;

    do
    {
        cout << endl << "\t\t\t\t\tEnter here: ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> choice;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //error due to invalid input
        if (cin.fail())
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\t\tInvalid input" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cin.clear();
            cin.ignore(10000, '\n');
            Sleep(1500);
        }
        else if (choice != 0)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\t\tInvalid input" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
        }
        //back to main menu
        else if (choice == 0)
        {
            system("cls");
            cout << endl << "\t\t\tHeading to Main Menu..." << endl;
            Sleep(1500);
            main();
        }
        else
        {
            fail = true;
        }

    } while (!fail);
}

void flightDetails()
{
    int choice;
    bool fail = false;

    //flights management menu
    do
    {
        system("cls");
        cout << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << "\t\t\tFLIGHT DETAILS MANAGEMENT" << endl << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << "\t\t\t\t[1] Add Flight" << endl;
        cout << "\t\t\t\t[2] Delete Flight" << endl;
        cout << "\t\t\t\t[0] Back" << endl;
        cout << endl << "\t\t\t\tEnter Here: ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> choice;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //error due to invalid input
        if (cin.fail())
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input." << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cin.clear();
            cin.ignore(10000, '\n');
            Sleep(1500);
        }
        else if (choice < 0 || choice > 2)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input." << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
        }
        //add new flight
        else if (choice == 1)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            addFlight();
        }
        //remove flight
        else if (choice == 2)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            removeFlight();
        }
        //back to main menu
        else if (choice == 0)
        {
            system("cls");
            cout << endl << "\t\t\tHeading to Main Menu..." << endl;
            Sleep(1500);
            main();
        }
        else
        {
            fail = true;
        }
    } while (!fail);
}

void addFlight()
{
    system("cls");
    cout << endl;
    
    int flightNo;
    string destination1, time1;
    string destination, time;
    int choice, choice1;
    string choice2;
    int totalFlight = 0;
    string line;
    bool valid = false, fail = false, fail1 = false;
    int id[100];
    string dest[100];
    int i = 0;
    ifstream infile("flight.txt");
    ofstream outfile("flight.txt", ios::app);

    //add new flight
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
    cout << "\t\t\tADD NEW FLIGHT" << endl << endl;
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    //ask user to input flight destination
    do
    {
        cout << "\t\t\t\t[1] Melaka" << endl;
        cout << "\t\t\t\t[2] Selangor" << endl;
        cout << "\t\t\t\t[3] Kuala Lumpur" << endl;
        cout << "\t\t\t\t[4] Penang" << endl;
        cout << "\t\t\t\t[5] Johor" << endl;
        cout << "\t\t\t\t[6] Kedah" << endl;
        cout << endl << "\t\t\t\t[0] Back" << endl;
        cout << endl << "\t\t\t\tEnter Flight Destination: ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> choice1;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //error due to invalid input
        if (cin.fail())
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input." << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
            cin.clear();
            cin.ignore(10000, '\n');
            addFlight();
        }
        else if (choice1 < 0 || choice1 > 6)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input." << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
            addFlight();
        }
        //convert user input into actual word of destination
        else if (choice1 == 1)
        {
            destination = "melaka";
            fail = true;
        }
        else if (choice1 == 2)
        {
            destination = "selangor";
            fail = true;
        }
        else if (choice1 == 3)
        {
            destination = "kl";
            fail = true;
        }
        else if (choice1 == 4)
        {
            destination = "penang";
            fail = true;
        }
        else if (choice1 == 5)
        {
            destination = "johor";
            fail = true;
        }
        else if (choice1 == 6)
        {
            destination = "kedah";
            fail = true;
        }
        //back to previous page
        else if (choice1 == 0)
        {
            flightDetails();
        }
    } while (!fail);
    
    //ask user to enter flight departure time
    while (!valid)
    {
        cout << "\t\t\t\tEnter Flight Departure Time (24-hours Format): ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> time;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //invalid time input
        if (time == "0")
        {
            cout << "\t\t\t\tLoading..." << endl;
            Sleep(1500);
            flightDetails();
        }
        else if (time.length() != 4)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid Input" << endl << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
        }
        else
        {
            int hours = (time[0] - '0') * 10 + (time[1] - '0');
            int minutes = (time[2] - '0') * 10 + (time[3] - '0');

            //invalid time input
            if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
            {
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
                cout << "\t\t\t\tInvalid Input" << endl << endl;
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                Sleep(1500);
            }
            else
            {
                if (infile.is_open())
                {
                    //check whether the flight exist or not
                    while (getline(infile, line))
                    {
                        infile >> flightNo >> destination1 >> time1;
                        id[i] = flightNo;
                        dest[i] = destination1;
                        i++;

                        //fligth existed
                        if ((time == time1) && (destination == destination1))
                        {
                            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
                            cout << endl << "\t\t\t\tFlight already existed. Please try again." << endl;
                            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                            Sleep(1500);
                            addFlight();
                        }
                    }
                    valid = true;
                }
                else
                {
                    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
                    cout << "\t\t\t\tflight.txt file is missing." << endl;
                    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    Sleep(1500);
                    main();
                }
            }
        }
    }
    
    int newID = 1;
    bool newId = false;
    
    //generate random numbers for flight id
    while (!newId)
    {
        newID = rand() % 99 + 1;

        for (int j = 0; j < i; j++)
        {
            if ((newID == id[j]) && (destination == dest[j]))
            {
                newID = rand() % 99 + 1;
            }
            else
            {
                newId = true;
            }
        }
    }

    cout << endl;
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_RED);
    cout << "\t\t\t\tPlease check the details of the flight:" << endl;
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "\t\t\t\t\tFlight ID\t: " << newID << endl;
    cout << "\t\t\t\t\tDestination\t: " << destination << endl;
    cout << "\t\t\t\t\tDepature Time\t: " << time << endl;
    cout << endl;
    Sleep(1500);

    //add flight confirmation
    cout << "\t\t\t\tAre you sure to add this flight? (y/n): ";
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
    cin >> choice2;
    cin.ignore(10000, '\n');
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    
    //confirm to add
    if (choice2 == "y" || choice2 == "Y")
    {
        if (outfile.is_open())
        {
            outfile << endl << newID << " " << destination << " " << time;
            outfile.close();
            cout << "\t\t\t\tAdding..." << endl;
            Sleep(1500);
            system("cls");
        }
        else
        {
            ofstream outfile("flight.txt", ios::app);
            outfile << "Flight Details";
            outfile << endl << newID << " " << destination << " " << time;
            outfile.close();
            cout << "\t\t\t\tAdding..." << endl;
            Sleep(1500);
            system("cls");
            addFlight();
        }
    }
    //cancel adding
    else if (choice2 == "n" || choice2 == "N")
    {
        cout << "\t\t\t\tLoading..." << endl;
        Sleep(1500);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
        cout << "\t\t\t\tPlease try again." << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        Sleep(1500);
        addFlight();
    }
    //error due to invalid input
    else
    {
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
        cout << "\t\t\t\tInvalid Input." << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        Sleep(1500);
        addFlight();
    }

    //flight added successful
    do
    {
        system("cls");
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
        cout << endl << "\t\t\tAdded successfully." << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << endl;
        cout << "\t\t\t\t[1] Add Another Flight" << endl;
        cout << "\t\t\t\t[2] Show All Flights" << endl;
        cout << "\t\t\t\t[0] Back" << endl;
        cout << endl << "\t\t\t\tEnter here: ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> choice;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //error due to invalid input
        if (cin.fail())
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cin.clear();
            cin.ignore(10000, '\n');
            Sleep(1500);
        }
        else if (choice < 0 || choice > 2)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
        }
        //back to previous page
        else if (choice == 0)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            flightDetails();
        }
        //add another flight
        else if (choice == 1)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            addFlight();
        }
        //view all flights
        else if (choice == 2)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            showFlight();
        }
    } while (!fail1);
}

void removeFlight()
{
    system("cls");
    cout << endl;

    int choice, choice1;
    int destination;
    string destination1, line, destination2, time, time1;
    int flightNo;
    int id[100];
    int i = 0;
    bool fail = false, fail1 = false, found = false, fail2 = false;

    ifstream infile("flight.txt");

    //ask user to enter destination of flight to be removed
    do
    {
        system("cls");
        cout << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << "\t\t\tDELETE FLIGHT" << endl << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        cout << "\t\t\t\t[1] Melaka" << endl;
        cout << "\t\t\t\t[2] Selangor" << endl;
        cout << "\t\t\t\t[3] Kuala Lumpur" << endl;
        cout << "\t\t\t\t[4] Penang" << endl;
        cout << "\t\t\t\t[5] Johor" << endl;
        cout << "\t\t\t\t[6] Kedah" << endl;
        cout << endl << "\t\t\t\t[0] Back" << endl;

        cout << endl << "\t\t\t\tSelect your destination: ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> destination;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //error due to invalid iput
        if (cin.fail())
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input." << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cin.clear();
            cin.ignore(10000, '\n');
            Sleep(1500);
        }
        else if (destination < 0 || destination > 6)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input." << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
        }
        //convert user input into actual word of destination
        else if (destination == 1)
        {
            destination1 = "melaka";
            fail = true;
        }
        else if (destination == 2)
        {
            destination1 = "selangor";
            fail = true;
        }
        else if (destination == 3)
        {
            destination1 = "kl";
            fail = true;
        }
        else if (destination == 4)
        {
            destination1 = "penang";
            fail = true;
        }
        else if (destination == 5)
        {
            destination1 = "johor";
            fail = true;
        }
        else if (destination == 6)
        {
            destination1 = "kedah";
            fail = true;
        }
        //back to previous page
        else if (destination == 0)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            flightDetails();
        }
        else
        {
            fail = true;
        }
    } while (!fail);

    //display all flights of the selected destination
    system("cls");
    cout << endl;
    cout << "\t\t\tDestination: " << destination1 << endl;
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
    cout << endl << "\t\t\t\tList of Flights" << endl;
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    if (infile.is_open())
    {
        cout << endl;
        cout << "\t\t\t\t";
        for (int i = 0; i < 35; i++)
        {
            cout << "-";
        }
        cout << endl;

        cout << "\t\t\t\tFlight ID\t|Flight Time" << endl;

        cout << "\t\t\t\t";
        for (int i = 0; i < 35; i++)
        {
            cout << "-";
        }
        cout << endl;

        //get data from text file
        while (getline(infile, line))
        {

            infile >> flightNo >> destination2 >> time;

            //add flight with selected destination into an array
            if (destination1 == destination2)
            {
                cout << "\t\t\t\t" << flightNo << "\t\t|" << time << endl;
                id[i] = flightNo;
                i++;
                Sleep(250);
            }
        }
        cout << "\t\t\t\t";
        for (int i = 0; i < 35; i++)
        {
            cout << "-";
        }
        cout << endl;
        infile.close();
    }


    Sleep(1500);
    cout << endl;
    cout << "\t\t\t\t[0] Back" << endl;
    cout << "\t\t\t\tWhich flight do you want to remove?" << endl;

    //ask user to select flight to be removed
    do
    {
        cout << endl;
        cout << "\t\t\t\tFlight ID: ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> choice1;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //error due to invalid input
        if (cin.fail())
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cin.clear();
            cin.ignore(10000, '\n');
            Sleep(1500);
        }
        //back to previous page
        else if (choice1 == 0)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            removeFlight();
        }
        else
        {
            fail1 = true;
        }
    } while (!fail1);

    //check whether input flight is in the array
    for (int j = 0; j < i; j++)
    {
        //flight found
        if (choice1 == id[j])
        {
            found = true;
            cout << "\t\t\t\tRemoving..." << endl;
            Sleep(1500);
            break;
        }
        else
        {
            continue;
        }
    }
    //flight not found
    if (!found)
    {
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
        cout << "\t\t\t\tInvalid Flight ID." << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        Sleep(1500);
        removeFlight();
    }

    infile.open("flight.txt");
    ofstream tempfile("temp.txt");

    tempfile << "Flight Details";

    //update data into a temporary file
    if (infile.is_open() && tempfile.is_open())
    {
        while (getline(infile, line))
        {
            infile >> flightNo >> destination2 >> time;

            if ((choice1 == flightNo) && (destination1 == destination2))
            {
                time1 = time;
            }

            //remove that flight
            if ((choice1 == flightNo) && (destination1 == destination2) && (time1 == time))
            {
                Sleep(1500);
            }
            else
            {
                tempfile << endl << flightNo << " " << destination2 << " " << time;
            }
        }
        infile.close();
        tempfile.close();
    }

    //copy data from temp file into actual text file
    updateFlightTxt();

    do
    {
        system("cls");
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
        cout << endl << "\t\t\tFlight removed successfully" << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << endl;
        cout << "\t\t\t\t[1] Remove Another Flight" << endl;
        cout << "\t\t\t\t[2] Show All Flights" << endl;
        cout << "\t\t\t\t[0] Back" << endl;
        cout << endl << "\t\t\t\tEnter here: ";
        SetConsoleTextAttribute(consoleHandle,FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> choice;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //error due to invalid input
        if (cin.fail())
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cin.clear();
            cin.ignore(10000, '\n');
            Sleep(1500);
        }
        else if (choice < 0 || choice > 2)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
        }
        //back to previous page
        else if (choice == 0)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            flightDetails();
        }
        //view all flights
        else if (choice == 2)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            showFlight();
        }
        //remove another flight
        else if (choice == 1)
        {
            system("cls");
            cout << endl << "\t\t\tLoading..." << endl;
            Sleep(1500);
            removeFlight();
        }
        else
        {
            fail2 = true;
        }
    } while (!fail2);
}

void adminLogin()
{
    system("cls");
    cout << endl;

    string username, password;

    //default username and password for admin
    string username1 = "admin";
    string password1 = "admin";

    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
    cout << "\t\t\tADMIN LOGIN" << endl << endl;
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    cout << "\t\t\t\t[0] Back" << endl << endl;
    cout << "\t\t\t\tAdmin Username: ";
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
    cin >> username;
    cin.ignore(10000, '\n');
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    //username matched
    if (username == username1)
    {
        cout << "\t\t\t\tPassword: ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> password;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //back to main menu
        if (password == "0")
        {
            system("cls");
            cout << endl << "\t\t\tHeading back Main Menu..." << endl;
            Sleep(1500);
            main();
        }
        //password incorrect
        else if (password != password1)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << endl << "\t\t\t\tWrong password." << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
            adminLogin();
        }
        //correct password
        else
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
            cout << endl << "\t\t\t\tLogging In..." << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
        }
    }
    //back to main menu
    else if (username == "0")
    {
        system("cls");
        cout << endl << "\t\t\tHeading back to Main Menu..." << endl;
        Sleep(1500);
        main();
    }
    //invalid username
    else
    {
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
        cout << endl << "\t\t\t\tInvalid username." << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        Sleep(1500);
        adminLogin();
    }
}

void login()
{
    system("cls");
    string username, password;
    string username1, password1, line;
    int choice;
    ifstream infile("user.txt");
    bool fail = false;

    if (infile.is_open())
    {
        //user login page
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << endl << "\t\t\tLOGIN" << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << endl;
        cout << "\t\t\t\t[1] Create New Account" << endl;
        cout << "\t\t\t\t[0] Back" << endl;
        cout << endl;
        cout << "\t\t\t\tUsername: ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> username;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //create new account
        if (username == "1")
        {
            signUp();
        }
        //back to main menu
        else if (username == "0")
        {
            system("cls");
            cout << endl << "\t\t\tHeading to Main Menu..." << endl;
            Sleep(1500);
            main();
        }

        //get data from text file
        while (getline(infile, line))
        {
            infile >> username1 >> password1;
            if (username == username1)
            {
                break;
            }
        }

        //if username existed
        if (username == username1)
        {
            cout << "\t\t\t\tPassword: ";
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
            cin >> password;
            cin.ignore(10000, '\n');
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

            //back
            if (password == "0")
            {
                Sleep(1500);
                login();
            }
            //incorrect password
            else if (password != password1)
            {
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
                cout << "\t\t\t\tWrong password. Please try again." << endl;
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                Sleep(1500);
                login();
            }
            //correct password
            else
            {
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
                cout << endl << "\t\t\t\tLogging In..." << endl;
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                Sleep(1500);
                bookTicket(username);
            }
        }
        //username not fount in text file
        else
        {
            Sleep(1500);
            do
            {
                system("cls");
                cout << endl;
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
                cout << "\t\t\tUser not found" << endl << endl;
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cout << "\t\t\t\t[1] Create New Account" << endl;
                cout << "\t\t\t\t[2] Try Again" << endl;
                cout << "\t\t\t\t[0] Back" << endl;
                cout << endl << "\t\t\t\tEnter here: ";
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
                cin >> choice;
                cin.ignore(10000, '\n');
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                //error due to invalid input
                if (cin.fail())
                {
                    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
                    cout << "\t\t\t\tInvalid input" << endl;
                    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    cin.clear();
                    cin.ignore(10000, '\n');
                    Sleep(1500);
                }
                else if (choice < 0 || choice > 2)
                {
                    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
                    cout << "\t\t\t\tInvalid input" << endl;
                    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    Sleep(1500);
                }
                //create new account
                else if (choice == 1)
                {
                    system("cls");
                    cout << endl << "\t\t\tLoading..." << endl;
                    Sleep(1500);
                    signUp();
                }
                //try again
                else if (choice == 2)
                {
                    system("cls");
                    cout << endl << "\t\t\tLoading..." << endl;
                    Sleep(1500);
                    login();
                }
                //back to main menu
                else if (choice == 0)
                {
                    system("cls");
                    cout << endl << "\t\t\tHeading to Main Menu..." << endl;
                    Sleep(1500);
                    main();
                }
                else
                {
                    fail = true;
                }

            } while (!fail);
        }
    }
    else
    {
        ofstream outfile("user.txt", ios::app);
        outfile << "username password";
        outfile.close();
        login();
    }
    infile.close();
}

void signUp()
{
    system("cls");
    string username, password, re_enter;
    string username1, password1, line;
    bool hit = false, match = false;
    ifstream infile("user.txt");
    ofstream outfile;
    outfile.open("user.txt", ios::app);

    //sign up page
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
    cout << endl << "\t\t\tCREATE NEW ACCOUNT" << endl;
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    //ask user to enter new username
    cout << endl;
    cout << "\t\t\t\t[0] Cancel" << endl;
    cout << endl;
    cout << "\t\t\t\tEnter Username (without spacing): ";
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
    cin >> username;
    cin.ignore(10000, '\n');
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    //cancel sign up
    if (username == "0")
    {
        system("cls");
        cout << endl << "\t\t\tLoading..." << endl;
        Sleep(1500);
        login();
    }

    //check whether account already created
    if (infile.is_open())
    {
        while (getline(infile, line))
        {
            infile >> username1 >> password1;
            if (username == username1)
            {
                break;
            }
        }
        //account already existed
        if (username == username1)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tAccount already existed" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
            infile.close();
            login();
        }
        //account not yet created
        else
        {
            while (!hit)
            {
                //create new passowrd
                cout << "\t\t\t\tEnter password: ";
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
                cin >> password;
                cin.ignore(10000, '\n');
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                //back
                if (password == "0")
                {
                    system("cls");
                    cout << endl << "\t\t\tLoading..." << endl;
                    Sleep(1500);
                    login();
                }

                //check whether password is valid or not
                if (password.length() >= 8)
                {
                    hit = true;
                    while (!match)
                    {
                        cout << "\t\t\t\tRe-enter password: ";
                        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
                        cin >> re_enter;
                        cin.ignore(10000, '\n');
                        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                        //back
                        if (re_enter == "0")
                        {
                            system("cls");
                            cout << endl << "\t\t\tLoading..." << endl;
                            Sleep(1500);
                            login();
                        }
                        //password matched
                        else if (re_enter == password)
                        {
                            match = true;
                        }
                        //password does not matched
                        else
                        {
                            cout << endl;
                            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
                            cout << "\t\t\t\tPassword does not match" << endl;
                            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                            Sleep(1500);
                        }
                    }
                }
                //invalid password entered
                else
                {
                    cout << endl;
                    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
                    cout << "\t\t\t\tMinimum 8 characters. Please try again." << endl;
                    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
            }

            //update data into text file
            outfile << endl << username << " " << password;
            outfile.close();
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
            cout << endl << "\t\t\t\tAccount created successfully" << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
            login();
        }
    }
    else
    {
        ofstream outfile("user.txt", ios::app);
        outfile << "username password";
        outfile.close();
        signUp();
    }
    infile.close();
}

void updateFlightTxt()
{
    //copy data from temporary file into another text file
    ifstream infile("temp.txt");
    ofstream outfile("flight.txt");
    string line;

    if (infile.is_open() && outfile.is_open())
    {
        while (getline(infile, line))
        {
            outfile << line;
            if (!infile.eof())
            {
                outfile << endl;
            }
        }
    }
}

void report()
{
    system("cls");
    cout << endl;

    //generate a simple report
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
    cout << "\t\t\tFLIGHT BOOKING REPORT" << endl;
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    ifstream infile("reserved.txt");
    reserved booked[100];
    string line;
    int m = 0, choice;
    bool fail = false;
    int kl = 0, kd = 0, sl = 0, ml = 0, pn = 0, jh = 0;
    int total = 0;

    if (infile.is_open())
    {
        //get booking data from text file
        while (getline(infile, line))
        {
            infile >> booked[m].username >> booked[m].id >> booked[m].destination >> booked[m].time >> booked[m].seat >> booked[m].price;
            m++;
        }

        //sort the data
        for (int j = 0; j < m - 1; j++)
        {
            for (int k = 0; k < m - j - 1; k++)
            {
                if (booked[k].username > booked[k + 1].username || ((booked[k].username == booked[k + 1].username) && booked[k].destination > booked[k + 1].destination) || ((booked[k].username == booked[k + 1].username) && (booked[k].destination == booked[k + 1].destination)) && booked[k].time > booked[k + 1].time)
                {
                    swap(booked[k], booked[k + 1]);
                }
            }
        }

        cout << endl;
        cout << "\t\t\t\t";
        for (int i = 0; i < 120; i++)
        {
            cout << "-";
        }
        cout << endl;

        cout << "\t\t\t\t  \t| Flight ID\t| Destination\t\t| Depature Time\t| Customer\t\t| Seat Type\t| Price" << endl;

        cout << "\t\t\t\t";
        for (int i = 0; i < 120; i++)
        {
            cout << "-";
        }
        cout << endl;

        //calculate the total fligth for each destination
        for (int j = 0; j < m; j++)
        {
            if (booked[j].destination == "kl")
            {
                booked[j].destination = "kuala lumpur";
                kl++;
            }
            else if (booked[j].destination == "kedah")
            {
                booked[j].destination = "kedah\t";
                kd++;
            }
            else if (booked[j].destination == "johor")
            {
                booked[j].destination = "johor\t";
                jh++;
            }
            else if (booked[j].destination == "selangor")
            {
                sl++;
            }
            else if (booked[j].destination == "penang")
            {
                pn++;
            }
            else if (booked[j].destination == "melaka")
            {
                ml++;
            }

            //calculate total price of all tickets
            total += booked[j].price;
        }

        //display out all the data
        for (int l = 0; l < m; l++)
        {
            cout << "\t\t\t\t" << l + 1 << "\t| " << booked[l].id << "\t\t| " << booked[l].destination << "\t\t| " << booked[l].time;
            cout << "\t\t| " << booked[l].username << "\t\t\t| " << booked[l].seat << "\t| " << booked[l].price << endl;
            Sleep(250);
        }

        cout << "\t\t\t\t";
        for (int i = 0; i < 120; i++)
        {
            cout << "-";
        }
        cout << endl;

        cout << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << "\t\t\t\tSummary" << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        cout << "\t\t\t\t";
        for (int i = 0; i < 120; i++)
        {
            cout << "-";
        }

        //show the summary data of the report
        cout << endl;
        cout << "\t\t\t\t\tSelangor\t: " << sl << endl;
        cout << "\t\t\t\t\tKuala Lumpur\t: " << kl << endl;
        cout << "\t\t\t\t\tJohor\t\t: " << jh << endl;
        cout << "\t\t\t\t\tPenang\t\t: " << pn << endl;
        cout << "\t\t\t\t\tKedah\t\t: " << kd << endl;
        cout << "\t\t\t\t\tMelaka\t\t: " << ml << endl;
        cout << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << "\t\t\t\t\tTotal Flight Ticket Booked\t: " << m << endl;
        cout << "\t\t\t\t\tTotal Profit\t\t\t: RM" << total << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        cout << "\t\t\t\t";
        for (int i = 0; i < 120; i++)
        {
            cout << "-";
        }
        cout << endl;

        Sleep(1500);
        cout << endl;
        cout << "\t\t\t\t\t[1] Print Report" << endl;
        cout << "\t\t\t\t\t[0] Back" << endl;

        do
        {
            cout << endl << "\t\t\t\t\tEnter here: ";
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
            cin >> choice;
            cin.ignore(10000, '\n');
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

            //error due to invalid input
            if (cin.fail())
            {
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
                cout << "\t\t\t\t\tInvalid input" << endl;
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cin.clear();
                cin.ignore(10000, '\n');
                Sleep(1500);
            }
            else if (choice < 0 || choice > 1)
            {
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
                cout << "\t\t\t\t\tInvalid input" << endl;
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                Sleep(1500);
            }
            //back to previous page
            else if (choice == 0)
            {
                system("cls");
                cout << endl << "\t\t\tHeading to main menu..." << endl;
                Sleep(1500);
                main();
            }
            //print report
            else if (choice == 1)
            {
                system("cls");
                cout << endl << "\t\t\tPrinting..." << endl;
                Sleep(1500);
                cout << endl << "\t\t\tHeading back..." << endl;
                Sleep(1500);
                main();
            }
        } while (!fail);

        infile.close();
    }
    else
    {
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
        cout << "\t\t\t\tMissing 'reserved.txt' file. Please try again." << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        exit(0);
    }
}

int seat(string username, string destination)
{
    int type;
    bool fail = false;

    //seat selection menu
    do
    {
        int price;
        if (destination == "melaka")
        {
            price = 52;
        }
        else if (destination == "selangor")
        {
            price = 46;
        }
        else if (destination == "kl")
        {
            price = 50;
        }
        else if (destination == "penang")
        {
            price = 68;
        }
        else if (destination == "johor")
        {
            price = 88;
        }
        else if (destination == "kedah")
        {
            price = 58;
        }

        system("cls");
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << endl << "\t\t\tSEAT" << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << endl << "\t\t\t\tDestination: " << destination << endl;
        cout << endl;
        cout << "\t\t\t\t[1] Premium Seat\t RM" << price << endl;
        cout << "\t\t\t\t[2] Standard Seat\t RM" << price / 2 << endl;
        cout << "\t\t\t\t[0] Cancel" << endl;
        cout << endl << "\t\t\t\tPlease select type of seat: ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> type;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //error due to invalid input
        if (cin.fail())
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input." << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cin.clear();
            cin.ignore(10000, '\n');
            Sleep(1500);
        }
        else if (type < 0 || type > 2)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid input." << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
        }
        //cancel selection
        else if (type == 0)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE);
            cout << "\t\t\t\tCancelling..." << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
            bookTicket(username);
        }
        //select premium seat
        else if (type == 1)
        {
            fail = true;
            return price;
        }
        //select standard seat
        else if (type == 2)
        {
            fail = true;
            return price / 2;
        }
    } while (!fail);
}

bool payment(string username, int price)

{
    int method;
    bool success = false, fail = false;
    string cardNum, expiry, cvv;
    string phoneNum, pin;
    string bankName, id, password;
    int bank;
    bool fail1 = false;
    
    //ask user to choose payment method
    do
    {
        system("cls");
        cout << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << "\t\t\tPAYMENT" << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << endl << "\t\t\t\t[1] Credit Card / Debit Card" << endl;
        cout << "\t\t\t\t[2] Online Banking" << endl;
        cout << "\t\t\t\t[0] Cancel" << endl;
        cout << endl << "\t\t\t\tPayment method: ";
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> method;
        cin.ignore(10000, '\n');
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        //error due to invalid input
        if (cin.fail())
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid Input." << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cin.clear();
            cin.ignore(10000, '\n');
            Sleep(1500);
        }
        else if (method < 0 || method > 2)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
            cout << "\t\t\t\tInvalid Input." << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
        }
        //pay by card
        else if (method == 1)
        {
            cout << endl << "\t\t\t\tProcessing..." << endl;
            Sleep(1500);

            //ask user to enter card number
            do
            {
                system("cls");
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
                cout << endl << "\t\t\tCREDIT / DEBIT CARD" << endl;
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cout << "\t\t\t\t[0] Back" << endl;
                cout << endl << "\t\t\t\tTotal amount: RM" << price << ".00" << endl;
                cout << endl << "\t\t\t\tCard Number (16 digits): ";
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
                cin >> cardNum;
                cin.ignore(10000, '\n');
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                //back
                if (cardNum == "0")
                {
                    cout << "\t\t\t\tLoading..." << endl;
                    Sleep(1500);
                    payment(username, price);
                }
                //valid card number
                else if (cardNum.length() == 16)
                {
                    for (int i = 0; i < 16; i++)
                    {
                        if (!isdigit(cardNum[i]))
                        {
                            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
                            cout << "\t\t\t\tInvalid card number." << endl;
                            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                            Sleep(1500);
                            payment(username, price);
                        }
                    }
                    //ask user to enter cvv pin
                    cout << "\t\t\t\tCVV (3 digits): ";
                    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
                    cin >> cvv;
                    cin.ignore(10000, '\n');
                    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                    //invalid cvv pin
                    if (cvv.length() != 3)
                    {
                        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
                        cout << "\t\t\t\tInvalid Input." << endl;
                        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                        Sleep(1500);
                    }
                    else
                    {
                        for (int j = 0; j < 3; j++)
                        {
                            //invalid cvv pin
                            if (!isdigit(cvv[j]))
                            {
                                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
                                cout << "\t\t\t\tInvalid Input." << endl;
                                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                                Sleep(1500);
                                break;
                            }
                            //valid cvv pin
                            else
                            {
                                fail = true;
                            }
                        }
                    }
                }
                //invalid card number
                else
                {
                    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
                    cout << "\t\t\t\tInvalid card number." << endl;
                    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    Sleep(1500);
                }
            } while (!fail);

            cout << endl << "\t\t\t\tProcessing..." << endl;
            Sleep(1500);
            success = true;
            return true;
        }
        //pay by online banking
        else if (method == 2)
        {
            cout << endl << "\t\t\t\tProcessing..." << endl;
            Sleep(1500);

            //ask user to choose bank
            do
            {
                system("cls");
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
                cout << endl << "\t\t\tONLINE BANKING" << endl;
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                cout << endl << "\t\t\t\t[1] Maybank" << endl;
                cout << "\t\t\t\t[2] Public Bank" << endl;
                cout << "\t\t\t\t[3] CIMB Bank" << endl;
                cout << endl << "\t\t\t\t[0] Back" << endl;
                cout << "\t\t\t\tSelect bank: ";
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
                cin >> bank;
                cin.ignore(10000, '\n');
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                //error due to invalid input
                if (cin.fail())
                {
                    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
                    cout << "\t\t\t\tInvalid input." << endl;
                    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    cin.clear();
                    cin.ignore(10000, '\n');
                    Sleep(1500);
                }
                else if (bank < 0 || bank > 3)
                {
                    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
                    cout << "\t\t\t\tInvalid input." << endl;
                    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    Sleep(1500);
                }
                //back
                else if (bank == 0)
                {
                    cout << "\t\t\t\tLoading..." << endl;
                    Sleep(1500);
                    payment(username, price);
                }
                //maybank
                else if (bank == 1)
                {
                    bankName = "Maybank";
                    cout << endl << "\t\t\t\tConnecting to " << bankName << "..." << endl;
                    Sleep(1500);

                    success = false;
                    do
                    {
                        //online banking page
                        system("cls");
                        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
                        cout << endl << " \t\t\t" << bankName << endl;
                        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                        cout << endl << "\t\t\t\tTotal amount: RM" << price << ".00" << endl;
                        cout << "\t\t\t\t[0] Back" << endl;

                        //ask user to enter bank username
                        cout << endl;
                        cout << "\t\t\t\tUsername: ";
                        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
                        cin >> id;
                        cin.ignore(10000, '\n');
                        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                        if (id == "0")
                        {
                            cout << endl << "\t\t\t\tLoading..." << endl;
                            Sleep(1500);
                            break;
                        }
                        else
                        {
                            //ask user to enter bank password
                            cout << "\t\t\t\tPassword: ";
                            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
                            cin >> password;
                            cin.ignore(10000, '\n');
                            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                            if (password == "0")
                            {
                                cout << endl << "\t\t\t\tLoading..." << endl;
                                Sleep(1500);
                            }
                            else
                            {
                                success = true;
                                fail1 = true;
                            }
                        }
                    } while (!success);
                }
                //public bank
                else if (bank == 2)
                {
                    bankName = "Public Bank";
                    cout << endl << "\t\t\t\tConnecting to " << bankName << "..." << endl;
                    Sleep(1500);

                    success = false;
                    do
                    {
                        //online banking page
                        system("cls");
                        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
                        cout << endl << " \t\t\t" << bankName << endl;
                        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                        cout << endl << "\t\t\t\tTotal amount: RM" << price << ".00" << endl;
                        cout << "\t\t\t\t[0] Back" << endl;

                        //ask user to enter bank username
                        cout << endl;
                        cout << "\t\t\t\tUsername: ";
                        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
                        cin >> id;
                        cin.ignore(10000, '\n');
                        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                        if (id == "0")
                        {
                            cout << endl << "\t\t\t\tLoading..." << endl;
                            Sleep(1500);
                            break;
                        }
                        else
                        {
                            //ask user to enter bank password
                            cout << "\t\t\t\tPassword: ";
                            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
                            cin >> password;
                            cin.ignore(10000, '\n');
                            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                            if (password == "0")
                            {
                                cout << endl << "\t\t\t\tLoading..." << endl;
                                Sleep(1500);
                            }
                            else
                            {
                                success = true;
                                fail1 = true;
                            }
                        }
                    } while (!success);
                }
                //cimb bank
                else if (bank == 3)
                {
                    bankName = "CIMB Bank";
                    cout << endl << "\t\t\t\tConnecting to " << bankName << "..." << endl;
                    Sleep(1500);

                    success = false;
                    do
                    {
                        //online banking page
                        system("cls");
                        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
                        cout << endl << " \t\t\t" << bankName << endl;
                        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                        cout << endl << "\t\t\t\tTotal amount: RM" << price << ".00" << endl;
                        cout << "\t\t\t\t[0] Back" << endl;

                        //ask user to enter bank username
                        cout << endl;
                        cout << "\t\t\t\tUsername: ";
                        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
                        cin >> id;
                        cin.ignore(10000, '\n');
                        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                        if (id == "0")
                        {
                            cout << endl << "\t\t\t\tLoading..." << endl;
                            Sleep(1500);
                            break;
                        }
                        else
                        {
                            //ask user to enter bank password
                            cout << "\t\t\t\tPassword: ";
                            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
                            cin >> password;
                            cin.ignore(10000, '\n');
                            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                            if (password == "0")
                            {
                                cout << endl << "\t\t\t\tLoading..." << endl;
                                Sleep(1500);
                            }
                            else
                            {
                                success = true;
                                fail1 = true;
                            }
                        }
                    } while (!success);
                }
            } while (!fail1);

            cout << endl << "\t\t\t\tProcessing..." << endl;
            Sleep(1500);
            success = true;
            return true;
        }
        //cancel payment
        else if (method == 0)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE);
            cout << endl << "\t\t\t\tCancelling..." << endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            Sleep(1500);
            bookTicket(username);
        }
        else
        {
            return false;
        }
    } while (!success);
}

//decoration
void display()
{
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "\t\t\t\t\t\t\t                  5.                                                  " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t                  &^                                                  " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t                  &^                                                  " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t                  &^                                                  " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t           YBBBBBB@&BBBBB?                 !PY~.     .~J~             " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t           &@~~~~~~~~~~!@B                  .Y@@&GJG&@&G^             " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t           5@BBBBBBBBBB#@?               .  .!&@@@@&:.                " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t            ?@@@@@@@@@@&^               .P&&@B?:#@@^                  " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t             !@@@@@@@@B:                  G@:   ~@P                   " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t           B@PGGGGGGGGPP@P                ..    .&.                   " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t           #&..........:@G                       :                    " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t           #@&&&&&&&&&&&@G                                            " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t           #&^^^^^^^^^^~@G                                            " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t           #@&&&&&&&&&&&@G                                            " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t           #&          .@G                                            " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t           #&          .@G              5GPPPPPPPPPPPPPPPG.           " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t           #&          .@G              @#.::::::::::::.J@^           " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t    JGGGGGP&@GGGGGGGGGGG@&PGGGGGGGGGGGPG@&PGGGGGGGGGGGGP#@BPGGGGB:    " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t    #P^~~~~^^~~~~~~~~~~~^^~~~~~~~~~~~~~~^^~~~~~~~~~~~~~~^^^~~~~~@~    " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t    #Y.?BBBBBBBBBBB5.^GBBBBBBBBBBB^^BBBBBBBBBBBG:~BBBBBBBBBBBG::&^    " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t    #Y.:^^^^^^^^^^^^::^^^^^^^^^^^^::^^^^^^^^^^^^::^^^^^^^^^^^^::&^    " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t    #Y.J&&&&&&&&&&&G.^#&&&&&&&&&&#~~#&&&&&&&&&&#^!&&&&#:7&&&&#::&^    " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t    #Y.P@@@@@@@@@@@&.~@@@@@@@@@@@@!!@@@@@@@@@@@@^?@@@@@^J@@@@@^:&^    " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t    #Y.?BBBBBBBBBBB5.:GBBBBBBBBBBB^^BBBBBBBBBBBG:7@@@@@:!BBBBG:.&^    " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t.!!!&BJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJG@@@@@5JJJJJJJY@5!!!." << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t!BBBGBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBGGGGGBBBBBBBBBGBBBB!" << endl;
    Sleep(100);
    cout << endl << endl << endl;

    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
    cout << "\t\t\t\t\t[..        [..[........[..          [..       [....     [..       [..[........     [... [......    [....          " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t[..        [..[..      [..       [..   [..  [..    [..  [. [..   [...[..                [..      [..    [..       " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t[..   [.   [..[..      [..      [..       [..        [..[.. [.. [ [..[..                [..    [..        [..     " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t[..  [..   [..[......  [..      [..       [..        [..[..  [..  [..[......            [..    [..        [..     " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t[.. [. [.. [..[..      [..      [..       [..        [..[..   [.  [..[..                [..    [..        [..     " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t[. [.    [....[..      [..       [..   [..  [..     [.. [..       [..[..                [..      [..     [..      " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t[..        [..[........[........   [....      [....     [..       [..[........          [..        [....          " << endl;
    Sleep(100);
    cout << endl;
    cout << "\t\t\t\t[..   [..        [.       [..       [..[.......        [.       [.......         [..       [..[..[...     [..[.." << endl;
    Sleep(100);
    cout << "\t\t\t\t[..  [..        [. ..     [. [..   [...[..    [..     [. ..     [..    [..       [. [..   [...[..[. [..   [..[.." << endl;
    Sleep(100);
    cout << "\t\t\t\t[.. [..        [.  [..    [.. [.. [ [..[..    [..    [.  [..    [..    [..       [.. [.. [ [..[..[.. [..  [..[.." << endl;
    Sleep(100);
    cout << "\t\t\t\t[. [.         [..   [..   [..  [..  [..[.......     [..   [..   [. [..           [..  [..  [..[..[..  [.. [..[.." << endl;
    Sleep(100);
    cout << "\t\t\t\t[..  [..     [...... [..  [..   [.  [..[..         [...... [..  [..  [..         [..   [.  [..[..[..   [. [..[.." << endl;
    Sleep(100);
    cout << "\t\t\t\t[..   [..   [..       [.. [..       [..[..        [..       [.. [..    [..       [..       [..[..[..    [. ..[.." << endl;
    Sleep(100);
    cout << "\t\t\t\t[..     [..[..         [..[..       [..[..       [..         [..[..      [..     [..       [..[..[..      [..[.." << endl;
    Sleep(100);
    cout << endl;
    cout << "\t\t\t\t\t\t      [.       [..[.......    [.......      [....     [.......    [... [......" << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t     [. ..     [..[..    [..  [..    [..  [..    [..  [..    [..       [..    " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t    [.  [..    [..[..    [..  [..    [..[..        [..[..    [..       [..    " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t   [..   [..   [..[. [..      [.......  [..        [..[. [..           [..    " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t  [...... [..  [..[..  [..    [..       [..        [..[..  [..         [..    " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t [..       [.. [..[..    [..  [..         [..     [.. [..    [..       [..    " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t[..         [..[..[..      [..[..           [....     [..      [..     [..    " << endl;
    Sleep(100);
    cout << endl;
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void byebye()
{
    system("cls");
    cout << endl << endl;
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
    cout << "\t\t\t\t\t\t[... [......[..     [..      [.       [...     [..[..   [..       [..      [.. [....     [..     [..     " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t     [..    [..     [..     [. ..     [. [..   [..[..  [..         [..    [..[..    [..  [..     [..     " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t     [..    [..     [..    [.  [..    [.. [..  [..[.. [..           [.. [..[..        [..[..     [..     " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t     [..    [...... [..   [..   [..   [..  [.. [..[. [.               [..  [..        [..[..     [..     " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t     [..    [..     [..  [...... [..  [..   [. [..[..  [..            [..  [..        [..[..     [..     " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t     [..    [..     [.. [..       [.. [..    [. ..[..   [..           [..    [..     [.. [..     [..     " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t     [..    [..     [..[..         [..[..      [..[..     [..         [..      [....       [.....        " << endl;
    Sleep(100);
    cout << endl << endl << endl;
    cout << "\t\t\t\t\t  >=>>=>         >>       >=======> >=======>       >=======> >=>       >=>    >===>    >=>    >=> >===>>=====>  >=>" << endl;
    Sleep(100);
    cout << "\t\t\t\t\t>=>    >=>      >>=>      >=>       >=>             >=>       >=>       >=>  >>    >=>  >=>    >=>      >=>      >=>" << endl;
    Sleep(100);
    cout << "\t\t\t\t\t >=>           >> >=>     >=>       >=>             >=>       >=>       >=> >=>         >=>    >=>      >=>      >=>" << endl;
    Sleep(100);
    cout << "\t\t\t\t\t   >=>        >=>  >=>    >=====>   >=====>         >=====>   >=>       >=> >=>         >=====>>=>      >=>      >> " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t      >=>    >=====>>=>   >=>       >=>             >=>       >=>       >=> >=>   >===> >=>    >=>      >=>      >> " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t>=>    >=>  >=>      >=>  >=>       >=>             >=>       >=>       >=>  >=>    >>  >=>    >=>      >=>         " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t  >=>>=>   >=>        >=> >=>       >=======>       >=>       >=======> >=>   >====>    >=>    >=>      >=>      >=>" << endl;
    Sleep(100);
    cout << endl << endl;
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "\t\t\t\t\t\t\t\t       ...:.                                      " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t\t       ^   :.                                     " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t\t       :    :.                                    " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t\t       :     :.             ........              " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t\t       :      :.       ...           .:.          " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t\t       :       .:....          :~.:?!^7~:         " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t\t     .::..                               ..       " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t\t  .::~:~^.......                           :      " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t\t     ^: .................................. :.  .. " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t\t.:...................^:^:.:.     ..       .!:....." << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t\t       :!:..:7..:~:..^~^...^      ..    ...:!.    " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t\t     .^^   ::7~!^::...~!.           .:~!.^~^:^~:  " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t\t     ~~   ~~.  :7.  ^!^^~!:.^~...^?^  ^!77:   ~Y  " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t\t      :   !~   !J^ ~~    ~7 :!   ^7  .~!?7^.^!?7  " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t\t        ..^!~7?J!  ^!:::!?~   .. .!!7!~^:.^:^^.   " << endl;
    Sleep(100);
    cout << "\t\t\t\t\t\t\t\t             ..  ...~~!!~:         ...            " << endl;
    Sleep(100);
    cout << endl << endl << endl << endl;
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    Sleep(2000);
}
