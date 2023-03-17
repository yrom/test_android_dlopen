#pragma once
#include <string>

namespace hello {
std::string get_greet(const std::string &who);
} // namespace hello

extern "C" {
char *C_get_greet(const char *who);
int C_add(int a);
}