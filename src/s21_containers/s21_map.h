#ifndef SRC_S21_CONTAINERS_S21_CONTAINERS_S21_MAP_H_
#define SRC_S21_CONTAINERS_S21_CONTAINERS_S21_MAP_H_

#include "../s21_minor_data_struct/s21_rb_tree.h"

namespace s21 {

template <class Key, class T, class Compare = std::less<Key>>
class map {
 public:
  struct MapCmp;

  using key_type = Key;
  using maped_type = T;
  using value_type = std::pair<const Key, T>;
  using size_type = size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator =
      typename RedBlackTree<value_type, MapCmp>::RedBlackTreeIterator;
  using const_iterator =
      typename RedBlackTree<value_type, MapCmp>::RedBlackTreeConstIterator;

  map() = default;
  map(std::initializer_list<value_type> const &items) : tree_(items) {}
  map(const map &other) : tree_(other.tree_) {}
  map(map &&other) noexcept : tree_(std::move(other.tree_)) {}
  ~map() = default;

  map &operator=(const map &other) {
    if (this != &other) {
      tree_ = other.tree_;
    }
    return *this;
  }
  map &operator=(map &&other) noexcept {
    if (this != &other) {
      tree_ = std::move(other.tree_);
    }
    return *this;
  }

  T &at(const key_type &key) {
    auto search_elem = value_type(key, maped_type{});
    iterator search_iter = tree_.find(search_elem);
    if (search_iter == tree_.end()) {
      throw std::out_of_range("Element not found in map.");
    }
    return (*search_iter).second;
  }

  const T &at(const key_type &key) const {
    auto search_elem = value_type(key, maped_type{});
    const_iterator search_iter = tree_.find(search_elem);
    if (search_iter == tree_.cend()) {
      throw std::out_of_range("Element not found in map.");
    }
    return (*search_iter).second;
  }

  T &operator[](const key_type &key) {
    auto search_elem = value_type(key, maped_type{});
    iterator search_iter = tree_.find(search_elem);
    if (search_iter == tree_.end()) {
      tree_.insert(search_elem);
      search_iter = tree_.find(search_elem);
    }
    return (*search_iter).second;
  }

  // Check if the map is empty
  bool empty() const { return tree_.empty(); }

  // Get the size of the map
  size_type size() const noexcept { return tree_.size(); }

  // Get the maximum size of the map
  size_type max_size() const noexcept { return tree_.max_size(); }

  // Clear the map
  void clear() { tree_.clear(); }

  // Insert a value into the map and return an iterator
  // to the element and a bool denoting whether the insertion took place
  std::pair<iterator, bool> insert(const value_type &value) {
    iterator iter = find(value.first);
    if (iter != end()) {
      return {iter, false};  // Element already exists
    } else {
      tree_.insert(value);
      return {find(value.first), true};
    }
  }

  std::pair<iterator, bool> insert(const key_type &key, const T &obj) {
    value_type insert_obj(key, obj);
    iterator iter = find(key);
    if (iter != end()) {
      return {iter, false};  // Element already exists
    } else {
      tree_.insert(insert_obj);
      return {find(key), true};
    }
  }

  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const T &obj) {
    value_type insert_obj(key, obj);
    iterator iter = find(key);
    if (iter != end()) {
      iter->second = obj;
      return {iter, false};  // Element already exists
    } else {
      tree_.insert(insert_obj);
      return {find(key), true};
    }
  }

  // Erase a value from the map
  void erase(iterator pos) { tree_.erase(pos); }

  // Swap two sets
  void swap(map &other) { tree_.swap(other.tree_); }

  // Merge two sets
  void merge(map &other) { tree_.merge(other.tree_); }

  // Find an element in the map
  iterator find(const key_type &key) {
    value_type search_pair(key, maped_type{});
    return tree_.find(search_pair);
  }

  const_iterator find(const key_type &key) const {
    value_type search_pair(key, maped_type{});
    return tree_.find(search_pair);
  }

  // Check if the map contains an element with a specific key
  bool contains(const key_type &key) const {
    return tree_.contains(value_type(key, maped_type{}));
  }

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
  RedBlackTree<value_type, MapCmp> tree_;
};

template <class Key, class T, class Compare>
struct s21::map<Key, T, Compare>::MapCmp {
  bool operator()(const_reference op1, const_reference op2) const noexcept {
    return Compare()(op1.first, op2.first);
  }
};

}  // namespace s21

#endif  // SRC_S21_CONTAINERS_S21_CONTAINERS_S21_MAP_H_
