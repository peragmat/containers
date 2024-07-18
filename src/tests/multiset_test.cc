#include "../test.h"

TEST(MultisetConstructor, DefaultConstructor) {
  s21::multiset<int> my_multiset;
  std::multiset<int> std_multiset;

  EXPECT_EQ(my_multiset.size(), std_multiset.size());
  EXPECT_TRUE(my_multiset.empty());
}

TEST(MultisetConstructor, InitializerListConstructor) {
  s21::multiset<int> my_multiset = {2, 1, 3, 1};
  std::multiset<int> std_multiset = {2, 1, 3, 1};

  EXPECT_EQ(my_multiset.size(), std_multiset.size());
  EXPECT_TRUE(
      std::equal(my_multiset.begin(), my_multiset.end(), std_multiset.begin()));
}

TEST(MultisetConstructor, CopyConstructor) {
  s21::multiset<int> original = {2, 1, 3, 1};
  s21::multiset<int> copy = original;
  std::multiset<int> std_original = {2, 1, 3, 1};
  std::multiset<int> std_copy = std_original;

  EXPECT_EQ(copy.size(), std_copy.size());
  EXPECT_TRUE(std::equal(copy.begin(), copy.end(), std_copy.begin()));
}

TEST(MultisetConstructor, MoveConstructor) {
  s21::multiset<int> original = {2, 1, 3, 1};
  s21::multiset<int> moved = std::move(original);
  std::multiset<int> std_original = {2, 1, 3, 1};
  std::multiset<int> std_moved = std::move(std_original);

  EXPECT_EQ(moved.size(), std_moved.size());
  EXPECT_TRUE(std::equal(moved.begin(), moved.end(), std_moved.begin()));
  EXPECT_TRUE(original.empty());
}

TEST(MultisetAssignment, CopyAssignment) {
  s21::multiset<int> original = {2, 1, 3, 1};
  s21::multiset<int> copy;
  copy = original;
  std::multiset<int> std_original = {2, 1, 3, 1};
  std::multiset<int> std_copy;
  std_copy = std_original;

  EXPECT_EQ(copy.size(), std_copy.size());
  EXPECT_TRUE(std::equal(copy.begin(), copy.end(), std_copy.begin()));
}

TEST(MultisetAssignment, MoveAssignment) {
  s21::multiset<int> original = {2, 1, 3, 1};
  s21::multiset<int> moved;
  moved = std::move(original);
  std::multiset<int> std_original = {2, 1, 3, 1};
  std::multiset<int> std_moved;
  std_moved = std::move(std_original);

  EXPECT_EQ(moved.size(), std_moved.size());
  EXPECT_TRUE(std::equal(moved.begin(), moved.end(), std_moved.begin()));
  EXPECT_TRUE(original.empty());
}

TEST(MultisetEmpty, EmptyMultiset) {
  s21::multiset<int> my_multiset;
  std::multiset<int> std_multiset;

  EXPECT_EQ(my_multiset.empty(), std_multiset.empty());
}

TEST(MultisetEmpty, NonEmptyMultiset) {
  s21::multiset<int> my_multiset = {2, 1, 3};
  std::multiset<int> std_multiset = {2, 1, 3};

  EXPECT_EQ(my_multiset.empty(), std_multiset.empty());
}

TEST(MultisetSize, EmptyMultiset) {
  s21::multiset<int> my_multiset;
  std::multiset<int> std_multiset;

  EXPECT_EQ(my_multiset.size(), std_multiset.size());
}

TEST(MultisetSize, NonEmptyMultiset) {
  s21::multiset<int> my_multiset = {2, 1, 3};
  std::multiset<int> std_multiset = {2, 1, 3};

  EXPECT_EQ(my_multiset.size(), std_multiset.size());
}

TEST(MultisetClear, EmptyMultiset) {
  s21::multiset<int> my_multiset;
  std::multiset<int> std_multiset;

  my_multiset.clear();
  std_multiset.clear();

  EXPECT_TRUE(my_multiset.empty());
  EXPECT_TRUE(std_multiset.empty());
}

TEST(MultisetClear, NonEmptyMultiset) {
  s21::multiset<int> my_multiset = {2, 1, 3};
  std::multiset<int> std_multiset = {2, 1, 3};

  my_multiset.clear();
  std_multiset.clear();

  EXPECT_TRUE(my_multiset.empty());
  EXPECT_TRUE(std_multiset.empty());
}

TEST(MultisetInsert, InsertNewElement) {
  s21::multiset<int> my_multiset;
  std::multiset<int> std_multiset;

  auto result = my_multiset.insert(2);
  auto std_result = std_multiset.insert(2);

  EXPECT_TRUE(result.second);
  EXPECT_EQ(*result.first, *std_result);
  EXPECT_EQ(my_multiset.size(), std_multiset.size());
}

