# Info
* https://microchiptech.github.io/fpga-hls-docs/
* https://microchiptech.github.io/fpga-hls-docs/userguide.html#smarthls-command-line-interface
* https://github.com/MicrochipTech/fpga-hls-libraries
* https://github.com/MicrochipTech/fpga-hls-examples

# How to use
* source /home/program/microchip/Libero_SoC_v2023.1/settings64.sh
* source /home/program/microchip/Libero_SoC_v2023.1/SmartHLS-2023.1/SmartHLS/examples/scripts/utils/autocomplete/bash_autocomplete.sh
* shls init
* open ./Makefile and add

```
ifeq ($(shell uname -o), Cygwin)
# Use cygpath to locate the Windows location
OPENCV_PATH := $(shell cygpath -t mixed $(LEGUP_ROOT_DIR)/precompiled_sw_libraries/opencv4.5.4-x86_64-cygwin)
else
OPENCV_PATH := $(LEGUP_ROOT_DIR)/precompiled_sw_libraries/opencv4.5.4-x86_64-linux
endif

USER_CXX_FLAG += -I$(OPENCV_PATH)/include/opencv4 -I./include
USER_LINK_FLAG += -L$(OPENCV_PATH)/lib -lopencv_core -lopencv_imgcodecs -lopencv_imgproc

ifeq ($(shell uname -o), Cygwin)
# Use semicolons as PATH separator on Windows
USER_ENV_VARS := PATH=$(OPENCV_PATH)/bin;$$PATH
else
USER_ENV_VARS := LD_LIBRARY_PATH=$(OPENCV_PATH)/lib
endif

PROGRAM_ARGUMENTS = -i ./iF-1.bmp -o ./oF-1.bmp
```

* shls sw_compile
* shls sw_run
