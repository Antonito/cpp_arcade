# Definitions for Makefile
NAME=			$(ROOT_DIR)/arcade

LOCAL_COMP_FLAGS=

LOCAL_LINK_FLAGS=	-ldl -L$(ROOT_DIR)/build/ -larcade_common -larcade_network -lgames_common

LOCAL_DEBUG_FLAGS=
