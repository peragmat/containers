#include "../test.h"

using namespace std;

TEST(Queue, Сonstructor_null_1) {
  s21::Queue<int> s21_Queue;
  std::queue<int> std_Queue;
  EXPECT_EQ(s21_Queue.size(), std_Queue.size());
  EXPECT_EQ(std_Queue.empty(), s21_Queue.empty());
}

TEST(Queue, Constructor_Default) {
  std::queue<int> std_Queue;
  s21::Queue<int> s21_Queue;

  EXPECT_EQ(s21_Queue.size(), std_Queue.size());
  EXPECT_EQ(s21_Queue.empty(), std_Queue.empty());
}

TEST(Queue, Initializer_queue) {
  std::initializer_list<int> il = {1, 2, 3};
  std::queue<int> std_Queue{il};
  s21::Queue<int> s21_Queue{1, 2, 3};

  EXPECT_EQ(std_Queue.size(), s21_Queue.size());
  EXPECT_EQ(std_Queue.front(), s21_Queue.front());
  EXPECT_EQ(std_Queue.back(), s21_Queue.back());
  EXPECT_EQ(std_Queue.empty(), s21_Queue.empty());
}

TEST(Queue, Push_1) {
  std::queue<double> std_Queue_1;
  s21::Queue<double> s21_Queue_1;
  std_Queue_1.push(1.2);
  std_Queue_1.push(1.1);
  s21_Queue_1.push(1.2);
  s21_Queue_1.push(1.1);
  EXPECT_EQ(std_Queue_1.front(), s21_Queue_1.front());
  EXPECT_EQ(std_Queue_1.back(), s21_Queue_1.back());
  EXPECT_EQ(std_Queue_1.size(), s21_Queue_1.size());

  std::queue<char> std_Queue_2;
  s21::Queue<char> s21_Queue_2;
  std_Queue_2.push('1');
  std_Queue_2.push('2');
  s21_Queue_2.push('1');
  s21_Queue_2.push('2');
  EXPECT_EQ(std_Queue_2.front(), s21_Queue_2.front());
  EXPECT_EQ(std_Queue_2.back(), s21_Queue_2.back());
  EXPECT_EQ(std_Queue_2.size(), s21_Queue_2.size());

  std::queue<string> std_Queue_3;
  s21::Queue<string> s21_Queue_3;
  std_Queue_3.push("string_1");
  std_Queue_3.push("string_2");
  s21_Queue_3.push("string_1");
  s21_Queue_3.push("string_2");
  EXPECT_EQ(std_Queue_3.front(), s21_Queue_3.front());
  EXPECT_EQ(std_Queue_3.back(), s21_Queue_3.back());
  EXPECT_EQ(std_Queue_3.size(), s21_Queue_3.size());
}

TEST(Queue, Push_2) {
  s21::Queue<double> s21_Queue;
  std::queue<double> std_Queue;

  std_Queue.push(1.1);
  s21_Queue.push(1.1);

  EXPECT_EQ(std_Queue.front(), s21_Queue.front());
  EXPECT_EQ(std_Queue.size(), s21_Queue.size());
}

TEST(Queue, Push_back) {
  std::queue<int> std_Queue;
  s21::Queue<int> s21_Queue;
  s21_Queue.push(1.1);
  s21_Queue.push(2.2);
  s21_Queue.push(3.3);
  std_Queue.push(1.1);
  std_Queue.push(2.2);
  std_Queue.push(3.3);

  for (size_t i = 0; i < std_Queue.size(); i++) {
    EXPECT_EQ(std_Queue.front(), s21_Queue.front());
    EXPECT_EQ(std_Queue.back(), s21_Queue.back());
    EXPECT_EQ(std_Queue.size(), s21_Queue.size());
  }
}

TEST(Queue, Pop_front) {
  std::initializer_list<double> il = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7};
  std::queue<double> std_Queue{il};
  s21::Queue<double> s21_Queue = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7};

  for (size_t i = 0; i < s21_Queue.size(); i++) {
    s21_Queue.pop();
    std_Queue.pop();
    EXPECT_EQ(s21_Queue.front(), std_Queue.front());
    EXPECT_EQ(s21_Queue.back(), std_Queue.back());
    EXPECT_EQ(std_Queue.size(), s21_Queue.size());
  }
}

TEST(Queue, front_back_empty) {
  s21::Queue<double> s21_Queue;

  EXPECT_EQ(s21_Queue.front(), 0);
  EXPECT_EQ(s21_Queue.back(), 0);
  EXPECT_EQ(s21_Queue.size(), 0);
}

