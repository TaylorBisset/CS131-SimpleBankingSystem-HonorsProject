#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <filesystem>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
namespace fs = std::filesystem;

/* - - - - - Objects - - - - - */
class Account 
{
private:
    int accountNumber;
    double accountValue;

public:
    Account(int number, double value) : accountNumber(number), accountValue(value) {}
    int getAccountNumber() const
    {
        return accountNumber;
    }
    double getAccountValue() const
    {
        return accountValue;
    }

    void updateAccountValue(double amount)
    {
        accountValue += amount;
    }
};

Account* findAccountByNumber(vector<Account>& accounts, int accountNumber) 
{
    for (Account& account : accounts) 
    {
        if (account.getAccountNumber() == accountNumber) 
        {
            return &account;
        }
    }
    return nullptr;
}

/* - - - - - Function prototypes - - - - - */

int main();

void displayStartMenu();
void login();
void displayProfileMenu();
void viewProfileDetails();
void transferFunds(vector<Account>& userAccounts);
void addAccount(vector<Account>& userAccounts);
void editProfile();
void updatePassword();
void updateName();
void updateAge();
void updateAddress();
void createProfile();

bool validLogin;
bool usernameExists(string username);

string getValidUsername();
string getValidPassword();
string username = "username";
string password = "password";

vector<Account> userAccounts;

/* - - - - - main - - - - - */

int main()
{
    if (!fs::exists("profiles"))
    {
        fs::create_directory("profiles");
        cout << "Created \"profiles\" directory.\n";
    }

    cout << "Welcome to Bisset Bank!\n\n";
    displayStartMenu();

    // End program sequence
    cout << endl << endl;
#ifdef _WIN32
    system("pause");
#else
    cout << "Press any key to continue . . . ";
    cin.get();
#endif
    return 0;
}

/* - - - - - FUNCTIONS - - - - - */

// Start Menu function
void displayStartMenu()
{
    int startMenu = 0;
    while (startMenu != 3)
    {
        cout << "\nWhat would you like to do?\n";
        cout << "1 = Login\n";
        cout << "2 = Create Profile\n";
        cout << "3 = Exit Program\n";
        cin >> startMenu;
        cin.ignore();

        switch (startMenu)
        {
        case 1:
            login();
            break;
        case 2:
            createProfile();
            break;
        case 3:
            cout << "\nThank you for using Bisset Bank. Goodbye!\n";
            return;
        default:
            cout << "\nInvalid option. Please try again.\n";
            break;
        }
    }
}

// Login function
void login()
{
    string loginUsername;
    string loginPassword;

    cout << "\nFill in your login information below\n";

    cout << "Username: ";
    getline(cin, loginUsername);
    cout << "Password: ";
    getline(cin, loginPassword);

    ifstream profileFile("profiles\\" + loginUsername + ".txt");
    if (!profileFile.is_open())
    {
        cout << "Error opening file for user \"" << loginUsername << "\".\n";
        displayStartMenu();
        return;
    }
    
    string storedUsername;
    string storedPassword;

    profileFile.ignore(10);                 // ignore "Username: "
    getline(profileFile, storedUsername);
    profileFile.ignore(10);                 // ignore "Password: "
    getline(profileFile, storedPassword);

    if (loginUsername == storedUsername)
    {
        if (loginPassword == storedPassword)
        {
            validLogin = true;

            // Read account info for userAccount account vector
            int accountNumber;
            double accountValue;
            string accountLine;
            while (getline(profileFile, accountLine))
            {
                if (accountLine.empty())
                {
                    break;
                }

                int accountNumberPos = accountLine.find("Account Number: ");
                if (accountNumberPos != string::npos)
                {
                    int accountNumber = stoi(accountLine.substr(accountNumberPos + 16));

                    int accountValuePos = accountLine.find("Account Value: ");
                    if (accountValuePos != string::npos)
                    {
                        double accountValue = stod(accountLine.substr(accountValuePos + 15));

                        userAccounts.push_back(Account(accountNumber, accountValue));
                    }
                }
            }

            displayProfileMenu();
        }
        else
        {
            cout << "Password: \"" << loginPassword << "\" does not match.\n";
            cout << "Would you like to try again? (y/n): ";
            char tryAgain;
            cin >> tryAgain;
            cin.ignore();
            int count = 0;
            if (tryAgain == 'y' && count < 3)
            {
                login();
                count++;
            }
            else if (count >= 3)
            {
                cout << "Too many attempts.\n";
                displayStartMenu();
            }
            else
            {
                displayStartMenu();
            }
        }
    }
    else
    {
        cout << "Username: \"" << loginUsername << "\" does not match.\n";
        cout << "Would you like to try again? (y/n): ";
        char tryAgain;
        cin >> tryAgain;
        cin.ignore();
        int count = 0;
        if (tryAgain == 'y' && count < 3)
        {
            login();
            count++;
        }
        else if (count >= 3)
        {
            cout << "Too many attempts.\n";
            displayStartMenu();
        }
        else
        {
            displayStartMenu();
        }
    }
}

