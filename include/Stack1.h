// Copyright 2022 VladislavRz <rzhevskii_vladislav@mail.ru>

#include "Node.h"
#include <utility>
#include <stdexcept>

#ifndef LAB5_STACK_H
#define LAB5_STACK_H

template <typename T>
class Stack_1 {
 public:
  Stack_1();
  explicit Stack_1(T&& value);
  ~Stack_1();
  Stack_1(const Stack_1& value) = delete;
  Stack_1(Stack_1&& stack) noexcept;

 public:
  Stack_1& operator=(const Stack_1& value) = delete;
  Stack_1& operator=(Stack_1&& stack) noexcept;

 public:
  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;

 private:
  Node<T> *_top;
};

template <typename T>
Stack_1<T>::Stack_1()
    :_top(nullptr) {}

template <typename T>
Stack_1<T>::Stack_1(T&& value) {
  _top = new Node<T>;
  _top->ptr = nullptr;
  _top->data = std::forward<T>(value);
}

template <typename T>
Stack_1<T>::Stack_1(Stack_1&& stack) noexcept {
  _top = new Node<T>;
  _top->ptr = std::move(stack._top->ptr);

  if (std::is_move_assignable<T>::value) {
    _top->data = std::move(stack._top->data);
  } else {
    _top->data = stack._top->data;
  }

  delete stack._top;
  stack._top = nullptr;
}
template <typename T>
Stack_1<T>::~Stack_1() {
  while (_top != nullptr) {
    this->pop();
  }
}

template <typename T>
Stack_1<T>& Stack_1<T>::operator=(Stack_1&& stack)  noexcept {
  if (&stack == this) {
    return *this;
  }

  while (_top != nullptr) {
    this->pop();
  }

  _top = new Node<T>;
  _top->ptr = std::move(stack._top->ptr);

  if (std::is_move_assignable<T>::value) {
    _top->data = std::move(stack._top->data);
  } else {
    _top->data = stack._top->data;
  }

  delete stack._top;
  stack._top = nullptr;

  return *this;
}

template <typename T>
void Stack_1<T>::push(T&& value) {
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
void Stack_1<T>::push(const T& value) {
  if (_top == nullptr) {
    _top = new Node<T>;
    _top->ptr = nullptr;
    _top->data = value;
  } else {
    Node<T>* tmp = new Node<T>;
    tmp->ptr = _top;
    tmp->data = value;
    _top = tmp;
  }
}

template <typename T>
void Stack_1<T>::pop() {
  if (_top != nullptr) {
    Node<T>* tmp = _top->ptr;

    delete _top;
    _top = tmp;
  }
}

template <typename T>
const T& Stack_1<T>::head() const {
  if (_top == nullptr) {
    throw std::runtime_error("stack is empty");
  }
  return _top->data;
}

#endif  // LAB5_STACK_H
