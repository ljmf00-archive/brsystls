
#if !defined(__i386__)
#error "Compiler isn't ix86-elf"
#endif
#if defined(__linux__)
#error "Use a cross-compiler!"
#endif