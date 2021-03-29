#!/usr/bin/env python3

import os, sys, shutil, json, colorama, serial
import os.path as path

CONFIG = {}
def read_config():
    global CONFIG
    with open('ntool_cfg.json', 'r') as f:
        CONFIG = json.loads(f.read())

def get_files(p, ext):
    files = []
    for r, _, f in os.walk(p, topdown=True):
        files += [path.join(r, x) for x in f if path.splitext(x)[1] == f'.{ext}']
    return files

def execute(cmd):
    print(f'{colorama.Fore.CYAN}    -> {cmd}{colorama.Style.RESET_ALL}')
    code = os.system(cmd)
    if code != 0:
        print(f'{colorama.Fore.RED}       Error: command returned code {code}{colorama.Style.RESET_ALL}')
        exit()

def esptool(thing):
    execute(f'{CONFIG["esptool"]} --chip esp32 --before default_reset --baud {CONFIG["upload_rate"]} --after hard_reset {thing}')



def toolchain():
    return path.join(CONFIG['toolchain_path'], 'bin', CONFIG['toolchain_prefix'])
def clean():
    try:
        shutil.rmtree('.build')
    except:
        pass

def build():
    print(f'{colorama.Fore.MAGENTA}==== BUILD')
    clean()
    if not path.isdir('.build'): os.mkdir('.build')
    tc = toolchain()

    # invoke the compiler for each of the files
    for f in get_files(CONFIG['src'], 'c'):
        print(f'{colorama.Fore.GREEN}  => Compiling: {f}{colorama.Style.RESET_ALL}')
        execute(f'{tc}gcc {CONFIG["gcc_flags"]} -nostdlib -c -o .build/{path.split(f)[1]}.o {f}')

    # get the object files and link them
    o_files = get_files('.build', 'o')
    print(f'{colorama.Fore.GREEN}  => Linking')
    execute(f'{tc}ld -T link.ld -nostdlib -e neutrino_main -o .build/neutrino.elf {" ".join(o_files)}')

    # convert the ELF file into an ESP image
    esptool('elf2image --flash_mode dio --flash_freq 80m .build/neutrino.elf')

def dump():
    print(f'{colorama.Fore.MAGENTA}==== DUMP')
    execute(f'{toolchain()}objdump -DMintel .build/neutrino.elf')

def upload():
    print(f'{colorama.Fore.MAGENTA}==== UPLOAD')
    esptool('write_flash 0x1000 .build/neutrino.bin')
    #esptool('verify_flash 0x1000 .build/neutrino.bin')

def monitor():
    print(f'{colorama.Fore.MAGENTA}==== MONITOR')
    execute(f'python3 -m serial.tools.miniterm {CONFIG["monitor_port"]} {CONFIG["monitor_rate"]}')

def addr2line(a):
    execute(f'{toolchain()}addr2line --exe=.build/neutrino.elf -p {a}')



def main():
    if len(sys.argv) < 2:
        print(f'Usage: {sys.argv[0]} ' + '{build,upload,monitor,dump,bum,a2l} [...]')
        exit()
    command = sys.argv[1]
    
    read_config()

    if   command == 'build':   build()
    elif command == 'dump':    dump()
    elif command == 'upload':  upload()
    elif command == 'monitor': monitor()
    elif command == 'bum':     build(); upload(); monitor()
    elif command == 'a2l':     addr2line(sys.argv[2])
    else: print(f'Unknown command {command}')

if __name__ == '__main__': main()