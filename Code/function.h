#include<iostream>
#include<fstream>
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
#include "database.h"
using namespace std;
//Data Structure
string clothesCategory;



//******************************************
//           DECORATE FUNCTION
//******************************************

void Color(Colour color);
void clearConsole();
void delay();
void date();
void pressEnterToSth(string something);
void welcomePage();
void invalidInput();
void callExit();
void setcenter(const string& text, int width);
string toLower(string& str);
void generateID();
void title(const string& title);
string getCurrentTimestamp();
void headerForDisplayProduct();

//checkSth
bool isSeperate(string s);
string checkUserName(string prompt);
bool isNumber(string s);
int checkNum(string prompt);
bool isDouble(string s);
double checkDouble(string prompt);
bool sthMore(string sth);
//******************************************
//              MAIN LOGIN FUCTION
//******************************************
void mainLogin(List* ls);

//******************************************
//      CHOOSE CATEGORY FUCTION
//*******************************************

void chooseCategory(List* ls);


//******************************************
//           ADMIN LOGIN FUNCTION
//******************************************

void adminLogin(List* ls);
void adminMenu(List* ls); // admin authentication
string getPassword();

//******************************************
//           USER LOGIN FUNCTION
//******************************************

struct UserLoginInfo {
    string name;
    string password;
    string gmail;
};

void forgotPassword(List* ls);
void userSignup(List* ls);
void checkLogin(List* ls);
void userLoginOrSignup(List* ls);
void saveUserInfo(const UserLoginInfo& user);
bool isUserExist(const string& name);
void changePassword(List* ls);

//****************************************
//           USER MENU FUNCTION
//****************************************
void createDataBase(const string& filename);
void loadFromData(List* L1,const string& filename);
void saveToData(List* L1,const string& filename);
void userMenu(List* ls);

//display
void displayAll(List* ls);

//search
void searchPage(List* ls);
void searchByID(List* ls);
void searchByPrice(List* ls,const int uniqueNum);
void searchByName(List* ls);

void buyPage(List* ls);
void historyPage(List* ls);

//****************************************
//           ADMIN MENU FUNCTION
//****************************************
void adminMenu(List* ls);

void deletePage(List* ls);
void deleteAll(List* ls);
void deleteByID(List* ls);

void updatePage(List* ls);
void updateStock(List* ls);
void updateInfoByID(List* ls);
void updatePrice(List* ls);

void addPage(List* ls);
void addBegin(List* ls);
void addByPosition(List* ls);
void addEnd(List* ls);
void adminRevenu(List* ls);

void searchPageAdmin(List* ls);

////****************************************
//           LINK LIST FUNCTION
//****************************************
void add_at_nth(List* ls, ClothingItem data, int position);
void delete_all(List* ls);
void delete_at_nth(List* ls,int position);
ClothingItem GetData();










//******************MAIN LOGIN********************
void mainLogin(List* ls){
    int choice;
    clearConsole();
    date();
    cout << "\n";
    title("AUTHENTICATION");
    cout << "\t\t\t\t\t";
    Color(LightGreen);
    cout<< "1. Admin Panel."<<endl;
    cout << "\t\t\t\t\t";
    cout<< "2. User Panel"<<endl;
    cout << "\t\t\t\t\t";
    cout << "3. Exit \n"<<endl;
    Color(DefaultColor);
    choice = checkNum("\t\t\t\t\tchoose option [1/2/3] : ");
    switch(choice)
    {
    case 1:
            clearConsole();
            adminLogin(ls);
            break;
    case 2:
            clearConsole();
            userLoginOrSignup(ls);
            break;
    case 3:
            callExit();
            break;
    default:
            invalidInput();
            pressEnterToSth("Choose again");
            mainLogin(ls);
    }
}
char getch() {
#ifdef _WIN32
    return _getch();
#else
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}
string getPassword(){
    string password;
    char ch;
    while((ch = getch()) != '\r' && ch != '\n'){
          if(ch == '\b' || ch == 127){ // Handle backspace (127 is DEL on some systems)
            if(!password.empty()){
                password.pop_back();
                cout << "\b \b";
            }
          }else{
            password += ch;
            cout << "*";
          }
    }
    cout << endl;
    return password;
}
void adminLogin(List* ls){
    string admin_username;
    string admin_password ;
    int tryCount = 0;
    int maxTries = 3;
    string y;

    do
    {
        clearConsole();
        cout << "\n\n\n\n\n\n\n\n\n";
        Color(LightBlue);
        cout << "\t\t\t\t\tADMIN LOGIN\n\n\t\t\t\t\t";
        Color(DefaultColor);
        cout << "admin Username: ";cin >> admin_username;
        cout << "\t\t\t\t\t\n\t\t\t\t\t";
        cout << "admin Password: " ;
        admin_password = getPassword();

        if (admin_username == "admin" && admin_password == "admin123")
        {
            Color(LightGreen);
            cout << "\n\n\t\t\t\t";
            cout << "You are accessed to the system!\n\n";
            pressEnterToSth("Continue");
            chooseCategory(ls);
            cin.get();
            pressEnterToSth("Continue");
            adminMenu(ls);
        }
        else
        {
            clearConsole();
            tryCount++;
            Color(Red);
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t";
            cout << "No. of attempts remain: " << maxTries - tryCount;
            Color(LightGreen);
            cout << "\n\n\n\n";
            cout << "\t\t\t\tDo you want to return to main Login [yes/no]";cin >> y;
            if(y == "yes" || y=="y"){
                cin.get();
                pressEnterToSth("Return to Main Login");
                mainLogin(ls);
            }
            if (tryCount >= maxTries)
            {
                Color(Red);
                cout << "\t\t\t\t\t\t\n\t\t\t\t";
                cout << "No permission to enter the system!";
                cin.get();
                callExit();
            }
        }
    }
    while (true);
}
void userLoginOrSignup(List* ls) {
    int choice;
    clearConsole();
    title("LOG IN OR SIGN UP");
    Color(LightGreen);
    cout << "\t\t\t\t\t1. User Log in." << endl;
    cout << "\t\t\t\t\t2. User Sign up" << endl;
    cout << "\t\t\t\t\t3. Forgot Password" << endl;
    cout << "\t\t\t\t\t4. Change Password" <<endl;
    cout << "\t\t\t\t\t5. Back to Authentication" << endl;
    cout << "\t\t\t\t\t6. Exit" << endl;
    Color(Orange);
    choice = checkNum("\n\t\t\t\t\tchoose option [1/2/3/4/5/6] : ");
    switch (choice) {
        case 1:
            checkLogin(ls);
            break;
        case 2:
            userSignup(ls);
            cin.get();
            pressEnterToSth("Return Back");
            userLoginOrSignup(ls);
            break;
        case 3:
            forgotPassword(ls);
            cin.get();
            pressEnterToSth("Return Back");
            userLoginOrSignup(ls);
            break;
        case 4:
            changePassword(ls);
            cin.get();
            pressEnterToSth("Return Back");
            userLoginOrSignup(ls);
        case 5:
            mainLogin(ls);
            break;
        case 6:
            callExit();
        default:
            invalidInput();
            pressEnterToSth("Enter Again");
            userLoginOrSignup(ls);
            break;
    }
}

