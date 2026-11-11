#include <iostream>
#include <limits>

#include "lists.h"

int main() {
    SingleList s;
    DoubleList d;
    PlanetList planets;
    append(s, 4);
    append(s, 2);
    append(s, 8);
    pushFront(d, 5);
    pushBack(d, 9);
    pushFrontViaInsert(d, 1);
    pushBackViaInsert(d, 12);
    erase(d, 9);
    std::cout << "Однонаправленный список: ";
    for (int x : values(s)) std::cout << x << ' ';
    std::cout << "\nМаксимум: " << maximum(s) << "\nОтсортирован: " << (sorted(s) ? "да" : "нет")
              << '\n';
    erase(s, 2);
    std::cout << "После удаления 2: ";
    for (int x : values(s)) std::cout << x << ' ';
    std::cout << "\nДвунаправленный список: ";
    for (int x : values(d)) std::cout << x << ' ';
    std::cout << "\n";
    DoubleList ordered;
    for (int x : {7, 1, 5, 3}) insertSorted(ordered, x);
    std::cout << "Сортированный список: ";
    for (int x : values(ordered)) std::cout << x << ' ';
    std::cout << "\n";
    // Отдельный список для демонстрации цикла.
    SingleList loop;
    append(loop, 10);
    append(loop, 20);
    append(loop, 30);
    loop.bottom->next = loop.top->next;
    std::cout << "Цикл найден: " << (cycleStart(loop.top) ? "да" : "нет") << '\n';
    breakCycle(loop.top);
    std::cout << "Цикл устранён: " << (!cycleStart(loop.top) ? "да" : "нет") << '\n';
    addPlanet(planets, "Земля", 149.6, 5.97, 12742);
    addPlanet(planets, "Марс", 227.9, 0.642, 6779);
    addPlanet(planets, "Юпитер", 778.6, 1898, 139820);
    addPlanet(planets, "Меркурий", 57.9, 0.330, 4879);
    int choice = 0;
    while (true) {
        std::cout << "\nСортировка планет: 1 - расстояние, 2 - масса, 3 - диаметр, 0 - выход: ";
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) break;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Введите число.\n";
            continue;
        }
        if (choice == 0) break;
        if (choice < 1 || choice > 3) {
            std::cout << "Неверный пункт.\n";
            continue;
        }
        for (const auto& name : planetNames(planets, choice)) std::cout << name << ' ';
        std::cout << '\n';
    }
    clear(s);
    clear(d);
    clear(ordered);
    clear(loop);
    clear(planets);
}
