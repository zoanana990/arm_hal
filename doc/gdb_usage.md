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
    - c, continue
    - b, break, breakpoint
      - b 16, add the breakpoint to the 16th lines
      - b i=1, when i == 1, the breakpoint is active
      - i b, the abbreviation of "info breakpoint"
      - b main, break when entry the main function
      - d break, delete break point
      - d break 1, delete the break point 1
    - s, step, this kind of step will get into the subfunction
    - n, next, this kind of next will not get into the subfunction
    - u, until, u 16 represent that execute until line 16th
    - p, print, p tmp, display the value
    - bt, see the stack and heap
3. write image to the flash
   ```shell
   monitor flash write_image erase build/STM32F4.elf
   ```
