CC     := gcc
CFLAGS := -O0 -g

OBJS   := time_attack_strcmp.o
BIN    := main

ifdef DEBUG
CFLAGS += -DDEBUG=$(DEBUG)
endif

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
	@echo "  CC $<"

valgrind:
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./$(BIN) 10

clean:
	rm -f $(OBJS) $(BIN)
