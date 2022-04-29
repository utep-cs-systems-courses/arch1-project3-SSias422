# makefile configuration

COMMON_OBJECTS	= main.o  #Wdinterrupthandler.o 
CPU		= msp430g2553
CFLAGS		= -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#Switch the compiler (for the internal make rules)
CC		= msp430-elf-gcc
AS		= msp430-elf-as
AR		= msp430-elf-ar

all: led.elf

libLcd.a: font-11x16.o font-5x7.o font-8x12.o lcdutils.o lcddraw.o
	$(AR) crs $@ $^

lcddraw.o: lcddraw.c lcddraw.h lcdutils.h
lcdutils.o: lcdutils.c lcdutils.h

#additional rules for files
led.elf: ${COMMON_OBJECTS} 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} $^ -o $@ -lTimer

load: led.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

main.o: led.h

wdInterrruptHandler.o: led.h
