
# nspire-nd-demos

demos built with [nspire-nd](https://github.com/0xFireball/nspire-nd), a 2d framework that runs on both desktop and `ndless` on the TI Nspire.

## Build

Linux/Unix: `make OUTDIR=linux PLATFORM=desktop`

Windows: `make OUTDIR=win PLATFORM=desktop CYGWIN=1 GXX=/cygdrive/c/TDM-GCC-64/bin/g++` (update the compiler path). Make sure you have all the required SDL headers and libs in `cyg/include` and `cyg/lib`.

Nspire: `make OUTDIR=binspire PLATFORM=nspire DEBUG=1`

Add `DEBUG=1` for debug symbols.

## Hacking

Debugging on desktop should be relatively painless,
and VSCode launch config is set up to debug the desktop
binary with GDB.

When debugging the Nspire you will have to use remote GDB:
`arm-none-eabi-gdb -tui -ex "target remote :3333" -ex "c" -ex "bt" pong.elf`