void userSignup(List* ls) {
    clearConsole();
    title("SIGN UP");
    UserLoginInfo user;
    Color(LightGreen);
    //cin.ignore();
    user.name = checkUserName("\n\t\t\t\t\tEnter your username: ");
    if (isUserExist(user.name)) {
        Color(Red);
        cout << "\n\n\t\t\tUsername already exists. Please choose a different username." << endl;
        cin.get();
        Color(LightGreen);
        pressEnterToSth("Enter new username");
        userSignup(ls);
        return;
    }

    cout << "\n\t\t\t\t\tEnter your Gmail: " ;cin>>user.gmail;

    string confirmPassword;
    do{
        cout << "\n\t\t\t\t\t";
        cout << "Enter password: ";
        user.password = getPassword();

        cout << "\n\t\t\t\t\t";
        cout << "Confirm password: ";
        confirmPassword = getPassword();

        if(confirmPassword == user.password){
            saveUserInfo(user);

            Color(LightBlue);
            cout << "\n\n\n\t\t\t\t\t";
            cout << "User signed up successfully!" << endl;
            break;
        }
    }while(true);
}
string currentUserName; //global variable
void checkLogin(List* ls) {
    clearConsole();
    string choice;
    UserLoginInfo user;
    cout << "\n\n\n\n\n\n\n\n\n";
    Color(Orange);
    cout << "\t\t\t\t\tUSER LOGIN\n";
    user.name = checkUserName("\n\t\t\t\t\tEnter your username: ");
    currentUserName = user.name;
    cout << "\t\t\t\t\t\n\t\t\t\t\t";
    cout << "Enter password: ";
    user.password = getPassword();
    Color(DefaultColor);

    ifstream infile("../dataBase/UserPassword/userData.csv");
    string line, storedName, storedPassword;
    bool found = false;

    while (getline(infile, line)) {
        stringstream ss(line);
        getline(ss, storedName, ',');
        getline(ss, storedPassword, ',');
        if ((user.name == storedName) && (user.password == storedPassword)) {
            found = true;
            break;
        }
    }

    if (found) {
        Color(LightGreen);
        cout << "\t\t\t\t\tLogin successful!\n\n" << endl;
        cin.get();
        pressEnterToSth("Continue");
        chooseCategory(ls);
        pressEnterToSth("Coninue");
        userMenu(ls);
    } else {
        Color(Orange);
        cout << "\t\t\t\t\tInvalid username or password.\n\n" << endl;
        cout << "Do you want to to return back ? [yes/no] : ";cin>>choice;
        choice = toLower(choice);
        if(choice == "yes" || choice=="y"){
                cin.get();
                pressEnterToSth("Return back");
                userLoginOrSignup(ls);
        }else{
                cin.get();
                pressEnterToSth("Login again");
                checkLogin(ls);
        }
    }
}
void saveUserInfo(const UserLoginInfo& user) {
    ofstream outfile("../dataBase/UserPassword/userData.csv", ios::app);
    outfile << user.name << ","<< user.password <<","<<user.gmail<< endl;
    outfile.close();
}

bool isUserExist(const string& name) {
    ifstream infile("../dataBase/UserPassword/userData.csv");
    string line, storedName;

    while (getline(infile,line)) {
        stringstream ss(line);
        getline(ss,storedName,',');
        if (name == storedName) {
            infile.close();
            return true;
        }
    }
    infile.close();
    return false;
}

