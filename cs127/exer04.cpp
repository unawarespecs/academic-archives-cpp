#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <limits>
#include <conio.h>
#include <windows.h>

using namespace std;

// --------------- Structs ---------------

struct Item
{
    string Name;
    double Price;
    unsigned int Stock;
    unsigned int Sold;
};

struct ItemType
{
    int Counter;
    string Type;
    Item item[50];
};

// --------------- End structs ---------------

// --------------- Function prototypes ---------------

void clear_screen();
void display_header();
void display_header_main();
string enter_password();
string enter_username();
bool user_validation();
void add_and_display_inventory(struct ItemType *, int);

// --------------- End function prototypes ---------------

const int MAX_ATTEMPTS = 3;
const string DEFAULT_USER = "admin";
const string DEFAULT_PASSWORD = "exer_04";

int main()
{
    int product_arr_size;
    ItemType *inventory_queue;

    if (user_validation())
        clear_screen();

    // Start with the main bits after the user has authenticated.
    display_header_main();
    cout << "Enter number of products for inventory: ";
    cin >> product_arr_size;
    while (true)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(LLONG_MAX, '\n');
            cout << "You have entered wrong input\n" << endl;

            cout << "Enter number of products for inventory: ";
            cin >> product_arr_size;
        }
        if (!cin.fail())
            break;
    }

    inventory_queue = new ItemType[product_arr_size];
    add_and_display_inventory(inventory_queue, product_arr_size);

    delete[] inventory_queue;
    system("pause");
    return EXIT_SUCCESS;
}

// --------------- Start function definitions. ---------------

// Self-explanatory (clears console)
void clear_screen()
{
    system("cls");
}

// Self-explanatory (displays header)
void display_header()
{
    cout << "-----------------------------------\n"
         << "|                                 |\n"
         << "| PRODUCT INVENTORY SYSTEM CS127L |\n"
         << "|                                 |\n"
         << "-----------------------------------\n";
}

// Self-explanatory (displays header after password entry)
void display_header_main()
{
    string tab = "  ";

    cout << tab << tab << tab << "***** INVENTORY SYSTEM C++.2 *****" << tab << tab << tab << endl
         << endl;
}

// Enter password using Windows API (and also displays asterisks).
string enter_password()
{
    DWORD con_mode;
    DWORD dwRead;

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

    const char BACKSPACE = 8;
    const char RETURN = 13;
    bool show_asterisk = true;

    string pass;
    unsigned char ch = 0;

    cout << "Enter password: ";

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
    SetConsoleMode(hIn, con_mode & (ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
    return pass;
}

// Self-explanatory (enter username prompt)
string enter_username()
{
    cin.clear();
    cin.sync();

    string username;
    cout << "Enter username: ";
    cin >> username;
    return username;
}

// Validate user and password combo.
bool user_validation()
{
    int attempts = 0;
    int attempts_remaining = MAX_ATTEMPTS;

    string entered_psw;
    string entered_user;

    while (attempts < MAX_ATTEMPTS)
    {
        display_header();
        entered_user = enter_username();
        clear_screen();

        display_header();
        entered_psw = enter_password();

        try
        {
            if (entered_user == DEFAULT_USER)
            {
                if (entered_psw != DEFAULT_PASSWORD)
                    throw entered_psw;
                else
                {
                    return true;
                    break;
                }
            }
            else
                throw entered_user;
        }
        catch (string error_credentials)
        {
            clear_screen();
            --attempts_remaining;
            if (attempts_remaining <= 0)
            {
                cerr << "Incorrect username or password.\n"
                     << "You have no attempts left.\n";
            }
            else if (attempts_remaining == 1)
            {
                cerr << "Incorrect username or password. Please try again. \n"
                     << "You have " << attempts_remaining << " attempt left.\n";
            }
            else
            {
                cerr << "Incorrect username or password. Please try again. \n"
                     << "You have " << attempts_remaining << " attempts left.\n";
            }
            attempts++;
        }
    }

    if (attempts == MAX_ATTEMPTS)
    {
        cout << "\nExiting program now...\n";
        exit(EXIT_FAILURE);
    }

    return false;
}

// The main bulk of the program.
void add_and_display_inventory(struct ItemType *item, int arr_size)
{
    cout << "\nEnter " << arr_size << " products:\n";

    int count = 0;
    while (count < arr_size)
    {
        cout << "Product " << count + 1 << ": ";
        cin >> item[count].Type;

        cout << "\nHow many " << item[count].Type << "? ";
        cin >> item[count].Counter;
        
        while (true)
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(LLONG_MAX, '\n');
                cout << "You have entered wrong input" << endl;

                cout << "\nHow many " << item[count].Type << "? ";
                cin >> item[count].Counter;
            }
            if (!cin.fail())
                break;
        }

        for (int i = 0; i < item[count].Counter; i++)
        {
            cout << item[count].Type << "[" << i + 1 << "]: ";
            cin.ignore(LLONG_MAX,'\n');
            getline(cin, item[count].item[i].Name);

            cout << "Price: Php ";
            cin >> item[count].item[i].Price;
            while (true)
            {
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(LLONG_MAX, '\n');
                    cout << "You have entered wrong input" << endl;

                    cout << "Price: Php ";
                    cin >> item[count].item[i].Price;
                }
                if (!cin.fail())
                    break;
            }

            cout << "Stock: ";
            cin >> item[count].item[i].Stock;
            while (true)
            {
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(LLONG_MAX, '\n');
                    cout << "You have entered wrong input" << endl;

                    cout << "Stock: ";
                    cin >> item[count].item[i].Stock;
                }
                if (!cin.fail())
                    break;
            }

            cout << "Sold: ";
            cin >> item[count].item[i].Sold;
            while (true)
            {
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(LLONG_MAX, '\n');
                    cout << "You have entered wrong input" << endl;

                    cout << "Sold: ";
                    cin >> item[count].item[i].Sold;
                }
                if (!cin.fail())
                    break;
            }

            cout << endl;
        }
        count++;
    }

    // FIXME: Find a way to display the second (or more) items
    //        when two or more products are defined.

    clear_screen();
    display_header_main();
    cout << "Prod No. Product         Name                     Price       Stock      Sold      Left      " << endl;
    cout << std::fixed << std::setprecision(2);
    cout << std::left;

    for (int a = 0; a < arr_size; a++)
    {
        cout << setw(9) << a + 1
             << setw(16) << item[a].Type;

        for (int b = 0; b < item[a].Counter; b++)
        {
            if (b == 0)
            {
                cout << setw(25) << item[a].item[b].Name
                     << setw(12) << item[a].item[b].Price
                     << setw(11) << item[a].item[b].Stock
                     << setw(10) << item[a].item[b].Sold
                     << setw(10) << (item[a].item[b].Stock - item[a].item[b].Sold);
            }
            else
            {
                cout << setw(25) << " "
                     << setw(25) << item[a].item[b].Name
                     << setw(12) << item[a].item[b].Price
                     << setw(11) << item[a].item[b].Stock
                     << setw(10) << item[a].item[b].Sold
                     << setw(10) << (item[a].item[b].Stock - item[a].item[b].Sold);
            }
            cout << endl;
        }   
    }
}
