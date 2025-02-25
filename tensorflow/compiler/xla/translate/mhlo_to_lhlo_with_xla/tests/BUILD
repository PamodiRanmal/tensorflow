load("//tensorflow:tensorflow.default.bzl", "filegroup")
load("//tensorflow/compiler/mlir:glob_lit_test.bzl", "glob_lit_tests")
load(
    "//tensorflow/core/platform:build_config_root.bzl",
    "tf_cuda_tests_tags",
)

package(licenses = ["notice"])

glob_lit_tests(
    data = [":test_utilities"],
    driver = "@llvm-project//mlir:run_lit.sh",
    tags_override = {
        "gpu_ops.mlir": tf_cuda_tests_tags() + [
            "noasan",
            "nomsan",
            "noubsan",
            "no_cuda_asan",
            "no_oss",
        ],
    },
    test_file_exts = [
        "mlir",
        "hlo",
        "hlotxt",
    ],
)

# Bundle together all of the test utilities that are used by tests.
filegroup(
    name = "test_utilities",
    testonly = True,
    data = [
        "//tensorflow/compiler/xla/translate:xla-translate",
        "//tensorflow/compiler/xla/translate/mhlo_to_lhlo_with_xla:xla-translate-gpu-opt",
        "//tensorflow/compiler/xla/translate/mhlo_to_lhlo_with_xla:xla-translate-opt",
        "@llvm-project//llvm:FileCheck",
        "@llvm-project//llvm:not",
    ],
)
