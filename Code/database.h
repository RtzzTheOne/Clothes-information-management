#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<windows.h>
#include<conio.h>  //empty(); pop_back(); _getch();
#include <iomanip>
#include "check.h"
using namespace std;
int numberOfClothes = 0;
// Create the database if
void createDataBase(const string& filename) {
    ifstream fileCheck(filename);
    if (!fileCheck) {
        ofstream file(filename);
        if (file.is_open()) {
            // Sample data
            file << "1,T-shirt,XL,Brown,20.00,10\n";
            file << "2,T-shirt,L,Brown,21.00,10\n";
            file << "3,T-shirt,X,Brown,25.00,10\n";
            file.close();
        } else {
            cout << "Error creating database\n";
        }
    }
    fileCheck.close();
}

// Load data from CSV file into the list
void loadFromData(List* L1,const string& filename) {
    fstream myfile;
    myfile.open(filename, ios::in);  // Read data
    if (!myfile.is_open()) {
        cout << "Error opening file\n";
        return;
    }

    ClothingItem item;
    string data,position, price, quantity;
    while (getline(myfile, data)) {
        stringstream mysplit(data);
        getline(mysplit, position, ',');
        getline(mysplit, item.id, ',');  // Split to get ID
        getline(mysplit, item.name, ',');
        getline(mysplit, item.size, ',');
        getline(mysplit, item.color, ',');
        getline(mysplit, price, ',');
        getline(mysplit, quantity, ',');
        item.position = stoi(position);
        item.quantity = stoi(quantity);
        item.price = stod(price);
        add_at_nth(L1, item,L1->size+1);
        numberOfClothes++;
    }
    myfile.close();
}
void saveToData(List* L1,const string& filename) {
    ofstream myfile(filename, ios::out | ios::trunc);  // Open file in write mode, truncating the file
    if (!myfile.is_open()) {
        cout << "Error opening file\n";
        return;
    }

    Element* tmp = L1->head;
    while (tmp != nullptr) {
        myfile  <<tmp->data.position<<"," << tmp->data.id << "," << tmp->data.name << "," << tmp->data.size
                << ","<< tmp->data.color << "," << tmp->data.price << "," << tmp->data.quantity << "\n";
        tmp = tmp->next;
    }
    myfile.close();
}
