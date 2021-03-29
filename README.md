# neutrino
Neutrino is an operating system for ESP32 that aims to provide preemptive multitasking and leverage its MMU, MPU and PID peripherals

# building
`./ntool.py build` - build only\
`./ntool.py upload` - upload the built image\
`./ntool.py monitor` - open a serial monitor\
`./ntool.py dump` - invoke objdump on the built image\
`./ntool.py bum` - build, upload and monitor

# config
`ntool_cfg.json`:
```js
{
    "toolchain_path": "/path/to/your/esp32/toolchain",
    "toolchain_prefix": "xtensa-esp32-elf-",
    "verbose": true, /* false will prevent ntool from logging every command it's executing */
    "src": "./src",
    "gcc_flags": "-O2 -Wall",

    "esptool": "python3 -m esptool", /* command used to invoke esptool */
    "upload_rate": "2000000", /* baud (bit/s) */
    "monitor_port": "/dev/ttyUSB0", /* set this to your serial port */
    "monitor_rate": "115200"
}
```