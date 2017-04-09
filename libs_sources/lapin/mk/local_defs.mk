# Definitions for Makefile
NAME=			$(ROOT_DIR)/lib/lib_arcade_lapin.so

LOCAL_COMP_FLAGS=	-fPIC

LOCAL_LINK_FLAGS=	-shared				\
			-L${HOME}/.froot/lib/		\
			-llapin -lsfml-graphics 	\
			-lsfml-audio -lsfml-window	\
			-lsfml-system -lm		\
			-ldl -lpthread			\
			-L$(ROOT_DIR)/build -larcade_common -larcade_exceptions

LOCAL_DEBUG_FLAGS=
