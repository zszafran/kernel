# Architecture Implementations

These subdirectories implement the kernel interfaces defined in `//src/includes/kernel` for different target architectures.

## Master Rule

This master rule allows the kernel binary to depend on a single generic build target. This target will automatically select the correct architectural dependencies at build-time.

```python
filegroup(
    name = "arch",
    srcs = select({
        ":config_x86_32": ["//src/arch/i686"],
        ":config_x86_64": ["//src/arch/x86_64"],
    }),
)
```
