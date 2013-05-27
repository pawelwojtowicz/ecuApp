cp $TOOLCHAIN_LIB/libm-2.12.1.so $TARGET_LIB
cp $TOOLCHAIN_LIB/libc-2.12.1.so $TARGET_LIB
cp $TOOLCHAIN_LIB/ld-2.12.1.so $TARGET_LIB

cd $TARGET_LIB
ln -s libm-2.12.1.so libm.so.6
ln -s libc-2.12.1.so libc.so.6
ln -s ld-2.12.1.so ld-linux.so.3
