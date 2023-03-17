#include <android/log.h>
#include <dlfcn.h>
#include <hello.h>
#include <map>
#define TAG __FILE_NAME__
#define LOGI(...)                                                              \
  ((void)__android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__))
namespace nnn {
using f_get_greet = char *(*)(const char *);
using f_add = int (*)(int);
static void *handle;
const char *lib = "libhello.so";
void *tryLoadLibrary() {
  if (handle) {
    return handle;
  }
  handle = dlopen(lib, RTLD_LAZY);
  if (handle) {
    LOGI("dlopen(%s): OK", lib);
    return handle;
    // dlclose(handle);
  } else {
    LOGI("dlopen(%s): NOK", lib);
    return nullptr;
  }
}
static std::map<const char *, void *> fptrs;
void *getFunctionPointer(const char *func) {
  auto iter = fptrs.find(func);
  void *fptr = iter != fptrs.end() ? iter->second : nullptr;
  if (!fptr) {
    void *handle = tryLoadLibrary();
    fptr = !handle ? nullptr : dlsym(handle, func);
    fptrs[func] = fptr;
    if (!fptr) {
      LOGI("Could not get function pointer for \"%s\":\nError: %s\n\n", func,
           dlerror());
      return nullptr;
    }
  }
  return fptr;
}
} // namespace nnn

extern "C" {

char *C_get_greet(const char *who) {
  auto get_greet =
      reinterpret_cast<nnn::f_get_greet>(nnn::getFunctionPointer(__FUNCTION__));
  if (get_greet) {
    LOGI("call %s from stub", __FUNCTION__);
    char *result = get_greet(who);

    size_t m = strlen(result);

    const char *suffix = " from_stub";
    size_t n = strlen(suffix);
    char *stub = static_cast<char *>(malloc(m + n + 1));
    memset(stub, 0, m + n + 1);
    memcpy(stub, result, m);
    memcpy(stub + m, suffix, n);
    free(result);
    return stub;
  }
  return NULL;
}
int C_add(int a) {
  LOGI("call %s from stub", __FUNCTION__);
  auto add =
      reinterpret_cast<nnn::f_add>(nnn::getFunctionPointer(__FUNCTION__));
  if (add) {
    return add(a) + 2;
  }
  return a;
}
}