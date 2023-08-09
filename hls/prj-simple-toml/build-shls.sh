#!/bin/sh

WORK_DIR=./

help()
{
    echo "Usage: ./$SCRIPT_NAME [options]";
    echo "Options:";
    echo "    -h --help             help";
    echo "    -d --dir              path to work dir. default: $WORK_DIR"
    echo ""
    echo "Example: ./$SCRIPT_NAME -h ";
}
SHORTARG_LIST=(
    "hd:"
)
LONGARG_LIST=(
    "help",
    "dir:",
)
opts=$(getopt \
    --options "$(printf "%s," "${SHORTARG_LIST[@]}")" \
    --longoptions "$(printf "%s," "${LONGARG_LIST[@]}")" \
    --name "$(basename "$0")" \
    -- "$@"
)
if [ $? -ne 0 ]; then
    exit 1
fi

eval set -- ${opts}
while true; do
    case "$1" in
        -h | --help)
                help
                exit 0
                ;;

        -d | --dir)
                shift
                WORK_DIR=$1
                ;;

        --)
            shift
            break
            ;;

        *)
            help
            exit 1
            ;;
    esac
    shift
done

cd $WORK_DIR

rm ./output*.*

source /home/program/microchip/Libero_SoC_v2023.1/settings64.sh
source /home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/examples/scripts/utils/autocomplete/bash_autocomplete.sh

shls sw_run -a
