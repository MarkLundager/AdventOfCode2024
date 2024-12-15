CC = gcc
CFLAGS = -Wall -Werror -pedantic -g
LDFLAGS = -lcurl -lm
PARSER_FILES = helper_functions.c
#DAYS = $(shell seq 1 9)
DAYS = $(shell seq -w 1 11)
all: $(foreach DAY, $(DAYS), ./day$(DAY)/day$(DAY))

%: %.c $(PARSER_FILES)
	$(CC) $(CFLAGS) -o  $@ $^ $(LDFLAGS)


test:
	./run.sh $(DAYS)

#gcc -Wall -Werror -pedantic -g -o day9 day9.c ../helper_functions.c -lcurl
#gcc -Wall -Werror -pedantic -O2 -o day11 day11.c ../helper_functions.c -lcurl