include variables.mk

all: $(FILE).hex

$(FILE).hex: $(EXE_DIR)/$(FILE).elf
	$(COPIER) $(CP_OPTIONS) $< $(EXE_DIR)/$@

%.elf: $(OBJECTS)
	mkdir -p $(EXE_DIR)
	$(CC) $(LL_OPTIONS) $@ $^
	
%.o: %.c
	$(CC) $(CC_OPTIONS) $@ $<

upload:
	$(UPLOADER) $(U_OPTIONS)

size:
	avr-size $(EXE_DIR)/$(FILE).elf

read:
	$(READER) $(R_OPTIONS)

write:
	$(WRITER) $(W_OPTIONS)