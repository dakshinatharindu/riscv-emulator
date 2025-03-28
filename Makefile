all:
	@$(MAKE) -s -C core
	@$(MAKE) -s -C baremetal

test_baremetal: all
	@$(MAKE) -s -C core test

clean:
	$(MAKE) -C core clean
	$(MAKE) -C baremetal clean

buildroot:
	git clone https://github.com/cnlohr/buildroot --recurse-submodules --depth 1

toolchain: buildroot
	cp -a configs/custom_kernel_config buildroot/kernel_config
	cp -a configs/buildroot_config buildroot/.config
	cp -a configs/busybox_config buildroot/busybox_config
	cp -a configs/uclibc_config buildroot/uclibc_config
	cp -a configs/uclibc_config buildroot/uclibc_config_extra
	true || cp -a configs/rootfsoverlay/* buildroot/output/target/
	make -C buildroot