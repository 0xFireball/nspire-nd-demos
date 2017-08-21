PRG_NAME = nd-demos

DEBUG = FALSE
XPLAT_TARGET=nspire

$(info Building for xplat target [${XPLAT_TARGET}])

ifeq ($(XPLAT_TARGET), nspire)
GCC = nspire-gcc
AS  = nspire-as
GXX = nspire-g++
LD  = nspire-ld
GENZEHN = genzehn
else
GCC = gcc
AS = as
GXX = g++
LD = ld
endif

CFLAGS += -Wall -W --std=c++14
LDFLAGS =
ZEHNFLAGS = --name $(PRG_NAME)

ifeq ($(XPLAT_TARGET), nspire)
	CFLAGS += -marm -Dnspire
else ifeq ($(XPLAT_TARGET), desktop)
	CFLAGS += -Ddesktop
endif

DESKEXT = bin
LINKLIBS =

CYGWIN = FALSE
ifeq ($(CYGWIN), 1)
$(info Enabling support for Cygwin/Windows: [${CYGWIN}])
	CFLAGS += -Lcyg/lib -Icyg/include -mwindows
	LINKLIBS += -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_gfx
	DESKEXT = exe
else
	CFLAGS += -I/usr/include/SDL
	LINKLIBS += -lSDL -lSDL_gfx
endif

ifeq ($(DEBUG),FALSE)
	CFLAGS += -Os
else
	CFLAGS += -O0 -g
endif

ADDFLAGS =
CFLAGS += $(ADDFLAGS)

OBJS = $(patsubst %.c, %.o, $(shell find . -name \*.c))
OBJS += $(patsubst %.cpp, %.o, $(shell find . -name \*.cpp))
OBJS += $(patsubst %.S, %.o, $(shell find . -name \*.S))
EXE = $(PRG_NAME)
DISTDIR = .

ifeq ($(XPLAT_TARGET), nspire)
TARGET=$(DISTDIR)/$(EXE).prg.tns
else ifeq ($(XPLAT_TARGET), desktop)
TARGET=$(DISTDIR)/$(EXE).$(DESKEXT)
endif

all: res exe

res: dirs assets

ASSET_PATH = ./assets
ASSET_FILES = $(shell find $(ASSET_PATH) -name \*.\*)
assets: $(ASSET_FILES)
	$(info Copying assets)
	cp -r $^ $(DISTDIR)

dirs:
	mkdir -p $(DISTDIR)

CXXFILES = $(shell find . -name \*.cpp)
HEADERFILES = $(shell find . -name \*.h)

$(info Compile: [${GXX} ${CFLAGS}])

ifeq ($(XPLAT_TARGET), nspire)

exe: $(EXE).tns
	make-prg $(DISTDIR)/$^ $(TARGET)

$(EXE).tns: $(EXE).elf
	$(GENZEHN) --input $(DISTDIR)/$^ --output $(DISTDIR)/$@ $(ZEHNFLAGS)

$(EXE).elf: $(CXXFILES) $(HEADERFILES)
	$(GXX) $(CFLAGS) $(CXXFILES) -o $(DISTDIR)/$(EXE).elf

else ifeq ($(XPLAT_TARGET), desktop)

exe: $(CXXFILES) $(HEADERFILES)
	$(GXX) $(CFLAGS) $(CXXFILES) $(LINKLIBS) -o $(TARGET)

endif

clean:
	find . -name \*.o -type f -delete
	rm -f $(DISTDIR)/*.tns $(DISTDIR)/$(EXE).elf $(TARGET)

.PHONY: all clean
