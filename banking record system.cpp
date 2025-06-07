#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

class Account {
public:
    int accountNumber;
    string name;
    double balance;

    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void showAccount() const {
        cout << left << setw(10) << accountNumber
             << setw(20) << name
             << "Rs. " << fixed << setprecision(2) << balance << endl;
    }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance.\n";
            return false;
        }
        balance -= amount;
        return true; }
    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }
};

vector<Account> accounts;

void saveAccountsToFile() {
    ofstream file("accounts.txt");
    for (const auto& acc : accounts) {
        file << acc.accountNumber << "," << acc.name << "," << acc.balance << endl;
    }
    file.close();
}

void loadAccountsFromFile() {
    accounts.clear();
    ifstream file("accounts.txt");
    int accNum;
    string name;
    double balance;
    string line;
    while (getline(file, line)) {
        sscanf(line.c_str(), "%d,%[^,],%lf", &accNum, &name[0], &balance);
        Account acc;
        acc.accountNumber = accNum;
        acc.name = name;
        acc.balance = balance;
        accounts.push_back(acc);
    }
    file.close();
}

void createAccount() {
    Account acc;
    acc.createAccount();
    accounts.push_back(acc);
    saveAccountsToFile();
    cout << "Account Created Successfully.\n";
}

void displayAllAccounts() {
    if (accounts.empty()) {
        cout << "No accounts available.\n";
        return;
    }
    cout << left << setw(10) << "Acc No" << setw(20) << "Name" << "Balance\n";
    for (const auto& acc : accounts) {
        acc.showAccount();
    }
}

void viewAccount(int accNum) {
    for (const auto& acc : accounts) {
        if (acc.getAccountNumber() == accNum) {
            acc.showAccount();
            return;
        }
    }
    cout << "Account not found.\n";
}

void depositMoney(int accNum, double amount) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == accNum) {
            acc.deposit(amount);
            saveAccountsToFile();
            cout << "Amount Deposited.\n";
            return;
        }
    }
    cout << "Account not found.\n";
}

void withdrawMoney(int accNum, double amount) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == accNum) {
            if (acc.withdraw(amount)) {
                saveAccountsToFile();
                cout << "Amount Withdrawn.\n";
            }
            return;
        }
    }
    cout << "Account not found.\n";
}

void deleteAccount(int accNum) {
    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if (it->getAccountNumber() == accNum) {
            accounts.erase(it);
            saveAccountsToFile();
            cout << "Account Deleted.\n";
            return;
        }
    }
    cout << "Account not found.\n";
}

int main() {
    loadAccountsFromFile();
    int choice, accNum;
    double amount;

    do {
        cout << "\n=== Banking System Menu ===\n";
        cout << "1. Create Account\n";
        cout << "2. View Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Delete Account\n";
        cout << "6. Display All Accounts\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createAccount();
            break;
        case 2:
            cout << "Enter Account Number: ";
            cin >> accNum;
            viewAccount(accNum);
            break;
        case 3:
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Amount: ";
            cin >> amount;
            depositMoney(accNum, amount);
            break;
        case 4:
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Amount: ";
            cin >> amount;
            withdrawMoney(accNum, amount);
            break;
        case 5:
            cout << "Enter Account Number to Delete: ";
            cin >> accNum;
            deleteAccount(accNum);
            break;
        case 6:
            displayAllAccounts();
            break;
        case 7:
            cout << "Exiting... Thank you!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
