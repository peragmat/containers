#include <gtest/gtest.h>

#include "include/vector_suit.h"

TEST_F(s21_vector_test, default_constructor) {
  s21::vector<int> v;
  std::vector<int> v_lib;
  EXPECT_EQ(v_lib.size(), v.size());
  EXPECT_EQ(v_lib.empty(), v.empty());
  EXPECT_ANY_THROW(v.at(0));
  EXPECT_ANY_THROW(v.front());
  EXPECT_EQ(v.capacity(), v_lib.capacity());

  v.reserve(10);
  v_lib.reserve(10);
  EXPECT_EQ(v.capacity(), v_lib.capacity());
  v.reserve(1), v_lib.reserve(1);
  EXPECT_EQ(v.capacity(), v_lib.capacity());
  v.shrink_to_fit();
  v_lib.shrink_to_fit();
  EXPECT_EQ(v.capacity(), v_lib.capacity());
}

TEST_F(s21_vector_test, operator_one) {
  s21::vector<int> a;
  s21::vector<int> b{1, 2, 3, 4, 5, 6};
  a = b;
  s21::vector<int> c(std::move(b));
  s21::vector<int> d(c);
  EXPECT_EQ(a.size(), c.size());
  EXPECT_EQ(d.size(), a.size());
}

TEST_F(s21_vector_test, count) {
  s21::vector<double> v(10);
  std::vector<double> v_lib(10);
  EXPECT_EQ(v.empty(), false);
  EXPECT_EQ(v.empty(), v_lib.empty());
  EXPECT_EQ(v.size(), v_lib.size());
  EXPECT_EQ(v.capacity(), v_lib.capacity());
  v.push_back(1);
  v_lib.push_back(1);
  EXPECT_EQ(v.empty(), false);
  EXPECT_EQ(v.empty(), v_lib.empty());
  EXPECT_EQ(v.size(), v_lib.size());
  EXPECT_EQ(v.capacity(), v_lib.capacity());
  v.pop_back();
  v_lib.pop_back();
  v.pop_back();
  v_lib.pop_back();
  v.pop_back();
  v_lib.pop_back();
  v.pop_back();
  v_lib.pop_back();
  v.pop_back();
  v_lib.pop_back();
  EXPECT_EQ(v.empty(), false);
  EXPECT_EQ(v.empty(), v_lib.empty());
  EXPECT_EQ(v.size(), v_lib.size());
  EXPECT_EQ(v.capacity(), v_lib.capacity());
}

TEST_F(s21_vector_test, one_value) {
  s21::vector<int> v;
  std::vector<int> v_lib;
  EXPECT_ANY_THROW(v.at(1));

  v.push_back(6);
  v_lib.push_back(6);
  EXPECT_EQ(v.at(0), v_lib.at(0));
  EXPECT_EQ(v[0], v_lib[0]);

  EXPECT_EQ(v.front(), v_lib.front());
  EXPECT_EQ(v.back(), v_lib.back());
  EXPECT_EQ(v.empty(), v_lib.empty());
  EXPECT_EQ(v.max_size(), v_lib.max_size());
}

TEST_F(s21_vector_test, clear) {
  s21::vector<int> v{1, 2, 3};
  std::vector<int> v_lib{1, 2, 3};
  EXPECT_EQ(v.capacity(), v_lib.capacity());
  EXPECT_EQ(v.empty(), v_lib.empty());
  EXPECT_EQ(v.size(), v_lib.size());
  EXPECT_EQ(v[0], v_lib[0]);
  EXPECT_EQ(v[1], v_lib[1]);
  EXPECT_EQ(v[2], v_lib[2]);
  EXPECT_EQ(v.front(), v_lib.front());
  EXPECT_EQ(v.back(), v_lib.back());

  v.clear();
  v_lib.clear();
  EXPECT_EQ(v_lib.capacity(), v.capacity());
  EXPECT_EQ(v_lib.size(), v.size());

  v.insert(v.begin(), 7);
  v_lib.insert(v_lib.begin(), 7);
  EXPECT_EQ(v[0], v_lib[0]);
  EXPECT_EQ(v.capacity(), v_lib.capacity());
  EXPECT_EQ(v.size(), v_lib.size());

  s21::vector<std::string> str{"home", "big", "hello"};
  std::vector<std::string> lib_str{"home", "big", "hello"};
  str.clear();
  lib_str.clear();
  EXPECT_EQ(str.size(), lib_str.size());
  EXPECT_EQ(str.capacity(), lib_str.capacity());

  str.insert(str.end(), "little");
  lib_str.insert(lib_str.end(), "little");
  EXPECT_EQ(str.capacity(), lib_str.capacity());
  EXPECT_EQ(str.size(), lib_str.size());
  EXPECT_EQ(*(str.data()), "little");
  EXPECT_EQ(*(lib_str.data()), "little");
}

