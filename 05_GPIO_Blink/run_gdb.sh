#!/bin/bash

gdb-multiarch \
        -ex "target remote :3333" \
        -s "out.elf" \
    	-ex "load" \
    	-ex "b main" \
    	-ex "set arc arm" \
        -ex "monitor system_reset" \
        -ex "continue" 
