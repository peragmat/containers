#ifndef SRC_S21_MINOR_DATA_STRUCT_S21_RB_TREE_H_
#define SRC_S21_MINOR_DATA_STRUCT_S21_RB_TREE_H_

#include <iostream>
#include <limits>
#include <string>

namespace s21 {

enum RBTColor : bool { kColorRed = false, kColorBlack = true };

// Класс, представляющий красно-черное дерево
template <typename T, class Compare = std::less<T>>
class RedBlackTree {
 public:
  struct Node;
  class RedBlackTreeIterator;
  class RedBlackTreeConstIterator;

  enum RBTypeInsert : bool { kNonUnique = false, kUnique = true };
  using key_type = T;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = RedBlackTreeIterator;
  using const_iterator = RedBlackTreeConstIterator;
  using size_type = std::size_t;
  using node_type = Node;
  using node_ptr = node_type *;

  RedBlackTree();
  RedBlackTree(const RedBlackTree &other);
  RedBlackTree(RedBlackTree &&other) noexcept;
  RedBlackTree(std::initializer_list<value_type> const &items);

  RedBlackTree &operator=(const RedBlackTree &other);
  RedBlackTree &operator=(RedBlackTree &&other) noexcept;

  ~RedBlackTree();

  // Иттераторы
  iterator begin() noexcept { return iterator(GetMinNode(root_), this); }
  const_iterator begin() const noexcept {
    return const_iterator(GetMinNode(root_), this);
  }
  const_iterator cbegin() const noexcept {
    return const_iterator(GetMinNode(root_), this);
  }
  iterator end() noexcept { return iterator(nil_, this); }
  const_iterator end() const noexcept { return const_iterator(nil_, this); }
  const_iterator cend() const noexcept { return const_iterator(nil_, this); }

  // Вставка значения в дерево
  std::pair<iterator, bool> insert(
      const value_type &value,
      RBTypeInsert insert_type = RBTypeInsert::kUnique);
  // Удаление значения из дерева
  void erase(iterator pos);

  bool empty() const { return size_ == 0U; };
  void swap(RedBlackTree &other);
  void clear() noexcept;
  void merge(RedBlackTree &other_tree);

  // Возвращает количество узлов в древе
  size_type size() const noexcept { return size_; };
  // Возвращает максимально возможное количество узлов
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(Node);
  }

  size_type count(const key_type &key) const;

  iterator find(const key_type &key) { return iterator(FindNode(key), this); };
  const_iterator find(const key_type &key) const {
    return const_iterator(FindNode(key), this);
  };
  bool contains(const key_type &key) const { return FindNode(key) != nil_; }

  iterator lower_bound(const key_type &key);
  iterator upper_bound(const key_type &key);
  const_iterator lower_bound(const key_type &key) const;
  const_iterator upper_bound(const key_type &key) const;
  std::pair<iterator, iterator> equal_range(const key_type &key) {
    return {lower_bound(key), upper_bound(key)};
  }
  std::pair<const_iterator, const_iterator> equal_range(
      const key_type &key) const {
    return {lower_bound(key), upper_bound(key)};
  }

 private:
  // Поиск значения в дереве
  node_ptr FindNode(const key_type &value) const;

  // Создание нового узла с фиктивным узлом вместо nullptr
  node_ptr CreateNode(const value_type &value, node_ptr parent);

  // Вспомогательные методы для взаимодействия с узлами дерева
  node_ptr get_parent(node_ptr node) const {
    return node ? node->parent : nullptr;
  }
  node_ptr get_left(node_ptr node) const { return node ? node->left : nil_; }
  node_ptr get_right(node_ptr node) const { return node ? node->right : nil_; }
  RBTColor get_color(node_ptr node) const {
    return node ? node->color : RBTColor::kColorBlack;
  }
  const_reference get_data(node_ptr node) const {
    return node ? node->data
                : throw std::logic_error(
                      "Запрос данны у несуществующего элемента.");
  }

  // Получить следующий по порядку элемент
  node_ptr GetNext(const node_ptr node) const;

  // Получить предедущий по порядку элемент
  node_ptr GetPrev(const node_ptr node) const;