TEST_F(s21_vector_test, insert) {
  s21::vector<int> v{1, 2, 3, 5, 10, 12, 15};
  std::vector<int> v_lib{1, 2, 3, 5, 10, 12, 15};
  v.insert(v.begin(), 80);
  v_lib.insert(v_lib.begin(), 80);
  EXPECT_EQ(v.size(), v_lib.size());
  EXPECT_EQ(v.capacity(), v_lib.capacity());
  EXPECT_EQ(v.front(), v_lib.front());
  EXPECT_EQ(v[3], v_lib[3]);
  EXPECT_EQ(v[0], 80);
  v_lib.insert(v_lib.end(), 23);
  v.insert(v.end(), 23);
  EXPECT_EQ(v.back(), v_lib.back());
  EXPECT_EQ(v.size(), v_lib.size());
  EXPECT_EQ(v.capacity(), v_lib.capacity());
  EXPECT_EQ(*(v.begin() + 5), 10);
  v_lib.insert(v_lib.begin() + 5, 12);
  v.insert(v.begin() + 5, 12);
  auto i = v.begin();
  auto j = v_lib.begin();

  for (; i != v.end() && j != v_lib.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
}

TEST_F(s21_vector_test, throws) {
  s21::vector<int> v;
  EXPECT_ANY_THROW(v.back());
  EXPECT_ANY_THROW(v.data());
}

TEST_F(s21_vector_test, erase) {
  s21::vector<int> v{1, 2, 3, 5, 10, 12, 15};
  std::vector<int> v_lib{1, 2, 3, 5, 10, 12, 15};
  EXPECT_EQ(v.size(), v_lib.size());
  EXPECT_EQ(v.capacity(), v_lib.capacity());
  v.erase(v.begin());
  v_lib.erase(v_lib.begin());
  EXPECT_EQ(v.front(), v_lib.front());

  EXPECT_EQ(v.back(), v_lib.back());
  EXPECT_EQ(v.size(), v_lib.size());
  EXPECT_EQ(v[3], v_lib[3]);
  EXPECT_EQ(v[0], v_lib[0]);

  auto i = v.begin();
  auto j = v_lib.begin();

  for (; i != v.end() && j != v_lib.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
  s21::vector<std::string> str{"home", "big", "hello"};
  std::vector<std::string> lib_str{"home", "big", "hello"};
  str.erase(str.end());
  lib_str.erase(lib_str.end());

  auto i1 = str.begin();
  auto j1 = lib_str.begin();

  for (; i1 != str.end() && j1 != lib_str.end(); i1++, j1++) {
    EXPECT_EQ(*i1, *j1);
  }
  for (; i1 != str.end() && j1 != lib_str.end(); i1++, j1++) {
    str.erase(i1);
    lib_str.erase(j1);
  }
  EXPECT_EQ(str.size(), lib_str.size());
  EXPECT_EQ(str.capacity(), lib_str.capacity());
}

TEST_F(s21_vector_test, push_back) {
  s21::vector<int> v;
  std::vector<int> v_lib;
  v.push_back(1);
  v_lib.push_back(1);
  EXPECT_EQ(v[0], v_lib[0]);
  EXPECT_EQ(v.size(), v_lib.size());
  EXPECT_EQ(v.capacity(), v_lib.capacity());
  v.push_back(22);
  v_lib.push_back(22);
  EXPECT_EQ(v[1], v_lib[1]);
  EXPECT_EQ(v.size(), v_lib.size());
  EXPECT_EQ(v.capacity(), v_lib.capacity());
  v.push_back(3);
  v_lib.push_back(3);
  v.push_back(3);
  v_lib.push_back(3);
  v.push_back(3);
  v_lib.push_back(3);
  v.push_back(3);
  v_lib.push_back(3);
  v.push_back(3);
  v_lib.push_back(3);
  v.push_back(3);
  v_lib.push_back(3);
  v.push_back(3);
  v_lib.push_back(3);
  v.push_back(1);
  v_lib.push_back(1);
  v.push_back(0);
  v_lib.push_back(0);
  auto i = v.begin();
  auto j = v_lib.begin();

  for (; i != v.end() && j != v_lib.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
  s21::vector<std::string> str{"home", "big", "hello"};
  std::vector<std::string> lib_str{"home", "big", "hello"};
  str.push_back("hey");
  lib_str.push_back("hey");
  EXPECT_EQ(str[3], lib_str[3]);
  EXPECT_EQ(str.capacity(), lib_str.capacity());
  EXPECT_EQ(str.size(), lib_str.size());
}

TEST_F(s21_vector_test, pop_back) {
  s21::vector<int> v;
  std::vector<int> v_lib;
  v.pop_back();
  EXPECT_EQ(v.capacity(), v_lib.capacity());
  EXPECT_EQ(v.size(), v_lib.size());
  for (int i = 0; i < 20; i++) {
    v.push_back(i);
    v_lib.push_back(i);
  }
  auto i = v.begin();
  auto j = v_lib.begin();
  for (; i != v.end() && j != v_lib.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
  v.pop_back();
  v_lib.pop_back();
  v.pop_back();
  v_lib.pop_back();
  v.pop_back();
  v_lib.pop_back();
  v.pop_back();
  v_lib.pop_back();
  auto i1 = v.begin();
  auto j1 = v_lib.begin();
  for (; i1 != v.end() && j1 != v_lib.end(); i1++, j1++) {
    EXPECT_EQ(*i1, *j1);
  }
  EXPECT_EQ(v.empty(), v_lib.empty());
}

TEST_F(s21_vector_test, emplace_back) {
  s21::vector<int> a;
  std::vector<int> b;

  a.insert_many_back(1);
  a.insert_many_back(1);
  a.insert_many_back(2);
  a.insert_many_back(3);
  a.insert_many_back(4);
  a.insert_many_back(5);

  b.emplace_back(1);
  b.emplace_back(1);
  b.emplace_back(2);
  b.emplace_back(3);
  b.emplace_back(4);
  b.emplace_back(5);

  auto j = b.begin();
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(*i, *j);
    j++;
  }
}

TEST_F(s21_vector_test, emplace_back2) {
  s21::vector<int> a;
  std::vector<int> b;

  a.insert_many_back(1, 1, 2, 3, 4, 5);
  b.emplace_back(1);
  b.emplace_back(1);
  b.emplace_back(2);
  b.emplace_back(3);
  b.emplace_back(4);
  b.emplace_back(5);
  EXPECT_EQ(a.size(), b.size());
  auto j = b.begin();
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(*i, *j);
    j++;
  }
}

TEST_F(s21_vector_test, emplace_back3) {
  s21::vector<int> a(0);
  std::vector<int> b(0);

  a.insert_many_back(1, 1, 2, 3, 4, 5);
  b.emplace_back(1);
  b.emplace_back(1);
  b.emplace_back(2);
  b.emplace_back(3);
  b.emplace_back(4);
  b.emplace_back(5);

  EXPECT_EQ(a.size(), b.size());
  auto j = b.begin();
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(*i, *j);
    j++;
  }
}

TEST_F(s21_vector_test, emplace_back4) {
  s21::vector<int> a{1, 2, 3, 4, 5, 6, 6};
  std::vector<int> b{1, 2, 3, 4, 5, 6, 6};

  a.insert_many_back(1, 1, 2, 3, 4, 5);
  b.emplace_back(1);
  b.emplace_back(1);
  b.emplace_back(2);
  b.emplace_back(3);
  b.emplace_back(4);
  b.emplace_back(5);

  EXPECT_EQ(a.size(), b.size());
  auto j = b.begin();
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(*i, *j);
    j++;
  }
}

