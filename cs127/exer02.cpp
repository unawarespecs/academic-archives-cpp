#include <iostream>
#include <iomanip>
using namespace std;

// NOTE ALL CODES MUST USE pointer variables –input,process and output

// global declaration
int i;
const int asize = 10;
typedef double *pointers; // typedefinition used for miles per gallon pointer variables

// prototype -------------------------------------------------------------------------------------

// for grade elimination
void getInput(double *input);   // prompt the user to input 10 grades
double getLow(double *low);     // compute and returns the value of the lowest grade
double getSum(double *sum);     // compute for the sum of 10 grades
double getAverage(double *avg); // gets average of grades after removal of lowest grade (10 grades - 1 from lowest)

// miles per gallon
void MilesPerrGallon(double *ptr1, double *ptr2, int sz); // final output of the computer miles
                                                          // and gallons

void MperG(); // prompts the user to specify the size of the array for miles and gallons
              // verify and validate the input for miles and gallons using exception handling

// choices and try again
char getChoice(char *ch);  // display the menu of choices and input the choice of the user
char tryAgain(char *resp); // self-explanatory (try again prompt)

// needed to reset cout after displaying grades/mpg
ios_base::fmtflags old_flags = cout.flags();
streamsize old_prec = cout.precision();

// end prototype ----------------------------------------------------------------------------------

int main()
{
    char choice;
    char *chr;
    int opt;

    char tryAgainResponse = 0;
    char *tar;
    tar = &tryAgainResponse;

    // add only declaration here
    do
    {
        chr = &choice;
        opt = getChoice(chr);

        switch (*chr)
        {
        case '1':
            double grade[asize];
            double *ptr;
            double *plow, *psum, *pave;
            double gsum, glow;
            double ave;

            ptr = grade;
            psum = &gsum;
            plow = &glow;
            pave = &ave;

            system("cls");

            cout << "You selected: [1] Grade Average and Elimination" << endl
                 << endl;
            getInput(ptr);

            system("cls");
            gsum = getSum(ptr);
            cout << "Sum: " << *psum << endl;

            glow = getLow(ptr);
            cout << "Lowest: " << *plow << endl;

            ave = getAverage(ptr);

            cout << fixed << setprecision(2);
            cout << "Average: " << *pave << endl;

            cout.precision(old_prec);
            cout.flags(old_flags);
            break;
        case '2':
            system("cls");
            cout << "You selected: [2] Miles per Gallon" << endl
                 << endl;
            MperG();
            break;
        case '3':
            cout << "Program has exited." << endl;
            exit(0);
        default:
            system("cls");
            continue;
        }

        while (true)
        {
            tryAgainResponse = tryAgain(tar);

            if (tryAgainResponse == 'N' || tryAgainResponse == 'n')
            {
                cout << "Program has exited." << endl
                     << endl;
                exit(0);
            }
            else if (tryAgainResponse == 'Y' || tryAgainResponse == 'y')
            {
                system("cls");
            }
            else
            {
                continue;
            }
            break;
        }

    } while (true);
}

///////////////////////////
char getChoice(char *ch)
{
    cout << "----------| Menu |----------" << endl
         << "[1] Grade Average and Elimination" << endl
         << "[2] Miles per Gallon" << endl
         << "[3] Quit Program" << endl
         << "----------------------------" << endl
         << endl
         << "Enter your choice: ";

    cin >> *ch;
    return *ch;
}

//////////////////////////////
void getInput(double *input)
{
    cout << "Enter " << asize << " grades: " << endl;
    for (int k = 0; k < asize; k++)
    {
        cout << "grade[" << k << "]: ";
        cin >> *(input + k);
    }
}

/////////////////////////////
double getSum(double *sum)
{
    double add = 0;

    cout << "You entered:" << endl
         << endl;
    for (i = 0; i < asize; i++)
    {
        cout << "grade[" << i + 1 << "]: ";
        cout << *(sum + i) << endl;
    }

    for (int j = 0; j < asize; j++)
        add += *(sum + j);

    return add;
}

////////////////////////////////
double getLow(double *low)
{
    double *xlow, baba;

    baba = *(low + 0);
    xlow = &baba;

    for (i = 0; i < asize; i++)
    {
        if (*(low + i) < *xlow)
            *xlow = *(low + i);
    }

    return *xlow;
}

////////////////////////////////
double getAverage(double *avg)
{
    double ave;
    double add = 0;
    double lowest = getLow(avg);

    for (i = 0; i < asize; i++)
        add += *(avg + i);

    ave = (add - lowest) / (asize - 1);

    return ave;
}

/////////////////////////

// prompts the user to specify the size of the array for miles and gallons
// verify and validate the input for miles and gallons using exception handling
void MperG()
{
    int ctr;
    pointers milPtr, galPtr;
    int msize;

    while (true)
    {
        try
        {
            cout << "Specify the size of the array: ";
            cin >> msize;

            if (msize < 5 || msize > 15)
                throw msize;

            break;
        }
        catch (int msizeerr)
        {
            cerr << endl
                 << "Array of size " << msizeerr << " is not allowed." << endl
                 << "Array size should be between 5-15 only." << endl;
        }
    }

    cout << fixed << setprecision(2) << endl;
    cout << "MILES\n";

    milPtr = new double[msize];
    for (ctr = 0; ctr < msize; ctr++)
    {
        while (true)
        {
            try
            {
                cout << "Miles[" << ctr << "]: ";
                cin >> *(milPtr + ctr);
                if (*(milPtr + ctr) < 100 || *(milPtr + ctr) > 250)
                    throw *(milPtr + ctr);

                break;
            }
            catch (double e)
            {
                cout << e << " is invalid, please enter a value between 100-250." << endl;
                continue;
            }
        }
    }

    /*********************************************************/
    system("cls");

    galPtr = new double[msize];
    cout << "GALLONS\n";

    for (ctr = 0; ctr < msize; ctr++)
    {
        while (true)
        {
            try
            {
                cout << "Gallons[" << ctr << "]: ";
                cin >> *(galPtr + ctr);
                if (*(galPtr + ctr) < 5 || *(galPtr + ctr) > 25)
                    throw *(galPtr + ctr);

                break;
            }
            catch (double e)
            {
                cout << e << " is invalid, please enter a value between 5-25." << endl;
                continue;
            }
        }
    }

    MilesPerrGallon(milPtr, galPtr, msize);
}

////////////////////////

// final output of the computer miles and gallons
void MilesPerrGallon(double *ptr1, double *ptr2, int sz)
{
    double mpg[sz];
    pointers mpgPtr;
    int index;

    mpgPtr = mpg;

    cout << fixed << setw(7) << setprecision(2) << showpoint
         << "miles"
         << "   /  "
         << "gallon"
         << "   =   "
         << "MPG"
         << endl;
    for (index = 0; index < sz; index++)
    {
        cout << *(ptr1 + index) << "    /   " << *(ptr2 + index)
             << "   =  " << ((*(ptr1 + index)) / (*(ptr2 + index))) << endl;
    }

    cout.precision(old_prec);
    cout.flags(old_flags);

    delete[] ptr1;
    delete[] ptr2;
}

////////////////////////
char tryAgain(char *resp)
{
    cout << "Do you want to try again? <y/n> ";
    cin >> *resp;

    return *resp;
}
