## Testing `dlopen()` on android


```sh
bazel build //app

adb install -r bazel-bin/app/app.apk
adb shell am start -S com.example.android/com.example.android.MainActivity
adb logcat
```

Logcat:

    03-17 14:39:29.268  7356  7356 I hello-stub.cc: dlopen(libhello.so): OK
    03-17 14:39:29.268  7356  7356 I hello-stub.cc: call C_get_greet from stub
    03-17 14:39:29.268  7356  7356 I hello.cc: get_greet('libhello.so')
    03-17 14:39:29.268  7356  7356 I hello.cc: ret: 'Hello libhello.so', 17
    03-17 14:39:29.268  7356  7356 I hello-stub.cc: call C_add from stub
    03-17 14:39:29.268  7356  7356 I native-lib.cc: add(0)->44
    03-17 14:39:29.268  7356  7356 I hello-stub.cc: call C_add from stub
    03-17 14:39:29.268  7356  7356 I native-lib.cc: add(1)->45
    03-17 14:39:29.268  7356  7356 I hello-stub.cc: call C_add from stub
    03-17 14:39:29.268  7356  7356 I native-lib.cc: add(2)->46

## Enable logging of dlopen/dlsym

```sh
adb shell setprop debug.ld.app.com.example.android dlerror,dlopen,dlsym
adb shell am start -S com.example.android/com.example.android.MainActivity
adb logcat
```

Logcat:

    D linker  : dlsym(handle=0x7f00088b3d30("/data/app/com.example.android-GiAxzcpTY5rpDn37u2gfFQ==/lib/x86_64/libapp.so"), sym_name="Java_com_example_android_MainActivity_stringFromJNI", sym_ver="(null)", caller="/apex/com.android.runtime/lib64/libart.so", caller_ns=runtime@0x7f00087fb010) ...
    D linker  : ... dlsym successful: sym_name="Java_com_example_android_MainActivity_stringFromJNI", sym_ver="(null)", found in="libapp", address=0x7eff2d751620
    D linker  : dlopen(name="libhello.so", flags=0x1, extinfo=(null), caller="/data/app/com.example.android-GiAxzcpTY5rpDn37u2gfFQ==/lib/x86_64/libapp.so", caller_ns=classloader-namespace@0x7f00087fb6f0, targetSdkVersion=23) ...
    D linker  : find_libraries(ns=classloader-namespace): task=libhello.so, is_dt_needed=0
    D linker  : find_library_internal(ns=classloader-namespace, task=libhello.so): Already loaded (by soname): /data/app/com.example.android-GiAxzcpTY5rpDn37u2gfFQ==/lib/x86_64/libhello.so
    D linker  : ... dlopen calling constructors: realpath="/data/app/com.example.android-GiAxzcpTY5rpDn37u2gfFQ==/lib/x86_64/libhello.so", soname="libhello.so", handle=0x7f00088b3f80
    D linker  : ... dlopen successful: realpath="/data/app/com.example.android-GiAxzcpTY5rpDn37u2gfFQ==/lib/x86_64/libhello.so", soname="libhello.so", handle=0x7f00088b3f80
    I hello-stub.cc: dlopen(libhello.so): OK
    D linker  : dlsym(handle=0x7f00088b3f80("/data/app/com.example.android-GiAxzcpTY5rpDn37u2gfFQ==/lib/x86_64/libhello.so"), sym_name="C_get_greet", sym_ver="(null)", caller="/data/app/com.example.android-GiAxzcpTY5rpDn37u2gfFQ==/lib/x86_64/libapp.so", caller_ns=classloader-namespace@0x7f00087fb6f0) ...
    D linker  : ... dlsym successful: sym_name="C_get_greet", sym_ver="(null)", found in="libhello.so", address=0x7eff2db56a80
    I hello-stub.cc: call C_get_greet from stub
    I hello.cc: get_greet('libhello.so')
    I hello.cc: ret: 'Hello libhello.so', 17
    I hello-stub.cc: call C_add from stub
    D linker  : dlsym(handle=0x7f00088b3f80("/data/app/com.example.android-GiAxzcpTY5rpDn37u2gfFQ==/lib/x86_64/libhello.so"), sym_name="C_add", sym_ver="(null)", caller="/data/app/com.example.android-GiAxzcpTY5rpDn37u2gfFQ==/lib/x86_64/libapp.so", caller_ns=classloader-namespace@0x7f00087fb6f0) ...
    D linker  : ... dlsym successful: sym_name="C_add", sym_ver="(null)", found in="libhello.so", address=0x7eff2db56c00
    I native-lib.cc: add(0)->44
    I hello-stub.cc: call C_add from stub
    I native-lib.cc: add(1)->45