void forgotPassword(List* ls) {
    string choice;
    clearConsole();
    cout << "\n\n\n\n\n\n\n\n\n";
    Color(Orange);
    cout << "\t\t\t\t\tFORGOT PASSWORD\n";
    string username;
    username = checkUserName("\n\t\t\t\t Enter your name :");
    if (!isUserExist(username)) {
        Color(Red);
        cout << "User Name doesn't Exit" << endl;
        cin.get();
        Color(LightGreen);
        pressEnterToSth("Return Back");
        userLoginOrSignup(ls);
        return;
    }
    string gmail;
    cout << "\n\t\t\t\tEnter your gmail: ";cin>>gmail;
    ifstream infile("../dataBase/UserPassword/userData.csv");
    string line, storedName, storedPassword, storedGmail;
    bool found = false;

    while (getline(infile, line)) {
        stringstream ss(line);
        getline(ss, storedName, ',');
        getline(ss, storedPassword, ',');
        getline(ss, storedGmail, ',');
        if (username == storedName && gmail == storedGmail) {
            cout << "\n\n\t\t\t\tYour password is: " << storedPassword << endl;
            found = true;
            break;
        }
    }
    infile.close();

    if (!found) {
        Color(Orange);
        cout << "\n\t\t\t\t\tGmail User is not matching .\n" << endl;
        cout << "\t\t\t\tDo you want to return to main Login [yes/no]";cin >> choice;
        choice = toLower(choice);
        if(choice == "yes" || choice=="y"){
            cin.get();
            pressEnterToSth("Return to Main Login");
            userLoginOrSignup(ls);
        } else {
            cin.get();
            pressEnterToSth("to Try Again");
            forgotPassword(ls);
        }
    }
}
void changePassword(List* ls) {
    clearConsole();
    title("CHANGE PASSWORD");
    string oldPassword, newPassword, confirmPassword;
    UserLoginInfo user;
    Color(LightGreen);
    string username;
    username = checkUserName("\n\t\t\t\t Enter your name :");
    if (!isUserExist(username)) {
        Color(Red);
        cout << "User Name doesn't Exit" << endl;
        cin.get();
        Color(LightGreen);
        pressEnterToSth("Return Back");
        userSignup(ls);
        return;
    }
    cout << "\n\t\t\t\t\tEnter your current password: ";
    oldPassword = getPassword();

    ifstream infile("../dataBase/UserPassword/userData.csv");
    ofstream tempFile("../dataBase/UserPassword/temp.csv");
    string line, storedName, storedPassword, storedGmail;
    bool passwordMatch = false;

    while (getline(infile, line)) {
        stringstream ss(line);
        getline(ss, storedName, ',');
        getline(ss, storedPassword, ',');
        getline(ss, storedGmail, ',');
        if (storedName == username && storedPassword == oldPassword) {
            passwordMatch = true;
            cout << "\n\t\t\t\t\tEnter new password: ";
            newPassword = getPassword();
            cout << "\n\t\t\t\t\tConfirm new password: ";
            confirmPassword = getPassword();

            if (newPassword == confirmPassword) {
                tempFile << storedName << "," << newPassword << "," << storedGmail << endl;
            } else {
                cout << "\n\t\t\t\t\tPasswords do not match. Try again." << endl;
                infile.close();
                tempFile.close();
                remove("../dataBase/UserPassword/temp.csv");
                changePassword(ls);
                return;
            }
        } else {
            tempFile << line << endl;
        }
    }
    infile.close();
    tempFile.close();
    remove("../dataBase/UserPassword/userData.csv");
    rename("../dataBase/UserPassword/temp.csv", "../dataBase/UserPassword/userData.csv");

    if (passwordMatch) {
        Color(LightGreen);
        cout << "\n\n\n\t\t\t\t\tPassword changed successfully!" << endl;
    } else {
        Color(Orange);
        cout << "\n\n\n\t\t\t\t\tCurrent password is incorrect." << endl;
        changePassword(ls);
    }
}
//*******************************************
//            CHOOSE CLOTHES CATEGORY
//*******************************************
void chooseCategory(List* ls){
    int choice;
    string currentDataBase;
    clearConsole();
    title("CLOTHES CATEGORY");
    Color(LightGreen);
    cout <<"\t\t\t\t";
    cout << " 1. Men\n\n";
    cout << "\t\t\t\t";
    cout << " 2. Women\n\n";
    cout << "\t\t\t\t";
    cout << " 3. Kids\n\n";
    cout << "\t\t\t\t";
    cout << " 4. Return to Main Login\n\n";
    cout << "\t\t\t\t";
    cout << " 5. Exit\n\n";
    choice = checkNum("\t\t\t\tChoose option [1/2/3/4/5]: ");
    switch (choice) {
    case 1:
        clothesCategory = "Men";
        break;
    case 2:
        clothesCategory = "Women";
        break;
    case 3:
        clothesCategory = "Kids";
        break;
    case 4:
        mainLogin(ls);
        break;
    case 6:
        callExit();
        break;
    default:
        cin.get();
        invalidInput();
        pressEnterToSth("Choose Again");
        chooseCategory(ls);
    }
    //new type of clothes
    numberOfClothes = 0;
    delete_all(ls);
    currentDataBase = "../dataBase/ClothesDataBase/"+ clothesCategory +"ClothesDataBase.csv";
    loadFromData(ls, currentDataBase);
}

//******************USER MENU*******************