TEST(Queue, Pop_front_back_throw) {
  s21::Queue<double> s21_Queue;

  ASSERT_ANY_THROW(s21_Queue.pop());
}

TEST(Queue, Copy_queue) {
  std::initializer_list<double> ls = {1.1, 2.2, 1.3, 1.4, 1.5, 1.6, 7.7};
  std::queue<double> std_Queue{ls};
  s21::Queue<double> s21_Queue = {1.1, 2.2, 1.3, 1.4, 1.5, 1.6, 7.7};

  std::queue<double> std_copy(std_Queue);
  s21::Queue<double> s21_copy(s21_Queue);

  EXPECT_EQ(std_Queue.size(), s21_Queue.size());
  EXPECT_EQ(s21_copy.size(), std_copy.size());

  for (size_t i = 0; i < std_Queue.size(); i++) {
    EXPECT_EQ(std_Queue.front(), s21_Queue.front());
    EXPECT_EQ(s21_Queue.back(), std_Queue.back());
    EXPECT_EQ(s21_copy.front(), std_copy.front());
    EXPECT_EQ(s21_copy.back(), std_copy.back());
    EXPECT_EQ(s21_Queue.size(), std_Queue.size());
    EXPECT_EQ(s21_copy.size(), std_copy.size());
    s21_copy.pop(), std_copy.pop();
  }
}

TEST(Queue, Copy_op) {
  std::initializer_list<double> ls = {1.1, 2.2, 1.3, 1.4, 1.5, 1.6, 7.7};
  std::queue<double> std_Queue{ls};
  s21::Queue<double> s21_Queue = {1.1, 2.2, 1.3, 1.4, 1.5, 1.6, 7.7};

  std::queue<double> std_copy;
  s21::Queue<double> s21_copy;
  std_copy = std_Queue;
  s21_copy = s21_Queue;

  EXPECT_EQ(s21_Queue.size(), std_Queue.size());
  EXPECT_EQ(s21_copy.size(), std_copy.size());

  for (size_t i = 0; i < std_Queue.size(); i++) {
    EXPECT_EQ(std_Queue.front(), s21_Queue.front());
    EXPECT_EQ(s21_Queue.back(), std_Queue.back());
    EXPECT_EQ(s21_copy.front(), std_copy.front());
    EXPECT_EQ(s21_copy.back(), std_copy.back());
    EXPECT_EQ(s21_Queue.size(), std_Queue.size());
    EXPECT_EQ(s21_copy.size(), std_copy.size());
    s21_copy.pop(), std_copy.pop();
  }
}

TEST(Queue, Move_queue) {
  std::initializer_list<double> ls = {1.1, 2.2, 1.3, 1.4, 1.5, 1.6, 7.7};
  std::queue<double> std_Queue{ls};
  s21::Queue<double> s21_Queue = {1.1, 2.2, 1.3, 1.4, 1.5, 1.6, 7.7};

  std::queue<double> std_move = std::move(std_Queue);
  s21::Queue<double> s21_move = move(s21_Queue);

  EXPECT_EQ(s21_Queue.size(), std_Queue.size());
  EXPECT_EQ(s21_move.size(), std_move.size());
  EXPECT_EQ(s21_Queue.empty(), true);

  for (size_t i = 0; i < std_move.size(); i++) {
    EXPECT_EQ(s21_move.back(), std_move.back());
    EXPECT_EQ(s21_move.front(), std_move.front());
    EXPECT_EQ(s21_move.size(), std_move.size());
    s21_move.pop(), std_move.pop();
  }
}

TEST(Queue, Move_op) {
  std::initializer_list<double> ls = {1.1, 2.2, 1.3, 1.4, 1.5, 1.6, 7.7};
  std::queue<double> std_Queue{ls};
  s21::Queue<double> s21_Queue{1.1, 2.2, 1.3, 1.4, 1.5, 1.6, 7.7};

  std::queue<double> std_move;
  s21::Queue<double> s21_move;

  std_move = std::move(std_Queue);
  s21_move = move(s21_Queue);

  EXPECT_EQ(s21_Queue.size(), std_Queue.size());
  EXPECT_EQ(s21_move.size(), std_move.size());
  EXPECT_EQ(s21_Queue.empty(), true);

  for (size_t i = 0; i < std_move.size(); i++) {
    EXPECT_EQ(s21_move.front(), std_move.front());
    EXPECT_EQ(s21_move.back(), std_move.back());
    EXPECT_EQ(s21_move.size(), std_move.size());
    s21_move.pop();
    std_move.pop();
  }
}

