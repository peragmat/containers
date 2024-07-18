#include "../test.h"

namespace {
TEST(Map, Constructor_Default) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(Map, Constructor_Initializer_list) {
  s21::map<int, std::string> s21_map = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  std::map<int, std::string> std_map = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(Map, Modifier_Insert) {
  s21::map<char, int> s21_map_1 = {{'b', 228}, {'c', 1337}};
  s21::map<char, int> s21_map_2 = {
      {'b', 228},
      {'c', 1337},
      {'d', 322},
      {'a', 5},
  };

  EXPECT_EQ(s21_map_1.insert('d', 322).second, true);
  EXPECT_EQ(s21_map_1.insert('d', 14).second, false);

  std::pair<char, int> pair1('a', 5);
  std::pair<char, int> pair2('a', 28);

  EXPECT_EQ(s21_map_1.insert(pair1).second, true);
  EXPECT_EQ(s21_map_1.insert(pair2).second, false);

  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_2.size());
}

TEST(Map, Rehash_And_Insert_In_Collision) {
  s21::map<std::string, int> s21_map;
  s21_map.insert("asd", 0);
  s21_map.insert("asa", 1);
  s21_map.insert("asf", 2);
  s21_map.insert("asg", 3);
  s21_map.insert("ash", 4);
  s21_map.insert("aqw", 5);
  s21_map.insert("fgh", 6);
  s21_map.insert("ghf", 7);
  s21_map.insert("dghfg", 8);
  s21_map.insert("dghfdsg", 9);
  s21_map.insert("dghfgfsadfsd", 10);
  s21_map.insert("dghfgfsadfsdasd", 11);
  s21_map.insert("dghfgfsadfsasdasdd", 12);
  s21_map.insert("dghfgfsadfsdasdasd", 13);
  s21_map.insert("dghfgfdsasadfdsasasdsadsad", 14);
  s21_map.insert("dghdsafgfsadfdsasasdsadsad", 15);
  s21_map.insert("ådsdghfgfsadfdsasasdsadsad", 16);
  s21_map.insert("dghfgfsadfdsasasdsaddsasad", 17);
  s21_map.insert("dghfgfsadfdsasassadadsadsad", 18);
  s21_map.insert("dghfgfsadfdsasdasasdsadsad", 19);
  s21_map.insert("dghasdaasdfgfsadfsasdsadsad", 20);
  s21_map.insert("asddghfgfsadfsasaß∂asdsadsad", 21);
  s21_map.insert("dghfgfsadfasdsasdsadsad", 22);
  s21_map.insert("dghfgfsadfsasdsadsad", 23);
  s21_map.insert("dghfgfsasdadfsasdsadsad", 24);
  s21_map.insert("asdsadadghfgfsadfsasdsadsad", 25);
  std::unordered_map<std::string, int> std_map;
  std_map.insert(std::pair<std::string, int>("asd", 0));
  std_map.insert(std::pair<std::string, int>("asa", 1));
  std_map.insert(std::pair<std::string, int>("asf", 2));
  std_map.insert(std::pair<std::string, int>("asg", 3));
  std_map.insert(std::pair<std::string, int>("ash", 4));
  std_map.insert(std::pair<std::string, int>("aqw", 5));
  std_map.insert(std::pair<std::string, int>("fgh", 6));
  std_map.insert(std::pair<std::string, int>("ghf", 7));
  std_map.insert(std::pair<std::string, int>("dghfg", 8));
  std_map.insert(std::pair<std::string, int>("dghfdsg", 9));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsd", 10));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsdasd", 11));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsasdasdd", 12));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsdasdasd", 13));
  std_map.insert(std::pair<std::string, int>("dghfgfdsasadfdsasasdsadsad",
  14)); std_map.insert(std::pair<std::string,
  int>("dghdsafgfsadfdsasasdsadsad", 15));
  std_map.insert(std::pair<std::string, int>("ådsdghfgfsadfdsasasdsadsad",
  16)); std_map.insert(std::pair<std::string,
  int>("dghfgfsadfdsasasdsaddsasad", 17)); std_map.insert(
      std::pair<std::string, int>("dghfgfsadfdsasassadadsadsad", 18));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfdsasdasasdsadsad",
  19)); std_map.insert(
      std::pair<std::string, int>("dghasdaasdfgfsadfsasdsadsad", 20));
  std_map.insert(
      std::pair<std::string, int>("asddghfgfsadfsasaß∂asdsadsad", 21));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfasdsasdsadsad", 22));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsasdsadsad", 23));
  std_map.insert(std::pair<std::string, int>("dghfgfsasdadfsasdsadsad", 24));
  std_map.insert(
      std::pair<std::string, int>("asdsadadghfgfsadfsasdsadsad", 25));
  for (auto i : std_map) {
    EXPECT_EQ(i.second, s21_map[i.first]);
  }
  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(Map, Modifier_Get_Value) {
  s21::map<std::string, int> m;
  m["123"] = 5;
  EXPECT_EQ(5, m["123"]);
}

TEST(Map, Modifier_Insert_or_assign) {
  s21::map<char, int> s21_map_1 = {{'b', 228}, {'c', 1337}};
  s21::map<char, int> s21_map_2 = {
      {'b', 228},
      {'c', 1337},
      {'d', 14},
      {'a', 28},
  };

  EXPECT_EQ(s21_map_1.insert_or_assign('d', 322).second, true);
  EXPECT_EQ(s21_map_1.insert_or_assign('d', 14).second, false);

  EXPECT_EQ(s21_map_1.insert_or_assign('a', 5).second, true);
  EXPECT_EQ(s21_map_1.insert_or_assign('a', 28).second, false);

  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_2.size());
}

TEST(Map, Modifier_Erase_1) {
  s21::map<int, std::string> s21_map_1 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  s21::map<int, std::string> s21_map_2 = {
      {1, "aboba"}, {3, "amogus"}, {4, "abobus"}};
  auto it = s21_map_1.begin();
  ++it;
  s21_map_1.erase(it);
  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_2.size());
}