void printElement(Element* tmp){
        Color(Yellow);
        string priceText;
        setcenter(to_string(tmp->data.position),6);
        setcenter(tmp->data.id,10);
        cout <<setw(20) <<left<< tmp->data.name;
        setcenter(tmp->data.size,15);
        setcenter(tmp->data.color,12);

        stringstream stream;
        stream << fixed << setprecision(2) << tmp->data.price;
        string result = stream.str();

        priceText = result + " $";
        cout << setw(18)<<right << priceText;
        setcenter(to_string(tmp->data.quantity),23);
        Color(DefaultColor);
}


// User menu
void userMenu(List* ls) {
    int input;
    clearConsole();
    string titleUser = "USER PANEL - " +clothesCategory;
    title(titleUser);
    Color(LightGreen);
    cout <<"\t\t\t\t";
    cout << " 1. Display All " << clothesCategory << " Products\n\n";
    cout << "\t\t\t\t";
    cout << " 2. Search\n\n";
    cout << "\t\t\t\t";
    cout << " 3. Buy\n\n";
    cout << "\t\t\t\t";
    cout << " 4. History\n\n";
    cout << "\t\t\t\t";
    cout << " 5. Return to Login Or Sign up Page\n\n";
    cout << "\t\t\t\t";
    cout << " 6. Exit\n\n";
    input = checkNum("\t\t\t\tChoose option [1/2/3/4/5/6]: ");
    pressEnterToSth("Continue");
    switch (input) {
    case 1:
        clearConsole();
        displayAll(ls);
        pressEnterToSth("Return Back");
        userMenu(ls);
        break;
    case 2:
        searchPage(ls);
        break;
    case 3:
        buyPage(ls);
        break;
    case 4:
        historyPage(ls);
        break;
    case 5:
        userLoginOrSignup(ls);
        break;
    case 6:
        callExit();
        break;
    default:
        invalidInput();
        userMenu(ls);
    }
}


// Search page
void searchPage(List* ls) {
    clearConsole();
    int c;
    bool searchMore;
    title("SEARCH PAGE");
    Color(LightGreen);
    cout << "\t\t\t\t1. Search by ID\n";
    cout << "\t\t\t\t2. Search by Price\n";
    cout << "\t\t\t\t3. Search by Name\n";
    cout << "\t\t\t\t4. Return\n";
    cout << "\t\t\t\t5. Exit\n";
    Color(Orange);
    c = checkNum("\t\t\t\tChoose option [1/2/3/4]: ");
    switch (c) {
        case 1:
            do{
                clearConsole();
                searchByID(ls);
                searchMore = sthMore("search");
            }while(searchMore ==1);
            break;
        case 2:
            do{
                clearConsole();
                searchByPrice(ls,1);
                searchMore = sthMore("search");
            }while(searchMore==1);
            break;
        case 3:
            do{
                clearConsole();
                searchByName(ls);
                searchMore = sthMore("search");
            }while(searchMore ==1);
            break;
        case 4:
            cin.get();
            pressEnterToSth("Return Back");
            userMenu(ls);
            break;
        case 5:
            callExit();break;
        default:
            invalidInput();
            pressEnterToSth("Choose Again");
            searchPage(ls);
            break;
    }
    cin.get();
    pressEnterToSth("Return Back");
    searchPage(ls);
}

void searchByID(List* ls) {
    int found = 0;
    string id;
    Color(LightBlue);
    cout << "\n\n\n\t\t\t\t\tSEARCH BY ID\n\n";
    Color(LightGreen);
    cout <<"\n\t\t\t\tEnter ID: ";cin >>id;
    Element* tmp = ls->head;
    while (tmp != nullptr) {
        if (tmp->data.id == id) {
                found++;
                if(found == 1){
                    title("DISPLAY FOUND PRODUCT");
                    headerForDisplayProduct();cout << "\n\n";
                }
                printElement(tmp);
                cout << endl;
            }
            tmp = tmp->next;
        }
        if(found==0){cout << "\n\n\t\tThere is no product id: \" " << id << " \" \n";}
}

