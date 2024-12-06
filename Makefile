###############################################################################
#	makefile
#	 by Alex Chadwick
#
#	A makefile script for generation of raspberry pi kernel images.
###############################################################################

# The toolchain to use. arm-none-eabi works, but there does exist 
# arm-bcm2708-linux-gnueabi.
ARMGNU ?= aarch64-linux-gnu

# The version of raspberry pi in use
RPI_VERSION = 3BPLUS

# The mount drive
BOOTMNT = /media/yassine/bootfs

# The intermediate directory for compiled object files.
BUILD = build/

# The directory in which source files are stored.
SOURCE = source/

# The directory in wich header files are stored
INCLUDE = include

# The flags for the compiler
FLAGS = -DRPI_VERSION=$(RPI_VERSION) -Wall -nostdlib -nostartfiles -ffreestanding \
		-I $(include) -mgeneral-regs-only

# The name of the output file to generate.
TARGET = kernel8.img

# The name of the assembler listing file to generate.
LIST = kernel.list

# The name of the map file to generate.
MAP = kernel.map

# The name of the linker script to use.
LINKER = kernel.ld

# The names of all object files that must be generated. Deduced from the 
# assembly code files in source.
OBJECTS = $(patsubst $(SOURCE)%.S,$(BUILD)%.o,$(wildcard $(SOURCE)*.S))
OBJECTS += $(patsubst $(SOURCE)%.c,$(BUILD)%.o,$(wildcard $(SOURCE)*.c))

# Rule to make everything.
all: $(TARGET) $(LIST)

# Rule to remake everything. Does not include clean.
rebuild: all

# Rule to make the listing file.
$(LIST) : $(BUILD)output.elf
	@echo "Creating listing file $@"
	$(ARMGNU)-objdump -d $(BUILD)output.elf > $(LIST)

# Rule to make the image file.
$(TARGET) : $(BUILD)output.elf
	@echo "Making the image file $@"
	$(ARMGNU)-objcopy $(BUILD)output.elf -O binary $(TARGET)
	cp $(TARGET) $(BOOTMNT)
	cp config.txt $(BOOTMNT)
	sync

# Rule to make the elf file.
$(BUILD)output.elf : $(OBJECTS) $(LINKER)
	@echo "Creating elf file $@"
	$(ARMGNU)-ld $(OBJECTS) -Map $(MAP) -o $(BUILD)output.elf -T $(LINKER)

# Rule to make the object files from asm files.
$(BUILD)%.o: $(SOURCE)%.S $(BUILD)
	@echo "Making ASM object file $@"
	$(ARMGNU)-gcc $(FLAGS) -I $(INCLUDE) -MMD -c $< -o $@

# Rule to make the object files from c files.
$(BUILD)%.o: $(SOURCE)%.c $(BUILD)
	@echo "Making C object file $@"
	$(ARMGNU)-gcc $(FLAGS) -I $(INCLUDE) -MMD -c $< -o $@

$(BUILD):
	@echo "Making build directory"
	@mkdir -p $@

# Rule to clean files.
clean : 
	-rm -rf $(BUILD)
	-rm -f $(TARGET)
	-rm -f $(LIST)
	-rm -f $(MAP)