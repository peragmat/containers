#ifndef SRC_S21_CONTAINERS_S21_CONTAINERS_S21_LIST_H_
#define SRC_S21_CONTAINERS_S21_CONTAINERS_S21_LIST_H_

#include <iostream>

using namespace std;

namespace s21 {
template <typename T>
class List {
  class Node;
  class ListIterator;
  class ListConstIterator;

 public:
  using value_type =
      T;  // defines the type of an element (T is template parameter)
  using reference = T &;  // defines the type of the reference to an element
  using const_reference =
      const T &;                  // defines the type of the constant reference
  using iterator = ListIterator;  // internal class ListIterator<T> defines the
                                  // type for iterating through the container
  using const_iterator =
      ListConstIterator;  // internal class ListConstIterator<T> defines the
                          // constant type for iterating through the containe
  using size_type = std::size_t;  // size_t defines the type of the container
                                  // size (standard type is size_t)
  using allocator = class std::allocator<T>;
  using allocator_node = typename std::allocator_traits<
      allocator>::rebind_alloc<s21::List<T>::Node>;

  List();             // default constructor, creates empty list 
  List(size_type n);  // parameterized constructor, creates the list of size n
  List(std::initializer_list<value_type> const &items);
  List(const List &l);      // copy constructor
  List(List &&l) noexcept;  // move constructor
  ~List();                  // destructor
  List &operator=(
      List const &l);  // assignment operator overload for moving object
  List &operator=(List &&l) noexcept;

  const_reference front() const noexcept {
    return head_->value_;
  };  // access the first element
  const_reference back() const noexcept {
    return tail_->value_;
  };  // access the last element

  iterator begin() const noexcept {
    return iterator(head_);
  };  // returns an iterator to the beginning
  iterator end() const noexcept {
    return iterator(zero_);
  };  // returns an iterator to the end
  // iterator end(){return iterator(tail_->pNext_);}; // returns an iterator to
  // the end

  const_iterator cbegin() const noexcept {
    return const_iterator(zero_->pNext_);
  };  // returns an const_iterator to the beginning
  const_iterator cend() const noexcept {
    return const_iterator(zero_);
  };  // returns an iterator to the end

  bool empty() const noexcept;  // checks whether the container is empty
  size_type size() const noexcept {
    return size_;
  };  // returns the number of elements
  size_type max_size() const noexcept { return alloc_n.max_size(); };

  void clear();  // clears the contents
  iterator insert(
      iterator pos,
      const_reference value);  // inserts element into concrete pos and returns
                               // the iterator that points to the new element
  void erase(iterator pos);    // erases element at pos

  void push_back(const_reference value_);   // adds an element to the end
  void pop_back();                          // removes the last element
  void push_front(const_reference value_);  // adds an element to the head
  void pop_front();                         // removes the first element
  void swap(List &other);
  void merge(List &other);
  void splice(const_iterator pos,
              List &other);  // возможно надо сделать перегрузку
  void reverse() noexcept;  // reverses the order of the elements
  void unique();            // removes consecutive duplicate elements
  void sort();              // sorts the elements

  T &operator[](const int index) const;
  void show() noexcept;

  template <class... Args>
  iterator insert_many(const_iterator pos,
                       Args &&...args);  // inserts new elements into the
                                         // container directly before pos

  template <class... Args>
  void insert_many_front(
      Args &&...args);  // appends new elements to the top of the container

  template <class... Args>
  void insert_many_back(
      Args &&...args);  // appends new elements to the end of the container

 private:
  class Node {
   public:
    Node *pNext_;
    Node *pPrev_;
    T value_;
    Node(T value = T(), Node *pPrev = nullptr, Node *pNext = nullptr) {
      value_ = value;
      pNext_ = pNext;
      pPrev_ = pPrev;
    }
  };

  class ListIterator {
    using value_type = T;
    using size_type = size_t;
    using Node = typename List<T>::Node;
    using reference = T &;  // defines the type of the reference to an element
    using const_reference = const T &;

   public:
    ListIterator() { iterNode_ = nullptr; }
    ListIterator(ListIterator const &other) : iterNode_(other.iterNode_){};
    ListIterator(ListIterator &&other) noexcept {
      if (*this != other) {
        iterNode_ = other.iterNode_;
        other.iterNode_ = nullptr;
      }
    };

    ListIterator(Node *current) : iterNode_(current){};

    ListIterator operator=(ListIterator const &other) {
      iterator it = other;
      return it;
    };

    ListIterator &operator++() {
      iterNode_ = iterNode_->pNext_;
      return *this;
    };  // префексная форма

