#include "lists.h"
#include <iostream>
#include <vector>

void print(const std::vector<int>& a) { for (int x : a) std::cout << x << ' '; std::cout << '\n'; }
int main() {
    SingleList s;
    for (int x : {4, 2, 8}) addEnd(s, x);
    std::cout << "Однонаправленный список: "; print(values(s));
    std::cout << "Максимум: " << maximum(s) << '\n';
    std::cout << "Отсортирован: " << (isSorted(s) ? "да" : "нет") << '\n';
    removeValue(s, 2);
    std::cout << "После удаления 2: "; print(values(s));
    clear(s);

    DoubleList d;
    addBeginning(d, 5); addBeginning(d, 1); addEnd(d, 12);
    std::cout << "Двунаправленный список: "; print(values(d));
    clear(d);
    for (int x : {5, 1, 7, 3}) insertSorted(d, x);
    std::cout << "Сортированный список: "; print(values(d));
    removeValue(d, 3);
    std::cout << "После удаления 3: "; print(values(d));
    clear(d);

    SingleList cycle;
    for (int x : {1, 2, 3, 4}) addEnd(cycle, x);
    cycle.bottom->next = cycle.top->next;
    std::cout << "Цикл найден: " << (cycleStart(cycle.top) ? "да" : "нет") << '\n';
    std::cout << "Цикл устранён: " << (breakCycle(cycle.top) ? "да" : "нет") << '\n';
    clear(cycle);

    SortedNames namesList;
    for (const auto& name : {"Ольга", "Анна", "Мария"}) namesList.insert(name);
    std::cout << "Имена по порядку: ";
    for (const auto& name : namesList.names()) std::cout << name << ' ';
    std::cout << "\nПоиск с конца (Мария): "
              << (namesList.findFromBottom("Мария") ? "найдено" : "нет") << '\n';

    PlanetList planets;
    planets.addPlanet("Меркурий", 57.9, 0.330, 4879);
    planets.addPlanet("Земля", 149.6, 5.972, 12742);
    planets.addPlanet("Марс", 227.9, 0.642, 6779);
    planets.addPlanet("Юпитер", 778.6, 1898, 139820);
    while (true) {
        std::cout << "\nСортировка планет: 1 - расстояние, 2 - масса, 3 - диаметр, 0 - выход: ";
        int choice;
        if (!(std::cin >> choice) || choice == 0) break;
        if (choice < 1 || choice > 3) { std::cout << "Неверный выбор\n"; continue; }
        for (const auto& name : planets.names(choice)) std::cout << name << ' ';
        std::cout << '\n';
    }
}
