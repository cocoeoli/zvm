cd ..
west build -b qemu_cortex_a53 ./hypervisor -p
west build -t run
