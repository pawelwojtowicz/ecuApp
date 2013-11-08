echo "Creating root directory for target filesystem on: "$STAGING
mkdir $STAGING

echo "Creating basic directory structure"
mkdir $STAGING/dev
mkdir $STAGING/dev/pts
mkdir $STAGING/etc
mkdir $STAGING/etc/init.d
mkdir $STAGING/proc
mkdir $STAGING/sys
mkdir $STAGING/root
mkdir $STAGING/bin
mkdir $STAGING/lib

echo "creating device files"
mknod $STAGING/dev/console c 5 1
mknod $STAGING/dev/null c 1 3