// Profile Menu function
void displayProfileMenu()
{
    while (validLogin)
    {
        int profileMenu = 0;
        while (profileMenu != 5)
        {
            cout << "\nWelcome to your Bisset Bank Account.\n";
            cout << "\nWhat would you like to do?\n";
            cout << "1 = View Profile Details\n";
            cout << "2 = Edit Profile\n";
            cout << "3 = Transfer Funds\n";
            cout << "4 = Add Account\n";
            cout << "5 = Logout\n";
            cin >> profileMenu;
            cin.ignore();

            switch (profileMenu)
            {
            case 1:
                viewProfileDetails();
                break;
            case 2:
                editProfile();
                break;
            case 3:
                transferFunds(userAccounts);
                break;
            case 4:
                addAccount(userAccounts);
                break;
            case 5:
                cout << "\nLogging out...\n";
                validLogin = false;
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
                break;
            }
        }
    }
}

// View Profile Details
void viewProfileDetails()
{
    string profileFilePath = "profiles\\" + username + ".txt";

    ifstream profileFile(profileFilePath);
    if (!profileFile.is_open())
    {
        cout << "Error opening profile file for user \"" << username << "\".\n";
        return;
    }

    string line;
    cout << "\nProfile Details:\n";

    while (getline(profileFile, line))
    {
        cout << line << endl;
    }

    profileFile.close();
}

//// View Accounts
//void viewAccounts()
//{
//    cout << "\n\tYour Accounts:\n";
//    for (const Account& account : userAccounts)
//    {
//        cout << "\t\tAccount number: " << account.getAccountNumber() << endl;
//        cout << "\t\t\tAccount value: $" << account.getAccountValue() << endl;
//    }
//}

// Transfer Funds
void transferFunds(vector<Account>& userAccounts) 
{
    cout << "\nTransfer Funds\n";

    int sourceAccountNumber, targetAccountNumber;
    double amount;

    cout << "\tEnter source account number: ";
    cin >> sourceAccountNumber;
    cout << "\tEnter target account number: ";
    cin >> targetAccountNumber;
    cout << "\tEnter amount to transfer: ";
    cin >> amount;

    if (amount <= 0) 
    {
        cout << "\nInvalid amount. Please enter a positive amount.\n";
        return;
    }

    Account* sourceAccount = findAccountByNumber(userAccounts, sourceAccountNumber);
    Account* targetAccount = findAccountByNumber(userAccounts, targetAccountNumber);

    if (!sourceAccount) 
    {
        cout << "\nSource account not found.\n";
        return;
    }
    if (!targetAccount) 
    {
        cout << "\nTarget account not found.\n";
        return;
    }
    if (sourceAccount->getAccountValue() < amount) 
    {
        cout << "\nInsufficient funds in the source account.\n";
        return;
    }

    sourceAccount->updateAccountValue(-amount);
    targetAccount->updateAccountValue(amount);

    cout << "\nFunds transferred successfully!\n";
}

// Add new banking Account
void addAccount(vector<Account>& userAccounts)
{
    // Randomize account number whebn creating new account
    int ascii = 0;
    for (char c : username)
    {
        ascii += static_cast<int>(c);
    }
    srand((ascii + static_cast<unsigned>(time(nullptr)) + clock()) + (ascii + static_cast<unsigned>(time(nullptr)) - clock()) * 11111111);

    int newAccountNumber = (10000000 + (rand() % 90000000));
    double initialBalance = 500.00;

    userAccounts.push_back(Account(newAccountNumber, initialBalance));
    cout << "Account " << newAccountNumber << " added successfully!\n";

    ofstream profileFile("profiles\\" + username + ".txt", ios::app);
    if (!profileFile.is_open())
    {
        cout << "Error opening profile file for user \"" << username << "\".\n";
        return;
    }

    profileFile << "Account Number: " << newAccountNumber << ", Account Value: " << initialBalance << endl;

    profileFile.close();
}

