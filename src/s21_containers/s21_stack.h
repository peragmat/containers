#ifndef SRC_S21_CONTAINERS_S21_CONTAINERS_S21_STACK_H_
#define SRC_S21_CONTAINERS_S21_CONTAINERS_S21_STACK_H_

#include <cstddef>
#include <list>  // заменить на наш лист

namespace s21 {
template <typename T>
class stack {
 public:
  // member type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  // constructors/destructor stack
  //  default constructor
  stack() = default;

  // Initializer list constructor, creates list initialized using
  stack(std::initializer_list<T> const& items);

  // copy constructor
  stack(const stack& other);

  // move constructor
  stack(stack&& other) noexcept;

  // Assignment operator overload for coping objec
  stack& operator=(const stack& other);

  // Assignment operator overload for moving object
  stack& operator=(stack&& other) noexcept;

  // destructor
  ~stack();

  // stack Element access
  // Accesses the top element
  const_reference top();

  // stack Capacity
  // Checks whether the container is empty
  bool empty() const;

  // Returns the number of elements in the container
  size_type size() const;

  // stack Modifiers
  // Inserts an element at the top
  void push(const_reference value);

  // Removes the top element
  void pop();

  // Swaps the contents
  void swap(stack& other);

  template <class... Args>

  // Pushes a new element on top of the stack
  void emplace(Args&&... args);

 private:
  std::list<value_type> list_;
};

template <typename T>
stack<T>::stack(std::initializer_list<T> const& items) : list_{items} {}

template <typename T>
stack<T>::stack(const stack& other) : list_{other.list_} {}

template <typename T>
stack<T>::stack(stack&& other) noexcept : list_{std::move(other.list_)} {}

template <typename T>
stack<T>& stack<T>::operator=(const stack& other) {
  if (this != &other) {
    stack(other).swap(*this);
  }
  return *this;
}

template <typename T>
stack<T>& stack<T>::operator=(stack&& other) noexcept {
  if (this != &other) {
    list_ = std::move(other.list_);
  }
  return *this;
}

template <typename T>
stack<T>::~stack() {}

template <typename T>
typename stack<T>::const_reference stack<T>::top() {
  return list_.back();
}

template <typename T>
bool stack<T>::empty() const {
  return list_.empty();
}

template <typename T>
typename stack<T>::size_type stack<T>::size() const {
  return list_.size();
}

template <typename T>
void stack<T>::push(const_reference value) {
  list_.push_back(value);
}

template <typename T>
void stack<T>::pop() {
  list_.pop_back();
}

template <typename T>
void stack<T>::swap(stack& other) {
  list_.swap(other.list_);
}

template <typename T>
template <class... Args>
void stack<T>::emplace(Args&&... args) {
  list_.emplace_front(std::forward<Args>(args)...);
}
};  // namespace s21

#endif  // SRC_S21_CONTAINERS_S21_CONTAINERS_S21_STACK_H_