TEST(Map, Modifier_Swap) {
  s21::map<int, std::string> s21_map_1 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  s21::map<int, std::string> s21_map_2 = {
      {10, "shtirlits"}, {12, "vovochka"}, {13, "poruchik"}, {14,
      "chepaev"}};
  s21::map<int, std::string> s21_map_3 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  s21::map<int, std::string> s21_map_4 = {
      {10, "shtirlits"}, {12, "vovochka"}, {13, "poruchik"}, {14,
      "chepaev"}};

  s21_map_1.swap(s21_map_2);
  auto it1 = s21_map_1.begin();
  auto it2 = s21_map_2.begin();
  auto it3 = s21_map_3.begin();
  auto it4 = s21_map_4.begin();
  while (it1 != s21_map_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  while (it2 != s21_map_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
  EXPECT_EQ(s21_map_1.size(), s21_map_4.size());
  EXPECT_EQ(s21_map_2.size(), s21_map_3.size());
}

}  // namespace

namespace {
TEST(Set, Constructor_Default) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Set, Constructor_Initializer_list) {
  s21::set<int> s21_set = {1, 2, 3, 4};
  std::set<int> std_set = {1, 2, 3, 4};
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Set, Constructor_Move) {
  s21::set<char> s21_set_1 = {'a', 'b', 'c', 'd'};
  std::set<char> std_set_1 = {'a', 'b', 'c', 'd'};
  s21::set<char> s21_set_2 = std::move(s21_set_1);
  std::set<char> std_set_2 = std::move(std_set_1);

  EXPECT_EQ(s21_set_2.size(), std_set_2.size());
  EXPECT_EQ(s21_set_1.size(), std_set_1.size());
  EXPECT_EQ(s21_set_1.empty(), std_set_1.empty());
  auto it1 = s21_set_2.begin();
  auto it2 = std_set_2.begin();
  while (it1 != s21_set_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Set, Modifier_Insert_1) {
  s21::set<char> s21_set_1 = {'a', 'c', 'd'};
  s21::set<char> s21_set_2 = {'a', 'c', 'd', 'b'};

  auto it = s21_set_1.begin();
  ++it;
  s21_set_1.insert('b');
  s21_set_1.insert('a');
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_set_1.size(), s21_set_2.size());
}

TEST(Set, Modifier_Insert_2) {
  s21::set<char> s21_set;

  s21_set.insert('b');
  s21_set.insert('b');
  s21_set.insert('b');

  EXPECT_EQ(s21_set.size(), size_t(1));
}

TEST(Set, Modifier_Insert_3) {
  s21::set<float> s21_set;
  std::set<float> std_set;

  s21_set.insert(0.0000000000000000000000000000000000000000001);
  s21_set.insert(0.000000000000000000000000000000000000000000099);
  std_set.insert(0.0000000000000000000000000000000000000000001);
  std_set.insert(0.000000000000000000000000000000000000000000099);

  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(Set, Modifier_Erase) {
  s21::set<char> s21_set_1 = {'a', 'c', 'd'};
  s21::set<char> s21_set_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_set_2.begin();
  ++it;
  s21_set_2.erase(it);
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_set_1.size(), s21_set_2.size());
}

TEST(Set, Modifier_Swap) {
  s21::set<char> s21_set_1 = {'a', 'b', 'o', 'b', 'a'};
  s21::set<char> s21_set_2 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21::set<char> s21_set_3 = {'a', 'b', 'o', 'b', 'a'};
  s21::set<char> s21_set_4 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21_set_1.swap(s21_set_2);
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  auto it3 = s21_set_3.begin();
  auto it4 = s21_set_4.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  while (it2 != s21_set_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
  EXPECT_EQ(s21_set_1.size(), s21_set_4.size());
  EXPECT_EQ(s21_set_2.size(), s21_set_3.size());
}

TEST(Set, Lookup_Contains) {
  s21::set<int> s21_set;
  s21_set.insert(1);
  s21_set.insert(2);
  s21_set.insert(3);
  s21_set.insert(4);
  EXPECT_EQ(s21_set.contains(1), true);
  EXPECT_EQ(s21_set.contains(2), true);
  EXPECT_EQ(s21_set.contains(3), true);
  EXPECT_EQ(s21_set.contains(4), true);
  EXPECT_EQ(s21_set.contains(7), false);
  EXPECT_EQ(s21_set.contains(-2), false);
  EXPECT_EQ(s21_set.contains(0), false);
}

TEST(Set, Lookup_Find) {
  s21::set<int> s21_set;
  s21_set.insert(1);
  s21_set.insert(2);
  s21_set.insert(3);
  s21_set.insert(4);
  auto it_end = s21_set.end();
  EXPECT_EQ(*(s21_set.find(1)), 1);
  EXPECT_EQ(*(s21_set.find(3)), 3);
  EXPECT_EQ(*(s21_set.find(4)), 4);
  EXPECT_EQ(*(s21_set.find(2)), 2);
  EXPECT_EQ(s21_set.find(-4), it_end);
  EXPECT_EQ(s21_set.find(0), it_end);
  EXPECT_EQ(s21_set.find(120), it_end);
}

TEST(Set, Rehash_And_Insert_In_Collision) {
  s21::set<std::string> s21_set;
  std::unordered_set<std::string> std_set;
  s21_set.insert("asd");
  s21_set.insert("asa");
  s21_set.insert("asf");
  s21_set.insert("asg");
  s21_set.insert("ash");
  s21_set.insert("aqw");
  s21_set.insert("fgh");
  s21_set.insert("ghf");
  s21_set.insert("dghfg");
  s21_set.insert("dghfdsg");
  s21_set.insert("dghfgfsadfsd");
  s21_set.insert("dghfgfsadfsdasd");
  s21_set.insert("dghfgfsadfsasdasdd");
  s21_set.insert("dghfgfsadfsdasdasd");
  s21_set.insert("dghfgfdsasadfdsasasdsadsad");
  s21_set.insert("dghdsafgfsadfdsasasdsadsad");
  s21_set.insert("ådsdghfgfsadfdsasasdsadsad");
  s21_set.insert("dghfgfsadfdsasasdsaddsasad");
  s21_set.insert("dghfgfsadfdsasassadadsadsad");
  s21_set.insert("dghfgfsadfdsasdasasdsadsad");
  s21_set.insert("dghasdaasdfgfsadfsasdsadsad");
  s21_set.insert("asddghfgfsadfsasaß∂asdsadsad");
  s21_set.insert("dghfgfsadfasdsasdsadsad");
  s21_set.insert("dghfgfsadfsasdsadsad");
  s21_set.insert("dghfgfsasdadfsasdsadsad");
  s21_set.insert("asdsadadghfgfsadfsasdsadsad");
  std_set.insert("asd");
  std_set.insert("asa");
  std_set.insert("asf");
  std_set.insert("asg");
  std_set.insert("ash");
  std_set.insert("aqw");
  std_set.insert("fgh");
  std_set.insert("ghf");
  std_set.insert("dghfg");
  std_set.insert("dghfdsg");
  std_set.insert("dghfgfsadfsd");
  std_set.insert("dghfgfsadfsdasd");
  std_set.insert("dghfgfsadfsasdasdd");
  std_set.insert("dghfgfsadfsdasdasd");
  std_set.insert("dghfgfdsasadfdsasasdsadsad");
  std_set.insert("dghdsafgfsadfdsasasdsadsad");
  std_set.insert("ådsdghfgfsadfdsasasdsadsad");
  std_set.insert("dghfgfsadfdsasasdsaddsasad");
  std_set.insert("dghfgfsadfdsasassadadsadsad");
  std_set.insert("dghfgfsadfdsasdasasdsadsad");
  std_set.insert("dghasdaasdfgfsadfsasdsadsad");
  std_set.insert("asddghfgfsadfsasaß∂asdsadsad");
  std_set.insert("dghfgfsadfasdsasdsadsad");
  std_set.insert("dghfgfsadfsasdsadsad");
  std_set.insert("dghfgfsasdadfsasdsadsad");
  std_set.insert("asdsadadghfgfsadfsasdsadsad");
  for (auto i : std_set) {
    EXPECT_TRUE(s21_set.find(i) != s21_set.end());
  }
  EXPECT_EQ(s21_set.size(), std_set.size());
}

}  // namespace

namespace {
TEST(Multiset, Constructor_Default) {
  s21::multiset<int> s21_multiset;
  std::multiset<int> std_multiset;
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
}

TEST(Multiset, Constructor_Initializer_list) {
  s21::multiset<int> s21_multiset = {1, 2, 3, 4};
  std::multiset<int> std_multiset = {1, 2, 3, 4};
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
}

TEST(Multiset, Constructor_Move) {
  s21::multiset<char> s21_multiset_1 = {'a', 'b', 'c', 'd'};
  std::multiset<char> std_multiset_1 = {'a', 'b', 'c', 'd'};
  s21::multiset<char> s21_multiset_2 = std::move(s21_multiset_1);
  std::multiset<char> std_multiset_2 = std::move(std_multiset_1);

  EXPECT_EQ(s21_multiset_2.size(), std_multiset_2.size());
  EXPECT_EQ(s21_multiset_1.size(), std_multiset_1.size());
  EXPECT_EQ(s21_multiset_1.empty(), std_multiset_1.empty());
  auto it1 = s21_multiset_2.begin();
  auto it2 = std_multiset_2.begin();
  while (it1 != s21_multiset_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Multiset, Modifier_Insert_1) {
  s21::multiset<char> s21_multiset_1 = {'a', 'c', 'd'};
  s21::multiset<char> s21_multiset_2 = {'a', 'c', 'd', 'b'};

  auto it = s21_multiset_1.begin();
  ++it;
  s21_multiset_1.insert('b');
  s21_multiset_1.insert('a');
  auto it1 = s21_multiset_1.begin();
  auto it2 = s21_multiset_2.begin();
  while (it1 != s21_multiset_1.end()) {
    ++it1, ++it2;
  }
  EXPECT_NE(s21_multiset_1.size(), s21_multiset_2.size());
}

TEST(Multiset, Modifier_Insert_2) {
  s21::multiset<char> s21_multiset;

  s21_multiset.insert('b');
  s21_multiset.insert('b');
  s21_multiset.insert('b');

  EXPECT_EQ(s21_multiset.size(), size_t(3));
}

TEST(Multiset, Modifier_Insert_3) {
  s21::multiset<float> s21_multiset;
  std::multiset<float> std_multiset;

  s21_multiset.insert(0.0000000000000000000000000000000000000000001);
  s21_multiset.insert(0.000000000000000000000000000000000000000000099);
  std_multiset.insert(0.0000000000000000000000000000000000000000001);
  std_multiset.insert(0.000000000000000000000000000000000000000000099);

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
}

TEST(Multiset, Modifier_Erase) {
  s21::multiset<char> s21_multiset_1 = {'a', 'c', 'd'};
  s21::multiset<char> s21_multiset_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_multiset_2.begin();
  ++it;
  s21_multiset_2.erase(it);
  auto it1 = s21_multiset_1.begin();
  auto it2 = s21_multiset_2.begin();
  while (it1 != s21_multiset_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_multiset_1.size(), s21_multiset_2.size());
}

TEST(Multiset, Modifier_Swap) {
  s21::multiset<char> s21_multiset_1 = {'a', 'b', 'o', 'b', 'a'};
  s21::multiset<char> s21_multiset_2 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21::multiset<char> s21_multiset_3 = {'a', 'b', 'o', 'b', 'a'};
  s21::multiset<char> s21_multiset_4 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21_multiset_1.swap(s21_multiset_2);
  auto it1 = s21_multiset_1.begin();
  auto it2 = s21_multiset_2.begin();
  auto it3 = s21_multiset_3.begin();
  auto it4 = s21_multiset_4.begin();
  while (it1 != s21_multiset_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  while (it2 != s21_multiset_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
  EXPECT_EQ(s21_multiset_1.size(), s21_multiset_4.size());
  EXPECT_EQ(s21_multiset_2.size(), s21_multiset_3.size());
}

TEST(Multiset, Lookup_Contains) {
  s21::multiset<int> s21_multiset;
  s21_multiset.insert(1);
  s21_multiset.insert(2);
  s21_multiset.insert(3);
  s21_multiset.insert(4);
  EXPECT_EQ(s21_multiset.contains(1), true);
  EXPECT_EQ(s21_multiset.contains(2), true);
  EXPECT_EQ(s21_multiset.contains(3), true);
  EXPECT_EQ(s21_multiset.contains(4), true);
  EXPECT_EQ(s21_multiset.contains(7), false);
  EXPECT_EQ(s21_multiset.contains(-2), false);
  EXPECT_EQ(s21_multiset.contains(0), false);
}

TEST(Multiset, Lookup_Find) {
  s21::multiset<int> s21_multiset;
  s21_multiset.insert(1);
  s21_multiset.insert(2);
  s21_multiset.insert(3);
  s21_multiset.insert(4);
  auto it_end = s21_multiset.end();
  EXPECT_EQ(*(s21_multiset.find(1)), 1);
  EXPECT_EQ(*(s21_multiset.find(3)), 3);
  EXPECT_EQ(*(s21_multiset.find(4)), 4);
  EXPECT_EQ(*(s21_multiset.find(2)), 2);
  EXPECT_EQ(s21_multiset.find(-4), it_end);
  EXPECT_EQ(s21_multiset.find(0), it_end);
  EXPECT_EQ(s21_multiset.find(120), it_end);
}

TEST(Multiset, Rehash_And_Insert_In_Collision) {
  s21::multiset<std::string> s21_multiset;
  std::unordered_set<std::string> std_multiset;
  s21_multiset.insert("asd");
  s21_multiset.insert("asa");
  s21_multiset.insert("asf");
  s21_multiset.insert("asg");
  s21_multiset.insert("ash");
  s21_multiset.insert("aqw");
  s21_multiset.insert("fgh");
  s21_multiset.insert("ghf");
  s21_multiset.insert("dghfg");
  s21_multiset.insert("dghfdsg");
  s21_multiset.insert("dghfgfsadfsd");
  s21_multiset.insert("dghfgfsadfsdasd");
  s21_multiset.insert("dghfgfsadfsasdasdd");
  s21_multiset.insert("dghfgfsadfsdasdasd");
  s21_multiset.insert("dghfgfdsasadfdsasasdsadsad");
  s21_multiset.insert("dghdsafgfsadfdsasasdsadsad");
  s21_multiset.insert("ådsdghfgfsadfdsasasdsadsad");
  s21_multiset.insert("dghfgfsadfdsasasdsaddsasad");
  s21_multiset.insert("dghfgfsadfdsasassadadsadsad");
  s21_multiset.insert("dghfgfsadfdsasdasasdsadsad");
  s21_multiset.insert("dghasdaasdfgfsadfsasdsadsad");
  s21_multiset.insert("asddghfgfsadfsasaß∂asdsadsad");
  s21_multiset.insert("dghfgfsadfasdsasdsadsad");
  s21_multiset.insert("dghfgfsadfsasdsadsad");
  s21_multiset.insert("dghfgfsasdadfsasdsadsad");
  s21_multiset.insert("asdsadadghfgfsadfsasdsadsad");
  std_multiset.insert("asd");
  std_multiset.insert("asa");
  std_multiset.insert("asf");
  std_multiset.insert("asg");
  std_multiset.insert("ash");
  std_multiset.insert("aqw");
  std_multiset.insert("fgh");
  std_multiset.insert("ghf");
  std_multiset.insert("dghfg");
  std_multiset.insert("dghfdsg");
  std_multiset.insert("dghfgfsadfsd");
  std_multiset.insert("dghfgfsadfsdasd");
  std_multiset.insert("dghfgfsadfsasdasdd");
  std_multiset.insert("dghfgfsadfsdasdasd");
  std_multiset.insert("dghfgfdsasadfdsasasdsadsad");
  std_multiset.insert("dghdsafgfsadfdsasasdsadsad");
  std_multiset.insert("ådsdghfgfsadfdsasasdsadsad");
  std_multiset.insert("dghfgfsadfdsasasdsaddsasad");
  std_multiset.insert("dghfgfsadfdsasassadadsadsad");
  std_multiset.insert("dghfgfsadfdsasdasasdsadsad");
  std_multiset.insert("dghasdaasdfgfsadfsasdsadsad");
  std_multiset.insert("asddghfgfsadfsasaß∂asdsadsad");
  std_multiset.insert("dghfgfsadfasdsasdsadsad");
  std_multiset.insert("dghfgfsadfsasdsadsad");
  std_multiset.insert("dghfgfsasdadfsasdsadsad");
  std_multiset.insert("asdsadadghfgfsadfsasdsadsad");
  for (auto i : std_multiset) {
    EXPECT_TRUE(s21_multiset.find(i) != s21_multiset.end());
  }
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
}

}  // namespace

TEST(Set, default_constructor) {
  s21::set<int> basic;
  basic.insert(5);
  basic.insert(20);
  basic.insert(2);
  int s[3] = {2, 5, 20};
  int *a = s;
  for (const int &item : basic) {
    EXPECT_EQ(item, *a++);
  }
}

TEST(Set, initializator_oper_constructor_int) {
  s21::set<int> basic = {6, 4, 2, 8, 0, -228};
  int s[6] = {-228, 0, 2, 4, 6, 8};
  int *a = s;
  for (const int &item : basic) {
    EXPECT_EQ(item, *a++);
  }
}

TEST(Set, initializator_constructor_int) {
  s21::set<int> basic{6, 4, 2, 8, 0, -228};
  int s[6] = {-228, 0, 2, 4, 6, 8};
  int *a = s;
  for (const int &item : basic) {
    EXPECT_EQ(item, *a++);
  }
}

TEST(Set, initializator_constructor_double) {
  s21::set<double> basic = {999, 6, 3, 2, 90, 0, -1};
  double s[7] = {-1, 0, 2, 3, 6, 90, 999};
  double *a = s;
  for (const double &item : basic) {
    EXPECT_DOUBLE_EQ(item, *a++);
  }
}

TEST(Set, initializator_constructor_char) {
  s21::set<char> basic = {'c', 'd', 'a', 'b'};
  char s[4] = {'a', 'b', 'c', 'd'};
  char *a = s;
  for (const char &item : basic) {
    EXPECT_TRUE(item == *a++);
  }
}

TEST(Set, copy_constructor_int) {
  s21::set<int> basic = {6, 4, 2, 8, 0, -228};
  s21::set<int> copy{basic};
  int s[6] = {-228, 0, 2, 4, 6, 8};
  int *a = s;
  for (const int &item : copy) {
    EXPECT_EQ(item, *a++);
  }
  EXPECT_EQ(basic.size(), 6);
  EXPECT_EQ(basic.size(), copy.size());
}

TEST(Set, move_constructor_int) {
  s21::set<int> basic = {6, 4, 2, 8, 0, -228};
  s21::set<int> move{std::move(basic)};
  int s[6] = {-228, 0, 2, 4, 6, 8};
  int *a = s;
  for (const int &item : move) {
    EXPECT_EQ(item, *a++);
  }
  EXPECT_EQ(basic.size(), 0);
  EXPECT_EQ(move.size(), 6);
}

TEST(Set, move_operator_int) {
  s21::set<int> basic = {6, 4, 2, 8, 0, -228};
  s21::set<int> move = std::move(basic);
  int s[6] = {-228, 0, 2, 4, 6, 8};
  int *a = s;
  for (const int &item : move) {
    EXPECT_EQ(item, *a++);
  }
  EXPECT_EQ(basic.size(), 0);
  EXPECT_EQ(move.size(), 6);
}

TEST(Set, iterator_begin_end) {
  s21::set<int> basic = {6, 4, 2, 8, 0, -228};
  auto iter = basic.begin();
  auto iter_end = basic.end();
  int s[6] = {-228, 0, 2, 4, 6, 8};
  int *a = s;
  while (iter != iter_end) {
    EXPECT_EQ(*iter++, *a++);
  }
  EXPECT_EQ(basic.size(), 6);
}

TEST(Set, empty_size) {
  s21::set<int> basic;
  EXPECT_TRUE(basic.empty());
  EXPECT_EQ(basic.size(), 0);
  basic.insert(4);
  EXPECT_EQ(basic.size(), 1);
  EXPECT_FALSE(basic.empty());
}

TEST(Set, empty_erase) {
  s21::set<int> basic;
  EXPECT_TRUE(basic.empty());
  basic.insert(4);
  EXPECT_FALSE(basic.empty());
  basic.erase(basic.find(4));
  EXPECT_TRUE(basic.empty());
}

TEST(Set, insert) {
  s21::set<int> basic;
  std::pair<s21::set<int>::iterator, bool> pair = basic.insert(5);
  EXPECT_EQ(*pair.first, 5);
  EXPECT_TRUE(pair.second);
  std::pair<s21::set<int>::iterator, bool> pair2 = basic.insert(5);
  EXPECT_EQ(*pair2.first, 5);
  EXPECT_FALSE(pair2.second);
  basic.insert(20);
  basic.insert(2);
  int s[3] = {2, 5, 20};
  int *a = s;
  for (const int &item : basic) {
    EXPECT_EQ(item, *a++);
  }
}

TEST(Set, empty_clear) {
  s21::set<int> basic;
  EXPECT_TRUE(basic.empty());
  basic.insert(4);
  EXPECT_FALSE(basic.empty());
  basic.clear();
  EXPECT_TRUE(basic.empty());
}

TEST(Set, size_clear) {
  s21::set<int> basic{1, 2, 3, 4, 5, 6};
  EXPECT_EQ(basic.size(), 6);
  basic.insert(4);
  basic.insert(7);
  EXPECT_EQ(basic.size(), 7);
  basic.clear();
  EXPECT_EQ(basic.size(), 0);
}

TEST(Set, swap_int) {
  s21::set<int> basic1{1, 2, 3};
  s21::set<int> basic2{1, 2, 3, 4};
  EXPECT_EQ(basic1.size(), 3);
  EXPECT_EQ(basic2.size(), 4);
  int s1[3] = {1, 2, 3};
  int s2[4] = {1, 2, 3, 4};
  int *a = s1;
  for (const int &item : basic1) {
    EXPECT_EQ(item, *a++);
  }
  a = s2;
  for (const int &item : basic2) {
    EXPECT_EQ(item, *a++);
  }
  basic1.swap(basic2);
  EXPECT_EQ(basic1.size(), 4);
  EXPECT_EQ(basic2.size(), 3);
  a = s1;
  for (const int &item : basic2) {
    EXPECT_EQ(item, *a++);
  }
  a = s2;
  for (const int &item : basic1) {
    EXPECT_EQ(item, *a++);
  }
}
TEST(Set, swap_double) {
  s21::set<double> basic1{78, 23, -9};
  s21::set<double> basic2{55, 22, -8, -0.5};
  EXPECT_EQ(basic1.size(), 3);
  EXPECT_EQ(basic2.size(), 4);
  double s1[3] = {-9, 23, 78};
  double s2[4] = {-8, -0.5, 22, 55};
  double *a = s1;
  for (const double &item : basic1) {
    EXPECT_DOUBLE_EQ(item, *a++);
  }
  a = s2;
  for (const double &item : basic2) {
    EXPECT_DOUBLE_EQ(item, *a++);
  }
  basic1.swap(basic2);
  EXPECT_EQ(basic1.size(), 4);
  EXPECT_EQ(basic2.size(), 3);
  a = s1;
  for (const double &item : basic2) {
    EXPECT_DOUBLE_EQ(item, *a++);
  }
  a = s2;
  for (const double &item : basic1) {
    EXPECT_DOUBLE_EQ(item, *a++);
  }
}

TEST(Set, merge_double) {
  s21::set<double> basic1{78, 23, -9, -8, -0.5};
  s21::set<double> basic2{55, 22, -8, -0.5};
  EXPECT_EQ(basic1.size(), 5);
  EXPECT_EQ(basic2.size(), 4);
  basic1.merge(basic2);
  double s1[7] = {-9, -8, -0.5, 22, 23, 55, 78};
  double *a = s1;
  for (const double &item : basic1) {
    EXPECT_DOUBLE_EQ(item, *a++);
  }
  EXPECT_EQ(basic1.size(), 7);
  EXPECT_EQ(basic2.size(), 2);
}

TEST(Set, merge_char) {
  s21::set<char> basic1{78, 23, -9, -8};
  s21::set<char> basic2{55, 22, -8, 0};
  EXPECT_EQ(basic1.size(), 4);
  EXPECT_EQ(basic2.size(), 4);
  basic1.merge(basic2);
  char s1[7] = {-9, -8, 0, 22, 23, 55, 78};
  char *a = s1;
  for (const char &item : basic1) {
    EXPECT_EQ(item, *a++);
  }
  EXPECT_EQ(basic1.size(), 7);
  EXPECT_EQ(basic2.size(), 1);
}

TEST(Set, iterator_find) {
  s21::set<double> basic1{78, 23, -9, 22, 22, 22, 23};
  EXPECT_EQ(basic1.size(), 4);
  auto iter_22 = basic1.find(22);
  EXPECT_DOUBLE_EQ(*iter_22, 22);
  EXPECT_DOUBLE_EQ(*++iter_22, 23);
  EXPECT_DOUBLE_EQ(*++iter_22, 78);
}

TEST(Set, iterator_find2) {
  s21::set<double> basic1{78, 7.75, -9, -999, -8, 0.5, 2.88};
  EXPECT_EQ(basic1.size(), 7);
  auto iter_22 = basic1.find(-9);
  EXPECT_DOUBLE_EQ(*iter_22, -9);
  EXPECT_DOUBLE_EQ(*++iter_22, -8);
  EXPECT_DOUBLE_EQ(*++iter_22, 0.5);
  EXPECT_DOUBLE_EQ(*++iter_22, 2.88);
  EXPECT_DOUBLE_EQ(*++iter_22, 7.75);
}

TEST(Set, contains_int) {
  s21::set<int> basic1{78, 7, -9, -999, -8, 0, 2};
  EXPECT_EQ(basic1.size(), 7);
  EXPECT_TRUE(basic1.contains(-9));
  EXPECT_TRUE(basic1.contains(-999));
  EXPECT_TRUE(basic1.contains(0));
  EXPECT_FALSE(basic1.contains(-33));
  EXPECT_FALSE(basic1.contains(77));
  EXPECT_FALSE(basic1.contains(-98));
}

TEST(Set, emplace_basic) {
  s21::set<int> basic;
  basic.insert_many(1, 3, 4, 4);
  EXPECT_TRUE(basic.contains(1));
  EXPECT_TRUE(basic.contains(3));
}

TEST(Multiset, default_constructor) {
  s21::multiset<int> basic;
  basic.insert(5);
  basic.insert(20);
  basic.insert(2);
  int s[3] = {2, 5, 20};
  int *a = s;
  for (const int &item : basic) {
    EXPECT_EQ(item, *a++);
  }
}

TEST(Multiset, initializator_oper_constructor_int) {
  s21::multiset<int> basic = {6, 4, 2, 8, 0, -228};
  int s[6] = {-228, 0, 2, 4, 6, 8};
  int *a = s;
  for (const int &item : basic) {
    EXPECT_EQ(item, *a++);
  }
}

TEST(Multiset, initializator_constructor_int) {
  s21::multiset<int> basic{6, 4, 2, 8, 0, -228};
  int s[6] = {-228, 0, 2, 4, 6, 8};
  int *a = s;
  for (const int &item : basic) {
    EXPECT_EQ(item, *a++);
  }
}

TEST(Multiset, initializator_constructor_double) {
  s21::multiset<double> basic = {999, 6, 3, 2, 90, 0, -1};
  double s[7] = {-1, 0, 2, 3, 6, 90, 999};
  double *a = s;
  for (const double &item : basic) {
    EXPECT_DOUBLE_EQ(item, *a++);
  }
}

TEST(Multiset, initializator_constructor_char) {
  s21::multiset<char> basic = {'c', 'd', 'a', 'b'};
  char s[4] = {'a', 'b', 'c', 'd'};
  char *a = s;
  for (const char &item : basic) {
    EXPECT_TRUE(item == *a++);
  }
}

TEST(Multiset, copy_constructor_int) {
  s21::multiset<int> basic = {6, 4, 2, 8, 0, -228};
  s21::multiset<int> copy{basic};
  int s[6] = {-228, 0, 2, 4, 6, 8};
  int *a = s;
  for (const int &item : copy) {
    EXPECT_EQ(item, *a++);
  }
  EXPECT_EQ(basic.size(), copy.size());
}

TEST(Multiset, move_constructor_int) {
  s21::multiset<int> basic = {6, 4, 2, 8, 0, -228};
  s21::multiset<int> move{std::move(basic)};
  int s[6] = {-228, 0, 2, 4, 6, 8};
  int *a = s;
  for (const int &item : move) {
    EXPECT_EQ(item, *a++);
  }
  EXPECT_EQ(basic.size(), 0);
  EXPECT_EQ(move.size(), 6);
}

TEST(Multiset, move_operator_int) {
  s21::multiset<int> basic = {6, 4, 2, 8, 0, -228};
  s21::multiset<int> move = std::move(basic);
  int s[6] = {-228, 0, 2, 4, 6, 8};
  int *a = s;
  for (const int &item : move) {
    EXPECT_EQ(item, *a++);
  }
  EXPECT_EQ(basic.size(), 0);
  EXPECT_EQ(move.size(), 6);
}

TEST(Multiset, iterator_begin_end) {
  s21::multiset<int> basic = {6, 4, 2, 8, 0, -228};
  auto iter = basic.begin();
  auto iter_end = basic.end();
  int s[6] = {-228, 0, 2, 4, 6, 8};
  int *a = s;
  while (iter != iter_end) {
    EXPECT_EQ(*iter++, *a++);
  }
  EXPECT_EQ(basic.size(), 6);
}

TEST(Multiset, empty_size) {
  s21::multiset<int> basic;
  EXPECT_TRUE(basic.empty());
  EXPECT_EQ(basic.size(), 0);
  basic.insert(4);
  EXPECT_EQ(basic.size(), 1);
  EXPECT_FALSE(basic.empty());
}

TEST(Multiset, empty_erase) {
  s21::multiset<int> basic;
  EXPECT_TRUE(basic.empty());
  basic.insert(4);
  EXPECT_FALSE(basic.empty());
  basic.erase(basic.find(4));
  EXPECT_TRUE(basic.empty());
}

TEST(Multiset, empty_clear) {
  s21::multiset<int> basic;
  EXPECT_TRUE(basic.empty());
  basic.insert(4);
  EXPECT_FALSE(basic.empty());
  basic.clear();
  EXPECT_TRUE(basic.empty());
}

TEST(Multiset, size_clear) {
  s21::multiset<int> basic{1, 2, 3, 4, 5, 6};
  EXPECT_EQ(basic.size(), 6);
  basic.insert(4);
  EXPECT_EQ(basic.size(), 7);
  basic.clear();
  EXPECT_EQ(basic.size(), 0);
}

TEST(Multiset, swap_int) {
  s21::multiset<int> basic1{1, 2, 3};
  s21::multiset<int> basic2{1, 2, 3, 4};
  EXPECT_EQ(basic1.size(), 3);
  EXPECT_EQ(basic2.size(), 4);
  int s1[3] = {1, 2, 3};
  int s2[4] = {1, 2, 3, 4};
  int *a = s1;
  for (const int &item : basic1) {
    EXPECT_EQ(item, *a++);
  }
  a = s2;
  for (const int &item : basic2) {
    EXPECT_EQ(item, *a++);
  }
  basic1.swap(basic2);
  EXPECT_EQ(basic1.size(), 4);
  EXPECT_EQ(basic2.size(), 3);
  a = s1;
  for (const int &item : basic2) {
    EXPECT_EQ(item, *a++);
  }
  a = s2;
  for (const int &item : basic1) {
    EXPECT_EQ(item, *a++);
  }
}
TEST(Multiset, swap_double) {
  s21::multiset<double> basic1{78, 23, -9};
  s21::multiset<double> basic2{55, 22, -8, -0.5};
  EXPECT_EQ(basic1.size(), 3);
  EXPECT_EQ(basic2.size(), 4);
  double s1[3] = {-9, 23, 78};
  double s2[4] = {-8, -0.5, 22, 55};
  double *a = s1;
  for (const double &item : basic1) {
    EXPECT_DOUBLE_EQ(item, *a++);
  }
  a = s2;
  for (const double &item : basic2) {
    EXPECT_DOUBLE_EQ(item, *a++);
  }
  basic1.swap(basic2);
  EXPECT_EQ(basic1.size(), 4);
  EXPECT_EQ(basic2.size(), 3);
  a = s1;
  for (const double &item : basic2) {
    EXPECT_DOUBLE_EQ(item, *a++);
  }
  a = s2;
  for (const double &item : basic1) {
    EXPECT_DOUBLE_EQ(item, *a++);
  }
}

TEST(Multiset, merge_int) {
  s21::multiset<double> basic1{78, 23, -9};
  s21::multiset<double> basic2{55, 22, -8, -0.5};
  EXPECT_EQ(basic1.size(), 3);
  EXPECT_EQ(basic2.size(), 4);
  basic1.merge(basic2);
  double s1[7] = {-9, -8, -0.5, 22, 23, 55, 78};
  double *a = s1;
  for (const double &item : basic1) {
    EXPECT_DOUBLE_EQ(item, *a++);
  }
  EXPECT_EQ(basic1.size(), 7);
  EXPECT_EQ(basic2.size(), 0);
}

TEST(Multiset, merge_char) {
  s21::multiset<char> basic1{78, 23, -9};
  s21::multiset<char> basic2{55, 22, -8, 0};
  EXPECT_EQ(basic1.size(), 3);
  EXPECT_EQ(basic2.size(), 4);
  basic1.merge(basic2);
  char s1[7] = {-9, -8, 0, 22, 23, 55, 78};
  char *a = s1;
  for (const char &item : basic1) {
    EXPECT_EQ(item, *a++);
  }
  EXPECT_EQ(basic1.size(), 7);
  EXPECT_EQ(basic2.size(), 0);
}

TEST(Multiset, count_double) {
  s21::multiset<double> basic1{78, 23, -9, 22, 22, 22, 23};
  EXPECT_EQ(basic1.size(), 7);
  EXPECT_DOUBLE_EQ(basic1.count(22), 3);
  EXPECT_DOUBLE_EQ(basic1.count(23), 2);
  EXPECT_DOUBLE_EQ(basic1.count(-9), 1);
}

TEST(Multiset, iterator_find) {
  s21::multiset<double> basic1{78, 23, -9, 22, 22, 22, 23};
  EXPECT_EQ(basic1.size(), 7);
  auto iter_22 = basic1.find(22);
  EXPECT_DOUBLE_EQ(*iter_22, 22);
  EXPECT_DOUBLE_EQ(*++iter_22, 22);
  EXPECT_DOUBLE_EQ(*++iter_22, 22);
  EXPECT_DOUBLE_EQ(*++iter_22, 23);
  EXPECT_DOUBLE_EQ(*++iter_22, 23);
  EXPECT_TRUE(basic1.end() == basic1.find(99));
}

TEST(Multiset, iterator_find2) {
  s21::multiset<double> basic1{78, 7.75, -9, -999, -8, 0.5, 2.88};
  EXPECT_EQ(basic1.size(), 7);
  auto iter_22 = basic1.find(-9);
  EXPECT_DOUBLE_EQ(*iter_22, -9);
  EXPECT_DOUBLE_EQ(*++iter_22, -8);
  EXPECT_DOUBLE_EQ(*++iter_22, 0.5);
  EXPECT_DOUBLE_EQ(*++iter_22, 2.88);
  EXPECT_DOUBLE_EQ(*++iter_22, 7.75);
}

TEST(Multiset, contains_int) {
  s21::multiset<int> basic1{78, 7, -9, -999, -8, 0, 2};
  EXPECT_EQ(basic1.size(), 7);
  EXPECT_TRUE(basic1.contains(-9));
  EXPECT_TRUE(basic1.contains(-999));
  EXPECT_TRUE(basic1.contains(0));
  EXPECT_FALSE(basic1.contains(-33));
  EXPECT_FALSE(basic1.contains(77));
  EXPECT_FALSE(basic1.contains(-98));
}

TEST(Multiset, equal_range_int) {
  s21::multiset<int> basic1{78, 7, -9, -999, -8, 7, 2};
  EXPECT_EQ(basic1.size(), 7);
  auto pair = basic1.equal_range(7);
  int size = 0;
  while (pair.first != pair.second) {
    ++size;
    EXPECT_EQ(*pair.first, 7);
    ++pair.first;
  }
  EXPECT_EQ(size, 2);
  EXPECT_EQ(basic1.size(), 7);
}

TEST(Multiset, equal_range_int2) {
  s21::multiset<int> basic1{78, 7, -9, -999, -8, 7, 2};
  EXPECT_EQ(basic1.size(), 7);
  auto pair = basic1.equal_range(-9);
  int size = 0;
  while (pair.first != pair.second) {
    ++size;
    EXPECT_EQ(*pair.first, -9);
    ++pair.first;
  }
  EXPECT_EQ(size, 1);
  EXPECT_EQ(basic1.size(), 7);
}

TEST(Multiset, lower_bound_and_upper_bound) {
  s21::multiset<int> basic1{782, 7, -9, -999, -8, 7, 2, 32};
  EXPECT_EQ(basic1.size(), 8);
  std::pair<s21::multiset<int>::iterator, s21::multiset<int>::iterator> pair
  = {
      basic1.lower_bound(-9), basic1.upper_bound(32)};
  char s1[6] = {-9, -8, 2, 7, 7, 32};
  char *a = s1;
  int size = 0;
  while (pair.first != pair.second) {
    ++size;
    EXPECT_EQ(*pair.first, *a++);
    ++pair.first;
  }
  EXPECT_EQ(size, 6);
  EXPECT_EQ(basic1.size(), 8);
}

TEST(Multiset, lower_bound_and_upper_bound2) {
  s21::multiset<int> basic1{782, 7, -9, -999, -8, 7, 2, 32};
  EXPECT_EQ(basic1.size(), 8);
  std::pair<s21::multiset<int>::iterator, s21::multiset<int>::iterator> pair
  = {
      basic1.lower_bound(-9), basic1.upper_bound(6)};
  char s1[3] = {-9, -8, 2};
  char *a = s1;
  int size = 0;
  while (pair.first != pair.second) {
    ++size;
    EXPECT_EQ(*pair.first, *a++);
    ++pair.first;
  }
  EXPECT_EQ(*pair.second, 7);
  EXPECT_EQ(size, 3);
  EXPECT_EQ(basic1.size(), 8);
}

TEST(Multiset, erase_reverse) {
  s21::multiset<int> basic1{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
  while (!basic1.empty()) {
    basic1.erase(--basic1.end());
  }
  EXPECT_EQ(basic1.size(), 0);
}

TEST(Multiset, emplace_basic) {
  s21::multiset<int> basic;
  basic.insert_many(1, 3, 4, 4);
  EXPECT_TRUE(basic.contains(1));
  EXPECT_TRUE(basic.contains(3));
  EXPECT_EQ(basic.count(4), 2);
}

TEST(Map, default_constructor_instructor_insert) {
  s21::map<int, int> basic;
  basic.insert({5, 5});
  basic.insert({20, 2});
  basic.insert({2, 20});
  int s[3] = {20, 5, 2};
  int *v = s, *d = v + 2;
  for (auto item : basic) {
    EXPECT_EQ(item.second, *v++);
    EXPECT_EQ(item.first, *d--);
  }
}

TEST(Map, initializator_constructor_int) {
  s21::map<int, int> basic = {{6, 7}, {4, 4}, {2, 2},
                              {8, 8}, {0, 2}, {-228, 5}};
  int s1[6] = {-228, 0, 2, 4, 6, 8};
  int s2[6] = {5, 2, 2, 4, 7, 8};
  int *a = s1, *b = s2;
  for (auto item : basic) {
    EXPECT_EQ(item.first, *a++);
    EXPECT_EQ(item.second, *b++);
  }
}

TEST(Map, initializator_constructor_double) {
  s21::map<double, double> basic = {{999, 222}, {6, 6},   {3, 3},  {2, 4},
                                    {90, -8},   {0, -29}, {-1, -1}};
  double s1[7] = {-1, 0, 2, 3, 6, 90, 999};
  double s2[7] = {-1, -29, 4, 3, 6, -8, 222};
  double *a = s1, *b = s2;
  for (auto item : basic) {
    EXPECT_DOUBLE_EQ(item.first, *a++);
    EXPECT_DOUBLE_EQ(item.second, *b++);
  }
}

TEST(Map, initializator_constructor_char) {
  s21::map<char, char> basic = {{'c', 'c'}, {'d', 'v'}, {'a', 'b'}, {'b',
  'n'}}; char s1[4] = {'a', 'b', 'c', 'd'}; char s2[4] = {'b', 'n', 'c',
  'v'}; char *a = s1, *b = s2; for (auto item : basic) {
    EXPECT_EQ(item.first, *a++);
    EXPECT_EQ(item.second, *b++);
  }
}

TEST(Map, copy_constructor_int) {
  s21::map<int, int> basic = {{6, 7}, {4, 4}, {2, 2},
                              {8, 8}, {0, 2}, {-228, 5}};
  s21::map<int, int> copy{basic};
  int s1[6] = {-228, 0, 2, 4, 6, 8};
  int s2[6] = {5, 2, 2, 4, 7, 8};
  int *a = s1, *b = s2;
  for (auto item : copy) {
    EXPECT_EQ(item.first, *a++);
    EXPECT_EQ(item.second, *b++);
  }
  EXPECT_EQ(basic.size(), copy.size());
}

TEST(Map, move_constructor_int) {
  s21::map<int, int> basic = {{6, 7}, {4, 4}, {2, 2},
                              {8, 8}, {0, 2}, {-228, 5}};
  s21::map<int, int> move{std::move(basic)};
  int s1[6] = {-228, 0, 2, 4, 6, 8};
  int s2[6] = {5, 2, 2, 4, 7, 8};
  int *a = s1, *b = s2;
  for (auto item : move) {
    EXPECT_EQ(item.first, *a++);
    EXPECT_EQ(item.second, *b++);
  }
  EXPECT_EQ(basic.size(), 0);
  EXPECT_EQ(move.size(), 6);
}

TEST(Map, move_operator_int) {
  s21::map<int, int> basic = {{6, 7}, {4, 4}, {2, 2},
                              {8, 8}, {0, 2}, {-228, 5}};
  s21::map<int, int> move = std::move(basic);
  int s1[6] = {-228, 0, 2, 4, 6, 8};
  int s2[6] = {5, 2, 2, 4, 7, 8};
  int *a = s1, *b = s2;
  for (auto item : move) {
    EXPECT_EQ(item.first, *a++);
    EXPECT_EQ(item.second, *b++);
  }
  EXPECT_EQ(basic.size(), 0);
  EXPECT_EQ(move.size(), 6);
}

TEST(Map, iterator_begin_end) {
  s21::map<int, int> basic = {{6, 7}, {4, 4}, {2, 2},
                              {8, 8}, {0, 2}, {-228, 5}};
  auto iter = basic.begin();
  auto iter_end = basic.end();
  int s1[6] = {-228, 0, 2, 4, 6, 8};
  int s2[6] = {5, 2, 2, 4, 7, 8};
  int *a = s1, *b = s2, size = 0;
  while (iter != iter_end) {
    EXPECT_EQ((*iter).first, *a++);
    EXPECT_EQ((*iter++).second, *b++);
    ++size;
  }
  EXPECT_EQ(size, 6);
}

TEST(Map, empty_size) {
  s21::map<int, int> basic;
  EXPECT_TRUE(basic.empty());
  EXPECT_EQ(basic.size(), 0);
  basic.insert({4, 4});
  EXPECT_EQ(basic.size(), 1);
  EXPECT_FALSE(basic.empty());
}

TEST(Map, empty_erase) {
  s21::map<int, int> basic;
  EXPECT_TRUE(basic.empty());
  basic.insert({4, 4});
  EXPECT_FALSE(basic.empty());
  basic.erase(basic.find(4));
  EXPECT_TRUE(basic.empty());
}

TEST(Map, insert) {
  s21::map<int, int> basic;
  auto pair = basic.insert({5, 5});
  EXPECT_EQ((*pair.first).first, 5);
  EXPECT_TRUE(pair.second);
  auto pair2 = basic.insert({5, 5});
  EXPECT_EQ((*pair2.first).first, 5);
  EXPECT_FALSE(pair2.second);
  basic.insert({20, 20});
  basic.insert({2, 2});
  int s[3] = {2, 5, 20};
  int *a = s;
  for (auto item : basic) {
    EXPECT_EQ(item.first, *a++);
  }
}

TEST(Map, empty_clear) {
  s21::map<int, int> basic;
  EXPECT_TRUE(basic.empty());
  basic.insert({4, 5});
  EXPECT_FALSE(basic.empty());
  basic.clear();
  EXPECT_TRUE(basic.empty());
}

TEST(Map, size_clear) {
  s21::map<int, int> basic{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}};
  EXPECT_EQ(basic.size(), 6);
  basic.insert({4, 4});
  EXPECT_EQ(basic.size(), 6);
  basic.insert({7, 7});
  EXPECT_EQ(basic.size(), 7);
  basic.clear();
  EXPECT_EQ(basic.size(), 0);
}

TEST(Map, swap_int) {
  s21::map<int, int> basic1{{1, 1}, {2, 2}, {3, 3}};
  s21::map<int, int> basic2{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  EXPECT_EQ(basic1.size(), 3);
  EXPECT_EQ(basic2.size(), 4);
  int s1[3] = {1, 2, 3};
  int s2[4] = {1, 2, 3, 4};
  int *a = s1;
  for (auto item : basic1) {
    EXPECT_EQ(item.first, *a);
    EXPECT_EQ(item.second, *a++);
  }
  a = s2;
  for (auto item : basic2) {
    EXPECT_EQ(item.first, *a);
    EXPECT_EQ(item.second, *a++);
  }
  basic1.swap(basic2);
  EXPECT_EQ(basic1.size(), 4);
  EXPECT_EQ(basic2.size(), 3);
  a = s1;
  for (auto item : basic2) {
    EXPECT_EQ(item.first, *a);
    EXPECT_EQ(item.second, *a++);
  }
  a = s2;
  for (auto item : basic1) {
    EXPECT_EQ(item.first, *a);
    EXPECT_EQ(item.second, *a++);
  }
}

TEST(Map, swap_double) {
  s21::map<double, double> basic1{{78, 78}, {23, 23}, {-9, -9}};
  s21::map<double, double> basic2{{55, 55}, {22, 22}, {-8, -8}, {-0.5,
  -0.5}}; EXPECT_EQ(basic1.size(), 3); EXPECT_EQ(basic2.size(), 4); double
  s1[3] = {-9, 23, 78}; double s2[4] = {-8, -0.5, 22, 55}; double *a = s1;
  for (auto item : basic1) {
    EXPECT_DOUBLE_EQ(item.first, *a);
    EXPECT_DOUBLE_EQ(item.second, *a++);
  }
  a = s2;
  for (auto item : basic2) {
    EXPECT_DOUBLE_EQ(item.first, *a);
    EXPECT_DOUBLE_EQ(item.second, *a++);
  }
  basic1.swap(basic2);
  EXPECT_EQ(basic1.size(), 4);
  EXPECT_EQ(basic2.size(), 3);
  a = s1;
  for (auto item : basic2) {
    EXPECT_DOUBLE_EQ(item.first, *a);
    EXPECT_DOUBLE_EQ(item.second, *a++);
  }
  a = s2;
  for (auto item : basic1) {
    EXPECT_DOUBLE_EQ(item.first, *a);
    EXPECT_DOUBLE_EQ(item.second, *a++);
  }
}

TEST(Map, merge_double) {
  s21::map<double, double> basic1{
      {78, 78}, {23, 23}, {-9, -9}, {-8, -8}, {-0.5, -0.5}};
  s21::map<double, double> basic2{{55, 55}, {22, 22}, {-8, -8}, {-0.5,
  -0.5}}; EXPECT_EQ(basic1.size(), 5); EXPECT_EQ(basic2.size(), 4);
  basic1.merge(basic2);
  double s1[7] = {-9, -8, -0.5, 22, 23, 55, 78};
  double *a = s1;
  for (auto item : basic1) {
    EXPECT_DOUBLE_EQ(item.first, *a);
    EXPECT_DOUBLE_EQ(item.second, *a++);
  }
  EXPECT_EQ(basic1.size(), 7);
  EXPECT_EQ(basic2.size(), 2);
}

TEST(Map, merge_char) {
  s21::map<char, char> basic1{{78, 78}, {23, 23}, {-9, -9}, {-8, -8}};
  s21::map<char, char> basic2{{55, 55}, {22, 22}, {-8, -8}, {0, 0}};
  EXPECT_EQ(basic1.size(), 4);
  EXPECT_EQ(basic2.size(), 4);
  basic1.merge(basic2);
  char s1[7] = {-9, -8, 0, 22, 23, 55, 78};
  char *a = s1;
  for (auto item : basic1) {
    EXPECT_EQ(item.first, *a);
    EXPECT_EQ(item.second, *a++);
  }
  EXPECT_EQ(basic1.size(), 7);
  EXPECT_EQ(basic2.size(), 1);
}

TEST(Map, iterator_find) {
  s21::map<double, double> basic1{{78, 78}, {23, 23}, {-9, -9}, {22, 22},
                                  {22, 22}, {22, 22}, {23, 23}};
  EXPECT_EQ(basic1.size(), 4);
  auto iter_22 = basic1.find(22);
  EXPECT_DOUBLE_EQ((*iter_22).first, 22);
  EXPECT_DOUBLE_EQ((*++iter_22).first, 23);
  EXPECT_DOUBLE_EQ((*++iter_22).first, 78);
}

TEST(Map, iterator_find2) {
  s21::map<double, double> basic1{{78, 78},     {7.75, 7.75}, {-9, -9},
                                  {-999, -999}, {-8, -8},     {0.5, 0.5},
                                  {2.88, 2.88}};
  EXPECT_EQ(basic1.size(), 7);
  auto iter_22 = basic1.find(-9);
  EXPECT_DOUBLE_EQ((*iter_22).first, -9);
  EXPECT_DOUBLE_EQ((*++iter_22).first, -8);
  EXPECT_DOUBLE_EQ((*++iter_22).first, 0.5);
  EXPECT_DOUBLE_EQ((*++iter_22).first, 2.88);
  EXPECT_DOUBLE_EQ((*++iter_22).first, 7.75);
}

TEST(Map, contains_int) {
  s21::map<int, int> basic1{{78, 78}, {7, 7}, {-9, -9}, {-999, -999},
                            {-8, -8}, {0, 0}, {2, 2}};
  EXPECT_EQ(basic1.size(), 7);
  EXPECT_TRUE(basic1.contains(-9));
  EXPECT_TRUE(basic1.contains(-999));
  EXPECT_TRUE(basic1.contains(0));
  EXPECT_FALSE(basic1.contains(-33));
  EXPECT_FALSE(basic1.contains(77));
  EXPECT_FALSE(basic1.contains(-98));
}

TEST(Map, at_oper_and_bad_list) {
  s21::map<int, int> basic1{{782, 7}, {7, 782}, {-9, -999}, {-999, -9},
                            {-8, 7},  {7, -8},  {2, 32},    {32, 2}};
  EXPECT_EQ(basic1.size(), 7);
  EXPECT_EQ(basic1.at(-8), 7);
  EXPECT_EQ(basic1.at(7), 782);
  EXPECT_EQ(basic1.at(2), 32);
  EXPECT_EQ(basic1[782], 7);
  EXPECT_EQ(basic1[-9], -999);
  EXPECT_EQ(basic1[32], 2);
}

TEST(Map, oper_insert) {
  s21::map<int, int> basic1{{782, 7}, {7, 782}, {-9, -999}, {-999, -9},
                            {-8, 7},  {7, -8},  {2, 32},    {32, 2}};
  EXPECT_EQ(basic1.size(), 7);
  EXPECT_EQ(basic1[4] = 5, 5);
  EXPECT_EQ(basic1[4], 5);
  EXPECT_EQ(basic1.size(), 8);
}

TEST(Map, at_except) {
  s21::map<int, int> basic1{{782, 7}, {7, 782}, {-9, -999}, {-999, -9},
                            {-8, 7},  {7, -8},  {2, 32},    {32, 2}};
  EXPECT_EQ(basic1.size(), 7);
  EXPECT_ANY_THROW(basic1.at(4));
  EXPECT_ANY_THROW(basic1.at(0));
  EXPECT_ANY_THROW(basic1.at(5));
  EXPECT_EQ(basic1.size(), 7);
}

TEST(Map, insert_parametrs) {
  s21::map<int, int> basic1{{782, 7}, {7, 782}, {-9, -999}, {-999, -9},
                            {-8, 7},  {7, -8},  {2, 32},    {32, 2}};
  EXPECT_EQ(basic1.size(), 7);
  auto pair1 = basic1.insert(8, 0);  // без {}
  EXPECT_TRUE(pair1.second);
  EXPECT_EQ((*pair1.first).first, 8);
  EXPECT_EQ((*pair1.first).second, 0);
  EXPECT_EQ(basic1.size(), 8);
}

TEST(Map, insert_parametrs_no) {
  s21::map<int, int> basic1{{782, 7}, {7, 782}, {-9, -999}, {-999, -9},
                            {-8, 7},  {7, -8},  {2, 32},    {32, 2}};
  EXPECT_EQ(basic1.size(), 7);
  auto pair1 = basic1.insert(7, 200);  // без {}
  EXPECT_FALSE(pair1.second);
  EXPECT_EQ((*pair1.first).first, 7);
  EXPECT_EQ((*pair1.first).second, 782);
  EXPECT_EQ(basic1.size(), 7);
}

TEST(Map, insert_or_assign_false) {
  s21::map<int, int> basic1{{782, 7}, {7, 782}, {-9, -999}, {-999, -9},
                            {-8, 7},  {7, -8},  {2, 32},    {32, 2}};
  EXPECT_EQ(basic1.size(), 7);
  auto pair1 = basic1.insert_or_assign(7, 200);
  EXPECT_FALSE(pair1.second);
  EXPECT_EQ((*pair1.first).first, 7);
  EXPECT_EQ((*pair1.first).second, 200);
  EXPECT_EQ(basic1.size(), 7);
}

TEST(Map, insert_or_assign_true) {
  s21::map<int, int> basic1{{782, 7}, {7, 782}, {-9, -999}, {-999, -9},
                            {-8, 7},  {7, -8},  {2, 32},    {32, 2}};
  EXPECT_EQ(basic1.size(), 7);
  auto pair1 = basic1.insert_or_assign(8, 200);
  EXPECT_TRUE(pair1.second);
  EXPECT_EQ((*pair1.first).first, 8);
  EXPECT_EQ((*pair1.first).second, 200);
  EXPECT_EQ(basic1.size(), 8);
}

TEST(Map, insert_or_assign_true_check) {
  s21::map<int, int> basic1{{782, 7}, {7, 782}, {-9, -999}, {-999, -9},
                            {-8, 7},  {7, -8},  {2, 32},    {32, 2}};
  EXPECT_EQ(basic1.size(), 7);
  auto pair1 = basic1.insert_or_assign(8, 200);
  EXPECT_TRUE(pair1.second);
  EXPECT_EQ((*pair1.first).first, 8);
  EXPECT_EQ((*pair1.first).second, 200);
  EXPECT_EQ(basic1.size(), 8);
  int s1[8] = {-999, -9, -8, 2, 7, 8, 32, 782};
  int s2[8] = {-9, -999, 7, 32, 782, 200, 2, 7};
  int *a = s1, *b = s2;
  for (auto item : basic1) {
    EXPECT_DOUBLE_EQ(item.first, *a++);
    EXPECT_DOUBLE_EQ(item.second, *b++);
  }
}

TEST(Map, insert_and_ins_assign_first_insert) {
  s21::map<int, int> basic;
  basic.insert(5, 4);
  s21::map<int, int> basic2;
  basic2.insert_or_assign(5, 4);
}

TEST(Map, emplace_basic) {
  s21::map<int, int> basic;
  basic.insert_many(std::make_pair(1, 2), std::make_pair(3, 2),
                    std::make_pair(4, 1), std::make_pair(2, 1));
  EXPECT_EQ(basic[1], 2);
  EXPECT_EQ(basic[4], 1);
}