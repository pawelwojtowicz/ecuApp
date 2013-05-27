IMAGE_OUTPUT=$(pwd)/rootfs.cpio
cd $STAGING
find . | cpio -o -H newc > $IMAGE_OUTPUT
