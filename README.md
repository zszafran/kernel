# OS Dev

The main goal of this project is to not only develope a kernel/os but to also provide a consistent developer setup straight from the repository. This includes the toolchains and binaries needed for building the source in addition to the utilities needed for future development.

## Setup

* Install [docker](https://www.docker.com/products/docker-desktop) and [vscode](https://code.visualstudio.com/)
* Clone the repo and open in vscode
* Connect to [dev container](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)
* Build/run the OS (`Cmd/Ctrl + Shift + B`)

## Bare Bones

This branch follows the [Bare Bone](https://wiki.osdev.org/Bare_Bones) tutorial to ensure that the build system and toolchains can provide the minimum necessary for basic kernel development.

## Meaty Skeleton

[Meaty Skeleton](https://wiki.osdev.org/Meaty_Skeleton)

## Dev Container

This container is a minimal Gentoo stage3 + portage image that installs some basic dev tools including Bazel and crossdev utils.

It also installs gcc and binutils for the `i686-elf` and `x86_64-elf` targets via crossdev.

This container can be run standalone using `docker run` but it also comes configured for `vscode` as a [Remote Container](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)

## Toolchain

Custom toolchains are provided for Bazel which reference the binaries installed in the dev container. This includes the compilers for the different crossdev targets, several GRUB binaries, and the QEMU binaries.

Toolchains can be manually selected using the `--config=i686` or `--config=x86_64` argument when running any Bazel command.

## Build System

The build system is powered by [Bazel](https://bazel.build/) and provides several custom Build Rules written around the custom toolchain. This includes `asm_binary`, `gcc_binary`, `gcc_linked_binary`, `gcc_library`, `gcc_builtin`, `grub_rescue`, and `qemu_deplay`.

> **NOTE**: The builtin cc_toolchain, cc_binary, and cc_library rules were specifically avoided for this project. It is likely that they would work well with this project, but for simplicity and flexibility the custom rules seemed like a better choice.

## Build Commands

Building the binary for i686 targets

```shell
bazel build --config=i686 src/kernel
```

Building the binary for x86_64 targets

```shell
bazel build --config=x86_64 src/kernel
```

Building the GRUB rescue ISO with kernel

```shell
bazel build --config=i686 src:rescue
```

Running the GRUB reduce ISO with QEMU

```shell
bazel run --config=i686 src:qemu
```

## Debugging

To start QEMU with GDB and block in booting

```shell
bazel run --config=i686 src:qemu_debug
```

> **TODO**: Need to install GDB for the crossdev targets via the Dockerfile.

## Visual Studio Code

To provide a consistent developer expierence [Visual Studio Code](https://code.visualstudio.com/) was selected as a preferred IDE for this codebase. It integrates with the Docker container via a `.devcontainer.json` configuration, and preinstalls extensions related to Bazel, linters, and intellisense.

Also included are several predefined tasks for building and running the various targets.

Lastly the debugger is configured to connect to the `:qemu_debug` process.

> **TODO**: Need to make debugger actually connect to QEMU's GDB.
