#!/bin/bash
source deploymentPaths

LINUX_IMG_PATH=$THIRD_PARTY_COMPONENTS/$KERNEL_VERSION/arch/arm/boot/zImage

echo "starting qemu with "$LINUX_IMG_PATH


qemu-system-arm -m 128 -M versatilepb -kernel $LINUX_IMG_PATH -nographic -append "console=ttyAMA0,115200 root=dev/ram"
