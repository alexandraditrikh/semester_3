#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    std::cin >> n;
    std::vector<int> mushrooms(n); // Создаем вектор размера n

    // Чтение данных
    for (int i = 0; i < n; ++i) {
        std::cin >> mushrooms[i];
    }

    int max_vas = weights.front(), min_mash = weights.front();
    for (int i = 0; i < n; i++){
        if ((i + 1) % 2 == 0 && min_mash > weights[i]) min_mash = weights[i];
        else if ((i + 1) % 2 == 1 && max_vas < weights[i]) max_vas = weights[i];
    }

    if (max_vas != min_mash){
        sw
    }
    return 0;
}