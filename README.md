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
