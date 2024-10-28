# Bank Management System

Welcome to **VR International Bank** – a Bank Management System developed in C. This project provides a user-friendly, terminal-based interface for managing bank accounts. Users can create, view, edit, and delete accounts, perform transactions, and manage multiple accounts within a secure directory-based structure.

## Features

1. **Account Creation and Management**:
   - Users can register if they don’t have an existing account.
   - A unique directory, named `surname_name`, is created for each user. Within this directory, account files are stored with the format: `surname_name_numberofaccount_account.txt`.
   - Each account file stores the account holder’s name, a randomly generated IBAN, account balance, and currency type.

2. **Transaction Options**:
   - Users can transfer money between accounts, with transactions recorded directly in the account files.
   - Transactions are available once users log in and select an account.

3. **Menu Navigation**:
   - After logging in, users can navigate through options:
     - **View Account** `(v)`: Display account details.
     - **Edit Account** `(e)`: Update account information.
     - **Make a Transaction** `(t)`: Transfer funds between accounts.
     - **Create an Account** `(c)`: Open a new account.
     - **Select Account** `(a)`: Choose an account to manage.
     - **Delete Account** `(d)`: Remove an account from the system.
     - **Quit** `(q)`: Exit the application.

## Example Usage

Here’s a sample interaction flow:

```plaintext
Welcome to VR International Bank!
Are you registered? (y/n): n
--------------------------------
Do you want to register? (y/n): y
Enter your name: Victor
Enter your surname: Racelescu
---------------------
Welcome Victor Racelescu at VR International Bank.
Login (press l): l
Enter your name: Victor
Enter your surname: Racelescu
---------------------
Login successful.
Victor Racelescu has no accounts.
Create account (c)
Please enter your choice: c
Account created successfully.
View account (v)
Edit account (e)
Make a transaction (t)
Create an account (c)
Select account (a)
Delete account (d)
Quit (q)
Please enter your choice: q
Quitting...
```

## Future Enhancements

Future plans could include:
- Additional security layers for authentication.
- More detailed transaction logs and history.
- Expanded support for other banking features like account statements.
