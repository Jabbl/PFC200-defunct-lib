#CROSS_COMPILE=arm-cortexa8-linux-gnueabihf-
#CC=$(CROSS_COMPILE)gcc
#SYSROOT = /home/wago/wago/ptxproj-2.6.20/platform-wago-pfcXXX/sysroot-target
#INCLUDE_PATH += -I$(SYSROOT)/usr/include
#CFLAGS += -Wall -pedantic -g -O2 $(INCLUDE_PATH)
#LDFLAGS += -L$(SYSROOT)/usr/lib
#AR=$(CROSS_COMPILE)ar
#LD=$(CROSS_COMPILE)ld

#
# Simple makefile to create a shared library.
# Note that all required environment variables are passed via ptxdist.
#

CXX += -std=gnu++11
export CXX

#
#Set SILENCE=@ to keep the makefile quiet.
#
SILENCE=@
export SILENCE

# Set warning level for this makefile and all subsequent
# We want all standard warnings + missing prototypes (can be dangerous). Be strict and treat all warnings as errors.
WARNINGS = -Wall -Wmissing-prototypes -Werror
export WARNINGS

CXXWARNINGS = -Wall -Wmissing-declarations -pedantic-errors -Wextra -Wshadow -Wno-type-limits -Werror
export CXXWARNINGS

# Defines for the C- compiler
DEFINES = -fPIC -funwind-tables -rdynamic
export DEFINES

CXXDEFINES = -fno-exceptions -fPIC -funwind-tables -rdynamic -fno-rtti
export CXXDEFINES

# Level of optimization (2 is most used for production)
OPTIMIZATION = -O2
export OPTIMIZATION

# Debugging level (0 = no debug info at all, 2 = standard debug info)
DEBUGGING = -g2
export DEBUGGING

STD_CXXFLAGS += $(CXXWARNINGS) $(DEBUGGING) $(OPTIMIZATION) $(CXXDEFINES)

TARGET=libbacnet

# Name of the library to build.
TARGET_LIB=$(TARGET).so
TARGET_LIB_TESTLINK = $(TARGET).check.bin

BACNET_PORT = linux

# Headers
BACNET_CODESYS_V2_INCLUDE = ../include

HEADER_PATHS = -I$(BACNET_CODESYS_V2_INCLUDE)
HEADER_PATHS += -Ilib/lz4/headers 
#HEADER_PATHS += -I/home/powertech/Wago/ptxproj-2.6.20/platform-wago-pfcXXX/sysroot-host/include/libxml2

# For using KBUS
HEADER_PATHS += -I"$(SYSROOT)/usr/include/OsLinux"
HEADER_PATHS += -I"$(SYSROOT)/usr/include/dal"
HEADER_PATHS += -I"$(SYSROOT)/usr/include"
LIBRARY_REFS += -ltypelabel -loslinux -ldbuskbuscommon
LIBRARY_REFS += -ldal -llibloader -lpthread -lffi -lrt -ldbus-glib-1 -lglib-2.0
LIBRARY_REFS += -lcurl


#
# add more flags here,
# but don't remove the "+="
# the CFLAGS and LDFLAGS are passed via ptxdist, aswell as CC,CXX,LD,AR etc.

# CFLAGS ^= flags for the c-compiler only.
CFLAGS 	 += -c $(WARNINGS) $(DEBUGGING) $(OPTIMIZATION) $(DEFINES) -g $(HEADER_PATHS) -include ../../settings.h

# CPPFLAGS ^= flags for both the c- and cpp-compiler.
CPPFLAGS +=

# CXXFLAGS ^= flags for the cpp-compiler only.
CXXFLAGS += $(STD_CXXFLAGS) -g $(HEADER_PATHS)

# LDFALGS ^= flags for the linker.
LDFLAGS  += $(LIBRARY_REFS) -rdynamic -shared -Wl,-soname,$(TARGET_LIB)


BACNET_CODESYS_V2 = ../src


CODESYS_V2_SRC = \
	$(BACNET_CODESYS_V2)/TestLib.c \
	$(BACNET_CODESYS_V2)/codesys.c \
	$(BACNET_CODESYS_V2)/starter.c \
	

CODESYS_V2_SRC_CXX = \
	$(BACNET_CODESYS_V2)/cpp/OctetString.cpp \
	$(BACNET_CODESYS_V2)/cpp/appDataValue2.cpp \
	$(BACNET_CODESYS_V2)/runner.cpp \


CODESYS_V2_TESTLINK_SRC = $(BACNET_CODESYS_V2)/verify_external_dependencies.c


#
# Add additional source files here
#
SRC = $(CODESYS_V2_SRC)

CXX_SRC = $(CODESYS_V2_SRC_CXX)


#
# External libraries
#
BACNET_PORT = arm7

#
# Convert *.c to *.o
#
C_OBJ = $(SRC:.c=.o)

CXX_OBJS = $(CXX_SRC:.cpp=.o)

# make all builds the lib including its test
all: $(TARGET_LIB_TESTLINK)


# cleans .o files
clean:
	$(RM) $(C_OBJ)
	$(RM) $(CXX_OBJS)
	$(RM) $(TARGET_LIB)
	$(RM) $(TARGET_LIB_TESTLINK)


# Linker rule
$(TARGET_LIB): $(C_OBJ) $(CXX_OBJS)
	@echo Linking $(notdir $@)
	$(SILENCE)$(LINK.o) $^ -o $@

# Check for missing references by compiling a seperate file with main() and linking the entire library to it
$(TARGET_LIB_TESTLINK): $(TARGET_LIB) $(CODESYS_V2_TESTLINK_SRC)
	@echo Checking for missing references
	$(SILENCE)$(CC) $(CODESYS_V2_TESTLINK_SRC) $(TARGET_LIB) -o $(TARGET_LIB_TESTLINK)

# Compiler rule
%.o: %.c
	$(SILENCE)echo Compiling $(basename $<).c
	$(SILENCE)$(COMPILE.c) $< -o $@

.cpp.o:
	@echo Compiling $(basename $<).cpp
	$(SILENCE)${CXX} -c ${CXXFLAGS} $*.cpp -o $@

.PHONY: all install clean

# end of development makefile
