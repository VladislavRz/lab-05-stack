#include "Stack1.h"
#include "Stack2.h"
#include <iostream>

int main() {
  Stack_1<int> s1(1);
  std::cout << "After create s1: " << s1.head() << std::endl;
  s1.push(2);
  std::cout << "After push: " << s1.head() << std::endl;
  s1.push(3);
  std::cout << "After push: " << s1.head() << std::endl;

  Stack_1<int> s2(std::move(s1));
  std::cout << "S2: " << s2.head() << std::endl;

  Stack_1<int> s3;
  s3 = std::move(s2);
  std::cout << "S3: " << s3.head() << std::endl;

  s3.pop();
  std::cout << "After pop: " << s3.head() << std::endl;

  return 0;
}