TEST(MultisetInsert, InsertExistingElement) {
  s21::multiset<int> my_multiset = {2, 1, 3};
  std::multiset<int> std_multiset = {2, 1, 3};

  auto result = my_multiset.insert(2);
  auto std_result = std_multiset.insert(2);

  EXPECT_TRUE(result.second);
  EXPECT_EQ(*result.first, *std_result);
  EXPECT_EQ(my_multiset.size(), std_multiset.size());
}

TEST(MultisetInsert, InsertMultipleElements) {
  s21::multiset<int> my_multiset;
  std::multiset<int> std_multiset;

  for (int i = 1; i <= 100; ++i) {
    auto result = my_multiset.insert(1);
    auto std_result = std_multiset.insert(1);

    EXPECT_TRUE(result.second);
    EXPECT_EQ(*result.first, *std_result);
  }

  EXPECT_EQ(my_multiset.size(), std_multiset.size());
}

TEST(MultisetErase, EraseExistingElement) {
  s21::multiset<int> my_multiset = {2, 1, 3, 2, 4};
  std::multiset<int> std_multiset = {2, 1, 3, 2, 4};

  auto my_iter = my_multiset.find(2);
  auto std_iter = std_multiset.find(2);

  my_multiset.erase(my_iter);
  std_multiset.erase(std_iter);

  EXPECT_EQ(my_multiset.size(), std_multiset.size());
  for (int value : my_multiset) {
    EXPECT_TRUE(std_multiset.find(value) != std_multiset.end());
  }
}

TEST(MultisetSwap, SwapSets) {
  s21::multiset<int> my_multiset1 = {1, 2, 3};
  s21::multiset<int> my_multiset2 = {4, 5};

  std::multiset<int> std_multiset1 = {1, 2, 3};
  std::multiset<int> std_multiset2 = {4, 5};

  my_multiset1.swap(my_multiset2);
  std_multiset1.swap(std_multiset2);

  EXPECT_EQ(my_multiset1.size(), std_multiset1.size());
  for (int value : my_multiset1) {
    EXPECT_TRUE(std_multiset1.find(value) != std_multiset1.end());
  }

  EXPECT_EQ(my_multiset2.size(), std_multiset2.size());
  for (int value : my_multiset2) {
    EXPECT_TRUE(std_multiset2.find(value) != std_multiset2.end());
  }
}

TEST(MultisetFind, FindExistingElement) {
  s21::multiset<int> my_multiset = {1, 2, 3};

  const s21::multiset<int>& const_multiset = my_multiset;
  auto it = const_multiset.find(2);

  EXPECT_NE(it, const_multiset.end());
  EXPECT_EQ(*it, 2);
}

TEST(MultisetFind, FindNonExistingElement) {
  s21::multiset<int> my_multiset = {1, 2, 3};

  const s21::multiset<int>& const_multiset = my_multiset;
  auto it = const_multiset.find(4);

  EXPECT_EQ(it, const_multiset.end());
}

TEST(MultisetInsertMany, InsertMultipleElements) {
  s21::multiset<int> ms;

  auto results = ms.insert_many(1, 2, 3, 4, 5);

  EXPECT_EQ(ms.size(), 5);
  for (const auto& result : results) {
    EXPECT_TRUE(result.second);
  }
}

TEST(MultisetInsertMany, InsertDuplicates) {
  s21::multiset<int> ms;

  auto results = ms.insert_many(1, 1, 1, 1, 2, 3, 1, 2, 3, 1, 1, 2, 3);

  EXPECT_EQ(ms.size(), 13);
}

TEST(MultisetInsertMany, InsertPairs) {
  s21::multiset<std::pair<int, int>> ms;

  auto results = ms.insert_many(std::make_pair(1, 2), std::make_pair(2, 3));

  EXPECT_EQ(ms.size(), 2);
  for (const auto& result : results) {
    EXPECT_TRUE(result.second);
  }
}

TEST(MultisetInsertMany, InsertWithHeterogeneousArgs) {
  s21::multiset<int> ms;

  auto results = ms.insert_many(1, 2, 3.0, 4.5);

  EXPECT_EQ(ms.size(), 4);
  for (const auto& result : results) {
    EXPECT_TRUE(result.second);
  }
}

TEST(MergeTest, EmptyMultiset) {
  s21::multiset<int> set1 = {1, 3, 5};
  s21::multiset<int> set2;

  set1.merge(set2);

  EXPECT_TRUE(set2.empty());
  EXPECT_EQ(set1.size(), 3U);
  EXPECT_TRUE(set1.contains(1));
  EXPECT_TRUE(set1.contains(3));
  EXPECT_TRUE(set1.contains(5));
}

TEST(MergeTest, NonEmptyMultiset) {
  s21::multiset<int> set1 = {1, 3, 5};
  s21::multiset<int> set2 = {2, 4, 6};

  set1.merge(set2);

  EXPECT_TRUE(set2.empty());
  EXPECT_EQ(set1.size(), 6U);
  EXPECT_TRUE(set1.contains(1));
  EXPECT_TRUE(set1.contains(2));
  EXPECT_TRUE(set1.contains(3));
  EXPECT_TRUE(set1.contains(4));
  EXPECT_TRUE(set1.contains(5));
  EXPECT_TRUE(set1.contains(6));
}

