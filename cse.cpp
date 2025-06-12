#include<iostream>
#include<fstream>
#include<ctime>
#include<map>

using namespace std;
class loginSystem {
    protected:
    static int userCount;

public:
    loginSystem() {
        userCount++; 
    }

    static int getUserCount() {
        return userCount;
    }
protected:
    string username, phnNo, password;
    map<pair<string, string>, pair<string, string> > users;
    const string SALT = "Rpay211"; 
void loadtomap()
     {
        ifstream fin("users.txt");

        string sUser, sPhnNo, sPass, sRole;
        while (fin >> sUser >> sPhnNo >> sPass >> sRole) {
            users[{sUser, sPhnNo}] = {sPass, sRole};
        }
        
        
    }

    string saltedPassword(const string& pass) {
        return pass + SALT;  // Concatenating password with salt
    }
    virtual bool authentication(string& loggedInUser) = 0;
};
int loginSystem::userCount = 0;

class UserRegistration : public loginSystem {
    public:
        void registerUser() {
            cout << "Enter Username: ";
            getline(cin, username);
            cout << "Enter Mobile Number: ";
            getline(cin, phnNo);
            cout << "Enter Password: ";
            getline(cin, password);
            cout << "Enter Role (user/admin): ";
            string role;
            getline(cin, role);
    
            string saltedPass = saltedPassword(password);
    
            // Store user details in a file named after the username
            string filename = username + ".txt";
            ofstream fout(filename, ios::app);
    
            fout << "Username: " << username << endl;
            fout << "Phone Number: " << phnNo << endl;
            fout << "Password: " << saltedPass << endl;
            fout << "Role: " << role << endl;
            fout.close();
            ofstream userdb("users.txt", ios::app);
    if (userdb) {
        userdb << username << " " << phnNo << " " << saltedPass << " " << role << endl;
        userdb.close();
    } else {
        cout << "Error writing to users.txt!\n";
    }
    
            cout << "User registered successfully!\n";
        }
    
        UserRegistration() {
            loadtomap();
        }
        bool authentication(string &loggedInUser) override {} 
    };
    


class userlogin : public loginSystem {
        public:
            userlogin() {
                loadtomap();
            }
        
            bool authentication(string& loggedInUser) override {
                string enteredUsername, enteredPhn, enteredPassword;
                cout << "Enter Username: ";
                getline(cin, enteredUsername);
                cout << "Enter Phone Number: ";
                getline(cin, enteredPhn);
                cout << "Enter Password: ";
                getline(cin, enteredPassword);
        
                string saltedPass = saltedPassword(enteredPassword);
                auto it = users.find({enteredUsername, enteredPhn});
        
                if (it != users.end() && it->second.first == saltedPass && it->second.second == "user") {
                    cout << "User login successful.\n";
                    loggedInUser = enteredUsername;
                    return true;
                }
        
                cout << "Invalid credentials or not a user.\n";
                return false;
            
            }
        };
        
class adminlogin : public loginSystem {
            public:
                adminlogin() {
                    loadtomap();
                }
            
                bool authentication(string& loggedInUser) override {
                    string enteredUsername, enteredPhn, enteredPassword;
                    cout << "Enter Admin Username: ";
                    getline(cin, enteredUsername);
                    cout << "Enter Phone Number: ";
                    getline(cin, enteredPhn);
                    cout << "Enter Password: ";
                    getline(cin, enteredPassword);
            
                    string saltedPass = saltedPassword(enteredPassword);
                    auto it = users.find({enteredUsername, enteredPhn});
            
                    if (it != users.end() && it->second.first == saltedPass && it->second.second == "admin") {
                        cout << "Admin login successful!\n";
                        loggedInUser = enteredUsername;
                        return true;
                    }
            
                    cout << "Invalid admin credentials!\n";
                    return false;
                }
        };
class AdminPanel {
                public:
                    void showMenu() {
                        int choice;
                        while (true) {
                            cout << "\n--- Admin Panel ---\n";
                            cout << "1. View All Users\n";
                            cout << "2. View User Transaction History\n";
                            cout << "3. Exit\n";
                            cout << "Enter your choice: ";
                            cin >> choice;
                            cin.ignore(); // clear newline
                
                            switch (choice) {
                                case 1:
                                cout << "\nTotal number of registered users: " << loginSystem::getUserCount() << endl;
                                    displayAllUsers();
                                    break;
                                case 2:
                                    viewUserTransaction();
                                    break;
                                case 3:
                                    cout << "Exiting Admin Panel...\n";
                                    return;
                                default:
                                    cout << "Invalid choice. Try again.\n";
                            }
                        }
                    }
                
                private:
                    void displayAllUsers() {
                        ifstream fin("users.txt");
                        if (!fin) {
                            cout << "Error: Could not open users.txt\n";
                            return;
                        }
                
                        string sUser, sPhnNo, sPass, sRole;
                        cout << "Registered Users:\n";
                        while (fin >> sUser >> sPhnNo >> sPass >> sRole) {
                            cout << "Username: " << sUser << ", Phone: " << sPhnNo << ", Role: " << sRole << "\n";
                        }
                        fin.close();
                    }
                
                    void viewUserTransaction() {
                        string uname;
                        cout << "Enter username to view transactions: ";
                        getline(cin, uname);
                        string filename = "transactions_" + uname + ".txt";
                        ifstream fin(filename);
                        if (!fin) {
                            cout << "No transaction file found for " << uname << endl;
                            return;
                        }
                
                        string line;
                        cout << "Transactions for " << uname << ":\n";
                        while (getline(fin, line)) {
                            cout << line << endl;
                        }
                        fin.close();
                    }
                };
                           

