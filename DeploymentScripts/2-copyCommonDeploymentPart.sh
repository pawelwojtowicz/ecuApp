echo "Common config files"
cp -r ConfigurationFiles/Common/* $STAGING

echo "copying busybox"
cp -r $BUSYBOX/bin $STAGING
cp -r $BUSYBOX/sbin $STAGING

cd $STAGING

echo "linking the init with BusyBox"
ln -s bin/busybox init 