// Search by Price
void searchByPrice(List* ls ,const int uniqueNum) {
    clearConsole();
    int found=0;
    int c;
    double price;
    Color(LightBlue);
    cout << "\n\n\t\t\t\t\tSEARCH BY PRICE\n\n";
    Color(DarkGreen);
    cout << "\t\t\t\t1. Smaller or equal\n";
    cout << "\t\t\t\t2. Higher or equal\n";
    cout << "\t\t\t\t3. Exact price\n";
    cout << "\t\t\t\t4. Return Back\n\n";
    Color(DefaultColor);
    c = checkNum("\t\t\t\tChoose [1/2/3/4]: ");
    if(c!=1&&c!=2&&c!=3){
        if(c==4){
            cin.get();
            pressEnterToSth("Return Back");
            if(uniqueNum == 1){
                searchPage(ls);
            }else{
                searchPageAdmin(ls);
            }
        }
        invalidInput();
        pressEnterToSth("Choice Again");
        searchByPrice(ls,uniqueNum);
    }
    Color(DarkGreen);
    price = checkDouble( "\n\n\t\t\t\tEnter Price: ");
    Element* tmp = ls->head;
    switch (c) {
    case 1:
        while (tmp != nullptr) {
            if (tmp->data.price <= price) {
                found++;
                if(found == 1){
                    title("DISPLAY FOUND PRODUCT");
                    headerForDisplayProduct();cout << "\n\n";
                }
                printElement(tmp);
                cout << endl;
            }
            tmp = tmp->next;
        if(found==0){cout << "\n\n\t\tThere is no product that have price smaller or eqaul to " << price << " $.\n";}

        break;
    case 2:
        while (tmp != nullptr) {
            if (tmp->data.price >= price) {
                found++;
                if(found == 1){
                    title("DISPLAY FOUND PRODUCT");
                    headerForDisplayProduct();cout << "\n\n";
                }
                printElement(tmp);
                cout << endl;
            }
            tmp = tmp->next;
        }
        if(found==0){cout << "\n\n\t\tThere is no product that have price higher or eqaul to " << price << " $.\n";}
        break;
    case 3:
        while (tmp != nullptr) {
            if (tmp->data.price == price) {
                found++;
                if(found == 1){
                    title("DISPLAY FOUND PRODUCT");
                    headerForDisplayProduct();cout << "\n\n";
                }
                printElement(tmp);
                cout << endl;
            }
            tmp = tmp->next;
        }
        if(found==0){cout << "\n\n\t\tThere is no product that have price eqaul to " << price << " $.\n";}
        break;
    }

}}
void searchByName(List* ls){
    int found=0;
    string name;
    Color(LightBlue);
    cout << "\n\n\t\t\t\t\tSEARCH BY NAME\n\n\t\t\t\t";
    cout << "Enter your cloth name: "; cin>> name;

    Element* tmp = ls->head;
    while(tmp!=nullptr){
        if(tmp->data.name == name){
            found++;
            if(found ==1 ){
                title("FOUND THE PRODUCT");
                headerForDisplayProduct();cout << "\n\n";
                cout << "\n\n";
            }
            printElement(tmp);
            cout <<endl;
            }
        tmp= tmp->next;
    }
    if(found ==0){
        Color(Red);
        cout << "\n\n\t\tThere is no product name :" << name << ".\n";
    }
    cout << endl;
    delete tmp;
}

// Buy page


void buyPage(List* ls) {
    List* temp = createEmptyList();
    bool buyMore;

    do {
        clearConsole();
        displayAll(ls);

        int position, quantity;
        Color(LightBlue);
        //check position
        position = checkNum("\n\t\tEnter the position of the product you want to buy: ");
        while(position > ls->size){
            Color(Red);
            cout << "\t\tnProduct not found at position :"<< position;
            Color(DefaultColor);
            position = checkNum("\n\t\tEnter the position of the product you want to buy: ");
        }

        quantity = checkNum("\n\t\tEnter the quantity you want to buy: ");

        Element* tmp = ls->head;
        bool found = false;

        while (tmp != nullptr) {
            if (tmp->data.position == position) {
                found = true;
                if (tmp->data.quantity >= quantity) {
                    tmp->data.quantity -= quantity;
                    ClothingItem item = tmp->data;
                    item.quantity = quantity;
                    add_at_nth(temp, item,temp->size+1);
                    cout << "\n\t\tItem added to cart.";
                } else {
                    cout << "\n\t\tNot enough stock available.\n";
                }
                break;
            }
            tmp = tmp->next;
        }

        buyMore = sthMore("buy");
    } while (buyMore==1);

    // Print receipt
    clearConsole();
    title("RECEIPT");

    double total = 0;
    //get current time
    //open userHistoryDataBase and get the data into file
    string timestamp = getCurrentTimestamp();
    string userHistoryFile = "../dataBase/UserHistory/"+currentUserName +"History.csv";
    ofstream historyFile(userHistoryFile, ios::app);  // Open file in append mode
    Element* t = temp->head;

    headerForDisplayProduct();setcenter("Total",10);
    cout << "\n\n";
    while (t != nullptr) {
        //print out the reciept
        printElement(t);
        stringstream stream;
        stream << fixed << setprecision(2) << t->data.price * t->data.quantity;
        string pricePerItem = stream.str();
        cout << setw(4) << right << pricePerItem <<" $"<< "\n";
        total += t->data.price * t->data.quantity;

        // Record to history file
        historyFile << timestamp << "," << t->data.id << "," << t->data.name << "," << t->data.size
                    << "," << t->data.color << ","<<clothesCategory << "," << t->data.price << ","
                    << t->data.quantity << ","<< t->data.price * t->data.quantity << "\n";

        t = t->next;
    }
    cout <<"\n"<< setw(103)<<right << "Total: \t" << total  << " $ " << "\n";
    historyFile.close();  // Close the history file after writing


    //Open adminRevenuDataBase and get data into it
    ofstream adminRevenu("../dataBase/AdminRevenu/adminRevenu.csv",ios::app);

    adminRevenu << timestamp <<"," << currentUserName <<"," <<clothesCategory<<","<<total <<"\n";
    Color(Orange);
    cout<< "\n\n";
    string file =  "../dataBase/ClothesDataBase/"+clothesCategory+"ClothesDataBase.csv";
    saveToData(ls,file);
    adminRevenu.close();
    // Update CSV file

    cin.get();
    pressEnterToSth("Return Back");
    userMenu(ls);
}




