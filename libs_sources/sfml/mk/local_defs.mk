# Definitions for Makefile
NAME=			$(ROOT_DIR)/lib/lib_arcade_sfml.so

LOCAL_COMP_FLAGS=	-fPIC

ifeq ($(UNAME_S),Darwin)
LOCAL_LINK_FLAGS=	-shared -F/Library/Frameworks -framework sfml-graphics -framework sfml-window -framework sfml-system -framework sfml-audio
else
LOCAL_LINK_FLAGS=	-shared -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
endif

LOCAL_LINK_FLAGS+=	-L$(ROOT_DIR)/build -larcade_common

LOCAL_DEBUG_FLAGS=
