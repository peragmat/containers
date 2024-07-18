#include "../test.h"

TEST(SetConstructor, DefaultConstructor) {
  s21::set<int> my_set;
  std::set<int> std_set;

  EXPECT_EQ(my_set.size(), std_set.size());
  EXPECT_EQ(my_set.empty(), std_set.empty());
}

TEST(SetConstructor, InitializerListConstructor) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> std_set = {1, 2, 3, 4, 5};

  EXPECT_EQ(my_set.size(), std_set.size());

  for (const auto& value : std_set) {
    EXPECT_TRUE(my_set.find(value) != my_set.end());
  }
}

TEST(SetConstructor, CopyConstructor) {
  s21::set<int> original_set = {1, 2, 3};
  s21::set<int> my_set_copy(original_set);
  std::set<int> std_set_copy(original_set.begin(), original_set.end());

  EXPECT_EQ(my_set_copy.size(), std_set_copy.size());

  for (const auto& value : std_set_copy) {
    EXPECT_TRUE(my_set_copy.find(value) != my_set_copy.end());
  }
}

TEST(SetConstructor, MoveConstructor) {
  s21::set<int> original_set = {1, 2, 3};
  s21::set<int> my_set_move(std::move(original_set));
  std::set<int> std_set_move = {1, 2, 3};

  EXPECT_EQ(my_set_move.size(), std_set_move.size());
  for (const auto& value : std_set_move) {
    EXPECT_TRUE(my_set_move.find(value) != my_set_move.end());
  }

  EXPECT_EQ(original_set.size(), 0);
  EXPECT_TRUE(original_set.empty());
  // std::cout << std::endl << *(original_set.begin()) << " " /*<<
  // original_set.end()*/ << std::endl;
  EXPECT_TRUE(original_set.begin() == original_set.end());
}

TEST(SetAssignmentOperator, CopyAssignmentOperator) {
  s21::set<int> original_set = {1, 2, 3};
  s21::set<int> my_set;

  my_set = original_set;

  EXPECT_EQ(my_set.size(), original_set.size());

  for (const auto& value : original_set) {
    EXPECT_TRUE(my_set.find(value) != my_set.end());
  }

  EXPECT_NE(&my_set, &original_set);
}

TEST(SetAssignmentOperator, MoveAssignmentOperator) {
  s21::set<int> original_set = {1, 2, 3};
  s21::set<int> my_set;

  my_set = std::move(original_set);

  EXPECT_EQ(my_set.size(), 3);

  EXPECT_TRUE(original_set.empty());
}

TEST(SetMethods, EmptyMethod) {
  s21::set<int> my_set;
  std::set<int> std_set;

  EXPECT_EQ(my_set.empty(), std_set.empty());

  my_set.insert(1);
  std_set.insert(1);
  EXPECT_EQ(my_set.empty(), std_set.empty());
}