TEST(MergeTest, EmptyTargetMultiset) {
  s21::multiset<int> set1;
  s21::multiset<int> set2 = {2, 4, 6};

  set1.merge(set2);

  EXPECT_TRUE(set2.empty());
  EXPECT_EQ(set1.size(), 3U);
  EXPECT_TRUE(set1.contains(2));
  EXPECT_TRUE(set1.contains(4));
  EXPECT_TRUE(set1.contains(6));
}

TEST(MergeTest, DuplicateValues) {
  s21::multiset<int> set1 = {1, 3, 3, 5};
  s21::multiset<int> set2 = {2, 3, 4, 6};

  set1.merge(set2);

  EXPECT_TRUE(set2.empty());
  EXPECT_EQ(set1.size(), 8U);
  EXPECT_EQ(set1.count(1), 1);
  EXPECT_EQ(set1.count(2), 1);
  EXPECT_EQ(set1.count(3), 3);
  EXPECT_EQ(set1.count(4), 1);
  EXPECT_EQ(set1.count(5), 1);
  EXPECT_EQ(set1.count(6), 1);
}

TEST(CountTest, EmptyMultiset) {
  s21::multiset<int> set;

  EXPECT_EQ(set.count(5), 0U);
  EXPECT_EQ(set.count(0), 0U);
}

TEST(CountTest, NonEmptyMultiset) {
  s21::multiset<int> set = {1, 2, 2, 3, 3, 3};

  EXPECT_EQ(set.count(1), 1U);
  EXPECT_EQ(set.count(2), 2U);
  EXPECT_EQ(set.count(3), 3U);
  EXPECT_EQ(set.count(0), 0U);
}

TEST(FindTest, EmptyMultiset) {
  s21::multiset<int> set;

  auto iter = set.find(5);

  EXPECT_EQ(iter, set.end());
}

TEST(FindTest, NonEmptyMultiset) {
  s21::multiset<int> set = {1, 2, 3, 4, 5};

  auto iter = set.find(3);

  EXPECT_NE(iter, set.end());
  EXPECT_EQ(*iter, 3);

  auto not_found_iter = set.find(6);
  EXPECT_EQ(not_found_iter, set.end());
}

TEST(ContainsTest, EmptyMultiset) {
  s21::multiset<int> set;

  EXPECT_FALSE(set.contains(5));
  EXPECT_FALSE(set.contains(0));
}

TEST(ContainsTest, NonEmptyMultiset) {
  s21::multiset<int> set = {1, 2, 2, 3, 3, 3};

  EXPECT_TRUE(set.contains(1));
  EXPECT_TRUE(set.contains(2));
  EXPECT_TRUE(set.contains(3));
  EXPECT_FALSE(set.contains(0));
}

TEST(LowerBoundTest, EmptyMultiset) {
  s21::multiset<int> set;

  auto iter = set.lower_bound(5);

  EXPECT_EQ(iter, set.end());
}

TEST(LowerBoundTest, NonEmptyMultiset) {
  s21::multiset<int> set = {1, 2, 3, 4, 5};

  auto iter = set.lower_bound(3);

  EXPECT_NE(iter, set.end());
  EXPECT_EQ(*iter, 3);

  auto not_found_iter = set.lower_bound(6);
  EXPECT_EQ(not_found_iter, set.end());
}

TEST(UpperBoundTest, EmptyMultiset) {
  s21::multiset<int> set;

  auto iter = set.upper_bound(5);

  EXPECT_EQ(iter, set.end());
}

TEST(UpperBoundTest, NonEmptyMultiset) {
  s21::multiset<int> set = {1, 2, 3, 4, 5};

  auto iter = set.upper_bound(3);

  EXPECT_NE(iter, set.end());
  EXPECT_EQ(*iter, 4);

  auto not_found_iter = set.upper_bound(5);
  EXPECT_EQ(not_found_iter, set.end());
}

TEST(EqualRangeTest, EmptyMultiset) {
  s21::multiset<int> set;

  auto range = set.equal_range(5);

  EXPECT_EQ(range.first, set.end());
  EXPECT_EQ(range.second, set.end());
}

TEST(EqualRangeTest, NonEmptyMultiset) {
  s21::multiset<int> set = {1, 2, 2, 3, 3, 3, 4, 5};

  auto range = set.equal_range(3);

  EXPECT_NE(range.first, set.end());
  EXPECT_NE(range.second, set.end());
  EXPECT_EQ(*range.first, 3);
  EXPECT_EQ(*range.second, 4);

  auto not_found_range = set.equal_range(6);
  EXPECT_EQ(not_found_range.first, set.end());
  EXPECT_EQ(not_found_range.second, set.end());
}