TEST(Queue, Swap) {
  std::initializer_list<double> ls_1 = {1.1, 2.2, 1.3, 1.4, 1.5, 1.6, 7.7};
  std::queue<double> std_Queue_1{ls_1};
  s21::Queue<double> s21_Queue_1{1.1, 2.2, 1.3, 1.4, 1.5, 1.6, 7.7};

  std::initializer_list<double> ls_2 = {9.9, 8.8, 5.5, 4.4, 3.3};
  std::queue<double> std_Queue_2{ls_2};
  s21::Queue<double> s21_Queue_2{9.9, 8.8, 5.5, 4.4, 3.3};

  std_Queue_1.swap(std_Queue_2);
  s21_Queue_1.swap(s21_Queue_2);
  EXPECT_EQ(std_Queue_1.size(), s21_Queue_1.size());
  EXPECT_EQ(std_Queue_2.size(), s21_Queue_2.size());

  for (size_t i = 0; i < std_Queue_1.size(); i++) {
    EXPECT_EQ(std_Queue_1.front(), s21_Queue_1.front());
    EXPECT_EQ(std_Queue_1.back(), s21_Queue_1.back());
    EXPECT_EQ(std_Queue_1.size(), s21_Queue_1.size());
    std_Queue_1.pop(), s21_Queue_1.pop();
  }

  for (size_t i = 0; i < std_Queue_2.size(); i++) {
    EXPECT_EQ(std_Queue_2.front(), s21_Queue_2.front());
    EXPECT_EQ(std_Queue_2.back(), s21_Queue_2.back());
    EXPECT_EQ(std_Queue_2.size(), s21_Queue_2.size());
    std_Queue_2.pop(), s21_Queue_2.pop();
  }
}

TEST(s21_Queue_test, insert_many_back_0) {
  std::queue<int> std_Queue;
  s21::Queue<int> s21_Queue;

  std_Queue.emplace(1);
  s21_Queue.insert_many_back(1);

  EXPECT_EQ(std_Queue.size(), s21_Queue.size());
  EXPECT_EQ(std_Queue.front(), s21_Queue.front());
  EXPECT_EQ(std_Queue.back(), s21_Queue.back());
}

TEST(s21_Queue_test, insert_many_back_1) {
  std::queue<int> std_Queue;
  s21::Queue<int> s21_Queue;

  s21_Queue.insert_many_back(4, 5, 6, 7, 8, 9);

  std_Queue.emplace(4);
  std_Queue.emplace(5);
  std_Queue.emplace(6);
  std_Queue.emplace(7);
  std_Queue.emplace(8);
  std_Queue.emplace(9);

  EXPECT_EQ(s21_Queue.size(), std_Queue.size());
  EXPECT_EQ(std_Queue.front(), s21_Queue.front());
  EXPECT_EQ(std_Queue.back(), s21_Queue.back());

  for (size_t i = 0; i < std_Queue.size(); i++) {
    EXPECT_EQ(std_Queue.front(), s21_Queue.front());
    EXPECT_EQ(std_Queue.back(), s21_Queue.back());
    EXPECT_EQ(std_Queue.size(), s21_Queue.size());
    std_Queue.pop(), s21_Queue.pop();
  }
}

TEST(s21_Queue_test, insert_many_back_2) {
  std::initializer_list<double> ls_1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::queue<double> std_Queue{ls_1};
  s21::Queue<int> s21_Queue{1, 2, 3, 4, 5, 6, 7, 8};

  s21_Queue.insert_many_back(4, 5, 6, 7, 8, 9);

  std_Queue.emplace(4);
  std_Queue.emplace(5);
  std_Queue.emplace(6);
  std_Queue.emplace(7);
  std_Queue.emplace(8);
  std_Queue.emplace(9);

  EXPECT_EQ(s21_Queue.size(), std_Queue.size());
  EXPECT_EQ(std_Queue.front(), s21_Queue.front());
  EXPECT_EQ(std_Queue.back(), s21_Queue.back());

  for (size_t i = 0; i < std_Queue.size(); i++) {
    EXPECT_EQ(std_Queue.front(), s21_Queue.front());
    EXPECT_EQ(std_Queue.back(), s21_Queue.back());
    EXPECT_EQ(std_Queue.size(), s21_Queue.size());
    std_Queue.pop(), s21_Queue.pop();
  }
}
