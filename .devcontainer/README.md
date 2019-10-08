# Dev Container

The directory contains the development container that provides the toolchain binaries and build system binaries.

## Dockerfile

The Dockerfile will be automatically built and run by the vscode remote container extension. This container will include the Bazel build system, crossdev toolchains, GRUB binaries, and QEMU binaries.

### Crossdev Targets

Additional crossdev targets can be installed by appending them to the Dockerfile:

```dockerfile
RUN crossdev --stage1 --stable --target i686-elf -oO /var/db/repos/crossdev
RUN crossdev --stage1 --stable --target x86_64-elf -oO /var/db/repos/crossdev
```

> **Bazel:** Remember to update the bazel toolchain to include any new binaries installed for this target. See `host/compiler.BUILD`, `toolchain/BUILD` and `src/arch/BUILD`.
>
> **QEMU:** Remember to configure a QEMU platform that can run this new target. See `.devcontainer/portage/package.use/qemu`.

### Bazel Memory Limits

To improve Bazel performance the `BAZEL_JAVAC_OPTS` variable can be configured to better match the host's available memory.

```bash
ENV BAZEL_JAVAC_OPTS="-J-Xms4g -J-Xmx4g"
```

> **Docker:** Remember to set the memory limits in Docker advanced perferences.

## Gentoo

The container is built using a Gentoo stage3 and portage images.

### portage/make.conf

This is mainly for configuring portage and how it compiles packages. The only real benefit of tweaking this file would be to improve the docker build time for the dev container image. This file should have little effect on the Bazel build system itself.

#### USE Flags

To avoid unnecessary dependencies and bloat, all USE flags are disabled by default. Package specific flags should be configured in `portage/package.use/foo` files.

```bash
USE="-*"
```

#### Concurrent Jobs

To improve performance when building gentoo packages the `MAKEOPTS` and `EMERGE_DEFAULT_OPTS` can be configured to better reflect the host's CPU.

```bash
MAKEOPTS="-j5"
EMERGE_DEFAULT_OPTS="--jobs=5"
```

> **Docker:** Remember to set the CPU limits in Docker advanced preferences.

### portage/package.accept_keywords

This is mainly for configuring which versions of packages to install. To install newer (unstable) versions add an entry to this file. Currently only Bazel is installed as an unstable version though it might be beneficial to install newer versions of QEMU as well.

```text
dev-util/bazel ~amd64
```

### portage/package.use/*

This directly contains USE flag configurations for individual gentoo packages. The only one likely to change much is `qemu` which has flags that specify which platforms it should be able to run.

### world

This file contains a list of all packages that should be installed when the container image is being created. This is a good place to add additional utilities that one might want available in a dev environment.

### zshrc

This file is the ZSH config where the shell prompt and features can be configured.