    ListIterator operator++(int) {
      ListIterator it = iterNode_;
      iterNode_ = iterNode_->pNext_;
      return it;
    };  // постфиксная форма

    ListIterator &operator--() {
      iterNode_ = iterNode_->pPrev_;
      return *this;
    };  // префексная форма

    ListIterator operator--(int) {
      ListIterator it = iterNode_;
      iterNode_ = iterNode_->pPrev_;
      return it;
    };  // постфиксная форма

    reference operator*() const {
      if (iterNode_ == nullptr) {
        throw invalid_argument("No value");
      }
      return iterNode_->value_;
    }
    bool operator==(const ListIterator &other) const noexcept {
      return iterNode_ == other.iterNode_;
    }  // проверяем указатели а не ноды
    bool operator!=(ListIterator &other) const noexcept {
      return iterNode_ != other.iterNode_;
    }
    bool operator!=(const ListIterator &other) const noexcept {
      return iterNode_ != other.iterNode_;
    }
    // ListIterator operator->() {return iterNode_;

   private:
    Node *iterNode_;
    friend class List<T>;
  };

  class ListConstIterator {
    using value_type = T;
    using size_type = size_t;
    using Node = typename List<T>::Node;
    using reference = T &;  // defines the type of the reference to an element
    using const_reference = const T &;

   public:
    ListConstIterator() { iterNode_ = nullptr; }
    ListConstIterator(ListConstIterator const &other)
        : iterNode_(other.iterNode_){};
    ListConstIterator(ListConstIterator &&other) noexcept {
      if (*this != other) {
        iterNode_ = other.iterNode_;
        other.iterNode_ = nullptr;
      }
    };

    ListConstIterator(Node *current) : iterNode_(current){};
    ListConstIterator &operator++() {
      iterNode_ = iterNode_->pNext_;
      return *this;
    };  // префексная форма

    ListConstIterator operator++(int) {
      ListConstIterator it = iterNode_;
      iterNode_ = iterNode_->pNext_;
      return it;
    }  // постфиксная форма

    ListConstIterator &operator--() {
      iterNode_ = iterNode_->pPrev_;
      return *this;
    };  // префексная форма

    ListConstIterator operator--(int) {
      ListConstIterator it = iterNode_;
      iterNode_ = iterNode_->pPrev_;
      return it;
    };  // постфиксная форма

    reference operator*() const { return iterNode_->value_; }
    bool operator==(const ListConstIterator &other) const {
      return iterNode_ == other.iterNode_;
    }  // проверяем указатели а не ноды
    bool operator!=(const ListConstIterator &other) const {
      return iterNode_ != other.iterNode_;
    }
    // ListConstIterator operator->() {return iterNode_;}

   private:
    Node *iterNode_;
    friend class List<T>;
  };

