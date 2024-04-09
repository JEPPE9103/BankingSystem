#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>

#define MIN_BALANCE 500

enum MenuChoice {
    OPEN_ACCOUNT = 1,
    BALANCE_ENQUIRY,
    DEPOSIT,
    WITHDRAW,
    CLOSE_ACCOUNT,
    SHOW_ACCOUNTS,
    QUIT
};

class InsufficientFunds {};

class Account {
private:
    long accountNumber;
    std::string firstName;
    std::string lastName;
    float balance;
    static long NextAccountNumber;

public:
    Account();
    Account(std::string fname, std::string lname, float balance);
    long getAccNo() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    float getBalance() const;
    void Deposit(float amount);
    void Withdraw(float amount);
    static void setLastAccountNumber(long accountNumber);
    static long getLastAccountNumber();
    friend std::ofstream &operator<<(std::ofstream &ofs, const Account &acc);
    friend std::ifstream &operator>>(std::ifstream &ifs, Account &acc);
    friend std::ostream &operator<<(std::ostream &os, const Account &acc);
};

long Account::NextAccountNumber = 0;

class Bank {
private:
    std::map<long, Account> accounts;

public:
    Bank();
    Account OpenAccount(std::string fname, std::string lname, float balance);
    Account BalanceEnquiry(long accountNumber) const;
    Account Deposit(long accountNumber, float amount);
    Account Withdraw(long accountNumber, float amount);
    void CloseAccount(long accountNumber);
    void ShowAllAccounts() const;
    ~Bank();
};

int main() {
    Bank b;
    int choice;
    std::string fname, lname;
    long accountNumber;
    float balance;
    float amount;

    std::cout << "***Banking System***" << std::endl;
    do {
        std::cout << "\n\tSelect one option below:";
        std::cout << "\n\t1 Open an Account";
        std::cout << "\n\t2 Balance Enquiry";
        std::cout << "\n\t3 Deposit";
        std::cout << "\n\t4 Withdrawal";
        std::cout << "\n\t5 Close an Account";
        std::cout << "\n\t6 Show All Accounts";
        std::cout << "\n\t7 Quit";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        Account acc; 

        switch (choice) {
                case OPEN_ACCOUNT:
                std::cout << "Enter First Name: ";
                std::cin >> fname;
                std::cout << "Enter Last Name: ";
                std::cin >> lname;
                std::cout << "Enter initial Balance: ";
                std::cin >> balance;
                acc = b.OpenAccount(fname, lname, balance);  // Assign the value here
                std::cout << std::endl << "Congratulations! Account is Created" << std::endl;
                std::cout << acc;
                break;

            case BALANCE_ENQUIRY:
                std::cout << "Enter Account Number: ";
                std::cin >> accountNumber;
                acc = b.BalanceEnquiry(accountNumber);
                std::cout << std::endl << "Your Account Details" << std::endl;
                std::cout << acc;
                break;

            case DEPOSIT:
                std::cout << "Enter Account Number: ";
                std::cin >> accountNumber;
                std::cout << "Enter Balance: ";
                std::cin >> amount;
                acc = b.Deposit(accountNumber, amount);
                std::cout << std::endl << "Amount is Deposited" << std::endl;
                std::cout << acc;
                break;

            case WITHDRAW:
                std::cout << "Enter Account Number: ";
                std::cin >> accountNumber;
                std::cout << "Enter Balance: ";
                std::cin >> amount;
                acc = b.Withdraw(accountNumber, amount);
                std::cout << std::endl << "Amount Withdrawn" << std::endl;
                std::cout << acc;
                break;

            case CLOSE_ACCOUNT:
                std::cout << "Enter Account Number: ";
                std::cin >> accountNumber;
                b.CloseAccount(accountNumber);
                std::cout << std::endl << "Account is Closed";
                break;

            case SHOW_ACCOUNTS:
                b.ShowAllAccounts();
                break;

            case QUIT:
                break;

            default:
                std::cout << "\nEnter correct choice";
                exit(0);
        }
    } while (choice != QUIT);

    return 0;
}

