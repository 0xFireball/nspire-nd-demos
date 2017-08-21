PRG_NAME = nd-demos

DEBUG = FALSE
PLATFORM=desktop
OUTDIR=build

$(info Building for xplat target [${PLATFORM}])

ifeq ($(PLATFORM), nspire)
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

ifeq ($(PLATFORM), nspire)
	CFLAGS += -marm -Dnspire
else ifeq ($(PLATFORM), desktop)
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

ifeq ($(PLATFORM), nspire)
TARGETBIN=$(OUTDIR)/$(EXE).prg.tns
else ifeq ($(PLATFORM), desktop)
TARGETBIN=$(OUTDIR)/$(EXE).$(DESKEXT)
endif

all: res exe

res: dirs assets

ASSET_PATH = ./assets
ASSET_FILES = $(shell find $(ASSET_PATH) -name \*.\*)
assets: $(ASSET_FILES)
	$(info Copying assets)
	cp -r $^ $(OUTDIR)

dirs:
	mkdir -p $(OUTDIR)

CXXFILES = $(shell find . -name \*.cpp)
HEADERFILES = $(shell find . -name \*.h)

$(info Compile: [${GXX} ${CFLAGS}])

ifeq ($(PLATFORM), nspire)

exe: $(EXE).tns
	make-prg $(OUTDIR)/$^ $(TARGETBIN)

$(EXE).tns: $(EXE).elf
	$(GENZEHN) --input $(OUTDIR)/$^ --output $(OUTDIR)/$@ $(ZEHNFLAGS)

$(EXE).elf: $(CXXFILES) $(HEADERFILES)
	$(GXX) $(CFLAGS) $(CXXFILES) -o $(OUTDIR)/$(EXE).elf

else ifeq ($(PLATFORM), desktop)

exe: $(CXXFILES) $(HEADERFILES)
	$(GXX) $(CFLAGS) $(CXXFILES) $(LINKLIBS) -o $(TARGETBIN)

endif

clean:
	find . -name \*.o -type f -delete
	rm -f $(OUTDIR)/*.tns $(OUTDIR)/$(EXE).elf $(TARGETBIN)

.PHONY: all assets clean
