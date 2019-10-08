# Toolchain

This directory contains the toolchain configured for different platform targets.

## Platform Targets

These define the platform that can be targed for compilation

```python
platform(
    name = "platform_i686",
    constraint_values = [
        "@platforms//cpu:x86_32",
    ],
)
```

> **Arch**: These are the same constraints used to select which `src/arch` directory to build into the kernel.

They can be manually specified when running nay Bazel command

```bash
bazel build --platforms=//toolchain:platform_i686
```

## Toolchains

A toolchain maps together a target platform to a `toolchain_info` configuration.

```python
toolchain(
    name = "toolchain_i686",
    ...
    target_compatible_with = [
        "@platforms//cpu:x86_32",
    ],
    toolchain = ":toolchain_info_i686",
    ...
)
```

## Toolchain Info

A `toolchain_info` configuration maps different toolchain binaries needed by build rules.

```python
toolchain_info(
    name = "toolchain_info_i686",
    archive = "@compiler//:host_i686-elf-ar",
    asm = "@compiler//:host_i686-elf-as",
    cflags = [...],
    gcc = "@compiler//:host_i686-elf-gcc",
    grub_file = "@grub//:host_grub-file",
    grub_mkrescue = "@grub//:host_grub-mkrescue",
    grub_platform = "@grub_platforms//:i386-pc",
    ldflags = [...],
    qemu = "@qemu//:host_qemu-system-i386",
)
```

> **Host:** The binaries referenced here are defined in the `host` directory.
