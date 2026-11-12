#include "lists.h"
#include <stdexcept>

void addEnd(SingleList& l, int x) {
    Cell* n = new Cell{x, nullptr};
    if (!l.top) l.top = n;
    else l.bottom->next = n;
    l.bottom = n;
}
void addBeginning(SingleList& l, int x) {
    l.top = new Cell{x, l.top};
    if (!l.bottom) l.bottom = l.top;
}
Cell* findCell(const SingleList& l, int x) {
    for (Cell* p = l.top; p; p = p->next) if (p->value == x) return p;
    return nullptr;
}
Cell* findBefore(const SingleList& l, int x) {
    for (Cell* p = l.top; p && p->next; p = p->next)
        if (p->next->value == x) return p;
    return nullptr;
}
bool removeValue(SingleList& l, int x) {
    Cell* prev = nullptr;
    Cell* p = l.top;
    while (p && p->value != x) { prev = p; p = p->next; }
    if (!p) return false;
    if (prev) prev->next = p->next;
    else l.top = p->next;
    if (l.bottom == p) l.bottom = prev;
    delete p;
    return true;
}
int maximum(const SingleList& l) {
    if (!l.top) throw std::invalid_argument("Пустой список");
    int answer = l.top->value;
    for (Cell* p = l.top->next; p; p = p->next)
        if (p->value > answer) answer = p->value;
    return answer;
}
bool isSorted(const SingleList& l) {
    for (Cell* p = l.top; p && p->next; p = p->next)
        if (p->value > p->next->value) return false;
    return true;
}
std::vector<int> values(const SingleList& l) {
    std::vector<int> result;
    for (Cell* p = l.top; p; p = p->next) result.push_back(p->value);
    return result;
}
void clear(SingleList& l) {
    while (l.top) { Cell* p = l.top; l.top = p->next; delete p; }
    l.bottom = nullptr;
}
Cell* cycleStart(Cell* top) {
    Cell* slow = top;
    Cell* fast = top;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            fast = top;
            while (fast != slow) { fast = fast->next; slow = slow->next; }
            return fast;
        }
    }
    return nullptr;
}
bool breakCycle(Cell* top) {
    Cell* start = cycleStart(top);
    if (!start) return false;
    Cell* last = start;
    while (last->next != start) last = last->next;
    last->next = nullptr;
    return true;
}
void insertCell(DoubleList& l, DCell* before, DCell* n) {
    if (!n) throw std::invalid_argument("Нет ячейки");
    if (!before) {
        n->prev = nullptr;
        n->next = l.top;
        if (l.top) l.top->prev = n;
        else l.bottom = n;
        l.top = n;
    } else {
        n->prev = before;
        n->next = before->next;
        if (before->next) before->next->prev = n;
        else l.bottom = n;
        before->next = n;
    }
}
void addBeginning(DoubleList& l, int x) { insertCell(l, nullptr, new DCell{x}); }
void addEnd(DoubleList& l, int x) { insertCell(l, l.bottom, new DCell{x}); }
bool removeValue(DoubleList& l, int x) {
    DCell* p = l.top;
    while (p && p->value != x) p = p->next;
    if (!p) return false;
    if (p->prev) p->prev->next = p->next;
    else l.top = p->next;
    if (p->next) p->next->prev = p->prev;
    else l.bottom = p->prev;
    delete p;
    return true;
}
void insertSorted(DoubleList& l, int x) {
    DCell* p = l.top;
    DCell* before = nullptr;
    while (p && p->value < x) { before = p; p = p->next; }
    insertCell(l, before, new DCell{x});
}
std::vector<int> values(const DoubleList& l) {
    std::vector<int> result;
    for (DCell* p = l.top; p; p = p->next) result.push_back(p->value);
    return result;
}
void clear(DoubleList& l) {
    while (l.top) { DCell* p = l.top; l.top = p->next; delete p; }
    l.bottom = nullptr;
}
PlanetList::~PlanetList() { for (Planet* p : owned) delete p; }
void PlanetList::addPlanet(const std::string& name, double distance, double mass, double diameter) {
    Planet* n = new Planet{name, distance, mass, diameter};
    owned.push_back(n);
    Planet** a = &byDistance;
    while (*a && (*a)->distance < distance) a = &(*a)->nextDistance;
    n->nextDistance = *a; *a = n;
    Planet** b = &byMass;
    while (*b && (*b)->mass < mass) b = &(*b)->nextMass;
    n->nextMass = *b; *b = n;
    Planet** c = &byDiameter;
    while (*c && (*c)->diameter < diameter) c = &(*c)->nextDiameter;
    n->nextDiameter = *c; *c = n;
}
std::vector<std::string> PlanetList::names(int order) const {
    if (order < 1 || order > 3) throw std::invalid_argument("Выберите 1, 2 или 3");
    std::vector<std::string> result;
    for (Planet* p = order == 1 ? byDistance : order == 2 ? byMass : byDiameter;
         p; p = order == 1 ? p->nextDistance : order == 2 ? p->nextMass : p->nextDiameter)
        result.push_back(p->name);
    return result;
}

SortedNames::SortedNames() {
    topSentinel.next = &bottomSentinel;
    bottomSentinel.prev = &topSentinel;
}
SortedNames::~SortedNames() {
    NameCell* p = topSentinel.next;
    while (p != &bottomSentinel) {
        NameCell* next = p->next;
        delete p;
        p = next;
    }
}
void SortedNames::insert(const std::string& name) {
    NameCell* p = topSentinel.next;
    while (p != &bottomSentinel && p->name < name) p = p->next;
    NameCell* n = new NameCell{name, p, p->prev};
    p->prev->next = n;
    p->prev = n;
}
bool SortedNames::findFromTop(const std::string& name) const {
    for (NameCell* p = topSentinel.next; p != &bottomSentinel && p->name <= name; p = p->next)
        if (p->name == name) return true;
    return false;
}
bool SortedNames::findFromBottom(const std::string& name) const {
    for (NameCell* p = bottomSentinel.prev; p != &topSentinel && p->name >= name; p = p->prev)
        if (p->name == name) return true;
    return false;
}
std::vector<std::string> SortedNames::names() const {
    std::vector<std::string> result;
    for (NameCell* p = topSentinel.next; p != &bottomSentinel; p = p->next)
        result.push_back(p->name);
    return result;
}
