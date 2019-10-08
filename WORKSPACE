workspace(name = "osdev")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive", "http_file")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

maybe(
    http_archive,
    name = "bazel_skylib",
    sha256 = "1dde365491125a3db70731e25658dfdd3bc5dbdfd11b840b3e987ecf043c7ca0",
    url = "https://github.com/bazelbuild/bazel-skylib/releases/download/0.9.0/bazel_skylib-0.9.0.tar.gz",
)

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")

bazel_skylib_workspace()

new_local_repository(
    name = "grub",
    build_file = "host/grub.BUILD",
    path = "/usr/bin",
)

new_local_repository(
    name = "grub_platforms",
    build_file = "host/grub_platforms.BUILD",
    path = "/usr/lib/grub",
)

new_local_repository(
    name = "qemu",
    build_file = "host/qemu.BUILD",
    path = "/usr/bin",
)

new_local_repository(
    name = "compiler",
    build_file = "host/compiler.BUILD",
    path = "/usr/bin",
)

register_toolchains(
    "//toolchain:toolchain_i686",
    "//toolchain:toolchain_x86_64",
)