  size_t size_;
  Node *head_;
  Node *tail_;
  Node *zero_;
  allocator_node alloc_n;
};

template <typename T>
List<T>::List() {
  zero_ = new Node(value_type(), zero_, zero_);
  head_ = tail_ = zero_;
  size_ = 0;

  zero_->pNext_ = head_;
  zero_->pPrev_ = tail_;
}

template <typename T>
List<T>::List(size_type n) : List() {
  for (size_type i = 0; i < n; i++) {
    push_back(value_type());
  }
}

template <typename value_type>
List<value_type>::List(std::initializer_list<value_type> const &items)
    : List() {
  for (auto element : items) {
    push_back(element);
  }
}

template <typename T>
List<T>::List(const List &l) : List() {
  // cout << "RJGB" << endl;
  // cout << "RJGB_x0 " << l.head_->value_ << endl;
  clear();

  Node *current = l.head_;
  for (size_t i = 0; i < l.size_; i++) {
    push_back(current->value_);
    current = current->pNext_;
  }
  // operator=(l);
}

template <typename T>
List<T>::List(List &&l) noexcept : List() {
  List();
  std::swap(head_, l.head_);
  std::swap(tail_, l.tail_);
  std::swap(size_, l.size_);
  std::swap(zero_, l.zero_);
}

template <typename T>
List<T>::~List() {
  clear();
  delete zero_;
}
template <typename T>
List<T> &List<T>::operator=(List const &l) {
  clear();
  // cout << "RJGB_o" << endl;
  Node *current = l.head_;
  for (size_t i = 0; i < l.size_; i++) {
    push_back(current->value_);
    current = current->pNext_;
  }
  // cout << "RJGB_x " << l.head_->value_ << endl;
  // (l);

  return *this;
}

template <typename T>
inline List<T> &List<T>::operator=(List &&l) noexcept {
  std::swap(head_, l.head_);
  std::swap(tail_, l.tail_);
  std::swap(size_, l.size_);
  std::swap(zero_, l.zero_);
  l.clear();
  return *this;
}

template <typename T>
inline bool List<T>::empty() const noexcept {
  return head_ == zero_;
}

template <typename T>
void List<T>::clear() {
  while (head_ != zero_) {
    Node *temp = head_;
    head_ = head_->pNext_;
    delete temp;  // Освобождаем память
  }
  size_ = 0;
  zero_->value_ = value_type();
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos,
                                           const_reference value) {
  // Создаем новый узел с указанным значением и указателями на предыдущий и
  // следующий узлы
  Node *current = new Node(value, pos.iterNode_->pPrev_, pos.iterNode_);

  // Обновляем указатели предыдущего и следующего узлов для соединения нового
  // узла
  pos.iterNode_->pPrev_->pNext_ = current;
  pos.iterNode_->pPrev_ = current;

  if (head_ == zero_) {
    zero_->pNext_ = zero_->pPrev_ = current;
    current->pNext_ = current->pPrev_ = zero_;
    head_ = tail_ = current;
  } else if (pos == begin()) {
    head_ = current;
    zero_->pNext_ = current;
  } else if (pos == end()) {
    current->pPrev_ = tail_;
    tail_->pNext_ = current;
    tail_ = current;
    zero_->pPrev_ = current;
    tail_->pNext_ = zero_;
  }
  size_++;
  zero_->value_ = size_;
  return pos;
}

template <typename T>
void List<T>::erase(iterator pos) {
  Node *tmp = pos.iterNode_;
  pos.iterNode_->pPrev_->pNext_ = pos.iterNode_->pNext_;
  pos.iterNode_->pNext_->pPrev_ = pos.iterNode_->pPrev_;
  if (tmp == zero_) {
    return;
  } else if (tmp->pPrev_ == zero_ && tmp->pNext_ == zero_) {
    head_ = tail_ = zero_;
    zero_->pNext_ = zero_;
    zero_->pPrev_ = zero_;
  } else if (tmp->pPrev_ == zero_) {  // head
    head_ = pos.iterNode_->pNext_;
    head_->pPrev_ = zero_;
    zero_->pNext_ = head_;
  } else if (tmp->pNext_ == zero_) {  // tail
    tail_ = pos.iterNode_->pPrev_;
    tail_->pNext_ = zero_;
    zero_->pPrev_ = tail_;
  }
  pos++;

  delete tmp;
  size_--;
  zero_->value_ = size_;
}

template <typename T>
void List<T>::pop_front() {
  if (size_ > 0) {
    erase(zero_->pNext_);
  } else {
    throw invalid_argument("Empty list");
  }
}

template <typename T>
void List<T>::swap(List &other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
  std::swap(zero_, other.zero_);

  // Node *cur_zero_= new Node (value_type(), zero_->pPrev_, zero_->pNext_);
  // cur_zero_->value_ = zero_->value_;
  // head_= other.head_;
  // tail_ = other.tail_;
  // size_ = other.size_;
  // zero_ = other.zero_;
  // zero_->value_ = other.zero_->value_;

  // other.head_= cur_zero_->pNext_;
  // other.tail_ = cur_zero_->pPrev_;
  // other.size_ = cur_zero_->value_;
  // other.zero_ = cur_zero_;
  // other.zero_->value_ = cur_zero_->value_;

  // other.zero_->pPrev_ = other.tail_;
  // other.zero_->pNext_ = other.head_;
  // other.tail_->pNext_ = other.zero_;
  // other.head_->pPrev_ = other.zero_;
}

template <typename T>
void List<T>::merge(List &other) {
  auto it = begin();

  if (size_ > 0) {
    for (iterator it2 = other.begin(); it2 != other.end();) {
      if (*it <= *it2) {
        it++;
      } else {
        insert(it, *it2);
        other.erase(it2);
        it2++;
      }
    }
  } else {
    swap(other);
  }
}

template <typename T>
void List<T>::splice(const_iterator pos, List &other) {
  for (auto i = other.begin(); i != other.end(); ++i) {
    insert(iterator(pos.iterNode_), *i);
  }
  other.clear();
}

template <typename T>
inline void List<T>::reverse() noexcept {
  Node *tmp = head_;
  for (auto it = begin(); it != end(); it--) {
    std::swap(it.iterNode_->pNext_, it.iterNode_->pPrev_);
  }
  std::swap(zero_->pNext_, zero_->pPrev_);
  head_ = tail_;
  tail_ = tmp;

  // ______________
  //     List <T> tmp_l (*this);
  //     Node *tmp = tmp_l.head_;
  //     clear();
  //     for (int i = 0; i < tmp_l.size_; i++){
  //          push_front(tmp->value_);
  //         tmp = tmp->pNext_;
  //     }

  // __________

  //     head_= tmp->tail_;
  //            if(index == 0){
  //             push_front(T value);
  //         } else {
  //             Node<T> *tmp = head_;
  //             for (int i = 0; i < size_ && i < index - 1; i++)
  //             {
  //                 tmp = tmp->pNext_;
  //             }
  //             Node<T> *newNode = new Node<T>(value, tmp);
  //             tmp->pNext_ = newNode;
  //         }
  //         size_++;
}

template <typename T>
inline void List<T>::unique() {
  // iterator tmp;
  Node *prev = new Node(head_->value_, nullptr, nullptr);
  Node *temp = head_->pNext_;
  for (; temp != tail_->pNext_; temp = temp->pNext_) {
    if (prev->value_ == temp->value_) {
      iterator it = temp->pPrev_;
      erase(it);
    } else {
      prev->value_ = temp->value_;
    }
  }
  delete prev;
}

template <typename T>
inline void List<T>::sort() {
  if (!this->empty()) {
    for (const_iterator it1 = cbegin(); it1 != cend(); it1++) {
      for (const_iterator it2 = cbegin(); it2 != --cend(); it2++) {
        if (it2.iterNode_->value_ > it2.iterNode_->pNext_->value_) {
          std::swap(it2.iterNode_->value_, it2.iterNode_->pNext_->value_);
        }
      }
    }
  }
}

template <typename T>
inline void List<T>::push_back(const_reference value) {
  insert(++iterator(tail_), value);

  // cout << "Create NODE" << endl; // Альтернатива
  // Node *current = new Node(value, zero_, zero_);
  // if(head_ == zero_){
  //     zero_->pNext_ = zero_->pPrev_ = current;
  //     current->pNext_ = current->pPrev_ = zero_;
  //     head_= tail_ = current;
  // } else {
  //     current->pPrev_ = tail_;
  //     tail_->pNext_ = current;
  //     tail_ = current;
  //     zero_->pPrev_ = tail_;
  //     zero_->value_ = size_ + 1;
  // }
  // size_++;
}

template <typename T>
inline void List<T>::push_front(const_reference value) {
  insert(iterator(head_), value);

  // Node *current = new Node(value, zero_, zero_); // Альтернатива
  // if(head_ == zero_){
  //     zero_->pNext_ = zero_->pPrev_ = current;
  //     current->pNext_ = current->pPrev_ = zero_;
  //     head_ = tail_ = current;
  // } else {
  //     current->pNext_ = head_;
  //     head_->pPrev_ = current;
  //     head_ = current;
  //     zero_->pNext_ = head_;
  //     zero_->value_ = size_ + 1;
  // }
  // size_++;
}

template <typename T>
inline void List<T>::pop_back() {
  if (size_ > 0) {
    erase(zero_->pPrev_);
  } else {
    throw invalid_argument("Empty list");
  }
}

template <typename T>
T &List<T>::operator[](const int index) const {
  int counter = 0;
  Node *current = this->head_;
  while (current != zero_) {
    if (counter == index) {
      return current->value_;
    }
    current = current->pNext_;
    counter++;
  }
  throw std::out_of_range("Index out of bounds");
}

template <typename T>
inline void List<T>::show() noexcept {
  Node *tmp = head_;
  for (int i = 0; i < size_; i++) {
    cout << tmp->value_ << " x ";
    tmp = tmp->pNext_;
  }
  cout << "SIZE s21: " << size() << endl;
}

// BONUSE
template <typename T>
template <class... Args>
typename List<T>::iterator List<T>::insert_many(const_iterator pos,
                                                Args &&...args) {
  iterator it(pos.iterNode_);
  for (auto value : {std::forward<Args>(args)...}) {
    insert(it, value);
  }

  return it;
}

template <typename T>
template <class... Args>
inline void List<T>::insert_many_front(Args &&...args) {
  insert_many(cbegin(), std::forward<Args>(args)...);

  // iterator it (head_);
  // for (auto value : {std::forward<Args>(args)...}) {
  //     insert(it, value);
  // }
}

template <typename T>
template <class... Args>
inline void List<T>::insert_many_back(Args &&...args) {
  insert_many(cend(), std::forward<Args>(args)...);

  // iterator it (tail_->pNext_);
  // for (auto value : {std::forward<Args>(args)...}) {
  //     insert(it, value);
  // }
}
};      // namespace s21
#endif  // SRC_S21_CONTAINERS_S21_CONTAINERS_S21_LIST_H_
