#include "../test.h"

TEST(MapConstructorTest, DefaultConstructor) {
  s21::map<int, int> my_map;
  EXPECT_TRUE(my_map.empty());
  EXPECT_EQ(my_map.size(), 0);
}

TEST(MapConstructorTest, InitializerListConstructor) {
  s21::map<int, int> my_map = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_EQ(my_map.find(1)->second, 10);
  EXPECT_FALSE(my_map.empty());
  EXPECT_EQ(my_map.size(), 3);
  EXPECT_EQ(my_map.at(1), 10);
  EXPECT_EQ(my_map.at(2), 20);
  EXPECT_EQ(my_map.at(3), 30);
}

TEST(MapConstructorTest, CopyConstructor) {
  s21::map<int, int> original_map = {{1, 10}, {2, 20}, {3, 30}};
  s21::map<int, int> copied_map(original_map);

  EXPECT_FALSE(copied_map.empty());
  EXPECT_EQ(copied_map.size(), original_map.size());
  EXPECT_EQ(copied_map.at(1), 10);
  EXPECT_EQ(copied_map.at(2), 20);
  EXPECT_EQ(copied_map.at(3), 30);

  copied_map[1] = 100;
  EXPECT_NE(copied_map.at(1), original_map.at(1));
}

TEST(MapConstructorTest, MoveConstructor) {
  s21::map<int, int> original_map = {{1, 10}, {2, 20}, {3, 30}};
  s21::map<int, int> moved_map(std::move(original_map));

  EXPECT_TRUE(original_map.empty());
  EXPECT_EQ(moved_map.size(), 3);
  EXPECT_EQ(moved_map.at(1), 10);
  EXPECT_EQ(moved_map.at(2), 20);
  EXPECT_EQ(moved_map.at(3), 30);

  moved_map[1] = 100;
  EXPECT_EQ(moved_map.at(1), 100);
  EXPECT_THROW(original_map.at(1), std::out_of_range);
}

TEST(MapAssignmentOperator, CopyAssignment) {
  s21::map<int, int> map1 = {{1, 10}, {2, 20}, {3, 30}};
  s21::map<int, int> map2 = {{4, 40}, {5, 50}};

  map2 = map1;

  EXPECT_EQ(map2.size(), map1.size());
  EXPECT_TRUE(std::equal(map1.begin(), map1.end(), map2.begin()));

  map1.clear();
  EXPECT_EQ(map2.size(), 3);
  EXPECT_EQ(map2[1], 10);
  EXPECT_EQ(map2[2], 20);
  EXPECT_EQ(map2[3], 30);
}

TEST(MapAssignmentOperator, MoveAssignment) {
  s21::map<int, int> map1 = {{1, 10}, {2, 20}, {3, 30}};
  s21::map<int, int> map2 = {{4, 40}, {5, 50}};

  map2 = std::move(map1);

  EXPECT_EQ(map2.size(), 3);
  EXPECT_TRUE(map1.empty());

  EXPECT_EQ(map2[1], 10);
  EXPECT_EQ(map2[2], 20);
  EXPECT_EQ(map2[3], 30);
}

TEST(MapAtMethod, AccessExistingElement) {
  s21::map<int, int> map = {{1, 10}, {2, 20}, {3, 30}};

  int& value_ref = map.at(2);
  const int& const_value_ref = map.at(2);

  EXPECT_EQ(value_ref, 20);
  EXPECT_EQ(const_value_ref, 20);
}

TEST(MapAtMethod, AccessNonExistingElement) {
  s21::map<int, int> map = {{1, 10}, {2, 20}, {3, 30}};

  EXPECT_THROW(map.at(4), std::out_of_range);
}

TEST(MapConstAtMethod, AccessExistingElement) {
  const s21::map<int, int> map = {{1, 10}, {2, 20}, {3, 30}};

  const int& value_ref = map.at(2);

  EXPECT_EQ(value_ref, 20);
}

TEST(MapConstAtMethod, AccessNonExistingElement) {
  const s21::map<int, int> map = {{1, 10}, {2, 20}, {3, 30}};

  EXPECT_THROW(map.at(4), std::out_of_range);
}

