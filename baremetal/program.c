int multiply(int a, int b) {
  int result;
  result = a * b;
  return result;
}

static void print(const char *s) {
  asm volatile(".option norvc\ncsrrw x0, 0x138, %0\n" : : "r"(s));
}

int main() {
  int a = 6;
  int b = 7;
  int product = multiply(a, b);

  print("Hello from RISC-V");

  return 0;
}
