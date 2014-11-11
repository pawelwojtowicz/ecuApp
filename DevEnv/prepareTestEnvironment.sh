ROOT=$(pwd)/..
export LD_LIBRARY_PATH=$ROOT/Bin/Target/lib
export APP_DIR=$ROOT/Bin/Target/bin
export CONFIG_DIR=$ROOT/Configuration
export LOG_DIR=$ROOT/Bin/Target/var/log
export VAR_RUN=$ROOT/Bin/Target/var/run
export TMP_DIR=$ROOT/Bin/Target/tmp
export UNITTEST_DIR=$ROOT/UnitTestSrc
unzip ../3rdParty/gmock-1.7.0.zip -d ../3rdParty
export GMOCK_DIR=$ROOT/3rdParty/gmock-1.7.0
export GOOGLE_TEST=$GMOCK_DIR/gtest

