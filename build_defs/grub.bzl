load("@bazel_skylib//lib:new_sets.bzl", "sets")

def _grub_mkrescue_impl(ctx):
    tc = ctx.toolchains["//toolchain:toolchain_type"]
    grub_platform_dirs = sets.to_list(sets.make([f.dirname for f in tc.grub_platform]))

    in_kernel_file = ctx.file.kernel
    in_config_file = ctx.file.config

    out_file = ctx.actions.declare_file("%s.iso" % ctx.attr.name)
    out_dir = ctx.actions.declare_directory("%s.grub_mkrescue" % ctx.attr.name)

    ctx.actions.run_shell(
        inputs = [in_kernel_file, in_config_file, tc.grub_mkrescue] + tc.grub_platform,
        outputs = [out_file, out_dir],
        progress_message = "Creating Grub rescue ISO for '%s'" % ctx.attr.name,
        command = """
            mkdir -p {dir}/boot/grub;
            cp {kernel} {dir}/boot;
            cp {config} {dir}/boot/grub/grub.cfg;
            {bin} -o {iso} \\
                -d {platform} \\
                {dir};
            """.format(
                bin = tc.grub_mkrescue.path,
                dir = out_dir.path,
                kernel = in_kernel_file.path,
                config = in_config_file.path,
                iso = out_file.path,
                platform = " ".join(grub_platform_dirs),
            ),
    )

    return [DefaultInfo(files = depset([out_file]))]

grub_mkrescue = rule(
    implementation = _grub_mkrescue_impl,
    toolchains = ["//toolchain:toolchain_type"],
    attrs = {
        "kernel": attr.label(
            allow_single_file = [".bin"],
        ),
        "config": attr.label(
            allow_single_file = [".cfg"],
        ),
    },
)