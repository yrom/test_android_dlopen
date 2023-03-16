## Testing `dlopen()` on android


```sh
bazel build //app

adb install -r bazel-bin/app/app.apk
adb shell am start -S com.example.android/com.example.android.MainActivity
adb logcat
```

Logcat:

    03-16 20:36:54.823  5731  5731 I native-lib.cc: dlopen(libhello.so): OK
    03-16 20:36:54.823  5731  5731 I native-lib.cc: get_greet: 0x7eff2db0db50
    03-16 20:36:54.823  5731  5731 I hello.cc: get_greet(world)
    03-16 20:36:54.823  5731  5731 I hello.cc: ret: Hello world, 11
    03-16 20:36:54.823  5731  5731 I native-lib.cc: get_greet(world)->Hello world, 11
    03-16 20:36:54.823  5731  5731 I native-lib.cc: add(0) -> 42
    03-16 20:36:54.823  5731  5731 I native-lib.cc: add(1) -> 43
    03-16 20:36:54.823  5731  5731 I native-lib.cc: add(2) -> 44
