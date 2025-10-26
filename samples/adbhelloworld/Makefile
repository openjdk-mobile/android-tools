# Android NDK: replace with the location to your Android NDK
ANDROID_NDK ?= /opt/android-ndk-r29
# OpenJDK: replace with the build directory of your OpenJDK for Android
JDK ?= /home/johan/openjdk/github/mobile/build/android-aarch64-server-release

ABI ?= aarch64
SYSROOT := $(ANDROID_NDK)/toolchains/llvm/prebuilt/linux-x86_64/sysroot
API := 32

OPENJDK_INCLUDE := $(JDK)/jdk/include
OPENJDK_INCLUDE_PLATFORM := $(OPENJDK_INCLUDE)/android

CXX:= $(ANDROID_NDK)/toolchains/llvm/prebuilt/linux-x86_64/bin/$(ABI)-linux-android$(API)-clang
CC := $(ANDROID_NDK)/toolchains/llvm/prebuilt/linux-x86_64/bin/$(ABI)-linux-android$(API)-clang

BINARY := hellojava

DEVICE_PATH := /data/local/tmp/$(BINARY)

CFLAGS := -O2 -fPIC
CFLAGS += -I$(OPENJDK_INCLUDE) -I$(OPENJDK_INCLUDE_PLATFORM) 
CFLAGS += --sysroot=$(SYSROOT)

STLFLAGS := -L$(ANDROID_NDK)/sources/cxx-stl/llvm-libc++/libs/$(ABI) -lc++_static -lc++abi

LDFLAGS := -lm -ldl -llog -lc++_static -lc++abi -L$(JDK)/images/static-libs/lib -L$(JDK)/images/static-libs/lib/server  -Wl,--export-dynamic  -ljvm -ljimage -Wl,--whole-archive -ljava -lnio -lnet -Wl,--no-whole-archive

SRCS := hellojava.c
OBJS := $(SRCS:.c=.o)

.PHONY: all clean run

all: $(BINARY)

# Build the executable
$(BINARY): $(OBJS)
	$(CXX) $(OBJS) $(LIBJVM) $(STLFLAGS) -o $(BINARY) $(LDFLAGS) --sysroot=$(SYSROOT)

%.o: %.c
	$(CXX) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(BINARY)
	rm -f $(OBJS)

# Push and run on connected device
run: all
	adb push $(BINARY) $(DEVICE_PATH)
	adb shell chmod +x $(DEVICE_PATH)
	adb shell $(DEVICE_PATH)

