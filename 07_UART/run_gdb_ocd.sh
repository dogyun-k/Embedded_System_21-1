#!/bin/bash

gdb-multiarch \
    -ex "set arc arm" \
    -ex "target remote :3333" \
    -ex "file out.elf" \
    -ex "load" \
    -ex "b EXTI0_IRQHandler" \
    -ex "b USART2_IRQHandler" \
    -ex "b main:141" \
    -ex "continue"
