// Copyright 2022 VladislavRz <rzhevskii_vladislav@mail.ru>

#include <gtest/gtest.h>

#include "Stack1.h"
#include "Stack2.h"

class TestClass {
 public:
  TestClass()
      :_a(0)
      ,_b(0)
      ,_c(' ')
      ,_d(false){}

  TestClass(int a, double b, char c, bool d)
      :_a(a)
      ,_b(b)
      ,_c(c)
      ,_d(d){}

  ~TestClass() = default;
  TestClass(const TestClass& a) = delete;
  TestClass(TestClass&&) = default;
  TestClass& operator =(TestClass&& a) = default;
  TestClass& operator =(const TestClass& a) = delete;

  int get_a() const { return _a; }
  double get_b() const { return _b; }
  char get_c() const { return _c; }
  bool get_d() const { return _d; }

 private:
  int _a;
  double _b;
  char _c;
  bool _d;
};

TEST(Stack_1, Constructors) {
  Stack_1<int> s1(10);
  EXPECT_EQ(s1.head(), 10);
  Stack_1<int> s2(std::move(s1));
  EXPECT_EQ(s2.head(), 10);
  Stack_1<int> s3;
  EXPECT_THROW(s3.head(), std::runtime_error);
  s3 = std::move(s2);
  EXPECT_EQ(s3.head(), 10);
}

TEST(Stack_1, Methods) {
  Stack_1<double> s1(1.5);
  s1.push(2.5);
  EXPECT_EQ(s1.head(), 2.5);
  s1.push(3.5);
  EXPECT_EQ(s1.head(), 3.5);

  double p = 4.5;
  s1.push(p);
  EXPECT_EQ(s1.head(), 4.5);
  s1.pop();
  EXPECT_EQ(s1.head(), 3.5);
}

TEST(Stack_2, Constructors) {
  EXPECT_THROW(Stack_2<int> s1, std::runtime_error);
  TestClass p(1, 1.0, '1', true);
  Stack_2<TestClass> s1(std::move(p));
  EXPECT_EQ(s1.head().get_a(), 1);
  Stack_2<TestClass> s2(std::move(s1));
  EXPECT_EQ(s2.head().get_b(), 1.0);
  Stack_2<TestClass> s3;
  EXPECT_THROW(s3.head(), std::runtime_error);
  s3 = std::move(s2);
  EXPECT_EQ(s3.head().get_c(), '1');
}

TEST(Stack_2, Methods) {
  TestClass p1(10, 10.0, 'A', true);
  TestClass p2(20, 20.0, 'B', false);
  Stack_2<TestClass> s1(std::move(p1));
  s1.push(std::move(p2));
  EXPECT_EQ(s1.head().get_a(), 20);
  s1.push_emplace(30, 30.0, 'C', true);
  EXPECT_EQ(s1.head().get_a(), 30);
  EXPECT_EQ(s1.head().get_b(), 30.0);
  EXPECT_EQ(s1.head().get_c(), 'C');
  EXPECT_EQ(s1.head().get_d(), true);
  s1.pop();
  EXPECT_EQ(s1.head().get_a(), 20);
}