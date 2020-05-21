#!/bin/bash

#Arguments: flag and file
FLAG=$1
FILE=$2
FILE_HEAD=$(echo $FILE | cut -f1 -d".")

case $FLAG in
        -hex)
                echo "Compiling file '$FILE' and creating hex object:"
                avr-gcc -mmcu=at90usb1286 -DF_CPU=8000000 -Wall -Os $FILE -o $FILE_HEAD.elf
                avr-objcopy -O ihex $FILE_HEAD.elf $FILE_HEAD.hex

                echo "DONE. Flash using flag -load"
                ;;
        -load)
                echo "Flashing hex program '$FILE' to board:"
                dfu-programmer at90usb1286 erase
                dfu-programmer at90usb1286 flash $FILE_HEAD.hex
                dfu-programmer at90usb1286 reset

                echo "DONE. Restart your LaFortuna board."
                ;;
        -all)
                echo "Compiling file '$FILE' and creating hex object:"
                avr-gcc -mmcu=at90usb1286 -DF_CPU=8000000 -Wall -Os $FILE -o $FILE_HEAD.elf
                avr-objcopy -O ihex $FILE_HEAD.elf $FILE_HEAD.hex

                echo "Flashing hex program '$FILE_HEAD' to board:"
                dfu-programmer at90usb1286 erase
                dfu-programmer at90usb1286 flash $FILE_HEAD.hex
                dfu-programmer at90usb1286 reset

                echo "Delete temporary files"
                rm $FILE_HEAD.elf
                rm $FILE_HEAD.hex

                echo "DONE. Power cycle your LaFortuna board."
                ;;
        -info)
                echo "------Compile & Flash script for LaFortuna------"
                echo "--Adapted from ak6g12's script by ec6g13 2015--"
esac
