CC = gcc
CFLAGS = -Wall -Werror -pedantic -g
LDFLAGS = -lcurl
PARSER_FILES = helper_functions.c
DAYS = $(shell seq 1 30)

all: $(foreach DAY, $(DAYS), ./day$(DAY)/day$(DAY))

%: %.c $(PARSER_FILES)
	$(CC) $(CFLAGS) -o  $@ $^ $(LDFLAGS)


test:
	./run.sh $(DAYS)

