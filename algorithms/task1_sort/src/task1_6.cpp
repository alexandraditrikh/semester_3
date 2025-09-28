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
            if (arr[j] < arr[j + 1]) {
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
    int citations[MAX_SIZE];
    int size;

    if (read_from_file(in, citations, size))
        return -1;
    if (size == 0)
        return 0;

    bubble_sort(citations, size);

    int h_index = 0;
    for (int i = 0; i < size; i++) {
        if (citations[i] >= i + 1) {
            h_index = i + 1;
        } else {
            break;
        }
    }

    return h_index;
}

int main() {
    ifstream in("../input/in6.txt");
    if (!in.is_open()) {
        cerr << "Cannot open input file\n";
        return 1;
    }

    int result = task(in);
    if (result == -1) {
        cerr << "Task failed due to invalid input\n";
        in.close();
        return 1;
    }

    cout << result << endl;

    in.close();
    return 0;
}