// History page
void historyPage(List* ls) {
    clearConsole();
    string userHistoryFile = "../dataBase/UserHistory/"+currentUserName +"History.csv";
    ifstream historyFile(userHistoryFile);
    if (!historyFile.is_open()) {
        cout << "There is no history at the moment\n";
        pressEnterToSth("Return Back");
        userMenu(ls);
    }

    string line;
    title("PURCHASE HISTORY");
    cout << "Timestamp\t\tID\tName\t\tSize\tColor\tType\tPrice\tQuantity\tTotal\n\n";
    while (getline(historyFile, line)) {
        stringstream ss(line);
        string timestamp, id, name, size, color,type, price, quantity, total;
        getline(ss, timestamp, ',');
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, size, ',');
        getline(ss, color, ',');
        getline(ss, type, ',');
        getline(ss, price, ',');
        getline(ss, quantity, ',');
        getline(ss, total, ',');
        cout << timestamp << "\t" << id << "\t" << name << "\t\t" << size << "\t"
             << color << "\t" <<type << "\t" << price << "$" << "\t" << quantity << "\t\t" << total  <<" $"<< "\n";
    }
    historyFile.close();

    pressEnterToSth("Return Back");
    userMenu(ls);
}


//adminMenu
void adminMenu(List* ls){
    int c;
    do{
        clearConsole();
        title("ADMIN PANEL");

        Color(LightGreen);
        cout << "\t\t\t\t1. Display All \n";
        cout << "\t\t\t\t2. Search\n ";
        cout << "\t\t\t\t3. Delete\n ";
        cout << "\t\t\t\t4. Update\n" ;
        cout << "\t\t\t\t5. Add the product\n";
        cout << "\t\t\t\t6. View the Revenu\n";
        cout << "\t\t\t\t7. Return\n";
        cout << "\t\t\t\t8. Exit\n\n";
        Color(LightBlue);
        c = checkNum("\t\t\t\tChoose option [1/2/3/4/5/6/7/8]: ");cin.ignore();
        switch(c){
            case 1:
                    clearConsole();
                    displayAll(ls);
                    cin.get();
                    pressEnterToSth("Return Back");
                    adminMenu(ls);
                    break;
            case 2: searchPageAdmin(ls);break;
            case 3: deletePage(ls);break;
            case 4: updatePage(ls);break;
            case 5: addPage(ls);break;
            case 6: adminRevenu(ls);break;
            case 7: cin.get();
                    pressEnterToSth("Return Back");
                    mainLogin(ls);break;
            case 8: callExit();break;
        }
    }while(c!=8);
}

void searchPageAdmin(List* ls) {
    clearConsole();
    int c;
    bool searchMore;
    title("SEARCH PAGE");
    Color(LightGreen);
    cout << "\t\t\t\t1. Search by ID\n";
    cout << "\t\t\t\t2. Search by Price\n";
    cout << "\t\t\t\t3. Search by Name\n";
    cout << "\t\t\t\t4. Return\n";
    cout << "\t\t\t\t5. Exit\n";
    Color(Orange);
    c = checkNum("\t\t\t\tChoose option [1/2/3/4]: ");
    switch (c) {
        case 1:
            do{
                clearConsole();
                searchByID(ls);
                searchMore = sthMore("search");
            }while(searchMore ==1);
            break;
        case 2:
            searchByPrice(ls,2);
            break;
        case 3:
            do{
                clearConsole();
                searchByName(ls);
                searchMore = sthMore("search");
            }while(searchMore ==1);
            break;
        case 4:
            cin.get();
            pressEnterToSth("Return Back");
            adminMenu(ls);
            break;
        case 5:
            callExit();break;
        default:
            invalidInput();
            pressEnterToSth("Choose Again");
            searchPageAdmin(ls);
            break;
    }
    cin.get();
    pressEnterToSth("Return Back");
    searchPageAdmin(ls);
}


void deletePage(List* ls){
    string currentDatabase = "../dataBase/ClothesDataBase/"+clothesCategory+"ClothesDataBase.csv";
    int c;
    bool deleteMore;
    int position;
    do{
        clearConsole();
        title("DELETE PAGE");
        Color(LightGreen);
        cout << "\t\t\t\t1. Delete by Position\n";
        cout << "\t\t\t\t2. Delete at the End \n ";
        cout << "\t\t\t\t3. Delete info by ID\n" ;
        cout << "\t\t\t\t4. Delete All \n";
        cout << "\t\t\t\t5. Return to main page\n ";
        cout << "\t\t\t\t6. Exit\n";
        Color(LightBlue);
        c = checkNum("\t\t\t\tChoose option [1/2/3/4/5]: ");
        switch(c){
            case 1:
                    do{
                        clearConsole();
                        Color(LightBlue);
                        cout << "\n\n\t\t\t\t\tDELETE BY POSITION \n\n";
                        Color(DefaultColor);
                        do{
                            position = checkNum("\t\t\t\tEnter Position :");
                        }while(position < 1 || position > ls->size);
                        delete_at_nth(ls,position);
                        saveToData(ls,currentDatabase);
                        deleteMore = sthMore("delete");
                    }while(deleteMore ==1);
                    break;
            case 2:
                    do{
                        clearConsole();
                        delete_at_nth(ls,ls->size);
                        saveToData(ls,currentDatabase);
                        deleteMore = sthMore("delete");
                    }while(deleteMore ==1);
                    break;

            case 3:
                    do{
                        clearConsole();
                        deleteByID(ls);
                        saveToData(ls, currentDatabase);
                        deleteMore = sthMore("delete");
                    }while(deleteMore ==1);
                    break;
            case 4:
                    clearConsole();
                    deleteAll(ls);
                    break;
            case 5: adminMenu(ls);break;
            case 6: callExit();break;
        }
    }while(c!=6);
    cin.get();
    pressEnterToSth("Return Back");
    deletePage(ls);
}