TEST(MapCapacityMethods, EmptyMethod) {
  s21::map<int, int> map;
  EXPECT_TRUE(map.empty());

  map[1] = 10;
  EXPECT_FALSE(map.empty());

  map.clear();
  EXPECT_TRUE(map.empty());
}

TEST(MapCapacityMethods, SizeMethod) {
  s21::map<int, int> map = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_EQ(map.size(), 3);

  map.erase(map.find(1));
  EXPECT_EQ(map.size(), 2);

  map.clear();
  EXPECT_EQ(map.size(), 0);
}

TEST(MapCapacityMethods, MaxSizeMethod) {
  s21::map<int, int> map;
  EXPECT_GE(map.max_size(), 0);
}

TEST(MapModifiers, ClearMethod) {
  s21::map<int, int> map = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_FALSE(map.empty());

  map.clear();
  EXPECT_TRUE(map.empty());
}

TEST(MapInsertMethod, InsertNewElement) {
  s21::map<int, int> map;

  auto result = map.insert({1, 10});

  EXPECT_TRUE(result.second);
  EXPECT_EQ(result.first->first, 1);
  EXPECT_EQ(result.first->second, 10);

  EXPECT_TRUE(map.contains(1));
  EXPECT_EQ(map.size(), 1);
}

TEST(MapInsertMethod, InsertExistingElement) {
  s21::map<int, int> map = {{1, 10}, {2, 20}};

  auto result = map.insert({2, 30});

  EXPECT_FALSE(result.second);
  EXPECT_EQ(result.first->first, 2);
  EXPECT_EQ(result.first->second, 20);

  EXPECT_EQ(map.size(), 2);
}

TEST(MapInsertMethod, InsertMultipleElements) {
  s21::map<int, int> map;

  map.insert({3, 30});
  map.insert({1, 10});
  map.insert({4, 40});
  map.insert({2, 20});

  EXPECT_EQ(map.size(), 4);

  EXPECT_EQ(map.at(1), 10);
  EXPECT_EQ(map.at(2), 20);
  EXPECT_EQ(map.at(3), 30);
  EXPECT_EQ(map.at(4), 40);

  EXPECT_FALSE(map.insert({3, 300}).second);
  EXPECT_EQ(map.at(3), 30);
}

TEST(MapInsertMethod, InsertAndGetValues) {
  s21::map<std::string, double> map;

  map.insert({"pi", 3.14159});
  map.insert({"e", 2.71828});
  map.insert({"phi", 1.61803});

  EXPECT_EQ(map.size(), 3);

  EXPECT_DOUBLE_EQ(map.at("pi"), 3.14159);
  EXPECT_DOUBLE_EQ(map.at("e"), 2.71828);
  EXPECT_DOUBLE_EQ(map.at("phi"), 1.61803);

  EXPECT_FALSE(map.insert({"pi", 3.14}).second);
  EXPECT_DOUBLE_EQ(map.at("pi"), 3.14159);
}

TEST(MapInsertMethod, InsertCustomType) {
  struct Point {
    int x, y;
    bool operator<(const Point& other) const {
      return x < other.x || (x == other.x && y < other.y);
    }
  };

  s21::map<Point, std::string> map;

  map.insert({{1, 2}, "A"});
  map.insert({{3, 4}, "B"});
  map.insert({{5, 6}, "C"});

  EXPECT_EQ(map.size(), 3);

  EXPECT_EQ(map.at({1, 2}), "A");
  EXPECT_EQ(map.at({3, 4}), "B");
  EXPECT_EQ(map.at({5, 6}), "C");

  auto result = map.insert({{3, 4}, "D"});
  EXPECT_FALSE(result.second);
  EXPECT_EQ(result.first->second, "B");

  EXPECT_THROW(map.at({7, 8}), std::out_of_range);
}

TEST(MapInsertMethod, InsertPairNewElement) {
  s21::map<int, double> my_map;

  auto result = my_map.insert(1, 1.1);

  ASSERT_TRUE(result.second);
  ASSERT_EQ(result.first->first, 1);
  ASSERT_EQ(result.first->second, 1.1);
  ASSERT_TRUE(my_map.contains(1));
}

TEST(MapInsertMethod, InsertPairExistingElement) {
  s21::map<int, double> my_map = {{1, 1.1}, {2, 2.2}};

  auto result = my_map.insert(2, 3.3);

  ASSERT_FALSE(result.second);
  ASSERT_EQ(result.first->first, 2);
  ASSERT_EQ(result.first->second, 2.2);
  ASSERT_TRUE(my_map.contains(2));
}

