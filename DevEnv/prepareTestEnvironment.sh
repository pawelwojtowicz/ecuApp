ROOT=$(pwd)/..
export LD_LIBRARY_PATH=$ROOT/Bin/Target/lib
export APP_DIR=$ROOT/Bin/Target/bin
export CONFIG_DIR=$ROOT/Configuration
export LOG_DIR=$ROOT/var/log
export TMP_DIR=$ROOT/tmp
unzip ../3rdParty/gtest-1.7.0.zip -d ../3rdParty
export GOOGLE_TEST=$ROOT/3rdParty/gtest-1.7.0