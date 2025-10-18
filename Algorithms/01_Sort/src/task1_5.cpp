#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

#define MAX_SIZE 10000

int read_from_file(ifstream& in, int* arr, int& size) {
    size = 0;
    int elem;
    while (in >> elem && size < MAX_SIZE)
        arr[size++] = elem;
    return in.fail() && !in.eof();
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

int task(ifstream& in, ofstream& out) {
    int arr[MAX_SIZE];
    int n;
    if (read_from_file(in, arr, n))
        return -1;
    if (n == 0)
        return 0;

    bubble_sort(arr, n);

    int freq = ceil(n / 5.0);
    for (int i = 0; i < n;) {
        int count = 1;

        int j = i + 1;
        for (j; j < n && arr[j] == arr[i]; j++) {
            count++;
        }

        if (count > freq) {
            for (int k = 0; k < count; k++) {
                out << arr[i] << " ";
            }
        }

        i = j;
    }

    return 0;
}

int main() {
    ifstream in("../input/in5.txt");
    if (!in.is_open()) {
        cerr << "Cannot open input file\n";
        return 1;
    }

    ofstream out("../output/out5.txt");
    if (!out.is_open()) {
        cerr << "Cannot open output file\n";
        in.close();
        return 1;
    }

    if (task(in, out)) {
        cerr << "Task failed due to invalid input\n";
        in.close();
        out.close();
        return 1;
    }

    in.close();
    out.close();
    return 0;
}