#include <iostream>

using namespace std;

int main()
{
    int year;

    cout << "Type a year here to determine if it is a leap year. > ";
    cin >> year;

    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) 
    {
        cout << "The year " << year << " is a leap year." << endl;
    }
    else
    {
        cout << "The year " << year << " is not a leap year." << endl;
    }

    return 0;
}