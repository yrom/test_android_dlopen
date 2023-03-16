load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")


cc_binary(
    name = "libhello.so",
    srcs = ["hello.cc"],
    copts = [
        "-fvisibility=hidden",
    ],
    deps = [
        ":version_script.lds"
    ],
    linkopts = [
        "-llog",
        "-Wl,-soname,libhello.so",
        "-lc++_shared",
         "-Wl,--version-script,$(location :version_script.lds)",
    ],
    linkshared = 1,
    linkstatic = 0,
)

cc_library(
    name = "hello",
    visibility = ["//visibility:public"],
    srcs = [
        "libhello.so",
    ],
)
