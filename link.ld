MEMORY
{
    DRAM (wx): ORIGIN = 0x3FFF0000, LENGTH = 0x51000
    IRAM (rx): ORIGIN = 0x40080000, LENGTH = 0x20000
}

SECTIONS
{
    .rodata :
    {
        *(.rodata)
    } > DRAM,

    .literal :
    {
        *(.literal)
    } > IRAM,

    .text :
    {
        *(.text)
    } > IRAM
}