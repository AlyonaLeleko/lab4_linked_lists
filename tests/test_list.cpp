#include "lists.h"
#include <gtest/gtest.h>
TEST(Single, AppendDeleteBottom) {
    SingleList l; addEnd(l, 1); addEnd(l, 2);
    EXPECT_EQ(l.bottom->value, 2);
    EXPECT_TRUE(removeValue(l, 2)); EXPECT_EQ(l.bottom->value, 1);
    EXPECT_TRUE(removeValue(l, 1)); EXPECT_EQ(l.top, nullptr); EXPECT_EQ(l.bottom, nullptr);
}
TEST(Single, SearchMaximumSorted) {
    SingleList l; addBeginning(l, 2); addEnd(l, 4); addEnd(l, 8);
    EXPECT_EQ(findCell(l, 4)->value, 4);
    EXPECT_EQ(findBefore(l, 4)->value, 2);
    EXPECT_EQ(maximum(l), 8); EXPECT_TRUE(isSorted(l));
    addEnd(l, 3); EXPECT_FALSE(isSorted(l)); clear(l);
}
TEST(Double, LinksAndSort) {
    DoubleList l; insertSorted(l, 5); insertSorted(l, 1); insertSorted(l, 3);
    EXPECT_EQ(values(l), (std::vector<int>{1,3,5}));
    EXPECT_EQ(l.bottom->prev->value, 3);
    EXPECT_TRUE(removeValue(l, 1)); EXPECT_EQ(l.top->prev, nullptr);
    clear(l);
}
TEST(Cycle, DetectAndBreak) {
    SingleList l; addEnd(l, 1); addEnd(l, 2); addEnd(l, 3);
    l.bottom->next = l.top->next;
    EXPECT_EQ(cycleStart(l.top), l.top->next);
    EXPECT_TRUE(breakCycle(l.top)); EXPECT_EQ(cycleStart(l.top), nullptr); clear(l);
}
TEST(Planet, ThreeOrders) {
    PlanetList p; p.addPlanet("A", 2, 3, 1); p.addPlanet("B", 1, 2, 3); p.addPlanet("C", 3, 1, 2);
    EXPECT_EQ(p.names(1), (std::vector<std::string>{"B","A","C"}));
    EXPECT_EQ(p.names(2), (std::vector<std::string>{"C","B","A"}));
    EXPECT_EQ(p.names(3), (std::vector<std::string>{"A","C","B"}));
}
TEST(Names, SentinelsAndReverseSearch) {
    SortedNames names;
    EXPECT_FALSE(names.findFromTop("Анна"));
    names.insert("Яна"); names.insert("Анна"); names.insert("Мария");
    EXPECT_EQ(names.names(), (std::vector<std::string>{"Анна", "Мария", "Яна"}));
    EXPECT_TRUE(names.findFromBottom("Мария"));
    EXPECT_TRUE(names.findFromTop("Анна"));
    EXPECT_FALSE(names.findFromBottom("Петр"));
}
TEST(Single, EmptyAndDeleteFirst) {
    SingleList l;
    EXPECT_TRUE(isSorted(l));
    EXPECT_FALSE(removeValue(l, 1));
    EXPECT_THROW(maximum(l), std::invalid_argument);
    addEnd(l, 3); addBeginning(l, 1);
    EXPECT_TRUE(removeValue(l, 1));
    EXPECT_EQ(l.top, l.bottom);
    clear(l);
}
