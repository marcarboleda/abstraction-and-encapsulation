#include <iostream>
#include <limits>
#include <cstdlib>

using namespace std;

class BankAccount {
protected:
    double accountBalance;

public:
    BankAccount() : accountBalance(0.0) {}  // Initialize to 0
    virtual ~BankAccount() = default;

    virtual string getName() const = 0;
    virtual void deposit(double amount) = 0;
    virtual bool withdraw(double amount) = 0;
    virtual double checkBalance() const = 0;
};

class SavingsAccount final : public BankAccount {
    const double MIN_BALANCE = 1000.0;

public:
    explicit SavingsAccount(double initialBalance) {
        accountBalance = initialBalance;  // Set initial balance
    }

    void deposit(double amount) override {
        if (amount <= 0) {
            cout << "\nInvalid deposit amount. Please enter a positive value." << endl;
        } else {
            accountBalance += amount;
            cout << "\nDeposited: " << amount << ". New balance: " << accountBalance << endl;
        } 
    }

    bool withdraw(double amount) override {
        if (amount <= 0) {
            cout << "\nInvalid withdrawal amount." << endl;
            return false;
        }
        if (accountBalance - amount < MIN_BALANCE) {
            cout << "\nInsufficient balance. Minimum balance of " << MIN_BALANCE << " must be maintained." << endl;
            return false;
        }
        accountBalance -= amount;
        cout << "\nWithdrawn: " << amount << ". New balance: " << accountBalance << endl;
        cout << endl;  
        return true;
    }

    double checkBalance() const override {
        return accountBalance;
    }

    string getName() const override {
        return "\nSavings Account";
    }
};

class CurrentAccount final : public BankAccount {
public:
    explicit CurrentAccount(double initialBalance) {
        accountBalance = initialBalance;  // Set initial balance
    }

    void deposit(double amount) override {
        if (amount <= 0) {
            cout << "\nInvalid deposit amount. Please enter a positive value." << endl;
        } else {
            accountBalance += amount;
            cout << "\nDeposited: " << amount << ". New balance: " << accountBalance << endl;
        }
        cout << endl; 
    }

    bool withdraw(double amount) override {
        if (amount <= 0) {
            cout << "\nInvalid withdrawal amount." << endl;
            return false;
        }
        if (accountBalance - amount < 0) {
            cout << "\nInsufficient balance to complete the withdrawal." << endl;
            return false;
        }

        accountBalance -= amount;
        cout << "\nWithdrawn: " << amount << ". New balance: " << accountBalance << endl;
        cout << endl;  
        return true;
    }

    double checkBalance() const override {
        return accountBalance;
    }

    string getName() const override {
        return "\nCurrent Account";
    }
};

double getValidAmount() {
    double amount;
    while (true) {
        cin >> amount;
        if (cin.fail() || amount < 0) {
            cout << "Invalid input. Please enter a valid amount: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return amount;
        }
    }
}

void accountMenu(BankAccount* account) {
    int subChoice;
    do {
        cout << account->getName() << " Menu\n";
        cout << "[1] Deposit\n[2] Withdraw\n[3] Check Balance\n[4] Back\n";
        cout << "Select an option: ";
        cin >> subChoice;

        switch (subChoice) {
            case 1: {
                cout << "\nEnter amount to deposit: ";
                const double depositAmount = getValidAmount();
                account->deposit(depositAmount);
                break;
            }
            case 2: {
                cout << "\nEnter amount to withdraw: ";
                const double withdrawAmount = getValidAmount();
                account->withdraw(withdrawAmount);
                break;
            }
            case 3: {
                double balance = account->checkBalance();
                if (balance > 0) {
                    cout << "\nCurrent Balance: " << balance << endl;
                } else {
                    cout << "\nThere is no balance available." << endl;
                }  
                break;
            }
            case 4:
                cout << "\nReturning to Main Menu..." << endl;
                cout << endl; 
                break;
            default:
                cout << "\nInvalid option. Please try again." << endl;
        }
    } while (subChoice != 4);
}

int main() {
    SavingsAccount savingsAccount(0.0); // Start with zero balance
    CurrentAccount currentAccount(0.0); // Start with zero balance

    BankAccount* selectedAccount = nullptr;

    string mainChoice;
    do {
        cout << "Main Menu\n";
        cout << "[1] Savings Account\n[2] Current Account\n[3] Exit\n";
        cout << "Select an option: ";
        cin >> mainChoice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid option." << endl;
            cout << endl;  
            continue;
        }

        if (mainChoice == "1") {
            selectedAccount = &savingsAccount;
        } else if (mainChoice == "2") {
            selectedAccount = &currentAccount; 
        } else if (mainChoice == "3") {
            cout << "\nExiting the system. Goodbye!\n" << endl;
        } else {
            cout << "Invalid option. Please try again." << endl;
            cout << endl;
            continue; 
        }

        if (selectedAccount) {
            accountMenu(selectedAccount);
            selectedAccount = nullptr; 
        }
    } while (mainChoice != "3");

    return 0;
}