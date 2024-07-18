#ifndef SRC_S21_CONTAINERS_S21_CONTAINERS_S21_QUEUE_H_
#define SRC_S21_CONTAINERS_S21_CONTAINERS_S21_QUEUE_H_

#include <iostream>

namespace s21 {

template <typename T, typename Container = s21::List<T>>
class Queue {
 public:
  using value_type =
      T;  // defines the type of an element (T is template parameter)
  using reference = T &;  // defines the type of the reference to an element
  using const_reference =
      const T &;                  // defines the type of the constant reference
  using size_type = std::size_t;  // size_t defines the type of the container
                                  // size (standard type is size_t)

  Queue() : basecontainer_() {}  // default constructor, creates empty queue
  Queue(std::initializer_list<value_type> const &items)
      : basecontainer_(items) {}
  Queue(const Queue &q)
      : basecontainer_(q.basecontainer_) {}  // copy constructor
  Queue(Queue &&q) noexcept : basecontainer_(move(q.basecontainer_)) {}
  ~Queue() {}                   // destructor
  Queue &operator=(Queue &q) {  // assignment operator overload for copy object
    basecontainer_ = q.basecontainer_;
    return *this;
  }
  Queue &operator=(
      Queue &&q) noexcept {  // assignment operator overload for moving object
    basecontainer_ = move(q.basecontainer_);
    return *this;
  }

  const_reference front() const noexcept {
    return basecontainer_.front();
  }  // access the first element
  const_reference back() const noexcept {
    return basecontainer_.back();
  }  // access the last element

  void push(const_reference value) {
    basecontainer_.push_back(value);
  }                                           // inserts element at the end
  void pop() { basecontainer_.pop_front(); }  // removes the first element
  void swap(Queue &other) {
    basecontainer_.swap(other.basecontainer_);
  }  // swaps the contents

  bool empty() const noexcept {
    return basecontainer_.empty();
  }  // checks whether the container is empty
  size_type size() const noexcept {
    return basecontainer_.size();
  }  // returns the number of elements
  // void show() noexcept {basecontainer_.show();}

  template <class... Args>
  void insert_many_back(Args &&...args) {
    return basecontainer_.insert_many_back(std::forward<Args>(args)...);
  }

 private:
  Container basecontainer_;  // !!! не уверено, что правильно написана в
                             // соответсвие с кодстайлом
};
}  // namespace s21
#endif  // SRC_S21_CONTAINERS_S21_CONTAINERS_S21_QUEUE_H_
