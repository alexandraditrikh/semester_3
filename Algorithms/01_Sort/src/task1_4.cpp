#include <cmath>
#include <fstream>
#include <iostream>

#define MAX_SIZE 10000
using namespace std;

int read_from_file(ifstream& in, int* nums, int& size, int& valDiff, int& indDiff) {
    if (!(in >> valDiff >> indDiff)) {
        cerr << "Error reading valDiff and indDiff" << endl;
        return 1;
    }

    size = 0;
    int num;

    while (in >> num && size < MAX_SIZE) {
        nums[size++] = num;
    }

    if (in.fail() && !in.eof()) {
        cerr << "Invalid data in file" << endl;
        return 1;
    }

    return 0;
}

void output_to_file(ofstream& out, int** all_pairs, int total_pairs) {
    if (total_pairs == 0) {
        out << "No pairs found" << endl;
        return;
    }
    for (int i = 0; i < total_pairs; i++) {
        out << "(" << all_pairs[i][0] << ", " << all_pairs[i][1] << ") ";
    }
}

int task(ifstream& in, ofstream& out) {
    int size;
    int nums[MAX_SIZE];
    int valDiff, indDiff;

    if (read_from_file(in, nums, size, valDiff, indDiff)) {
        return -1;
    }

    if (size == 0) {
        out << "File is empty" << endl;
        return 0;
    }

    int** all_pairs = new int*[MAX_SIZE * MAX_SIZE];
    for (int i = 0; i < MAX_SIZE * MAX_SIZE; ++i) {
        all_pairs[i] = new int[2];
    }
    int total_pairs = 0;

    for (int i = 0; i < size; i++) {
        int start = max(0, i - indDiff);
        int end = min(size - 1, i + indDiff);

        for (int j = start; j <= end; j++) {
            if (i == j)
                continue;
            if (abs(nums[i] - nums[j]) <= valDiff) {
                all_pairs[total_pairs][0] = i;
                all_pairs[total_pairs][1] = j;
                total_pairs++;
            }
        }
    }

    output_to_file(out, all_pairs, total_pairs);

    for (int i = 0; i < MAX_SIZE * MAX_SIZE; ++i) {
        delete[] all_pairs[i];
    }
    delete[] all_pairs;

    return 0;
}

int main() {
    ifstream in("../input/in4.txt");
    if (!in.is_open()) {
        cerr << "Cannot open input file\n";
        return 1;
    }

    ofstream out("../output/out4.txt");
    if (!out.is_open()) {
        cerr << "Cannot open output file\n";
        in.close();
        return 1;
    }

    if (task(in, out)) {
        cerr << "Task failed due to invalid input.\n";
        in.close();
        out.close();
        return 1;
    }

    in.close();
    out.close();
    return 0;
}