void updatePage(List* ls){
    clearConsole();
    int c;
    bool updateMore;
    string file = "../dataBase/ClothesDataBase/"+clothesCategory+"ClothesDataBase.csv";
    title("UPDATE PAGE");
    Color(LightGreen);
    cout << "\t\t\t\t1. Update Stock \n";
    cout << "\t\t\t\t2. Update Price \n";
    cout << "\t\t\t\t3. Update information \n ";
    cout << "\t\t\t\t4. Return to main page\n ";
    cout << "\t\t\t\t5. Exit\n";
    Color(LightBlue);
    c = checkNum("\t\t\t\tChoose option [1/2/3/4/5]: ");
    switch(c){
            case 1:
                    do{
                        clearConsole();
                        updateStock(ls);
                        saveToData(ls,file);
                        updateMore = sthMore("update");
                    }while(updateMore == 1);break;
            case 2:
                    do{
                        clearConsole();
                        updatePrice(ls);
                        saveToData(ls,file);
                        updateMore = sthMore("updare");
                    }while(updateMore == 1);break;
            case 3:
                    do{
                        clearConsole();
                        updateInfoByID(ls);
                        saveToData(ls,file);
                        updateMore = sthMore("updare");
                    }while(updateMore == 1);break;
            case 4: adminMenu(ls);break;
            case 5: callExit();break;
            default:
                invalidInput();
                cin.get();
                pressEnterToSth("Choose Again");
                updatePage(ls);
                break;

    }
    cin.get();
    pressEnterToSth("Return Back");
    updatePage(ls);
}

void addPage(List* ls){
    int c;
    string file = "../dataBase/ClothesDataBase/"+clothesCategory+"ClothesDataBase.csv";
    bool addMore;
    do{
        clearConsole();
        title("ADD PAGE");
        Color(LightGreen);
        cout << "\t\t\t\t1. Add Begin \n";
        cout << "\t\t\t\t2. Add by Position \n ";
        cout << "\t\t\t\t3. Add end  \n" ;
        cout << "\t\t\t\t4. Return to main page\n ";
        cout << "\t\t\t\t5. Exit\n\n";
        Color(LightBlue);
        c = checkNum("\t\t\tChoose option [1/2/3/4/5]: ");
        switch(c){
            case 1:
                do{
                    clearConsole();
                    addBegin(ls);
                    saveToData(ls, file);
                    addMore = sthMore("add");
                }while(addMore==1);
                cin.get();
                pressEnterToSth("Return Back");
                addPage(ls);
                break;
            case 2:
                do{
                    clearConsole();
                    addByPosition(ls);
                    saveToData(ls, file);
                    addMore = sthMore("add");
                }while(addMore==1);
                cin.get();
                pressEnterToSth("Return Back");
                addPage(ls);
                break;
            case 3:
                do{
                    clearConsole();
                    addEnd(ls);
                    saveToData(ls, file);
                    addMore = sthMore("add");
                }while(addMore==1);
                cin.get();
                pressEnterToSth("Return Back");
                addPage(ls);
                break;
            case 4: adminMenu(ls);break;
            case 5: callExit();break;
        }
    }while(c!=5);
}


string generateID(int num){
    ostringstream oss;
    if(clothesCategory=="Men"){
        oss<<"M"<<setw(3)<<setfill('0')<<num;
    }else if(clothesCategory =="Women"){
        oss<<"W"<<setw(3)<<setfill('0')<<num;
    }else if(clothesCategory == "Kids"){
        oss<<"K"<<setw(3)<<setfill('0')<<num;
    }
    return oss.str();
}
//Get data from user
ClothingItem GetData(List* ls){
    numberOfClothes++;
    ClothingItem data;
    string titlE = "INPUT NEW " + clothesCategory + "CLOTH DATA";
    title(titlE);
    Color(Yellow);
    data.position = ls->size+1;
    //wrong with this
    cin.ignore();
    data.id = generateID(numberOfClothes);
    cout << "\n\t\t\t\tInput new name: ";   getline(cin, data.name);
    cout << "\n\t\t\t\tInput new size: ";   getline(cin, data.size);
    cout << "\n\t\t\t\tInput new color: ";   getline(cin, data.color);
    data.price = checkDouble("\n\t\t\t\tInput new price: ");
    data.quantity = checkNum("\n\t\t\t\tInput new quantity: ");
    return data;
}