  void set_data(node_ptr node, const T &value) {
    if (node) node->data = value;
  }
  void set_color(node_ptr node, RBTColor node_color) {
    if (node) node->color = node_color;
  }
  void set_parent(node_ptr node, node_ptr parent_node) {
    if (node) node->parent = parent_node;
  }
  void set_left(node_ptr node, node_ptr left_node) {
    if (node) node->left = left_node;
  }
  void set_right(node_ptr node, node_ptr right_node) {
    if (node) node->right = right_node;
  }

  // Поиск минимального узла
  node_ptr GetMinNode(node_ptr node) const;
  node_ptr GetMaxNode(node_ptr node) const;

  // Вспомогательные приватные методы для вставки и удаления узлов
  void InsertNode(const_reference value);
  void InsertUniqueNode(const_reference value);
  void InsertInRoot(const_reference value);
  void InsertNewNodeWithFix(node_ptr node, node_ptr parent,
                            const_reference value);
  void EraseNode(node_ptr node);

  void UpdateNil() {
    set_right(nil_, GetMinNode(root_));
    set_left(nil_, GetMaxNode(root_));
  };

  // Вспомогательные приватные методы для балансировки дерева
  void RotateLeft(node_ptr node);
  void RotateRight(node_ptr node);
  void FixInsertion(node_ptr node);
  void Transplant(node_ptr node, node_ptr from_node);
  void FixErase(node_ptr node);

  // Копирование узлов дерева src_node в this
  node_ptr CopyTree(const node_ptr src_node, node_ptr parent,
                    const node_ptr oth_nil);

  void Clear(node_ptr node);

  node_ptr nil_;   // Фиктивный нулевой элемент
  node_ptr root_;  // Указатель на корневой узел
  size_type size_;
  Compare cmp_;
};

// Класс, представляющий узел красно-черного дерева
template <typename T, typename Compare>
struct RedBlackTree<T, Compare>::Node {
 public:
  // Констркутор для создания и инициализация фейкера
  Node()
      : parent(this),
        left(this),
        right(this),
        color(RBTColor::kColorBlack),
        data(T{}) {}

  // Конструктор для инициализации узла
  Node(const value_type &value, RBTColor node_color = RBTColor::kColorRed)
      : parent(nullptr),
        left(nullptr),
        right(nullptr),
        color(node_color),
        data(value) {}

  // Удаление узла
  ~Node() = default;

  node_ptr parent;  // Указатель на родительский узел
  node_ptr left;  // Указатель на левый дочерний узел
  node_ptr right;  // Указатель на правый дочерний узел
  RBTColor color;  // Цвет узла
  T data;          // Значение узла
};

template <typename T, typename Compare>
RedBlackTree<T, Compare>::RedBlackTree(const RedBlackTree &other)
    : RedBlackTree() {
  if (other.root_ != other.nil_) {
    root_ = CopyTree(other.root_, nil_, other.nil_);
  }
  cmp_ = other.cmp_;
}