TEST_F(s21_vector_test, emplace) {
  s21::vector<int> a;
  std::vector<int> b;
  a.insert_many(a.cbegin(), 1, 1, 2, 3, 4, 5);

  b.emplace(b.cbegin(), 1);
  b.emplace(b.cbegin(), 1);
  b.emplace(b.cbegin(), 2);
  b.emplace(b.cbegin(), 3);
  b.emplace(b.cbegin(), 4);
  b.emplace(b.cbegin(), 5);

  EXPECT_EQ(a.size(), b.size());
  auto j = b.begin();
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(*i, *j);
    j++;
  }
}

TEST_F(s21_vector_test, emplace1) {
  s21::vector<int> a;
  std::vector<int> b;
  a.insert_many(a.cbegin(), 1);
  a.insert_many(a.cbegin(), 1);
  a.insert_many(a.cbegin(), 2);
  a.insert_many(a.cbegin(), 3);
  a.insert_many(a.cbegin(), 4);
  a.insert_many(a.cbegin(), 5);
  b.emplace(b.cbegin(), 1);
  b.emplace(b.cbegin(), 1);
  b.emplace(b.cbegin(), 2);
  b.emplace(b.cbegin(), 3);
  b.emplace(b.cbegin(), 4);
  b.emplace(b.cbegin(), 5);

  EXPECT_EQ(a.size(), b.size());
  auto j = b.begin();
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(*i, *j);
    j++;
  }
}

