# kernel

```shell
bazel build --config=x86_32 src/kernel
```

```shell
bazel build --config=x86_64 src/kernel
```

```shell
bazel build --config=x86_32 src/kernel:rescue
```

```shell
bazel run --config=x86_32 src/kernel:qemu
```