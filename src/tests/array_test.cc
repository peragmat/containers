#include <gtest/gtest.h>

#include "include/array_suit.h"

TEST_F(s21_array_test, constr1) {
  s21::array<int, 10> arr1;
  std::array<int, 10> arr2;
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr1.max_size(), arr2.max_size());
}

TEST_F(s21_array_test, constr2) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr1.max_size(), arr2.max_size());
  for (int i = 0; i < 10; i++) EXPECT_EQ(arr1.at(i), arr2.at(i));
}

TEST_F(s21_array_test, constr3) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr1.max_size(), arr2.max_size());
  for (int i = 0; i < 10; i++) EXPECT_EQ(arr1.at(i), arr2.at(i));
}

TEST_F(s21_array_test, constr4) {
  try {
    s21::array<int, 3> arr1 = {1, 2, 3, 4};
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const &err) {
    EXPECT_EQ(err.what(), std::string("Too many initializers for s21::array"));
  }
}

TEST_F(s21_array_test, constr5) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  std::array<int, 3> arr2 = {1, 2, 3};
  auto arr11 = std::move(arr1);
  auto arr22 = std::move(arr2);
  auto it1 = arr11.begin();
  for (auto it2 = arr22.begin(); it2 != arr22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr11.size(), arr22.size());
}

TEST_F(s21_array_test, constr6) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  std::array<int, 3> arr2 = {1, 2, 3};
  auto arr11 = arr1;
  auto arr22 = arr2;
  auto it1 = arr11.begin();
  for (auto it2 = arr22.begin(); it2 != arr22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr11.size(), arr22.size());
}

TEST_F(s21_array_test, constr7) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  std::array<int, 3> arr2 = {1, 2, 3};
  s21::array<int, 3> arr11;
  std::array<int, 3> arr22;
  arr11 = std::move(arr1);
  arr22 = std::move(arr2);
  auto it1 = arr11.begin();
  for (auto it2 = arr22.begin(); it2 != arr22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr11.size(), arr22.size());
}

TEST_F(s21_array_test, at1) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (int i = 0; i < 10; i++) EXPECT_EQ(arr1.at(i), arr2.at(i));
}

TEST_F(s21_array_test, at2) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_ANY_THROW(arr1.at(-3));
}

TEST_F(s21_array_test, operator1) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (int i = 0; i < 10; i++) EXPECT_EQ(arr1[i], arr2[i]);
}

TEST_F(s21_array_test, front1) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(arr1.front(), arr2.front());
}

TEST_F(s21_array_test, back1) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(arr1.back(), arr2.back());
}

TEST_F(s21_array_test, data1) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(*(arr1.data()), *(arr2.data()));
}

TEST_F(s21_array_test, begin1) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it1 = arr1.begin();
  auto it2 = arr2.begin();
  EXPECT_EQ(*it1, *it2);
}

TEST_F(s21_array_test, end1) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  auto it1 = arr1.end();
  auto it2 = arr2.end();
  it1--, it2--;
  EXPECT_EQ(*it2, *it1);
}

TEST_F(s21_array_test, empty1) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(arr1.empty(), arr2.empty());
}

TEST_F(s21_array_test, empty2) {
  s21::array<int, 10> arr1;
  std::array<int, 10> arr2;
  EXPECT_EQ(arr1.empty(), arr2.empty());
}

TEST_F(s21_array_test, size1) {
  s21::array<int, 10> arr1;
  std::array<int, 10> arr2;
  EXPECT_EQ(arr1.size(), arr2.size());
}

TEST_F(s21_array_test, size2) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(arr1.size(), arr2.size());
}

TEST_F(s21_array_test, max_size1) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(arr1.max_size(), arr2.max_size());
}

TEST_F(s21_array_test, max_size2) {
  s21::array<double, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<double, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(arr1.max_size(), arr2.max_size());
}

TEST_F(s21_array_test, swap1) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::array<int, 10> arr11;
  std::array<int, 10> arr22;
  arr1.swap(arr11);
  arr2.swap(arr22);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr11.size(), arr22.size());
  auto it1 = arr11.begin();
  for (auto it2 = arr22.begin(); it2 != arr22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST_F(s21_array_test, swap2) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::array<int, 10> arr11 = {389, 3829, 111, 189, 11};
  std::array<int, 10> arr22 = {389, 3829, 111, 189, 11};
  arr1.swap(arr11);
  arr2.swap(arr22);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr11.size(), arr22.size());
  auto it1 = arr11.begin();
  for (auto it2 = arr22.begin(); it2 != arr22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST_F(s21_array_test, swap3) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::array<int, 10> arr11;
  std::array<int, 10> arr22;
  arr1.swap(arr11);
  arr2.swap(arr22);
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_EQ(arr11.size(), arr22.size());
  auto it1 = arr11.begin();
  for (auto it2 = arr22.begin(); it2 != arr22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST_F(s21_array_test, fill) {
  s21::array<int, 10> arr1;
  std::array<int, 10> arr2;
  arr1.fill(225);
  arr2.fill(225);
  EXPECT_EQ(arr1.size(), arr2.size());
  auto it1 = arr1.begin();
  for (auto it2 = arr2.begin(); it2 != arr2.end(); ++it2) EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(arr1.size(), arr2.size());
}

TEST_F(s21_array_test, iter1) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it1 = arr1.begin();
  auto it2 = arr2.begin();
  for (int i = 0; i < 4; i++) ++it1, ++it2;
  EXPECT_EQ(*it1, *it2);
}

TEST_F(s21_array_test, iter2) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::array<int, 10> arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it1 = arr1.end();
  auto it2 = arr2.end();
  for (int i = 0; i < 3; i++) --it1, --it2;
  EXPECT_EQ(*it1, *it2);
}

TEST_F(s21_array_test, iter3) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it1 = arr1.end();
  auto it2 = arr1.end();
  EXPECT_EQ(it1 == it2, true);
}

TEST_F(s21_array_test, iter4) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it1 = arr1.end();
  auto it2 = arr1.end();
  EXPECT_EQ(it1 != it2, false);
}

TEST_F(s21_array_test, iter5) {
  s21::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it1 = arr1.end();
  auto it2 = arr1.end();
  ++it2;
  EXPECT_EQ(it1 == it2, false);
}