TEST(MapInsertOrAssign, InsertOrAssignNewElement) {
  s21::map<int, double> my_map;

  auto result = my_map.insert_or_assign(1, 1.1);

  ASSERT_TRUE(result.second);
  ASSERT_EQ(result.first->first, 1);
  ASSERT_EQ(result.first->second, 1.1);
  ASSERT_TRUE(my_map.contains(1));
}

TEST(MapInsertOrAssign, InsertOrAssignExistingElement) {
  s21::map<int, double> my_map = {{1, 1.1}, {2, 2.2}};

  auto result = my_map.insert_or_assign(2, 3.3);

  ASSERT_FALSE(result.second);
  ASSERT_EQ(result.first->first, 2);
  ASSERT_EQ(result.first->second, 3.3);
  ASSERT_TRUE(my_map.contains(2));
}

TEST(MapInsertOrAssign, InsertOrAssignNewElementWithAssignment) {
  s21::map<int, double> my_map;

  auto result = my_map.insert_or_assign(1, 1.1);

  ASSERT_TRUE(result.second);
  ASSERT_EQ(result.first->first, 1);
  ASSERT_EQ(result.first->second, 1.1);
  ASSERT_TRUE(my_map.contains(1));
}

TEST(MapInsertOrAssign, InsertOrAssignExistingElementWithAssignment) {
  s21::map<int, double> my_map = {{1, 1.1}, {2, 2.2}};

  auto result = my_map.insert_or_assign(2, 3.3);

  ASSERT_FALSE(result.second);
  ASSERT_EQ(result.first->first, 2);
  ASSERT_EQ(result.first->second, 3.3);
  ASSERT_TRUE(my_map.contains(2));
}

TEST(MapErase, EraseExistingElement) {
  s21::map<int, double> my_map = {{1, 1.1}, {2, 2.2}, {3, 3.3}};

  my_map.erase(my_map.find(2));

  ASSERT_EQ(my_map.size(), 2);
  ASSERT_FALSE(my_map.contains(2));
  ASSERT_TRUE(my_map.contains(1));
  ASSERT_TRUE(my_map.contains(3));
}

TEST(MapErase, EraseNonExistingElement) {
  s21::map<int, double> my_map = {{1, 1.1}, {2, 2.2}, {3, 3.3}};

  my_map.erase(my_map.find(4));

  ASSERT_EQ(my_map.size(), 3);
  ASSERT_TRUE(my_map.contains(1));
  ASSERT_TRUE(my_map.contains(2));
  ASSERT_TRUE(my_map.contains(3));
}

TEST(MapErase, EraseLastElement) {
  s21::map<int, double> my_map = {{1, 1.1}};

  my_map.erase(my_map.find(1));

  ASSERT_EQ(my_map.size(), 0);
  ASSERT_FALSE(my_map.contains(1));
}

TEST(MapErase, EraseWithComparator) {
  s21::map<int, double, std::greater<int>> my_map = {
      {3, 3.3}, {2, 2.2}, {1, 1.1}};

  my_map.erase(my_map.find(2));

  ASSERT_EQ(my_map.size(), 2);
  ASSERT_FALSE(my_map.contains(2));
  ASSERT_TRUE(my_map.contains(1));
  ASSERT_TRUE(my_map.contains(3));
}

TEST(MapSwapMerge, Swap) {
  s21::map<int, double> my_map1 = {{1, 1.1}, {2, 2.2}};
  s21::map<int, double> my_map2 = {{3, 3.3}, {4, 4.4}};

  my_map1.swap(my_map2);

  ASSERT_EQ(my_map1.size(), 2);
  ASSERT_EQ(my_map2.size(), 2);

  ASSERT_TRUE(my_map1.contains(3));
  ASSERT_TRUE(my_map1.contains(4));
  ASSERT_TRUE(my_map2.contains(1));
  ASSERT_TRUE(my_map2.contains(2));
}

