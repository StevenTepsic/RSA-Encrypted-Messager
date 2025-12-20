// RSA Crypt.cpp : This file contains the 'main' function. Program execution begins and ends there.
// *This program is to convert numbers and characters with RSA encryption 
//
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cmath> 
#include <map>
#include <string>
#include "RSA header.h"



int main()
{
    //initialize algorithmic variables
    int selection = 0;
    string input;   

    cout << "Enter 'p':";  //obtain p value from user

    cin >> p;

    cout << endl << "Enter 'q':";  //obtain q from user

    cin >> q;

    cout << endl << "Enter 'e':";  //obtain q from user

    cin >> e;

    calcN();
    calcPhi(); 
    d = modInverse(e, phi); //calc N, phi, and d

    cout << endl << "Your N value is: " << N << endl;
    cout << "Your phi value is: " << phi << endl;
    cout << "Your d value is: " << d << endl;

    do {
        displayMenu();   //displays menu to user
        selection = getInteger(1, 4, "Please select menu option ");

        switch (selection) {  //paths for user selections
        case 1:
            cout << "Enter the string you wish to be encrypted" << endl;  //encrypts string of characters
            getline(cin, input);
            encryptString(input);
            break;
        case 2:
            encryptNumbers();   //encrypts numbers to numbers *vestigal calculator*
            break;
        case 3:
            decryptString();  //decrypts string of numbers must be seperated by spaces
            break;
        case 4:
            break;
        default:
            cout << "switching error" << endl;
            break;
        }
    } while (selection != 4);

    




}


