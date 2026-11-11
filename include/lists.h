#pragma once
#include <string>
#include <vector>

struct Node {
    int value;
    Node* next = nullptr;
};
struct SingleList {
    Node* top = nullptr;
    Node* bottom = nullptr;
};
void append(SingleList& a, int x);
bool erase(SingleList& a, int x);
int maximum(const SingleList& a);
bool sorted(const SingleList& a);
std::vector<int> values(const SingleList& a);
void clear(SingleList& a);
Node* cycleStart(Node* top);
bool breakCycle(Node* top);

struct DNode {
    int value;
    DNode* next = nullptr;
    DNode* prev = nullptr;
};
struct DoubleList {
    DNode* top = nullptr;
    DNode* bottom = nullptr;
};
void insertAfter(DoubleList& a, DNode* pos, DNode* node);
void pushFront(DoubleList& a, int x);
void pushBack(DoubleList& a, int x);
void pushFrontViaInsert(DoubleList& a, int x);
void pushBackViaInsert(DoubleList& a, int x);
bool erase(DoubleList& a, int x);
void insertSorted(DoubleList& a, int x);
std::vector<int> values(const DoubleList& a);
void clear(DoubleList& a);

struct Planet {
    std::string name;
    double distance, mass, diameter;
    Planet* nextDistance = nullptr;
    Planet* nextMass = nullptr;
    Planet* nextDiameter = nullptr;
};
struct PlanetList {
    std::vector<Planet*> owned;
    Planet* byDistance = nullptr;
    Planet* byMass = nullptr;
    Planet* byDiameter = nullptr;
};
void addPlanet(PlanetList& a, const std::string& name, double distance, double mass,
               double diameter);
std::vector<std::string> planetNames(const PlanetList& a, int field);
void clear(PlanetList& a);
