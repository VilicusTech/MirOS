# Remake the kernel
make 

# Rebuild the ISO 
./makeiso.sh

# Run QEMU
qemu-system-x86_64 -drive file=image.iso -display gtk -serial stdio