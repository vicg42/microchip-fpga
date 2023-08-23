#!/bin/sh

SCRIPT_NAME=`basename "$0"`

WORK_DIR=./
#SHLS_CMD=" "

help()
{
    echo "Usage: $SCRIPT_NAME [options]";
    echo "Options:";
    echo "    -h --help             help";
    echo "    -d --dir              path to work dir. default: $WORK_DIR"
    echo "    -c --cmd              apply one of shls console commands."
    echo ""
    echo "Examples: ";
    echo "    < get help using $SCRIPT_NAME >:             $SCRIPT_NAME -h "
    echo "    < get help shls commands >:                   $SCRIPT_NAME -c -h "
    echo "    < apply shls command >:                       $SCRIPT_NAME -c hw"
    echo "    < apply shls commands sw_compile & sw_run >:  $SCRIPT_NAME"
    echo " "
}
SHORTARG_LIST=(
    "hd:c:"
)
LONGARG_LIST=(
    "help",
    "dir:",
    "cmd",
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

        -c | --cmd)
                shift
                SHLS_CMD=$1
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

if [[ -z $SHLS_CMD ]]; then
    shls sw_run -a
else
    shls $SHLS_CMD
fi
