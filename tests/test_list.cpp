#include <gtest/gtest.h>

#include <stdexcept>

#include "lists.h"
TEST(Single, AppendDeleteBottom) {
    SingleList a;
    EXPECT_THROW(maximum(a), std::runtime_error);
    append(a, 3);
    append(a, 9);
    append(a, 1);
    EXPECT_EQ(maximum(a), 9);
    EXPECT_FALSE(sorted(a));
    EXPECT_TRUE(erase(a, 1));
    EXPECT_EQ(a.bottom->value, 9);
    EXPECT_TRUE(erase(a, 3));
    EXPECT_EQ(a.top->value, 9);
    EXPECT_TRUE(erase(a, 9));
    EXPECT_EQ(a.bottom, nullptr);
    EXPECT_FALSE(erase(a, 9));
    clear(a);
}
TEST(Double, LinksAndSort) {
    DoubleList a;
    pushFront(a, 4);
    pushBack(a, 8);
    pushFrontViaInsert(a, 2);
    pushBackViaInsert(a, 10);
    EXPECT_EQ(values(a), (std::vector<int>{2, 4, 8, 10}));
    EXPECT_TRUE(erase(a, 4));
    EXPECT_EQ(a.top->next->prev, a.top);
    EXPECT_TRUE(erase(a, 2));
    EXPECT_EQ(a.top->prev, nullptr);
    EXPECT_TRUE(erase(a, 10));
    EXPECT_EQ(a.bottom->next, nullptr);
    clear(a);
    insertSorted(a, 5);
    insertSorted(a, 1);
    insertSorted(a, 3);
    EXPECT_EQ(values(a), (std::vector<int>{1, 3, 5}));
    clear(a);
}
TEST(Cycle, DetectAndBreak) {
    SingleList a;
    append(a, 1);
    append(a, 2);
    append(a, 3);
    EXPECT_EQ(cycleStart(a.top), nullptr);
    a.bottom->next = a.top->next;
    EXPECT_EQ(cycleStart(a.top), a.top->next);
    EXPECT_TRUE(breakCycle(a.top));
    EXPECT_EQ(cycleStart(a.top), nullptr);
    clear(a);
}
TEST(Planet, ThreeOrders) {
    PlanetList a;
    addPlanet(a, "B", 2, 1, 3);
    addPlanet(a, "A", 1, 3, 2);
    addPlanet(a, "C", 3, 2, 1);
    EXPECT_EQ(planetNames(a, 1), (std::vector<std::string>{"A", "B", "C"}));
    EXPECT_EQ(planetNames(a, 2), (std::vector<std::string>{"B", "C", "A"}));
    EXPECT_EQ(planetNames(a, 3), (std::vector<std::string>{"C", "A", "B"}));
    clear(a);
}
