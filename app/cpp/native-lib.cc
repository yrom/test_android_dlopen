#include <android/log.h>
#include <dlfcn.h>
#include <hello.h>
#include <jni.h>
#include <string>
#define TAG __FILE_NAME__
#define LOGI(...)                                                              \
  ((void)__android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__))

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_android_MainActivity_stringFromJNI(JNIEnv *env,
                                                    jobject /* this */) {
  char *result = C_get_greet("libhello.so");

  for (int i = 0; i < 3; i++) {
    auto j = C_add(i);
    LOGI("add(%d)->%d",i, j);
  }
  jstring str = env->NewStringUTF(result);
  free(result);
  return str;
}
