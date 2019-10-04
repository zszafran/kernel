load("@bazel_skylib//lib:shell.bzl", "shell")

def _asm_binary_impl(ctx):
    tc = ctx.toolchains["//toolchain:toolchain_type"]

    in_files = ctx.files.srcs

    out_file = ctx.actions.declare_file("%s.o" % ctx.attr.name)

    ctx.actions.run(
        inputs = in_files,
        outputs = [out_file],
        progress_message = "Compiling Assembly '%s' binary" % ctx.attr.name,
        arguments = [
            " ".join([f.path for f in in_files]),
            "-o",
            out_file.path
        ],
        executable = tc.asm,
    )

    return [DefaultInfo(files = depset([out_file]))]

asm_binary = rule(
    implementation = _asm_binary_impl,
    toolchains = ["//toolchain:toolchain_type"],
    attrs = {
        "srcs": attr.label_list(
            allow_files = [".S"],
        ),
    },
)