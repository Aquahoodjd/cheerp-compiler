// RUN: %clang_cc1 -fsanitize=address -fno-sanitize-address-use-odr-indicator -emit-llvm -o - -triple x86_64-linux %s | FileCheck %s

// No alias on Windows but indicators should work.
// RUN: %clang_cc1 -fsanitize=address -fno-sanitize-address-use-odr-indicator -emit-llvm -o - -triple x86_64-windows-msvc %s | FileCheck %s

// XFAIL: cheerp-leaningtech-webbrowser-wasm

static int global;

int main() {
  return global;
}

// CHECK-NOT: __odr_asan_gen
// CHECK-NOT: private alias
// CHECK: [[VAR:@.*global.*]] ={{.*}} global { i32, [28 x i8] } zeroinitializer, align 32
// CHECK: @0 = internal global {{.*}} [[VAR]] to i64), {{.*}}, i64 -1 }]
// CHECK: call void @__asan_register_globals(i64 ptrtoint (ptr @0 to i64), i64 1)
// CHECK: call void @__asan_unregister_globals(i64 ptrtoint (ptr @0 to i64), i64 1)
