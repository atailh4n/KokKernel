CC=gcc
NASM=nasm
CFLAGS=-m32 -ffreestanding -nostdlib -Wall -Wextra
LDFLAGS=-m elf_i386 --no-warn-rwx-segment
OBJS=boot.o kernel.o memorymgr.o lib/itoa.o drivers/vga.o drivers/keyboard.o progs/ez_alloc.o
INCLUDE_PATH=../includes

# Varsayılan hedef: kernel.bin oluşturulacak
all: kernel.bin

# boot.asm dosyasını derlemek
boot.o: boot.asm
	$(NASM) -f elf32 -o $@ $<

# C dosyalarını derlemek
%.o: %.c
	$(CC) -I $(INCLUDE_PATH) $(CFLAGS) -c $< -o $@

# kernel.bin'i oluşturma
kernel.bin: $(OBJS)
	ld $(LDFLAGS) -T linker.ld -o kernel.bin $(OBJS)

# Temizlik: Derleme dosyalarını ve kernel.bin'i silme
clean:
	rm -f $(OBJS) kernel.bin