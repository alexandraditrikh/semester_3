#include <fstream>
#include <iostream>

using namespace std;

#define MAX_SIZE 1000

int read_from_file(ifstream& in, int arr[][2], int& size) {
    if (!(in >> size))
        return 1;
    if (size > MAX_SIZE)
        return 1;

    for (int i = 0; i < size; i++) {
        if (!(in >> arr[i][0] >> arr[i][1]))
            return 1;
    }
    return 0;
}

void bubble_sort(int arr[][2], int size) {
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j][1] > arr[j + 1][1]) {
                swap(arr[j][0], arr[j + 1][0]);
                swap(arr[j][1], arr[j + 1][1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

void task(int events[][2], int size, int& max_number_events, int& max_break) {
    if (size == 0) {
        max_number_events = 0;
        max_break = 0;
        return;
    }

    bubble_sort(events, size);

    int greedy_max_events = 0;
    int last_end_time = -1;

    greedy_max_events = 1;
    last_end_time = events[0][1];
    for (int i = 1; i < size; i++) {
        if (events[i][0] >= last_end_time + 10) {
            greedy_max_events++;
            last_end_time = events[i][1];
        }
    }

    max_number_events = greedy_max_events;

    if (greedy_max_events == 2) {  //TODO: Переделать часть - подбирать последнее мероприятие
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (events[j][0] >= events[i][1] + 10) {
                    int current_break = events[j][0] - events[i][1];
                    if (current_break > max_break) {
                        max_break = current_break;
                    }
                }
            }
        }
    }

    else if (greedy_max_events > 2) {
        last_end_time = events[0][1];
        int selected_count = 1;

        for (int i = 1; i < size && selected_count < greedy_max_events; i++) {
            if (events[i][0] >= last_end_time + 10) {
                int current_break = events[i][0] - last_end_time;
                if (current_break > max_break) {
                    max_break = current_break;
                }
                last_end_time = events[i][1];
                selected_count++;
            }
        }
    }
    return;
}

int main() {
    ifstream in("../input/in7.txt");
    if (!in.is_open()) {
        cerr << "Cannot open input file\n";
        return 1;
    }

    int events[MAX_SIZE][2];
    int size;

    if (read_from_file(in, events, size)) {
        cerr << "Task failed due to invalid input\n";
        in.close();
        return 1;
    }

    int max_number_events = 0, max_break = 0;
    task(events, size, max_number_events, max_break);

    cout << max_number_events << " " << max_break << endl;

    in.close();
    return 0;
}