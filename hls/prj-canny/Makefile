SRCS=canny.cpp gaussian_filter.cpp gf_sw.cpp hf_sw.cpp hysteresis_filter.cpp nm_sw.cpp nonmaximum_suppression.cpp sf_sw.cpp sobel_filter.cpp util.cpp
LOCAL_CONFIG = -legup-config=config.tcl
LEVEL = $(LEGUP_ROOT_DIR)/examples

ifneq ("$(wildcard $(GUI_BASE_DIR)Makefile.user)","")
include $(GUI_BASE_DIR)Makefile.user
endif
include $(LEVEL)/Makefile.common
