# Advanced Account Management System

## Overview

The Advanced Account Management System is a C++ console application designed to manage user accounts with features like sign-up, login, and password retrieval. This program includes basic encryption for storing passwords securely and has robust error handling and input validation to ensure a smooth user experience.

## Features

- **Sign-Up**: Create a new account by providing a username, email, and password. Passwords are stored securely using simple encryption.
- **Login**: Access your account by entering your username and password. The system verifies your credentials and displays account details upon successful login.
- **Password Retrieval**: Retrieve your password by entering your username and registered email. If the details match, the system will display your password.

## How to Use

### Prerequisites

- A C++ compiler (e.g., g++, clang++)
- A command-line interface to run the compiled program

### Compilation

To compile the program, run the following command in your terminal:

```sh
g++ -o account_manager account_manager.cpp
