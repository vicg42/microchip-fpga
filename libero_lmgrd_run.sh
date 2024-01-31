#!/bin/bash

LIBERO_COMMON_PATH=/home/program/microchip/common

$LIBERO_COMMON_PATH/demons/lmgrd -c $LIBERO_COMMON_PATH/lics/License.dat -l $LIBERO_COMMON_PATH/logs/lic_log.txt  || exit 1
$LIBERO_COMMON_PATH/demons/lmutil lmstat -c $LIBERO_COMMON_PATH/lics/License.dat || exit 1

exit 0
