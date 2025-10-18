#include <cctype>
#include <fstream>
#include <iostream>

#define MAX_SIZE 10000

using namespace std;

int read_arr_from_file(ifstream& in, int* arr, int& size) {
    size = 0;
    int num;
    while (in >> num && size < MAX_SIZE) {
        arr[size++] = num;
    }
    if (!in.eof()) {
        return 1;
    }
    return 0;
}

void bubble_sort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

int task(ifstream& in) {
    int size = 0;
    int arr[MAX_SIZE];

    if (read_arr_from_file(in, arr, size)) {
        return -1;
    }

    if (size == 0) {
        return 0;
    }

    bubble_sort(arr, size);

    
    for (int i = 0; i < size;) {
        int count = 1;
        int j = i + 1;
        for (; j < size && arr[j] == arr[i]; j++) {
            count++;
        }

        i = j;

        if (count < 2)
            return 1;
    }

    return 0;
}

int main() {
    ifstream in("../input/in3.txt");
    if (!in.is_open()) {
        cerr << "Cannot open input file" << endl;
        return 1;
    }

    int res = task(in);
    if (res == -1)
        cerr << "Invalid data\n";
    else if (res)
        cout << "No\n";
    else
        cout << "Yes\n";

    in.close();
    return res;
}