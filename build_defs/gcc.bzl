load("@bazel_skylib//lib:paths.bzl", "paths")

def _gcc_binary_impl(ctx):
    tc = ctx.toolchains["//toolchain:toolchain_type"]

    in_files = ctx.files.srcs
    in_includes_files = ctx.files.includes

    out_files = list()

    for in_file in in_files:
        out_file = ctx.actions.declare_file(paths.replace_extension(in_file.basename, ".o"))
        out_files.append(out_file)

        args = ctx.actions.args()
        args.add("-c", in_file.path)
        args.add("-o", out_file.path)
        args.add_all(["-I%s" % i.label.package for i in ctx.attr.includes])
        args.add_all(tc.cflags)
        args.add_all(ctx.attr.cflags)
        args.add_all(ctx.attr.cppflags)

        ctx.actions.run(
            inputs = [in_file] + in_includes_files,
            outputs = [out_file],
            progress_message = "Compiling C '%s' binary" % in_file.basename,
            arguments = [args],
            executable = tc.gcc,
        )

    return [DefaultInfo(files = depset(out_files))]

gcc_binary = rule(
    implementation = _gcc_binary_impl,
    toolchains = ["//toolchain:toolchain_type"],
    attrs = {
        "srcs": attr.label_list(
            allow_files = [".c"],
        ),
        "includes": attr.label_list(
            allow_files = [".h"],
        ),
        "cflags": attr.string_list(),
        "cppflags": attr.string_list(),
    },
)

def _gcc_executable_impl(ctx):
    tc = ctx.toolchains["//toolchain:toolchain_type"]

    in_files = ctx.files.srcs + [
        ctx.file.crti,
        ctx.file.crtn,
        ctx.file.crtbegin,
        ctx.file.crtend,
    ]

    out_file = ctx.actions.declare_file("%s.bin" % ctx.attr.name)

    args = ctx.actions.args()
    args.add("-T", ctx.file.linker.path)
    args.add("-o", out_file.path)
    args.add_all(tc.ldflags)
    args.add_all(ctx.attr.ldflags)
    args.add(ctx.file.crti.path)
    args.add(ctx.file.crtbegin.path)
    args.add_all([f.path for f in ctx.files.srcs])
    args.add(ctx.file.crtend.path)
    args.add(ctx.file.crtn.path)

    ctx.actions.run(
        inputs = in_files + [ctx.file.linker],
        outputs = [out_file],
        progress_message = "Linking C '%s' executable" % ctx.attr.name,
        arguments = [args],
        executable = tc.gcc,
    )

    return [DefaultInfo(files = depset([out_file]))]

gcc_executable = rule(
    implementation = _gcc_executable_impl,
    toolchains = ["//toolchain:toolchain_type"],
    attrs = {
        "srcs": attr.label_list(
            allow_files = [".o", ".a"],
        ),
        "crti": attr.label(
            allow_single_file = [".o"],
        ),
        "crtn": attr.label(
            allow_single_file = [".o"],
        ),
        "crtbegin": attr.label(
            allow_single_file = [".o"],
        ),
        "crtend": attr.label(
            allow_single_file = [".o"],
        ),
        "linker": attr.label(
            allow_single_file = [".ld"],
        ),
        "ldflags": attr.string_list(),
    },
)

def _gcc_builtin_impl(ctx):
    tc = ctx.toolchains["//toolchain:toolchain_type"]

    out_file = ctx.actions.declare_file("%s.o" % ctx.attr.name)

    command = "cat $({bin} {flags} -print-file-name={name}.o) > {out}".format(
        bin = tc.gcc.path,
        flags = " ".join(tc.cflags),
        name = ctx.attr.name,
        out = out_file.path,
    )

    ctx.actions.run_shell(
        tools = [tc.gcc],
        inputs = [],
        outputs = [out_file],
        progress_message = "Locating GCC builtin for '%s'" % ctx.attr.name,
        command = command,
    )

    return [DefaultInfo(files = depset([out_file]))]

gcc_builtin = rule(
    implementation = _gcc_builtin_impl,
    toolchains = ["//toolchain:toolchain_type"],
    attrs = {},
)

def _gcc_library_impl(ctx):
    tc = ctx.toolchains["//toolchain:toolchain_type"]

    in_files = ctx.files.srcs

    out_file = ctx.actions.declare_file("%s.a" % ctx.attr.name)

    args = ctx.actions.args()
    args.add("rcs", out_file.path)
    args.add_all([f.path for f in in_files])

    ctx.actions.run(
        inputs = in_files,
        outputs = [out_file],
        progress_message = "Creating GCC library for '%s'" % ctx.attr.name,
        arguments = [args],
        executable = tc.archive,
    )

    return [DefaultInfo(files = depset([out_file]))]

gcc_library = rule(
    implementation = _gcc_library_impl,
    toolchains = ["//toolchain:toolchain_type"],
    attrs = {
        "srcs": attr.label_list(
            allow_files = [".o"],
        ),
    },
)

def _gcc_linker_impl(ctx):
    tc = ctx.toolchains["//toolchain:toolchain_type"]

    in_file = ctx.file.src
    out_file = ctx.actions.declare_file("%s.ld" % ctx.attr.name)

    command = "{bin} -P -D__ASM__ -E -x c {includes} {cflags} {input} | grep -v '^#' >> {output}".format(
        bin = tc.gcc.path,
        cflags = " ".join(tc.cflags),
        includes = " ".join(["-I%s" % i.label.package for i in ctx.attr.includes]),
        input = in_file.path,
        output = out_file.path,
    )

    ctx.actions.run_shell(
        tools = [tc.gcc],
        inputs = [in_file],
        outputs = [out_file],
        progress_message = "Proprocessing '%s' linker" % ctx.attr.name,
        command = command,
    )

    return [DefaultInfo(files = depset([out_file]))]

gcc_linker = rule(
    implementation = _gcc_linker_impl,
    toolchains = ["//toolchain:toolchain_type"],
    attrs = {
        "src": attr.label(
            allow_single_file = [".ld"],
        ),
        "includes": attr.label_list(
            allow_files = [".h"],
        ),
    },
)
