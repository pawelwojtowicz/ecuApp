CURR_DIR=$(pwd)

KERNEL_DIR=linux-3.3.3

LINUX_IMG_PATH=$CURR_DIR/$KERNEL_DIR/arch/arm/boot/zImage

echo "starting qemu with "$LINUX_IMG_PATH

qemu-system-arm -m 128 -M versatilepb -kernel $LINUX_IMG_PATH -nographic -append "console=ttyAMA0,115200 initrd=dev/ram0 init=init"
