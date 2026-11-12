#pragma once
#include <string>
#include <vector>

struct Cell { int value; Cell* next = nullptr; };
struct SingleList { Cell* top = nullptr; Cell* bottom = nullptr; };
void addEnd(SingleList& list, int value);
void addBeginning(SingleList& list, int value);
bool removeValue(SingleList& list, int value);
Cell* findCell(const SingleList& list, int value);
Cell* findBefore(const SingleList& list, int value);
int maximum(const SingleList& list);
bool isSorted(const SingleList& list);
std::vector<int> values(const SingleList& list);
void clear(SingleList& list);
Cell* cycleStart(Cell* top);
bool breakCycle(Cell* top);

struct DCell { int value; DCell* next = nullptr; DCell* prev = nullptr; };
struct DoubleList { DCell* top = nullptr; DCell* bottom = nullptr; };
void insertCell(DoubleList& list, DCell* before, DCell* cell);
void addBeginning(DoubleList& list, int value);
void addEnd(DoubleList& list, int value);
bool removeValue(DoubleList& list, int value);
void insertSorted(DoubleList& list, int value);
std::vector<int> values(const DoubleList& list);
void clear(DoubleList& list);

struct Planet {
    std::string name;
    double distance, mass, diameter;
    Planet* nextDistance = nullptr;
    Planet* nextMass = nullptr;
    Planet* nextDiameter = nullptr;
};
class PlanetList {
    std::vector<Planet*> owned;
    Planet* byDistance = nullptr;
    Planet* byMass = nullptr;
    Planet* byDiameter = nullptr;
public:
    PlanetList() = default;
    PlanetList(const PlanetList&) = delete;
    PlanetList& operator=(const PlanetList&) = delete;
    ~PlanetList();
    void addPlanet(const std::string& name, double distance, double mass, double diameter);
    std::vector<std::string> names(int order) const;
};

// Задания 7 и 8: сортированный двунаправленный список имён с ограничителями.
struct NameCell {
    std::string name;
    NameCell* next = nullptr;
    NameCell* prev = nullptr;
};
class SortedNames {
    NameCell topSentinel{""};      // меньше любого имени
    NameCell bottomSentinel{""};   // больше любого имени
public:
    SortedNames();
    SortedNames(const SortedNames&) = delete;
    SortedNames& operator=(const SortedNames&) = delete;
    ~SortedNames();
    void insert(const std::string& name);
    bool findFromTop(const std::string& name) const;
    bool findFromBottom(const std::string& name) const;
    std::vector<std::string> names() const;
};
