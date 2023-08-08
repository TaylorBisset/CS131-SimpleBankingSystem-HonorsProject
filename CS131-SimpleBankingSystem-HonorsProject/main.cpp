#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

/* - - - - - Function prototypes - - - - - */

void   displayStartMenu();
void   login();
void   displayProfileMenu();
void   createProfile();
bool   validLogin;
bool   usernameExists(string username);
string getValidUsername();
string getValidPassword();
string username = "username";
string password = "password";

/* - - - - - main - - - - - */

int main()
{
    cout << "Welcome to Bisset Bank!\n\n";
    displayStartMenu();
}

/* - - - - - FUNCTIONS - - - - - */

// Start Menu function
void displayStartMenu()
{
    int startMenu = 0;
    while (startMenu != 3)
    {
        cout << "\nWhat would you like to do?\n";
        cout << "1 = Login\n2 = Create Profile\n3 = Exit Program\n";
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
    cin >> loginUsername;
    cout << "Password: ";
    cin >> loginPassword;

    ifstream profileFile("Profiles\\" + loginUsername + ".txt");
    if (profileFile.is_open())
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

    if (loginUsername == username)
    {
        if (loginPassword == password)
        {
            validLogin = true;
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
        while (profileMenu != 3)
        {
            cout << "\nWelcome to your Bisset Bank Account, " << username << endl;
            cout << "\nWhat would you like to do?\n";
            cout << "1 = View Accounts\n2 = Edit Profile\n3 = Logout\n";
            cin >> profileMenu;
            cin.ignore();

            switch (profileMenu)
            {
            case 1:
                //viewProfileAccounts()
                break;
            case 2:
                //editProfile()
                break;
            case 3:
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

// Create Profile function
void createProfile()
{
    cout << "\nLet's create a new profile for you!\n";
    username = getValidUsername();
    password = getValidPassword();

    ofstream profileFile("Profiles\\" + username + ".txt");
    if (!profileFile.is_open())
    {
        cout << "Error creating profile for user \"" << username << "\".\n";
        return;
    }
    if (profileFile.is_open())
    {
        profileFile << "Username: " << username << endl;
        profileFile << "Password: " << password << endl;

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
    ifstream profileFile("Profiles\\" + username + ".txt");
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