class UserAccount {
private:
    string username;
    double balance;
    
public:
    UserAccount(const string& username) {
        this->username = username;
        this->balance = 1000.0;  // or load from file if needed
    }

    double getBalance() {
        return balance;
    }

    bool updateBalance(double amount) {
        if (balance + amount < 0) {  
            cout << "Insufficient balance!\n";
            return false;
        }
        balance += amount;
        return true;
    }

};

// Base class for transactions
class Transaction {
public:
    virtual bool process(UserAccount& user, double amount) = 0;//pure virtual function
};


class SendMoney : public Transaction {
public:
    bool process(UserAccount& user, double amount) {
        return user.updateBalance(-amount);  // Deduct money
    }
};

class MakePayment : public Transaction {
public:
    bool process(UserAccount& user, double amount)  {
        return user.updateBalance(-amount);
    }
};

class MobileRecharge : public Transaction {
public:
    bool process(UserAccount& user, double amount)  {
        return user.updateBalance(-amount);
    }
};

class PayBills : public Transaction {
public:
    bool process(UserAccount& user, double amount)  {
        return user.updateBalance(-amount);
    }
};

class TransactionLogger {
public:
    void logTransaction(const string& username, const string& type, double amount) {
        // Get current time and date
        time_t now = time(0);
        tm *ltm = localtime(&now);

        // Format the date and time
        char timeBuffer[80];
        strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", ltm);

        string filename = "transactions_" + username + ".txt";
        ofstream file(filename, ios::app);
        if (file) {
            file << timeBuffer << type << ": taka" << amount << endl;
            file.close();
        } else {
            cout << "Error: Could not open " << filename << " for writing!" << endl;
        }
    }
};

class ShowTransactionHistory {
public:
    void showTransactions(const string& username) {
        string filename = "transactions_" + username + ".txt";
        ifstream file(filename);

        if (file) {
            string line;
            cout << "Transaction history for " << username << ":\n";
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        } else {
            cout << "Error: Could not open " << filename << " for reading!" << endl;
        }
    }
};

class UserPanel 
{
private:
    string username;
    UserAccount Account;
    TransactionLogger logger;
    ShowTransactionHistory History;

public:
    UserPanel(const string& uname) : username(uname), Account(uname) {}

    
public:
    void showMenu() {
        int choice;
        double menu;
        while(true)
       {
        cout << "\n--- Transaction Menu ---\n";
            cout << "1. Send Money\n2. Make Payment\n3. Mobile Recharge\n4. Pay Bills\n";
            cout << "5. Show Balance\n6. Transaction History\n7. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();  // Ignore newline character left in the buffer
            string type;
            double amount;
            switch (choice) {
                case 1:
                {
                    cout << "Enter amount to send: ";
                    cin >> menu;Transaction* t = new SendMoney();
                    if (t->process(Account, menu)) {
                        logger.logTransaction(username, "Send Money", menu);
                    } else {
                        cout << "Transaction failed.\n";
                    }
                    delete t;
                }
                    break;
                
                case 2:
                    cout << "Enter amount to pay: ";
                    cin >> menu;
                    {Transaction* t = new MakePayment();
                    if (t->process(Account, menu)) {
                        logger.logTransaction(username, "MakePayment", menu);
                    } else {
                        cout << "Transaction failed.\n";
                    }
                    delete t;
                }
                    break;
                case 3:
                    cout << "Enter amount for mobile recharge: ";
                    cin >> menu;
                    {Transaction* t = new MobileRecharge();
                    if (t->process(Account, menu)) {
                        logger.logTransaction(username, "MobileRecharge", menu);
                    } else {
                        cout << "Transaction failed.\n";
                    }
                    delete t;
                }
                    break;
                case 4:
                    cout << "Enter amount for bill payment: ";
                    cin >> menu;
                    {Transaction* t = new PayBills();
                    if (t->process(Account, menu)) {
                        logger.logTransaction(username, "PayBills", menu);
                    } else {
                        cout << "Transaction failed.\n";
                    }
                    delete t;
                }
                    break;
                case 5:
                    cout << "Current balance: " << Account.getBalance() << endl;
                    break;
                case 6:
                    History.showTransactions(username);
                    break;
                case 7:
                    cout << "Logging out...\n";
                    return; // Exit the loop and logout
                default:
                    cout << "Invalid choice! Please try again.\n";
            }

       }
    }

};

int main() {
    int choice;
    while (true) {
        cout << "\n--- Welcome to RPay ---\n";
        cout << "1. Register\n";
        cout << "2. User Login\n";
        cout << "3. Admin Login\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            UserRegistration reg;
            reg.registerUser();
        } else if (choice == 2) {
            userlogin user;
            string loggedInUser;
            if (user.authentication(loggedInUser)) {
                UserPanel panel(loggedInUser);
                panel.showMenu();
            } else {
                cout << "Login failed.\n";
            }
        } else if (choice == 3) {
            string loggedInAdmin;
            adminlogin admin;
            if (admin.authentication(loggedInAdmin)) {
                AdminPanel adminPanel;
                adminPanel.showMenu();
            } else {
                cout << "Admin login failed.\n";
            }
        } else if (choice == 4) {
            cout << "Exiting. Thank you!\n";
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}