TEST_F(s21_vector_test, emplace2) {
  s21::vector<int> a(0);
  std::vector<int> b(0);
  a.insert_many(a.cbegin(), 1, 1, 2, 3, 4, 5);

  b.emplace(b.cbegin(), 1);
  b.emplace(b.cbegin(), 1);
  b.emplace(b.cbegin(), 2);
  b.emplace(b.cbegin(), 3);
  b.emplace(b.cbegin(), 4);
  b.emplace(b.cbegin(), 5);

  EXPECT_EQ(a.size(), b.size());
  auto j = b.begin();
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(*i, *j);
    j++;
  }
}

TEST_F(s21_vector_test, emplace3) {
  s21::vector<int> a{1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<int> b{1, 2, 3, 4, 5, 6, 7, 8};
  a.insert_many(a.cbegin(), 1, 1, 2, 3, 4, 5);

  b.emplace(b.cbegin(), 1);
  b.emplace(b.cbegin(), 1);
  b.emplace(b.cbegin(), 2);
  b.emplace(b.cbegin(), 3);
  b.emplace(b.cbegin(), 4);
  b.emplace(b.cbegin(), 5);

  EXPECT_EQ(a.size(), b.size());
  auto j = b.begin();
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(*i, *j);
    j++;
  }
}

TEST_F(s21_vector_test, swap) {
  s21::vector<int> v{1, 3, 5};
  std::vector<int> v_lib{1, 3, 5};
  s21::vector<int> v1{12, 4, 6};
  std::vector<int> v_lib1{12, 4, 6};
  v.swap(v1);
  v_lib.swap(v_lib1);
  auto i = v.cbegin();
  auto j = v_lib.cbegin();
  for (; i != v.cend() && j != v_lib.cend(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
  auto i1 = v1.begin();
  auto j1 = v_lib1.begin();
  for (; i1 != v1.end() && j1 != v_lib1.end(); i1++, j1++) {
    EXPECT_EQ(*i1, *j1);
  }
}
