#include<cstring>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<windows.h>
#include<conio.h>  //empty(); pop_back(); _getch();
#include <iomanip>
#include "structure.h"
using namespace std;


enum Colour{
    Orange,
    Red,
    Yellow,
    LightGreen,
    DarkGreen,
    LightBlue,
    DarkBlue,
    DefaultColor
} ;
//************DECORATED FUNCTION***************
void Color(Colour color ){
    switch(color){
        case 0: cout << "\033[38;2;255;165;0m" ;break;
        case 1:  cout << "\033[38;2;255;69;0m";break;
        case 2:  cout << "\033[38;2;255;215;0m" ;break;
        case 3: cout << "\033[38;2;173;255;47m";break;
        case 4: cout << "\033[38;2;0;255;0m";break;
        case 5: cout << "\033[38;2;0;255;255m";break;
        case 6:cout << "\033[38;2;0;191;255m";break;
        case 7: cout << "\033[0m";break;
    }
}

void setcenter(const string& text, int width) {
    int padding = (width - text.length()) / 2;
    int check = (padding*2)+ text.length() ;
    if (padding > 0) {
        cout <<setfill(' ')<< setw(padding) << "" << text << setw(padding) << "";
        if(check != width ){
            cout << setw(1) <<"";
        }
    } else {
        cout << text ;
    }
}
void title(const string& title){
    Color(LightGreen);
    cout << "\n\t\t\t\t    ------------";
    Color(DarkGreen);
    cout << "------------";
    Color(LightBlue);
    cout << "------------\n";
    cout << "\t\t\t\t    ";

    Color(Yellow);
    setcenter(title,36);
    Color(LightGreen);
    cout << "\n\t\t\t\t    ------------";
    Color(DarkGreen);
    cout << "------------";
    Color(LightBlue);
    cout << "------------\n\n\n";
    Color(DefaultColor);
};

void clearConsole(){
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
         //_WIN32
}
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock())
        ;
}
void date(){
    time_t T = time(NULL);
    struct tm tm = *localtime(&T);
    cout << "\n\n\n";
    Color(Orange);
    cout << "\t\t\t\t\t   Date:" << tm.tm_mday << "/" << tm.tm_mon + 1 << "/" << tm.tm_year + 1900 << endl;
    Color(DefaultColor);
}
void pressEnterToSth(string something){
    int process;
    Color(LightBlue);
    cout << "\t\t\t\t    Press Enter to "<<something << "......";
    cin.get();
    Color(DarkBlue);
    cout << "\n\n\t\t\t\t Loading";
    for (process = 0; process < 25; process++)
    {
        delay(20);
        cout << ".";
    }
    Color(DefaultColor);
}
string getCurrentTimestamp() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-"
       << 1 + ltm->tm_mon << "-"
       << ltm->tm_mday << " "
       << ltm->tm_hour << ":"
       << ltm->tm_min << ":"
       << ltm->tm_sec;
    return ss.str();
}
void invalidInput(){
        Color(Red);
        cin.ignore();
        cout << "\n\n\t\t\t\t";
        cout << "      Invalid choice!Please try again.";
        cout << "\n";
        Color(DefaultColor);

}
void welcomePage(){
    clearConsole();
    date();
    cout << "\n";
    title("CLOTHES INFORMATION MANAGEMENT");
    Color(LightGreen);
    cout << "\t\t\t\t";
    cout << "Prepared By    :    Team 5  ";
    cout << "\n\n";
    cout << "\t\t\t\t";
    cout << "Mini Project   :    Clothes Information Management";
    cout << "\n\n";
    pressEnterToSth("Continue");
    Color(DefaultColor);
}
void callExit(){
    clearConsole();
    title("THANK YOU ");
    Color(LightGreen);
    cout << "\n\n\t\t\tTeam Member :\n\n";
    cout << "\t\t\t\t1.Song Sodamony\n";
    cout << "\t\t\t\t2.Uth Rathana\n";
    cout << "\t\t\t\t3.Sokhom Panha\n\n";

    cout << "\t\t\tLecture: Seak Leng\n\n";

    cin.get();
    pressEnterToSth("Exit the Program");

    clearConsole();
    Color(Red);
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\t";
    cout << "You are out of the System.";
    cout << "\n\n";
    cout << "\t\t\t\t";
    Color(DefaultColor);
    exit(0);
}
void headerForDisplayProduct(){
    setcenter("N-",6);setcenter("ID",10);setcenter("Name",20);setcenter("Size",15);
    setcenter("Color",12);setcenter("Price",24);setcenter("Quantity",15);
    //cout <<\n\n;
}


