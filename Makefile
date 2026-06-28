all:
	

buildroot:
	git clone https://github.com/cnlohr/buildroot --recurse-submodules --depth 1
	cp -a configs/custom_kernel_config buildroot/kernel_config
	cp -a configs/buildroot_config buildroot/.config
	cp -a configs/busybox_config buildroot/busybox_config
	cp -a configs/uclibc_config buildroot/uclibc_config
	cp -a configs/uclibc_config buildroot/uclibc_config_extra
	make -C buildroot -j8
	cp -a configs/rootfsoverlay/* buildroot/output/target/
	make -C buildroot -j8

run:
	./remu/build/bin/remu -k buildroot/output/images/Image -d remu/resources/dtb/mini.dtb

clean:
	rm -rf buildroot