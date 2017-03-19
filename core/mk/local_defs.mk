# Definitions for Makefile
NAME=			../arcade

INC_DIR=		-I./src/exceptions/		\
			-I./src/network/		\
			-I./src/logger/			\
			-I./src/			\
			-I./../common/

LOCAL_COMP_FLAGS=

LOCAL_LINK_FLAGS=	-ldl

LOCAL_DEBUG_FLAGS=
