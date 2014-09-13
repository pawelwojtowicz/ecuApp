ROOT=$(pwd)/..
export LD_LIBRARY_PATH=$ROOT/Bin/Target/lib
export APP_DIR=$ROOT/Bin/Target/bin
export CONFIG_DIR=$ROOT/Configuration
export LOG_DIR=$ROOT/var/log
export TMP_DIR=$ROOT/tmp
unzip ../3rdParty/gmock-1.7.0.zip -d ../3rdParty
export GMOCK_DIR=$ROOT/3rdParty/gmock-1.7.0
export GOOGLE_TEST=$GMOCK_DIR/gtest

