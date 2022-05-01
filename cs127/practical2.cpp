#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <limits>

using namespace std;

const int SHOE_MAXIMUM = 10;
const string SHOE_RECORD_FILENAME = "shoeInventory.txt";

struct DatePurchase
{
    unsigned int Day;
    unsigned int Month;
    unsigned int Year;
};

struct Shoe
{
    string StockNum;
    string Type;
    string Brand;
    DatePurchase Date;
    unsigned int Quantity;
    double Cost;
};

struct ShoeRec
{
    Shoe Shoes[SHOE_MAXIMUM];
};

void inputShoe(struct ShoeRec *, int);
void compVal(struct ShoeRec *, int, ofstream &);

/////////////////////////////////////////////////////////////////////

int main()
{
    ofstream output_file;
    output_file.open(SHOE_RECORD_FILENAME.c_str(), ios::app);

    int shoe_size;
    ShoeRec *shoe_inventory;

    while (true)
    {
        try
        {
            cout << "Enter number of shoes to add into the record: ";
            cin >> shoe_size;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(LLONG_MAX, '\n');
            }
            if (!cin.fail())
                if (shoe_size < 1 || shoe_size > SHOE_MAXIMUM)
                    throw shoe_size;

            break;
        }
        catch (...)
        {
            cerr << endl << "You have entered an invalid input, try again (shoe entries must be between 1 and 10).\n";
            continue;
        }
    }

    shoe_inventory = new ShoeRec[shoe_size];
    inputShoe(shoe_inventory, shoe_size);
    compVal(shoe_inventory, shoe_size, output_file);

    output_file.close();
    delete[] shoe_inventory;

    system("pause");
    return EXIT_SUCCESS;
}

/////////////////////////////////////////////////////////////////////

void inputShoe(struct ShoeRec *getshoe, int arr_size)
{
    system("cls");
    cout << "\nEntering the details for " << arr_size << " shoes:\n\n";

    int count = 0;
    while (count < arr_size)
    {
        // stock number
        while (true)
        {
            try
            {
                cout << "Enter stock number for shoe #" << count + 1 << ": ";
                cin >> getshoe[count].Shoes->StockNum;
                if (getshoe[count].Shoes->StockNum.size() > 8)
                    throw getshoe[count].Shoes->StockNum;

                break;
            }
            catch (string stock_err)
            {
                cerr << "Stock Number should be limited to 8 characters only\n\n";
                continue;
            }
        }

        // shoe type
        cout << "Enter shoe type for shoe #" << count + 1 << ": ";
        cin.ignore(LLONG_MAX, '\n');
        getline(cin, getshoe[count].Shoes->Type);

        // shoe brand
        while (true)
        {
            try
            {
                cout << "Enter shoe brand for shoe #" << count + 1 << ": ";
                getline(cin, getshoe[count].Shoes->Brand);
                if (getshoe[count].Shoes->Brand.size() < 1 || getshoe[count].Shoes->Brand.size() > 20)
                    throw getshoe[count].Shoes->Brand;

                break;
            }
            catch (string brand_err)
            {
                cerr << "Shoe brand should be limited to 20 characters only\n\n";
                continue;
            }
        }

        // month of purchase
        while (true)
        {
            try
            {
                cout << "Enter the month of purchase for shoe #" << count + 1 << ": ";
                cin >> getshoe[count].Shoes->Date.Month;
                if (getshoe[count].Shoes->Date.Month < 1 || getshoe[count].Shoes->Date.Month > 12)
                    throw getshoe[count].Shoes->Date.Month;

                break;
            }
            catch (unsigned int month_err)
            {
                cerr << "The month of purchase should be between 1-12 (January-December) only\n\n";
                continue;
            }
        }

        // day of purchase
        while (true)
        {
            try
            {
                cout << "Enter the day of purchase for shoe #" << count + 1 << ": ";
                cin >> getshoe[count].Shoes->Date.Day;
                if (getshoe[count].Shoes->Date.Day < 1 || getshoe[count].Shoes->Date.Day > 31)
                    throw getshoe[count].Shoes->Date.Day;

                break;
            }
            catch (unsigned int day_err)
            {
                cerr << "The day of purchase should be between 1-31 only\n\n";
                continue;
            }
        }

        // year of purchase
        while (true)
        {
            try
            {
                cout << "Enter the year of purchase for shoe #" << count + 1 << ": ";
                cin >> getshoe[count].Shoes->Date.Year;
                if (getshoe[count].Shoes->Date.Year < 2000 || getshoe[count].Shoes->Date.Year > 2021)
                    throw getshoe[count].Shoes->Date.Year;

                break;
            }
            catch (unsigned int year_err)
            {
                cerr << "The year of purchase should be between the years 2000-2021 only\n\n";
                continue;
            }
        }

        // shoe quantity
        while (true)
        {
            try
            {
                cout << "Enter the quantity for shoe #" << count + 1 << ": ";
                cin >> getshoe[count].Shoes->Quantity;
                if (getshoe[count].Shoes->Quantity < 1 || getshoe[count].Shoes->Quantity > 10)
                    throw getshoe[count].Shoes->Quantity;

                break;
            }
            catch (unsigned int quant_err)
            {
                cerr << "The quantity should be between 1-10 only\n\n";
                continue;
            }
        }

        // shoe cost
        cout << "Enter the cost for shoe #" << count + 1 << ": Php ";
        cin >> getshoe[count].Shoes->Cost;

        cout << endl;
        count++;
    }
}

void compVal(struct ShoeRec *tValue, int arr_size, ofstream &file_out)
{
    system("cls");

    // display to console,
    cout << fixed << setprecision(2);
    cout << left;
    cout << "StockNumber Shoe Type           Shoe Brand          Date Purchased   Shoe Quantity    Shoe Cost         Total Value\n" << endl;

    for (int i = 0; i < arr_size; i++)
    {
        cout << setw(12) << tValue[i].Shoes->StockNum
             << setw(20) << tValue[i].Shoes->Type
             << setw(20) << tValue[i].Shoes->Brand
             << setw(0) << tValue[i].Shoes->Date.Month
             << setw(0) << "-" << tValue[i].Shoes->Date.Day 
             << setw(0) << "-" << tValue[i].Shoes->Date.Year
             << setw(8) << " "
             << setw(17) << tValue[i].Shoes->Quantity
             << setw(0) << "Php " << setw(14) << tValue[i].Shoes->Cost
             << "Php " << setw(0) << (tValue[i].Shoes->Cost * tValue[i].Shoes->Quantity)
             << endl;
    }
    cout << endl;

    // then output to file
    file_out << fixed << setprecision(2);
    file_out << left;
    file_out << "StockNumber Shoe Type           Shoe Brand          Date Purchased   Shoe Quantity    Shoe Cost         Total Value\n" << endl;

    for (int i = 0; i < arr_size; i++)
    {
        file_out << setw(12) << tValue[i].Shoes->StockNum
             << setw(20) << tValue[i].Shoes->Type
             << setw(20) << tValue[i].Shoes->Brand
             << setw(0) << tValue[i].Shoes->Date.Month
             << setw(0) << "-" << tValue[i].Shoes->Date.Day 
             << setw(0) << "-" << tValue[i].Shoes->Date.Year
             << setw(8) << " "
             << setw(17) << tValue[i].Shoes->Quantity
             << setw(0) << "Php " << setw(14) << tValue[i].Shoes->Cost
             << "Php " << setw(0) << (tValue[i].Shoes->Cost * tValue[i].Shoes->Quantity)
             << endl;
    }
    file_out << endl;

    cout << "Record saved to " << SHOE_RECORD_FILENAME << ".\n";
}