// Edit Profile function
void editProfile()
{
    while (validLogin)
    {
        int editChoice = 0;
        while (editChoice != 5)
        {
            cout << "\nEditing your profile.\n";
            cout << "\nWhat would you like to do?\n";
            cout << "1 = Edit Password\n";
            cout << "2 = Edit Name\n";
            cout << "3 = Edit Age\n";
            cout << "4 = Edit Address\n";
            cout << "5 = Return to Profile Menu\n";
            cin >> editChoice;
            cin.ignore();

            switch (editChoice)
            {
            case 1:
                updatePassword();
                break;
            case 2:
                updateName();
                break;
            case 3:
                updateAge();
                break;
            case 4:
                updateAddress();
                break;
            case 5:
                cout << "\nReturning to Profil Menu\n";
                displayProfileMenu();
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
                break;
            }
        }
    }
}

// Update password
void updatePassword()
{
    string newPassword = getValidPassword();
    string profileFilePath = "profiles\\" + username + ".txt";

    ifstream profileFileIn(profileFilePath);
    if (!profileFileIn.is_open())
    {
        cout << "Error opening profile file for user \"" << username << "\".\n";
        return;
    }

    vector<string> fileLines;
    string line;

    while (getline(profileFileIn, line))
    {
        if (line.find("Password: ") != string::npos)
        {
            line = "Password: " + newPassword;
        }
        fileLines.push_back(line);
    }

    profileFileIn.close();

    ofstream profileFileOut(profileFilePath);
    if (!profileFileOut.is_open())
    {
        cout << "Error opening profile file for writing.\n";
        return;
    }

    for (const string& updatedLine : fileLines)
    {
        profileFileOut << updatedLine << endl;
    }

    profileFileOut.close();

    cout << "Password updated successfully!\n";
}

// Update name
void updateName()
{
    string profileFilePath = "profiles\\" + username + ".txt";

    ifstream profileFileIn(profileFilePath);
    if (!profileFileIn.is_open())
    {
        cout << "Error opening profile file for user \"" << username << "\".\n";
        return;
    }

    vector<string> fileLines;
    string line;

    while (getline(profileFileIn, line))
    {
        if (line.find("Real Name: ") != string::npos)
        {
            string newName;
            cout << "Enter your new name: ";
            getline(cin, newName);
            line = "Real Name: " + newName;
        }
        fileLines.push_back(line);
    }

    profileFileIn.close();

    ofstream profileFileOut(profileFilePath);
    if (!profileFileOut.is_open())
    {
        cout << "Error opening profile file for writing.\n";
        return;
    }

    for (const string& updatedLine : fileLines)
    {
        profileFileOut << updatedLine << endl;
    }

    profileFileOut.close();

    cout << "Name updated successfully!\n";
}

// Update age
void updateAge()
{
    string profileFilePath = "profiles\\" + username + ".txt";

    ifstream profileFileIn(profileFilePath);
    if (!profileFileIn.is_open())
    {
        cout << "Error opening profile file for user \"" << username << "\".\n";
        return;
    }

    vector<string> fileLines;
    string line;

    while (getline(profileFileIn, line))
    {
        if (line.find("Age: ") != string::npos)
        {
            int newAge;
            cout << "Enter your new age: ";
            cin >> newAge;
            cin.ignore();
            line = "Age: " + to_string(newAge);
        }
        fileLines.push_back(line);
    }

    profileFileIn.close();

    ofstream profileFileOut(profileFilePath);
    if (!profileFileOut.is_open())
    {
        cout << "Error opening profile file for writing.\n";
        return;
    }

    for (const string& updatedLine : fileLines)
    {
        profileFileOut << updatedLine << endl;
    }

    profileFileOut.close();

    cout << "Age updated successfully!\n";
}

// Update address
void updateAddress()
{
    string profileFilePath = "profiles\\" + username + ".txt";

    ifstream profileFileIn(profileFilePath);
    if (!profileFileIn.is_open())
    {
        cout << "Error opening profile file for user \"" << username << "\".\n";
        return;
    }

    vector<string> fileLines;
    string line;

    while (getline(profileFileIn, line))
    {
        if (line.find("Address: ") != string::npos)
        {
            string newAddress;
            cout << "Enter your new address: ";
            getline(cin, newAddress);
            line = "Address: " + newAddress;
        }
        fileLines.push_back(line);
    }

    profileFileIn.close();

    ofstream profileFileOut(profileFilePath);
    if (!profileFileOut.is_open())
    {
        cout << "Error opening profile file for writing.\n";
        return;
    }

    for (const string& updatedLine : fileLines)
    {
        profileFileOut << updatedLine << endl;
    }

    profileFileOut.close();

    cout << "Address updated successfully!\n";
}

