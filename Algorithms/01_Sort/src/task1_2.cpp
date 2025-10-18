#include <cctype>
#include <cstdlib> 
#include <fstream>
#include <iostream>

using namespace std;
#define MAX_NUMBER 1000
#define MAX_EL_SIZE 100
#define MAX_SIZE 1000

bool is_greater(const char* a, const char* b) {
    char ab[MAX_EL_SIZE * 2] = {0};
    char ba[MAX_EL_SIZE * 2] = {0};

    int i = 0, j = 0;

    while (a[i] != '\0') {
        ab[j++] = a[i++];
    }
    i = 0;
    while (b[i] != '\0') {
        ab[j++] = b[i++];
    }
    ab[j] = '\0';

    i = 0;
    j = 0;
    while (b[i] != '\0') {
        ba[j++] = b[i++];
    }
    i = 0;
    while (a[i] != '\0') {
        ba[j++] = a[i++];
    }
    ba[j] = '\0';

    i = 0;
    while (ab[i] != '\0' && ba[i] != '\0') {
        if (ab[i] > ba[i])
            return true;
        if (ab[i] < ba[i])
            return false;
        i++;
    }
    return false;
}

void bubble_sort(char arr[][MAX_EL_SIZE], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (!is_greater(arr[j], arr[j + 1])) {
                char temp[MAX_EL_SIZE];
                // Копируем arr[j] в temp
                int k = 0;
                while (arr[j][k] != '\0') {
                    temp[k] = arr[j][k];
                    k++;
                }
                temp[k] = '\0';

                k = 0;
                while (arr[j + 1][k] != '\0') {
                    arr[j][k] = arr[j + 1][k];
                    k++;
                }
                arr[j][k] = '\0';

                k = 0;
                while (temp[k] != '\0') {
                    arr[j + 1][k] = temp[k];
                    k++;
                }
                arr[j + 1][k] = '\0';
            }
        }
    }
}

int read_from_file(ifstream& in, char arr[][MAX_EL_SIZE], int& size) {
    size = 0;
    char c;

    while (in.get(c)) {
        if (isspace(c))
            continue;

        if (!isdigit(c)) {
            return 1;
        }

        int count_num = 0;
        arr[size][count_num++] = c;

        while (in.get(c) && !isspace(c) && c != '\n' && c != '\r') {
            if (!isdigit(c)) {
                return 1;
            }
            if (count_num >= MAX_EL_SIZE - 1) {
                return 1;
            }
            arr[size][count_num++] = c;
        }
        arr[size][count_num] = '\0';

        if (count_num > 4) {
            return 1;
        }
        if (count_num == 4) {
            char num[5];
            for (int i = 0; i < 4; i++)
                num[i] = arr[size][i];
            num[4] = '\0';
            if (atoi(num) > 1000 || atoi(num) < 0) {
                return 1;
            }
        }

        size++;
        if (size >= MAX_SIZE)
            break;

        if (!in || in.eof())
            break;
    }

    return 0;
}

int task(ifstream& in, ofstream& out) {
    char arr[MAX_SIZE][MAX_EL_SIZE];
    int size;

    if (read_from_file(in, arr, size)) {
        return 1;
    }

    bubble_sort(arr, size);

    for (int i = 0; i < size; i++) {
        out << arr[i];
    }

    return 0;
}

int main() {
    ifstream in("../input/in2.txt");
    if (!in.is_open()) {
        cerr << "Cannot open input file" << endl;
        return 1;
    }

    ofstream out("../output/out2.txt");
    if (!out.is_open()) {
        cerr << "Cannot open output file" << endl;
        in.close();
        return 1;
    }

    if (task(in, out)) {
        cerr << "Invalid input data" << endl;
        in.close();
        out.close();
        return 1;
    }

    in.close();
    out.close();
    return 0;
}