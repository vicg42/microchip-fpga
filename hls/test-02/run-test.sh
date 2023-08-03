#!/bin/sh

cd /home/v.halavachenka/work/microchip-hls/vicg-hls-test-02/

rm ./inputF-*.bmp
rm ./outputF-*.bmp

source /home/program/microchip/Libero_SoC_v2023.1/settings64.sh
source /home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/examples/scripts/utils/autocomplete/bash_autocomplete.sh

shls sw_run -a