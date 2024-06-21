#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cstdlib> // for exit()

using namespace std;

class AccountManager {
    string username, email, password;
    string searchUsername, searchPassword, searchEmail;
    fstream file;

    string encrypt(const string &password) {
        string encrypted = password;
        for (char &c : encrypted) {
            c += 3; // Simple Caesar cipher for illustration
        }
        return encrypted;
    }

    string decrypt(const string &password) {
        string decrypted = password;
        for (char &c : decrypted) {
            c -= 3;
        }
        return decrypted;
    }

public:
    void login();
    void signUp();
    void retrievePassword();
    void inputValidation(string &input, const string &prompt);
};

void AccountManager::inputValidation(string &input, const string &prompt) {
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (!input.empty()) break;
        cout << "Input cannot be empty. Please try again.\n";
    }
}

void AccountManager::signUp() {
    cout << "\n----- Sign Up -----\n";
    inputValidation(username, "Enter Your Username: ");
    inputValidation(email, "Enter Your Email Address: ");
    inputValidation(password, "Enter Your Password: ");

    file.open("userData.txt", ios::out | ios::app);
    if (!file) {
        cerr << "File could not be opened for writing.\n";
        return;
    }
    file << username << "*" << email << "*" << encrypt(password) << endl;
    file.close();
    cout << "Account created successfully!\n";
}

void AccountManager::login() {
    cout << "\n----- Login -----\n";
    inputValidation(searchUsername, "Enter Your Username: ");
    inputValidation(searchPassword, "Enter Your Password: ");

    file.open("userData.txt", ios::in);
    if (!file) {
        cerr << "File could not be opened for reading.\n";
        return;
    }

    bool found = false;
    while (getline(file, username, '*') &&
           getline(file, email, '*') &&
           getline(file, password)) {
        if (username == searchUsername && decrypt(password) == searchPassword) {
            cout << "Account Login Successful!\n";
            cout << "Username: " << username << "\n";
            cout << "Email: " << email << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Invalid username or password.\n";
    }
    file.close();
}

void AccountManager::retrievePassword() {
    cout << "\n----- Retrieve Password -----\n";
    inputValidation(searchUsername, "Enter Your Username: ");
    inputValidation(searchEmail, "Enter Your Email Address: ");

    file.open("userData.txt", ios::in);
    if (!file) {
        cerr << "File could not be opened for reading.\n";
        return;
    }

    bool found = false;
    while (getline(file, username, '*') &&
           getline(file, email, '*') &&
           getline(file, password)) {
        if (username == searchUsername && email == searchEmail) {
            cout << "Account Found!\n";
            cout << "Your Password: " << decrypt(password) << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Account not found.\n";
    }
    file.close();
}

int main() {
    AccountManager account;
    char option;

    while (true) {
        cout << "\n----- Main Menu -----\n";
        cout << "1 - Login\n";
        cout << "2 - Sign-Up\n";
        cout << "3 - Forgot Password\n";
        cout << "4 - Exit\n";
        cout << "Enter Your Choice: ";
        cin >> option;
        cin.ignore(); // To ignore the newline character left in the input buffer

        switch (option) {
            case '1':
                account.login();
                break;
            case '2':
                account.signUp();
                break;
            case '3':
                account.retrievePassword();
                break;
            case '4':
                cout << "Exiting program...\n";
                exit(0);
            default:
                cout << "Invalid selection. Please try again.\n";
        }
    }
    return 0;
}
