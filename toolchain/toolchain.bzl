def _toolchain_info(ctx):
    return [
        platform_common.ToolchainInfo(
            gcc = ctx.executable.gcc,
            asm = ctx.executable.asm,
            archive = ctx.executable.archive,
            grub_mkrescue = ctx.executable.grub_mkrescue,
            grub_file = ctx.executable.grub_file,
            grub_platform = ctx.files.grub_platform,
            qemu = ctx.executable.qemu,
            cflags = ctx.attr.cflags,
            ldflags = ctx.attr.ldflags,
        ),
    ]

toolchain_info = rule(
    _toolchain_info,
    attrs = {
        "gcc": attr.label(
            executable = True,
            default = "@compiler//:host_i686-elf-gcc",
            allow_single_file = True,
            cfg = "host",
        ),
        "asm": attr.label(
            executable = True,
            default = "@compiler//:host_i686-elf-as",
            allow_single_file = True,
            cfg = "host",
        ),
        "archive": attr.label(
            executable = True,
            default = "@compiler//:host_i686-elf-ar",
            allow_single_file = True,
            cfg = "host",
        ),
        "grub_mkrescue": attr.label(
            executable = True,
            default = "@grub//:host_grub-mkrescue",
            allow_single_file = True,
            cfg = "host",
        ),
        "grub_file": attr.label(
            executable = True,
            default = "@grub//:host_grub-file",
            allow_single_file = True,
            cfg = "host",
        ),
        "grub_platform": attr.label(
            cfg = "host",
        ),
        "qemu": attr.label(
            executable = True,
            default = "@qemu//:host_qemu-system-i386",
            allow_single_file = True,
            cfg = "host",
        ),
        "cflags": attr.string_list(),
        "ldflags": attr.string_list(),
    },
)
