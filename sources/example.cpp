// Copyright 2022 VladislavRz <rzhevskii_vladislav@mail.ru>
#include <example.hpp>

#include <stdexcept>

auto example() -> void {
  throw std::runtime_error("something wrong");
}
