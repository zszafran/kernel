def _gcc_binary_impl(ctx):
    tc = ctx.toolchains["//toolchain:toolchain_type"]

    in_files = ctx.files.srcs

    out_file = ctx.actions.declare_file("%s.o" % ctx.attr.name)

    arguments = [
        "-c",
        " ".join([f.path for f in in_files]),
        "-o",
        out_file.path
    ]

    arguments.extend(ctx.attr.cflags)

    ctx.actions.run(
        inputs = in_files,
        outputs = [out_file],
        progress_message = "Compiling C '%s' binary" % ctx.attr.name,
        arguments = arguments,
        executable = tc.gcc,
    )

    return [DefaultInfo(files = depset([out_file]))]

gcc_binary = rule(
    implementation = _gcc_binary_impl,
    toolchains = ["//toolchain:toolchain_type"],
    attrs = {
        "srcs": attr.label_list(
            allow_files = [".c"],
        ),
        "cflags": attr.string_list(),
    },
)

def _gcc_linked_binary_impl(ctx):
    tc = ctx.toolchains["//toolchain:toolchain_type"]

    in_files = ctx.files.srcs

    out_file = ctx.actions.declare_file("%s.bin" % ctx.attr.name)

    arguments = [
        "-T",
        ctx.file.config.path,
        "-o",
        out_file.path,
    ]

    arguments.extend(ctx.attr.cflags)
    arguments.extend([f.path for f in in_files])

    ctx.actions.run(
        inputs = in_files + [ctx.file.config],
        outputs = [out_file],
        progress_message = "Linking C '%s' binary" % ctx.attr.name,
        arguments = arguments,
        executable = tc.gcc,
    )

    return [DefaultInfo(files = depset([out_file]))]

gcc_linked_binary = rule(
    implementation = _gcc_linked_binary_impl,
    toolchains = ["//toolchain:toolchain_type"],
    attrs = {
        "srcs": attr.label_list(
            allow_files = [".o"],
        ),
        "config": attr.label(
            allow_single_file = [".ld"],
        ),
        "cflags": attr.string_list(),
    },
)