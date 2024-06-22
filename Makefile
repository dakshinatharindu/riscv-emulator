all:
	@$(MAKE) -s -C core
	@$(MAKE) -s -C baremetal

test_baremetal: all
	@$(MAKE) -s -C core test

clean:
	$(MAKE) -C core clean
	$(MAKE) -C baremetal clean