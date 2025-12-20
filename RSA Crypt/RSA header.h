#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cmath> 
#include <map>
#include <string>
using namespace std;

int p = 3;
int q = 11;
int e = 3;
int N = p * q;
int phi = (p - 1) * (q - 1);
int m;
int d;  //decryptKey

int power(int& a, int n) {  //function to get power without using doubles
    int c = a;
    for (size_t i = 0; i < n - 1; i++)
        a *= c;
    return a;
}

int modPow(int base, int exp, int mod) {  //long form modulo power for more accuracy
    int result = 1;
    base %= mod;

    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }

    return result;
}

int calcPhi() {
    phi = (p - 1) * (q - 1); 
    return phi;//calc phi
}

int calcN() {
    N = p * q;
    return N;  //calc N 
}

int modInverse(int e, int phi) {
    int t = 0, newt = 1;
    int r = phi, newr = e;
    while (newr != 0) {
        int quotient = r / newr;
        int temp = newt;
        newt = t - quotient * newt;
        t = temp;

        temp = newr;
        newr = r - quotient * newr;
        r = temp;
    }
    if (r > 1) return -1; // no inverse exists
    if (t < 0) t += phi;
    return t;
}

void encryptString(string input) {  //function to take entire string and encrypt into numbers RSA
    int securedChar;

    calcN();
    calcPhi();

    map<char, int> charValues;
    for (char c = 'A'; c <= 'Z'; ++c) {
        charValues.emplace(c, c - 'A' + 1);
    }
    charValues.emplace(' ', 32);

    cout << endl;

    for (int i = 0; i < input.size(); i++) {
        char ch = toupper(static_cast<unsigned char>(input[i]));


        if (charValues.count(ch) == 0) {
            continue; //skips unsupported characters
        }
        int m = charValues[ch];
        securedChar = modPow(m, e, N); //encrypt num

        cout << setw(2) << setfill('0') << securedChar << ' ';

    }
    cout << endl << endl;

}

void decryptString() {  //function to decrypt string of numbers into characters through RSA
    int d = modInverse(e, phi);
    if (d < 0) d += phi;

    calcN();
    calcPhi();

    map<int, char> charValues;
    for (char c = 'A'; c <= 'Z'; ++c) {
        charValues.emplace(c - 'A' + 1, c);
    }
    charValues.emplace(32, ' ');

    

    cout << "Enter encrypted message:\n";

    string line;
    getline(cin, line);

    stringstream ss(line);
    int num;

    cout << endl;

    while (ss >> num) {
        int decodedNum = modPow(num, d, N);

        if (charValues.count(decodedNum)) {
            cout << charValues[decodedNum];
        }
    }

    cout << endl << endl;
}

void displayMenu() { //so we can display options to user   credit rafoster17
    cout << "Press 1 if you have a string of characters to be encrypted" << endl;
    cout << "Press 2 if you have individual numbers to be encrypted" << endl;
    cout << "Press 3 to decode a string of numbers seperated by spaces" << endl;
    cout << "Press 4 to exit" << endl;
}

int getInteger(int lowest, int highest, string prompt)  //credit rafoster17
{
    /*
    * This function will get a string input for a number and will call the function isNumber to make sure the user typed in only digits.
    * If the function isNumber returns false the user will be notified and asked to reinput.
    * In addition to the overloaded plain getInteger, this function will also check for low and high constraints
    */
    int number = 0;
    bool needNumber = true;
    //string prompt = "";

    prompt = prompt + to_string(lowest) + " and " + to_string(highest) + " ";
    do {
        cout << prompt;
        cin >> number;
        if (cin.fail()) {
            cout << "Must be a number " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        needNumber = ((number < lowest) || (number > highest)); //check if in bounds
        if (needNumber) {
            cout << "\a Invalid number - please enter" << endl;
        }
    } while (needNumber);

    //cin.ignore(100, '\n');

    return number;
} //getInteger

void encryptNumbers() {  //function to encrypt numbers to numbers from RSA
                         //mostly vestigal function from when it started as a calculator
    while (true) {
        int securedChar;
        string rsaOut = "";
        stringstream ss;
        string holder;
        fstream oF;

        calcN();
        calcPhi();


        cout << "Enter number to be encoded:";

        cin >> m;   //get preencrypted numbers


        securedChar = modPow(m, e, N); //encrypt num

        cout << endl << "Your encrypted character is: " << securedChar << endl;

        ss.str("");
        ss.clear();


        ss << setfill('0') << setw(2) << static_cast<int>(securedChar);  //display all numbers together
        holder = ss.str();
        rsaOut += holder + " ";

        cout << "Your Encrypted message is:" << endl << rsaOut << endl;



        if (cin.fail()) { break; }

    }
}