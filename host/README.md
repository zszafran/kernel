# Host Rules

This directory contains build targets that reference binaries installed on the host machine. These are referenced by the toolchain which in turn is passed into the custom build rules.

## Compilers

These rules wrap around the binaries installed by the `crossdev` utility. After installing an additional crossdev target these rules should be updated to include them.

`@compiler//:host_i686-elf-gcc`

`@compiler//:host_i686-elf-as`

`@compiler//:host_i686-elf-ar`

`@compiler//:host_x86_64-elf-gcc`

`@compiler//:host_x86_64-elf-as`

`@compiler//:host_x86_64-elf-ar`

## GRUB

These rules wrap around the various GRUB binaries and moduled.

`@grub_platforms//:i386-pc`

`@grub//:host_grub-mkrescue`

## QEMU

These rules wrap around the various QEMU binaries which allow the kernel/os to be run/debugged on different platforms. If a new crossdev target is added to the dev encironment it is likely that a new QEMU binary will need to be installed and in turn a rule will need to be added here to reference it.

`@qemu//:host_qemu-system-i386`

`@qemu//:host_qemu-system-x86_64`
