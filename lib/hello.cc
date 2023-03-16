#include <android/log.h>
#include <ctime>
#include <iostream>
#include <string>
#define EXPORT __attribute__((visibility("default")))
#define TAG __FILE_NAME__
#define LOGI(...)                                                              \
  ((void)__android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__))
namespace hello {
std::string get_greet(const std::string &who) { return "Hello " + who; }
} // namespace hello

extern "C" EXPORT const char *C_get_greet(const char *who) {
  LOGI("get_greet(%s)", who);
  std::string str(who);
  auto ret = hello::get_greet(str).c_str();
  LOGI("ret: %s, %d", ret, strlen(ret));
  return ret;
}

extern "C" EXPORT int C_add(int a) { return a + 42; }
