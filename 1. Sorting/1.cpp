#include <iostream>

double theFunction(double x, double A, double B, double C) {
    return (A * pow(x, 2)) + B * x + C;
}

void insertionSort(double arr[], int n)
{
    int i, j;
    double key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


int main()
{

    std::cout << "ilosc argumentow: ";
    int arr_size; std::cin >> arr_size;

    double* args = new double[arr_size];
    for (int i = 0; i < arr_size; i++)
    {
        std::cout << "arg[" << i << "] = ";
        std::cin >> args[i];
    }

    std::cout << "A B C: ";
    double A, B, C;
    std::cin >> A >> B >> C;


    //double A = 1.0, B = 3.0, C = 5.0;
    //double args[] = { 2.0, 2.0, 5.0 };
    //int arr_size = sizeof(args) / sizeof(double);


    double* results = new double[arr_size];
    for (int i = 0; i < arr_size; i++)
        results[i] = theFunction(args[i], A, B, C);

    insertionSort(results, arr_size);

    std::cout << "\nPosortowane wyniki: ";
    for (int i = 0; i < arr_size; i++)
        std::cout << "\ny = " << results[i];
}