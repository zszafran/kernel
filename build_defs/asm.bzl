load("@bazel_skylib//lib:paths.bzl", "paths")

def _asm_binary_impl(ctx):
    tc = ctx.toolchains["//toolchain:toolchain_type"]

    in_files = ctx.files.srcs

    out_files = list()

    for in_file in in_files:
        out_file = ctx.actions.declare_file(paths.replace_extension(in_file.basename, ".o"))
        out_files.append(out_file)

        args = ctx.actions.args()
        args.add(in_file.path)
        args.add("-o", out_file.path)

        ctx.actions.run(
            inputs = [in_file],
            outputs = [out_file],
            progress_message = "Compiling Assembly '%s' binary" % ctx.attr.name,
            arguments = [args],
            executable = tc.asm,
        )

    return [DefaultInfo(files = depset(out_files))]

asm_binary = rule(
    implementation = _asm_binary_impl,
    toolchains = ["//toolchain:toolchain_type"],
    attrs = {
        "srcs": attr.label_list(
            allow_files = [".S"],
        ),
    },
)
