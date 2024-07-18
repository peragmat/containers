#ifndef SRC_S21_CONTAINERS_S21_CONTAINERS_S21_SET_H_
#define SRC_S21_CONTAINERS_S21_CONTAINERS_S21_SET_H_

#include "../s21_minor_data_struct/s21_rb_tree.h"

namespace s21 {

template <class T, class Compare = std::less<T>>
class set {
 public:
  using key_type = T;
  using value_type = T;
  using size_type = size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator =
      typename RedBlackTree<value_type, Compare>::RedBlackTreeIterator;
  using const_iterator =
      typename RedBlackTree<value_type, Compare>::RedBlackTreeConstIterator;

  set() = default;
  set(std::initializer_list<value_type> const &items) : tree_(items) {}
  set(const set &other) : tree_(other.tree_) {}
  set(set &&other) noexcept : tree_(std::move(other.tree_)) {}
  ~set() = default;

  set &operator=(const set &other) {
    if (this != &other) {
      tree_ = other.tree_;
    }
    return *this;
  }
  set &operator=(set &&other) noexcept {
    if (this != &other) {
      tree_ = std::move(other.tree_);
    }
    return *this;
  }

  // Check if the set is empty
  bool empty() const { return tree_.empty(); }

  // Get the size of the set
  size_type size() const noexcept { return tree_.size(); }

  // Get the maximum size of the set
  size_type max_size() const noexcept { return tree_.max_size(); }

  // Clear the set
  void clear() { tree_.clear(); }

  // Insert a value into the set and return an iterator
  // to the element and a bool denoting whether the insertion took place
  std::pair<iterator, bool> insert(const value_type &value) {
    iterator iter = find(value);
    if (iter != end()) {
      return {iter, false};
    } else {
      tree_.insert(value);
      return {find(value), true};
    }
  }

  // Erase a value from the set
  void erase(iterator pos) { tree_.erase(pos); }

  // Swap two sets
  void swap(set &other) { tree_.swap(other.tree_); }

  // Merge two sets
  void merge(set &other) { tree_.merge(other.tree_); }

  // Find an element in the set
  iterator find(const key_type &key) { return tree_.find(key); }

  // Check if the set contains an element with a specific key
  bool contains(const key_type &key) const { return tree_.contains(key); }

  // Iterator methods
  iterator begin() noexcept { return tree_.begin(); }
  const_iterator begin() const noexcept { return tree_.cbegin(); }

  iterator end() noexcept { return tree_.end(); }
  const_iterator end() const noexcept { return tree_.cend(); }

  const_iterator cbegin() const noexcept { return tree_.cbegin(); }
  const_iterator cend() const noexcept { return tree_.cend(); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> results;
    (results.emplace_back(insert(std::forward<Args>(args))), ...);
    return results;
  }

 private:
  s21::RedBlackTree<value_type, Compare> tree_;
};

}  // namespace s21

#endif  // SRC_S21_CONTAINERS_S21_CONTAINERS_S21_SET_H_
