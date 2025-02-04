// RUN: %clangxx_asan -O1 %s -o %t && not %run %t 2>&1 | FileCheck %s

struct IntHolder {
  int val;
};

const IntHolder *saved;

__attribute__((noinline)) void save(const IntHolder &holder) {
  saved = &holder;
}

int main(int argc, char *argv[]) {
  save({argc});
  int x = saved->val;  // BOOM
  // CHECK: ERROR: AddressSanitizer: stack-use-after-scope
  // CHECK:  #0 0x{{.*}} in {{.*main}}
  return x;
}
