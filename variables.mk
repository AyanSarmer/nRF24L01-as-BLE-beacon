# Основные параметры проекта
FILE				= sensor
MCU					= attiny85
# Папки хранения файлов
SRC_DIR       		= src
INC_DIR       		= inc
EXE_DIR       		= exe
# Список объектных файлов
SOURCES       		= $(wildcard $(SRC_DIR)/*.c)
ASM_SOURCES       	= $(wildcard $(SRC_DIR)/*.S)
OBJECTS       		= $(SOURCES:.c=.o)
OBJECTS       		+= $(ASM_SOURCES:.S=.o)
# Компилятор GCC и опции его утилит
PREAMBLE      		= avr-
CC      			= $(PREAMBLE)gcc
	CC_OPTIONS  	= -x c
	CC_OPTIONS  	+= -funsigned-char
	CC_OPTIONS  	+= -funsigned-bitfields
	CC_OPTIONS  	+= -I $(INC_DIR)
	CC_OPTIONS  	+= -Og
	CC_OPTIONS  	+= -ffunction-sections
	CC_OPTIONS  	+= -fdata-sections
	CC_OPTIONS  	+= -fpack-struct
	CC_OPTIONS  	+= -fshort-enums
	CC_OPTIONS  	+= -Wall
	CC_OPTIONS  	+= -mmcu=$(MCU)
	CC_OPTIONS  	+= -c
	CC_OPTIONS  	+= -std=gnu99
	CC_OPTIONS  	+= -o
	
	LL_OPTIONS		+= -Wl,--start-group 
	LL_OPTIONS		+= -Wl,-lm  
	LL_OPTIONS		+= -Wl,--end-group 
	LL_OPTIONS		+= -Wl,--gc-sections 
	LL_OPTIONS		+= -mmcu=$(MCU) 
	LL_OPTIONS		+= -lprintf_flt 
	LL_OPTIONS		+= -Wl,-u,vfprintf
	LL_OPTIONS		+= -o
# Копировщик и его опции
COPIER				= $(PREAMBLE)objcopy
	CP_OPTIONS		= -O ihex
# Загрузчик и его опции
UPLOADER      		= avrdude
	U_OPTIONS		= -p $(MCU)
	U_OPTIONS		+= -c usbasp
	U_OPTIONS		+= -P usb
	U_OPTIONS		+= -e
	U_OPTIONS		+= -U flash:w:$(EXE_DIR)/$(FILE).hex:i
# Чтение фьюзов
READER				= $(UPLOADER)
	R_OPTIONS		= -p m328p
	R_OPTIONS		+= -c usbasp
	R_OPTIONS		+= -P usb
	R_OPTIONS		+= -U lock:r:lock.hex:r
	R_OPTIONS		+= -U hfuse:r:hfuse.hex:r
	R_OPTIONS		+= -U lfuse:r:lfuse.hex:r
	R_OPTIONS		+= -U efuse:r:efuse.hex:r	
# Запись фьюзов
WRITER				= $(UPLOADER)
	LOCK_BYTE		= 0x3F
	LOW_BYTE		= 0xE2
	HIGH_BYTE		= 0xD9
	EXT_BYTE		= 0x07
	W_OPTIONS		= -p m328p
	W_OPTIONS		+= -c usbasp
	W_OPTIONS		+= -P usb
	W_OPTIONS		+= -U lfuse:w:$(LOW_BYTE):m
	W_OPTIONS		+= -U hfuse:w:$(HIGH_BYTE):m
	W_OPTIONS		+= -U efuse:w:$(EXT_BYTE):m 
	W_OPTIONS		+= -U lock:w:$(LOCK_BYTE):m


	
