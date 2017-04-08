# Definitions for Makefile
NAME=			$(ROOT_DIR)/server_arcade

INC_DIR=		$(ROOT_DIR)/network/src/		\
			$(ROOT_DIR)/network/src/exceptions	\
			$(ROOT_DIR)/common/src		\
			$(ROOT_DIR)/exceptions/src

LOCAL_COMP_FLAGS=

LOCAL_LINK_FLAGS=	-L$(ROOT_DIR)/build/ -larcade_network -larcade_exceptions -pthread

LOCAL_DEBUG_FLAGS=
