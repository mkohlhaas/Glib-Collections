CFLAGS  += $(shell pkg-config --cflags glib-2.0)
LDFLAGS += $(shell pkg-config --libs   glib-2.0)
binaries = ex-compile \
           ex-garray-1 \
           ex-garray-2 \
           ex-garray-3 \
           ex-garray-4 \
           ex-garray-5 \
           ex-garray-6 \
           ex-garray-7 \
           ex-garray-8 \
           ex-ghashtable-1 \
           ex-ghashtable-2 \
           ex-ghashtable-3 \
           ex-ghashtable-4 \
           ex-ghashtable-5 \
           ex-ghashtable-6 \
           ex-ghashtable-7 \
           ex-glist-1 \
           ex-glist-2 \
           ex-glist-3 \
           ex-glist-4 \
           ex-gqueue-1 \
           ex-gqueue-2 \
           ex-gqueue-3 \
           ex-gqueue-4 \
           ex-gqueue-5 \
           ex-gqueue-6 \
           ex-gslist-01 \
           ex-gslist-02 \
           ex-gslist-03 \
           ex-gslist-04 \
           ex-gslist-05 \
           ex-gslist-06 \
           ex-gslist-07 \
           ex-gslist-08 \
           ex-gslist-09 \
           ex-gslist-10 \
           ex-gslist-11 \
           ex-gtree-1 \
           ex-gtree-2 \
           ex-gtree-3 \
           ex-gtree-4 \
           ex-gtree-5 \
           ex-gtree-6

.PHONY: all clean

# Build mode for project: DEBUG or RELEASE
BUILD_MODE            ?= DEBUG

ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g -pg -O0
endif

all: $(binaries)

clean:
	@rm -f $(binaries)
