void neutrino_main(void) {
    while(1) {
        *(volatile unsigned int* const)0x3FF480A0 = 0xffffffff;
        *(volatile unsigned int* const)(0x3ff5F000 + 0x0060) = 0xDEADBEEF;
        *(volatile unsigned int* const)(0x3ff60000 + 0x0060) = 0xDEADBEEF;
    }
}