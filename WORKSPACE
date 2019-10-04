workspace(name = "osdev")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive", "http_file")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

maybe(
    http_archive,
    name = "bazel_skylib",
    url = "https://github.com/bazelbuild/bazel-skylib/releases/download/0.9.0/bazel_skylib-0.9.0.tar.gz",
    sha256 = "1dde365491125a3db70731e25658dfdd3bc5dbdfd11b840b3e987ecf043c7ca0",
)

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")

bazel_skylib_workspace()

new_local_repository(
    name = "grub",
    path = "/usr/bin",
    build_file = "local/grub.BUILD",
)

new_local_repository(
    name = "grub_platforms",
    path = "/usr/lib/grub",
    build_file = "local/grub_platforms.BUILD",
)

new_local_repository(
    name = "qemu",
    path = "/usr/bin",
    build_file = "local/qemu.BUILD",
)

new_local_repository(
    name = "compiler",
    path = "/usr/bin",
    build_file = "local/compiler.BUILD",
)

register_toolchains(
    "//toolchain:toolchain_i686",
    "//toolchain:toolchain_x86_64",
)