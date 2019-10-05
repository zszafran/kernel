load(":toolchain.bzl", "toolchain_info")

platform(
    name = "platform_i686",
    constraint_values = [
        "@platforms//cpu:x86_32",
    ],
)

platform(
    name = "platform_x86_64",
    constraint_values = [
        "@platforms//cpu:x86_64",
    ],
)

toolchain_type(name = "toolchain_type")

toolchain_info(
    name = "toolchain_info_i686",
    gcc = "@compiler//:host_i686-elf-gcc",
    asm = "@compiler//:host_i686-elf-as",
    qemu = "@qemu//:host_qemu-system-i386",
    grub_mkrescue = "@grub//:host_grub-mkrescue",
    grub_file = "@grub//:host_grub-file",
    grub_platform = "@grub_platforms//:i386-pc",
    cflags = [],
)

toolchain(
    name = "toolchain_i686",
    exec_compatible_with = [
        "@platforms//cpu:x86_64",
    ],
    target_compatible_with = [
        "@platforms//cpu:x86_32",
    ],
    toolchain = ":toolchain_info_i686",
    toolchain_type = ":toolchain_type",
)

toolchain_info(
    name = "toolchain_info_x86_64",
    gcc = "@compiler//:host_x86_64-elf-gcc",
    asm = "@compiler//:host_x86_64-elf-as",
    qemu = "@qemu//:host_qemu-system-x86_64",
    grub_mkrescue = "@grub//:host_grub-mkrescue",
    grub_file = "@grub//:host_grub-file",
    grub_platform = "@grub_platforms//:i386-pc",
    cflags = [],
)

toolchain(
    name = "toolchain_x86_64",
    exec_compatible_with = [
        "@platforms//cpu:x86_64",
    ],
    target_compatible_with = [
        "@platforms//cpu:x86_64",
    ],
    toolchain = ":toolchain_info_x86_64",
    toolchain_type = ":toolchain_type",
)
