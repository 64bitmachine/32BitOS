
GPPPARAMS	= -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings
ASPARAMS	= --32
LDPARAMS	= -melf_i386

objects = loader.o gdt.o port.o interruptstubs.o interrupts.o keyboard.o kernel.o

%.o: %.cpp
	g++ $(GPPPARAMS) -o $@ -c $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

32bitkernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

install: 32bitkernel.bin
	echo "32 bit kernel created"

32bitkernel.iso: 32bitkernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "32 Bit OS" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/32bitkernel.bin' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

run: 32bitkernel.iso
	rm -rf docs
	doxygen config/doc
	(killall VirtualBoxVM && sleep 1) || true
	VirtualBoxVM --startvm "32 Bit OS" &

.PHONY: clean
clean:
	rm -rf $(objects) 32bitkernel.bin 32bitkernel.iso