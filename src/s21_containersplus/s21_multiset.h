#ifndef SRC_S21_CONTAINERSPLUS_S21_MULTISET_H_
#define SRC_S21_CONTAINERSPLUS_S21_MULTISET_H_

#include "../s21_minor_data_struct/s21_rb_tree.h"

namespace s21 {

template <class Key, class Compare = std::less<Key>>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using size_type = size_t;
  using key_compare = Compare;
  using value_compare = Compare;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator =
      typename RedBlackTree<value_type, key_compare>::RedBlackTreeIterator;
  using const_iterator =
      typename RedBlackTree<value_type, key_compare>::RedBlackTreeConstIterator;

  multiset() = default;
  multiset(std::initializer_list<value_type> const &items) : multiset() {
    for (auto item : items) {
      insert(item);
    }
  }
  multiset(const multiset &other) : tree_(other.tree_) {}
  multiset(multiset &&other) noexcept : tree_(std::move(other.tree_)) {}
  ~multiset() = default;

  multiset &operator=(const multiset &other) {
    if (this != &other) {
      tree_ = other.tree_;
    }
    return *this;
  }
  multiset &operator=(multiset &&other) noexcept {
    if (this != &other) {
      tree_ = std::move(other.tree_);
    }
    return *this;
  }

  // Check if the multiset is empty
  bool empty() const { return tree_.empty(); }

  // Get the size of the multiset
  size_type size() const noexcept { return tree_.size(); }

  // Get the maximum size of the multiset
  size_type max_size() const noexcept { return tree_.max_size(); }

  // Clear the multiset
  void clear() { tree_.clear(); }

  // Insert a value into the multiset and return an iterator
  // to the element and a bool denoting whether the insertion took place
  std::pair<iterator, bool> insert(const value_type &value) {
    tree_.insert(value, s21::RedBlackTree<value_type, key_compare>::kNonUnique);
    iterator iter = find(value);
    return {iter, iter != end()};
  }

  // Erase a value from the multiset
  // void erase(const key_type &value) { tree_.erase(value); }
  void erase(iterator pos) { tree_.erase(pos); }

  // Swap two sets
  void swap(multiset &other) { tree_.swap(other.tree_); }

  // Merge two sets
  void merge(multiset &other) {
    if (other.begin() == other.end()) return;

    iterator begin = other.begin();
    iterator end = other.end();
    while (begin != end) {
      insert(*begin);
      other.erase(begin++);
    }
  }

  size_type count(const Key &key) const { return tree_.count(key); }

  // Find an element in the multiset
  iterator find(const key_type &key) { return tree_.find(key); }
  const_iterator find(const key_type &key) const { return tree_.find(key); }

  // Check if the multiset contains an element with a specific key
  bool contains(const key_type &key) const { return tree_.contains(key); }

  iterator lower_bound(const key_type &key) { return tree_.lower_bound(key); }
  iterator upper_bound(const key_type &key) { return tree_.upper_bound(key); }
  const_iterator lower_bound(const key_type &key) const {
    return tree_.lower_bound(key);
  }
  const_iterator upper_bound(const key_type &key) const {
    return tree_.upper_bound(key);
  }
  std::pair<iterator, iterator> equal_range(const key_type &key) {
    return tree_.equal_range(key);
  };
  std::pair<const_iterator, const_iterator> equal_range(
      const key_type &key) const {
    return tree_.equal_range(key);
  };

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
  s21::RedBlackTree<value_type, key_compare> tree_;
};

}  // namespace s21

#endif  // SRC_S21_CONTAINERSPLUS_S21_MULTISET_H_
