load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "hello_header",
    hdrs = [
        "hello.h",
    ],
    includes = [
        ".",
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "libhello.so",
    srcs = [
        "hello.cc",
    ],
    copts = [
        "-fvisibility=hidden",
    ],
    linkopts = [
        "-llog",
        "-Wl,-soname,libhello.so",
        "-Wl,--version-script,$(location :version_script.lds)",
    ],
    linkshared = 1,
    linkstatic = 1,
    deps = [
        ":hello_header",
        ":version_script.lds",
    ],
)

cc_library(
    name = "hello",
    srcs = [
        "libhello.so",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":hello_header",
    ],
)