TEST(SetMethods, SizeMethod) {
  s21::set<int> my_set = {1, 2, 3};
  std::set<int> std_set = {1, 2, 3};

  EXPECT_EQ(my_set.size(), std_set.size());

  my_set.erase(my_set.find(1));
  std_set.erase(std_set.find(1));
  EXPECT_EQ(my_set.size(), std_set.size());

  my_set.clear();
  std_set.clear();
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(SetMethods, MaxSizeMethod) {
  s21::set<int> my_set;
  EXPECT_GE(my_set.max_size(), 0);
}

TEST(SetInsertMethod, InsertExistingElement) {
  s21::set<int> my_set = {1, 2, 3};
  std::set<int> std_set = {1, 2, 3};

  auto result1 = my_set.insert(2);
  auto result2 = std_set.insert(2);

  EXPECT_EQ(result1.second, result2.second);
  EXPECT_EQ(*result1.first, *result2.first);

  for (int i = 1; i <= 3; ++i) {
    EXPECT_EQ(my_set.find(i) != my_set.end(), std_set.find(i) != std_set.end());
  }
}

TEST(SetInsertMethod, InsertString) {
  s21::set<std::string> my_set;
  std::set<std::string> std_set;

  auto result1 = my_set.insert("Hello");
  auto result2 = std_set.insert("Hello");

  EXPECT_EQ(result1.second, result2.second);
  EXPECT_EQ(*result1.first, *result2.first);

  for (const auto& value : std_set) {
    EXPECT_EQ(my_set.find(value) != my_set.end(),
              std_set.find(value) != std_set.end());
  }
}

TEST(SetEraseMethod, EraseExistingElement) {
  s21::set<int> my_set = {1, 2, 3};
  std::set<int> std_set = {1, 2, 3};

  my_set.erase(my_set.find(2));
  std_set.erase(std_set.find(2));

  EXPECT_EQ(my_set.size(), std_set.size());
  EXPECT_EQ(my_set.find(2) == my_set.end(), std_set.find(2) == std_set.end());

  for (int i = 1; i <= 3; ++i) {
    EXPECT_EQ(my_set.find(i) != my_set.end(), std_set.find(i) != std_set.end());
  }
}

TEST(SetSwapMethod, SwapWithEmptySet) {
  s21::set<int> my_set = {1, 2, 3};
  s21::set<int> empty_set;

  my_set.swap(empty_set);

  EXPECT_TRUE(my_set.empty());
  EXPECT_EQ(empty_set.size(), 3);
  EXPECT_TRUE(empty_set.find(1) != empty_set.end());
  EXPECT_TRUE(empty_set.find(2) != empty_set.end());
  EXPECT_TRUE(empty_set.find(3) != empty_set.end());
}

TEST(SetSwapMethod, SwapWithNonEmptySet) {
  s21::set<int> my_set = {1, 2, 3};
  s21::set<int> other_set = {4, 5};

  my_set.swap(other_set);

  EXPECT_EQ(my_set.size(), 2);
  EXPECT_TRUE(my_set.find(4) != my_set.end());
  EXPECT_TRUE(my_set.find(5) != my_set.end());

  EXPECT_EQ(other_set.size(), 3);
  EXPECT_TRUE(other_set.find(1) != other_set.end());
  EXPECT_TRUE(other_set.find(2) != other_set.end());
  EXPECT_TRUE(other_set.find(3) != other_set.end());
}

TEST(SetMergeMethod, MergeWithEmptySet) {
  s21::set<int> my_set = {1, 2, 3};
  s21::set<int> empty_set;

  my_set.merge(empty_set);

  EXPECT_EQ(my_set.size(), 3);
  EXPECT_TRUE(my_set.find(1) != my_set.end());
  EXPECT_TRUE(my_set.find(2) != my_set.end());
  EXPECT_TRUE(my_set.find(3) != my_set.end());
  EXPECT_TRUE(empty_set.empty());
}

TEST(SetMergeMethod, MergeWithNonEmptySet) {
  s21::set<int> my_set = {1, 2, 3};
  s21::set<int> other_set = {3, 4, 5};

  my_set.merge(other_set);

  EXPECT_EQ(my_set.size(), 5);
  for (int i = 1; i < 6; i++) {
    EXPECT_TRUE(my_set.find(i) != my_set.end());
  }

  EXPECT_EQ(other_set.size(), 1);
}

TEST(SetFindMethod, FindExistingElement) {
  s21::set<int> my_set = {1, 2, 3};

  auto iter = my_set.find(2);

  EXPECT_TRUE(iter != my_set.end());
  EXPECT_EQ(*iter, 2);
}

TEST(SetFindMethod, FindNonExistingElement) {
  s21::set<int> my_set = {1, 2, 3};

  auto iter = my_set.find(4);

  EXPECT_TRUE(iter == my_set.end());
}

TEST(SetFindMethod, FindStringElement) {
  s21::set<std::string> my_set = {"apple", "banana", "orange"};

  auto iter = my_set.find("banana");

  EXPECT_TRUE(iter != my_set.end());
  EXPECT_EQ(*iter, "banana");
}

TEST(SetContainsMethod, ContainsExistingElement) {
  s21::set<int> my_set = {1, 2, 3};

  EXPECT_TRUE(my_set.contains(2));
}

TEST(SetContainsMethod, ContainsNonExistingElement) {
  s21::set<int> my_set = {1, 2, 3};

  EXPECT_FALSE(my_set.contains(4));
}

TEST(SetContainsMethod, ContainsStringElement) {
  s21::set<std::string> my_set = {"apple", "banana", "orange"};

  EXPECT_TRUE(my_set.contains("banana"));
}

TEST(SetIteratorMethods, BeginEndEmptySet) {
  s21::set<int> my_set;
  EXPECT_EQ(my_set.begin(), my_set.end());
}

TEST(SetIteratorMethods, BeginEndNonEmptySet) {
  s21::set<int> my_set = {1, 2, 3};

  EXPECT_NE(my_set.begin(), my_set.end());
  EXPECT_EQ(*my_set.begin(), 1);
  EXPECT_EQ(*std::prev(my_set.end()), 3);
  EXPECT_EQ(std::distance(my_set.begin(), my_set.end()), 3);
}

TEST(SetIteratorMethods, CBeginCEndConstSet) {
  const s21::set<int> my_set = {1, 2, 3};

  EXPECT_NE(my_set.cbegin(), my_set.cend());
  EXPECT_EQ(*my_set.cbegin(), 1);
  EXPECT_EQ(*std::prev(my_set.cend()), 3);
  EXPECT_EQ(std::distance(my_set.cbegin(), my_set.cend()), 3);
}

// Тест методов итератора: инкремент и декремент
TEST(SetIteratorMethods, IncrementDecrement) {
  s21::set<int> my_set = {1, 2, 3};

  auto iter = my_set.begin();
  EXPECT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 3);
  ++iter;
  EXPECT_EQ(iter, my_set.end());

  iter = std::prev(my_set.end());
  EXPECT_EQ(*iter, 3);
  --iter;
  EXPECT_EQ(*iter, 2);
  --iter;
  EXPECT_EQ(*iter, 1);

  EXPECT_EQ(iter, my_set.begin());
}

