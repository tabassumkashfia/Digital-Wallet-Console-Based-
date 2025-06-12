# 💸 RPay: A Console-Based Mobile Finance App

**RPay** is a C++ OOP-based digital wallet application that simulates a mobile finance system. Inspired by real-world apps like **bKash** and **GPay**, this console application allows users to register, log in, and perform common financial tasks such as sending money, making payments, mobile recharge, and viewing transaction history.

🌟 Features of RPay – Mobile Finance Console App
👤 User Management
User Registration

New users can register with a unique username and secure password.

User Login

Registered users can log in with their credentials.

Account Balance Tracking

Each user has an individual wallet balance that updates with every transaction.

💸 Transactions
Send Money

Users can send money to another registered user.

Balance is deducted from the sender and added to the receiver.

Make Payment

Pay merchants or services using the “Make Payment” option.

Common use-cases: shopping, online services, etc.

Mobile Recharge

Recharge a mobile number by deducting the amount from the user’s balance.

Pay Bills

Pay utility bills (e.g., electricity, water, internet).

Amount is deducted and recorded with a timestamp.

🧾 Transaction History
Per-User Logging

Each user’s transactions are saved in their own history file.

Includes Details:

Transaction type

Amount

Date and time

Persistent Storage

History remains even after the program exits.

🔐 Security & Validation
Basic Input Validation

Prevents invalid usernames, duplicate registrations, or sending to non-existent users.

File-based Authentication

Passwords and user data are stored and verified via local text files.

🛠 Admin Mode (optional/extendable):
View all registered users

Access all transaction logs

### 👤 User Mode:
- 🔐 User Registration & Login
- 💸 Send Money
- 🛍 Make Payments (e.g., shopping)
- 📱 Mobile Recharge
- 💡 Pay Bills (electricity, water, etc.)
- 🧾 View Transaction History (logged to file with timestamps)
- 💰 Check Balance

### 🛠 Admin Mode:
- 🔍 View all registered users
- 🧾 View overall transaction logs (if implemented)

## 🧰 Technologies Used

- **C++**
- **OOP Concepts:** Classes, Encapsulation, File Handling
- **Standard Libraries:** `<iostream>`, `<fstream>`, `<ctime>`, `<vector>`, etc.
🧪 Usage Flow
Launch the app

Choose:

1 → Register

2 → User Login

3 → Admin Login

4 → Exit

User Menu (after login):

1 → Send Money

2 → Make Payment

3 → Mobile Recharge

4 → Pay Bills

5 → Show Transaction History

6 → Show Balance

7 → Logout

🗂 Transaction History
Each transaction is stored in a text file (history.txt) with:

Username

Transaction type

Amount

Timestamp

📌 Each user has their own individual transaction log file for better organization.

🧑‍💻 Author
Kashfia Tabassum
📧 Email: your-email@example.com
🔗 LinkedIn

⚠️ Limitations
No real encryption (for educational use only)

Console UI (no graphics or GUI yet)

Data is stored in plain text files

🔒 This project is intended for learning OOP and file handling in C++. For production-level apps, secure authentication and encrypted databases are necessary.
