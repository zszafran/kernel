def _qemu_deploy_impl(ctx):
    tc = ctx.toolchains["//toolchain:toolchain_type"]

    in_cdrom = ctx.file.cdrom

    out_file = ctx.actions.declare_file("%s.sh" % ctx.attr.name)

    args = list()

    if ctx.attr.nographic:
        args.append("-nographic")

    if ctx.attr.curses:
        args.append("-curses")

    if ctx.attr.debugger:
        args.append("-S")
        args.append("-s")

    if ctx.attr.showcursor:
        args.append("-show-cursor")

    if ctx.attr.usb:
        args.append("-usb")

    for device in ctx.attr.devices:
        args.append("-device")
        args.append(device)

    args.extend([
        "-vga",
        ctx.attr.vga,
        "-serial",
        ctx.attr.serial,
        "-cpu",
        ctx.attr.cpu,
        "-cdrom",
        in_cdrom.short_path,
    ])

    ctx.actions.write(
        output = out_file,
        content = "%s %s $@" % (tc.qemu.path, " ".join(args)),
        is_executable = True,
    )

    runfiles = ctx.runfiles(files = [in_cdrom, tc.qemu])

    return [DefaultInfo(executable = out_file, runfiles = runfiles)]

qemu_deploy = rule(
    implementation = _qemu_deploy_impl,
    toolchains = ["//toolchain:toolchain_type"],
    executable = True,
    attrs = {
        "cdrom": attr.label(
            allow_single_file = [".iso"],
            mandatory = True,
        ),
        "nographic": attr.bool(),
        "curses": attr.bool(),
        "vga": attr.string(
            default = "std",
        ),
        "serial": attr.string(
            default = "mon:stdio",
        ),
        "cpu": attr.string(
            default = "max",
        ),
        "debugger": attr.bool(),
        "showcursor": attr.bool(),
        "usb": attr.bool(),
        "devices": attr.string_list(),
    },
)
