#include <iostream>
#include <iomanip>

using namespace std;

// ---------- start prototype ----------

char getMenu(char *ans);                      		  // selection menu
void getBinDisplay(int *ptr, int *xsize);     		  // display array for binary searching
int getLoc(int *ptr, int size, int *xtarget); 		  // binary search proc
int binarySearch(int *arr, int x, int low, int high); // binary search main bits

int getSize(int *asize);                // desired size for array in grade elim
void getInput(double *ptr, int xsize);  // populate array of grades
double getElim(double *ptr, int xsize); // elim value

char getTry(char *resp); // try again prompt

// ---------- end prototype ------------

typedef double *DoublePointer;
typedef int *IntPointer;
typedef char *CharPointer;

std::ios_base::fmtflags old_flags = cout.flags();
std::streamsize old_prec = cout.precision();

int main(int argc, char *argv[])
{
    CharPointer chr, tar_a;
    char ch = 0;
    int opt;
    char tar = 0;
    tar_a = &tar;

    int array_size = 12;
    IntPointer asize, bin_arr;
    asize = &array_size;
    int binNum[array_size] = {4, 7, 8, 10, 14, 21, 22, 36, 62, 77, 81, 91};
    bin_arr = binNum;

    while (true)
    {
        chr = &ch;
        opt = getMenu(chr);

        try
        {
            switch (*chr)
            {
            case '1':
                system("cls");

                cout << "Option 1: Binary Searching" << endl;
                getBinDisplay(bin_arr, asize);
                getLoc(bin_arr, array_size, asize);

                break;
            case '2':
                int grade_arr_size;
                IntPointer gsize;
                DoublePointer grades_array;
                gsize = &grade_arr_size;

                system("cls");

                cout << "Option 2: Grade Elimination" << endl;

                grade_arr_size = getSize(gsize);
                grades_array = new double[grade_arr_size];
                cout << endl;
                getInput(grades_array, grade_arr_size);
                getElim(grades_array, grade_arr_size);

                delete[] grades_array;
                break;
            case '3':
                cout << "Program has exited." << endl;
                exit(0);
            default:
                throw *chr;
            }
        }
        catch (char wrong_answer)
        {
            cout << wrong_answer << " is an invalid choice, please try again." << endl
                 << endl;
            system("pause");
            cout << endl;
            continue;
        }

        while (true)
        {
            tar = getTry(tar_a);

            try
            {
                if (tar == 'N' || tar == 'n')
                {
                    cout << "Program has exited." << endl
                         << endl;
                    exit(0);
                }
                else if (tar == 'Y' || tar == 'y')
                {
                    system("cls");
                }
                else
                {
                    throw tar;
                }
            }
            catch (char error)
            {
                cout << "Invalid input, type [y]es or [n]o" << endl;
                continue;
            }
            break;
        }
    }
}

char getMenu(char *ans)
{
    cout << "----------| Menu |----------" << endl
         << "[1] Binary Searching" << endl
         << "[2] Grade Elimination" << endl
         << "[3] Quit Program" << endl
         << "----------------------------" << endl
         << endl
         << "Enter your choice: ";

    cin >> *ans;
    return *ans;
}

char getTry(char *resp)
{
    cout << "Do you want to try again? <y/n> ";
    cin >> *resp;

    return *resp;
}

void getInput(double *ptr, int xsize)
{
    cout << "Enter " << xsize << " grades: " << endl;
    for (int k = 0; k < xsize; k++)
    {
        cout << "grade[" << k + 1 << "]: ";
        cin >> *(ptr + k);
    }
}

int getSize(int *asize)
{
    while (true)
    {
        try
        {
            cout << "Specify the number of grades to be entered (5-10 only): ";
            cin >> *asize;

            if (*asize < 5 || *asize > 10)
                throw *asize;

            break;
        }
        catch (int asizeerr)
        {
            cout << endl
                 << "Grades of size " << asizeerr << " are not allowed." << endl
                 << "The number of grades entered should be between 5-10 only." << endl
                 << endl;
        }
    }

    return *asize;
}

double getElim(double *ptr, int xsize)
{
    double add = 0;
    double low_a;
    DoublePointer xlow;
    double lowest;
    double ave;
    int i;

    for (int j = 0; j < xsize; j++)
        add += *(ptr + j);

    low_a = *(ptr + 0);
    xlow = &low_a;

    for (i = 0; i < xsize; i++)
    {
        if (*(ptr + i) < *xlow)
            *xlow = *(ptr + i);
    }
    lowest = *xlow;

    ave = (add - lowest) / (xsize - 1);
    cout << fixed << setprecision(2) << endl
         << "Results:" << endl
         << lowest << " is eliminated" << endl
         << "average is " << ave << endl;

    cout.precision(old_prec);
    cout.flags(old_flags);

    return ave;
}

void getBinDisplay(int *ptr, int *xsize)
{
    int temp;
    temp = *xsize;

    cout << "Displaying elements in the array" << endl;
    for (int i = 0; i < temp; i++)
        cout << setw(5) << *(ptr + i);
    cout << endl
         << endl;
}

int binarySearch(int *arr, int x, int low, int high)
{
    // Repeat until the pointers low and high meet each other
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] < x)
            low = mid + 1;

        else
            high = mid - 1;
    }

    return -1;
}

int getLoc(int *ptr, int size, int *xtarget)
{
    int temp;
    int result;
    int n = size;

    while (true)
    {
        cout << "Enter your target key: ";
        cin >> temp;

        result = binarySearch(ptr, temp, 0, n - 1);

        try
        {
            if (result == -1)
            {
                throw temp;
            }
            else
            {
                cout << "Element " << temp << " is found at index [" << result << "]" << endl
                     << endl;
                break;
            }
        }
        catch (int elem_not_in_array)
        {
            cout << "Element " << elem_not_in_array << " is not in the list." << endl
                 << endl;
            continue;
        }
    }
    return temp;
}