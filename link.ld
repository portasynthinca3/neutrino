MEMORY
{
    DRAM (wx): ORIGIN = 0x3FFAE000, LENGTH = 0x51FFF
    IRAM (rx): ORIGIN = 0x40080000, LENGTH = 0x3FFFF
}

SECTIONS
{
    .literal : 
    {
        *(.literal)
    } > IRAM,
    
    .text : 
    {
        *(.text)
    } > IRAM
}