// Create Profile function
void createProfile()
{
    cout << "\nLet's create a new profile for you!\n";
    username = getValidUsername();
    password = getValidPassword();

    ofstream profileFile("profiles\\" + username + ".txt");
    if (!profileFile.is_open())
    {
        cout << "Error creating profile for user \"" << username << "\".\n";
        return;
    }
    if (profileFile.is_open())
    {
        profileFile << "Username: " << username << endl;
        profileFile << "Password: " << password << endl;
        profileFile << "Real Name: " << username << endl;
        profileFile << "Age: " << 30 << endl;
        profileFile << "Address: " << "123 Main Street" << endl;
        profileFile << "- - - - - - - - - - - - - - - - - - - -" << endl;

        addAccount(userAccounts);
        
        profileFile << "Accounts:\n";
        for (const Account& account : userAccounts)
        {
            profileFile << "Account Number: " << account.getAccountNumber() << ", Account Value: " << account.getAccountValue() << endl;
        }

        profileFile.close();
        cout << "Congratulations!\nProfile created successfully!\n";
    }
    else
    {
        cout << "Error creating the profile file.\n";
    }

    return;
}

// Checks for existing profiles
bool usernameExists(string username)
{
    ifstream profileFile("profiles\\" + username + ".txt");
    return profileFile.good();
}

// Get valid username function
string getValidUsername()
{
    string username;
    bool isUsernameValid = false;

    cout << endl;
    cout << "Please create a new username.\n";
    cout << "Your username must be at least 6 characters long,\n";
    cout << "and must only contain letters and numbers.\n";

    while (!isUsernameValid)                        // initiate while loop to check for a valid username input 
    {
        cout << "\n\tEnter your username here: ";
        getline(cin, username);                     // user inputs their desired username 

        if (usernameExists(username))
        {
            cout << "Username \"" << username << "\" already exists.\nPlease choose a different username.\n";
        }

        if (username.size() > 5)
        {
            isUsernameValid = true;                 // set true, until proven otherwise 
            for (char c : username)                 // range-based for loop 
            {
                if (!isalnum(c) || isspace(c))      // checks if each character is NOT alphanumeric or is a space 
                {
                    isUsernameValid = false;
                    cout << "Invalid username. Please only use letters and numbers.\n";
                    break;
                }
            }
        }
        else if (username.size() < 6)
        {
            cout << "Invalid username. Please ensure there are at least 6 characters.\n";
        }
    }

    if (isUsernameValid == true)
    {
        cout << "\n\tValid username.\n\tYour username is: " << username << endl;
        cout << "\n- - - - - - - - - - - - - - - - - - - -\n";
    }
    return username;
}

// Get valid password function
string getValidPassword()
{
    string password;
    bool isPasswordValid = false;

    cout << endl;
    cout << "Please create a password for your new profile.\n";
    cout << "Your password must be at least 8 characters long, \n";
    cout << "and must contain at least:\n";
    cout << "2 letters,\n2 numbers,\n2 standard special characters (e.g. !@#$%^&*()),\nand no spaces.\n\n";
    cout << "Remember to NEVER share your password with anyone.\n";

    while (!isPasswordValid)                        // initiate while loop to check for a valid password input 
    {
        cout << "\n\tEnter your password here: ";
        getline(cin, password);                     // user inputs their desired password 
        int alphaCount = 0;
        int digitCount = 0;
        int specialCount = 0;

        if (password.size() > 7)
        {
            isPasswordValid = true;                 // set true, until proven otherwise 
            for (char c : password)                 // range-based for loop 
            {
                if (isspace(c))                     // checks if password contains a space 
                {
                    isPasswordValid = false;
                    cout << "Invalid password. Please do not use spaces.\n";
                }
                if (isalpha(c))                     // checks password for letters 
                {
                    alphaCount++;
                }
                if (isdigit(c))                     // checks password for numbers 
                {
                    digitCount++;
                }
                if (c == '!' || c == '@' || (c >= '#' && c <= '&') || (c >= '(' && c <= '*')) // checks for special characters 
                {
                    specialCount++;
                }
            }
        }
        else
        {
            cout << "Invalid password. Please ensure there are at least 8 characters.\n";
            isPasswordValid = false;
        }
        if (alphaCount < 2)
        {
            cout << "Invalid password. You must use at least 2 letters.\n";
            isPasswordValid = false;
        }
        if (digitCount < 2)
        {
            cout << "Invalid password. You must use at least 2 numbers.\n";
            isPasswordValid = false;
        }
        if (specialCount < 2)
        {
            cout << "Invalid password. You must use at least 2 standard special characaters (e.g. !@#$%^&*()).\n";
            isPasswordValid = false;
        }
    }
    cout << "\n\tValid password.\n\tYour password is: " << password << endl;
    cout << "\n- - - - - - - - - - - - - - - - - - - -\n";
    return password;
}

/*
for file pathing to be OS independent, I should consider the following snippet

`
fs::path profileFilePath = fs::path("profiles") / (username + ".txt");
std::ifstream profileFile(profileFilePath);
`

*/