template <typename T, typename Compare>
std::pair<typename RedBlackTree<T, Compare>::iterator, bool>
RedBlackTree<T, Compare>::insert(const value_type &value,
                                 RBTypeInsert insert_type) {
  // Проверка на переполнение дерева
  if (max_size() == size_) {
    throw std::overflow_error(
        "Insertion is not possible. The element limit has been reached");
  }

  // Если дерево пусто, вставляем элемент в корень
  if (root_ == nil_) {
    InsertInRoot(value);
    return {find(value), true};
  } else if (insert_type == RBTypeInsert::kUnique) {
    // Если вставка уникального элемента и элемент уже существует,
    // возвращаем итератор на существующий элемент
    iterator iter = find(value);
    if (iter != end()) {
      return {iter, false};
    } else {
      // Вставляем уникальный элемент
      InsertUniqueNode(value);
      return {find(value), true};
    }

  } else {
    // Вставка элемента без проверки на уникальность
    InsertNode(value);
    return {find(value), true};
  }
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::InsertNode(const_reference value) {
  // Начинаем поиск места для вставки элемента, начиная с корня
  node_ptr node = root_;
  node_ptr parent = root_;

  // Проходим по дереву до тех пор, пока не найдем подходящее место для вставки
  do {
    parent = node;
    if (cmp_(value, get_data(node))) {
      // Если значение меньше, чем текущий узел, идем влево
      node = get_left(node);
    } else {
      // Если значение больше или равно текущему узлу, идем вправо
      node = get_right(node);
    }
  } while (node != nil_);
  // Вызываем функцию для вставки нового узла и исправления возможных нарушений
  // свойств красно-черного дерева
  InsertNewNodeWithFix(node, parent, value);
}


// Аналогично предедущему но вставка УНИКАЛЬНОГО элемента
template <typename T, typename Compare>
void RedBlackTree<T, Compare>::InsertUniqueNode(const_reference value) {
  node_ptr node = root_;
  node_ptr parent = root_;
  do {
    parent = node;
    if (cmp_(value, get_data(node))) {
      node = get_left(node);
    } else if (cmp_(get_data(node), value)) {
      node = get_right(node);
    } else {
      return;
    }
  } while (node != nil_);
  InsertNewNodeWithFix(node, parent, value);
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::InsertInRoot(const_reference value) {
  root_ = new Node(value, RBTColor::kColorBlack);
  set_parent(root_, nil_);
  set_left(root_, nil_);
  set_right(root_, nil_);
  size_++;
  UpdateNil();
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::InsertNewNodeWithFix(node_ptr node,
                                                    node_ptr parent,
                                                    const_reference value) {
  node = CreateNode(value, parent);
  if (cmp_(value, get_data(parent))) {
    set_left(parent, node);
  } else {
    set_right(parent, node);
  }

  FixInsertion(node);
  UpdateNil();
  size_++;
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::RotateLeft(node_ptr x) {
  // Сохраняем правого потомка x
  node_ptr min_node = get_right(x);
  // Переносим левое поддерево min_node в качестве правого поддерева x
  set_right(x, get_left(min_node));

  // Если у min_node есть левый потомок, устанавливаем его родителем x
  if (get_left(min_node) != nil_) {
    set_parent(get_left(min_node), x);
  }

  // Устанавливаем родителя min_node таким же, как у x
  set_parent(min_node, get_parent(x));

  // Обновляем указатель на корень, если x был корневым узлом
  if (get_parent(x) == nil_) {
    root_ = min_node;
  } else if (x == get_left(get_parent(x))) {
    set_left(get_parent(x), min_node);
  } else {
    set_right(get_parent(x), min_node);
  }

  // Перевешиваем x влево
  set_left(min_node, x);
  set_parent(x, min_node);
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::RotateRight(node_ptr min_node) {
  // Сохраняем левого потомка min_node
  node_ptr x = get_left(min_node);

  // Переносим правое поддерево x в качестве левого поддерева min_node
  set_left(min_node, get_right(x));

  // Если у x есть правый потомок, устанавливаем его родителем min_node
  if (get_right(x) != nil_) {
    set_parent(get_right(x), min_node);
  }

  // Устанавливаем родителя x таким же, как у min_node
  set_parent(x, get_parent(min_node));

  // Обновляем указатель на корень, если min_node был корневым узлом
  if (get_parent(min_node) == nil_) {
    root_ = x;
  } else if (min_node == get_right(get_parent(min_node))) {
    set_right(get_parent(min_node), x);
  } else {
    set_left(get_parent(min_node), x);
  }

  // Перевешиваем min_node вправо
  set_right(x, min_node);
  set_parent(min_node, x);
}

// Метод для балансировки дерева после вставки
template <typename T, typename Compare>
void RedBlackTree<T, Compare>::FixInsertion(node_ptr node) {
  while (get_color(get_parent(node)) == RBTColor::kColorRed) {
    node_ptr uncle;
    auto parent = get_parent(node);
    auto grandparent = get_parent(parent);

    // Отец левый ребенок
    if (parent == get_left(grandparent)) {
      uncle = get_right(grandparent);

      // Есть красный дядя
      if (get_color(uncle) == RBTColor::kColorRed) {
        // Случай 1: Есть красный дядя
        set_color(parent, RBTColor::kColorBlack);
        set_color(uncle, RBTColor::kColorBlack);
        set_color(grandparent, RBTColor::kColorRed);

        node = grandparent;
      } else {
        if (node == get_right(parent)) {
          // Случай 2: node - правый ребенок
          node = parent;
          RotateLeft(node);
        }
        // Случай 3: node - левый ребенок
        set_color(get_parent(node), RBTColor::kColorBlack);
        set_color(get_parent(get_parent(node)), RBTColor::kColorRed);
        RotateRight(get_parent(get_parent(node)));
      }
    } else {
      uncle = get_left(grandparent);

      // Есть красный дядя
      if (get_color(uncle) == RBTColor::kColorRed) {
        // Случай 1: Есть красный дядя
        set_color(parent, RBTColor::kColorBlack);
        set_color(uncle, RBTColor::kColorBlack);
        set_color(grandparent, RBTColor::kColorRed);

        node = grandparent;
      } else {  // Нет дяди
        // node - левый ребеной
        if (node == get_left(get_parent(node))) {
          // Случай 2: node - левый ребенок
          node = get_parent(node);
          RotateRight(node);
        }
        // Случай 3: node - левый ребенок
        set_color(get_parent(node), RBTColor::kColorBlack);
        set_color(get_parent(get_parent(node)), RBTColor::kColorRed);
        RotateLeft(get_parent(get_parent(node)));
      }
    }
  }
  // Восстанавливаем свойство красного корня
  root_->color = RBTColor::kColorBlack;
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::erase(iterator pos) {
  node_ptr del_node = FindNode(*pos);
  if (del_node != nil_ && del_node) {
    EraseNode(del_node);
  }
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::Transplant(node_ptr to_node,
                                          node_ptr from_node) {
  // Замена поддерева с корнем to_node поддеревом с корнем from_node
  if (get_parent(to_node) == nil_) {
    root_ = from_node;
  } else if (to_node == get_left(get_parent(to_node))) {
    set_left(get_parent(to_node), from_node);
  } else {
    set_right(get_parent(to_node), from_node);
  }

  // Обновляем родителя для from_node
  set_parent(from_node, get_parent(to_node));
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::EraseNode(node_ptr node_to_del) {
  node_ptr child = nullptr;
  node_ptr min_node = nullptr;
  RBTColor removed_color = get_color(node_to_del);

  // Если узел имеет менее 2-х детей
  if (get_left(node_to_del) == nil_) {
    child = get_right(node_to_del);
    Transplant(node_to_del, get_right(node_to_del));
  } else if (get_right(node_to_del) == nil_) {
    child = get_left(node_to_del);
    Transplant(node_to_del, get_left(node_to_del));
  } else {
    // Узел имеет 2 детей
    min_node = GetMinNode(get_right(node_to_del));
    removed_color = get_color(min_node);
    child = get_right(min_node);

    if (get_parent(min_node) == node_to_del) {
      set_parent(child, min_node);
    } else {
      Transplant(min_node, get_right(min_node));
      set_right(min_node, get_right(node_to_del));
      set_parent(get_right(min_node), min_node);
    }
    Transplant(node_to_del, min_node);
    set_left(min_node, get_left(node_to_del));
    set_parent(get_left(min_node), min_node);
    set_color(min_node, get_color(node_to_del));
  }

  if (removed_color == RBTColor::kColorBlack) {
    FixErase(child);
  }

  delete node_to_del;
  UpdateNil();
  size_--;
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::FixErase(node_ptr node) {
  while (node != root_ && get_color(node) == RBTColor::kColorBlack) {
    if (node == get_left(get_parent(node))) {
      // Узел - левый потомок своего родителя
      node_ptr brother = get_right(get_parent(node));

      if (get_color(brother) == RBTColor::kColorRed) {
        // Случай 1: Красный брат
        set_color(brother, RBTColor::kColorBlack);
        set_color(get_parent(node), RBTColor::kColorRed);
        RotateLeft(get_parent(node));
        brother = get_right(get_parent(node));
      }

      if (get_color(get_left(brother)) == RBTColor::kColorBlack &&
          get_color(get_right(brother)) == RBTColor::kColorBlack) {
        // Случай 2: Оба потомка брата черные
        set_color(brother, RBTColor::kColorRed);
        node = get_parent(node);
      } else {
        if (get_color(get_right(brother)) == RBTColor::kColorBlack) {
          // Случай 3: Правый потомок брата черный
          set_color(get_left(brother), RBTColor::kColorBlack);
          set_color(brother, RBTColor::kColorRed);
          RotateRight(brother);
          brother = get_right(get_parent(node));
        }
        // Случай 4: Цвета узлов узла, его родителя и левого потомка брата
        //  меняются так, чтобы соответствовать свойствам красно-черного дерева
        set_color(brother, get_color(get_parent(node)));
        set_color(get_parent(node), RBTColor::kColorBlack);
        set_color(get_right(brother), RBTColor::kColorBlack);
        RotateLeft(get_parent(node));
        node = root_;
      }
    } else {
      // Узел - правый потомок своего родителя
      node_ptr brother = get_left(get_parent(node));

      if (get_color(brother) == RBTColor::kColorRed) {
        // Случай 1: Красный брат
        set_color(brother, RBTColor::kColorBlack);
        set_color(get_parent(node), RBTColor::kColorRed);
        RotateRight(get_parent(node));
        brother = get_left(get_parent(node));
      }

      if (get_color(get_left(brother)) == RBTColor::kColorBlack &&
          get_color(get_right(brother)) == RBTColor::kColorBlack) {
        // Случай 2: Оба потомка брата черные
        set_color(brother, RBTColor::kColorRed);
        node = get_parent(node);
      } else {
        if (get_color(get_left(brother)) == RBTColor::kColorBlack) {
          // Случай 3: Левый потомок брата черный
          set_color(get_right(brother), RBTColor::kColorBlack);
          set_color(brother, RBTColor::kColorRed);
          RotateLeft(brother);
          brother = get_left(get_parent(node));
        }
        // Случай 4: Цвета узлов узла, его родителя и правого потомка брата
        //  меняются так, чтобы соответствовать свойствам красно-черного дерева
        set_color(brother, get_color(get_parent(node)));
        set_color(get_parent(node), RBTColor::kColorBlack);
        set_color(get_left(brother), RBTColor::kColorBlack);
        RotateRight(get_parent(node));
        node = root_;
      }
    }
  }
  // Устанавливаем цвет корня в черный
  set_color(node, RBTColor::kColorBlack);
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::node_ptr RedBlackTree<T, Compare>::CopyTree(
    const node_ptr src_node, node_ptr parent, const node_ptr oth_nil) {
  if (src_node == oth_nil) {
    return nil_;
  }

  Node *new_node = new Node(get_data(src_node), get_color(src_node));
  set_parent(new_node, parent);
  size_++;

  node_ptr left = CopyTree(get_left(src_node), new_node, oth_nil);
  node_ptr right = CopyTree(get_right(src_node), new_node, oth_nil);
  set_left(new_node, left);
  set_right(new_node, right);

  return new_node;
}

template <typename T, typename Compare>
RedBlackTree<T, Compare>::RedBlackTree()
    : nil_(new Node()), root_(nil_), size_(0U) {
  set_left(root_, nil_);
  set_right(root_, nil_);
}

template <typename T, typename Compare>
RedBlackTree<T, Compare>::RedBlackTree(RedBlackTree &&other) noexcept
    : nil_(other.nil_),
      root_(other.root_),
      size_(other.size_),
      cmp_(other.cmp_) {
  other.nil_ = new Node();
  other.root_ = other.nil_;
  other.size_ = 0U;
}

template <typename T, typename Compare>
RedBlackTree<T, Compare>::RedBlackTree(
    std::initializer_list<value_type> const &items)
    : RedBlackTree() {
  for (auto item : items) {
    insert(item);
  }
}

template <typename T, typename Compare>
RedBlackTree<T, Compare>::~RedBlackTree() {
  Clear(root_);
  set_parent(nil_, nullptr);
  set_left(nil_, nullptr);
  set_right(nil_, nullptr);
  delete nil_;
}

template <typename T, typename Compare>
class RedBlackTree<T, Compare>::RedBlackTreeIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type *;
  using reference = value_type &;

  RedBlackTreeIterator() = delete;
  RedBlackTreeIterator(node_ptr p, RedBlackTree *tree) : cur_(p), tree_(tree) {}
  ~RedBlackTreeIterator() = default;

  reference operator*() const noexcept { return cur_->data; }

  pointer operator->() const noexcept { return &(cur_->data); }

  iterator &operator++() noexcept {
    cur_ = tree_->GetNext(cur_);
    return *this;
  }

  iterator operator++(int) noexcept {
    iterator tmp(cur_, tree_);
    ++(*this);
    return tmp;
  }

  iterator &operator--() noexcept {
    cur_ = tree_->GetPrev(cur_);
    return *this;
  }

  iterator operator--(int) noexcept {
    iterator tmp(cur_, tree_);
    --(*this);
    return tmp;
  }

  friend bool operator==(const iterator &a, const iterator &b) noexcept {
    return a.cur_ == b.cur_;
  }
  friend bool operator!=(const iterator &a, const iterator &b) noexcept {
    return a.cur_ != b.cur_;
  }

 private:
  node_ptr cur_{};
  RedBlackTree *tree_;
};

template <typename T, typename Compare>
class RedBlackTree<T, Compare>::RedBlackTreeConstIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = const T;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type *;
  using reference = value_type &;

  RedBlackTreeConstIterator() = delete;
  RedBlackTreeConstIterator(node_ptr p, const RedBlackTree *tree)
      : cur_(p), tree_(tree) {}
  ~RedBlackTreeConstIterator() = default;

  reference operator*() const noexcept { return cur_->data; }

  pointer operator->() const noexcept { return &(cur_->data); }

  const_iterator &operator++() noexcept {
    cur_ = tree_->GetNext(cur_);
    return *this;
  }

  const_iterator operator++(int) noexcept {
    const_iterator tmp(cur_, tree_);
    ++(*this);
    return tmp;
  }

  const_iterator &operator--() noexcept {
    cur_ = tree_->GetPrev(cur_);
    return *this;
  }

  const_iterator operator--(int) noexcept {
    const_iterator tmp(cur_, tree_);
    --(*this);
    return tmp;
  }

  friend bool operator==(const const_iterator &a,
                         const const_iterator &b) noexcept {
    return a.cur_ == b.cur_;
  }
  friend bool operator!=(const const_iterator &a,
                         const const_iterator &b) noexcept {
    return a.cur_ != b.cur_;
  }

 private:
  node_ptr cur_{};
  const RedBlackTree *tree_;
};

template <typename T, typename Compare>
RedBlackTree<T, Compare> &RedBlackTree<T, Compare>::operator=(
    const RedBlackTree &other) {
  if (root_ == other.root_) {
    return *this;
  }
  Clear(root_);
  root_ = CopyTree(other.root_, nil_, other.nil_);
  size_ = other.size_;
  cmp_ = other.cmp_;
  UpdateNil();

  return *this;
}

template <typename T, typename Compare>
RedBlackTree<T, Compare> &RedBlackTree<T, Compare>::operator=(
    RedBlackTree &&other) noexcept {
  if (root_ == other.root_) {
    return *this;
  }

  Clear(root_);
  delete (nil_);

  root_ = other.root_;
  nil_ = other.nil_;
  size_ = other.size_;
  cmp_ = other.cmp_;
  UpdateNil();

  other.nil_ = new Node();
  other.root_ = other.nil_;
  other.size_ = 0U;

  return *this;
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::swap(RedBlackTree &other) {
  std::swap(root_, other.root_);
  std::swap(nil_, other.nil_);
  std::swap(size_, other.size_);
  std::swap(cmp_, other.cmp_);
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::clear() noexcept {
  Clear(root_);
  root_ = nil_;
  size_ = 0U;
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::merge(RedBlackTree &other_tree) {
  if (other_tree.root_ == other_tree.nil_) return;

  iterator begin = other_tree.begin();
  iterator end = other_tree.end();
  while (begin != end) {
    auto res = insert(*begin);
    if (res.second) {
      other_tree.erase(begin++);
    } else {
      ++begin;
    }
  }
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::node_ptr
RedBlackTree<T, Compare>::CreateNode(const value_type &value, node_ptr parent) {
  node_ptr curr = new Node(value);
  set_left(curr, nil_);
  set_right(curr, nil_);
  set_parent(curr, parent);
  return curr;
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::node_ptr RedBlackTree<T, Compare>::FindNode(
    const key_type &value) const {
  node_ptr current_node = root_;

  while (current_node != nil_) {
    if (cmp_(get_data(current_node), value)) {
      current_node = get_right(current_node);
    } else if (cmp_(value, get_data(current_node))) {
      current_node = get_left(current_node);
    } else {
      break;  // for optimization
    }
  }
  return current_node;
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::size_type RedBlackTree<T, Compare>::count(
    const key_type &key) const {
  auto range = equal_range(key);
  size_type count = 0;
  for (auto it = range.first; it != range.second; ++it) {
    count++;
  }
  return count;
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::iterator
RedBlackTree<T, Compare>::lower_bound(const key_type &key) {
  node_ptr search_node = root_;
  node_ptr result = nil_;
  while (search_node != nil_) {
    if (!cmp_(get_data(search_node), key)) {
      result = search_node;
      search_node = get_left(search_node);
    } else {
      search_node = get_right(search_node);
    }
  }
  return iterator(result, this);
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::iterator
RedBlackTree<T, Compare>::upper_bound(const key_type &key) {
  node_ptr search_node = root_;
  node_ptr result = nil_;
  while (search_node != nil_) {
    if (cmp_(key, get_data(search_node))) {
      result = search_node;
      search_node = get_left(search_node);
    } else {
      search_node = get_right(search_node);
    }
  }
  return iterator(result, this);
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::const_iterator
RedBlackTree<T, Compare>::lower_bound(const key_type &key) const {
  node_ptr search_node = root_;
  node_ptr result = nil_;
  while (search_node != nil_) {
    if (!cmp_(get_data(search_node), key)) {
      result = search_node;
      search_node = get_left(search_node);
    } else {
      search_node = get_right(search_node);
    }
  }
  return const_iterator(result, this);
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::const_iterator
RedBlackTree<T, Compare>::upper_bound(const key_type &key) const {
  node_ptr search_node = root_;
  node_ptr result = nil_;
  while (search_node != nil_) {
    if (cmp_(key, get_data(search_node))) {
      result = search_node;
      search_node = get_left(search_node);
    } else {
      search_node = get_right(search_node);
    }
  }
  return const_iterator(result, this);
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::node_ptr
RedBlackTree<T, Compare>::GetMinNode(node_ptr node) const {
  while (node != nil_ && get_left(node) != nil_) {
    node = get_left(node);
  }
  return node;
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::node_ptr
RedBlackTree<T, Compare>::GetMaxNode(node_ptr node) const {
  while (node != nil_ && get_right(node) != nil_) {
    node = get_right(node);
  }
  return node;
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::node_ptr RedBlackTree<T, Compare>::GetNext(
    const node_ptr node) const {
  node_ptr next_node = nil_;
  node_ptr parent = get_parent(node);
  // Поиск наименьшего среди детей, поскольку он справа => больше своего
  // родителя
  next_node = GetMinNode(get_right(node));

  // Проверяем не дошли ли мы до максимального значения.
  if (next_node == nil_ && node != nil_->left) {
    if (node == get_left(parent)) {
      next_node = parent;
    } else if (next_node == get_right(node)) {
      next_node = node;
      // Поднимаемся до родителя пока мы правый ребенок и наши значения равны
      while (get_right(parent) == next_node) {
        next_node = parent;
        parent = get_parent(next_node);
      }
      // Идем до родителя (мы слева от него)
      next_node = parent;
    }
  }
  return next_node;
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::node_ptr RedBlackTree<T, Compare>::GetPrev(
    const node_ptr node) const {
  if (node == nil_) {
    return GetMaxNode(root_);
  }
  node_ptr next_node = nil_;
  node_ptr parent = get_parent(node);
  // Поиск наибольшего среди детей, поскольку он слева => меньше своего родителя
  next_node = GetMaxNode(get_left(node));

  // Проверяем не дошли ли мы до минимального значения.
  if (next_node == nil_ && node != nil_->right) {
    if (node == get_right(parent)) {
      next_node = parent;
    } else if (next_node == get_left(node)) {
      next_node = node;
      // Поднимаемся до родителя пока мы правый ребенок и наши значения равны
      while (get_left(parent) == next_node) {
        next_node = parent;
        parent = get_parent(next_node);
      }
      // Идем до родителя (мы слева от него)
      next_node = parent;
    }
  }
  return next_node;
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::Clear(node_ptr node) {
  if (node != nil_) {
    Clear(get_left(node));
    Clear(get_right(node));
    delete node;
  }
}

}  // namespace s21

#endif  // SRC_S21_MINOR_DATA_STRUCT_S21_RB_TREE_H_
