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
vpath %.tns $(DISTDIR)
vpath %.elf $(DISTDIR)
vpath %.$(DESKEXT) $(DISTDIR)

ifeq ($(XPLAT_TARGET), nspire)
nspire: $(EXE).prg.tns
else ifeq ($(XPLAT_TARGET), desktop)
desktop: $(EXE).$(DESKEXT)
endif

CXXFILES = $(shell find . -name \*.cpp)
HEADERFILES = $(shell find . -name \*.h)

$(info Compile: [${GXX} ${CFLAGS}])

.PHONY: all clean assets

ifeq ($(XPLAT_TARGET), nspire)

$(EXE).tns: $(EXE).elf
	$(GENZEHN) --input $(DISTDIR)/$^ --output $(DISTDIR)/$@ $(ZEHNFLAGS)

$(EXE).prg.tns: $(EXE).tns
	make-prg $(DISTDIR)/$^ $(DISTDIR)/$@

$(EXE).elf: $(CXXFILES) $(HEADERFILES)
	mkdir -p $(DISTDIR)
	$(GXX) $(CFLAGS) $(CXXFILES) -o $(DISTDIR)/$(EXE).elf

else ifeq ($(XPLAT_TARGET), desktop)

$(EXE).$(DESKEXT): $(CXXFILES) $(HEADERFILES)
	mkdir -p $(DISTDIR)
	$(GXX) $(CFLAGS) $(CXXFILES) $(LINKLIBS) -o $(DISTDIR)/$(EXE).$(DESKEXT)

endif

ASSET_PATH = ./assets
assets:
	$(info Copying assets)
	cp -r $(ASSET_PATH)/* $(DISTDIR)

clean:
	find . -name \*.o -type f -delete
	rm -f $(DISTDIR)/*.tns $(DISTDIR)/$(EXE).elf $(DISTDIR)/$(EXE).$(DESKEXT)