TEST(SetIteratorMethods, CreateConstIterator) {
  const s21::set<int> my_set = {1, 2, 3};

  // Создание const_iterator с помощью метода begin()
  s21::set<int>::const_iterator iter_begin = my_set.begin();
  EXPECT_EQ(*iter_begin, 1);  // Проверка начального элемента

  // Создание const_iterator с помощью метода end()
  s21::set<int>::const_iterator iter_end = my_set.end();
  EXPECT_EQ(iter_end, my_set.cend());  // Итератор должен быть равен cend()
}

TEST(SetInsertMany, InsertMultipleElements) {
  s21::set<int> s;

  auto results = s.insert_many(1, 2, 3);

  EXPECT_EQ(s.size(), 3);
  for (const auto& result : results) {
    EXPECT_TRUE(result.second);
  }
}

TEST(SetInsertMany, InsertDuplicates) {
  s21::set<int> s;

  auto results = s.insert_many(1, 2, 1);

  EXPECT_EQ(s.size(), 2);
  for (size_t i = 0; i < results.size(); ++i) {
    if (i < 2) {
      EXPECT_TRUE(results[i].second);
    } else {
      EXPECT_FALSE(results[i].second);
    }
  }
}

TEST(SetInsertMany, InsertWithHeterogeneousArgs) {
  s21::set<std::string> s;

  auto results = s.insert_many("one", "two", "three");

  EXPECT_EQ(s.size(), 3);
  for (const auto& result : results) {
    EXPECT_TRUE(result.second);
  }
}

TEST(SetInsertMany, InsertPairs) {
  s21::set<std::pair<int, int>> s;

  auto results = s.insert_many(std::make_pair(1, 1), std::make_pair(2, 2),
                               std::make_pair(3, 3));

  EXPECT_EQ(s.size(), 3);
  for (const auto& result : results) {
    EXPECT_TRUE(result.second);
  }
}
