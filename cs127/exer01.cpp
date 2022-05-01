#include <iostream>
#include <iomanip>
using namespace std;

// global (required, don't modify)
int i;
int row, col;
const int sizeRow = 4;
const int sizeCol = 5;

// function (required, don't modify)
int getMenu(int ans);                      // returns the correct choice otherwise returns -1 if not. (prof said this line can only be modified)
void getInput(int list[], int dim);        // input for both option 1 and 2
void getBubble(int list[], int dim);       // perform the bubble sorting
void getSelect(int list[], int dim);       // perform the selection sorting
void convert2DimSort(int list[], int dim); // convert one dimensional to 2-dimensional for both option 1 and 2
void get2DOut(int list1[][sizeCol]);       // displaying the values in ascending and descending order 2-D
void getHeap(int list3[], int dimen);      // process heapyfication or heap sort 1-D

// additional global declarations
const int arraySize = sizeRow * sizeCol;
const int arraySizeHeap = 10;
int array_sort[sizeRow * sizeCol];
int array_sort_2dim[sizeRow][sizeCol];
int array_sort_heap[arraySizeHeap];

// additional funcs
char tryAgain(char resp);
void swap(int *xp, int *yp);
void heapify(int list[], int n, int i);

int main()
{
    int sagot, choice;
    char again, rep_bool;

    do
    {
        sagot = getMenu(choice);

        switch (sagot)
        {
        case 1: // bubble sort
            system("cls");
            cout << "Processing bubble sorting technique... " << endl
                 << endl;
            getInput(array_sort, arraySize);
            getBubble(array_sort, arraySize);

            convert2DimSort(array_sort, arraySize);
            get2DOut(array_sort_2dim);

            break;
        case 2: // selection sort
            system("cls");
            cout << "Processing selection sorting technique... " << endl
                 << endl;
            getInput(array_sort, arraySize);
            getSelect(array_sort, arraySize);

            convert2DimSort(array_sort, arraySize);
            get2DOut(array_sort_2dim);
            break;
        case 3: // heap sort
            system("cls");
            cout << "Processing heap sorting technique... " << endl
                 << endl;
            getInput(array_sort_heap, arraySizeHeap);

            cout << endl
                 << "Heapyfied values ..." << endl;
            getHeap(array_sort_heap, arraySizeHeap);
            break;
        case 4:
            cout << "Program has exited.\n";
            exit(1);
        }

        while (true)
        {
            rep_bool = tryAgain(again);

            if (rep_bool == 'N' || rep_bool == 'n')
            {
                cout << "Program has exited." << endl
                     << endl;
                exit(0);
            }
            else if (rep_bool == 'Y' || rep_bool == 'y')
            {
                memset(array_sort, 0, sizeof(array_sort));
                memset(array_sort_2dim, 0, sizeof(array_sort_2dim));
                memset(array_sort_heap, 0, sizeof(array_sort_heap));
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

/////////////////////////////////
int getMenu(int ans)
{
    cout << "--| Sorting Algorithms |--" << endl
         << "[1] Bubble Sort" << endl
         << "[2] Selection Sort" << endl
         << "[3] Heap Sort" << endl
         << "[4] Quit Program" << endl
         << "--------------------------" << endl
         << endl
         << "Enter your choice: ";

    cin >> ans;

    if (ans == 1 || ans == 2 || ans == 3 || ans == 4)
        return ans;
    else
        return -1;
}
////////////////////////////////////
void getInput(int list[], int dim) // for both option 1 and 2 only (may be used in option 3, need different vars)
{
    cout << "Enter " << dim << " numbers: " << endl;
    for (int k = 0; k < dim; k++)
    {
        cout << "num[" << k + 1 << "]: ";
        cin >> list[k];
    }
}

//////////////////////////////////////
void convert2DimSort(int list[], int dim) // convert one dimensional to 2-dimensional for both option 1 and 2
{
    memcpy(array_sort_2dim, list, dim * sizeof(int));
}

////////////////////////////////////////////////
void get2DOut(int list1[][sizeCol]) // displaying the values in ascending and descending order 2-D
{
    int reversed_2d_arr[sizeRow][sizeCol];
    memcpy(reversed_2d_arr, list1, arraySize * sizeof(int));

    cout << endl
         << "Ascending Order" << endl;

    for (int i = 0; i < sizeRow; i++)
    {
        for (int j = 0; j < sizeCol; j++)
        {
            cout << setw(6) << list1[i][j];
        }
        cout << endl;
    }
    
    cout << endl
         << "Descending Order" << endl;

    for (int k = sizeRow - 1; k >= 0; k--)
    {
        for (int l = sizeCol - 1; l >= 0; l--)
        {
            cout << setw(6) << reversed_2d_arr[k][l];
        }
        cout << endl;
    }
}

/////////////////////////////////////////////
void swap(int *xp, int *yp) // for bubble/sel sort
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

////////////////////////////////////////////
void getBubble(int list[], int dim) // perform the bubble sorting
{
    for (int i = 0; i < dim - 1; i++)
    {
        for (int j = 0; j < dim - i - 1; j++)
        {
            if (list[j] > list[j + 1])
                swap(&list[j], &list[j + 1]);
        }
    }
}

///////////////////////////////////////////////
void getSelect(int list[], int dim) // perform the selection sorting
{
    for (int step = 0; step < dim - 1; step++)
    {
        int minimum = step;
        for (int i = step + 1; i < dim; i++)
        {
            if (list[i] < list[minimum])
                minimum = i;
        }
        swap(&list[minimum], &list[step]);
    }
}
//////////////////////////////////////////////
void getHeap(int list3[], int dimen) // process heapyfication or heap sort 1-D
{
    for (int i = dimen / 2 - 1; i >= 0; i--)
        heapify(list3, dimen, i);

    for (int i = dimen - 1; i >= 0; i--)
    {
        swap(list3[0], list3[i]);
        heapify(list3, i, 0);
    }

    for (int m = 0; m < dimen; m++)
    {
        cout << "Arr[" << m + 1 << "]: " << list3[m] << endl;
    }
}
///////////////////////////////////////////////
char tryAgain(char resp) 
{
    cout << "Do you want to try again? <y/n> ";
    cin >> resp;

    return resp;
}
///////////////////////////////////////////////
void heapify(int list[], int n, int i) // for heap sorting technique
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    // if left child is larger than root
    if (l < n && list[l] > list[largest])
        largest = l;

    // if right child is larger than largest so far
    if (r < n && list[r] > list[largest])
        largest = r;

    // if largest is not root
    if (largest != i)
    {
        swap(list[i], list[largest]);

        // recursively heapify the affected sub-tree
        heapify(list, n, largest);
    }
}