#include <iostream>
#include <vector>
#include <limits> // Для std::numeric_limits

void sort_by_bubble(std::vector<int> &arr);

int main() {
    std::vector<int> arr = {1, 8, 2, 5, 3, 11};

    // Вывод исходного массива (используем range-based for)
    std::cout << "Массив до сортировки:";
    for (const auto &num : arr) {
        std::cout << ' ' << num;
    }
    std::cout << std::endl;

    // Сортировка
    sort_by_bubble(arr);

    // Вывод отсортированного массива
    std::cout << "Массив после сортировки:";
    for (const auto &num : arr) {
        std::cout << ' ' << num;
    }
    std::cout << std::endl;

    // Кросс-платформенная пауза
    std::cout << "Нажмите Enter для выхода...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return 0;
}

void sort_by_bubble(std::vector<int> &arr) {
    bool swapped;
    for (size_t i = 0; i < arr.size() - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]); // Используем стандартный swap
                swapped = true;
            }
        }
        // Если не было обменов, массив уже отсортирован
        if (!swapped) break;
    }
}
