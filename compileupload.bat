@echo off
SET BOARD=at90usb1286
SET CLOCK=8000000
SET fName=%1

if '%1' equ  set /p fName=Input file name:

echo Compiling file %fName% and creating hex object:
for /f "tokens=* delims= " %%F in ('echo %fName%') do (
	avr-gcc -mmcu=%BOARD% -DF_CPU=%CLOCK% -Os "%%~pdnxF" -o "%%~pdnF.elf"
	avr-objcopy -O ihex "%%~pdnF.elf" "%%~pdnF.hex"
	echo ---Compiled and Hex Created---
	pause

	echo Flashing hex program %%~nF.hex to board:
	dfu-programmer %BOARD% erase 
	dfu-programmer %BOARD% flash "%%~pdnF.hex"
	dfu-programmer %BOARD% reset
)
echo ---Object Uploaded---
pause