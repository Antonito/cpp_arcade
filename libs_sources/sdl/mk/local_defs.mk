# Definitions for Makefile
NAME=			$(ROOT_DIR)/lib/lib_arcade_sdl.so

LOCAL_COMP_FLAGS=	-fPIC

ifeq ($(UNAME_S),Darwin)
LOCAL_LINK_FLAGS=	-shared -F/Library/Frameworks -framework SDL2 -framework SDL2_ttf -lSDL2_image
else
LOCAL_LINK_FLAGS=	-shared -lSDL2 -lSDL2_image -lpng -lSDL2_ttf
endif

LOCAL_LINK_FLAGS+=	-L$(ROOT_DIR)/build -larcade_common -larcade_exceptions

LOCAL_DEBUG_FLAGS=