//Update Page Function
void updateInfoByID(List* ls){
    string id;
    Element* e = ls->head;
    title("UPDATE CLOTH INFORMATION");
    Color(LightBlue);
    cout << "\n\t\t\t\tEnter your ID: ";cin>>id; cin.ignore();
    while(e != nullptr){
        if(e->data.id == id){
            Color(Yellow);
            cout << "\n\t\t\t\tInput new name: ";   getline(cin, e->data.name);
            cout << "\n\t\t\t\tInput new size: ";   getline(cin, e->data.size);
            cout << "\n\t\t\t\tInput new color: ";   getline(cin, e->data.color);
            e->data.price = checkDouble("\n\t\t\t\tInput new price: ");
            e->data.quantity = checkNum("\n\t\t\t\tInput new quantity: ");
            Color(DarkGreen);
            cout << "\n\n\n\n\t\t\t\t\tUPDATED SUCCESSFULLY" << endl;
            return;
        }
        e = e->next;
    }
}
void updateStock(List* ls){
    int found = 0;
    string id;
    Element* e = ls->head;
    title("UPDATE STOCK");
    Color(LightBlue);
    cout << "\n\t\t\t\tEnter your ID: ";cin>>id; cin.ignore();
    while(e != nullptr){
        if(e->data.id == id){
            found =1;
            e->data.quantity = checkNum("\n\t\t\t\tInput new Stock: ");
            Color(DarkGreen);
            cout << "\n\n\t\t\t\t\tUPDATED STOCK SUCCESSFULLY" << endl;
            break;
        }
        e = e->next;
    }
   if(!found){
        cout << "\n\t\t\tThere is no "<<id << " in the DataBase" <<endl;
   }
}
void updatePrice(List* ls){
    string id;
    Element* e = ls->head;
    title("UPDATE PRICE");
    Color(LightBlue);
    cout << "\n\t\t\t\tEnter your ID: ";cin>>id;cin.ignore();
    while(e != nullptr){
        if(e->data.id == id){
            e->data.price = checkDouble("\n\t\t\t\tUpdate New Price:  ");
            Color(DarkGreen);
            cout << "\n\n\t\t\t\t\tUPDATED STOCK SUCCESSFULLY" << endl;
            break;
        }
        e = e->next;
    }
}
//Delete page Function
void deleteAll(List* ls){
    string choice;

    cout << "\n\n\t\t\t\tAre you sure you want to delete all of your data?";

    cout << "\n\t\t\t\t choose[yes/no]: ";
    cin >> choice;
    choice = toLower(choice);
    if(choice=="yes" || choice=="y"){
        delete_all(ls);
        cout << "\n\t\t\t\t\tAll of your data has been deleted." << endl;
    }else{
        cout << "\n\t\t\t\t\tNo data deleted" << endl;
    }
}
void deleteByID(List* ls){
    string id;
    Color(LightBlue);
    cout << "\t\t\t\t\tDELETE  BY ID \n\n\t\t\t\t\t";
    cout <<"\n\t\t\t\tEnter your id you want to delete: ";cin >> id;
    int count =1;
    Element* tmp = ls->head;
    while(tmp!= nullptr){
        if(tmp->data.id == id){
            delete_at_nth(ls, count);
            cout << "Data with ID = "<< id << " has been deleted successfully."<< endl;
        }
        count ++;
        tmp = tmp -> next;
    }
}
//Add page Function
void addBegin(List* ls){
    ClothingItem newData;
    Color(LightBlue);
    cout << "\n\n\t\t\t\t\t ADD BEGIN\n\n";
    newData = GetData(ls);
    add_at_nth(ls,newData,1); //equal to add begin
}
void addByPosition(List* ls){
    ClothingItem newData;
    int position;
    Color(LightBlue);
    cout << "\t\t\t\t\t ADD  BY POSITION \n\n";
    Color(DefaultColor);
    position = checkNum("Enter the position that you want to Add: ");
    if(position <0 || position > ls->size +1){
        cin.get();
        cout << "Invalid Position";
        pressEnterToSth("Enter Again");
        addByPosition(ls);
    }
    newData = GetData(ls);
    add_at_nth(ls, newData, position);
}
void addEnd(List* ls){
    ClothingItem newData;
    Color(LightBlue);
    cout << "\t\t\t\t\t ADD END \n\n\n\t\t\t";
    cout << "Please input your new last data:" << endl;
    newData = GetData(ls);
    add_at_nth(ls, newData,ls->size+1);
}

void adminRevenu(List* ls){
    double price, total;
    clearConsole();
    ifstream adminRevenu("../dataBase/AdminRevenu/adminRevenu.csv");
    if (!adminRevenu.is_open()) {
        cout << "There is no history at the moment\n";
        cin.get();
        pressEnterToSth("Return Back");
        adminMenu(ls);
    }

    string line;
    title("DISPLAY REVENU");
    cout << "Timestamp\t\t\tUerName\t\tType\t\tRevenu\n\n";
    while (getline(adminRevenu, line)) {
        stringstream ss(line);
        string timestamp, userName,type, revenu ;
        getline(ss, timestamp, ',');
        getline(ss, userName, ',');
        getline(ss, type, ',');
        getline(ss, revenu,',');
        price = stod(revenu);
        total +=price;
        cout << timestamp << "\t\t" << userName << "\t\t" <<type << "\t\t" << price << " $" << endl;
    }
    cout << "\n\t\t\tTotalRevenu:  "<<total << " $" <<endl;
    adminRevenu.close();
    cin.get();
    pressEnterToSth("Return Back");
    adminMenu(ls);
}
void displayAll(List* ls) {
    if(ls->size <1){
        cout << "\n\n\n\t\t\tThere is no product at the moment\n";
        return;
    }
    Element* tmp = ls->head;
    title("DISPLAY ALL THE PRODUCT");
    headerForDisplayProduct();cout << "\n\n";
    while (tmp != nullptr) {
            printElement(tmp);
            tmp = tmp->next;
            cout << endl;

    }
    cout << endl;
}

