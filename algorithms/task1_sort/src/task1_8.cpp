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
    int nums[MAX_SIZE];
    int size;
    if (read_from_file(in, nums, size))
        return -1;
    if (size == 0) {
        return 0;
    }

    bubble_sort(nums, size);

    for (int i = 0; i < size - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int left = i + 1;
        int right = size - 1;

        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];

            if (sum == 0) {
                out << nums[i] << " " << nums[left] << " " << nums[right] << endl;

                while (left < right && nums[left] == nums[left + 1])
                    left++;
                while (left < right && nums[right] == nums[right - 1])
                    right--;

                left++;
                right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }

    return 0;
}

int main() {
    ifstream in("../input/in8.txt");
    if (!in.is_open()) {
        cerr << "Cannot open input file\n";
        return 1;
    }

    ofstream out("../output/out8.txt");
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