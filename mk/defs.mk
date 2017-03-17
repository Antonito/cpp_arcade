# Commands definitions
RM=		rm -f
RM_DIR=		rm -rf
ECHO=		echo -ne
RANLIB=		ar rcs
CP=		cp
CHDIR=		cd
MKDIR=		mkdir

ROOT_DIR:=	$(realpath $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))/../)
INSTALL_DIR=	bin/
INSTALL_PATH=	$(ROOT_DIR)/$(INSTALL_DIR)

# Compilation and link definitions
CXX=		clang++
CPP_VER=	c++14

# Debug Infos | -lasan needs to be first
ifeq ($(DEBUG), yes)
CXXFLAGS=	-g -DDEBUG $(LOCAL_DEBUG_FLAGS)
LDFLAGS=	-g
else
CXXFLAGS=	-DNDEBUG
LDFLAGS=
endif

CXXFLAGS+=	$(INC_DIR)			\
		$(LOCAL_COMP_FLAGS)

LDFLAGS+=	-lstdc++			\
		$(LOCAL_LINK_FLAGS)

ifeq ($(CXX),clang++)
CXXFLAGS+=	-std=$(CPP_VER) -W -Wall -Wextra
LDFLAGS+=
else ifeq ($(CXX),g++)
CXXFLAGS+=	-std=$(CPP_VER) -W -Wall -Wextra
LDFLAGS+=
else
CXXFLAGS+=
LDFLAGS+=
endif
