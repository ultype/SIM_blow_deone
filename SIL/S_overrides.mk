MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
DRONE_HOME := $(patsubst %/SIL/S_overrides.mk, %, $(MKFILE_PATH))

$(info MKFILE_PATH = $(MKFILE_PATH))
$(info DRONE_HOME = $(DRONE_HOME))

INCLUDES = -I${TRICK_HOME}/trick_models \
		   -I$(DRONE_HOME)/models/drone/include/ \
		   -I$(DRONE_HOME)/models/wind/include/ \
		   -I$(DRONE_HOME)/models/dynamic/include/

TRICK_CFLAGS += --std=c++11 ${INCLUDES} -g -D_GNU_SOURCE -DCONFIG_SIL_ENABLE
TRICK_CFLAGS += -Wall -Wmissing-prototypes -Wextra -Wshadow -Imodels
TRICK_CXXFLAGS += --std=c++11 ${INCLUDES} -g -DCONFIG_SIL_ENABLE
TRICK_CXXFLAGS += -Wall -Wextra -Wshadow -Imodels
TRICK_USER_LINK_LIBS += -larmadillo -lboost_serialization -lgsl -lgslcblas \
			-I$(DRONE_HOME)/models/drone/include/ \
			-I$(DRONE_HOME)/models/wind/include/ \
			-I$(DRONE_HOME)/models/dynamic/include/
MAKEFLAGS += -j16
