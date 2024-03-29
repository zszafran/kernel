# Build Definitions

This is a collection of custom build rules that wrap around the toolchain.

## GCC

```python
load("//build_defs:gcc.bzl", "gcc_binary", "gcc_library", "gcc_builtin")
```

### gcc_binary

```python
gcc_binary(
    name = "foo",
    srcs = [
        "foo.c",
        "bar.S",
    ],
    includes = ["//src/include"],
)
```

### gcc_library

```python
gcc_library(
    name = "foo",
    srcs = [
        ":stdio",
        ":stdlib",
        ":string",
    ],
)
```

### gcc_executable

```python
gcc_executable(
    name = "foo",
    srcs = [
        ":bar",
        ":baz",
    ],
    linker = "linker.ld",
    crtbegin = ":crtbegin",
    crtend = ":crtend",
    crti = ":crti",
    crtn = ":crtn",
)
```

### gcc_builtin

```python
gcc_builtin(name = "crtbegin")

gcc_builtin(name = "crtend")
```

### gcc_linker

```python
gcc_linker(
    name = "foo",
    src = "linker.ld",
    includes = ["//src/include"],
)
```

## GRUB

```python
load("//build_defs:grub.bzl", "grub_mkrescue")
```

### grub_mkrescue

```python
grub_mkrescue(
    name = "foo",
    config = "grub.cfg",
    kernel = "//src/kernel",
)
```

## QEMU

```python
load("//build_defs:qemu.bzl", "qemu_deploy")
```

### qemu_deploy

```python
qemu_deploy(
    name = "foo",
    cdrom = ":rescue",
    cpu = "max",
    curses = True,
    nographic = True,
    serial = "mon:stdio",
    vga = "std",
)
```
