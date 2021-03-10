#    Copyright (c) 2016 Manuel Sabban <manu@sabban.eu>
    
#    Permission is hereby granted, free of charge, to any person 
#    obtaining a copy of this software and associated documentation 
#    files (the "Software"), to deal in the Software without 
#    restriction, including without limitation the rights to use, copy, 
#    modify, merge, publish, distribute, sublicense, and/or sell copies 
#    of the Software, and to permit persons to whom the Software is 
#    furnished to do so, subject to the following conditions:
#    The above copyright notice and this permission notice shall be 
#    included in all copies or substantial portions of the Software.
#    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
#    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
#    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
#    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
#    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
#    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
#    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
#    DEALINGS IN THE SOFTWARE.

TARGET=atmega32

all: main.elf

i2co:
	${MAKE} -C i2c

ds1307read: i2c
	${MAKE} -C ds1307

ds1307write: i2c
	${MAKE} -C ds1307

ds1307: ds1307read ds1307write

main.o: main.c
	avr-gcc -mmcu=${TARGET} -c main.c -o main.o -Os

main.elf:  main.o ds1307 i2co
	avr-gcc -mmcu=${TARGET} -o  main.elf main.o i2c/i2c.o ds1307/ds1307read.o ds1307/ds1307write.o

dude:
	avrdude -P /dev/ttyACM0 -b 19200 -c avrisp -p ${TARGET} -U "flash:w:main.elf:a"

clean:
	rm -f main.o
	rm -f main.elf
	rm -f *~
	rm -f ds1307/ds1307*.o
	rm -f i2c/i2c.o
	find . -name "*"~ -exec rm -f {} \;
