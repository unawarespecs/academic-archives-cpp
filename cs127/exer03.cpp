#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

using namespace std;

// ----------------------------------------------------------

string sort(string &str);                   // rearranging the orders of string to test if it is an anagram
string RemSpacePunct(string &str);          // function that removes space and punctuation in std::string
bool areAnagrams(string str1, string str2); // process the string if anagram and returns the value 1 or 0
void palindrome(char sal[120]);             // testing whether the c-string value is palindrome or not
string password();                          // asking the user to enter the password
char menu();                                // displaying choices a, b, and c then returns the answer
char quit();                                // asking the user if he/she wants to quit
string EnterPassword();                     // processing if the password is correct and displaying it with "*" sign

// ----------------------------------------------------------

const string DEFAULT_PASSWORD = "exer_03";
const int MAX_ATTEMPTS = 3;

int main()
{
    char ans, let;
    string pass;

    while (true)
    {
        pass = EnterPassword();

        if (pass == DEFAULT_PASSWORD)
            ans = menu();

    switch_stat:
        switch (ans)
        {
        case 'a':
        {
            system("cls");
            cout << "[a] Check the palindrome" << endl;

            const int PALIN_SIZE = 120;
            char palin[PALIN_SIZE];
            cout << "Type a word: ";
            cin.ignore(1, '\n');
            cin.getline(palin, PALIN_SIZE);
            palindrome(palin);
        }
        break;
        case 'b':
        {
            system("cls");
            cout << "[b] Test if two strings are anagrams" << endl;

            string str1, str2;
            cout << "Testing whether the following strings are anagrams:" << endl
                 << endl;

            cout << "Enter string 1: ";
            cin.ignore(INT_MAX, '\n');

            cin.clear();
            getline(cin, str1);

            cout << "Enter string 2: ";
            cin.clear();
            getline(cin, str2);

            if (areAnagrams(str1, str2))
                cout << "The two strings are anagram of each other." << endl;
            else
                cout << "The two strings are not anagram of each other." << endl;
        }
        break;
        case 'c':
        {
            if (quit() == 'n')
                ans = menu();
            goto switch_stat;
            continue;
        }
        }
        do
        {
            cout << endl
                 << "Do you want to try again [y/n]" << endl
                 << "Choice: ";
            cin >> let;
            let = tolower(let);
        } while (let != 'n' && let != 'y');

        if (let == 'y')
        {
            ans = menu();
            goto switch_stat;
        }
        else if (let == 'n')
            continue;
    }
}

// asking the user if he/she wants to quit
char quit()
{
    char ch, ans;

    while (true)
    {
        cout << "Do you want to quit now? [y/n] " << endl
             << "Choice: ";
        cin >> ch;

        ch = tolower(ch);

        if (ch == 'n')
            return ch;
        else if (ch == 'y')
            exit(EXIT_SUCCESS);
    }
}

// processing if the password is correct and displaying it with "*" sign
string EnterPassword()
{
    int attempts = 0;
    string entered_psw;

    while (attempts < MAX_ATTEMPTS)
    {
        entered_psw = password();

        if (entered_psw != DEFAULT_PASSWORD)
        {
            cout << "Incorrect password. Please try again." << endl
                 << endl;
            attempts++;
        }
        else
        {
            break;
        }
    }

    if (attempts == MAX_ATTEMPTS)
    {
        cout << "You have reached the maximum attempt for password input." << endl
             << "Exiting program now..." << endl;
        exit(EXIT_FAILURE);
    }

    return entered_psw;
}

// displaying choices a, b, and c then returns the answer
char menu()
{
    char choice;

    system("cls");
    cout << "------| Menu |------" << endl
         << "[a] Check the palindrome" << endl
         << "[b] Test if two strings are anagrams" << endl
         << "[c] Exit program" << endl
         << endl;

    while (true)
    {
        try
        {
            cout << "Your choice: ";
            cin >> choice;

            choice = tolower(choice);

            if (choice == 'a' || choice == 'b' || choice == 'c')
            {
                return choice;
                break;
            }
            else
                throw choice;
        }
        catch (char inc_ans)
        {
            cout << "Invalid choice, try again" << endl;
            continue;
        }
    }
}

// asking the user to enter the password
string password()
{
    const char BACKSPACE = 8;
    const char RETURN = 13;
    bool show_asterisk = true;

    string pass;
    unsigned char ch = 0;

    cout << "Enter password: ";

    DWORD con_mode;
    DWORD dwRead;

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

    GetConsoleMode(hIn, &con_mode);
    SetConsoleMode(hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

    while (ReadConsoleA(hIn, &ch, 1, &dwRead, NULL) && ch != RETURN)
    {
        if (ch == BACKSPACE)
        {
            if (pass.length() != 0)
            {
                if (show_asterisk)
                    cout << "\b \b";
                pass.resize(pass.length() - 1);
            }
        }
        else
        {
            pass += ch;
            if (show_asterisk)
                cout << '*';
        }
    }
    cout << endl;
    return pass;
}

// rearranging the orders of string to test if it is an anagram
string sort(string &str)
{
    std::sort(str.begin(), str.end());
    return str;
}

// process the string if anagram and returns the value 1 or 0
bool areAnagrams(string str1, string str2)
{
    cout << "String 1: " << str1 << endl
         << "String 2: " << str2 << endl;

    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);

    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);

    RemSpacePunct(str1);
    RemSpacePunct(str2);

    int n1 = str1.length();
    int n2 = str2.length();

    sort(str1);
    sort(str2);

    // Compare sorted strings
    for (int i = 0; i < n1; i++)
        if (str1[i] != str2[i])
            return false;

    return true;
}

// function that removes space and punctuation in std::string
string RemSpacePunct(string &str)
{
    // rem puncts
    for (int i = 0, len = str.size(); i < len; i++)
    {
        if (ispunct(str[i]))
        {
            str.erase(i--, 1);
            len = str.size();
        }
    }

    str.erase(remove(str.begin(), str.end(), ' '), str.end()); // rem spaces

    return str;
}

// testing whether the c-string value is palindrome or not
void palindrome(char sal[120])
{
    char palin_rev[120];
    char palin_fix[120];
    strcpy(palin_rev, sal);
    strrev(palin_rev);
    cout << "In reverse order: " << palin_rev << endl;
    if (strcmpi(sal, palin_rev) == 0)
    {
        cout << "Entered word is a palindrome" << endl;
    }
    else
    {
        cout << "Entered word is not a palindrome" << endl;
    }
}