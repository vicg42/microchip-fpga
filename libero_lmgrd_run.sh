#!/bin/bash

LIB_SLV_F_1YR=./LIB-SLV-F-1YR.dat
SmartHLS_F_1YR=./SmartHLS-F-1YR.dat

LIBERO_PATH=/home/program/microchip/Libero_SoC_v2023.1 #./program/microchip/Libero_SoC_v2023.1 #
LIBERO_COMMON_PATH=/home/program/microchip/common


if [[ ! -d $LIBERO_COMMON_PATH/demons ]]; then
    echo "can't find $LIBERO_COMMON_PATH/demons" || exit 1
fi

if [[ ! -f $LIBERO_PATH/Libero/bin64/actlmgrd ]]; then
    echo "can't find $LIBERO_PATH/Libero/bin64/actlmgrd" || exit 1
fi


$LIBERO_COMMON_PATH/demons/lmgrd -c $LIBERO_COMMON_PATH/lics/License.dat -l $LIBERO_COMMON_PATH/logs/lic_log.txt  || exit 1

$LIBERO_COMMON_PATH/demons/lmutil lmstat -c $LIBERO_COMMON_PATH/lics/License.dat || exit 1

exit 0