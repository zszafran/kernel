def _qemu_deploy_impl(ctx):
    tc = ctx.toolchains["//toolchain:toolchain_type"]

    in_cdrom = ctx.file.cdrom

    out_file = ctx.actions.declare_file("%s.sh" % ctx.attr.name)

    ctx.actions.write(
        output = out_file,
        content = """
            {bin} \\
                -nographic \\
	            -curses \\
	            -vga std \\
	            -serial mon:stdio \\
	            -cpu max \\
	            -s \\
                -cdrom {iso}
            """.format(
                bin = tc.qemu.path,
                iso = in_cdrom.short_path,
            ),
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
        ),
    },
)