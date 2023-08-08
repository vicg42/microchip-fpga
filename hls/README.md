# Info
* https://microchiptech.github.io/fpga-hls-docs/
## smarthls-command-line-interface
* https://microchiptech.github.io/fpga-hls-docs/userguide.html#smarthls-command-line-interface
## pragmas
* https://microchiptech.github.io/fpga-hls-docs/pragmas.html#pragmas
* https://microchiptech.github.io/fpga-hls-docs/userguide.html#loop-pipelining-1
* https://microchiptech.github.io/fpga-hls-docs/userguide.html#function-pipelining-1
* https://microchiptech.github.io/fpga-hls-docs/userguide.html#data-flow-parallelism
* https://microchiptech.github.io/fpga-hls-docs/userguide.html#multi-threading-with-smarthls-threads
## Module control
* https://microchiptech.github.io/fpga-hls-docs/userguide.html?highlight=vsim#module-control-interface
* https://microchiptech.github.io/fpga-hls-docs/userguide.html?highlight=vsim#module-control-driver
## SmartHLS C/C++ Library
*https://microchiptech.github.io/fpga-hls-docs/userguide.html?highlight=vsim#smarthls-c-c-library
## Examples
* https://github.com/MicrochipTech/fpga-hls-libraries
* https://github.com/MicrochipTech/fpga-hls-examples
* https://github.com/MicrochipTech/fpga-hls-examples/blob/main/Training1/SmartHLS_Training_Session_1.pdf

# How to build project
## ver1. (manual)
* setup enveiroment

``` sh
source /home/program/microchip/Libero_SoC_v2023.1/settings64.sh
source /home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/examples/scripts/utils/autocomplete/bash_autocomplete.sh
```
* initialization

``` sh
shls init
```

* open ./Makefile and add

```
ifneq ("$(wildcard $(GUI_BASE_DIR)Makefile.user)","")
include $(GUI_BASE_DIR)Makefile.user
endif
```

* compile

``` sh
shls sw_compile
```

* run app
``` sh
shls sw_run
```

## ver2. (auto)

``` sh
./run-shls.sh
```

# Pytest

``` sh
./run-pytest.sh
```
