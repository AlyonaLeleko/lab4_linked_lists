#include "lists.h"

#include <stdexcept>

void append(SingleList& a, int x) {
    Node* p = new Node{x};
    if (!a.top)
        a.top = a.bottom = p;
    else {
        a.bottom->next = p;
        a.bottom = p;
    }
}
bool erase(SingleList& a, int x) {
    Node* prev = nullptr;
    Node* p = a.top;
    while (p && p->value != x) {
        prev = p;
        p = p->next;
    }
    if (!p) return false;
    if (prev)
        prev->next = p->next;
    else
        a.top = p->next;
    if (a.bottom == p) a.bottom = prev;
    delete p;
    return true;
}
int maximum(const SingleList& a) {
    if (!a.top) throw std::runtime_error("Список пуст");
    int mx = a.top->value;
    for (Node* p = a.top->next; p; p = p->next)
        if (p->value > mx) mx = p->value;
    return mx;
}
bool sorted(const SingleList& a) {
    for (Node* p = a.top; p && p->next; p = p->next)
        if (p->value > p->next->value) return false;
    return true;
}
std::vector<int> values(const SingleList& a) {
    std::vector<int> v;
    for (Node* p = a.top; p; p = p->next) v.push_back(p->value);
    return v;
}
void clear(SingleList& a) {
    while (a.top) {
        Node* p = a.top;
        a.top = p->next;
        delete p;
    }
    a.bottom = nullptr;
}
Node* cycleStart(Node* top) {
    Node* slow = top;
    Node* fast = top;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            fast = top;
            while (fast != slow) {
                fast = fast->next;
                slow = slow->next;
            }
            return fast;
        }
    }
    return nullptr;
}
bool breakCycle(Node* top) {
    Node* start = cycleStart(top);
    if (!start) return false;
    Node* p = start;
    while (p->next != start) p = p->next;
    p->next = nullptr;
    return true;
}
void insertAfter(DoubleList& a, DNode* pos, DNode* p) {
    if (!pos) {
        p->prev = nullptr;
        p->next = a.top;
        if (a.top)
            a.top->prev = p;
        else
            a.bottom = p;
        a.top = p;
    } else {
        p->prev = pos;
        p->next = pos->next;
        if (pos->next)
            pos->next->prev = p;
        else
            a.bottom = p;
        pos->next = p;
    }
}
void pushFront(DoubleList& a, int x) {
    DNode* p = new DNode{x};
    p->next = a.top;
    if (a.top)
        a.top->prev = p;
    else
        a.bottom = p;
    a.top = p;
}
void pushBack(DoubleList& a, int x) {
    DNode* p = new DNode{x};
    p->prev = a.bottom;
    if (a.bottom)
        a.bottom->next = p;
    else
        a.top = p;
    a.bottom = p;
}
void pushFrontViaInsert(DoubleList& a, int x) { insertAfter(a, nullptr, new DNode{x}); }
void pushBackViaInsert(DoubleList& a, int x) { insertAfter(a, a.bottom, new DNode{x}); }
bool erase(DoubleList& a, int x) {
    DNode* p = a.top;
    while (p && p->value != x) p = p->next;
    if (!p) return false;
    if (p->prev)
        p->prev->next = p->next;
    else
        a.top = p->next;
    if (p->next)
        p->next->prev = p->prev;
    else
        a.bottom = p->prev;
    delete p;
    return true;
}
void insertSorted(DoubleList& a, int x) {
    DNode* p = a.top;
    while (p && p->value <= x) p = p->next;
    insertAfter(a, p ? p->prev : a.bottom, new DNode{x});
}
std::vector<int> values(const DoubleList& a) {
    std::vector<int> v;
    for (DNode* p = a.top; p; p = p->next) v.push_back(p->value);
    return v;
}
void clear(DoubleList& a) {
    while (a.top) {
        DNode* p = a.top;
        a.top = p->next;
        delete p;
    }
    a.bottom = nullptr;
}
void addPlanet(PlanetList& a, const std::string& name, double distance, double mass,
               double diameter) {
    Planet* p = new Planet{name, distance, mass, diameter};
    a.owned.push_back(p);
    auto insert = [p](Planet*& head, auto next, auto get) {
        Planet** cur = &head;
        while (*cur && get(*cur) <= get(p)) cur = &((*cur)->*next);
        p->*next = *cur;
        *cur = p;
    };
    insert(a.byDistance, &Planet::nextDistance, [](Planet* q) { return q->distance; });
    insert(a.byMass, &Planet::nextMass, [](Planet* q) { return q->mass; });
    insert(a.byDiameter, &Planet::nextDiameter, [](Planet* q) { return q->diameter; });
}
std::vector<std::string> planetNames(const PlanetList& a, int field) {
    std::vector<std::string> v;
    if (field < 1 || field > 3) throw std::invalid_argument("Номер сортировки 1-3");
    Planet* p = field == 1 ? a.byDistance : field == 2 ? a.byMass : a.byDiameter;
    while (p) {
        v.push_back(p->name);
        p = field == 1 ? p->nextDistance : field == 2 ? p->nextMass : p->nextDiameter;
    }
    return v;
}
void clear(PlanetList& a) {
    for (Planet* p : a.owned) delete p;
    a.owned.clear();
    a.byDistance = a.byMass = a.byDiameter = nullptr;
}
