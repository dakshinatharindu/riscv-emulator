all:
	@$(MAKE) -s -C core
	@$(MAKE) -s -C baremetal

test_baremetal: all
	@$(MAKE) -s -C core test

clean:
	$(MAKE) -C core clean
	$(MAKE) -C baremetal clean

buildroot:
	git clone https://github.com/buildroot/buildroot.git

toolchain: buildroot
	make -C buildroot qemu_riscv32_nommu_virt_defconfig
	LD_LIBRARY_PATH="" make -C buildroot -j8