Account::Account() {
}

Account::Account(std::string fname, std::string lname, float balance) {
    NextAccountNumber++;
    accountNumber = NextAccountNumber;
    firstName = fname;
    lastName = lname;
    this->balance = balance;
}

long Account::getAccNo() const {
    return accountNumber;
}

std::string Account::getFirstName() const {
    return firstName;
}

std::string Account::getLastName() const {
    return lastName;
}

float Account::getBalance() const {
    return balance;
}

void Account::Deposit(float amount) {
    balance += amount;
}

void Account::Withdraw(float amount) {
    if (balance - amount < MIN_BALANCE)
        throw InsufficientFunds();
    balance -= amount;
}

void Account::setLastAccountNumber(long accountNumber) {
    NextAccountNumber = accountNumber;
}

long Account::getLastAccountNumber() {
    return NextAccountNumber;
}

std::ofstream &operator<<(std::ofstream &ofs, const Account &acc) {
    ofs << acc.accountNumber << std::endl;
    ofs << acc.firstName << std::endl;
    ofs << acc.lastName << std::endl;
    ofs << acc.balance << std::endl;
    return ofs;
}

std::ifstream &operator>>(std::ifstream &ifs, Account &acc) {
    ifs >> acc.accountNumber;
    ifs >> acc.firstName;
    ifs >> acc.lastName;
    ifs >> acc.balance;
    return ifs;
}

std::ostream &operator<<(std::ostream &os, const Account &acc) {
    os << "First Name:" << acc.getFirstName() << std::endl;
    os << "Last Name:" << acc.getLastName() << std::endl;
    os << "Account Number:" << acc.getAccNo() << std::endl;
    os << "Balance:" << acc.getBalance() << std::endl;
    return os;
}

Bank::Bank() {
    Account account;
    std::ifstream infile;
    infile.open("Bank.data");
    if (!infile) {
        return;
    }
    while (infile >> account) {
        accounts.insert(std::pair<long, Account>(account.getAccNo(), account));
    }
    Account::setLastAccountNumber(account.getAccNo());
    infile.close();
}

Account Bank::OpenAccount(std::string fname, std::string lname, float balance) {
    std::ofstream outfile;
    Account account(fname, lname, balance);
    accounts.insert(std::pair<long, Account>(account.getAccNo(), account));
    outfile.open("Bank.data", std::ios::trunc);
    std::map<long, Account>::iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++) {
        outfile << itr->second;
    }
    outfile.close();
    return account;
}

Account Bank::BalanceEnquiry(long accountNumber) const {
    std::map<long, Account>::const_iterator itr = accounts.find(accountNumber);
    return itr->second;
}

Account Bank::Deposit(long accountNumber, float amount) {
    std::map<long, Account>::iterator itr = accounts.find(accountNumber);
    itr->second.Deposit(amount);
    return itr->second;
}

Account Bank::Withdraw(long accountNumber, float amount) {
    std::map<long, Account>::iterator itr = accounts.find(accountNumber);
    itr->second.Withdraw(amount);
    return itr->second;
}

void Bank::CloseAccount(long accountNumber) {
    std::map<long, Account>::iterator itr = accounts.find(accountNumber);
    std::cout << "Account Deleted" << std::endl << itr->second;
    accounts.erase(accountNumber);
}

void Bank::ShowAllAccounts() const {
    std::map<long, Account>::const_iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++) {
        std::cout << "Account " << itr->first << std::endl << itr->second << std::endl;
    }
}

Bank::~Bank() {
    std::ofstream outfile;
    outfile.open("Bank.data", std::ios::trunc);
    std::map<long, Account>::const_iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++) {
        outfile << itr->second;
    }
    outfile.close();
}


