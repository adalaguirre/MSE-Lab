#This is my first makefile

include sources.mk

EXEC = app.elf

# Architecure Specific flags
LINKER_FILE = stm32f411.ld
CPU = cortex-m4
ARCH = armv7e-m
SPECS = nosys.specs
FPU = fpv4-sp-d16

ARCHFLAGS = -mcpu=$(CPU) -mthumb -march=$(ARCH) -mfloat-abi=hard -mfpu=$(FPU) --specs=$(SPECS)

OBJS := $(SRCS:.c=.o) # Creating Object List from Source List

CC = arm-none-eabi-gcc

# Compiler Flags
CFLAGS = -g -O0 -std=c99 -Werror -Wall $(ARCHFLAGS)

# Linker Flags
LDFLAGS = -nostdlib -T $(LINKER_FILE)

# Sizeflags
SZFLAGS = -Btd

%.o : %.c 
	$(CC) -c $< $(CFLAGS) $(INCLUDES) -o $@

app : $(OBJS)
	$(CC) $(OBJS) -o $@
	

.PHONY : clean
clean:
	rm -f $(OBJS) $(EXEC)

.PHONY : build
build: $(EXEC)

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(INCLUDES) $(LDFLAGS) -o $@

.PHONY : flash
flash: 
	openocd -f board/st_nucleo_f4.cfg -c "program $(EXEC) verify reset" -c shutdown