all:
	@$(MAKE) -s -C core
	@$(MAKE) -s -C baremetal

buildroot:
	git clone https://github.com/cnlohr/buildroot --recurse-submodules --depth 1

toolchain: buildroot
	cp -a configs/custom_kernel_config buildroot/kernel_config
	cp -a configs/buildroot_config buildroot/.config
	cp -a configs/busybox_config buildroot/busybox_config
	cp -a configs/uclibc_config buildroot/uclibc_config
	cp -a configs/uclibc_config buildroot/uclibc_config_extra
	make -C buildroot -j8
	cp -a configs/rootfsoverlay/* buildroot/output/target/
	make -C buildroot -j8

run_qemu: buildroot
	qemu-system-riscv32 -cpu rv32,mmu=false -machine virt  -nographic -bios none -kernel buildroot/output/images/Image -s -S

