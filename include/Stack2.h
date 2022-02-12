// Copyright 2022 VladislavRz <rzhevskii_vladislav@mail.ru>

#include "Node.h"
#include <type_traits>
#include <utility>
#include <stdexcept>

#ifndef LAB5_STACK2_H
#define LAB5_STACK2_H

template <typename T>
class Stack_2 {
 public:
  Stack_2();
  explicit Stack_2(T&& value);
  ~Stack_2();
  Stack_2(const Stack_2& value) = delete;
  Stack_2(Stack_2&& stack) noexcept;

 public:
  Stack_2& operator=(const Stack_2& value) = delete;
  Stack_2& operator=(Stack_2&& stack) noexcept;

 public:
  template <typename ... Args>
  void push_emplace(Args&& ... value);
  void push(T&& value);
  const T& head() const;
  void pop();

 private:
  Node<T> *_top;
};

template <typename T>
Stack_2<T>::Stack_2() {
  if (std::is_move_assignable<T>::value &&
      std::is_move_constructible<T>::value &&
      !std::is_copy_assignable<T>::value &&
      !std::is_copy_constructible<T>::value) {
    _top = nullptr;
  } else {
    throw std::runtime_error("incorrect type for initialization");
  }
}

template <typename T>
Stack_2<T>::Stack_2(T&& value) {
  if (std::is_move_assignable<T>::value &&
      std::is_move_constructible<T>::value &&
      !std::is_copy_assignable<T>::value &&
      !std::is_copy_constructible<T>::value) {
    _top = new Node<T>;
    _top->ptr = nullptr;
    _top->data = std::forward<T>(value);
  } else {
    throw std::runtime_error("incorrect type for initialization");
  }
}

template <typename T>
Stack_2<T>::Stack_2(Stack_2&& stack) noexcept {
  _top = new Node<T>;
  _top->ptr = std::move(stack._top->ptr);
  _top->data = std::move(stack._top->data);

  delete stack._top;
  stack._top = nullptr;
}

template <typename T>
Stack_2<T>::~Stack_2() {
  while (_top != nullptr) {
    this->pop();
  }
}

template <typename T>
Stack_2<T>& Stack_2<T>::operator=(Stack_2&& stack) noexcept {
  if (&stack == this) {
    return *this;
  }

  while (_top != nullptr) {
    this->pop();
  }

  _top = new Node<T>;
  _top->ptr = std::move(stack._top->ptr);
  _top->data = std::move(stack._top->data);

  delete stack._top;
  stack._top = nullptr;

  return *this;
}

template <typename T>
template <typename ... Args>
void Stack_2<T>::push_emplace(Args&& ... value) {
  if (_top == nullptr) {
    _top = new Node<T>;
    _top->ptr = nullptr;
    T new_t = T(std::forward<Args>(value) ...);
    _top->data = std::move(new_t);
  } else {
    Node<T>* tmp = new Node<T>;
    tmp->ptr = _top;
    T new_t = T(std::forward<Args>(value) ...);
    tmp->data = std::move(new_t);
    _top = tmp;
  }
}

template <typename T>
void Stack_2<T>::push(T&& value) {
  if (_top == nullptr) {
    _top = new Node<T>;
    _top->ptr = nullptr;
    _top->data = std::forward<T>(value);
  } else {
    Node<T>* tmp = new Node<T>;
    tmp->ptr = _top;
    tmp->data = std::forward<T>(value);
    _top = tmp;
  }
}

template <typename T>
const T& Stack_2<T>::head() const {
  if (_top == nullptr) {
     throw std::runtime_error("stack is empty");
  }
  return _top->data;
}
template <typename T>
void Stack_2<T>::pop() {
  if (_top != nullptr) {
    Node<T>* tmp = _top->ptr;

    delete _top;
    _top = tmp;
  }
}

#endif  // LAB5_STACK2_H
