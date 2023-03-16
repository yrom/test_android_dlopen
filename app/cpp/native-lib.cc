#include <android/log.h>
#include <dlfcn.h>
#include <jni.h>
#include <string>
#define TAG __FILE_NAME__
#define LOGI(...)                                                              \
  ((void)__android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__))
namespace nnn {
void test_dlopen(const std::string &lib);
}
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_android_MainActivity_stringFromJNI(JNIEnv *env,
                                                          jobject /* this */) {
  std::string hello = "Hello from C++";
  nnn::test_dlopen("libhello.so");
  return env->NewStringUTF(hello.c_str());
}

namespace nnn {
using f_get_greet = char *(*)(const char *);
using f_add = int (*)(int);
void *getFunctionPointer(void *lib, const char *func) {
  void *fptr = dlsym(lib, func);
  if (!fptr) {
    LOGI("Could not get function pointer for \"%s\":\nError: %s\n\n", func,
         dlerror());
    return nullptr;
  }
  return fptr;
}
void test_dlopen(const std::string &lib) {
  void *handle = dlopen(lib.c_str(), RTLD_LAZY);
  if (handle) {
    LOGI("dlopen(%s): OK", lib.c_str());
    auto get_greet = reinterpret_cast<f_get_greet>(
        getFunctionPointer(handle, "C_get_greet"));

    if (get_greet) {
      LOGI("get_greet: %p", get_greet);
      const char *w = "world";
      const char *r = get_greet(w);
      size_t l = strlen(r);
      char cpy[l + 1];
      strcpy(cpy, r);
      LOGI("get_greet(%s)->%s, %d", w, cpy, l);
    } else {
      LOGI("get_greet = nulptr");
    }

    auto add = reinterpret_cast<f_add>(getFunctionPointer(handle, "C_add"));
    if (add) {
      for (int i = 0; i < 3; ++i) {
        int result = add(i);
        LOGI("add(%d) -> %d", i, result);
      }
    } else {
      LOGI("add = nulptr");
    }
    dlclose(handle);
  } else {
    LOGI("dlopen(%s): NOK", lib.c_str());
  }
}
} // namespace nnn