TEST(MapSwapMerge, Merge) {
  s21::map<int, double> my_map1 = {{1, 1.1}, {2, 2.2}};
  s21::map<int, double> my_map2 = {{3, 3.3}, {4, 4.4}};

  my_map1.merge(my_map2);

  ASSERT_EQ(my_map1.size(), 4);
  ASSERT_EQ(my_map2.size(), 0);

  ASSERT_TRUE(my_map1.contains(1));
  ASSERT_TRUE(my_map1.contains(2));
  ASSERT_TRUE(my_map1.contains(3));
  ASSERT_TRUE(my_map1.contains(4));
}

TEST(MapSwapMerge, MergeWithDuplicates) {
  s21::map<int, double> my_map1 = {{1, 1.1}, {2, 2.2}};
  s21::map<int, double> my_map2 = {{2, 3.3}, {4, 4.4}};

  my_map1.merge(my_map2);

  ASSERT_EQ(my_map1.size(), 3);
  ASSERT_EQ(my_map2.size(), 1);

  ASSERT_TRUE(my_map1.contains(1));
  ASSERT_TRUE(my_map1.contains(2));
  ASSERT_TRUE(my_map1.contains(4));

  ASSERT_EQ(my_map1[2], 2.2);
}

TEST(MapSwapMerge, MergeWithComparator) {
  s21::map<int, double, std::greater<int>> my_map1 = {{2, 2.2}, {1, 1.1}};
  s21::map<int, double, std::greater<int>> my_map2 = {{3, 3.3}, {4, 4.4}};

  my_map1.merge(my_map2);

  ASSERT_EQ(my_map1.size(), 4);
  ASSERT_EQ(my_map2.size(), 0);

  ASSERT_TRUE(my_map1.contains(1));
  ASSERT_TRUE(my_map1.contains(2));
  ASSERT_TRUE(my_map1.contains(3));
  ASSERT_TRUE(my_map1.contains(4));
}

TEST(MapSwapMerge, SwapAndMerge) {
  s21::map<int, double> my_map1 = {{1, 1.1}, {2, 2.2}};
  s21::map<int, double> my_map2 = {{3, 3.3}, {4, 4.4}};
  s21::map<int, double> my_map3 = {{5, 5.5}};

  my_map1.swap(my_map2);
  my_map1.merge(my_map3);

  ASSERT_EQ(my_map1.size(), 3);
  ASSERT_EQ(my_map2.size(), 2);
  ASSERT_EQ(my_map3.size(), 0);

  ASSERT_TRUE(my_map1.contains(5));
  ASSERT_TRUE(my_map1.contains(3));
  ASSERT_TRUE(my_map1.contains(4));
}

TEST(MapContainsMethod, ContainsExistingKey) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_TRUE(map.contains(2));
  EXPECT_TRUE(map.contains(3));
}

TEST(MapContainsMethod, ContainsNonExistingKey) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_FALSE(map.contains(4));
  EXPECT_FALSE(map.contains(5));
}

TEST(MapIteratorMethods, BeginEnd) {
  s21::map<int, double> map = {{1, 1.1}, {2, 2.2}, {3, 3.3}};

  auto iter = map.begin();
  EXPECT_EQ(iter->first, 1);
  EXPECT_DOUBLE_EQ(iter->second, 1.1);

  auto citer = map.cbegin();
  EXPECT_EQ(citer->first, 1);
  EXPECT_DOUBLE_EQ(citer->second, 1.1);

  auto end_iter = map.end();
  EXPECT_EQ(--end_iter, map.find(3));
}

TEST(MapIteratorMethods, IterateOverElements) {
  s21::map<char, int> map = {{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}};

  int expected_value = 1;
  for (const auto& pair : map) {
    EXPECT_EQ(pair.second, expected_value);
    ++expected_value;
  }
}
TEST(MapInsertMany, InsertMultipleElements) {
  s21::map<int, int> m;

  auto results = m.insert_many(std::make_pair(1, 1), std::make_pair(2, 2),
                               std::make_pair(3, 3));

  EXPECT_EQ(m.size(), 3);
  for (const auto& result : results) {
    EXPECT_TRUE(result.second);
  }
}

TEST(MapInsertMany, InsertPairs) {
  s21::map<int, std::string> m;

  auto results =
      m.insert_many(std::make_pair(1, "one"), std::make_pair(2, "two"));

  EXPECT_EQ(m.size(), 2);
  for (const auto& result : results) {
    EXPECT_TRUE(result.second);
  }
}
