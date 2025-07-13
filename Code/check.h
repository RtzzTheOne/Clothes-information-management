#include<iostream>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<sstream>
// Platform-specific includes
#ifdef _WIN32
    #include<windows.h>
    #include<conio.h>
#else
    #include<termios.h>
    #include<unistd.h>
#endif
#include <iomanip>
#include "decorate.h"

using namespace std;
//checkSth
bool isSeperate(string s);
string checkUserName(string prompt);
bool isNumber(string s);
int checkNum(string prompt);
bool isDouble(string s);
double checkDouble(string prompt);
bool sthMore(string sth);
//Get data from user
ClothingItem GetData(List* ls);

//Code Below
bool isSeperate(string s){
    for (char c : s) {
        if (c == ' ') {
            return true;
        }
    }
    return false;
}
string checkUserName(string prompt)
{
    cin.ignore();
    string user;
    cout << prompt;
    getline(cin,user);
    if(!isSeperate(user))
    {
        return user;
    }
    invalidInput();
    return checkUserName(prompt);
}

bool isNumber(string s)
{
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int checkNum(string prompt){
    string s;
    cout << prompt;
    cin >> s;
    if(isNumber(s)){
        return stoi(s);
    }else{
        invalidInput();
        return checkNum(prompt);
    }
}


bool isDouble(string s) {
    bool decimalPointSeen = false;
    for (char c : s) {
        if (!isdigit(c)) {
            if (c == '.' && !decimalPointSeen) {
                decimalPointSeen = true;
            } else {
                return false;
            }
        }
    }
    return !s.empty() && !(s.size() == 1 && s[0] == '.'); // Ensures the string is not empty and not just a single dot
}

double checkDouble(string prompt) {
    string s;
    cout << prompt;
    cin >> s;
    //cin.ignore();

    if (isDouble(s)) {
        return stod(s);
    } else {
        invalidInput();
        return checkDouble(prompt);
    }

}
string toLower(string& str) {
    for (char& c : str) {
        c = tolower(c);
    }
    return str;
}
bool sthMore(string sth){
    string choice;
    cout <<"\n\t\t\t\tDo you to " <<sth << " more ? [yes/no] ";
    cin >> choice;
    choice = toLower(choice);
    if(choice == "yes" || choice == "y" ){
        return true;
    }
    if(choice == "no" || choice == "n" ){
        return false;

    }else{
        invalidInput();
        return sthMore(sth);
    }
}
