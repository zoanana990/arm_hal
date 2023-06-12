# GDB usage in STM32F4
1. Link the openocd to the STM32F4
   ```shell
   target remote localhost:3333
   ```
2. Do the reset operation
   ```shell
   monitor reset
   monitor halt
   load
   ```
   There are some common commands
    - `c`, continue
    - `b`, break, breakpoint
      - `b 16`, add the breakpoint to the 16th lines
      - `b i=1`, when `i == 1`, the breakpoint is active
      - `i b`, the abbreviation of `info breakpoint`
      - `b main`, break when entry the `main` function
      - `d break`, delete break point
      - `d break 1`, delete the break point 1
    - `s`, step, this kind of step will get into the sub-function
    - `n`, next, this kind of next will not get into the sub-function
    - `u`, until, `u 16` represent that execute until line 16th
    - `p`, print, `p tmp`, display the value
    - `bt`, see the stack and heap
    - `x`, see the de-reference of address. That is, see the `*(pointer)` by using `x pointer`
      - example 1, show a value in the address
        ```shell
        (gdb) x 0x40011000
        0x40011000:     0x000000c0
        ```
      - example 2, show 16 value from the address
        ```shell
        (gdb) x/16w 0x40011000
        0x40011000:     0x000000c0      0x00000000      0x00000023      0x00002008
        0x40011010:     0x00000000      0x00000000      0x00000000      0x00000000
        0x40011020:     0x00000000      0x00000000      0x00000000      0x00000000
        0x40011030:     0x00000000      0x00000000      0x00000000      0x00000000
        ```
3. write image to the flash
   ```shell
   monitor flash write_image erase build/STM32F4.elf
   ```
