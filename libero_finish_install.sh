#!/bin/bash

LIB_SLV_F_1YR=~/work/_install/LIB-SLV-F-1YR.dat
SmartHLS_F_1YR=~/work/_install/SmartHLS-F-1YR.dat

LIBERO_PATH=/home/program/microchip/Libero_SoC_v2023.2
SmartHLS_VER=SmartHLS-2023.2
LIBERO_COMMON_PATH=/home/program/microchip/common


if [[ ! -f $LIB_SLV_F_1YR ]]; then
    echo "Error: can't find $LIB_SLV_F_1YR"
    exit 1
fi

if [[ ! -f $SmartHLS_F_1YR ]]; then
    echo "Error: can't find $SmartHLS_F_1YR"
    exit 1
fi

if [[ ! -d $LIBERO_COMMON_PATH/demons ]]; then
    echo "Warning: can't find $LIBERO_COMMON_PATH/demons. Create $LIBERO_COMMON_PATH/demons"
    mkdir -p $LIBERO_COMMON_PATH/demons || exit 1
fi

for arg in actlmgrd lmgrd lmutil mgcld snpslmd
do
    if [[ ! -f $LIBERO_COMMON_PATH/demons/$arg ]]; then
        cp -v $LIBERO_PATH/Libero/bin64/$arg $LIBERO_COMMON_PATH/demons
        if [[ ! $? -eq 0 ]]; then
            echo "Error: can't find $LIBERO_PATH/Libero/bin64/$arg"
            exit 1
        fi
    fi
done

if [[ ! -d $LIBERO_COMMON_PATH/lics ]]; then
    echo "Warning: can't find $LIBERO_COMMON_PATH/lics. Create $LIBERO_COMMON_PATH/lics"
    mkdir -p $LIBERO_COMMON_PATH/lics || exit 1
    cp -v $LIB_SLV_F_1YR $LIBERO_COMMON_PATH/lics/License.dat || exit 1

    echo "Edit $LIBERO_COMMON_PATH/lics/License.dat ...."

    HOST_ID=$(hostname) || exit 1
    sed -i "s/<put.hostname.here>/$HOST_ID/g" $LIBERO_COMMON_PATH/lics/License.dat || exit 1

    STRING_EDITED="$LIBERO_COMMON_PATH/demons/actlmgrd port=1702"
    STRING_EDITED_SED=$(echo $STRING_EDITED | sed 's#/#\\/#g') #get absolute path and replace / to \/
    sed -i "s/PATH\/actlmgrd/$STRING_EDITED_SED/g" $LIBERO_COMMON_PATH/lics/License.dat || exit 1

    #remove first the first occurrence in a file
    sed -i '0,/1702/s/1702//' $LIBERO_COMMON_PATH/lics/License.dat || exit 1

    STRING_EDITED="$LIBERO_COMMON_PATH/demons/mgcld port=1703"
    STRING_EDITED_SED=$(echo $STRING_EDITED | sed 's#/#\\/#g') #get absolute path and replace / to \/
    sed -i "s/PATH\/mgcld/$STRING_EDITED_SED/g" $LIBERO_COMMON_PATH/lics/License.dat || exit 1

    STRING_EDITED="$LIBERO_COMMON_PATH/demons/snpslmd port=1704"
    STRING_EDITED_SED=$(echo $STRING_EDITED | sed 's#/#\\/#g') #get absolute path and replace / to \/
    sed -i "s/PATH\/snpslmd/$STRING_EDITED_SED/g" $LIBERO_COMMON_PATH/lics/License.dat || exit 1

    STRING_EDITED=$(find $SmartHLS_F_1YR -type f -print | xargs grep "INCREMENT SmartHLS actlmgrd")
    echo "$STRING_EDITED" >> $LIBERO_COMMON_PATH/lics/License.dat

    STRING_EDITED=$(find $SmartHLS_F_1YR -type f -print | xargs grep "INCREMENT SmartHLS_SOC actlmgrd")
    echo "$STRING_EDITED" >> $LIBERO_COMMON_PATH/lics/License.dat

    echo "Edit $LIBERO_COMMON_PATH/lics/License.dat - Done"
fi

if [[ ! -f $LIBERO_PATH/settings64.sh ]]; then
    echo "Warning: can't find $LIBERO_PATH/settings64.sh. Create $LIBERO_PATH/settings64.sh"

    touch $LIBERO_PATH/settings64.sh

    echo "Edit $LIBERO_PATH/settings64.sh ..."

    echo "# For Floating License from a License Servers" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export LIBERO=$LIBERO_PATH" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export LIBERO_ROOTDIR=\$LIBERO/Libero/bin" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export LIBERO_LIBDIR=\$LIBERO/Libero/lib64" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export LIBERO_SHLS=\$LIBERO/$SmartHLS_VER/SmartHLS/bin/" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "#export LIBERO_MODELSIM=\$LIBERO/ModelSimPro/modeltech/bin/" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export LIBERO_MODELSIM=\$LIBERO/ModelSimPro/modeltech/linuxacoem/" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export PATH=\$LIBERO_MODELSIM:\$LIBERO_SHLS:\$LIBERO_ROOTDIR:\$PATH" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export LD_LIBRARY_PATH=\$LIBERO_LIBDIR:\$LD_LIBRARY_PATH" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "# For real display 0 for remote display 1" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export DISPLAY=:1" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "# <1702> is the port number of libero" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "# <1703> is the port number of modelsim" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "# <1704> is the port number of synopsys" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "# localhost is server address" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export LM_LICENSE_FILE=1702@localhost:\$LM_LICENSE_FILE" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export LM_LICENSE_FILE=1703@localhost:\$LM_LICENSE_FILE" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export SNPSLMD_LICENSE_FILE=1704@localhost:\$SNPSLMD_LICENSE_FILE" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "" >> $LIBERO_PATH/settings64.sh || exit 1
    echo "export MTI_VCO_MODE=32" >> $LIBERO_PATH/settings64.sh || exit 1

    echo "Edit $LIBERO_PATH/settings64.sh - Done"
fi

$LIBERO_COMMON_PATH/demons/lmgrd -c $LIBERO_COMMON_PATH/lics/License.dat -l $LIBERO_COMMON_PATH/logs/lic_log.txt  || exit 1
$LIBERO_COMMON_PATH/demons/lmutil lmstat -c $LIBERO_COMMON_PATH/lics/License.dat || exit 1

exit 0
