# Banking System
This is a simple banking system implemented in C++ that allows users to perform various banking operations such as opening an account, checking balance, depositing money, withdrawing money, closing an account, and showing all accounts.

### Features
- Open Account: Users can open a new account by providing their first name, last name, and initial balance.
- Balance Enquiry: Users can check the balance of their account by providing the account number.
- Deposit: Users can deposit money into their account by providing the account number and the amount to deposit.
- Withdrawal: Users can withdraw money from their account by providing the account number and the amount to withdraw.
- Close Account: Users can close their account by providing the account number.
- Show All Accounts: Users can view details of all the accounts present in the bank.
### Requirements
- C++ compiler
- Standard Template Library (STL)
### How to Use
- Compile the code using any C++ compiler.
- Run the compiled executable.
- Follow the on-screen instructions to perform various banking operations.
### Usage Example
```
***Banking System***

        Select one option below:
        1 Open an Account
        2 Balance Enquiry
        3 Deposit
        4 Withdrawal
        5 Close an Account
        6 Show All Accounts
        7 Quit
Enter your choice: 1
Enter First Name: John
Enter Last Name: Doe
Enter initial Balance: 1000

Congratulations! Account is Created
First Name: John
Last Name: Doe
Account Number: 1
Balance: 1000

...

Enter your choice: 7

```

### File Structure
- main.cpp: Contains the main program logic.
- Account.cpp and Account.h: Define the Account class and its methods for account management.
- Bank.cpp and Bank.h: Define the Bank class and its methods for bank operations.
- Bank.data: File to store account data persistently.
### Note
The minimum balance required to keep the account open is set to 500 units (MIN_BALANCE).
