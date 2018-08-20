include Config
all:

# ************* #
# Real targets. #
# ************* #

# Interface headers.
FACE_INCS = $(wildcard bbmacro/*.h)

# Proof of compilability.
PROOF_SRCS = proof.c
PROOF_OBJS = $(patsubst %.c, build/%.o, $(PROOF_SRCS))

$(PROOF_OBJS): build/%.o: %.c $(FACE_INCS)
	@mkdir -p build
	$(CC) $(ALL_CFLAGS) -c $< -I. -o $@

# Demo programs.
DEMO_SRCS = $(wildcard demo/*.c)
DEMO_BINS = $(patsubst demo/%.c, build/%, $(DEMO_SRCS))

$(DEMO_BINS): build/%: demo/%.c $(FACE_INCS)
	@mkdir -p build
	$(CC) $(ALL_CFLAGS) $(ALL_LDFLAGS) $< -I. -o $@

# ************** #
# Phony targets. #
# ************** #

.PHONY: all proof demo install clean dist

all:
proof: $(PROOF_OBJS)
demo: $(DEMO_BINS)

install: all
	install -m644 $(FACE_INCS) -Dt $(DESTDIR)$(INCDIR)/bbmacro
clean:
	rm -rf build
dist:
	@mkdir -p build
	tar -zcf build/$(TARNAME).tar.gz --transform="s/^\./$(TARNAME)/" \
		--exclude="./build" --exclude="./.*" .
