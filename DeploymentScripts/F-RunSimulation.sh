#!/bin/bash
source deploymentPaths

LINUX_IMG_PATH=$THIRD_PARTY_COMPONENTS/$KERNEL_VERSION/arch/arm/boot/zImage

echo starting up the qemu
echo "kernel=[$LINUX_IMG_PATH]"
echo "rootfs=[$ROOT_FILE_SYSTEM_IMAGE]"

qemu-system-arm -m 128 -M versatilepb -net nic -net user,hostfwd=tcp::8080-:80 -kernel $LINUX_IMG_PATH -initrd $ROOT_FILE_SYSTEM_IMAGE -nographic -append "console=ttyAMA0,115200 root=/dev/ram init=linuxrc" 
