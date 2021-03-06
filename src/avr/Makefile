# Additional avr build rules

# Use the avr toolchain
CROSS_PREFIX=avr-

dirs-y += src/avr lib/pjrc_usb_serial

CFLAGS += -mmcu=$(CONFIG_MCU)

# Add avr source files
src-y += avr/main.c avr/timer.c avr/gpio.c
src-$(CONFIG_AVR_WATCHDOG) += avr/watchdog.c
src-$(CONFIG_AVR_USBSERIAL) += avr/usbserial.c ../lib/pjrc_usb_serial/usb_serial.c
src-$(CONFIG_AVR_SERIAL) += avr/serial.c

# Suppress broken "misspelled signal handler" warnings on gcc 4.8.1
CFLAGS_klipper.elf := $(CFLAGS_klipper.elf) $(if $(filter 4.8.1, $(shell $(CC) -dumpversion)), -w)

# Build the additional hex output file
target-y += $(OUT)klipper.elf.hex

$(OUT)klipper.elf.hex: $(OUT)klipper.elf
	@echo "  Creating hex file $@"
	$(Q)$(OBJCOPY) -j .text -j .data -O ihex $< $@

flash: $(OUT)klipper.elf.hex
	@echo "  Flashing $(FLASH_DEVICE) via avrdude"
	$(Q)avrdude -p$(CONFIG_MCU) -cwiring -P"$(FLASH_DEVICE)" -D -U"flash:w:$(OUT)klipper.elf.hex:i"
